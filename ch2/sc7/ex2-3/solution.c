#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define MAXLEN 1023
#define BUFFER_SIZE 3
#define HEX_DIGITS "0123456789ABCDEF"

void clear_buffer(char buffer[]);
void clear_n_buffer(char buffer[], int num_to_clear);
int first_null_index(char buffer[]);
void push_buffer(char buffer[], char c);
int is_hex_buffer(char buffer[]);
void process_hex_buffer(char buffer[]);
void read_hex_digs(char hex_str[], int index, char buffer[]);
long htoi(char s[]);
int dig_val(char);

int main() {

    char buffer[BUFFER_SIZE], c;
    clear_buffer(buffer);

    while ((c=getchar()) != EOF) {
        push_buffer(buffer, c);
        if (is_hex_buffer(buffer)) {
            process_hex_buffer(buffer);
        }
    }
    
    if (is_hex_buffer(buffer)) {
        process_hex_buffer(buffer);
    }

}

void clear_buffer(char buffer[]) {
    for (int i=0; i < BUFFER_SIZE; ++i) {
        buffer[i] = '\0';
    }
}

void clear_n_buffer(char buffer[], int num_to_clear) {
    for (int i = 0; i < num_to_clear; ++i) {
        push_buffer(buffer, '\0');
    }
}

int first_null_index(char buffer[]) {\
    for (int i=0; i<BUFFER_SIZE; ++i) {
        if (buffer[i] == '\0') return i;
    }
    return -1;
}

void push_buffer(char buffer[], char c) {
    int n_index = first_null_index(buffer);
    if (n_index >= 0) {
        buffer[n_index] = c;
    } else {
        for (int i=0; i<BUFFER_SIZE-1; ++i) {
            buffer[i] = buffer[i+1];
        }
        buffer[BUFFER_SIZE-1] = c;
    }
}

int is_hex_buffer(char buffer[]) {
    return isxdigit(buffer[0])
        || (buffer[0] == '-' && isxdigit(buffer[1]));
}

void process_hex_buffer(char buffer[]) {
    char hex_str[MAXLEN];
    hex_str[0] = buffer[0];
    if (buffer[0] == '-') {
        hex_str[1] = buffer[1];
        if (isxdigit(buffer[2])
            || (buffer[1] == '0' && tolower(buffer[2]) == 'x')) {
            hex_str[2] = buffer[2];
            read_hex_digs(hex_str, 3, buffer);
        } else {
            hex_str[2] = '\0';
            clear_n_buffer(buffer, 2);
        }
    } else if (buffer[0] == '0' && tolower(buffer[1]) == 'x') {
        hex_str[1] = buffer[1];
        if (isxdigit(buffer[2])) {
            hex_str[2] = buffer[2];
            read_hex_digs(hex_str, 3, buffer);
        } else {
            hex_str[2] = '\0';
            clear_n_buffer(buffer, 1);
        }
    } else if (isxdigit(buffer[1])) {
        hex_str[1] = buffer[1];
        if (isxdigit(buffer[2])) {
            hex_str[2] = buffer[2];
            read_hex_digs(hex_str, 3, buffer);
        } else {
            hex_str[2] = '\0';
            clear_n_buffer(buffer, 2);
        }
    } else if (buffer[1] == '\0') {
        read_hex_digs(hex_str, 1, buffer);
    } else {
        hex_str[1] = '\0';
        clear_n_buffer(buffer, 1);
    }
    if (tolower(hex_str[strlen(hex_str)-1]) != 'x') {
        printf("Hex: %s\n", hex_str);
        printf("Dec: %ld\n\n", htoi(hex_str));
    }
}

void read_hex_digs(char hex_str[], int index, char buffer[]) {
    int c;
    while (index < MAXLEN - 1 && isxdigit(c=getchar())) {
        hex_str[index] = c;
        ++index;
    }
    hex_str[index] = '\0';
    clear_buffer(buffer);
    push_buffer(buffer, c);
}

long htoi(char s[]) {

    long s_len = strlen(s);
    long d_factor = 1;
    long result = 0;

    for (int i=0; i<s_len; ++i) {
        char c_dig = s[s_len-1-i];
        if (isxdigit(c_dig)) {
            result += d_factor * dig_val(toupper(c_dig));
        } else {
            break;
        }
        d_factor *= 16;
    }
    if (s[0] == '-') result *= -1;
    return result;
}

int dig_val(char c) {
    int i = 0;
    while (HEX_DIGITS[i] != c) {
        i += 1;
    }
    return i;
}
