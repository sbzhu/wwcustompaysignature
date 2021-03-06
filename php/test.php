<?php /*
 * Copyright (C) 2018 All rights reserved.
 *   
 * @File test.php
 * @Brief 
 * @Author abelzhu, abelzhu@tencent.com
 * @Version 1.0
 * @Date 2018-11-07
 *
 */
 
include_once("signature.php");

$secret = "at23pxnPBNQY3JiA8N5U1gabiQqxZwqH_Gihg7a_wrULmlOPVP-iiRjv9JWYPrDk";

$json = '
{
    	"orderid" : "ord7",
        "buyer_corpid": "ww66302cfadbdd3c64",
    	"buyer_userid" : "invitetest",
        "product_id": "product_id_xxx",
        "product_name": "product_name_xxx",
        "product_detail": "product_detail_xxx",
        "unit_name": "台",
        "unit_price": 1,
        "num": 3,
        "nonce_str" : "129031823",
        "ts": 1548302135,
        "sig": "mPOwVW/vQ74xN+b+Yu1KMa9RrmhKJaJjAtXHTof+EpU="
} ';

$signGetter = new SignatureGetter($secret); 
print($signGetter->Get($json)."\n");
