#ifndef E5061DA8_74F9_4C5D_ADF4_8873DA397C10
#define E5061DA8_74F9_4C5D_ADF4_8873DA397C10
class Logger
{
private:
    unsigned long lastReport_;

public:
    Logger() : lastReport_(0)
    {
    }

    void setup();
    void tick();
};

#endif /* E5061DA8_74F9_4C5D_ADF4_8873DA397C10 */
