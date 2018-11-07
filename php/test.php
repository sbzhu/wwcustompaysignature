<?php
include_once("signature.php");

$secret = "gHqphoZuLCqHsSWbnojEKPLsWPE10G8UyKEE1B4uV64";
$stringA = "errcode=0&errmsg=ok&nonce_str=5K8264ILTKCH16CQ2502SI8ZNMTM67VS&order_type=0&order_type=1&out_trade_no=1458098496971&out_trade_no=1458098496983&total_num=2&ts=1541498084";

$signGetter = new SignatureGetter($secret); 

print($signGetter->GetSha1HmacSign($secret, $stringA)."\n");
