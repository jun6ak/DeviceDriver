#include "Application.h"
#include <iostream>

void Application::readAndPrint(long startAddr, long endAddr)
{
    vector<int> data;

    for (long addr = startAddr; addr <= endAddr; addr++)
    {
        data.push_back(deviceDriver->read(addr));
    }

    for (const auto& value : data)
    {
        std::cout << std::uppercase << std::hex << value;
    }
}

void Application::writeAll(int value)
{
    /*
        ✔ WriteAll(value)
        ▪ 0x00 ~ 0x04 까지 모두 value 값으로 Write한다.
    */
}
