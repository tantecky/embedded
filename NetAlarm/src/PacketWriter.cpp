#include "PacketWriter.h"
#include "NetAlarm.h"

PacketWriter::PacketWriter(const NetAlarm &alarm):
  alarm_(alarm), size_(0), tip_(packet_)
{
}

void PacketWriter::writePacket(PacketType packetType)
{
  size_ = 0;
  tip_ = packet_;

  switch (packetType) {
    case PACKET_ARM:
    case PACKET_DISARM:
    case PACKET_TRIGGER:
      writeHeader_();
      writeByte_(packetType);
      break;
  }
}

void PacketWriter::writeHeader_()
{
  uint32_t id = alarm_.id();

  // network is big endian
  *tip_++ = id >> 24;
  *tip_++ = id >> 16 & 0xFF;
  *tip_++ = id >> 8 & 0xFF;
  *tip_++ = id & 0xFF;

  size_ += 4;
}

void PacketWriter::writeByte_(byte byte)
{
  if(size_ < MAX_PACKET_SIZE)
  {
    *tip_++ = byte;
    size_++;
  }
}
