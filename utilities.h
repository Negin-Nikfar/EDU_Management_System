//
// Created by intel one on 7/9/2026.
//

#ifndef EDU_PROJECT_UTILITIES_H
#define EDU_PROJECT_UTILITIES_H
#include "data.h"

void extract_string_value(char *line, const char *key, char *output);
float extract_number_value(char *line, const char *key);
int extract_string_array(char *line, char output[][20]);

void read_password(char *buffer);

int check_prerequisites(Student student, Course course);

float calculate_gpa(Student student, char *target_semester, Course courses[], int course_count);

#endif //EDU_PROJECT_UTILITIES_H