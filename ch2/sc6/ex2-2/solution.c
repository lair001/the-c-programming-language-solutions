#include <stdio.h>

/* Max chars in line excluding null char */
#define MAXLINE 1023

void get_line(char s[], int lim);

int main()
{
    char s[MAXLINE + 1];
    get_line(s, MAXLINE + 1);
    printf("\n%s\n", s);

}

void get_line(char s[], int lim)
{
    int c, i;

    /* This for loop is equivalent to that in the prompt */
    for (i=0; i<lim-1; ++i) {
        if ((c=getchar()) == EOF) break;
        if (c == '\n') break;
        s[i] = c;
    }
    s[i] = '\n';
    s[i + 1] = '\0';
}
