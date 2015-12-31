#ifndef PACKETREADER_H_VEIWPRYR
#define PACKETREADER_H_VEIWPRYR
class NetAlarm;
#include <Arduino.h>

#include "PacketTypes.h"

class PacketReader
{
  public:
  static const byte MAX_RX_PACKET_SIZE = 32;
  PacketReader(NetAlarm &alarm);

  byte *receiveBuffer() { return receiveBuffer_; }
  void processPacket(byte size);

  private:
  byte receiveBuffer_[MAX_RX_PACKET_SIZE];
  NetAlarm &alarm_;
  byte size_;
  byte processed_;

  byte readByte_();
  uint32_t readUint32_();
  bool gotValidId_();
};

#endif /* end of include guard: PACKETREADER_H_VEIWPRYR */
