
#include "AdsLib.h"
#include "AdsNotificationOOI.h"
#include "AdsVariable.h"

#include <array>
#include <iostream>
#include <iomanip>
#include <cstring>
#include <limits>
#include <stdexcept>

// #pragma pack(1) instead of __attribute__((packed)) would also work
struct __attribute__((packed)) PackedStruct
{
    bool digitalSwitch;
    char text[5];
    float real;
    short number;
    unsigned char byte;
};
// #pragma pack() closes #pragma pack(1)

// Always use #pragma pack(n) at beginning and #pragma pack() at end
#pragma pack(2)
struct AlignedStruct
{
    bool digitalSwitch;
    char text[5];
    float real;
    int16_t number;
    uint8_t byte;
    //uint8_t _padding;
};
#pragma pack()

struct AlignedStructs
{
    AlignedStruct struct1;
    AlignedStruct struct2;
    AlignedStruct struct3;
};

union AlignedUnion
{
    AlignedStructs structs;
    AlignedStruct structsArray[3];
};

template <typename T>
static void printHexData(std::ostream& out, void* value)
{
    // Store default output flags to be able to restore them
    std::ios_base::fmtflags f(out.flags());
    
    // Copy type data to raw data
    const int length = sizeof(T);
    uint8_t rawData[length];
    memcpy(rawData, value, length);
    
    out << "data length: " << length << "\n";
    
    // Print the raw data
    for (int i = 0; i < length; i++)
    {
        out << std::uppercase << std::setfill('0') << std::setw(2) << std::right << std::hex << (uint32_t)rawData[i] << " ";
    }
    
    out << "\n";
    out.flags(f);
}


static void printPackedStruct(std::ostream& out, std::string prefix, PackedStruct& value)
{
    out << "addresses:" << "\n";
    out << "digitalSwitch: " << &(value.digitalSwitch) << " (size: " << sizeof(bool) << ", min: " << std::numeric_limits<bool>::min() << ", max: " << std::numeric_limits<bool>::max() << ")" << "\n";
    out << "text: " << &(value.text) << " (size: " << sizeof(char[5]) << ", min: " << std::numeric_limits<char>::min() << ", max: " << std::numeric_limits<char>::max() << ")" << "\n";
    out << "real: " << &(value.real) << " (size: " << sizeof(float) << ", min: " << std::numeric_limits<float>::min() << ", max: " << std::numeric_limits<float>::max() << ")" << "\n";
    out << "number: " << &(value.number) << " (size: " << sizeof(short) << ", min: " << std::numeric_limits<short>::min() << ", max: " << std::numeric_limits<short>::max() << ")" << "\n";
    out << "byte: " << &(value.byte) << " (size: " << sizeof(unsigned char) << ", min: " << std::numeric_limits<unsigned char>::min() << ", max: " << std::numeric_limits<unsigned char>::max() << ")" << "\n";

    out << "values:" << "\n";
    out << prefix << "bSwitch = " <<  value.digitalSwitch << "\n";
    out << prefix << "sText = " <<  value.text << "\n";
    out << prefix << "nReal = " <<  value.real << "\n";
    out << prefix << "nInt = " <<  value.number << "\n";
    out << prefix << "nByte = " <<  value.byte << "\n";
    
    printHexData<PackedStruct>(out, (void*)&value);
}

static void printAlignedStruct(std::ostream& out, std::string prefix, AlignedStruct& value)
{
    out << "addresses:" << "\n";
    out << "digitalSwitch: " << &(value.digitalSwitch) << " (size: " << sizeof(bool) << ", min: " << std::numeric_limits<bool>::min() << ", max: " << std::numeric_limits<bool>::max() << ")" << "\n";
    out << "text: " << &(value.text) << " (size: " << sizeof(char[5]) << ", min: " << std::numeric_limits<char>::min() << ", max: " << std::numeric_limits<char>::max() << ")" << "\n";
    out << "real: " << &(value.real) << " (size: " << sizeof(float) << ", min: " << std::numeric_limits<float>::min() << ", max: " << std::numeric_limits<float>::max() << ")" << "\n";
    out << "number: " << &(value.number) << " (size: " << sizeof(short) << ", min: " << std::numeric_limits<short>::min() << ", max: " << std::numeric_limits<short>::max() << ")" << "\n";
    out << "byte: " << &(value.byte) << " (size: " << sizeof(unsigned char) << ", min: " << std::numeric_limits<unsigned char>::min() << ", max: " << std::numeric_limits<unsigned char>::max() << ")" << "\n";

    out << "values:" << "\n";
    out << prefix << "bSwitch = " <<  value.digitalSwitch << "\n";
    out << prefix << "sText = " <<  value.text << "\n";
    out << prefix << "nReal = " <<  value.real << "\n";
    out << prefix << "nInt = " <<  value.number << "\n";
    out << prefix << "nByte = " <<  value.byte << "\n";
    
    printHexData<AlignedStruct>(out, (void*)&value);
}

