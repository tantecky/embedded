#ifndef DB882A5D_FBDB_40F3_8A7D_214441CF15FD
#define DB882A5D_FBDB_40F3_8A7D_214441CF15FD

constexpr bool isPowerof2(int v)
{
    return v && ((v & (v - 1)) == 0);
}

constexpr int log2(int n)
{
    return ((n < 2) ? 1 : 1 + log2(n / 2));
}

#endif /* DB882A5D_FBDB_40F3_8A7D_214441CF15FD */
