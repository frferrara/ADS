/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   AdsClient.hpp
 * Author: fef
 *
 * Created on August 10, 2021, 4:50 PM
 */

#ifndef ADSCLIENT_HPP
#define ADSCLIENT_HPP


#include <string>


using namespace std;


namespace AdsAL
{
namespace AdsClient
{
    

    class AdsClient
    {
    public:
        AdsClient(const string& ipV4, const string& amsNetId, AdsPort port);

        void Connect();

        template <typename T>
        T Read(const string& pathToAdsVariable);

        template <typename T>
        void Write(const string& pathToAdsVariable, T value);
    };
}
}


#endif /* ADSCLIENT_HPP */

