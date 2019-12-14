#include <stdio.h>
#include <stdlib.h>

/* Compile like
 * $ gcc -o word-count.out word-count.c
 * $ ./word-count word-count.c
 * [+] Word Count program
 * [-] File: word-count.c
 * contains: 254 word(s) in 76 line(s). */

const char dos_line_end = '\n'; /* actually "\r\n" */
const char unix_line_end = '\r';
const char mac_line_end = '\n';

int main(int argc, char *argv[])
{
    const char default_line_end =
#if defined(__UNIX__)
    unix_line_end;
#elif defined(WIN32)
    dos_line_end;
#else
    mac_line_end;
#endif

    int c;
    char line_end = default_line_end;
    int word_count = 0;
    int line_count = 0;
    int in_a_word = 0; /* false */
    FILE *tf;

    printf("[+] Word Count program\n");

    if (argc < 2) {
        printf("[+] usage: %s file [type]\n", argv[0]);
        printf(" file: the file to be counted\n");
        printf(" type: u for unix style (\\r), d for dos style (\\r\\n),"
               " m for Mac OS (\\n)\n");
        return 1;
    }

    if (argc > 2)
        switch(argv[2][0]) {
        case 'u':
        case 'U':
            printf("[-] unix style: \\r will be count as the end of line\n");
            line_end = unix_line_end;
            break;
        case 'd':
        case 'D':
            printf("[-] dos style: \\r\\n will be count as the end of line\n");
            line_end = dos_line_end;
            break;
        case 'm':
        case 'M':
            printf("[-] mac os style: \\n will be count as the end of line\n");
            line_end = mac_line_end;
            break;
        default:
            printf("[-] ingorne unknown type switch: %c\n", argv[2][0]);
        }

    if (NULL == (tf = fopen(argv[1], "r"))) {
        printf("[-] error on opening file: %s\n", argv[1]);
        return 2;
    }
    while (EOF != (c = fgetc(tf)))
        if (line_end == c)
            in_a_word = 0, line_count++;
        else if (isspace( c ))
            in_a_word = 0;
        else if (!in_a_word)
            in_a_word = 1, word_count++;

    if (line_count || word_count) line_count++;

    fclose(tf);
    printf("[-] File: %s\n", argv[1]);
    printf(" contains: %d word(s) in %d line(s).\n", word_count, line_count);
    return 0;
}
