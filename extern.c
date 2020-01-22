#include "stagekit.h"

void sk_alloff(void)
{
  send_raw_value(0, STAGEKIT_ALLOFF);
  usleep(10000);
  //sending this twice ensures the command is recieved. in testing, it would sometimes get stuck with only one off call. no clue why
  send_raw_value(0,STAGEKIT_ALLOFF);
}

void sk_nostrobe(void)
{
  send_raw_value(0, STAGEKIT_NO_STROBE);
  usleep(10000);
}

void sk_slowstrobe(void)
{
  send_raw_value(0, STAGEKIT_SLOW_STROBE);
  usleep(10000);
}

void sk_medstrobe(void)
{
  send_raw_value(0, STAGEKIT_MEDIUM_STROBE);
  usleep(10000);
}

void sk_faststrobe(void)
{
  send_raw_value(0, STAGEKIT_FAST_STROBE);
  usleep(10000);
}

void sk_fasteststrobe(void)
{
  send_raw_value(0, STAGEKIT_FAST_STROBE);
  usleep(10000);
}

void sk_fogon(void)
{
  send_raw_value(0, STAGEKIT_FOG_ON);
  usleep(10000);
}

void sk_fogoff(void)
{
  send_raw_value(0, STAGEKIT_FOG_OFF);
  usleep(10000);
}

void sk_setred(unsigned short left)
{
  send_raw_value(left<<8, STAGEKIT_RED);
  usleep(10000);
}

void sk_setyellow(unsigned short left)
{
  send_raw_value(left<<8, STAGEKIT_YELLOW);
  usleep(10000);
}

void sk_setgreen(unsigned short left)
{
  send_raw_value(left<<8, STAGEKIT_GREEN);
  usleep(10000);
}

void sk_setblue(unsigned short left)
{
  send_raw_value(left<<8, STAGEKIT_BLUE);
  usleep(10000);
}

void sk_setleds(unsigned short red, unsigned short yellow, unsigned short green, unsigned short blue)
{
  send_raw_value(red<<8, STAGEKIT_RED);
  usleep(10000);
  send_raw_value(yellow<<8, STAGEKIT_YELLOW);
  usleep(10000);
  send_raw_value(green<<8, STAGEKIT_GREEN);
  usleep(10000);
  send_raw_value(blue<<8, STAGEKIT_BLUE);
  usleep(10000);
}
