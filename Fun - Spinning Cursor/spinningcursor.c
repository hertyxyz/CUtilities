#include <stdio.h>
#include <unistd.h>
#include <string.h>

void advanceCursorLine()
{
    static int stage = 0;
    char stages[4] = {'|','/','-','\\'};
    printf("%c\b", stages[stage]);
    fflush(stdout);
    stage = (stage + 1) % 4;
}

void advanceCursorDotsA()
{
    static int stage = 0;
    char* stages[10] = {"⠋","⠙","⠹","⠸","⠼","⠴","⠦","⠧","⠇","⠏"};
    printf("%s\b\b", stages[stage]);
    fflush(stdout);
    stage = (stage + 1) % 10;
}

void advanceCursorExpand()
{
    static int stage = 0;
    char* stages[6] = {"⠂","-","–","—","–","-"};
    printf("%s\b\b", stages[stage]);
    fflush(stdout);
    stage = (stage + 1) % 6;
}

void advanceCursorFlip()
{
    static int stage = 0;
    char* stages[12] = {"_","_","_","-","`","`","'","´","-","_","_","_"};
    printf("%s\b\b", stages[stage]);
    fflush(stdout);
    stage = (stage + 1) % 12;
}

void advanceCursorGrowV()
{
    static int stage = 0;
    char* stages[10] = {"▁","▃","▄","▅","▆","▇","▆","▅","▄","▃"};
    printf("%s\b\b", stages[stage]);
    fflush(stdout);
    stage = (stage + 1) % 10;
}

void advanceCursorGrowH()
{
    static int stage = 0;
    char* stages[12] = {"▏","▎","▍","▌","▋","▊","▉","▊","▋","▌","▍","▎"};
    printf("%s\b\b", stages[stage]);
    fflush(stdout);
    stage = (stage + 1) % 12;
}

void advanceCursorNoise()
{
    static int stage = 0;
    char* stages[3] = {"▓","▒","░"};
    printf("%s\b\b", stages[stage]);
    fflush(stdout);
    stage = (stage + 1) % 3;
}

void advanceCursorBounce()
{
    static int stage = 0;
    char* stages[4] = {"⠁","⠂","⠄","⠂"};
    printf("%s\b\b", stages[stage]);
    fflush(stdout);
    stage = (stage + 1) % 4;
}

void advanceCursorArc()
{
    static int stage = 0;
    char* stages[6] = {"◜","◠","◝","◞","◡","◟"};
    printf("%s\b\b", stages[stage]);
    fflush(stdout);
    stage = (stage + 1) % 6;
}

void advanceCursorClock()
{
    static int stage = 0;
    char* stages[12] = {"🕛","🕐","🕑","🕒","🕓","🕔","🕕","🕖","🕗","🕘","🕙","🕚"};
    printf("%s\b\b", stages[stage]);
    fflush(stdout);
    stage = (stage + 1) % 12;
}

void advanceCursorMoon()
{
    static int stage = 0;
    char* stages[8] = {"🌑","🌒","🌓","🌔","🌕","🌖","🌗","🌘"};
    printf("%s\b\b", stages[stage]);
    fflush(stdout);
    stage = (stage + 1) % 8;
}

void advanceCursorNade()
{
    static int stage = 0;
    char* stages[14] = {"،   ","′   "," ´ "," ‾ ","  ⸌","  ⸊","  |","  ⁎","  ⁕"," ෴ ","  ⁓","   ","   ","   "};
    printf("%s\b\b\b\b", stages[stage]);
    fflush(stdout);
    stage = (stage + 1) % 14;
}

void advanceCursorPong()
{
    static int stage = 0;
    char* stages[30] = {"▐⠂       ▌",
            			"▐⠈       ▌",
            			"▐ ⠂      ▌",
            			"▐ ⠠      ▌",
            			"▐  ⡀     ▌",
            			"▐  ⠠     ▌",
            			"▐   ⠂    ▌",
            			"▐   ⠈    ▌",
            			"▐    ⠂   ▌",
            			"▐    ⠠   ▌",
            			"▐     ⡀  ▌",
            			"▐     ⠠  ▌",
            			"▐      ⠂ ▌",
            			"▐      ⠈ ▌",
            			"▐       ⠂▌",
            			"▐       ⠠▌",
            			"▐       ⡀▌",
            			"▐      ⠠ ▌",
            			"▐      ⠂ ▌",
            			"▐     ⠈  ▌",
            			"▐     ⠂  ▌",
            			"▐    ⠠   ▌",
            			"▐    ⡀   ▌",
            			"▐   ⠠    ▌",
            			"▐   ⠂    ▌",
            			"▐  ⠈     ▌",
            			"▐  ⠂     ▌",
            			"▐ ⠠      ▌",
            			"▐ ⡀      ▌",
            			"▐⠠       ▌"};
    printf("%s\b\b\b\b\b\b\b\b\b\b", stages[stage]);
    fflush(stdout);
    stage = (stage + 1) % 30;
}

void advanceCursorBounceBall()
{
    static int stage = 0;
    char* stages[10] = {"( ●    )","(  ●   )","(   ●  )","(    ● )","(     ●)","(    ● )","(   ●  )","(  ●   )","( ●    )","(●     )"};
    printf("%s\b\b\b\b\b\b\b\b", stages[stage]);
    fflush(stdout);
    stage = (stage + 1) % 10;
}

void advanceCursorBounceBar()
{
    static int stage = 0;
    char* stages[15] = {"[    ]",
            			"[=   ]",
            			"[==  ]",
            			"[=== ]",
            			"[ ===]",
            			"[  ==]",
            			"[   =]",
            			"[    ]",
            			"[   =]",
            			"[  ==]",
            			"[ ===]",
            			"[====]",
            			"[=== ]",
            			"[==  ]",
            			"[=   ]"};
    printf("%s\b\b\b\b\b\b", stages[stage]);
    fflush(stdout);
    stage = (stage + 1) % 15;
}

void advanceCursorSlide()
{
    static int stage = 0;
    char* stages[5] = {"[==   ]","[ ==  ]","[  == ]","[   ==]","[=   =]"};
    printf("%s\b\b\b\b\b\b\b", stages[stage]);
    fflush(stdout);
    stage = (stage + 1) % 5;
}

void advanceCursorShark()
{
    static int stage = 0;
    char* stages[26] = {"▐|\\____________▌",
            		   "▐_|\\___________▌",
            		   "▐__|\\__________▌",
            		   "▐___|\\_________▌",
            		   "▐____|\\________▌",
            		   "▐_____|\\_______▌",
            		   "▐______|\\______▌",
            		   "▐_______|\\_____▌",
            		   "▐________|\\____▌",
            		   "▐_________|\\___▌",
            		   "▐__________|\\__▌",
            		   "▐___________|\\_▌",
            		   "▐____________|\\▌",
            		   "▐____________/|▌",
            		   "▐___________/|_▌",
            		   "▐__________/|__▌",
            		   "▐_________/|___▌",
            		   "▐________/|____▌",
            		   "▐_______/|_____▌",
            		   "▐______/|______▌",
            		   "▐_____/|_______▌",
            		   "▐____/|________▌",
            		   "▐___/|_________▌",
            		   "▐__/|__________▌",
            		   "▐_/|___________▌",
            		   "▐/|____________▌"};
    printf("%s\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b", stages[stage]);
    fflush(stdout);
    stage = (stage + 1) % 26;
}

int main(int argc, char **argv) {
    for (int i = 0; i < 30; i++)
    {
        advanceCursorShark();
        usleep(100000);
    }
    printf("\n");
    return 0;
}
