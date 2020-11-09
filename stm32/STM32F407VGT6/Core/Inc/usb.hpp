#ifndef E6BB1AAD_FCC5_49C4_80BD_AFCFF4472F34
#define E6BB1AAD_FCC5_49C4_80BD_AFCFF4472F34
#include "FreeRTOS.h"
#include "queue.h"
#include "semphr.h"
#include "usbd_cdc_if.h"
#include "cmsis_os.h"

constexpr uint16_t RxCapacity = APP_RX_DATA_SIZE;
constexpr uint16_t TxCapacity = APP_TX_DATA_SIZE;

class Usb
{
private:
    QueueHandle_t rxQueue_;
    SemaphoreHandle_t txMutex_;
    uint16_t bytesReceived_;
    uint8_t rxBuffer_[RxCapacity];
    uint8_t txBuffer_[TxCapacity];

public:
    Usb()
    {
    }

    void init();
    void processRx();
    inline void write(const char *text, uint16_t len)
    {
        write((uint8_t *)(text), len);
    }
    void write(uint8_t *text, uint16_t len);
    int printf(const char *format, ...);
};

extern Usb Serial;

#endif /* E6BB1AAD_FCC5_49C4_80BD_AFCFF4472F34 */
