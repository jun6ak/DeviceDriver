#pragma once
#include "FlashMemoryDevice.h"
#include <vector>

using namespace std;

class DeviceDriver
{
public:
    DeviceDriver(FlashMemoryDevice* hardware);
    int read(long address);
    void write(long address, int data);


protected:
    FlashMemoryDevice* m_hardware;

    const int READ_COUNT = 5;

    vector<int> readFlashSeveralTimes(long address, int count);
    void checkReadValidity(vector<int> data);
    void checkWriteValidity(long address);
};