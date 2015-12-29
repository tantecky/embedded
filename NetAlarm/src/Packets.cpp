#include <Arduino.h>
#include "NetAlarm.h"
#include "Packets.h"

PacketWriter::PacketWriter(const NetAlarm &alarm):
  alarm_(alarm), size_(0), tip_(packet_)
{
}

void PacketWriter::writeHeader_()
{
  size_ = 0;
  tip_ = packet_;

  uint32_t id = alarm_.id();

  // network is big endian
  *tip_++ = id >> 24;
  *tip_++ = id >> 16 & 0xFF;
  *tip_++ = id >> 8 & 0xFF;
  *tip_++ = id & 0xFF;

  size_ += 4;
}
