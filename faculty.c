//
// Created by intel one on 7/9/2026.
//

#include <stdio.h>
#include <string.h>
#include "data.h"
#include "faculty.h"

#include <conio.h>

void add_capacity_request(int offering_index, Offering offerings[], Faculty faculty[],
                          int faculty_index, Request requests[], int *request_count,
                          Calendar *calendar) {
    if (!calendar->offering_active) {
        printf("Offering period isn't active.\n");
        return;
    }
    printf("Enter extra capacity to add: ");
    int extra_capacity;
    scanf("%d", &extra_capacity);

    if (extra_capacity <= 0) {
        printf("Invalid extra capacity.\n");
        return;
    }
    Request r;
    r.id = *request_count + 1;
    r.type = ADD_CAPACITY;
    strcpy(r.faculty_id, faculty[faculty_index].faculty_id);
    strcpy(r.course_id, offerings[offering_index].course_id);
    strcpy(r.semester, offerings[offering_index].semester);
    r.extra_cap = extra_capacity;
    strcpy(r.place, offerings[offering_index].place);
    r.status = PENDING;

    requests[*request_count] = r;
    (*request_count)++;
    save_requests(requests, *request_count);
    printf("Sent request to admin.\n");
}

void record_grades(int offering_index, Offering offerings[], Student students[],
                   int student_count, Calendar *calendar) {
    if (!calendar->grade_recording_active) {
        printf("Grade recording isn't active.\n");
        return;
    }
    int enrolled_indexes[100];
    int enrolled_count = 0;
    for (int i = 0; i < student_count; i++) {
        for (int j = 0; j < students[i].enrollment_count; j++) {
            if (strcmp(students[i].enrollments[j].course_id, offerings[offering_index].course_id) == 0 &&
                strcmp(students[i].enrollments[j].semester, offerings[offering_index].semester) == 0) {
                enrolled_indexes[enrolled_count] = i;
                enrolled_count++;
                break;
            }
        }
    }
    if (enrolled_count == 0) {
        printf("No students enrolled in this offering.\n");
        return;
    }
    printf("1. Enter grades manually\n");
    printf("2. Import from CSV\n");
    printf("Enter an option: ");
    int choice;
    scanf("%d", &choice);

    if (choice == 1) {
        for (int j = 0; j < enrolled_count; j++) {
            int student_index = enrolled_indexes[j];
            printf("%s %s: ", students[student_index].first_name, students[student_index].last_name);
            float grade;
            scanf("%f", &grade);

            while (grade < 0 || grade > 20) {
                printf("Invalid grade. Try again!\n");
                scanf("%f", &grade);
            }
            for (int k = 0; k < students[student_index].enrollment_count; k++) {
                if (strcmp(students[student_index]. enrollments[k].course_id, offerings[offering_index].course_id) == 0 &&
                    strcmp(students[student_index].enrollments[k].semester, offerings[offering_index].semester) == 0) {
                    students[student_index].enrollments[k].grade = grade;
                    break;
                    }
            }
        }
        save_students(students, student_count);
        printf("Grades recorded.\n");
    }
    else if (choice == 2) {
    printf("CSV import will be later.\n");
    }
}

void remove_offering_request(int offering_index, Offering offerings[], Faculty faculty[],
                             int faculty_index, Request requests[], int *request_count,
                             Calendar *calendar) {
    if (!calendar->offering_active) {
        printf("Offering period has ended.\n");
        return;
    }
    Request r;
    r.id = *request_count + 1;
    r.type = REMOVE_OFFERING;
    strcpy(r.faculty_id, faculty[faculty_index].faculty_id);
    strcpy(r.course_id, offerings[offering_index].course_id);
    strcpy(r.semester, offerings[offering_index].semester);
    r.extra_cap = 0;
    strcpy(r.place, offerings[offering_index].place);
    r.status = PENDING;

    requests[*request_count] = r;
    (*request_count)++;
    save_requests(requests, *request_count);
    printf("Sent request to admin.\n");
}

