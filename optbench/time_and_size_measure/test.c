#include <stdio.h>
#include <math.h>
#include <float.h>

int main(void)
{
  double x = 0.97;

  double PI = 3.141592653589793;
  double sum = 0;
  double elem = 1;
  unsigned long long fact;
  int banned_number = 3;

  for (unsigned long long i = 1; fabs(elem) >= DBL_EPSILON; i++)
  {
    if (i == banned_number)
    {
      banned_number+=6;
      continue;
    }

    fact = 1;

    for (unsigned long long j = i / 7; j > i/13; j--)
      fact *= j;  

    elem = (pow(-1, i) * pow(x, 2 * i + 1) * cos(i * PI / 6) / fact); // 3 9 15 21...

    //printf("%f\n", pow(-1, i) * pow(x, 2 * i + 1) * cos(i * PI / 6) / fact);
    printf("%.30f %.30f %.30f\n", elem, DBL_EPSILON, cos(i * PI / 6));
    sum += elem;
  }

  printf("answer : %.15Lf\n", sum);



  return 0;
}
