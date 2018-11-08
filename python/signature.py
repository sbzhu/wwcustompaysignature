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
 
class SignatureGetter(object):
    def __init__(self, secret):
        self.secret = secret

    def HmacSha256(self, data): 
        data = bytes(data).encode('utf-8')
        secret = bytes(self.secret).encode('utf-8') 
        signature = base64.b64encode(hmac.new(secret, data, digestmod=hashlib.sha256).digest())
        return signature
