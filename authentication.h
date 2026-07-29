//
// Created by intel one on 7/9/2026.
//

#ifndef EDU_PROJECT_AUTHENTICATION_H
#define EDU_PROJECT_AUTHENTICATION_H

#include "data.h"

#define ADMIN_USERNAME "admin"
#define ADMIN_PASSWORD "admin.123"

typedef enum Role {
    ROLE_STUDENT,
    ROLE_FACULTY,
    ROLE_ADMIN
} Role;

int authenticate(Role role, Student students[], int student_count,
                 Faculty faculty[], int faculty_count);

void forgot_password(Student students[], int student_count, Faculty faculties[], int faculty_count);

#endif //EDU_PROJECT_AUTHENTICATION_H