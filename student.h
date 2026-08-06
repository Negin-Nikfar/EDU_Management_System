//
// Created by intel one on 7/9/2026.
//

#ifndef EDU_PROJECT_STUDENT_H
#define EDU_PROJECT_STUDENT_H

#include "data.h"

void student_dashboard(int student_index, Student students[], int student_count,
                       Offering offerings[], int *offering_count,
                       Course courses[], int course_count,
                       Faculty faculty[], int faculty_count,
                       Calendar *calendar);

void student_offerings(int student_index, Student students[], int student_count,
                       Offering offerings[], int *offerings_count,
                       Course courses[], int course_count,
                       Faculty faculty[], int faculty_count,
                       Calendar *calendar);

void enroll_in_course(int student_index, Student students[], int student_count,
                      Offering offerings[], int matching_indexes[], int matching_count,
                      Course courses[], int course_count, Calendar *calendar);

void withdraw_course(int student_index, Student students[], int student_count,
                     Offering offerings[], int matching_indexes[], int matching_count,
                     Calendar *calendar);

void search_offerings_student(Offering offerings[], int matching_indexes[],
                              int matching_count, Course courses[], int course_count,
                              Faculty faculty[], int faculty_count);

void list_courses_student(Course courses[], int course_count);

void report_card(int student_index, Student students[], Course courses[], int course_count,
                 Offering offerings[], int offering_count, Faculty faculty[], int faculty_count);

void show_semester_report(int student_index, Student students[], Course courses[],
                          int course_count, Offering offerings[], int offering_count,
                          Faculty faculty[], int faculty_count, char *semester);

#endif //EDU_PROJECT_STUDENT_H