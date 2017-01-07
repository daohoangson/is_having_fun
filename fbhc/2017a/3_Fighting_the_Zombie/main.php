<?php

function solveP($h, $spells)
{
	$bestP = 0;
	foreach ($spells as $spell) {
		$spellP = solveOne($h, $spell);
		$bestP = max($bestP, $spellP);
	}

	return $bestP;
}

function solveOne($h, $spell)
{
	if (!preg_match('#^(?<x>\d+)d(?<y>\d+)(?<z>(\-|\+)\d+)?$#', $spell, $matches)) {
		die(sprintf("Bad spell notation %s\n", $spell));
	}

	$x = intval($matches['x']);
	$y = intval($matches['y']);
	$z = isset($matches['z']) ? intval($matches['z']) : 0;

	$min = $x + $z;
	$max = $x * $y + $z;
	if ($max < $min) {
		$tmp = $min;
		$min = $max;
		$max = $tmp;
	}

	$p = 1;
	if ($min > $h || $max < $h) {
		$p = 0;
	} else {
		for ($i = $min; $i < $h; $i++) {
			$p -= doP($i - $z, $x, $y);
		}
	}

	return $p;
}

# http://mathworld.wolfram.com/Dice.html
# How many ways are there to roll $p with $n $s-sided dice.
function doP($p, $n, $s) 
{
	$result = 0;
	$kFrom = 0;
	$kTo = floor(($p - $n) / $s);
	for ($k = 0; $k <= $kTo; $k++) {
		$result += (pow(-1, $k) * doC($n, $k) * doC($p - $s * $k - 1, $n - 1));
	}

	$result /= pow($s, $n);

	return $result;
}
function doC($n, $r)
{
	$result = doFactorial($n) / doFactorial($r) / doFactorial($n - $r);
	return $result;
}
function doFactorial($n)
{
	if ($n <= 1) {
		return 1;
	}

	static $values = [];
	if (!isset($values[$n])) {
		$values[$n] = $n * doFactorial($n - 1);
	}

	return $values[$n];
}

function main($path)
{
	$input = file_get_contents($path);
	$lines = preg_split('#(\r|\n)#', $input, -1, PREG_SPLIT_NO_EMPTY);
	
	$t = intval(array_shift($lines));
	for ($i = 0; $i < $t; $i++) {
		$line = array_shift($lines);
		list($h, $s) = array_map('intval', preg_split('#[^0-9]#', $line, -1, PREG_SPLIT_NO_EMPTY));
		if ($h < 1) {
			die(sprintf('$h < 1 (%s)', $h));
		}
		if ($s < 1) {
			die(sprintf('$s < 1 (%s)', $s));
		}

		$line = array_shift($lines);
		$spells = preg_split('#\s#', $line, -1, PREG_SPLIT_NO_EMPTY);
		if (count($spells) !== $s) {
			die(sprintf('count($spells) < $s (%d): %s', $s, implode(' ', $spells)));
		}

		$p = solveP($h, $spells);
		echo(sprintf("Case #%d: %.6f\n", $i + 1, $p));
	}
}

main($argv[1]);