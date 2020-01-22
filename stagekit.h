/*
 * This code (stagekit.h & stagekit.c) is intended to allow control over
 * the Rock Band Stage Kit made by PDP. I intended this header to be
 * fairly self-documenting to assist anyone that may wish to impliment
 * support for the device in another API/OS. To get started, #include this
 * file in your program, call sk_init(filename), where filename is the event
 * file matching the stagekit (such as /dev/input/event5), then call the
 * various sk_* macros such as sk_faststrobe(); or sk_setred(0xFF);
 */

/*
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
 *
 * You can contact the author by email at this address:
 * Wayne M. Galen <wayne.galen@gmail.com>
 */

#ifndef STAGEKIT_H_INCLUDED
#define STAGEKIT_H_INCLUDED
#include <unistd.h>

#define STAGEKIT_ALLOFF 0xFFFF
#define STAGEKIT_NO_STROBE 0x700
#define STAGEKIT_SLOW_STROBE 0x300
#define STAGEKIT_MEDIUM_STROBE 0x400
#define STAGEKIT_FAST_STROBE 0x500
#define STAGEKIT_FASTEST_STROBE 0x600
#define STAGEKIT_FOG_ON 0x100
#define STAGEKIT_FOG_OFF 0x200
#define STAGEKIT_RED 0x8000
#define STAGEKIT_YELLOW 0x6000
#define STAGEKIT_GREEN 0x4000
#define STAGEKIT_BLUE 0x2000

extern int sk_init(char* filename);
extern int send_raw_value(unsigned short left, unsigned short right);
extern void sk_close(void);

extern void sk_alloff(void);
extern void sk_nostrobe(void);
extern void sk_slowstrobe(void);
extern void sk_medstrobe(void);
extern void sk_faststrobe(void);
extern void sk_fasteststrobe(void);
extern void sk_fogon(void);
extern void sk_fogoff(void);

extern void sk_setred(unsigned short left);
extern void sk_setyellow(unsigned short left);
extern void sk_setgreen(unsigned short left);
extern void sk_setblue(unsigned short left);

extern void sk_setleds(unsigned short red, unsigned short yellow, unsigned short green, unsigned short blue);

#endif // STAGEKIT_H_INCLUDED
