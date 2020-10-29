#ifndef E6BB1AAD_FCC5_49C4_80BD_AFCFF4472F34
#define E6BB1AAD_FCC5_49C4_80BD_AFCFF4472F34
#include <FreeRTOS.h>
#include <queue.h>
#include <usbd_cdc_if.h>
#include <cmsis_os.h>

constexpr uint16_t RxCapacity = APP_RX_DATA_SIZE;
constexpr uint16_t TxCapacity = APP_TX_DATA_SIZE;

class Usb
{
private:
    QueueHandle_t rxQueue_;
    uint16_t bytesReceived_;
    uint8_t rxBuffer_[RxCapacity];
    uint8_t txBuffer_[TxCapacity];

public:
    Usb()
    {
    }

    void init();
    void processRx();
    void write(const char *text, uint16_t len);
    inline void write(uint8_t *text, uint16_t len)
    {
        CDC_Transmit_FS(text, len);
        osDelay(1);
    }
};

#endif /* E6BB1AAD_FCC5_49C4_80BD_AFCFF4472F34 */
