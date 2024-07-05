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

    void mockNextValidReadData(int data)
    {
        EXPECT_CALL(mockedFlash, getData(testing::_))
            .Times(VALID_READ_COUNT)
            .WillRepeatedly(testing::Return(data));
    }

    void mockNextInvalidReadData(int data)
    {
        EXPECT_CALL(mockedFlash, getData(testing::_))
            .Times(VALID_READ_COUNT)
            .WillOnce(testing::Return(data + 1))
            .WillRepeatedly(testing::Return(data));
    }

protected:
    long address;
    const long ADDRESS_A = 0x0A;
    const unsigned char BLANK_BYTE = 0xFF;
    const int VALID_READ_COUNT = 5;

    MockedFlash mockedFlash;
    DeviceDriver deviceDriver{ &mockedFlash };
};

TEST_F(DeviceDriverTest, ReadFiveTimes) {
    mockNextValidReadData(BLANK_BYTE);

    EXPECT_EQ(deviceDriver.read(address), BLANK_BYTE);
    EXPECT_EQ(mockedFlash.getReadCount(), VALID_READ_COUNT);
}

TEST_F(DeviceDriverTest, ReadValidData) {
    mockNextValidReadData(BLANK_BYTE);

    EXPECT_EQ(deviceDriver.read(address), BLANK_BYTE);
}

TEST_F(DeviceDriverTest, ReadInvalidData) {
    mockNextInvalidReadData(BLANK_BYTE);

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

TEST_F(DeviceDriverTest, WriteData) {
    mockNextValidReadData(BLANK_BYTE);

    deviceDriver.write(address, 0x0);
}

TEST_F(DeviceDriverTest, WriteDataInvalidRegion) {
    mockNextValidReadData(0);

    EXPECT_THROW(deviceDriver.write(address, 0x0), exception);
}