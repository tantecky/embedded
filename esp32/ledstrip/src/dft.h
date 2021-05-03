#ifndef E90244BF_CFF3_4358_916B_8B971344ACE9
#define E90244BF_CFF3_4358_916B_8B971344ACE9

#ifdef __cplusplus
extern "C"
{
#endif

    struct blk
    {
        float r;
        float i;
    };

    static const float tcos[] =
        {-1.0, 0.0, 0.7071068,                  /* cos(pi), cos(pi/2), cos(pi/4) */
         0.9238795, 0.9807853, 0.9951847,       /* cos(pi/8), ... cos(pi/32) */
         0.9987955, 0.9996988, 0.9999247,       /* cos(pi/64), ... cos(pi/256) */
         0.9999812, 0.9999952938, 0.9999988234, /* cos(pi/512), ... cos(pi/2048) */
         0.9999997055, 0.9999999264};           /* cos(pi/4096), cos(pi/8192) */

    static const float tsin[] =
        {0.0, 1.0, 0.7071068,                          /* sin(pi), sin(pi/2), sin(pi/4) */
         0.3826834, 0.1950903, 0.0980171,              /* sin(pi/8), ... sin(pi/32) */
         4.9067674e-2, 2.4541228e-2, 1.2271538e-2,     /* sin(pi/64), ... sin(pi/256) */
         6.1358846e-3, 3.067956691e-3, 1.533980094e-3, /* sin(pi/512), ...  sin(pi/2048) */
         7.669902711e-4, 3.834950931e-4};              /* sin(pi/4096), sin(pi/8192) */

    void fft(struct blk *x, int sz, int dir);
    /* dir=-1/1 for DFT/IFT */
    void hfold(struct blk *x, int n, int dir);
    /* fftc(*blk,sz)   Complex-Complex DFT   sz = # of complex inputs/outputs */
    void fftc(struct blk *x, int sz);
    /* iftc(*blk,sz)   Complex-Complex IFT   sz = # of complex inputs/outputs */
    void iftc(struct blk *x, int sz);
    /* fftr(*blk,sz)   Real-Complex DFT      sz = # of real inputs */
    void fftr(struct blk *x, int sz);
    /* iftr(*blk,sz)   Complex-Real IFT      sz = # of real outputs */
    void iftr(struct blk *x, int sz);

#ifdef __cplusplus
}
#endif

#endif /* E90244BF_CFF3_4358_916B_8B971344ACE9 */
