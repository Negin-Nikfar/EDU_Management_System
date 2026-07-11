//
// Created by intel one on 7/9/2026.
//

#include <stdio.h>
#include <string.h>
#include "data.h"
#include "utilities.h"

void save_students(Student students[], int count) {
    FILE *f = fopen("../data/students.json", "w");
    if (f == NULL) {
        printf("Error opening data/students.json\n");
        return;
    }
    fprintf(f, "[\n");
    for (int i = 0; i < count; i++) {
        fprintf(f, " {\n");
        fprintf(f, " \"first_name\": \"%s\", \n", students[i].first_name);
        fprintf(f, " \"last_name\": \"%s\", \n", students[i].last_name);
        fprintf(f, " \"student_id\": \"%s\", \n", students[i].student_id);
        fprintf(f, " \"entrance_year\": %d, \n", students[i].entrance_year);
        fprintf(f, " \"national_code\": \"%s\", \n", students[i].national_code);
        fprintf(f, " \"field\": \"%s\", \n", students[i].field);
        fprintf(f, " \"department\": \"%s\", \n", students[i].department);
        fprintf(f, " \"section\": \"%s\", \n", students[i].section);
        fprintf(f, " \"mentor\": \"%s\", \n", students[i].mentor);
        fprintf(f, " \"password\": \"%s\", \n", students[i].password);
        fprintf(f ," \"birthplace\": \"%s\", \n", students[i].security.birthplace);
        fprintf(f, " \"first_school\": \"%s\", \n", students[i].security.first_school);
        fprintf(f, " \"first_book\": \"%s\", \n", students[i].security.first_book);
        fprintf(f, " \"bike_color\": \"%s\", \n", students[i].security.bike_color);
        fprintf(f, " \"enrollments\": [\n");
        for (int j = 0; j < students[i].enrollment_count; j++) {
            fprintf(f, " {\"semester\": \"%s\", \"course_id\": \"%s\", \"grade\": %.2f}",
                students[i].enrollments[j].semester,
                students[i].enrollments[j].course_id,
                students[i].enrollments[j].grade);
            if (j < students[i].enrollment_count - 1) {
                fprintf(f, ",\n");
            }
            else {
                fprintf(f, "\n");
            }
            fprintf(f, " ]\n");
        }
        fprintf(f, " }");
        if (i < count - 1) {
            fprintf(f, ",\n");
        }
        else {
            fprintf(f, "\n");
        }
    }
    fprintf(f, "]\n");
    fclose(f);
}

int load_students(Student students[], int max_count) {
    FILE *f = fopen("../data/students.json", "r");
    if (f == NULL) {
        printf("Error opening data/students.json\n");
    }
    int count = -1;
    char line[300];
    while (fgets(line, sizeof(line), f) != NULL) {
        if (strstr(line, "\"first_name\"") != NULL) {
            count++;
            students[count].enrollment_count = 0;
            extract_string_value(line, "first_name", students[count].first_name);
        }
        else if (strstr(line, "\"last_name\"") != NULL) {
            extract_string_value(line, "last_name", students[count].last_name);
        }
        else if (strstr(line, "\"student_id\"") != NULL) {
            extract_string_value(line, "student_id", students[count].student_id);
        }
        else if (strstr(line, "\"entrance_year\"") != NULL) {
            students[count].entrance_year = (int) extract_number_value(line, "entrance_year");
        }
        else if (strstr(line, "\"national_code\"") != NULL) {
            extract_string_value(line, "national_code", students[count].national_code);
        }
        else if (strstr(line, "\"field\"") != NULL) {
            extract_string_value(line, "field", students[count].field);
        }
        else if (strstr(line, "\"department\"") != NULL) {
            extract_string_value(line, "department", students[count].department);
        }
        else if (strstr(line, "\"section\"") != NULL) {
            extract_string_value(line, "section", students[count].section);
        }
        else if (strstr(line, "\"mentor\"") != NULL) {
            extract_string_value(line, "mentor", students[count].mentor);
        }
        else if (strstr(line, "\"password\"") != NULL) {
            extract_string_value(line, "password", students[count].password);
        }
        else if (strstr(line, "\"birthplace\"") != NULL) {
            extract_string_value(line, "birthplace", students[count].security.birthplace);
        }
        else if (strstr(line, "\"first_school\"") != NULL) {
            extract_string_value(line, "first_school",students[count].security.first_school);
        }
        else if (strstr(line, "\"first_book\"") != NULL) {
            extract_string_value(line, "first_book",students[count].security.first_book);
        }
        else if (strstr(line, "\"bike_color\"") != NULL) {
            extract_string_value(line, "bike_color", students[count].security.bike_color);
        }
        else if (strstr(line, "\"course_id\"") != NULL && strstr(line, "\"semester\"") != NULL) {
            int j = students[count].enrollment_count;
            extract_string_value(line, "semester", students[count].enrollments[j].semester);
            extract_string_value(line, "course_id", students[count].enrollments[j].course_id);
            students[count].enrollments[j].grade = extract_number_value(line, "grade");
            students[count].enrollment_count++;
        }
    }
    fclose(f);
    return ++count;
}
