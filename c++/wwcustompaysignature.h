/*
 * Copyright (C) 2018 All rights reserved.
 *   
 * @File wwcustompaysignature.h
 * @Brief 
 * @Author abelzhu, abelzhu@tencent.com
 * @Version 1.0
 * @Date 2018-11-06
 *
 */

#pragma once
 
#include <string>
#include <vector>
#include "3rd/rapidjson/rapidjson/document.h" 
 
namespace wework {

class CustomPaySignature { 

public: 
    CustomPaySignature(const std::string & sSecret) : m_sSecret(sSecret) 
    { 
    }

    std::string Get(const std::string & sJson);

private: 

    int Json2ParamString(
            const std::string sName, 
            const rapidjson::Value & json, 
            std::vector<std::string> * pVecParam);

    std::string GetSourceString(std::vector<std::string> vecParam);

    std::string HmacSha256Sign(const std::string & sKey, const std::string & sStr);

private: 
    std::string m_sSecret;
}; // class
 
}  // namespace
