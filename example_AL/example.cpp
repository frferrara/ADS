/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   example.cpp
 * Author: fef
 *
 * Created on November 12, 2021, 2:18 PM
 */

#include <cstdio>
#include <cstdlib>
#include <exception>

#include "TcAdsClientWrapper.hpp"
#include "AdsCommon.hpp"


using namespace std;
using namespace AdsAL::AdsClient;
using namespace AdsAL::AdsCommon;


static void NotifyCallback(uint32_t userHandle, uint64_t timeStamp, uint32_t notificationHandle, uint32_t size)
{
    
}

/*
 * 
 */
int main()
{
    TcAdsClientWrapper *adsClient = 0;
    
    try
    {
        adsClient = new TcAdsClientWrapper(&NotifyCallback);
        
        const string remoteIpV4 = "192.168.0.26";
        const string amsNetId = "169.254.197.241.1.1";
        
        adsClient->Connect(remoteIpV4, amsNetId, AdsPort::StandardAdsApplicationPort);
    }
    catch (exception &e)
    {
        // Do something with the exception
    }
    
    if (adsClient) delete adsClient;
    
    printf("Hello World!\n");
    return 0;
}
