#include <usb.hpp>
#include <usbd_cdc_if.h>
#include <cmsis_os.h>

void Usb::init()
{
    rxQueue_ = xQueueCreate(RxCapacity, sizeof(uint8_t));
    rxQueue = &rxQueue_;
}

void Usb::processRx()
{
    uint8_t byte;
    uint16_t idx = 0;
    bytesReceived_ = 0;

    // waiting here
    xQueueReceive(rxQueue_, &byte, portMAX_DELAY);
    rxBuffer_[idx] = byte;
    idx++;
    bytesReceived_++;

    const int bytesInQ = RxCapacity - uxQueueSpacesAvailable(rxQueue_);

    while (bytesInQ >= bytesReceived_)
    {
        if (xQueueReceive(rxQueue_, &byte, portMAX_DELAY) == pdPASS)
        {
            rxBuffer_[idx] = byte;
            idx++;
            bytesReceived_++;
        }
        else
        {
            break;
        }
    }

    write(rxBuffer_, bytesReceived_);
    write("Done\n", 5);
}

void Usb::write(const char *text, uint16_t len)
{
    write((uint8_t *)(text), len);
}
