#include "PacketReader.h"
#ifndef NETALARM_TESTING
#include "NetAlarm.h"
#else
#include "fixtures.hpp"
#endif /* ifndef  */

PacketReader::PacketReader(NetAlarm &alarm):
  alarm_(alarm)
{
}

void PacketReader::processPacket(byte size)
{
  // some junk, discard it
  if(size < 5)
    return;
  // packet is too large, discard it
  else if(size > MAX_RX_PACKET_SIZE)
    return;

  size_ = size;
  processed_ = 0;

  if(!gotValidId_())
    return;

  PacketType packetType = static_cast<PacketType>(readByte_());
  switch (packetType) 
  {
    case PACKET_ARM:
      alarm_.arm();
      break;
    case PACKET_DISARM:
      alarm_.disarm();
      break;

      // unknown/unsupported packet
    default:
      return;
  }
}

byte PacketReader::readByte_()
{
  return receiveBuffer_[processed_++];
}

uint32_t PacketReader::readUint32_()
{
  // network is big endian
  return readByte_() << 24 | readByte_() << 16 
    | readByte_() << 8 | readByte_();
}

bool PacketReader::gotValidId_()
{
  return alarm_.id() == readUint32_();
}
