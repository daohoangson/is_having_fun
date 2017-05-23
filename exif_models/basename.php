<?php

$cwd = getcwd();
$files = glob($cwd . '/*.*');
$tzOffset = 7 * 3600;

require(dirname(__FILE__) . '/getid3/getid3.php');

$l = count($files);
for($i = 0; $i < $l; $i++) {
	$file = $files[$i];
	$basename = basename($file);
	if (substr_count($basename, '.') !== 1) {
		// only process file with exactly one dot (before extension)
		continue;
	}
	$dotPos = strpos($basename, '.');
	$ext = strtolower(substr($basename, $dotPos + 1));
	if (preg_match('#^\d{4}-\d{2}-\d{2} \d{2}\.\d{2}\.\d{2}#', $basename)) {
		// ignore file in correct date time format already
		continue;
	}

	$timestamp = 0;

	if ($timestamp === 0) {
		if (preg_match('#^IMG_(?<Y>\d{4})(?<m>\d{2})(?<d>\d{2})_(?<H>\d{2})(?<i>\d{2})(?<s>\d{2})\.#', $basename, $matches)) {
			$timestamp = gmmktime($matches['H'], $matches['i'], $matches['s'], $matches['m'], $matches['d'], $matches['Y']);
			$timestamp -= $tzOffset;
		}
	}

	if ($timestamp === 0) {
		if (preg_match('#^(?<sec>\d{10})(?<msec>\d{3})\.#', $basename, $matches)) {
			$timestamp = intval($matches['sec']);
		}
	}

	if ($timestamp === 0) {
		$data = @exif_read_data($file);

		foreach(array(
			'DateTimeOriginal',
			'DateTime',
		) as $dateTimeKey) {
			if ($timestamp === 0 && !empty($data[$dateTimeKey])) {
				if (preg_match(
					'#^(?<Y>\d{4}):(?<m>\d{2}):(?<d>\d{2}) (?<H>\d{2}):(?<i>\d{2}):(?<s>\d{2})$#',
					$data[$dateTimeKey],
					$matches
				)) {
					$timestamp = gmmktime($matches['H'], $matches['i'], $matches['s'], $matches['m'], $matches['d'], $matches['Y']);
					$timestamp -= $tzOffset;
				}
			}
		}

		if ($timestamp === 0 && !empty($data['FileDateTime'])) {
			$FileDateTime = intval($data['FileDateTime']);
			if ($FileDateTime !== filemtime($file)) {
				// do not use file modified time if reported by exif
				// those were unreliable
				$timestamp = $FileDateTime;
			}
		}

		// var_dump($data);exit;
	}

	if ($timestamp === 0) {
		$getID3 = new getID3;
		$data = $getID3->analyze($file);
		
		if (!empty($data['tags']['quicktime']['creation_date'][0])) {
			$creationDate = $data['tags']['quicktime']['creation_date'][0];
			$creationDateParsed = strtotime($creationDate);
			if ($creationDateParsed > 0) {
				$timestamp = $creationDateParsed;
			}
		}
	}

	if (empty($timestamp)) {
		die(sprintf("Unable to extract timestamp for %s\n", $file));
	}

	$timestampStr = gmdate('Y-m-d H.i.s', $timestamp + $tzOffset);
	$newFile = sprintf('%s/%s.%s', dirname($file), $timestampStr, $ext);
	if (file_exists($newFile)) {
		die(sprintf("Target already exists %s -> %s\n", $basename, $newFile));
	}
	// var_dump($file, $newFile);exit;

	if (!rename($file, $newFile)) {
		die(sprintf("Cannot move %s -> %s\n", $basename, $newFile));
	} else {
		echo(sprintf("%s -> %s\n", basename($file), basename($newFile)));
		// die(0);
	}
}

