#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>

// A-Z ASCII Art (5x5 blocks)
const char *alpha[26][5] = {
    {" AAA ", "A   A", "AAAAA", "A   A", "A   A"}, // A
    {"BBBB ", "B   B", "BBBB ", "B   B", "BBBB "}, // B
    {" CCCC", "C    ", "C    ", "C    ", " CCCC"}, // C
    {"DDDD ", "D   D", "D   D", "D   D", "DDDD "}, // D
    {"EEEEE", "E    ", "EEEE ", "E    ", "EEEEE"}, // E
    {"FFFFF", "F    ", "FFFF ", "F    ", "F    "}, // F
    {" GGGG", "G    ", "G  GG", "G   G", " GGGG"}, // G
    {"H   H", "H   H", "HHHHH", "H   H", "H   H"}, // H
    {" III ", "  I  ", "  I  ", "  I  ", " III "}, // I
    {" JJJJ", "    J", "    J", "J   J", " JJJ "}, // J
    {"K   K", "K  K ", "KKK  ", "K  K ", "K   K"}, // K
    {"L    ", "L    ", "L    ", "L    ", "LLLLL"}, // L
    {"M   M", "MM MM", "M M M", "M   M", "M   M"}, // M
    {"N   N", "NN  N", "N N N", "N  NN", "N   N"}, // N
    {" OOO ", "O   O", "O   O", "O   O", " OOO "}, // O
    {"PPPP ", "P   P", "PPPP ", "P    ", "P    "}, // P
    {" QQQ ", "Q   Q", "Q   Q", "Q  QQ", " QQQQ"}, // Q
    {"RRRR ", "R   R", "RRRR ", "R  R ", "R   R"}, // R
    {" SSSS", "S    ", " SSS ", "    S", "SSSS "}, // S
    {"TTTTT", "  T  ", "  T  ", "  T  ", "  T  "}, // T
    {"U   U", "U   U", "U   U", "U   U", " UUU "}, // U
    {"V   V", "V   V", "V   V", " V V ", "  V  "}, // V
    {"W   W", "W   W", "W W W", "WW WW", "W   W"}, // W
    {"X   X", " X X ", "  X  ", " X X ", "X   X"}, // X
    {"Y   Y", " Y Y ", "  Y  ", "  Y  ", "  Y  "}, // Y
    {"ZZZZZ", "   Z ", "  Z  ", " Z   ", "ZZZZZ"}  // Z
};

int main() {
    char input[50];
    struct winsize w;
    srand(time(NULL));

    printf("Enter anything (Letters A-Z): ");
    if (fgets(input, sizeof(input), stdin) == NULL) return 1;
    input[strcspn(input, "\n")] = 0;

    while (1) {
        ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
        int rows = w.ws_row;
        int cols = w.ws_col;

        // Clear screen
        printf("\033[2J\033[H");

        // Vertical Center
        for (int i = 0; i < (rows / 2) - 3; i++) printf("\n");

        // Random Disco Color (ANSI 31-36)
        int color = 31 + (rand() % 6);
        printf("\033[1;%dm", color);

        // Print Big Font Row by Row
        for (int r = 0; r < 5; r++) {
            // Horizontal padding calculation
            int word_width = strlen(input) * 6; 
            for (int p = 0; p < (cols - word_width) / 2; p++) printf(" ");

            for (int i = 0; i < strlen(input); i++) {
                char c = toupper(input[i]);
                if (c >= 'A' && c <= 'Z') {
                    printf("%s ", alpha[c - 'A'][r]);
                } else {
                    printf("      "); // Space for numbers/symbols
                }
            }
            printf("\n");
        }

        printf("\033[0m"); // Reset
        fflush(stdout);
        usleep(150000);
    }
    return 0;
}