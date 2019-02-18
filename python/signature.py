#!/usr/bin/env python
# -*- coding:utf-8 -*-
##
 # Copyright (C) 2018 All rights reserved.
 #   
 # @File signature.py
 # @Brief 
 # @Author abelzhu, abelzhu@tencent.com
 # @Version 1.0
 # @Date 2018-11-08
 #
 #

import string
import random
import hashlib
import time
import struct
import sys    
import hmac
import base64
import json
 
class SignatureGetter(object):
    def __init__(self, secret):
        self.secret = secret

    def Get(self, jsonStr) : 
        jsonDict = json.loads(jsonStr)

        paramList = []
        self.Json2List(jsonDict, paramList)

        paramList.sort()

        return self.HmacSha256(self.List2String(paramList))

    def List2String(self, paramList):
        str = ""
        for param in paramList:
            if 0 == param.find('sig='):
                continue # egnore sig self
            str += (param + '&')
        return str.rstrip('&')


    def HmacSha256(self, data): 
        data = bytes(data).encode('utf-8')
        secret = bytes(self.secret).encode('utf-8') 
        signature = base64.b64encode(hmac.new(secret, data, digestmod=hashlib.sha256).digest())
        return signature 

    def Json2List(self, jsonDict, paramList): 
        for k, v in jsonDict.items():
            if isinstance(v, list):
                for item in v:
                    self.Json2List(item, paramList)
            else :
                paramList.append(k + '=' + str(v))
