#pragma once

#include "DeviceDriver.h"

class Application
{
public:
    Application(DeviceDriver* driver)
        : deviceDriver{ driver } { }

    void readAndPrint(long startAddr, long endAddr);
    void writeAll(int value);

private:
    DeviceDriver* deviceDriver;
};