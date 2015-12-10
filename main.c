/*
 *
 */

#include<stdio.h>
#include<math.h>
#include<gsl/gsl_integration.h>

#include"recur.c"
#include"adjust.c"
#include"timer.c"
#include"gsl_integration.c"
#include"timer.h"

#define NMAX 100

int main (void)
{
    double vals1[NMAX + 1], vals2[NMAX + 1], time1a, time1b, time2a, time2b, tmin = 1., tmax = 2.;     
    int nmin = 0, nmax = NMAX, count1 = 1000, count2 = 800;

    integral_recur (nmin, nmax, vals1); // Recursion formula stores I(0) to I(100) in the array vals1
    integral_gen (nmin, nmax, vals2);   // Gsl_integration algorithm stores I(0) to I(100) in the array vals2

    printf
        ("    n       Recursion        Gsl_Integrator        Absolute Error*10^9\n");
    int x;

    for (x = 0; x < 101; x++)
    {
        printf("   %6d     %15.15f     %15.15f      %15.15f \n", x, vals1[x],
            vals2[x], fabs (1.e9 * (vals1[x] - vals2[x])));
    }
    
    printf
        ("\n  Reccurance formula time  \n Time per call (usec) Total time (sec)    Count\n");

    int y;

    do  
    {
        timer_start();
        for (y = 0; y < count1; y++)
        {
             integral_recur (nmin, nmax, vals1);
        }
        time1a = timer_stop (); 
        time1b = time1a / count1; 
  
        printf (" %10.2f usec     %10.6f sec    %10d\n", time1b * 1.e6, time1a, count1);
        count1 = adjust_rep_count (count1, time1a, tmin, tmax);
    }
    while ((time1a > tmax) || (time1a < tmin)); 

    printf ("Time per recur function call = %f usec \n", time1b * 1.e6);

    printf
         ("\n  Gsl_Integration time  \n Time per call (usec) Total time (sec)    Count\n");
     
    do
    {
        timer_start();
        for (y = 0; y < count2; y++)
        {
             integral_gen (nmin, nmax, vals2);   
        }
        time2a = timer_stop (); 
        time2b = time2a / count2;
      
        printf (" %10.2f usec     %10.6f sec    %10d\n", time2b * 1.e6, time2a, count2);
        count2 = adjust_rep_count (count2, time2a, tmin, tmax); 
    }
    while ((time2a > tmax) || (time2a < tmin));

    printf ("Time per GSL function call = %f usec \n", time2b * 1.e6);

    printf ("Ratio  Tgsl / Trecur = %f\n", time2b / time1b);   

    return 0;
}







                          
