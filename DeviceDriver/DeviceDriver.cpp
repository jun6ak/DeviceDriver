#include "DeviceDriver.h"
#include <vector>
#include <stdexcept>

using namespace std;

DeviceDriver::DeviceDriver(FlashMemoryDevice* hardware) : m_hardware(hardware)
{}

int DeviceDriver::read(long address)
{
    vector<int> data;

    for (int i = 0; i < 5; i++)
    {
        data.push_back((int)(m_hardware->read(address)));
    }

    int comp = data[0];
    for (int& value : data)
    {
        if (value == comp) continue;

        throw runtime_error("[READ ERROR] Flash Memory is not unstable.");
    }

    return comp;
}

void DeviceDriver::write(long address, int data)
{
    // TODO: implement this method
    m_hardware->write(address, (unsigned char)data);
}