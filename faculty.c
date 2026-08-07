//
// Created by intel one on 7/9/2026.
//

#include <stdio.h>
#include <string.h>
#include <math.h>
#include <conio.h>
#include "data.h"
#include "utilities.h"
#include "faculty.h"

#include <stdlib.h>

void add_capacity_request(int offering_index, Offering offerings[], Faculty faculty[],
                          int faculty_index, Request requests[], int *request_count,
                          Calendar *calendar) {
    if (!calendar->offering_active) {
        print_error("Offering period isn't active.\n");
        return;
    }
    printf("Enter extra capacity to add: ");
    int extra_capacity;
    scanf("%d", &extra_capacity);

    if (extra_capacity <= 0) {
        print_error("Invalid extra capacity.\n");
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
    print_success("Sent request to admin.\n");
}

void record_grades(int offering_index, Offering offerings[], Student students[],
                   int student_count, Calendar *calendar) {
    if (!calendar->grade_recording_active) {
        print_error("Grade recording isn't active.\n");
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
        print_error("No students enrolled in this offering.\n");
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
                print_warning("Invalid grade. Try again!\n");
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
        print_success("Grades recorded.\n");
    }
    else if (choice == 2) {
    printf("Enter CSV file path: ");
        char filepath[200];
        scanf(" %[^\n]", filepath);

        FILE *f = fopen(filepath, "r");
        if (f == NULL) {
            print_error("Couldn't open file.");
            return;
        }

        char line[300];
        int line_number = 0;
        int updated_count = 0;
        int skipped_count = 0;

        while (fgets(line, sizeof(line), f) != NULL) {
            line_number++;
            line[strcspn(line, "\r\n")] = '\0';

            if (line_number == 1) {
                continue;
            }
            if (strlen(line) == 0) {
                continue;
            }

            char *sid_token = strtok(line, ",");
            char *grade_token = strtok(NULL, ",");

            if (sid_token == NULL || grade_token == NULL) {
                print_warning("Invalid row (missing fields).");
                skipped_count++;
                continue;
            }
            while (*sid_token == ' ') {
                sid_token++;
            }
            while (*grade_token == ' ') {
                grade_token++;
            }

            int student_index = -1;
            for (int j = 0; j < enrolled_count; j++) {
                int idx = enrolled_indexes[j];
                if (strcmp(students[idx].student_id, sid_token) == 0) {
                    student_index = idx;
                    break;
                }
            }
            if (student_index == -1) {
                print_warning("Student not enrolled in this offering.");
                skipped_count++;
                continue;
            }
            float grade = 0;
            char *endptr;
            grade = (float) strtod(grade_token, &endptr);
            if (endptr == grade_token || *endptr != '\0') {
                print_warning("Invalid grade.");
                skipped_count++;
                continue;
            }
            if (grade < 0 || grade > 20) {
                print_warning("Invalid grade.");
                skipped_count++;
                continue;
            }
            for (int k = 0; k < students[student_index].enrollment_count; k++) {
                if (strcmp(students[student_index].enrollments[k].course_id, offerings[offering_index].course_id) == 0 &&
                    strcmp(students[student_index].enrollments[k].semester, offerings[offering_index].semester) == 0) {
                    students[student_index].enrollments[k].grade = grade;
                    break;
                }
            }
            updated_count++;
        }
        fclose(f);
        save_students(students, student_count);
        char message[100];
        sprintf(message, "Imported %d grade(s). Skipped %d row(s).", updated_count, skipped_count);
        print_success(message);
    }
    else {
        print_error("Invalid choice. Try again!");
    }
}


void remove_offering_request(int offering_index, Offering offerings[], Faculty faculty[],
                             int faculty_index, Request requests[], int *request_count,
                             Calendar *calendar) {
    if (!calendar->offering_active) {
        print_error("Offering period has ended.\n");
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
    print_success("Sent request to admin.\n");
}

void publish_homework(int offering_index, Offering offerings[],
                      Homework homeworks[], int *hw_count, Calendar *calendar) {
    if (!calendar->class_exam_active) {
        print_error("Class period isn't active.\n");
        return;
    }
    Homework hw;
    sprintf(hw.offering_id, "%s_%s_%s", offerings[offering_index].course_id,
            offerings[offering_index].faculty_id, offerings[offering_index].semester);
    printf("Enter homework title: ");
    scanf(" %[^\n]", hw.title);

    printf("Enter total score: ");
    scanf("%f", &hw.total_score);

    printf("Enter number of questions: ");
    int n;
    scanf("%d", &n);

    if (n < 1) {
        print_error("Number of questions must be greater than zero.\n");
        return;
    }
    hw.num_questions = n;
    for (int i = 0; i < n; i++) {
        printf("Questions %d: ", i + 1);
        scanf(" %[^\n]", hw.questions[i].text);

        printf("Option a: ");
        scanf(" %[^\n]", hw.questions[i].option_a);

        printf("Option b: ");
        scanf(" %[^\n]", hw.questions[i].option_b);

        printf("Option c: ");
        scanf(" %[^\n]", hw.questions[i].option_c);

        printf("Option d: ");
        scanf(" %[^\n]", hw.questions[i].option_d);

        printf("Correct option (a/b/c/d): ");
        scanf(" %c", &hw.questions[i].correct);
    }
    homeworks[*hw_count] = hw;
    (*hw_count)++;
    save_homeworks(homeworks, *hw_count);
    print_success("Homework published.\n");
}

void publish_exam(int offering_index, Offering offerings[],
                  Exam exams[], int *exam_count, Calendar *calendar) {
    if (!calendar->class_exam_active) {
        print_error("Class period isn't active.\n");
        return;
    }
    Exam ex;
    sprintf(ex.offering_id, "%s_%s_%s", offerings[offering_index].course_id,
        offerings[offering_index].faculty_id, offerings[offering_index].semester);
    printf("Enter exam title: ");
    scanf(" %[^\n]", ex.title);

    printf("Enter total score: ");
    scanf("%f", &ex.total_score);

    printf("Enter number of questions: ");
    int n;
    scanf("%d", &n);

    if (n < 1) {
        print_error("Number of questions must be greater than zero.\n");
        return;
    }

    ex.num_questions = n;
    for (int i = 0; i < n; i++) {
        printf("Questions %d type? (1. MCQ 2. Descriptive): ", i + 1);
        int type_choice;
        scanf("%d", &type_choice);

        printf("Enter question text: ");
        scanf(" %[^\n]", ex.questions[i].text);

        if (type_choice == 1) {
            ex.questions[i].type = MCQ;
            printf("Option a: ");
            scanf(" %[^\n]", ex.questions[i].option_a);

            printf("Option b: ");
            scanf(" %[^\n]", ex.questions[i].option_b);

            printf("Option c: ");
            scanf(" %[^\n]", ex.questions[i].option_c);

            printf("Option d: ");
            scanf(" %[^\n]", ex.questions[i].option_d);

            printf("Correct option (a/b/c/d): ");
            scanf(" %c", &ex.questions[i].correct);
        }
        else {
            ex.questions[i].type = DESCRIPTIVE;
            printf("Enter reference answer: ");
            scanf(" %[^\n]", ex.questions[i].reference_answer);
        }
    }
    exams[*exam_count] = ex;
    (*exam_count)++;
    save_exams(exams, *exam_count);
    print_success("Exam published.\n");
}

void show_survey_results(int offering_index, Offering offerings[], SurveyScore surveys[], int survey_count) {
    char offering_id[160];
    sprintf(offering_id, "%s_%s_%s", offerings[offering_index].course_id, offerings[offering_index].faculty_id,
            offerings[offering_index].semester);
    int scores[100];
    int n = 0;
    for (int i = 0; i < survey_count; i++) {
        if (strcmp(surveys[i].offering_id, offering_id) == 0) {
            scores[n] = surveys[i].score;
            n++;
        }
    }
    if (n == 0) {
        print_error("No survey responses yet.\n");
        return;
    }
    float sum = 0;
    for (int i = 0; i < n; i++) {
        sum += scores[i];
    }
    float average = sum / n;
    float sum_sq_diff = 0;
    for (int i = 0; i < n; i++) {
        sum_sq_diff += (scores[i] - average) * (scores[i] - average);
    }
    float std_dev = sqrt(sum_sq_diff / n);
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (scores[j] > scores[j + 1]) {
                int temp = scores[j];
                scores[j] = scores[j + 1];
                scores[j + 1] = temp;
            }
        }
    }
    int Q1 = scores[n / 4];
    int Q2 = scores[n / 2];
    int Q3 = scores[3 * n / 4];
    printf("Survey Results:\n");
    printf("Average: %.2f\n", average);
    printf("Std Dev: %.2f\n", std_dev);
    printf("Q1: %d Q2: %d Q3: %d\n", Q1, Q2, Q3);
    printf("Distribution:\n");
    for (int s = 1; s <= 10; s++) {
        int count = 0;
        for (int i = 0; i < n; i++) {
            if (scores[i] == s) {
                count++;
            }
        }
        printf("%d | ", s);
        for (int k = 0; k < count; k++) {
            printf("#");
        }
        printf(" (%d)\n", count);
    }
}

