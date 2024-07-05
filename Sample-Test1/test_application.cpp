#include "pch.h"
#include "MockedFlashMemoryDevice.cpp"
#include "../DeviceDriver/Application.cpp"

#include <stdexcept>
#include <string>

using namespace std;

class ApplicationTest : public testing::Test
{
public:
    void mockNextValidReadData(long address, int data)
    {
        EXPECT_CALL(mockedFlash, read(address))
            .Times(VALID_READ_COUNT)
            .WillRepeatedly(testing::Return(data));
    }

    void mockNextInvalidReadData(int data)
    {
        EXPECT_CALL(mockedFlash, read(testing::_))
            .Times(VALID_READ_COUNT)
            .WillOnce(testing::Return(data + 1))
            .WillRepeatedly(testing::Return(data));
    }

protected:
    const unsigned char BLANK_BYTE = 0xFF;
    const int VALID_READ_COUNT = 5;

    MockedFlash mockedFlash;
    DeviceDriver deviceDriver{ &mockedFlash };
    Application application{ &deviceDriver };
};

TEST_F(ApplicationTest, ReadAndPrint)
{
    mockNextValidReadData(1, BLANK_BYTE);
    mockNextValidReadData(2, BLANK_BYTE);
    mockNextValidReadData(3, BLANK_BYTE);
    mockNextValidReadData(4, BLANK_BYTE);

    application.readAndPrint(1, 4);
}