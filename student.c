//
// Created by intel one on 7/9/2026.
//

#include <stdio.h>
#include <string.h>
#include "data.h"
#include "utilities.h"
#include "student.h"

#include <conio.h>

void search_offerings_student(Offering offerings[], int matching_indexes[],
                              int matching_count, Course courses[], int course_count,
                              Faculty faculty[], int faculty_count) {
    printf("1. Search by course name\n");
    printf("2. Search by course id\n");
    printf("3. Search by department\n");
    printf("Enter a choice: ");
    int choice;
    scanf("%d", &choice);

    printf("The phrase to search: ");
    char answer[100];
    scanf("%s", answer);

    int found  = 0;
    for (int i = 0; i < matching_count; i++) {
        int index = matching_indexes[i];
        char course_name[100] = "Unknown";
        for (int j = 0; j < course_count; j++) {
            if (strcmp(courses[j].course_id, offerings[index].course_id) == 0) {
                strcpy(course_name, courses[j].name);
                break;
            }
        }
        int match = 0;
        if (choice == 1 && strstr(course_name, answer) != NULL) {
            match = 1;
        }
        else if (choice == 2 && strstr(offerings[index].course_id, answer) != NULL) {
            match = 1;
        }
        else if (choice == 3 && strstr(offerings[index].department, answer) != NULL) {
            match = 1;
        }
        if (match) {
            char faculty_display[100] = "Unknown";
            for (int j = 0; j < faculty_count; j++) {
                if (strcmp(faculty[j].faculty_id, offerings[index].faculty_id) == 0) {
                    sprintf(faculty_display, "Dr. %s", faculty[j].last_name);
                    break;
                }
            }
            printf("| %s | %s | %s | %s | %d | %d | %s | %s |\n",
                course_name, offerings[index].course_id, faculty_display,
                offerings[index].semester, offerings[index].capacity,
                offerings[index].enrolled_count, offerings[index].department, offerings[index].place);
            found = 1;
        }
    }
    if (!found) {
        printf("No offerings found.\n");
    }
}

void enroll_in_course(int student_index, Student students[], int student_count,
                      Offering offerings[], int matching_indexes[], int matching_count,
                      Course courses[], int course_count, Calendar *calendar) {
    if (!calendar->unit_selection_active) {
        printf("Unit selection isn't active.\n");
        return;
    }
    printf("Enter offering number: ");
    int number;
    scanf("%d", &number);

    if (number < 1 || number > matching_count) {
        printf("Invalid offering number.\n");
        return;
    }
    int offering_index = matching_indexes[number - 1];
    if (offerings[offering_index].enrolled_count >= offerings[offering_index].capacity) {
        printf("No capacity available.\n");
        return;
    }
    int course_index = -1;
    for (int i = 0; i < course_count; i++) {
        if (strcmp(courses[i].course_id, offerings[offering_index].course_id) == 0) {
            course_index = i;
            break;
        }
    }
    if (course_index == -1 || !check_prerequisites(students[student_index], courses[course_index])) {
        printf("Prerequisites not met.\n");
        return;
    }
    for (int i = 0; i < students[student_index].enrollment_count; i++) {
        if (strcmp(students[student_index].enrollments[i].course_id, offerings[offering_index].course_id) == 0 &&
            strcmp(students[student_index].enrollments[i].semester, offerings[offering_index].semester) == 0) {
            printf("You are already enrolled in this course.\n");
            return;
        }
    }
    int enrollment_index = students[student_index].enrollment_count;
    strcpy(students[student_index].enrollments[enrollment_index].semester, offerings[offering_index].semester);
    strcpy(students[student_index].enrollments[enrollment_index].course_id, offerings[offering_index].course_id);
    students[student_index].enrollments[enrollment_index].grade = -1;
    students[student_index].enrollment_count++;
    offerings[offering_index].enrolled_count++;
    save_students(students, student_count);
    printf("Enrolled successfully.\n");
}