static void NotifyCallback(const AmsAddr* pAddr, const AdsNotificationHeader* pNotification, uint32_t hUser)
{
    const uint8_t* data = reinterpret_cast<const uint8_t*>(pNotification + 1);
    std::cout << std::setfill('0') <<
        "NetId: " << pAddr->netId <<
        " hUser 0x" << std::hex << hUser <<
        " sample time: " << std::dec << pNotification->nTimeStamp <<
        " sample size: " << std::dec << pNotification->cbSampleSize <<
        " value:";
    for (size_t i = 0; i < pNotification->cbSampleSize; ++i) {
        std::cout << " 0x" << std::hex << (int)data[i];
    }
    std::cout << '\n';
}

static void NotifyPackedStructureCallback(const AmsAddr* pAddr, const AdsNotificationHeader* pNotification, uint32_t hUser)
{
    // Store default output flags to be able to restore them
    std::ios_base::fmtflags f(std::cout.flags());
    
    const PackedStruct* data = reinterpret_cast<const PackedStruct*>(pNotification + 1);
    std::cout << std::setfill('0') <<
        "NetId: " << pAddr->netId <<
        " hUser 0x" << std::hex << hUser <<
        " sample time: " << std::dec << pNotification->nTimeStamp <<
        " sample size: " << std::dec << pNotification->cbSampleSize <<
        "\n";
    PackedStruct printData = *data;
    printPackedStruct(std::cout, "MAIN.stOutput.", printData);
    
    // Restore output flags
    std::cout.flags(f);
}

static void NotifyAlignedStructureCallback(const AmsAddr* pAddr, const AdsNotificationHeader* pNotification, uint32_t hUser)
{
    // Store default output flags to be able to restore them
    std::ios_base::fmtflags f(std::cout.flags());
    
    const AlignedStruct* data = reinterpret_cast<const AlignedStruct*>(pNotification + 1);
    std::cout << std::setfill('0') <<
        "NetId: " << pAddr->netId <<
        " hUser 0x" << std::hex << hUser <<
        " sample time: " << std::dec << pNotification->nTimeStamp <<
        " sample size: " << std::dec << pNotification->cbSampleSize <<
        "\n";
    AlignedStruct printData = *data;
    printAlignedStruct(std::cout, "MAIN.stAlignedOutput.", printData);
    
    // Restore output flags
    std::cout.flags(f);
}

static void NotifyArrayOfAlignedStructureCallback(const AmsAddr* pAddr, const AdsNotificationHeader* pNotification, uint32_t hUser)
{
    // Store default output flags to be able to restore them
    std::ios_base::fmtflags f(std::cout.flags());
    
    const AlignedStruct* data = reinterpret_cast<const AlignedStruct*>(pNotification + 1);
    std::cout << std::setfill('0') <<
        "NetId: " << pAddr->netId <<
        " hUser 0x" << std::hex << hUser <<
        " sample time: " << std::dec << pNotification->nTimeStamp <<
        " sample size: " << std::dec << pNotification->cbSampleSize <<
        "\n";
    AlignedStruct printData1 = data[0];
    printAlignedStruct(std::cout, "MAIN.uAlignedOutput.aAlignedStructs[0].", printData1);
    AlignedStruct printData2 = data[1];
    printAlignedStruct(std::cout, "MAIN.uAlignedOutput.aAlignedStructs[1].", printData2);
    AlignedStruct printData3 = data[2];
    printAlignedStruct(std::cout, "MAIN.uAlignedOutput.aAlignedStructs[2].", printData3);
    
    // Restore output flags
    std::cout.flags(f);
}

static void notificationExample(std::ostream& out, const AdsDevice& route)
{
    const AdsNotificationAttrib attrib = {
        1,
        ADSTRANS_SERVERCYCLE,
        0,
        {4000000}
    };

    out << __FUNCTION__ << "():\n";
    AdsNotification notification { route, 0x4020, 4, attrib, &NotifyCallback, 0xDEADBEEF };

    out << "Hit ENTER to stop notifications\n";
    std::cin.ignore();
}

static void notificationByNameExample(std::ostream& out, const AdsDevice& route)
{
    const AdsNotificationAttrib attrib = {
        1,
        ADSTRANS_SERVERCYCLE,
        0,
        {4000000}
    };

    out << __FUNCTION__ << "():\n";
    AdsNotification notification { route, "MAIN.byByte[4]", attrib, &NotifyCallback, 0xBEEFDEAD };

    out << "Hit ENTER to stop by name notifications\n";
    std::cin.ignore();
}

