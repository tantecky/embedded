#include <usb.hpp>
#include <usbd_cdc_if.h>
#include <cmsis_os.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdarg.h>

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
    printf("Ticks %d\r\n", HAL_GetTick());
}

void Usb::write(uint8_t *text, uint16_t len)
{
    if (len > TxCapacity)
    {
        len = TxCapacity;
    }

    CDC_Transmit_FS(text, len);
    osDelay(1);
}

int Usb::printf(const char *format, ...)
{
    va_list ap;
    va_start(ap, format);
    return vdprintf((int)this, format, ap);
}

extern "C"
{
    __attribute__((weak)) int _write(int file, char *ptr, int len)
    {
        switch (file)
        {
        case STDIN_FILENO:
            break;
        case STDOUT_FILENO:
        case STDERR_FILENO:
        default:
            ((class Usb *)file)->write((uint8_t *)ptr, len);
            break;
        }
        return len;
    }
}