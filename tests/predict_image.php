<?php

chdir(__DIR__);
chdir("..");

function colorrgb($r, $g, $b)
{
    $r = intval(max(0, min(255, $r)));
    $g = intval(max(0, min(255, $g)));
    $b = intval(max(0, min(255, $b)));

    echo "\x1b[48;2;$r;$g;{$b}m";
}

function colorless()
{
    echo "\x1b[0m";
}

$urls = json_decode(file_get_contents("tests/imgurls.json"), true);
$lns = explode("\n", file_get_contents("tests/imgdata.txt"));

$imgsz = 32;

$i = rand(0, count($lns)-1);
$ln = explode(':', $lns[$i]);
$actual = array_keys($urls)[intval($ln[0])];
$imgdat = explode(' ', trim($ln[1]));

$j = 0;
for ($y=0; $y<$imgsz; $y++)
{
    for ($x=0; $x<$imgsz; $x++)
    {
        $r = intval(255*floatval($imgdat[$j]));
        $j++;
        $g = intval(255*floatval($imgdat[$j]));
        $j++;
        $b = intval(255*floatval($imgdat[$j]));
        $j++;

        colorrgb($r, $g, $b);
        echo "  ";
        colorless();
    }
    echo "\n";
}
echo "\nActual: $actual\n";

$cmd = "bin/elantia predict img_recognition.ai {$ln[1]} | tee prediction.txt";
passthru($cmd);
$p = file_get_contents("prediction.txt");
$predicted = array_keys($urls)[intval($p)];
echo "\nPredicted: $predicted\n";