void offering_menu(int offering_index, Faculty faculty[], int faculty_index,
                   Offering offerings[],Course courses[], int course_count,
                   Student students[], int student_count,
                   Request requests[], int *request_count,
                   Calendar *calendar) {
    char course_name[100] = "Unknown";
    for (int j = 0; j < course_count; j++) {
        if (strcmp(courses[j].course_id, offerings[offering_index].course_id) == 0) {
            strcpy(course_name, courses[j].name);
            break;
        }
    }
    printf("| %s | %s | %s | %s | %d | %d | %s | %s |\n",
           course_name, offerings[offering_index].course_id,
           offerings[offering_index].faculty_id, offerings[offering_index].semester,
           offerings[offering_index].capacity, offerings[offering_index].enrolled_count,
           offerings[offering_index].department, offerings[offering_index].place);
    int running = 1;
    while (running) {
        printf("1. Add Capacity\n");
        printf("2. Record grades\n");
        printf("3. Remove offering\n");
        printf("4. Publish a homework\n");
        printf("5. Publish an exam\n");
        printf("6. Go back\n");
        printf("Enter an option: ");
        int choice;
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                add_capacity_request(offering_index, offerings, faculty, faculty_index,
                                     requests, request_count, calendar);
                break;
            case 2:
                record_grades(offering_index, offerings, students, student_count, calendar);
                break;
            case 3:
                remove_offering_request(offering_index, offerings, faculty, faculty_index,
                                        requests, request_count, calendar);
                break;
            case 4:
                printf("This part will be later...\n");
                break;
            case 5:
                printf("This part will be later...\n");
                break;
            case 6:
                running = 0;
                break;
            default:
                printf("Invalid choice. Try again!\n");
        }
    }
}

void my_offerings(int faculty_index, Faculty faculty[],
                  Offering offerings[], int *offering_count,
                  Course courses[], int course_count,
                  Student students[], int student_count,
                  Request requests[], int *request_count,
                  Calendar *calendar) {
    char my_faculty_id[50];
    strcpy(my_faculty_id, faculty[faculty_index].faculty_id);
    int mine_indexes[100];
    int mine_count = 0;

    for (int i = 0; i < *offering_count; i++) {
        if (strcmp(offerings[i].faculty_id, my_faculty_id) == 0) {
            mine_indexes[mine_count] = i;
            mine_count++;
        }
    }
    printf("Faculty: My offerings\n");
    printf("List of my Offerings(all offerings ordered by semester)\n");

    if (mine_count == 0) {
        printf("You have no offerings.\n");
        return;
    }
    for (int i = 0; i < mine_count; i++) {
        int index = mine_indexes[i];
        char course_name[100];
        for (int j = 0; j < course_count; j++) {
            if (strcmp(courses[j].course_id, offerings[index].course_id) == 0) {
                strcpy(course_name, courses[j].name);
                break;
            }
        }
        printf("| %d | %s | %s | %s | %s | %d | %d | %s | %s |\n",
            i + 1, course_name, offerings[index].course_id,
            offerings[index].faculty_id, offerings[index].semester,
            offerings[index].capacity, offerings[index].enrolled_count,
            offerings[index].department, offerings[index].place);
        printf("1. Go to offering\n");
        printf("2. Search\n");
        printf("3. Go back\n");
        printf("4. Enter an option: ");
    }
    int choice;
    scanf("%d", &choice);

    if (choice == 1) {
        printf("Enter offering number: ");
        int number;
        scanf("%d", &number);

        if (number < 1 || number > mine_count) {
            printf("Invalid number.\n");
            return;
        }
        int offering_index = mine_indexes[number - 1];
        offering_menu(offering_index, faculty, faculty_index, offerings,courses,
                      course_count, students, student_count, requests,request_count,
                      calendar);
    }
    else if (choice == 2) {
        printf("This part will be later.\n");
    }
}

void list_offerings_semester(Offering offerings[], int offering_count,
                             Course courses[], int course_count) {
    printf("Enter semester number: ");
    char semester[50];
    scanf("%s", semester);

    int found = 0;
    for (int i = 0; i < offering_count; i++) {
        if (strcmp(offerings[i].semester, semester) == 0) {
            char course_name[100] = "Unknown";
            for (int j = 0; j < course_count; j++) {
                if (strcmp(courses[j].course_id, offerings[i].course_id) == 0) {
                    strcpy(course_name, courses[j].name);
                    break;
                }
            }
            printf(" | %s | %s | %s | %s | %d | %d | %s | %s |\n",
                course_name, offerings[i].course_id, offerings[i].faculty_id,
                offerings[i].semester, offerings[i].capacity, offerings[i].enrolled_count,
                offerings[i].department, offerings[i].place);
            found = 1;
        }
    }
    if (!found) {
        printf("No offering found for this semester.\n");
    }
}

