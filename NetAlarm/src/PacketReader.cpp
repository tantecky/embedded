#include "PacketReader.h"
#ifndef NETALARM_TESTING
#include "NetAlarm.h"
#else
#include "fixtures.hpp"
#endif /* ifndef  */
#include "Debug.h"

PacketReader::PacketReader(NetAlarm &alarm):
  alarm_(alarm), processed_(0)
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
  {
    DEBUG_PRINT("Received packet got invalid ID");
    return;
  } 

  PacketType packetType = static_cast<PacketType>(readByte_());
  DEBUG_PRINT(String("Received packet type: ") + String(packetType));

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
      DEBUG_PRINT("Received unknown packet");
      return;
  }
}

byte PacketReader::readByte_()
{
  byte byteRead = receiveBuffer_[processed_++];
  DEBUG_PRINT(String("Byte read: ") + String(byteRead));
  return byteRead;
}

uint32_t PacketReader::readUint32_()
{
  // network is big endian
  return static_cast<uint32_t>(readByte_()) << 24 
    | static_cast<uint32_t>(readByte_()) << 16
    | static_cast<uint32_t>(readByte_()) << 8 
    | static_cast<uint32_t>(readByte_());
}

bool PacketReader::gotValidId_()
{
  uint32_t idFromPacket = readUint32_();
  DEBUG_PRINT(String("ID from packet: ") + String(idFromPacket));
  return alarm_.id() == idFromPacket;
}
