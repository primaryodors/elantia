<?php

// TODO: This script should be in Python, however I can write the functionality faster in a familiar language than
// in one I'm still learning.

$urls =
[
    "bread" =>
    [
        "https://cdn.pixabay.com/photo/2014/07/09/22/09/bread-388647_1280.jpg",
        "https://cdn.pixabay.com/photo/2017/06/23/23/57/bread-2436370_640.jpg",
        "https://cdn.pixabay.com/photo/2018/06/10/20/30/bread-3467243_640.jpg",
        "https://cdn.pixabay.com/photo/2019/05/06/14/24/bread-4183225_640.jpg",
        "https://cdn.pixabay.com/photo/2019/11/21/14/46/bread-4642686_640.jpg",
        "https://cdn.pixabay.com/photo/2020/10/20/18/02/bread-5671125_640.jpg",
        "https://cdn.pixabay.com/photo/2018/02/06/17/10/grain-bread-3135224_640.jpg",
        // "https://cdn.pixabay.com/photo/2018/01/19/17/26/bread-3092886_640.png",
        "https://cdn.pixabay.com/photo/2017/07/07/20/56/bread-2482703_640.jpg",
        "https://cdn.pixabay.com/photo/2015/01/18/16/02/bruschetta-603115_640.jpg",
        "https://cdn.pixabay.com/photo/2022/03/23/15/40/sliced-bread-7087438_640.jpg",
        "https://cdn.pixabay.com/photo/2019/03/10/16/22/bread-4046506_640.jpg"
    ],
    "wine" =>
    [
        "https://cdn.pixabay.com/photo/2017/06/16/10/32/wine-2408620_640.jpg",
        "https://cdn.pixabay.com/photo/2018/01/12/09/45/glass-3077869_640.jpg",
        "https://cdn.pixabay.com/photo/2016/07/26/16/16/wine-1543170_640.jpg",
        "https://cdn.pixabay.com/photo/2016/07/04/02/42/wine-glasses-1495861_640.jpg",
        "https://cdn.pixabay.com/photo/2015/07/18/13/14/wine-850337_640.jpg",
        "https://cdn.pixabay.com/photo/2017/09/26/16/44/wine-2789265_640.jpg",
        "https://cdn.pixabay.com/photo/2014/08/26/19/19/glass-428315_640.jpg",
        "https://cdn.pixabay.com/photo/2015/05/31/11/15/wine-791133_640.jpg",
        "https://cdn.pixabay.com/photo/2022/03/08/13/41/drinks-7055770_640.jpg",
        "https://cdn.pixabay.com/photo/2017/10/26/17/53/wine-2891894_640.jpg",
        "https://cdn.pixabay.com/photo/2020/02/02/15/07/wine-4813260_640.jpg",
        "https://cdn.pixabay.com/photo/2015/07/16/23/20/white-wine-848268_640.jpg"
    ],
    "cheese" =>
    [
        "https://cdn.pixabay.com/photo/2015/02/10/02/42/cheese-630511_640.jpg",
        "https://cdn.pixabay.com/photo/2016/10/11/16/44/parmesan-1732086_640.jpg",
        "https://cdn.pixabay.com/photo/2017/01/11/19/56/cheese-1972744_640.jpg",
        "https://cdn.pixabay.com/photo/2018/09/03/20/06/cheese-3652274_640.jpg",
        "https://cdn.pixabay.com/photo/2019/08/22/04/56/cheese-4422507_640.jpg",
        "https://cdn.pixabay.com/photo/2013/02/13/17/44/cheese-81402_640.jpg",
        "https://cdn.pixabay.com/photo/2015/03/11/11/09/kaseplatte-668516_640.jpg",
        "https://cdn.pixabay.com/photo/2018/09/06/12/26/cheese-3658141_640.jpg",
        "https://cdn.pixabay.com/photo/2020/05/17/04/33/cheese-5179967_640.jpg",
        "https://cdn.pixabay.com/photo/2015/06/26/09/50/soft-cheese-822350_640.jpg"
    ],
    "fruit" =>
    [
        "https://cdn.pixabay.com/photo/2016/08/17/09/57/fruit-bowl-1600003_640.jpg",
        "https://cdn.pixabay.com/photo/2016/12/10/21/28/plums-1898196_640.jpg",
        "https://cdn.pixabay.com/photo/2017/09/26/13/31/apple-2788616_640.jpg",
        "https://cdn.pixabay.com/photo/2015/06/29/13/04/peaches-825564_640.jpg",
        "https://cdn.pixabay.com/photo/2014/06/21/22/07/lime-374216_640.jpg",
        "https://cdn.pixabay.com/photo/2018/07/05/23/12/pear-3519397_640.jpg",
        "https://cdn.pixabay.com/photo/2020/05/31/18/34/blueberries-5243712_640.jpg",
        "https://cdn.pixabay.com/photo/2020/05/08/18/16/healthy-5146826_640.jpg",
        "https://cdn.pixabay.com/photo/2017/07/21/22/11/apricots-2527193_640.jpg",
        "https://cdn.pixabay.com/photo/2020/05/17/19/43/apple-5183288_640.jpg",
        "https://cdn.pixabay.com/photo/2021/10/02/08/29/pumpkin-6674599_640.jpg",
        "https://cdn.pixabay.com/photo/2016/07/02/22/42/berries-1493905_640.jpg",
        "https://cdn.pixabay.com/photo/2024/02/11/13/33/kumquats-8566508_640.jpg",
        "https://cdn.pixabay.com/photo/2018/07/03/10/46/berry-3513546_640.jpg",
        "https://cdn.pixabay.com/photo/2022/05/27/10/35/strawberry-7224875_640.jpg",
        "https://cdn.pixabay.com/photo/2017/06/03/18/06/cherry-2369275_640.jpg",
        "https://cdn.pixabay.com/photo/2019/11/19/13/10/fruit-4637398_640.jpg"
    ],
    "soup" =>
    [
        "https://cdn.pixabay.com/photo/2015/02/03/16/31/soup-622737_1280.jpg",
        "https://cdn.pixabay.com/photo/2015/05/02/01/04/miso-soup-749368_640.jpg",
        "https://cdn.pixabay.com/photo/2016/07/07/19/51/soup-1503117_640.jpg",
        "https://cdn.pixabay.com/photo/2023/05/27/13/49/soup-8021564_640.jpg",
        "https://cdn.pixabay.com/photo/2020/11/09/13/22/soup-5726677_640.jpg",
        "https://cdn.pixabay.com/photo/2014/12/16/23/45/soup-570922_640.jpg",
        "https://cdn.pixabay.com/photo/2023/05/27/13/49/soup-8021569_640.jpg",
        "https://cdn.pixabay.com/photo/2022/09/23/20/17/pumpkin-soup-7475122_640.jpg",
        "https://cdn.pixabay.com/photo/2020/01/02/04/39/lentil-soup-4734947_640.jpg",
        "https://cdn.pixabay.com/photo/2018/04/24/19/57/soup-3347872_640.jpg",
        "https://cdn.pixabay.com/photo/2013/01/08/01/22/minestrone-74303_640.jpg",
        "https://cdn.pixabay.com/photo/2022/01/18/08/43/soup-6946614_640.jpg",
        "https://cdn.pixabay.com/photo/2022/07/20/19/11/liver-dumpling-7334775_640.jpg",
        "https://cdn.pixabay.com/photo/2018/08/31/19/13/pumpkin-soup-3645375_640.jpg"
    ]
];

chdir(__DIR__);
chdir("..");
if (!file_exists("images")) mkdir("images");

$imgsz = 20;
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
$cmd = "bin/elantia create img_recognition.ai --inputs $inputs --outputs $outputs --layers 5 --neurons 1000 --function SELU";
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