void list_courses_faculty(Course courses[], int course_count) {
    printf("List of courses\n");
    for (int i = 0; i < course_count; i++) {
        printf("| %s | %s | %d | ", courses[i].name, courses[i].course_id, courses[i].units);
        for (int j = 0; j < courses[i].prereq_count; j++) {
            printf("%s", courses[i].prerequisites[j]);
            if (j < courses[i].prereq_count - 1) {
                printf(", ");
            }
        }
        printf(" | %s | %s | %s |\n", courses[i].section, courses[i].field, courses[i].department);
    }
}

void offer_course(Faculty faculty[], int faculty_index,
                  Course courses[], int course_count,
                  Request requests[], int *request_count,
                  Calendar *calendar) {
    if (!calendar->offering_active) {
        printf("Offering period isn't active.\n");
        return;
    }
    printf("Enter the course id: ");
    char course_id[50];
    scanf("%s", course_id);

    int course_index = -1;
    for (int i = 0; i < course_count; i++) {
        if (strcmp(courses[i].course_id, course_id) == 0) {
            course_index = i;
            break;
        }
    }
    if (course_index == -1) {
        printf("Course not found.\n");
        return;
    }
    printf(" | %s | %s | %d |\n", courses[course_index].name,
           courses[course_index].course_id, courses[course_index].units);
    for (int i = 0; i < courses[course_index].prereq_count; i++) {
        printf("%s", courses[course_index].prerequisites[i]);
        if (i < courses[course_index].prereq_count - 1) {
            printf(", ");
        }
    }
    printf(" | %s | %s | %s |\n", courses[course_index].section, courses[course_index].field,
           courses[course_index].department);
    printf("Enter semester number: ");
    char semester[50];
    scanf("%s", semester);

    printf("Enter the capacity: ");
    int capacity;
    scanf("%d", &capacity);

    if (capacity <= 0) {
        printf("Invalid capacity.\n");
        return;
    }
    printf("Enter the place: ");
    char place[100];
    scanf(" %[^\n]", place);

    Request r;
    r.id = *request_count + 1;
    r.type = OFFER_COURSE;
    strcpy(r.faculty_id, faculty[faculty_index].faculty_id);
    strcpy(r.course_id, course_id);
    strcpy(r.semester, semester);
    r.extra_cap = capacity;
    strcpy(r.place, place);
    r.status = PENDING;

    requests[*request_count] = r;
    (*request_count)++;
    save_requests(requests, *request_count);
    printf("Sent request to admin.\n");
    printf("Press any key to go to offerings...\n");
    getch();

}

void faculty_dashboard(int faculty_index,Faculty faculty[], int faculty_count,
                       Offering offerings[], int *offering_count,
                       Course courses[], int course_count,
                       Request requests[], int *request_count,
                       Student students[], int student_count,
                       Calendar *calendar) {
    int running = 1;
    while (running) {
        printf("Faculty\n");
        printf("Welcome %s %s\n", faculty[faculty_index].first_name, faculty[faculty_index].last_name);
        printf("1. My offerings\n");
        printf("2. List of offerings in semester\n");
        printf("3. List of courses\n");
        printf("4. Offer a course\n");
        printf("5. Log out\n");
        printf("Enter an option: ");
        int choice;
        scanf("%d", &choice);

        switch (choice) {
        case 1:
            my_offerings(faculty_index, faculty, offerings, offering_count,
                         courses, course_count, students, student_count,
                         requests, request_count, calendar);
            break;
        case 2:
            list_offerings_semester(offerings, *offering_count, courses, course_count);
            break;
        case 3:
            list_courses_faculty(courses, course_count);
            break;
        case 4:
            offer_course(faculty, faculty_index, courses, course_count,
                         requests, request_count, calendar);
            break;
        case 5:
            running = 0;
            break;
        default:
            printf("Invalid choice. Try again!\n");
        }
    }
}