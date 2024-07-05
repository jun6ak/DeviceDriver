#include "../DeviceDriver/FlashMemoryDevice.h"
#include "gmock/gmock.h"

class MockedFlash : public FlashMemoryDevice
{
public:
    MOCK_METHOD(unsigned char, read, (long address), (override));
    MOCK_METHOD(void, write, (long address, unsigned char data), (override));
};