void offering_menu(int offering_index, Faculty faculty[], int faculty_index,
                   Offering offerings[],Course courses[], int course_count,
                   Student students[], int student_count,
                   Request requests[], int *request_count,
                   Homework homeworks[], int *hw_count,
                   Exam exams[], int *exam_count,
                   SurveyScore surveys[], int survey_count,
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
        printf("6. Show survey results\n");
        printf("7. Go back\n");
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
                publish_homework(offering_index, offerings,
                            homeworks, hw_count, calendar);
                break;
            case 5:
                publish_exam(offering_index, offerings,
                         exams, exam_count, calendar);
                break;
            case 6:
                show_survey_results(offering_index, offerings, surveys, survey_count);
                break;
            case 7:
                running = 0;
                break;
            default:
                print_error("Invalid choice. Try again!\n");
        }
    }
}

void search_my_offerings(Offering offerings[], int matching_indexes[],
                         int matching_count, Course courses[], int course_count) {
    printf("1. Search by course name\n");
    printf("2. Search by course id\n");
    printf("3. Search by semester\n");
    printf("Enter an option: ");
    int choice;
    scanf("%d", &choice);

    printf("The phrase to search: ");
    char phrase[50];
    scanf("%s", phrase);

    int found = 0;
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
        if (choice == 1 && strstr(course_name, phrase) != NULL) {
            match = 1;
        }
        else if (choice == 2 && strstr(offerings[index].course_id, phrase) != NULL) {
            match = 1;
        }
        else if (choice == 3 && strstr(offerings[index].semester, phrase) != NULL) {
            match = 1;
        }
        if (match) {
            printf("| %s | %s | %s | %s | %d | %d | %s | %s |\n",
                course_name, offerings[index].course_id,
                offerings[index].faculty_id, offerings[index].semester,
                offerings[index].capacity, offerings[index].enrolled_count,
                offerings[index].department, offerings[index].place);
            found = 1;
        }
    }
    if (!found) {
        print_error("No offering found. Try again!\n");
    }
}

