#include "pch.h"
#include "MockedFlashMemoryDevice.cpp"
#include "../DeviceDriver/DeviceDriver.cpp"

TEST(DeviceDriverTest, ReadFiveTimes) {
    MockedFlashMemoryDevice mockedHardware;
    DeviceDriver deviceDriver(&mockedHardware);

    long address = 0xA0;

    deviceDriver.read(address);

    EXPECT_EQ(mockedHardware.getReadCount(), 5);
}