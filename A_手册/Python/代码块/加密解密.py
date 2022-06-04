# -*- coding:utf-8 -*-
#
##################
#
# 加密解密方法
# 必须库: pip install cryptography

from cryptography.fernet import Fernet


def get_3rd_session(self, openid):
    """加密

    Args:
        string openid         代价加密数据
    
    Return:
        string encrypted_data 加密后的数据
        string key            公钥
    """
    
    key = Fernet.generate_key().decode("utf-8")  # 得到一个获取key
    cipher = Fernet(key)  # 根据key获取，一个加密
    encrypted_data = cipher.encrypt(openid.encode('utf-8')).decode("utf-8") # 加密数据

    return encrypted_data, key


def get_openid_from_encrypted_data(self, encrypted_data, key):
    """解密

    Args:
        string encryped_data 要解密的数据
        string key           公钥

    Return:
        string raw_data      解密后的数据
    """
    cipher = Fernet(key)
    raw_data = cipher.decrypt(encrypted_data)

    return raw_data
