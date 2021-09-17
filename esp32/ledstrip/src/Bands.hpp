#ifndef D0615D1C_A2F3_4138_B4BF_7E34AC5ADD44
#define D0615D1C_A2F3_4138_B4BF_7E34AC5ADD44

#include <cstring>
#include <type_traits>

class Bands
{
public:
    static constexpr int Count = 16;

    static constexpr float Freqs[] =
        {
            20, // <20 Hz; 60 Hz)
            60,
            155,
            250,
            375,
            500,
            1250,
            2000,
            3000,
            4000,
            5000,
            6000,
            8500,
            12000,
            14500,
            17000,
    };

    static constexpr float Amplitudes[] =
        {
            1.0f / 1e6,
            1.0f / 1e6,
            1.0f / 1e6,
            1.0f / 1e6,
            1.0f / 1e6,
            1.0f / 1e5,
            1.0f / 1e5,
            1.0f / 1e5,
            1.0f / 1e5,
            1.0f / 1e5,
            1.0f / 1e5,
            1.0f / 1e5,
            1.0f / 1e5,
            1.0f / 1e5,
            1.0f / 1e5,
            1.0f / 1e5,
    };

private:
    float values[Count] = {0};

    static_assert(sizeof(values) == sizeof(Freqs), "lengths have to match");
    static_assert(sizeof(Amplitudes) == sizeof(Freqs), "lengths have to match");

    void normalize();

public:
    void fill(const float *const freqs, const float *const mags);
    inline const float getValue(const int bandIdx) const { return values[bandIdx]; }
    void print() const;
};

#endif /* D0615D1C_A2F3_4138_B4BF_7E34AC5ADD44 */
