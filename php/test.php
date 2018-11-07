<?php
include_once("signature.php");

$secret = "gHqphoZuLCqHsSWbnojEKPLsWPE10G8UyKEE1B4uV64";

$json = '
{
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
} ';

$signGetter = new SignatureGetter($secret); 
print($signGetter->Get($json)."\n");
