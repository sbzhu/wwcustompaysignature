#!/usr/bin/env python
# -*- coding:utf-8 -*-
##
 # Copyright (C) 2018 All rights reserved.
 #   
 # @File test.py
 # @Brief 
 # @Author abelzhu, abelzhu@tencent.com
 # @Version 1.0
 # @Date 2018-11-08
 #
 #
 
from signature import SignatureGetter

secret = "aaaaaa"
json = "bbb"

signGetter = SignatureGetter(secret)

print signGetter.HmacSha256(json)

