/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   TcAdsClientWrapper.hpp
 * Author: fef
 *
 * Created on October 5, 2021, 11:17 AM
 */

#ifndef TCADSCLIENTWRAPPER_HPP
#define TCADSCLIENTWRAPPER_HPP


#include "AdsDevice.h"
#include "AdsLib.h"
#include "TcAdsClient.hpp"


using namespace std;


namespace AdsAL
{
namespace AdsClient
{

    class TcAdsClientWrapper : TcAdsClient
    {
    public:
        TcAdsClientWrapper();
        
        TcAdsClientWrapper(const TcAdsClientWrapper& orig);
        
        virtual ~TcAdsClientWrapper();
        
        void Connect(const string& ipV4, const string& amsNetId, AdsPort port);
        
        template <typename T>
        T Read(const string& pathToAdsVariable);
        
        template <typename T>
        void Write(const string& pathToAdsVariable, T value);
        
        void RegisterNotification(string& pathToAdsVariable, AdsNotificationType notificationType, NotifyCallback callback, uint32_t userHandle, uint32_t length, uint32_t maxDelay = 0, uint32_t cycleTime = 0);
        
    private:
        AdsDevice route;
    };
    
}
}

#endif /* TCADSCLIENTWRAPPER_HPP */

