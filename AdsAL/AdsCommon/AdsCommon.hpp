/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   AdsCommon.hpp
 * Author: fef
 *
 * Created on October 5, 2021, 11:08 AM
 */

#ifndef ADSCOMMON_HPP
#define ADSCOMMON_HPP

namespace AdsAL
{
namespace AdsCommon
{

    enum AdsPort
    {
        StandardAdsApplicationPort = 851
    };
    
    enum AdsNotificationType
    {
        Cyclic          = 3,
        ValueChanged    = 4
    };

    typedef void (*NotifyCallbackFunc)(uint32_t userHandle, uint64_t timeStamp, uint32_t notificationHandle, uint32_t size);
}
}

#endif /* ADSCOMMON_HPP */

