#include "../DeviceDriver/FlashMemoryDevice.h"
#include "gmock/gmock.h"

class MockedFlashMemoryDevice : public FlashMemoryDevice
{
public:
    MockedFlashMemoryDevice() : readCount{ 0 } {}

    //MOCK_METHOD(unsigned char, read, (long address), (override));
    //MOCK_METHOD(void, wirte, (long address, unsigned char data), (override));

    unsigned char read(long address) override
    {
        readCount++;
        return 0;
    }

    void write(long address, unsigned char data) override
    {

    }

    int getReadCount()
    {
        return readCount;
    }

private:
    int readCount;
};
