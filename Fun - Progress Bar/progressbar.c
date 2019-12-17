#include <stdio.h>
#include <stddef.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

void printBar(size_t count, size_t max)
{
    const char pfix[] = "Progress: [";
    const char sfix[] = "]";
    const size_t szPfix = sizeof(pfix) - 1;
    const size_t szSfix = sizeof(sfix) - 1;
    char *buffer = calloc(max + szPfix + szSfix + 1, 1);
    size_t i = 0;
    strcpy(buffer, pfix);
    for (; i < max; i++)
    {
        buffer[szPfix + i] = i < count ? '#' : ' ';
    }
    strcpy(&buffer[szPfix + i], sfix);
    printf("\r\b%c[2K\r%s", 27, buffer);
    fflush(stdout);
    free(buffer);
}

int main(int argc, char **argv)
{
    size_t seconds = 1;
    size_t maxwait = 80;
    printf("%s\n", "");
    printBar(0, maxwait);
    for (; seconds <= maxwait; seconds++)
    {
        usleep(100000);
        printBar(seconds, maxwait);
    }
}
