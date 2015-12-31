#ifndef FIXTURES_HPP_FVMWRZY6
#define FIXTURES_HPP_FVMWRZY6

#include <stdint.h>
#include <stdbool.h>

typedef bool boolean;
typedef uint8_t byte;

class Ethernet
{
};

class NetAlarm
{
  friend class NetAlarmTests_PacketReader_processPacket_Test;
  public:
    explicit NetAlarm(const uint32_t id):
      id_(id), armed_(true)
    {
    }
    uint32_t id() const { return id_; }

    void arm()
    {
      if (armed_)
        return;

      armed_ = true;
    }

    void disarm()
    {
      if (!armed_)
        return;

      armed_ = false;
    }

  private:
    const uint32_t id_;
    bool armed_;
};

#endif /* end of include guard: FIXTURES_HPP_FVMWRZY6 */
