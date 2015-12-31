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
  public:
    explicit NetAlarm(const uint32_t id):
      id_(id) { }
    uint32_t id() const { return id_; }

    void arm() {}
    void disarm() {}

  private:
    const uint32_t id_;
};

#endif /* end of include guard: FIXTURES_HPP_FVMWRZY6 */
