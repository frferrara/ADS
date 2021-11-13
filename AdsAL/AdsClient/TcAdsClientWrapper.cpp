/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   TcAdsClientWrapper.cpp
 * Author: fef
 * 
 * Created on October 5, 2021, 11:17 AM
 */


#include "AdsVariable.h"
#include "TcAdsClientWrapper.hpp"


using namespace std;
using namespace AdsAL::AdsClient;


TcAdsClientWrapper::TcAdsClientWrapper(NotifyCallbackFunc callback)
{
    this->callback = callback;
}

TcAdsClientWrapper::TcAdsClientWrapper(const TcAdsClientWrapper& orig) 
{
    this->callback = orig.callback;
    this->route = orig.route;
}

TcAdsClientWrapper::~TcAdsClientWrapper() 
{
}

void TcAdsClientWrapper::Connect(const string& ipV4, const string& amsNetId, AdsPort port)
{
    AdsDevice route { ipV4, amsNetId, port };
    this->route = &route;
}

template <typename T>
T TcAdsClientWrapper::Read(const string& pathToAdsVariable)
{
    AdsVariable<T> variable { route, pathToAdsVariable };
    
    return (T)variable;
}

template <typename T>
void TcAdsClientWrapper::Write(const string& pathToAdsVariable, T value)
{
    AdsVariable<T> variable { route, pathToAdsVariable };
    
    variable = value;
}

void TcAdsClientWrapper::RegisterNotification(string& pathToAdsVariable, AdsNotificationType notificationType, uint32_t userHandle, uint32_t length, uint32_t maxDelay, uint32_t cycleTime)
{
    AdsNotificationAttrib attributes {
        length,
        notificationType,
        maxDelay,
        {cycleTime}
    };
    
    AdsNotification notification { *route, pathToAdsVariable, attributes, (PAdsNotificationFuncExConst)(&TcAdsClientWrapper::NotifyCallback), userHandle };
}

void TcAdsClientWrapper::NotifyCallback(const AmsAddr* pAddr, const AdsNotificationHeader* pNotification, uint32_t hUser)
{
    
}
