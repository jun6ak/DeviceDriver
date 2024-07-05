#include "DeviceDriver.h"
#include <stdexcept>

DeviceDriver::DeviceDriver(FlashMemoryDevice* hardware) : m_hardware(hardware)
{}

int DeviceDriver::read(long address)
{
    vector<int> data = readFlashSeveralTimes(address, READ_COUNT);

    checkValidity(data);

    return *data.begin();
}

void DeviceDriver::write(long address, int data)
{
    // TODO: implement this method
    m_hardware->write(address, (unsigned char)data);
}

vector<int> DeviceDriver::readFlashSeveralTimes(long address, int count)
{
    vector<int> data;

    for (int i = 0; i < count; i++)
    {
        data.push_back((int)(m_hardware->read(address)));
    }

    return data;
}

void DeviceDriver::checkValidity(vector<int> data)
{
    if (data.size() == 0)
    {
        throw runtime_error("[READ ERROR] Must read flash before checking validity.");
    }

    for (int& value : data)
    {
        if (value == *data.begin()) continue;

        throw runtime_error("[READ ERROR] Flash Memory is not unstable.");
    }
}