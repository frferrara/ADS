/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   TcAdsClient.hpp
 * Author: fef
 *
 * Created on October 5, 2021, 11:03 AM
 */

#ifndef TCADSCLIENT_HPP
#define TCADSCLIENT_HPP


#include "AdsCommon.hpp"


using namespace std;
using namespace AdsAL::AdsCommon;


namespace AdsAL
{
namespace AdsClient
{

    class TcAdsClient
    {
    public:
        virtual ~TcAdsClient() = default;
        
        virtual void Connect(const string& ipV4, const string& amsNetId, AdsPort port) = 0;
        
        template <typename T>
        T Read(const string& pathToAdsVariable) {}
        
        template <typename T>
        void Write(const string& pathToAdsVariable, T value) {}
        
        virtual void RegisterNotification(string& pathToAdsVariable, AdsNotificationType notificationType, uint32_t userHandle, uint32_t length, uint32_t maxDelay = 0, uint32_t cycleTime = 0) = 0;
    };
    
}
}


#endif /* TCADSCLIENT_HPP */

