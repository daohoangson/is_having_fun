<?php

error_reporting(E_ALL);
ini_set('display_errors', 1);
$dupes = file('./dupes.txt');
$imagedupes = file('./imagedupes.txt');
// $lsAld = file('./ls-ald.txt');
$prefix = '/mnt/volume-sfo2-02/docker-rclone-data/';
$primary = 'Photos/';
$secondary = 'Phones/';
$data = array();
$index = array();
$sizes = array();
$similarNotDupes = array();

function escapeSpaces($str) {
	return str_replace(' ', '\ ', $str);
}

foreach($imagedupes as $line) {
	$parts = preg_split('#' . preg_quote($prefix, '#') . '#', $line, -1, PREG_SPLIT_NO_EMPTY);
	if (count($parts) < 2) {
		// too few parts
		var_dump($line, $parts);
		die(1);
	}

	$partKey = '';
	$partValues = array();
	foreach ($parts as $part) {
		$part = trim($part);
		if (substr($part, 0, strlen($primary)) === $primary) {
			$partKey = $part;
		} elseif (substr($part, 0, strlen($secondary)) !== $secondary) {
			// unexpected prefix
			var_dump($line, $part);
			die(1);
		}

		$partValues[] = $part;
	}

	if ($partKey === '') {
		$partKey = reset($partValues);
	}
	if (isset($data[$partKey])) {
		// data exists
		var_dump($line, $data);
		die(1);
	}
	$data[$partKey] = array(
		'imagedupes' => $partValues,
		// 'dupes' => array(),
	);

	foreach ($partValues as $partValue) {
		$index[$partValue] =& $data[$partKey];
	}
}

$lineNo = 0;
while(true) {
	if (count($dupes) === 0) {
		// done
		break;
	}
	if (count($dupes) < 3) {
		// too few lines
		var_dump($lineNo, $dupes);
		die(1);
	}

	$lines = array();
	$lines[] = array_shift($dupes);
	$lines[] = array_shift($dupes);
	while ($lines[count($lines) - 1] !== "\n") {
		$lines[] = array_shift($dupes);
	}
	$lineNo += count($lines);

	if (count($lines) > 3) {
		$basename = basename(trim($lines[0]));
		if ($basename === '.DS_Store') {
			continue;
		}

		// dupes should be 1 vs 1 only
		var_dump($lineNo, $lines, $basename);
		die(1);
	}
	$line1 = $lines[0];
	$line2 = $lines[1];

	if (substr($line1, 0, strlen($prefix)) !== $prefix) {
		// bad first line (wrong prefix)
		var_dump($lineNo, $line1);
		die(1);
	}
	$path1 = trim(substr($line1, strlen($prefix)));

	if (substr($line2, 0, strlen($prefix)) !== $prefix) {
		// bad 2nd line (wrong prefix)
		var_dump($lineNo, $line2);
		die(1);
	}
	$path2 = trim(substr($line2, strlen($prefix)));

	if (!isset($index[$path1])) {
		// index not found
		// var_dump($lineNo, $path1, $path2);
		// die(1);
		continue;
	}
	$index[$path1]['dupes'][$path1] = $path2;
}

// foreach ($lsAld as $line) {
// 	$size = intval(substr($line, 23, 9));
// 	$path = trim(substr($line, 44));
// 	if (substr($path, 0, strlen($prefix)) !== $prefix) {
// 		// bad prefix
// 		var_dump($line, $size, $path);
// 		die(1);
// 	}

// 	$path = substr($path, strlen($prefix));
// 	$sizes[$path] = $size;
// }

foreach ($data as $set) {
	// if (count($set['imagedupes']) !== 2) {
		// continue;
	// }

	// $found = array();
	$foundSomething = false;
	foreach ($set['imagedupes'] as $path) {
		if (isset($set['dupes'][$path])) {
			// $found[] = $path;
			continue;
		} elseif (!empty($set['dupes']) && array_search($path, $set['dupes'], true) !== false) {
			// $found[] = $path;
			continue;
		}

		// $found[] = sprintf('scp "root@138.68.232.99:%s%s" "./%d-%s"',
		// 	escapeSpaces($prefix),
		// 	escapeSpaces($path),
		// 	count($similarNotDupes),
		// 	basename($path)
		// );
		// $fullPath = sprintf('%s%s', $prefix, $path); 

		// if (!isset($sizes[$path])) {
		// 	// no size info
		// 	var_dump($set, $fullPath);
		// 	die(1);
		// }
		// $found[$fullPath] = $sizes[$path];
		$foundSomething = true;
	}
	// if (empty($found)) {
	// 	continue;
	// }

	// $similarNotDupes[] = $found;

	if ($foundSomething) {
		$similarNotDupes[] = $set['imagedupes'];
	}
}

// var_export($data);
foreach ($similarNotDupes as $similar) {
	// $setSizes = array_values($similar);
	// $sizeDelta = max($setSizes) - min($setSizes);
	// $percent = $sizeDelta / max($setSizes) * 100;
	// if ($percent < .5) {
	// 	continue;
	// }

	// foreach ($similar as $path => $size) {
	// 	echo(sprintf("%s - %s\n", $path, $size));
	// }
	// echo(sprintf("\$sizeDelta = %d, \$percent=%.2f%%\n", $sizeDelta, $percent));

	foreach ($similar as $path) {
		echo(sprintf("%s%s\n", $prefix, $path));
	}
	echo("\n");
}
