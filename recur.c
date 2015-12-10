/*
 *Recurrnce Relation Algorithm
 */

#include<stdio.h>
#include<math.h>

void integral_recur(int nmin, int nmax, double vals[]);
void integral_recur(int nmin, int nmax, double vals[])
{
    vals[100] = 0.00367843028136748866811; // Initial Condidtion evaluated using an integrator //

    int i;

    for (i = nmax - 1; i >= nmin; i--) 
    {
        vals[i] = vals[i + 1] / (i + 1) + 1 / (M_E * (i + 1)); // New recursion formula // 
    }
}


