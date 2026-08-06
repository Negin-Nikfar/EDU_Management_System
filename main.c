//
// Created by intel one on 7/9/2026.
//
#include <stdio.h>
#include "data.h"
#include "admin.h"
#include "authentication.h"
#include "faculty.h"
#include "student.h"

int main(void) {
    Student students[100];
    int student_count = load_students(students, 100);

    Faculty faculty[100];
    int faculty_count = load_faculty(faculty, 100);

    Course courses[100];
    int course_count = load_courses(courses, 100);

    Offering offerings[100];
    int offering_count = load_offerings(offerings, 100);

    Request requests[100];
    int request_count = load_requests(requests, 100);

    Calendar calendar = load_calendar();

    int running = 1;
    while (running) {
        printf("1. Login as student\n");
        printf("2. Login as faculty\n");
        printf("3. Login as admin\n");
        printf("4. Forgot password\n");
        printf("5. Exit\n");
        printf("Enter an option: ");
        int choice;
        scanf("%d", &choice);

        switch (choice) {
            case 1: {
                    int index = authenticate(ROLE_STUDENT, students, student_count, faculty, faculty_count);
                    if (index != -1) {
                        student_dashboard(index, students, student_count, offerings, &offering_count,
                           courses, course_count, faculty, faculty_count, &calendar);
                    }
                    break;
                }
            case 2: {
                    int index = authenticate(ROLE_FACULTY, students, student_count, faculty, faculty_count);
                    if (index != -1) {
                        faculty_dashboard(index, faculty, faculty_count, offerings, &offering_count,
                            courses, course_count, requests, &request_count, students, student_count,
                            &calendar);
                    }
                    break;
                }
            case 3: {
                    int index = authenticate(ROLE_ADMIN, students, student_count, faculty, faculty_count);
                    if (index != -1) {
                        admin_dashboard(students, &student_count, faculty, &faculty_count,
                                        courses, &course_count, offerings, &offering_count,
                                        requests, &request_count, &calendar);
                    }
                    break;
                }
            case 4:
                forgot_password(students, student_count, faculty, faculty_count);
                break;
            case 5:
                running = 0;
                break;
            default:
                printf("Invalid choice. Try again!\n");
        }
    }
    return 0;
}

void admin_dashboard(Student students[], int *student_count,
                     Faculty faculty[], int *faculty_count,
                     Course courses[], int *course_count,
                     Offering offerings[], int *offering_count,
                     Request requests[], int *request_count,
                     Calendar *calendar) {
    int running = 1;
    while (running) {
        printf("Admin dashboard: \n");
        printf("Welcome %s\n", ADMIN_USERNAME);
        printf("1. Calendar\n");
        printf("2. Students\n");
        printf("3. Faculty members\n");
        printf("4. Requests\n");
        printf("5. Offerings\n");
        printf("6. Courses\n");
        printf("7. Log out\n");
        printf("8. Enter an option: \n");

        int choice;
        scanf("%d", &choice);
        switch (choice) {
        case 1:
            admin_calendar(calendar);
            break;
        case 2:
            admin_students(students, student_count);
            break;
        case 3:
            admin_faculty(faculty, faculty_count);
            break;
        case 4:
            admin_requests(requests, request_count, offerings, offering_count,
                courses, *course_count, faculty, *faculty_count);
            break;
        case 5:
            admin_offerings(offerings, offering_count, courses, *course_count, students, student_count);
            break;
        case 6:
            admin_courses(courses, course_count, offerings, *offering_count, calendar);
            break;
        case 7:
            running = 0;
            break;
        default:
            printf("Invalid choice. Try again!\n");
        }
    }
}