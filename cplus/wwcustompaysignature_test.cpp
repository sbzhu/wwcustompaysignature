/*
 * Copyright (C) 2018 All rights reserved.
 *   
 * @File wwcustompaysignature_test.cpp
 * @Brief 
 * @Author abelzhu, abelzhu@tencent.com
 * @Version 1.0
 * @Date 2018-11-07
 *
 */
#include <string>
#include <iostream>

using namespace std;

#include "wwcustompaysignature.h"

using namespace wework;

int main(int argc, char *argv[])
{
    const std::string sSecret = "gHqphoZuLCqHsSWbnojEKPLsWPE10G8UyKEE1B4uV64";

    const std::string sJson = "{ \
        \"errcode\": 0, \
        \"errmsg\": \"ok\", \
        \"total_num\": 2, \
        \"order_list\": [ \
            { \
                \"out_trade_no\": \"1458098496971\", \
                \"order_type\": 1 \
            }, \
            { \
                \"out_trade_no\": \"1458098496983\", \
                \"order_type\": 0 \
            } \
        ], \
        \"ts\": 1541498084, \
        \"nonce_str\": \"5K8264ILTKCH16CQ2502SI8ZNMTM67VS\", \
        \"sign\": \"C380BEC2BFD727A4B6845133519F3AD6\" \
    }";


    cout << CustomPaySignature(sSecret).Get(sJson) << endl;

    return 0;
}
