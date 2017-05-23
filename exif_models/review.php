<?php

$dupes = file('./similar.txt');
$images = array();
$basics = array();
$priorities = array('path' => array());

$linesTotal = count($dupes);
$lineNo = filter_input(INPUT_GET, 'line_no', FILTER_VALIDATE_INT);
if ($lineNo <= 0) {
	$lineNo = 0;
}
while($lineNo < $linesTotal) {
	if ($lineNo > $linesTotal - 2) {
		printf("Invalid line_no %d (total %d)\n", $lineNo, $linesTotal);
		var_dump($dupes);
		die(1);
	}

	$lines = array();
	$lines[] = $dupes[$lineNo++];
	$lines[] = $dupes[$lineNo++];
	while ($lines[count($lines) - 1] !== "\n" && $lineNo < $linesTotal) {
		$lines[] = $dupes[$lineNo++];
	}

	$paths = array();
	foreach ($lines as $line) {
		$line = trim($line);
		if (strlen($line) === 0) {
			continue;
		}
		$path = $line;

		if (!file_exists($path)) {
			$pathBak = $path . '.bak';
			if (!file_exists($pathBak)) {
				printf("File not exists %s\n", $path);
				exit(1);
			}
			$path = $pathBak;
		}

		$paths[] = $path;
	}

	foreach ($paths as $path) {
		$image = new Imagick($path);
		$imageWidth = $image->getImageWidth();
		$imageHeight = $image->getImageHeight();
		if (empty($imageWidth) || empty($imageHeight)) {
			printf("Invalid image: %s\n", $path);
			exit(1);
		}

		$basics[$path]['size'] = filesize($path);
		$basics[$path]['width'] = $imageWidth;
		$basics[$path]['height'] = $imageHeight;

		$shortSideLength = 75;
		$ratio = $imageWidth / $imageHeight;
		if ($ratio > 1) {
			$width = ceil($shortSideLength * $ratio);
			$height = $shortSideLength;
		} else {
			$width = $shortSideLength;
			$height = ceil(max(1, $shortSideLength / $ratio));
		}
		foreach ($image AS $frame) {
			$frame->thumbnailImage($width, $height, true, true);
			$frame->setImagePage($width, $height, 0, 0);
		}

		$images[$path] = $image;
	}

	break;
}
$nextLink = sprintf('review.php?line_no=%d', $lineNo);

$savePaths = filter_input(INPUT_POST, 'paths', FILTER_DEFAULT, FILTER_REQUIRE_ARRAY);
$savePrimary = filter_input(INPUT_POST, 'primary');
if (!empty($savePrimary)) {
	foreach($savePaths as $savePath) {
		if (!isset($images[$savePath])) {
			printf("Invalid save path %s\n", $savePath);
			die(1);
		}
	}
	if (!isset($images[$savePrimary])) {
		printf("Invalid save primary %s\n", $savePrimary);
		die(1);
	}
	foreach ($savePaths as $savePath) {
		if ($savePath === $savePrimary) {
			continue;
		}

		$savePathBak = $savePath . '.bak';
		if (file_exists($savePathBak)) {
			printf("Backup file exists for %s\n", $savePath);
			die(1);
		}
		if (!rename($savePath, $savePathBak)) {
			printf("Cannot rename %s to %s\n", $savePath, $savePathBak);
			die(1);
		}
		if (!copy($savePrimary, $savePath)) {
			printf("Cannot copy %s to %s\n", $savePrimary, $savePath);
			die(1);
		}
	}

	if (!empty($nextLink)) {
		header('Location: '. $nextLink);
	} else {
		echo("All done!\n");
	}
	die(0);
}

