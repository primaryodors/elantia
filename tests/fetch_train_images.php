<?php

// TODO: This script should be in Python, however I can write the functionality faster in a familiar language than
// in one I'm still learning.

function json_encode_pretty($array)
{
	return preg_replace("/([ \t]*)([^\\s]*) ([{\\[])\n/", "\$1\$2\n\$1\$3\n", json_encode($array, JSON_PRETTY_PRINT));
}

chdir(__DIR__);
chdir("..");

$urls = json_decode(file_get_contents("tests/imgurls.json"), true);

$imgsz = 32;
$imgdata = [];
$catid = 0;
foreach ($urls as $category => $list)
{
    if (!file_exists("images/$category")) mkdir("images/$category");
    foreach ($list as $url)
    {
        $fn = explode("/",$url);
        $fn = $fn[count($fn)-1];
        $fn = "images/$category/$fn";

        if (!file_exists($fn))
        {
            echo "Downloading $url...\n";
            $c = file_get_contents($url);
            if (!$c) continue;
            file_put_contents($fn, $c);
        }

        $im = imagecreatefromjpeg($fn);
        if (!$im) continue;
        $w = imagesx($im);
        $h = imagesy($im);

        $out = imagecreatetruecolor($imgsz, $imgsz);
        imagecopyresampled($out, $im, 0, 0, 0, 0, $imgsz, $imgsz, $w, $h);

        $pixarray = [];
        for ($y=0; $y<$imgsz; $y++)
        {
            for ($x=0; $x<$imgsz; $x++)
            {
                $c = imagecolorat($out, $x, $y);
                $pixarray[] = 0.00392 * (($c >> 16) & 0xFF);        // red
                $pixarray[] = 0.00392 * (($c >> 8) & 0xFF);         // green
                $pixarray[] = 0.00392 * ($c & 0xFF);                // blue
            }
        }

        $imgdata[] = "$catid: ".implode(" ", $pixarray);
    }

    $catid++;
}

$fn = "tests/imgdata.txt";
file_put_contents($fn, implode("\n", $imgdata));
if (file_exists($fn)) echo "Wrote $fn.\n";

$train = [];
foreach ($imgdata as $ln) if (rand(0,1) < 0.15) $train[] = $ln;
$fn = "tests/img_train_data.txt";
file_put_contents($fn, implode("\n", $train));
if (file_exists($fn)) echo "Wrote $fn.\n";

$inputs = $imgsz*$imgsz*3;
$outputs = count(array_keys($urls));
$cmd = "bin/elantia create img_recognition.ai --inputs $inputs --outputs $outputs --layers 8 --neurons 1000 --function SELU";
echo "$cmd\n";
passthru($cmd);

$cmd = "bin/elantia train img_recognition.ai tests/img_train_data.txt --iter 1000000";
echo "$cmd\n";
passthru($cmd);

$lno = rand(0, count($imgdata));
$test = explode(":",$imgdata[$lno]);
$expect = $test[0];
$test = $test[1];
$cmd = "bin/elantia predict img_recognition.ai $test";
echo "Testing image with expected output $expect...\n";
passthru($cmd);
