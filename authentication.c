//
// Created by intel one on 7/9/2026.
//

#include <stdio.h>
#include <string.h>
#include <conio.h>
#include "utilities.h"
#include "authentication.h"

int authenticate(Role role, Student students[], int student_count,
                 Faculty faculteis[], int faculty_count) {
    char username[50];
    printf("Enter your username: ");
    scanf("%s", username);

    int i = -1;
    if (role == ROLE_STUDENT) {
        for (int j = 0; j < student_count; j++) {
            if (strcmp(students[j].student_id, username) == 0) {
                i = j;
                break;
            }
        }
    }
    else if (role == ROLE_FACULTY) {
        for (int j = 0; j < faculty_count; j++) {
            if (strcmp(faculteis[j].faculty_id, username) == 0) {
                i = j;
                break;
            }
        }
    }
    else if (role == ROLE_ADMIN) {
        if (strcmp(username, ADMIN_USERNAME) == 0) {
            i = 0;
        }
    }
    if (i == -1) {
        printf("Invalid username.\n");
        return -1;
    }
    printf("Enter password: ");
    char password[50];
    read_password(password);
    printf("\n");

    if (role == ROLE_STUDENT && strcmp(students[i].password, password) != 0) {
        printf("Incorrect password.\n");
        return -1;
    }
    if (role == ROLE_FACULTY && strcmp(faculteis[i].password, password) != 0) {
        printf("Incorrect password.\n");
        return -1;
    }
    if (role == ROLE_ADMIN && strcmp(password, ADMIN_PASSWORD) != 0) {
        printf("Incorrect password.\n");
        return -1;
    }
    return i;
}