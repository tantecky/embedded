#ifndef E6BB1AAD_FCC5_49C4_80BD_AFCFF4472F34
#define E6BB1AAD_FCC5_49C4_80BD_AFCFF4472F34
#include <FreeRTOS.h>
#include <queue.h>

class Usb
{
private:
    QueueHandle_t rxQueue_;

public:
    Usb()
    {
    }

    void init();
    void process();
};

#endif /* E6BB1AAD_FCC5_49C4_80BD_AFCFF4472F34 */
