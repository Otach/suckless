#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <stdlib.h>

#include "../util.h"

const char *
get_volume(void)
{
    FILE *fp;
    char volume_level[4];
    memset(volume_level, '\0', sizeof(volume_level));
    
    fp = popen("pamixer --get-volume-human", "r"); 
    if (fp == NULL) {
           printf("Failed to run command\n"); 
           exit(1);
    }

    fgets(volume_level, sizeof(volume_level), fp);
    pclose(fp);

    return bprintf("%d", atoi(volume_level));
}

