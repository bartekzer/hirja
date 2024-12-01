#include <math.h>
#include <stdio.h>
#include <time.h>

#define GEPOCH (1721425.5)
#define gyEPOCH (1948439.5)

int leap(int y) {
  if (!(y % 4) && (!(y % 400) || y % 100))
    return 1;
  return 0;
}

int gregorian_julian(void) {
  int gd, gm, gy, jd;
  time_t t;
  struct tm tm;

  t = time(NULL);
  tm = *localtime(&t);
  gd = tm.tm_mday;
  gm = tm.tm_mon + 1;
  gy = tm.tm_year + 1900;

  printf("%d %d %d\n", gd, gm, gy);

  jd = GEPOCH - 1;
  jd += 365 * (gy - 1);
  jd += floor((gy - 1) / 4);
  jd += floor((gy - 1) / 100);
  jd += floor((gy - 1) / 400);
  jd += floor((367 * gm - 362) / 12);

  if (gm > 2)
    jd -= leap(gy) ? 1 : 2;

  jd += gd;

  jd = floor(jd);
  jd += 0.5;

  return jd;
}

/*
    Computes the Julian date given a Gregorian date.

    https://aa.usno.navy.mil/faq/gmD_formula
*/
int gregorianToJulian(void) {
  int gd, gm, gy, jd;
  time_t t;
  struct tm tm;

  t = time(NULL);
  tm = *localtime(&t);
  gd = tm.tm_mday;
  gm = tm.tm_mon + 1;
  gy = tm.tm_year + 1900;

  jd = gd - 32075 + 1461 * (gy + 4800 + (gm - 14) / 12) / 4 +
       367 * (gm - 2 - (gm - 14) / 12 * 12) / 12 -
       3 * ((gy + 4900 + (gm - 14) / 12) / 100) / 4;

  return jd;
}

int main(void) {
  int jd = gregorianToJulian();
  printf("gmulian Day 1: %d\n", jd);

  int jd2 = gregorian_julian();
  printf("gmulian Day 2: %d\n", jd2);
}
