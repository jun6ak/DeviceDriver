#include "pch.h"
#include "MockedFlashMemoryDevice.cpp"
#include "../DeviceDriver/DeviceDriver.cpp"

#include <stdexcept>
#include <string>

using namespace std;

class DeviceDriverTest : public testing::Test
{
public:
    void SetUp() override
    {
        address = ADDRESS_A;
    }
protected:
    long address;
    const long ADDRESS_A = 0x0A;

    MockedFlash mockedFlash;
    DeviceDriver deviceDriver{ &mockedFlash };
};

TEST_F(DeviceDriverTest, ReadFiveTimes) {
    EXPECT_CALL(mockedFlash, getData(testing::_))
        .Times(5)
        .WillRepeatedly(testing::Return(0));

    EXPECT_EQ(deviceDriver.read(address), 0);
    EXPECT_EQ(mockedFlash.getReadCount(), 5);
}

TEST_F(DeviceDriverTest, ReadValidData) {
    EXPECT_CALL(mockedFlash, getData(testing::_))
        .Times(5)
        .WillRepeatedly(testing::Return(0));

    try
    {
        EXPECT_EQ(deviceDriver.read(address), 0);
    }
    catch (...)
    {
        FAIL();
    }
}

TEST_F(DeviceDriverTest, ReadInvalidData) {
    EXPECT_CALL(mockedFlash, getData(testing::_))
        .Times(5)
        .WillOnce(testing::Return(1))
        .WillRepeatedly(testing::Return(0));

    try
    {
        int data = deviceDriver.read(address);
        FAIL();
    }
    catch (exception& e)
    {
        EXPECT_EQ(string("[READ ERROR] Flash Memory is not unstable."), string(e.what()));
    }
}