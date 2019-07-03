# -*- coding:utf-8 -*-
#
####################
#
# 二维码生成
# 必须库：qrcode
# 转换为base64 : base64

import qrcode
import base64

from io import StringIO #使用缓存

def index(text):
    # 生成二维码
    qr = qrcode.QRCode(  #二维码配置
        version=5,
        error_correction=qrcode.constants.ERROR_CORRECT_L,
        box_size=8,
        border=4
    )
    qr.add_data(text) #添加数据
    qr.make(fit=True) #将数据编译为QR码数组

    img = qr.make_image() #根据QR码数据制作图像

    #将图片保存到缓存
    img_buffer = StringIO()
    img.save(img_buffer, 'png')
    res = img_buffer.getvalue()
    img_buffer.close()

    return base64.b64encode(res) #转换base64
