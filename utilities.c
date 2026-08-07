//
// Created by intel one on 7/9/2026.
//

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <conio.h>
#include "data.h"
#include "utilities.h"

#include <time.h>

#define COLOR_RED "\033[1;31m"
#define COLOR_GREEN "\033[1;32m"
#define COLOR_YELLOW "\033[1;33m"
#define COLOR_CYAN "\033[1;36m"
#define COLOR_RESET "\033[0m"

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

int check_prerequisites(Student student, Course course) {
    for (int i = 0; i < course.prereq_count; i++) {
        int prereq_passed = 0;
        for (int j = 0; j < student.enrollment_count; j++) {
            if (strcmp(student.enrollments[j].course_id, course.prerequisites[i]) == 0 &&
                student.enrollments[j].grade >= 10.0) {
                prereq_passed = 1;
                break;
                }
        }
        if (!prereq_passed) {
            return 0;
        }
    }
    return 1;
}

float calculate_gpa(Student student, char *target_semester, Course courses[], int course_count) {
    float total_weight = 0.00;
    int total_units = 0;
    for (int i = 0; i < student.enrollment_count; i++) {
        if (target_semester != NULL && strcmp(student.enrollments[i].semester, target_semester) != 0) {
            continue;
        }
        if (student.enrollments[i].grade < 0) {
            continue;
        }
        int course_index = -1;
        for (int j = 0; j < course_count; j++) {
            if (strcmp(courses[j].course_id, student.enrollments[i].course_id) == 0) {
                course_index = j;
                break;
            }
        }
        if (course_index == -1) {
            continue;
        }
        total_weight += student.enrollments[i].grade * courses[course_index].units;
        total_units += courses[course_index].units;
    }
    if (total_weight == 0) {
        return 0.00;
    }
    return total_weight / (float) total_units;
}

#ifdef _WIN32
#include <windows.h>

void enable_ansi_colors() {
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD dwMode = 0;
    GetConsoleMode(hOut, &dwMode);
    dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
    SetConsoleMode(hOut, dwMode);
}
#else
void enable_ansi_colors()
{

}
#endif

void print_error(const char *error_message) {
    printf("%sError: %s%s", COLOR_RED, error_message ,COLOR_RESET);
}

void print_success(const char *success_message) {
    printf("%s%s%s", COLOR_GREEN, success_message, COLOR_RESET);
}

void print_warning(const char* warning_message) {
    printf("%sWarning: %s%s", COLOR_YELLOW, warning_message, COLOR_RESET);
}

const char *get_greeting() {
    time_t now = time(NULL);
    struct tm *local_time = localtime(&now);
    int hour = local_time->tm_hour;

    if (hour < 12) {
        return "Good morning";
    }
    else if (hour < 17) {
        return "Good afternoon";
    }
    else {
        return "Good evening";
    }
}

int confirm_logout() {
    printf("%sAre you sure you want to log out? [y/n] %s", COLOR_YELLOW, COLOR_RESET);
    char answer;
    scanf(" %c", &answer);
    return (answer == 'y' || answer == 'Y');
}

void print_admin_stats(int student_count, int faculty_count, int offering_count) {
    printf("%sStudents: %d | Faculty members: %d | Total offerings: %d%s\n",
           COLOR_CYAN, student_count, faculty_count, offering_count, COLOR_RESET);
}