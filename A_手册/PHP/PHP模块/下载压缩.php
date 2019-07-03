<?php

    /**
     * 下载压缩
     *
     * @param string $downDir 下载目录
     * @param string $packDir 打包目录
     */
    public function zip($downDir, $packDir) {
        
        $time = time();
        $time = date('Y-m-d*H-i-s', $time); //最终生成的文件名（含路径）

        $zip = new ZipArchive();
        if ($zip->open($downDir, ZipArchive::CREATE) === TRUE) {
            //调用方法，对要打包的根目录进行操作，并将ZipArchive的对象传递给方法
            $this->addFileToZip($packDir, $zip);
            $zip->close();
        }

        header("Cache-Control: public");
        header("Content-Description: File Transfer");
        //文件名
        header('Content-disposition: attachment; filename=' . basename($downDir));
        //zip格式的
        header("Content-Type: application/zip");
        //告诉浏览器，这是二进制文件
        header("Content-Transfer-Encoding: binary");
        //告诉浏览器，文件大小
        header('Content-Length: ' . filesize($downDir));
        @readfile($downDir);
        unlink($downDir);
        exit();
    }

    /**
     * 循环压缩方法
     *
     * 可以将文件压缩到zip中,并除去没用文件夹
     * @param string $path   路径
     * @param string $zip    ZipArchive对象
     * @param string $folder 文件路径的上一层,用于解决压缩文件路径不对问题
     */
    function addFileToZip($path, $zip, $folder = "") {
        //打开当前文件夹由$path指定。
        $handler = opendir($path);
        /*
         * 循环的读取文件夹下的所有文件和文件夹
         * 其中$filename = readdir($handler)是每次循环的时候将读取的文件名赋值给$filename，
         * 为了不陷于死循环，所以还要让$filename !== false。
         * 一定要用!==，因为如果某个文件名如果叫'0'，或者某些被系统认为是代表false，用!=就会停止循环
         */
        while (($filename = readdir($handler)) !== false) {
            //文件夹文件名字为'.'和‘..’，不要对他们进行操作
            if ($filename != "." && $filename != "..") {
                // 如果读取的某个对象是文件夹，则递归
                if (is_dir($path . "/" . $filename)) {
                    /**
                     * 创建当前文件的路径
                     * @var string
                     */
                    $folder = $folder . "/" . $filename;

                    /**
                     * 创建一个文件夹
                     */
                    $zip->addEmptyDir($folder);

                    /**
                     * 循环调用自己,创建文件夹
                     * @return string 路径的上一层
                     */
                    $folder = $this->addFileToZip($path . "/" . $filename, $zip, $folder);
                } else {
                    /**
                     * 将文件加入zip对象,在特定的位置添加文件,并用以前的文件名命名
                     */
                    $zip->addFile($path . "/" . $filename, $folder . "/" . $filename);
                }
            }
        }

        /**
         * 进行字符串切割,使路径变成上一级路径
         * $folderT array 路径切割后的数据
         * $folder string 重新拼接后的路径
         */
        $folderT = explode("/", $folder);
        array_pop($folderT);
        $folder = implode("/", $folderT);

        @closedir($path);
        return $folder;
    }