static void notificationPackedStructExample(std::ostream& out, const AdsDevice& route)
{
    const AdsNotificationAttrib attrib = {
        sizeof(PackedStruct),
        ADSTRANS_SERVERONCHA,
        0,
        {500000} // 5ms
    };
    
    out << __FUNCTION__ << "():\n";
    AdsNotification notification { route, "MAIN.stOutput", attrib, &NotifyPackedStructureCallback, 0xFEF };
    
    out << "Hit ENTER to stop PackedStruct notifications\n";
    std::cin.ignore();
}

static void notificationAlignedStructExample(std::ostream& out, const AdsDevice& route)
{
    const AdsNotificationAttrib attrib = {
        sizeof(AlignedStruct),
        ADSTRANS_SERVERONCHA,
        0,
        {500000} // 5ms
    };
    
    out << __FUNCTION__ << "():\n";
    AdsNotification notification { route, "MAIN.stAlignedOutput", attrib, &NotifyAlignedStructureCallback, 0xFEF };
    
    out << "Hit ENTER to stop AlignedStruct notifications\n";
    std::cin.ignore();
}

static void notificationArrayOfAlignedStructExample(std::ostream& out, const AdsDevice& route)
{
    const AdsNotificationAttrib attrib = {
        3 * sizeof(AlignedStruct),
        ADSTRANS_SERVERONCHA,
        0,
        {500000} // 5ms
    };
    
    out << __FUNCTION__ << "():\n";
    AdsNotification notification { route, "MAIN.uAlignedOutput.aAlignedStructs", attrib, &NotifyArrayOfAlignedStructureCallback, 0xFEF };
    
    out << "Hit ENTER to stop array of AlignedStruct notifications\n";
    std::cin.ignore();
}

static void readExample(std::ostream& out, const AdsDevice& route)
{
    AdsVariable<uint8_t> readVar {route, 0x4020, 0};

    out << __FUNCTION__ << "():\n";
    for (size_t i = 0; i < 8; ++i) {
        out << "ADS read " << std::hex << (uint32_t)readVar << '\n';
    }
}

static void readByNameExample(std::ostream& out, const AdsDevice& route)
{
    AdsVariable<uint8_t> readVar {route, "MAIN.byByte[4]"};

    out << __FUNCTION__ << "():\n";
    for (size_t i = 0; i < 8; ++i) {
        out << "ADS read " << std::hex << (uint32_t)readVar << '\n';
    }
}

static void readWriteExample(std::ostream& out, const AdsDevice& route)
{
    AdsVariable<uint8_t> simpleVar {route, "MAIN.byByte[0]"};
    AdsVariable<uint8_t> validation {route, "MAIN.byByte[0]"};

    out << __FUNCTION__ << "():\n";
    simpleVar = 0xA5;
    out << "Wrote " << 0xA5 << " to MAIN.byByte and read " << (uint32_t)validation << " back\n";
    simpleVar = 0x5A;
    out << "Wrote " << (uint32_t)simpleVar << " to MAIN.byByte and read " << (uint32_t)validation << " back\n";
}

static void readWritePackedStruct(std::ostream& out, const AdsDevice& route)
{    
    AdsVariable<PackedStruct> writeStruct {route, "MAIN.stInput"};
    AdsVariable<PackedStruct> readStruct {route, "MAIN.stOutput"};

    PackedStruct value;
    value.digitalSwitch = true;
    char tmp[5] = "halo";
    strcpy(value.text, tmp);
    value.real = 1.2345;
    value.number = 678;
    value.byte = 254;

    out << __FUNCTION__ << "():\n";
    out << "Writing:" << "\n";
    printPackedStruct(out, "MAIN.stInput.", value);
    writeStruct = value;
    auto validation = (PackedStruct)readStruct;
    out << "Reading:" << "\n";
    printPackedStruct(out, "MAIN.stOutput.", validation);
}

static void readWriteAlignedStruct(std::ostream& out, const AdsDevice& route)
{    
    AdsVariable<AlignedStruct> writeStruct {route, "MAIN.stAlignedInput"};
    AdsVariable<AlignedStruct> readStruct {route, "MAIN.stAlignedOutput"};

    AlignedStruct value;
    value.digitalSwitch = true;
    char tmp[5] = "halo";
    strcpy(value.text, tmp);
    value.real = 1.2345;
    value.number = 678;
    value.byte = 254;

    out << __FUNCTION__ << "():\n";
    out << "Writing:" << "\n";
    printAlignedStruct(out, "MAIN.stAlignedInput.", value);
    writeStruct = value;
    auto validation = (AlignedStruct)readStruct;
    out << "Reading:" << "\n";
    printAlignedStruct(out, "MAIN.stAlignedOutput.", validation);
}

