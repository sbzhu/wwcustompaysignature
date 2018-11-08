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

secret = "gHqphoZuLCqHsSWbnojEKPLsWPE10G8UyKEE1B4uV64"
json = """{
   "errcode": 0,
   "errmsg": "ok",
   "total_num": 2,
   "order_list": [
        {
     "out_trade_no": "1458098496971",
     "order_type": 1
    },
    {
     "out_trade_no": "1458098496983",
     "order_type": 0
    }
   ],
   "ts": 1541498084,
   "nonce_str": "5K8264ILTKCH16CQ2502SI8ZNMTM67VS",
   "sign": "C380BEC2BFD727A4B6845133519F3AD6"
  }"""
stringA = "errcode=0&errmsg=ok&nonce_str=5K8264ILTKCH16CQ2502SI8ZNMTM67VS&order_type=0&order_type=1&out_trade_no=1458098496971&out_trade_no=1458098496983&total_num=2&ts=1541498084"

signGetter = SignatureGetter(secret)

print signGetter.HmacSha256(json)

