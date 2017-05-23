<?php

$cwd = getcwd();
$files = glob($cwd . '/*.*');
$mapping = array();

$l = count($files);
for($i = 0; $i < $l; $i++) {
	$file = $files[$i];
	$basename = basename($file);
	if (strtolower(substr($basename, -4)) !== '.jpg') {
		continue;
	}

	$data = exif_read_data($file);
	$model = '';
	if (!empty($data['Make'])) {
		$data['Make'] = trim($data['Make']);
		$model = $data['Make'];
	}
	if (!empty($data['Model'])) {
		$data['Model'] = trim($data['Model']);
		if (!empty($model)) {
			if (substr($data['Model'], 0, strlen($model)) === $model) {
				// Model already includes Make
				$model = '';
			} else {
				$model .= ' ';
			}
		}
		$model .= $data['Model'];
	}

	// var_dump($file, $model);

	if (empty($model)) {
		continue;
	}

	$target = sprintf('%s/%s', $cwd, $model);
	if (!is_dir($target)) {
		if (!mkdir($target)) {
			die(sprintf("Cannot mkdir %s\n", $target));
		}
	}

	$newFile = sprintf('%s/%s', $target, $basename);
	if (file_exists($newFile)) {
		die(sprintf("Target already exists %s -> %s\n", $basename, $newFile));
	}

	if (!rename($file, $newFile)) {
		die(sprintf("Cannot move %s to %s\n", $file, $newFile));
	}
}

