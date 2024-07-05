#include "pch.h"
#include "MockedFlashMemoryDevice.cpp"
#include "../DeviceDriver/Application.cpp"

#include <stdexcept>
#include <string>

using namespace std;

class ApplicationTest : public testing::Test
{
public:
    void mockNextValidReadData(long startAddr, long endAddr, int data)
    {
        for (long addr = startAddr; addr <= endAddr; addr++)
        {
            EXPECT_CALL(mockedFlash, read(addr))
                .Times(VALID_READ_COUNT)
                .WillRepeatedly(testing::Return(data));
        }
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
    // Arrange
    mockNextValidReadData(1, 4, BLANK_BYTE);
    testing::internal::CaptureStdout();

    // Act
    application.readAndPrint(1, 4);

    // Assert
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(string("FFFFFFFF"), output);
}

