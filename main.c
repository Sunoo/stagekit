#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include "stagekit.h"

int main()
{
    int i;
    unsigned int color;
    printf("Initializing StageKit...\n");
    char* errorStr = "";
    char* foundfile = "";
    int error = sk_init(NULL, &foundfile, &errorStr);
    if (error != 0) {
        printf("%s\n", errorStr);
        exit(error);
    }
    printf("Found StageKit on %s\n", foundfile);
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
        {
            return 0;
        }

        switch (i)
        {
            case 0:
                error = sk_alloff(&errorStr);
                printf("Turned off everything\n");
                break;
            case 1:
                error = sk_setstrobe(0, &errorStr);
                printf("Turned off strobe\n");
                break;
            case 2:
                error = sk_setstrobe(1, &errorStr);
                printf("Started a slow strobe\n");
                break;
            case 3:
                error = sk_setstrobe(2, &errorStr);
                printf("Started a medium strobe\n");
                break;
            case 4:
                error = sk_setstrobe(3, &errorStr);
                printf("Started a fast strobe\n");
                break;
            case 5:
                error = sk_setstrobe(4, &errorStr);
                printf("Started the fastest strobe\n");
                break;
            case 6:
                printf("Enter a value (in hex) for the red lights:");
                scanf("%2x", &color);
                error = sk_setred(color, &errorStr);
                printf("Sent %2x to the red array\n", color);
                break;
            case 7:
                printf("Enter a value (in hex) for the yellow lights:");
                scanf("%2x", &color);
                error = sk_setyellow(color, &errorStr);
                printf("Sent %2x to the yellow array\n", color);
                break;
            case 8:
                printf("Enter a value (in hex) for the green lights:");
                scanf("%2x", &color);
                error = sk_setgreen(color, &errorStr);
                printf("Sent %2hx to the green array\n", color);
                break;
            case 9:
                printf("Enter a value (in hex) for the blue lights:");
                scanf("%2x", &color);
                error = sk_setblue(color, &errorStr);
                printf("Sent %2x to the blue array\n", color);
                break;
            case 10:
                error = sk_setfog(true, &errorStr);
                printf("Fog engaged\n");
                break;
            case 11:
                error = sk_setfog(false, &errorStr);
                printf("Fog disengaged\n");
                break;
            case 12:
                error = 0;
                usleep(60000);
                break;
        }
        if (error != 0) {
            printf("%s\n", errorStr);
            exit(error);
        }
    }
    return 0;
}
