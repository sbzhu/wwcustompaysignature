/*
 * Copyright (C) 2018 All rights reserved.
 *   
 * @File wwcustompaysignature.cpp
 * @Brief 
 * @Author abelzhu, abelzhu@tencent.com
 * @Version 1.0
 * @Date 2018-11-06
 *
 */

#ifndef __STDC_FORMAT_MACROS
#define __STDC_FORMAT_MACROS
#endif
#include <inttypes.h>
#include <stdio.h>
#include <string>
#include <string.h>
#include <algorithm>
#include<iostream>
#include <sstream>
#include <openssl/rsa.h>
#include <openssl/engine.h>
#include <openssl/pem.h>
#include <openssl/evp.h>
#include <openssl/err.h>
#include "openssl/hmac.h"
#include "openssl/sha.h"
#include <openssl/pem.h>
#include <openssl/err.h>

#include "3rd/rapidjson/rapidjson/document.h" 
#include "comm2/core/utils/iBase64.h"

#include "wwcustompaysignature.h"

namespace wework {

std::string CustomPaySignature::Get(const std::string & sJson)
{
    rapidjson::Document json;
    json.Parse<0>(sJson.c_str());

    std::vector<std::string> vecParam;
    (void)Json2ParamString("root", json, &vecParam);

    return HmacSha256Sign(m_sSecret, GetSourceString(vecParam));
} 

std::string CustomPaySignature::GetSourceString(const std::vector<std::string> vecParam_)
{ 
    // sort 
    std::vector<std::string> vecParam(vecParam_);
    std::sort(vecParam.begin(), vecParam.end(), 
        [](const std::string & a, const std::string & b) {
            return a < b;
        }
    );

    // make string
    std::string sParamString;
    for (const auto & item : vecParam) { 
        if (0 == item.find("sign=")) continue;  // do not use sign self
        sParamString += (item + '&');
    }
    if (sParamString.size() > 0) sParamString.erase(sParamString.size() - 1); // remove the last &

    return sParamString;
}

std::string CustomPaySignature::HmacSha256Sign(const std::string & sKey, const std::string & sStr)
{
    // Hmac-Sha256
    unsigned int len = SHA256_DIGEST_LENGTH;
    unsigned char hash[SHA256_DIGEST_LENGTH];
    size_t keyLen = sKey.size();
    size_t valueLen = sStr.size();

    HMAC_CTX hmac;
    HMAC_CTX_init(&hmac);
    HMAC_Init_ex(&hmac, (unsigned char*)sKey.data(), keyLen, EVP_sha256(), NULL);
    HMAC_Update(&hmac, (unsigned char*)sStr.data(), valueLen);
    HMAC_Final(&hmac, hash, &len);
    HMAC_CTX_cleanup(&hmac); 

    // base64 encode
    std::string sBase64Signature;
    Comm::EncodeBase64(hash, sBase64Signature, SHA256_DIGEST_LENGTH);

    return sBase64Signature;
}

int CustomPaySignature::Json2ParamString(
        const std::string sName, 
        const rapidjson::Value & json, 
        std::vector<std::string> * pVecParam)
{
    int ret = 0;

    std::stringstream ss;

    if (json.IsNull()) { 
        return 0;
    } else if (json.IsObject()) { 
        for (auto iter = json.MemberBegin(); json.MemberEnd() != iter; ++iter) { 
            ret = Json2ParamString(iter->name.GetString(), iter->value, pVecParam);
            if (0 != ret) return ret;
        }
    } else if (json.IsArray()) { 
        for (auto iter = json.Begin(); json.End() != iter; ++iter) { 
            ret = Json2ParamString(sName, *iter, pVecParam);
            if (0 != ret) return ret;
        }
    } else if (json.IsBool()) {
        ss << json.GetBool();
        pVecParam->push_back(sName + '=' + ss.str());
    } else if (json.IsInt()) {
        ss << json.GetInt();
        pVecParam->push_back(sName + '=' + ss.str());
    } else if (json.IsInt64()) {
        ss << json.GetInt64();
        pVecParam->push_back(sName + '=' + ss.str());
    } else if (json.IsUint()) {
        ss << json.GetUint();
        pVecParam->push_back(sName + '=' + ss.str());
    } else if (json.IsUint64()) {
        ss << json.GetUint64();
        pVecParam->push_back(sName + '=' + ss.str());
    } else if (json.IsDouble()) {
        ss << json.GetDouble();
        pVecParam->push_back(sName + '=' + ss.str());
    } else if (json.IsString()) {
        ss << json.GetString();
        pVecParam->push_back(sName + '=' + ss.str());
    } else if (json.IsNumber()) {
        ss << json.GetDouble();
        pVecParam->push_back(sName + '=' + ss.str());
    }

    return 0;
}


} // namespace
