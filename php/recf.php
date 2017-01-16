#!/opt/php/bin/php
<?php

$top = "..";

function find_files_recursively($path_name) {
	$files = array();
	$queue = array();
	array_push($queue, $path_name);
	while (count($queue) > 0) {
		$dorf = array_shift($queue);
		if (is_dir($dorf)) {
			$dh = opendir($dorf);
			while (($entry = readdir($dh)) !== false) {
				if ($entry === '.' or $entry === '..')
					continue;
				array_push($queue, $dorf . '/' . $entry);
			}
		} else {
			$files[] = $dorf;
		}
	}
        sort($files, SORT_LOCALE_STRING);
	return $files;
}

$allfiles = find_files_recursively($top);

foreach($allfiles as $pn) {
    echo substr($pn, 0), "\n";
}

