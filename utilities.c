//
// Created by intel one on 7/9/2026.
//

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <conio.h>
#include "utilities.h"

void extract_string_value(char *line, const char *key, char *output) {
    char search_key[100];
    sprintf(search_key, "\"%s\"", key);
    char *found = strstr(line, search_key);
    if (found == NULL) {
        return;
    }
    char *colon = strchr(found, ':');
    char *value_start = strchr(colon, '"');
    value_start += 1;
    char *value_end = strchr(value_start, '"');
    int len = value_end - value_start;
    strncpy(output, value_start, len);
    output[len] = '\0';
}
float extract_number_value(char *line, const char *key) {
    char search_key[100];
    sprintf(search_key, "\"%s\"", key);
    char *found = strstr(line, search_key);
    if (found == NULL) {
        return 0;
    }
    char *colon = strchr(found, ':');
    float value = atof(colon + 1);
    return value;
}

int extract_string_array(char *line, char output[][20]) {
    int count = 0;
    char *ptr = strchr(line, '[');
    if (ptr == NULL) {
        return 0;
    }
    while (ptr != NULL) {
        char *quote_start = strchr(ptr, '"');
        if (quote_start == NULL) {
            break;
        }
        quote_start++;
        char *quote_end = strchr(quote_start, '"');
        if (quote_end == NULL) {
            break;
        }
        int len = quote_end - quote_start;
        strncpy(output[count], quote_start, len);
        output[count][len] = '\0';
        count++;
        ptr = quote_end + 1;
        if (strchr(ptr, ']') != NULL && strchr(ptr, ']') < strchr(ptr, '"')) {
            break;
        }
    }
    return count;
}

void read_password(char *buffer) {
    int i = 0;
    char ch;
    while (1) {
        ch = getch();
        if (ch == 13) {
            break;
        }
        if (ch == 8) {
            if (i > 0) {
                i--;
                printf("\b \b");
            }
        }
        else {
            buffer[i] = ch;
            i++;
            printf("*");
        }
    }
    buffer[i] = '\0';
}