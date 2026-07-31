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

#endif //EDU_PROJECT_ADMIN_H