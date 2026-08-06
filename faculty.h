//
// Created by intel one on 7/9/2026.

#ifndef EDU_PROJECT_FACULTY_H
#define EDU_PROJECT_FACULTY_H

#include "data.h"

void faculty_dashboard(int faculty_index,Faculty faculty[], int faculty_count,
                       Offering offering[], int *offering_count,
                       Course courses[], int course_count,
                       Request requests[], int *request_count,
                       Student students[], int student_count,
                       Homework homeworks[], int *hw_count,
                       Exam exams[], int *exam_count,
                       SurveyScore surveys[], int survey_count,
                       Calendar *calendar);

void my_offerings(int faculty_index, Faculty faculty[],
                  Offering offerings[], int *offering_count,
                  Course courses[], int course_count,
                  Student students[], int student_count,
                  Request requests[], int *request_count,
                  Homework homeworks[], int *hw_count,
                  Exam exams[], int *exam_count,
                  SurveyScore surveys[], int survey_count,
                  Calendar *calendar);

void offering_menu(int offering_index, Faculty faculty[], int faculty_index,
                   Offering offerings[],Course courses[], int course_count,
                   Student students[], int student_count,
                   Request requests[], int *request_count,
                   Homework homeworks[], int *hw_count,
                   Exam exams[], int *exam_count,
                   SurveyScore surveys[], int survey_count,
                   Calendar *calendar);

void add_capacity_request(int offering_index, Offering offerings[], Faculty faculty[],
                          int faculty_index, Request requests[], int *request_count,
                          Calendar *calendar);

void remove_offering_request(int offering_index, Offering offerings[], Faculty faculty[],
                             int faculty_index, Request requests[], int *request_count,
                             Calendar *calendar);

void record_grades(int offering_index, Offering offerings[], Student students[],
                   int student_count, Calendar *calendar);

void offer_course(Faculty faculty[], int faculty_index,
                  Course courses[], int course_count,
                  Request requests[], int *request_count,
                  Calendar *calendar);

void list_offerings_semester(Offering offerings[], int offering_count,
                             Course courses[], int course_count);

void list_courses_faculty(Course courses[], int course_count);

#endif //EDU_PROJECT_FACULTY_H