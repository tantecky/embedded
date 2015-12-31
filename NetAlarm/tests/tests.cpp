#include <gtest/gtest.h>
#include <string.h>        

#include "fixtures.hpp"
#include "PacketReader.h"
#include "PacketWriter.h"

using namespace ::testing;


class NetAlarmTests : public Test
{
  public:
    uint32_t id;
    byte *disarmPacket;
    byte disarmPacketSize;

    NetAlarm *alarm;
    PacketWriter *writer;
    PacketReader *reader;

    virtual void SetUp() 
    {
      id = 0xDEADBEEF;
      alarm = new NetAlarm(id);
      writer = new PacketWriter(*alarm);
      reader = new PacketReader(*alarm);
      disarmPacket = new byte[5];

      disarmPacket[0] = 0xDE;
      disarmPacket[1] = 0xAD;
      disarmPacket[2] = 0xBE;
      disarmPacket[3] = 0xEF;
      disarmPacket[4] = PACKET_DISARM;

      disarmPacketSize = static_cast<byte>(sizeof(disarmPacket));

      memcpy(reader->receiveBuffer(), disarmPacket, disarmPacketSize);
    }

    virtual void TearDown() 
    {
      delete[] disarmPacket;
      delete reader;
      delete writer;
      delete alarm;
    }
};

TEST_F(NetAlarmTests, NetAlarm_id)
{
  ASSERT_EQ(alarm->id(), id);
}

TEST_F(NetAlarmTests, PacketWriter_writeHeader)
{
  writer->writeHeader_();
  byte *packet = writer->packet();

  ASSERT_EQ(packet[0], 0xDE);
  ASSERT_EQ(packet[1], 0xAD);
  ASSERT_EQ(packet[2], 0xBE);
  ASSERT_EQ(packet[3], 0xEF);
  ASSERT_EQ(writer->size(), 4);
}

TEST_F(NetAlarmTests, PacketWriter_writeByte)
{
  writer->writeHeader_();
  writer->writeByte_(0xAA);
  byte *packet = writer->packet();

  ASSERT_EQ(packet[4], 0xAA);
  ASSERT_EQ(writer->size(), 5);
}

TEST_F(NetAlarmTests, PacketWriter_writePacket_TRIGGER)
{
  writer->writePacket(PACKET_TRIGGER);
  byte *packet = writer->packet();

  ASSERT_EQ(packet[4], PACKET_TRIGGER);
  ASSERT_EQ(writer->size(), 5);
}

TEST_F(NetAlarmTests, PacketReader_readByte)
{
  ASSERT_EQ(reader->readByte_(), 0xDE);
  ASSERT_EQ(reader->processed_, 1);
}

TEST_F(NetAlarmTests, PacketReader_readUint32)
{
  ASSERT_EQ(reader->readUint32_(), id);
  ASSERT_EQ(reader->processed_, 4);
}

TEST_F(NetAlarmTests, PacketReader_gotValidId)
{
  ASSERT_TRUE(reader->gotValidId_());
  ASSERT_EQ(reader->processed_, 4);
}

TEST_F(NetAlarmTests, PacketReader_processPacket)
{
  reader->processPacket(disarmPacketSize);
  ASSERT_FALSE(alarm->armed_);
  ASSERT_EQ(reader->processed_, 5);
}
