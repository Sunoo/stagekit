/*
 *
 * This code is modified version of the fftest.c program
 * which Tests the force feedback driver by Johan Deneux.
 * Modifications to incorporate into Word War vi
 * by Stephen M.Cameron
 *
 * Additional modifications to create a support library for the Rock Band Stage Kit from PDP
 * by Wayne M. Galen
 *
 * Copyright 2001-2002 Johann Deneux <deneux@ifrance.com>
 * Copyright 2008 Stephen M. Cameron <smcameron@yahoo.com>
 * Copyright 2010 Wayne M. Galen <wayne.galen@gmail.com>
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

#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <dirent.h>
#include <stdexcept>
#include "stagekit.h"

#ifdef __linux__
#define HAS_LINUX_JOYSTICK_INTERFACE 1
#endif

#ifdef HAS_LINUX_JOYSTICK_INTERFACE
#include <linux/input.h>

static int event_fd;
static unsigned long features[4];
static struct ff_effect effect;
#endif

#define BITS_PER_LONG (sizeof(long) * 8)
#define OFF(x) ((x) % BITS_PER_LONG)
#define BIT(x) (1UL << OFF(x))
#define LONG(x) ((x) / BITS_PER_LONG)
#define test_bit(bit, array) ((array[LONG(bit)] >> OFF(bit)) & 1)

void send_raw_value(unsigned short left, unsigned short right)
{
#ifdef HAS_LINUX_JOYSTICK_INTERFACE
    struct input_event play;
    // download the effect
    effect.u.rumble.strong_magnitude = left;
    effect.u.rumble.weak_magnitude = right;

    if (ioctl(event_fd, EVIOCSFF, &effect) == -1)
    {
        char errorMsg[256];
        snprintf(errorMsg, 255, "failed to upload effect: %s\n", strerror(errno));
        throw std::runtime_error(errorMsg);
    }
    play.type = EV_FF;
    play.code = effect.id;
    play.value = 1;

    if (write(event_fd, (const void*)&play, sizeof(play)) == -1)
        throw std::runtime_error((char*)"write returned -1");
#endif
}

void sk_close(void)
{
#ifdef HAS_LINUX_JOYSTICK_INTERFACE
    close(event_fd);
#endif
}

char* sk_init(char* filename)
{
#ifdef HAS_LINUX_JOYSTICK_INTERFACE
    if (filename == NULL)
    {
        struct dirent* dp;
        const char* dir_path = "/dev/input";
        DIR* dir = opendir(dir_path);
        // No event interface file passed. Probing for stagekit.
        struct input_id device_info;

        while ((dp = readdir(dir)) != NULL)
        {
            if (strspn(dp->d_name, "event"))
            {
                char tryfile[256];
                strcpy(tryfile, dir_path);
                strcat(tryfile, "/");
                strcat(tryfile, dp->d_name);
                event_fd = open(tryfile, O_RDWR);
                if (!(event_fd < 0))
                {
                    ioctl(event_fd, EVIOCGID, &device_info);

                    if ((device_info.vendor == 0x0e6f) && (device_info.product == 0x0103))
                    {
                        // Stage kit found
                        filename = tryfile;
                        break;
                    }
                    else
                    {
                        close(event_fd);
                    }
                }
            }
        }
    }
    else
    {
        event_fd = open(filename, O_RDWR);
        if (event_fd < 0)
        {
            char errorMsg[256];
            snprintf(errorMsg, 255, "Can't open %s: %s", filename, strerror(errno));
            throw std::runtime_error(errorMsg);
        }
    }

    // Query device
    if (ioctl(event_fd, EVIOCGBIT(EV_FF, sizeof(unsigned long) * 4), features) == -1)
    {
        char errorMsg[256];
        snprintf(errorMsg, 255, "Query of rumble device failed: %s:%s", filename, strerror(errno));
        throw std::runtime_error(errorMsg);
    }

    // download a lights out effect
    effect.type = FF_RUMBLE;
    effect.id = -1;
    effect.direction = 0;
    effect.trigger.button = 0;
    effect.trigger.interval = 0;
    if (ioctl(event_fd, EVIOCSFF, &effect) == -1)
    {
        char errorMsg[256];
        snprintf(errorMsg, 255, "%s: failed to allocate effect: %s", filename, strerror(errno));
        throw std::runtime_error(errorMsg);
    }
    return filename;
#else
    return NULL;
#endif
}

void sk_alloff(void)
{
    send_raw_value(0, STAGEKIT_ALLOFF);
    usleep(10000);
    // sending this twice ensures the command is recieved. in testing, it would sometimes get stuck with only one off call. no clue why
    send_raw_value(0, STAGEKIT_ALLOFF);
    usleep(10000);
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

void sk_setred(unsigned short red)
{
    send_raw_value(red << 8, STAGEKIT_RED);
    usleep(10000);
}

void sk_setyellow(unsigned short yellow)
{
    send_raw_value(yellow << 8, STAGEKIT_YELLOW);
    usleep(10000);
}

void sk_setgreen(unsigned short green)
{
    send_raw_value(green << 8, STAGEKIT_GREEN);
    usleep(10000);
}

void sk_setblue(unsigned short blue)
{
    send_raw_value(blue << 8, STAGEKIT_BLUE);
    usleep(10000);
}
