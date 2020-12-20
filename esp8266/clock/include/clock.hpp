#ifndef DCC88C0F_125C_4C12_BF0B_8DAEEA272855
#define DCC88C0F_125C_4C12_BF0B_8DAEEA272855

#include "main.hpp"

class Clock
{

private:
    static const char ntpServerName[];
    static constexpr int timeZone = 1;         // Central European Time
    static constexpr int NTP_PACKET_SIZE = 48; // NTP time is in the first 48 bytes of message
    static byte packetBuffer[];                //buffer to hold incoming & outgoing packets

    static time_t prevDisplay; // when the digital clock was displayed

    static time_t getNtpTime();
    static void sendNTPpacket(IPAddress &address);

    static void draw();

public:
    static int hour;

    static void setup();
    static void tick();
};

#endif /* DCC88C0F_125C_4C12_BF0B_8DAEEA272855 */
