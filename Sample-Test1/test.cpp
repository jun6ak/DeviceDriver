#include "pch.h"
#include "MockedFlashMemoryDevice.cpp"
#include "../DeviceDriver/DeviceDriver.cpp"

class DeviceDriverTest : public testing::Test
{
protected:
    MockedFlash mockedFlash;
    DeviceDriver deviceDriver{ &mockedFlash };
};

TEST_F(DeviceDriverTest, ReadFiveTimes) {
    long address = 0xA0;

    EXPECT_CALL(mockedFlash, getData(testing::_)).Times(5).WillRepeatedly(testing::Return(0));

    deviceDriver.read(address);

    EXPECT_EQ(mockedFlash.getReadCount(), 5);
}