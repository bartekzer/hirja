#include <math.h>
#include <stdio.h>
#include <time.h>

const double GEPOCH = 1721425.5;
const double IEPOCH = 1948439.5;

int leap(int year);
int hirji_julian(int year, int month, int day);
double gregorian_julian(int year, int month, int day);
void gregorian_date(int *year, int *month, int *day);

int main(void) {
  const char *islamic_months[12] = {
#ifndef __ASCII_MONTHS
      "Ṣafar",
      "Rabīʿ al-Awwal",
      "Rabīʿ ath-Thānī",
      "Jumādā al-ʾŪlā",
      "Jumādā ath-Thāniyah",
      "Rajab",
      "Shaʿbān",
      "Ramaḍān",
      "Shawwāl",
      "Dhū al-Qaʿdah",
      "Dhū al-Ḥijjah"
#else
      "Safar",     "Rabi' I",       "Rabi' II",     "Jumada I",
      "Jumada II", "Rajab",         "Sha'ban",      "Ramadan",
      "Shawwal",   "Dhu al-Qa'dah", "Dhu al-Hijjah"
#endif
  };

  int gy, gm, gd;
  gregorian_date(&gy, &gm, &gd);

  double jd = gregorian_julian(gy, gm, gd);

  int iy = (int)(((jd - IEPOCH) * 30 + 10646) / 10631);

  int im = (int)(((jd - (hirji_julian(iy, 1, 1) + 29)) / 29.5) + 1);
  if (im > 12)
    im = 12;

  int id = (int)(jd - hirji_julian(iy, im, 1) + 1);

  printf("%d %s %d\n", id - 29, islamic_months[im - 1], iy);

  return 0;
}

int leap(year)
int year;
{ return (year % 4 == 0 && (year % 100 != 0 || year % 400 == 0)); }

int hirji_julian(year, month, day)
int year, month, day;
{
  return day + (int)ceil(29.5 * (month - 1)) + 354 * year +
         floor((3 + 11 * year) / 30) + IEPOCH - 355;
}

double gregorian_julian(year, month, day)
int year, month, day;
{
  double jd = GEPOCH - 1 + 365 * (year - 1) + floor((year - 1) / 4) -
              floor((year - 1) / 100) + floor((year - 1) / 400) +
              floor((367 * month - 362) / 12);
  if (month > 2)
    jd -= leap(year) ? 1 : 2;
  return floor(jd + day) + 0.5;
}

void gregorian_date(year, month, day) int *year, *month, *day;
{
  time_t t = time(NULL);
  struct tm tm = *localtime(&t);
  *year = tm.tm_year + 1900;
  *month = tm.tm_mon + 1;
  *day = tm.tm_mday;
}