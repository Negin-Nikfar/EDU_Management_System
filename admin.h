//
// Created by intel one on 7/9/2026.
//

#ifndef EDU_PROJECT_ADMIN_H
#define EDU_PROJECT_ADMIN_H
#include "data.h"

void admin_dashboard(Student students[], int *student_count,
                    Faculty faculty[], int *faculty_count,
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

void admin_requests(Request requests[], int *request_count,
                    Offering offerings[], int *offering_count,
                    Course courses[], int course_count,
                    Faculty faculties[], int faculty_count);

void admin_offerings(Offering offerings[], int *offering_count,
                     Course courses[], int course_count,
                     Student students[], int *student_count);
void search_offerings(Offering offerings[], int matching_indexes[],
                      int matching_count, Course courses[], int course_count);
void admin_enroll_student(Offering offerings[], int matching_indexes[],
                          int matching_count, Student students[], int *student_count);
void admin_withdraw_student(Offering offerings[], int matching_indexes[],
                            int matching_count, Student students[],int student_count);

void admin_courses(Course courses[], int *course_count, Offering offerings[],
                   int offering_count, Calendar *calendar);
void search_courses(Course courses[], int course_count);
void add_course(Course courses[], int *course_count, Calendar *calendar);
void remove_course(Course courses[], int *course_count, Offering offerings[], int offering_count);

#endif //EDU_PROJECT_ADMIN_H