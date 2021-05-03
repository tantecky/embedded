/* dft.c        Paul Mennen paul@mennen.org

fftc(*blk,sz)         Complex-Complex DFT   sz = # of complex inputs/outputs
iftc(*blk,sz)         Complex-Complex IFT   sz = # of complex inputs/outputs
fftr(*blk,sz)         Real-Complex DFT      sz = # of real inputs
iftr(*blk,sz)         Complex-Real IFT      sz = # of real outputs

*/

#include <stdio.h>
#include <math.h>
#include "dft.h"

#define RMS 1.414213562 /* adjust FFT results to read rms */

void fft(struct blk *x, int sz, int dir)
/* In-place complex to complex transform. From Oppenheim & Schafer, pg 332
*/
/* dir=-1/1 DFT/IFT, sz = Number of complex elements, must be a power of 2
*/
{
    float Wr, Wi, Ur, Ui, Tr, Ti, Vr, Vi;
    int k, mm, le, le1, j, i, ii, m;

    m = 0;
    le = j = sz;
    while (j >>= 1)
        m++;                    /* m = number of folds = log2(sz) */
    for (mm = 1; mm <= m; mm++) /* do m folds */
    {
        le1 = le >> 1; /* le1 = le/2 */
        Ur = 1.0;
        Ui = 0.0;                 /* initial phasor */
        Wr = tcos[m - mm];        /* Wr=cos(PI/le1); (phasor increment) */
        Wi = dir * tsin[m - mm];  /* Wi=dir*sin(PI/le1); (phasor increment) */
        for (j = 0; j < le1; j++) /* do sz/2 butterflys in le/2 groups */
        {
            i = j;         /* i points to one butterfly leg */
            while (i < sz) /* do sz/le butterflys */
            {
                ii = i + le1; /* ii points to the other butterfly leg */
                Tr = x[i].r + x[ii].r;
                Ti = x[i].i + x[ii].i;
                Vr = x[i].r - x[ii].r;
                Vi = x[i].i - x[ii].i;
                if (mm == m)
                {
                    x[ii].r = Vr;
                    x[ii].i = Vi;
                } /* last fold */
                else
                {
                    x[ii].r = Vr * Ur - Vi * Ui;
                    x[ii].i = Vr * Ui + Vi * Ur;
                }
                x[i].r = Tr;
                x[i].i = Ti;
                i += le;
            }
            Tr = Ur;
            Ur = Ur * Wr - Ui * Wi;
            Ui = Ui * Wr + Tr * Wi; /* update phasor */
        }                           /* end for (j=0; j<le1; j++) */
        le = le1;
    } /* end for (mm=1; mm<=m; mm++) */

    /* bit reversal */
    m = sz >> 1;
    j = 0;
    for (i = 0; i < sz - 1; i++)
    {
        if (i < j)
        {
            Tr = x[j].r;
            Ti = x[j].i; /* swap i & j */
            x[j].r = x[i].r;
            x[j].i = x[i].i;
            x[i].r = Tr;
            x[i].i = Ti;
        }
        k = m;
        while (k <= j)
        {
            j -= k;
            k >>= 1;
        }
        j += k;
    }
}

void hfold(struct blk *x, int n, int dir) /* dir=-1/1 for DFT/IFT */
{
    float Wr, Wi, Ur, Ui, Zr, Zi, Xr, Xi, Yr, Yi;
    int k, n2, nk;
    k = 0;
    n2 = n;
    while (n2 >>= 1)
        k++; /* k = number of folds */
    /*        Initial phasor (Ur,Ui)           Phasor increment (Wr,Wi) */
    /* DFT:  -cos(PI/n) - i*sin(PI/n)          cos(PI/n) + i*sin(PI/n)  */
    /* IFT:   cos(PI/n) - i*sin(PI/n)          cos(PI/n) - i*sin(PI/n)  */
    Ur = dir * (Wr = tcos[k]);
    Wi = dir * (Ui = -tsin[k]);
    n2 = n >> 1;
    for (k = 1; k <= n2; k++)
    {
        Zr = x[k].r + x[nk = n - k].r;
        Zi = x[k].i - x[nk].i;
        Xr = x[k].r - x[nk].r;
        Xi = x[k].i + x[nk].i;
        Yr = Ui * Xr - Ur * Xi;
        Yi = Ui * Xi + Ur * Xr;
        x[k].r = Zr + Yr;
        x[k].i = Zi + Yi;
        x[nk].r = Zr - Yr;
        x[nk].i = Yi - Zi;
        Zr = Ur;
        Ur = Ur * Wr - Ui * Wi;
        Ui = Ui * Wr + Zr * Wi; /* update phasor */
    }
}

/* fftc(*blk,sz)   Complex-Complex DFT   sz = # of complex inputs/outputs */
void fftc(struct blk *x, int sz)
{
    float sc;
    fft(x, sz, -1);
    sc = 1.0 / sz;
    while (--sz >= 0)
    {
        x[sz].r *= sc;
        x[sz].i *= sc;
    }
}

/* iftc(*blk,sz)   Complex-Complex IFT   sz = # of complex inputs/outputs */
void iftc(struct blk *x, int sz)
{
    fft(x, sz, 1);
}

/* fftr(*blk,sz)   Real-Complex DFT      sz = # of real inputs */
void fftr(struct blk *x, int sz)
{
    float sc;
    sc = (0.5 * RMS) / sz; /* scale fft results (as rms single sided spectrum) */
    fft(x, sz >>= 1, -1);
    hfold(x, sz, -1); /* hermitian fold */
    x[0].r = RMS * (x[0].r + x[0].i);
    x[0].i = 0.0; /* don't compute fmax term */
    while (--sz >= 0)
    {
        x[sz].r *= sc;
        x[sz].i *= sc;
    }
}

/* iftr(*blk,sz)   Complex-Real IFT      sz = # of real outputs */
void iftr(struct blk *x, int sz)
{
    float sc;
    hfold(x, sz >>= 1, 1); /* hermitian fold */
    x[0].i = x[0].r;
    fft(x, sz, 1);
    sc = 1.0 / RMS; /* scale result (assume rms single sided spectrum) */
    while (--sz >= 0)
    {
        x[sz].r *= sc;
        x[sz].i *= sc;
    } /* scale result */
}