void withdraw_course(int student_index, Student students[], int student_count,
                     Offering offerings[], int matching_indexes[], int matching_count,
                     Calendar *calendar) {
    if (!calendar->unit_selection_active) {
        printf("Unit selection isn't active.\n");
        return;
    }
    printf("Enter offering number: ");
    int number;
    scanf("%d", &number);

    if (number < 1 || number > matching_count) {
        printf("Invalid offering number.\n");
        return;
    }
    int offering_index = matching_indexes[number - 1];
    int enrolled_index = -1;
    for (int i = 0; i < students[student_index].enrollment_count; i++) {
        if (strcmp(students[student_index].enrollments[i].course_id, offerings[offering_index].course_id) == 0 &&
            strcmp(students[student_index].enrollments[i].semester, offerings[offering_index].semester) == 0) {
            enrolled_index = i;
            break;
            }
    }
    if (enrolled_index == -1) {
        printf("You aren't enrolled in this course.\n");
        return;
    }
    for (int i = enrolled_index; i < students[student_index].enrollment_count - 1; i++) {
        students[student_index].enrollments[i] = students[student_index].enrollments[i + 1];
    }
    students[student_index].enrollment_count--;
    offerings[offering_index].enrolled_count--;
    save_students(students, student_count);
    printf("Withdrawn successfully.\n");
}

void student_offerings(int student_index, Student students[], int student_count,
                       Offering offerings[], int *offerings_count,
                       Course courses[], int course_count,
                       Faculty faculty[], int faculty_count, Calendar *calendar) {
    printf("Student: Offerings\n");
    printf("Enter semester number: ");
    char semester[50];
    scanf("%s", semester);

    int matching_indexes[100];
    int matching_count = 0;
    for (int i = 0; i < *offerings_count; i++) {
        if (strcmp(offerings[i].semester, semester) == 0) {
            matching_indexes[matching_count] = i;
            matching_count++;
        }
    }
    if (matching_count == 0) {
        printf("No offerings found for this semester.\n");
        return;
    }
    printf("List of offerings - %s\n", semester);
    for (int i = 0; i < matching_count; i++) {
        int index = matching_indexes[i];
        char course_name[100] = "Unknown";
        for (int j = 0; j < course_count; j++) {
            if (strcmp(courses[j].course_id, offerings[index].course_id) == 0) {
                strcpy(course_name, courses[j].name);
                break;
            }
        }
        char faculty_display[100] = "Unknown";
        for (int j = 0; j < faculty_count; j++) {
            if (strcmp(faculty[j].faculty_id, offerings[index].faculty_id) == 0) {
                sprintf(faculty_display, "Dr. %s", faculty[j].last_name);
                break;
            }
        }
        printf("| %d | %s | %s | %s | %s | %d | %d | %s | %s |\n",
               i + 1, course_name, offerings[index].course_id, faculty_display,
               offerings[index].semester, offerings[index].capacity,
               offerings[index].enrolled_count, offerings[index].department,
               offerings[index].place);
    }
    printf("1. Search\n");
    printf("2. Enroll in course\n");
    printf("3. Withdrew course\n");
    printf("4. Go back\n");
    printf("Enter a choice: ");
    int choice;
    scanf("%d", &choice);

    if (choice == 1) {
        search_offerings_student(offerings, matching_indexes, matching_count,
                                 courses, course_count, faculty, faculty_count);
    }
    else if (choice == 2) {
        enroll_in_course(student_index, students, student_count, offerings,
            matching_indexes, matching_count, courses, course_count, calendar);
    }
    else if (choice == 3) {
        withdraw_course(student_index, students, student_count, offerings,
                        matching_indexes, matching_count, calendar);
        save_offerings(offerings, *offerings_count);
    }
}

