#include <stdio.h>
#include <unistd.h>
#include <stdexcept>
#include "stagekit.h"

int main()
{
    int i;
    unsigned int color;
    printf("Initializing StageKit...\n");
    char* filename = sk_init(NULL);
    printf("Found StageKit on %s\n", filename);
    printf("0 - Panic\n");
    printf("1-5 - Strobe\n");
    printf("6 - Set red lights\n");
    printf("7 - Set yellow lights\n");
    printf("8 - Set green lights\n");
    printf("9 - Set blue lights\n");
    printf("10 - Fog on\n");
    printf("11 - Fog off\n");
    while (i != -1)
    {
        if (scanf("%i", &i) == EOF)
            return 0;

        switch (i)
        {
            case 0:
                sk_alloff();
                printf("Turned off everything\n");
                break;
            case 1:
                sk_setstrobe(0);
                printf("Turned off strobe\n");
                break;
            case 2:
                sk_setstrobe(1);
                printf("Started a slow strobe\n");
                break;
            case 3:
                sk_setstrobe(2);
                printf("Started a medium strobe\n");
                break;
            case 4:
                sk_setstrobe(3);
                printf("Started a fast strobe\n");
                break;
            case 5:
                sk_setstrobe(4);
                printf("Started the fastest strobe\n");
                break;
            case 6:
                printf("Enter a value (in hex) for the red lights:");
                scanf("%2x", &color);
                sk_setred(color);
                printf("Sent %2x to the red array\n", color);
                break;
            case 7:
                printf("Enter a value (in hex) for the yellow lights:");
                scanf("%2x", &color);
                sk_setyellow(color);
                printf("Sent %2x to the yellow array\n", color);
                break;
            case 8:
                printf("Enter a value (in hex) for the green lights:");
                scanf("%2x", &color);
                sk_setgreen(color);
                printf("Sent %2hx to the green array\n", color);
                break;
            case 9:
                printf("Enter a value (in hex) for the blue lights:");
                scanf("%2x", &color);
                sk_setblue(color);
                printf("Sent %2x to the blue array\n", color);
                break;
            case 10:
                sk_setfog(true);
                printf("Fog engaged\n");
                break;
            case 11:
                sk_setfog(false);
                printf("Fog disengaged\n");
                break;
            case 12:
                usleep(60000);
                break;
        }
    }
    return 0;
}
