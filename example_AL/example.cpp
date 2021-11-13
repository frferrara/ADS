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


using namespace std;
using namespace AdsAL::AdsClient;

/*
 * 
 */
int main()
{
    TcAdsClientWrapper *adsClient = 0;
    
    try
    {
        adsClient = new TcAdsClientWrapper();
    }
    catch (exception &e)
    {
        // Do something with the exception
    }
    
    if (adsClient) delete adsClient;
    
    printf("Hello World!\n");
    return 0;
}

