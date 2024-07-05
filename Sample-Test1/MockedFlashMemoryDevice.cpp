#include "../DeviceDriver/FlashMemoryDevice.h"
#include "gmock/gmock.h"

class FlashSimulator : public FlashMemoryDevice
{
public:
    FlashSimulator() : readCount{ 0 } { }

    unsigned char read(long address) override
    {
        readCount++;
        return getData(address);
    }

    void write(long address, unsigned char data) override
    {
        return;
    }

    int getReadCount()
    {
        return readCount;
    }

    virtual unsigned char getData(long address)
    {
        return 0;
    }

protected:
    int readCount;
};

class MockedFlash : public FlashSimulator
{
public:
    MockedFlash() : FlashSimulator{ } {}

    MOCK_METHOD(unsigned char, getData, (long address), (override));
};