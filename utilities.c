//
// Created by intel one on 7/9/2026.
//

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
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