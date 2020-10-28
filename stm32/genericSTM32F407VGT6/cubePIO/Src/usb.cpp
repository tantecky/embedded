#include <usb.hpp>
#include <usbd_cdc_if.h>
#include <cmsis_os.h>

void Usb::init()
{
    rxQueue_ = xQueueCreate(2 * APP_RX_DATA_SIZE, sizeof(uint8_t));
    rxQueue = &rxQueue_;
}

void Usb::process()
{
    uint8_t byte;

    while (xQueueReceive(rxQueue_, &byte, portMAX_DELAY) == pdPASS)
    {
        CDC_Transmit_FS(&byte, 1);
        osDelay(1);
    }
}