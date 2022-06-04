# -*- coding:utf-8 -*-
#
# 图片与base64之间的转换
#
# 前端使用<img src="data:image/jpg;base64,这里是base64的编码"/>
import base64,os

def imagetobase(path):
    dist_image = (".png",".jpg")

    if os.path.isdir(path):
        for filename in os.listdir(path): #listdir的参数是文件夹的路径
            lostname = os.path.splitext(filename)[1]
            
            if lostname in dist_image:
                path_name = os.path.join(path,filename)
                with open(path_name, "rb") as f:
                    base64_data = base64.b64encode((f.read())) #使用base64进行加密
                    print("base64:" + base64_data + "<br/>")

            
        #     # file=open('1.txt','wt')#写成文本格式
        #     # file.write(base64_data)
        #     # file.close()

def basetoimage(path):
    imgdata = base64.b64decode(path)

    print(imgdata)

if __name__ == "__main__":
    a = r"D:\Pictures" #这里因为\ 是转义
    imagetobase(a)