#include <gtest/gtest.h>
#include "fixtures.hpp"

#include "PacketReader.h"
#include "PacketWriter.h"

using namespace ::testing;

const uint32_t id = 0xDEADBEEF;

class NetAlarmTests : public Test
{
  public:
    NetAlarm *alarm;
    PacketWriter *writer;

    virtual void SetUp() 
    {
      alarm = new NetAlarm(id);
      writer = new PacketWriter(*alarm);
    }

    virtual void TearDown() 
    {
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
  // ASSERT_EQ(packet[1], 0xAD);
  // ASSERT_EQ(packet[2], 0xBE);
  // ASSERT_EQ(packet[3], 0xEF);
  // ASSERT_EQ(writer->size(), 4);
}

// TEST_F(NetAlarmTests, PacketWriter_writeByte)
// {
  // writer->writeHeader_();
  // writer->writeByte_(0xAA);
  // byte *packet = writer->packet();

  // ASSERT_EQ(packet[4], 0xAA);
  // ASSERT_EQ(writer->size(), 5);
// }

// TEST_F(NetAlarmTests, PacketWriter_writePacket_TRIGGER)
// {
  // writer->writePacket(PACKET_TRIGGER);
  // byte *packet = writer->packet();

  // ASSERT_EQ(packet[4], PACKET_TRIGGER);
  // ASSERT_EQ(writer->size(), 5);
// }