static void readWriteArrayOfAlignedStructs(std::ostream& out, const AdsDevice& route)
{
    AdsVariable<AlignedStructs> writeStructs {route, "MAIN.uAlignedInput.stAlignedStructs"};
    AdsVariable<std::array<AlignedStruct, 3>> readStructs {route, "MAIN.uAlignedOutput.aAlignedStructs"};
    
    
    AlignedStructs value;
    value.struct1.digitalSwitch = true;
    char tmp1[5] = "halo";
    strcpy(value.struct1.text, tmp1);
    value.struct1.real = 1.2345;
    value.struct1.number = 12345;
    value.struct1.byte = 1;
    value.struct2.digitalSwitch = false;
    char tmp2[5] = "helo";
    strcpy(value.struct2.text, tmp2);
    value.struct2.real = 2.3456;
    value.struct2.number = 23456;
    value.struct2.byte = 11;
    value.struct3.digitalSwitch = true;
    char tmp3[5] = "hilo";
    strcpy(value.struct3.text, tmp3);
    value.struct3.real = 3.4567;
    value.struct3.number = 32767;
    value.struct3.byte = 111;
    
    out << __FUNCTION__ << "():\n";
    out << "Writing:" << "\n";
    printAlignedStruct(out, "MAIN.uAlignedInput.stAlignedStructs.stAligned1.", value.struct1);
    printAlignedStruct(out, "MAIN.uAlignedInput.stAlignedStructs.stAligned2.", value.struct2);
    printAlignedStruct(out, "MAIN.uAlignedInput.stAlignedStructs.stAligned3.", value.struct3);
    writeStructs = value;
    std::array<AlignedStruct, 3> validation = readStructs;
    out << "Reading:" << "\n";
    printAlignedStruct(out, "MAIN.uAlignedOutput.aAlignedStructs[0].", validation[0]);
    printAlignedStruct(out, "MAIN.uAlignedOutput.aAlignedStructs[1].", validation[1]);
    printAlignedStruct(out, "MAIN.uAlignedOutput.aAlignedStructs[2].", validation[2]);
}

static void readWriteArrayExample(std::ostream& out, const AdsDevice& route)
{
    out << __FUNCTION__ << "():\n";
    static const std::array<uint8_t, 4> arrayToWrite = { 1, 2, 3, 4 };
    AdsVariable<std::array<uint8_t, 4> > arrayVar {route, "MAIN.byByte"};
    arrayVar = arrayToWrite;
    std::array<uint8_t, 4> readArray = arrayVar;
    out << "Wrote array with first value " << (uint32_t)arrayToWrite[0] << " and last value " <<
        (uint32_t)arrayToWrite[3] << "\n";
    out << "Read back array with first value " << (uint32_t)readArray[0] << " and last value " <<
        (uint32_t)readArray[3] << "\n";
}

static void readStateExample(std::ostream& out, const AdsDevice& route)
{
    out << __FUNCTION__ << "():\n";
    const auto state = route.GetState();

    out << "ADS state: " << std::dec << (uint16_t)state.ads << " devState: " << std::dec << (uint16_t)state.device <<
        '\n';
}

static void runExample(std::ostream& out)
{
    out << "Starting example\n";
    out << "Defining AmsNetId\n";
    static const AmsNetId remoteNetId { 169, 254, 197, 241, 1, 1 };
    out << "Defining remoteIpV4\n";
    //static const char remoteIpV4[] = "ads-server";
    static const char remoteIpV4[] = "192.168.0.26";

    // uncomment and adjust if automatic AmsNetId deduction is not working as expected
    //out << "Setting ADS local address\n";
    //AdsSetLocalAddress({192, 168, 1, 112, 1, 1});

    out << "Defining ADS route\n";
    AdsDevice route {remoteIpV4, remoteNetId, AMSPORT_R0_PLC_TC3};
    out << "Route set, starting examples\n";
    notificationExample(out, route);
    notificationByNameExample(out, route);
    readExample(out, route);
    readByNameExample(out, route);
    readWriteExample(out, route);
    readWriteArrayExample(out, route);
    readStateExample(out, route);
    readWritePackedStruct(out, route);
    notificationPackedStructExample(out, route);
    readWriteAlignedStruct(out, route);
    notificationAlignedStructExample(out, route);
    readWriteArrayOfAlignedStructs(out, route);
    notificationArrayOfAlignedStructExample(out, route);
}

int main()
{
    try {
        runExample(std::cout);
    } catch (const AdsException& ex) {
        std::cout << "Error: " << ex.errorCode << "\n";
        std::cout << "AdsException message: " << ex.what() << "\n";
    } catch (const std::runtime_error& ex) {
        std::cout << ex.what() << '\n';
    }
    std::cout << "Hit ENTER to continue\n";
    std::cin.ignore();
}
