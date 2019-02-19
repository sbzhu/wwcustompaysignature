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
    const std::string sSecret = "at23pxnPBNQY3JiA8N5U1gabiQqxZwqH_Gihg7a_wrULmlOPVP-iiRjv9JWYPrDk";

    const std::string sJson = "{
    	\"orderid\" : \"ord7\",
        \"buyer_corpid\": \"ww66302cfadbdd3c64\",
    	\"buyer_userid\" : \"invitetest\",
        \"product_id\": \"product_id_xxx\",
        \"product_name\": \"product_name_xxx\",
        \"product_detail\": \"product_detail_xxx\",
        \"unit_name\": \"台\",
        \"unit_price\": 1,
        \"num\": 3,
        \"nonce_str\" : \"129031823\",
        \"ts\": 1548302135,
        \"sig\": \"mPOwVW/vQ74xN+b+Yu1KMa9RrmhKJaJjAtXHTof+EpU=\"
    }";


    cout << CustomPaySignature(sSecret).Get(sJson) << endl;

    return 0;
}