void list_courses_student(Course courses[], int course_count) {
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

void show_semester_report(int student_index, Student students[], Course courses[],
                          int course_count, Offering offerings[], int offering_count,
                          Faculty faculty[], int faculty_count, char *semester) {
    Student s = students[student_index];
    int semester_indexes[100];
    int semester_count = 0;

    for (int i = 0; i < s.enrollment_count; i++) {
        if (strcmp(s.enrollments[i].semester, semester) == 0) {
            semester_indexes[semester_count] = i;
            semester_count++;
        }
    }
    if (semester_count == 0) {
        printf("No records for this semester.\n");
        return;
    }
    printf("Report card - %s %s - %s\n", s.first_name, s.last_name, semester);
    printf("| course name | course id | units | grade | passed | instructor's name |\n");

    int enrolled_count = 0, passed_count  = 0, failed_count = 0;
    for (int i = 0; i < semester_count; i++) {
        int k = semester_indexes[i];
        char course_name[100] = "Unknown";
        int units = 0;
        for (int j = 0; j < course_count; j++) {
            if (strcmp(courses[j].course_id, s.enrollments[k].course_id) == 0) {
                strcpy(course_name, courses[j].name);
                units = courses[j].units;
                break;
            }
        }
        char instructor[100] = "N/A";
        for (int j = 0; j < offering_count; j++) {
            if (strcmp(offerings[j].course_id, s.enrollments[k].course_id) == 0 &&
                strcmp(offerings[j].semester, semester) == 0) {
                for (int f = 0; f < faculty_count; f++) {
                    if (strcmp(faculty[f].faculty_id, offerings[j].faculty_id) == 0) {
                        sprintf(instructor, "Dr. %s", faculty[f].last_name);
                        break;
                    }
                }
                break;
            }
        }
        char *passed = (s.enrollments[i].grade >= 10.0) ? "Yes" : "No";
        printf("| %s | %s | %d | %.2f | %s | %s |\n",
                course_name, s.enrollments[k].course_id, units, s.enrollments[k].grade, passed, instructor);
        enrolled_count++;
        if (s.enrollments[k].grade >= 10.0) {
            passed_count++;
        }
        else {
            failed_count++;
        }
    }
    float gpa = calculate_gpa(s, semester, courses, course_count);
    printf("Enrolled courses: %d\n", enrolled_count);
    printf("Passed courses: %d\n", passed_count);
    printf("Failed courses: %d\n", failed_count);
    printf("GPA: %.2f\n", gpa);
    printf("Press any key to go back...");
    getch();
}

void report_card(int student_index, Student students[], Course courses[], int course_count,
                 Offering offerings[], int offering_count, Faculty faculty[], int faculty_count) {
    Student s = students[student_index];
    printf("Student: Report card\n");
    printf("|student id |%s |\n", s.student_id);
    printf("|first name |%s |\n", s.first_name);
    printf("last name |%s |\n", s.last_name);
    printf("|national code |%s |\n", s.national_code);
    printf("|field |%s |\n", s.field);
    printf("|entrance year |%d |\n", s.entrance_year);
    printf("|section |%s |\n", s.section);
    printf("|mentor |%s |\n", s.mentor);
    printf("|department |%s |\n", s.department);

    float overall_gpa = calculate_gpa(s, NULL, courses, course_count);
    printf("|GPA |%.2f |\n", overall_gpa);

    printf("1. Go to semester\n");
    printf("2. Go back\n");
    printf("Enter a choice: ");
    int choice;
    scanf("%d", &choice);

    if (choice == 1) {
        printf("Enter semester number: ");
        char semester_number[50];
        scanf("%s", semester_number);
        show_semester_report(student_index, students, courses, course_count, offerings,
                             offering_count, faculty, faculty_count, semester_number);
    }
}

void student_dashboard(int student_index, Student students[], int student_count,
                       Offering offerings[], int *offering_count,
                       Course courses[], int course_count,
                       Faculty faculty[], int faculty_count,
                       Calendar *calendar) {
    int running = 1;
    while (running) {
        printf("Student\n");
        printf("1. Offerings\n");
        printf("2. Courses\n");
        printf("3. Report card\n");
        printf("4. Log out\n");
        printf("Enter an option: ");
        int choice;
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                student_offerings(student_index, students, student_count, offerings,
                                  offering_count, courses, course_count, faculty,
                                  faculty_count, calendar);
                break;
            case 2:
                list_courses_student(courses, course_count);
                break;
            case 3:
                report_card(student_index, students, courses, course_count, offerings,
                            *offering_count, faculty, faculty_count);
                break;
            case 4:
               running = 0;
                break;
            default:
                printf("Invalid choice. Try again!\n");
        }
    }
}