$data = array();
$dataCommon = null;
foreach (array_keys($images) as $path) {
	$pathData = @exif_read_data($path);
	if (empty($pathData)) {
		$pathData = array();
	}
	$data[$path] = $pathData;
}
function findDataCommon(array $a, array $b) {
	$c = array();
	foreach (array_keys($a) as $k) {
		if (!isset($b[$k])) {
			continue;
		}
		if (is_array($a[$k]) && is_array($b[$k])) {
			$ck = findDataCommon($a[$k], $b[$k]);
			if (!empty($ck)) {$c[$k] = $ck;}
			continue;
		}
		if ($a[$k] === $b[$k]) {
			$c[$k] = $a[$k];
			continue;
		}
	}
	return $c;
}
function findDataDiff(array $a, array $b) {
	$d = array();
	foreach (array_keys($a) as $k) {
		if (!isset($b[$k])) {
			$d[$k] = $a[$k];
			continue;
		}
		if (is_array($a[$k]) && is_array($b[$k])) {
			$dk = findDataDiff($a[$k], $b[$k]);
			if (!empty($dk)) {$d[$k] = $dk;}
			continue;
		}
		if ($a[$k] !== $b[$k]) {
			$d[$k] = $a[$k];
			continue;
		}
	}
	foreach (array_keys($b) as $k) {
		if (!isset($a[$k])) {
			$d[$k] = $b[$k];
			continue;
		}
	}
	ksort($d);
	return $d;
}
foreach ($data as $pathData) {
	if ($dataCommon === null) {
		$dataCommon = $pathData;
		continue;
	}
	$dataCommon = findDataCommon($dataCommon, $pathData);
}

echo '<form method="POST">';

$summaries = array('size' => array(), 'width' => array(), 'height' => array());
$dimensionMatches = false;
$autoCheckes = array();
foreach (array_keys($images) as $path) {
	$summaries['size'][] = $basics[$path]['size'];
	$summaries['width'][] = $basics[$path]['width'];
	$summaries['height'][] = $basics[$path]['height'];
}
if (min($summaries['width']) == max($summaries['width'])
	&& min($summaries['height']) == max($summaries['height'])) {
	$dimensionMatches = true;
}

$sizeDelta = (max($summaries['size']) - min($summaries['size']));
foreach (array_keys($images) as $path) {
	$autoCheckes[$path] = 0;
	if ($sizeDelta == 0) {
		continue;
	}

	if ($dimensionMatches
		&& ($basics[$path]['size'] == min($summaries['size']))
	) {
		// get the smallest file if dimension matches
		$autoCheckes[$path] += 10;
	}

	if (!$dimensionMatches
		&& $basics[$path]['width'] == max($summaries['width'])
		&& $basics[$path]['height'] == max($summaries['height'])
	) {
		// get the largest dimension
		$autoCheckes[$path] += 10;
	}

	if (!empty($priorities['path'])) {
		foreach ($priorities['path'] as $priorityPath => $point) {
			if (strpos($path, $priorityPath) !== false) {
				$autoCheckes[$path] += $point;
			}
		}
	}
}

foreach ($images as $path => $image) {
	echo '<input type="hidden" name="paths[]" value="', htmlentities($path), '" />';
	echo '<h2>', $path, '</h2>';
	echo '<table><tbody></tr>';
	echo '<td valign="top"><img src="data:image/', $image->getImageFormat(), ';base64,', base64_encode($image->getImageBlob()), '" ';
	echo 'width="', $image->getImageWidth(), '" ';
	echo 'height="', $image->getImageHeight(), '" ';
	echo '/></td>';
	echo '<td valign="top" style="position: relative; width: 100%;"><div style="height: 100%; overflow: scroll; position: absolute; width: 100%;"><div>';
	echo '<label><input type="radio" name="primary" ';

	if ($autoCheckes[$path] > 0 && $autoCheckes[$path] == max($autoCheckes)) {
		echo 'checked="checked" ';
	}

	echo 'value="', htmlentities($path), '" />Is primary</label>';
	if (empty($data[$path])) {
		echo '<pre>', var_export($basics[$path], true), '</pre>';
	} else {
		echo '<pre>', var_export(findDataDiff($data[$path], $dataCommon), true), '</pre>';
	}
	echo '</div></div></td>';
	echo '</tr></tbody></table>';
}

if ($sizeDelta > 0) {
	echo '<p>Delta Size: ', $sizeDelta, '</p>';
} else {
	echo '<p>File size matches</p>';
}
if ($dimensionMatches) {
	echo '<p>Dimension matches</p>';
}

echo '<input type="hidden" name="next" value="', htmlentities($nextLink), '" />';
echo '<input type="submit" value="Save" />';
echo '</form>';

if ($lineNo < $linesTotal) {
	echo '<a href="', htmlentities($nextLink), '">Next</a>';

	if ($sizeDelta === 0 && $dimensionMatches) {
		echo '<script>
			var $secondsToNext = 3;
			function countToNext() {
				if (secondsToNext === 0) {
					return;
				}
				secondsToNext--;
				document.write(secondsToNext + " till next...");
				setTimeout("countToText", 1000);
			}
			countToNext();
		</script>';
	}
}
