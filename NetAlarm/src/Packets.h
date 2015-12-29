#ifndef PACKETS_H_ACGYNJXY
#define PACKETS_H_ACGYNJXY

class PacketWriter
{
  public:
    PacketWriter(const NetAlarm &alarm);

    byte *packet() { return packet_; }

  private:
    static const byte MAX_PACKET_SIZE = 32;

    byte packet_[MAX_PACKET_SIZE];
    const NetAlarm &alarm_;
    byte size_;
    byte *tip_;

    void writeHeader_();

};


#endif /* end of include guard: PACKETS_H_ACGYNJXY */