void my_offerings(int faculty_index, Faculty faculty[],
                  Offering offerings[], int *offering_count,
                  Course courses[], int course_count,
                  Student students[], int student_count,
                  Request requests[], int *request_count,
                  Homework homeworks[], int *hw_count,
                  Exam exams[], int *exam_count,
                  SurveyScore surveys[], int survey_count,
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
        print_error("You have no offerings.\n");
        return;
    }
    printf("|number | course name | course id | faculty id | semester | capacity "
           "| no. enrollments | department | place |\n");
    printf("|-------|-------------|-----------|------------|----------|----------"
           "|-----------------|------------|-------|\n");
    for (int i = 0; i < mine_count; i++) {
        int index = mine_indexes[i];
        char course_name[100] = "Unknown";
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
    }
    printf("1. Go to offering\n");
    printf("2. Search\n");
    printf("3. Go back\n");
    printf("Enter an option: ");
    int choice;
    scanf("%d", &choice);

    if (choice == 1) {
        printf("Enter offering number: ");
        int number;
        scanf("%d", &number);

        if (number < 1 || number > mine_count) {
            print_error("Invalid number.\n");
            return;
        }
        int offering_index = mine_indexes[number - 1];
        offering_menu(offering_index, faculty, faculty_index, offerings,courses,
                      course_count, students, student_count, requests,request_count,
                      homeworks, hw_count, exams, exam_count,
                      surveys, survey_count, calendar);
    }
    else if (choice == 2) {
        search_my_offerings(offerings, mine_indexes, mine_count, courses, course_count);
    }
}

void list_offerings_semester(Offering offerings[], int offering_count,
                             Course courses[], int course_count) {
    printf("Enter semester number: ");
    char semester[50];
    scanf("%s", semester);

    printf("| course name | course id | faculty id | semester | capacity "
           "| no. enrollments | department | place |\n");
    printf("|-------------|-----------|------------|----------|----------"
           "|-----------------|------------|-------|\n");
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
        print_error("No offering found for this semester.\n");
    }
}

void list_courses_faculty(Course courses[], int course_count) {
    printf("List of courses\n");
    printf("| course name | course id | units | prerequisites (separated by comma) "
           "| section | field | department |\n");
    printf("|-------------|-----------|-------|--------------------------------------"
           "|---------|-------|------------|\n");
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
        print_error("Offering period isn't active.\n");
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
        print_error("Course not found.\n");
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
        print_error("Invalid capacity.\n");
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
    print_success("Sent request to admin.\n");
    printf("Press any key to go to offerings...\n");
    getch();
}

void faculty_dashboard(int faculty_index,Faculty faculty[],
                       Offering offerings[], int *offering_count,
                       Course courses[], int course_count,
                       Request requests[], int *request_count,
                       Student students[], int student_count,
                       Homework homeworks[], int *hw_count,
                       Exam exams[], int *exam_count,
                       SurveyScore surveys[], int survey_count,
                       Calendar *calendar) {
    int running = 1;
    while (running) {
        printf("Faculty\n");
        printf("%s, %s %s!\n", get_greeting(), faculty[faculty_index].first_name,
               faculty[faculty_index].last_name);
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
                         requests, request_count,homeworks, hw_count,
                         exams, exam_count, surveys, survey_count, calendar);
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
            if (confirm_logout()) {
                running = 0;
            }
            break;
        default:
            print_error("Invalid choice. Try again!\n");
        }
    }
}