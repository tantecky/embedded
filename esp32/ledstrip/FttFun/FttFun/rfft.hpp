#ifndef _RFFT_H
#define _RFFT_H

//  out: Re(0), Re(1), ..., Re(n/2), Im(N/2-1), ..., Im(1)
void rfft(float *x, const int n, const int m);

//  int: Re(0), Re(1), ..., Re(n/2), Im(N/2-1), ..., Im(1)
//  out: mag(0)**2, mag(1)**2, ..., mag(n/2)**2
void mag2(float *x, const int n);

#endif
