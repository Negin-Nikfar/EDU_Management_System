//
// Created by intel one on 7/9/2026.
//

#ifndef EDU_PROJECT_ADMIN_H
#define EDU_PROJECT_ADMIN_H
#include "data.h"

void admin_dashboard(Student students[], int *student_count,
                    Faculty faculties[], int *faculty_count,
                    Course courses[], int *course_count,
                    Offering offerings[], int *offering_count,
                    Request requests[], int *request_count,
                    Calendar *calendar);

void admin_calendar(Calendar *calendar);

void admin_students(Student students[], int *student_count);
void show_students_table(Student students[], int student_count);

void search_students(Student students[], int student_count);
void register_students(Student students[], int *student_count);
void register_one_student(Student students[], int *student_count);
void remove_student(Student students[], int *student_count);

void admin_faculty(Faculty faculties[], int *faculty_count);
void show_faculty_table(Faculty faculty[], int faculty_count);

void search_faculty(Faculty faculty[], int faculty_count);
void register_faculty(Faculty faculty[], int *faculty_count);
void remove_faculty(Faculty faculty[], int *faculty_count);

#endif //EDU_PROJECT_ADMIN_H