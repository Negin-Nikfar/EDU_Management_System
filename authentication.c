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
        printf("Username not found.\n");
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

void forgot_password(Student students[], int student_count, Faculty faculties[], int faculty_count) {
    while (1) {
        char username[50];
        printf("Enter username: ");
        scanf("%s", username);

        int student_index = -1;
        for (int i = 0; i < student_count; i++) {
            if (strcmp(students[i].student_id, username) == 0) {
                student_index = i;
                break;
            }
        }
        int faculty_index = -1;
        for (int i = 0; i < faculty_count; i++) {
            if (strcmp(faculties[i].faculty_id, username) == 0) {
                faculty_index = i;
                break;
            }
        }
        if (student_index == -1 && faculty_index == -1) {
            printf("Username not found.\n");
            printf("1. Retry\n");
            printf("2. Go to login menu\n");
            printf("Enter an option: ");
            int ch;
            scanf("%d", &ch);
            if (ch == 2) {
                return;
            }
            else {
                continue;
            }
        }
        if (faculty_index != -1) {
            printf("Password reset is only available for students!\n");
            return;
        }
        int all_correct = 1;
        if (all_correct && strlen(students[student_index].security.birthplace) > 0) {
            char answer[100];
            printf("Where were you born? ");
            scanf("%s", answer);
            if (strcmp(answer, students[student_index].security.birthplace) != 0) {
                all_correct = 0;
            }
        }
        if (all_correct && strlen(students[student_index].security.first_school) > 0) {
            char answer[100];
            printf("What was the name of your first school? ");
            scanf("%s", answer);
            if (strcmp(answer, students[student_index].security.first_school) != 0) {
                all_correct = 0;
            }
        }
        if (all_correct && strlen(students[student_index].security.first_book) > 0) {
            char answer[100];
            printf("What was the title of the first book you read ? ");
            scanf("%s", answer);
            if (strcmp(answer, students[student_index].security.first_book) != 0) {
                all_correct = 0;
            }
        }
        if (all_correct && strlen(students[student_index].security.bike_color) > 0) {
            char answer[100];
            printf("What was the color of your first bike? ");
            scanf("%s", answer);
            if (strcmp(answer, students[student_index].security.bike_color) != 0) {
                all_correct = 0;
            }
        }
        if (all_correct != 1) {
            printf("Incorrect answer.\n");
            printf("1. Retry\n");
            printf("2. Go to login menu\n");
            printf("Enter an option: ");
            int ch;
            scanf("%d", &ch);
            if (ch == 2) {
                return;
            }
            else {
                continue;
            }
        }
        printf("Authentication successful.\n");
        while (1) {
            char new_password[50];
            char confirm[50];
            printf("Enter your new password: ");
            read_password(new_password);
            printf("\n");

            printf("Confirm your password: ");
            read_password(confirm);
            printf("\n");

            if (strcmp(new_password, confirm) != 0) {
                printf("Passwords aren't matching.\n");
                printf("1. Retry.\n");
                printf("2. Cancel (go to login menu).\n");
                printf("Enter an option: ");
                int ch;
                scanf("%d", &ch);
                if (ch == 2) {
                    return;
                }
                else {
                    continue;
                }
            }
            strcpy(students[student_index].password, new_password);
            save_students(students, student_count);
            printf("Password changed successfully.\n");
            printf("Press any key to go to login menu...\n");
            getch();
            return;
        }
    }
}
