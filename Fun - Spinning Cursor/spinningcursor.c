#include <stdio.h>
#include <unistd.h>

void advanceCursor()
{
    static int stage = 0;
    char stages[4] = {'|','/','-','\\'};
    printf("%c\b", stages[stage]);
    fflush(stdout);
    stage = (stage + 1) % 4;
}

int main(int argc, char **argv) {
    for (int i = 0; i < 100; i++)
    {
        advanceCursor();
        usleep(50000);
    }
    printf("\n");
    return 0;
}
