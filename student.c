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
    printf("Enter an option: ");
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
        print_error("No offerings found.\n");
    }
}

void enroll_in_course(int student_index, Student students[], int student_count,
                      Offering offerings[], int matching_indexes[], int matching_count,
                      Course courses[], int course_count, Calendar *calendar) {
    if (!calendar->unit_selection_active) {
        print_error("Unit selection isn't active.\n");
        return;
    }
    printf("Enter offering number: ");
    int number;
    scanf("%d", &number);

    if (number < 1 || number > matching_count) {
        print_error("Invalid offering number.\n");
        return;
    }
    int offering_index = matching_indexes[number - 1];
    if (offerings[offering_index].enrolled_count >= offerings[offering_index].capacity) {
        print_error("No capacity available.\n");
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
        print_error("Prerequisites not met.\n");
        return;
    }
    for (int i = 0; i < students[student_index].enrollment_count; i++) {
        if (strcmp(students[student_index].enrollments[i].course_id, offerings[offering_index].course_id) == 0 &&
            strcmp(students[student_index].enrollments[i].semester, offerings[offering_index].semester) == 0) {
            print_error("You are already enrolled in this course.\n");
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
    print_success("Enrolled successfully.\n");
}

void enroll_thesis(int student_index, Student students[], int student_count,
                   Offering offerings[], int *offering_count, Calendar *calendar) {
    if (strcmp(students[student_index].section, "PhD") != 0) {
        print_error("Only PhD students can enroll in the thesis course.\n");
        return;
    }
    if (!calendar->unit_selection_active) {
        print_error("Unit selection isn't active.\n");
        return;
    }
    printf("Enter semester number: ");
    char semester_number[50];
    scanf("%s", semester_number);

    int thesis_offering_index = -1;
    for (int i = 0; i < *offering_count; i++) {
        if (strcmp(offerings[i].course_id, "THESIS") == 0 &&
            strcmp(offerings[i].faculty_id, students[student_index].mentor) == 0 &&
            strcmp(offerings[i].semester, semester_number) == 0) {
            thesis_offering_index = i;
            break;
            }
    }
    if (thesis_offering_index == -1) {
        print_error("Your mentor hasn't offered the thesis this semester.\n");
        return;
    }
    for (int i = 0; i < students[student_index].enrollment_count; i++) {
        if (strcmp(students[student_index].enrollments[i].course_id, "THESIS") == 0 &&
            strcmp(students[student_index].enrollments[i].semester, semester_number) == 0) {
            print_error("You are already enrolled in a thesis course this semester.\n");
            return;
        }
    }
    int enrolled_index = students[student_index].enrollment_count;
    strcpy(students[student_index].enrollments[enrolled_index].semester, semester_number);
    strcpy(students[student_index].enrollments[enrolled_index].course_id, "THESIS");
    students[student_index].enrollments[enrolled_index].grade = -1;
    students[student_index].enrollment_count++;
    offerings[thesis_offering_index].enrolled_count++;
    save_students(students, student_count);
    save_offerings(offerings, *offering_count);
    print_success("Enrolled in thesis successfully!\n");
}

void withdraw_course(int student_index, Student students[], int student_count,
                     Offering offerings[], int matching_indexes[], int matching_count,
                     Calendar *calendar) {
    if (!calendar->unit_selection_active) {
        print_error("Unit selection isn't active.\n");
        return;
    }
    printf("Enter offering number: ");
    int number;
    scanf("%d", &number);

    if (number < 1 || number > matching_count) {
        print_error("Invalid offering number.\n");
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
        print_error("You aren't enrolled in this course.\n");
        return;
    }
    for (int i = enrolled_index; i < students[student_index].enrollment_count - 1; i++) {
        students[student_index].enrollments[i] = students[student_index].enrollments[i + 1];
    }
    students[student_index].enrollment_count--;
    offerings[offering_index].enrolled_count--;
    save_students(students, student_count);
    print_success("Withdrawn successfully.\n");
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
        print_error("No offerings found for this semester.\n");
        return;
    }
    printf("List of offerings - %s\n", semester);
    printf("| number | course name | course id | faculty name | semester | capacity "
           "| no. enrollments | department | place |\n");
    printf("|--------|-------------|-----------|--------------|----------|----------"
           "|-----------------|------------|-------|\n");
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
    printf("3. Withdraw course\n");
    printf("4. Go back\n");
    printf("Enter an option: ");
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
        print_error("No records for this semester.\n");
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
        char *passed = (s.enrollments[k].grade >= 10.0) ? "Yes" : "No";
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
    printf("|last name |%s |\n", s.last_name);
    printf("|national code |%s |\n", s.national_code);
    printf("|field |%s |\n", s.field);
    printf("|entrance year |%d |\n", s.entrance_year);
    printf("|section |%s |\n", s.section);
    printf("|mentor |%s |\n", s.mentor);
    printf("|department |%s |\n", s.department);

    float overall_gpa = calculate_gpa(s, NULL, courses, course_count);
    printf("|GPA |%.2f |\n", overall_gpa);

    if (strcmp(s.section, "PhD") == 0 && strlen(s.phd_thesis.title) > 0) {
        printf("|thesis title |%s |\n", s.phd_thesis.title);
        printf("|thesis abstract |%s |\n", s.phd_thesis.abstract);
        printf("|thesis citations |%d |\n", s.phd_thesis.citations);
    }

    printf("1. Go to semester\n");
    printf("2. Go back\n");
    printf("Enter an option: ");
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

void run_surveys_for_student(int student_index, Student students[], SurveyScore surveys[],
                             int *survey_count, Offering offerings[], int offering_count,
                             Course courses[], int course_count, char *last_semester) {
    Student s = students[student_index];
    for (int i = 0; i < s.enrollment_count; i++) {
        if (strcmp(s.enrollments[i].semester, last_semester) != 0) {
            continue;
        }
        int offering_index = -1;
        for (int j = 0; j < offering_count; j++) {
            if (strcmp(offerings[j].course_id, s.enrollments[i].course_id) == 0 &&
                strcmp(offerings[j].semester, last_semester) == 0) {
                offering_index = j;
                break;
            }
        }
        if (offering_index == -1) {
            continue;
        }
        char offering_id[160];
        sprintf(offering_id, "%s_%s_%s", offerings[offering_index].course_id,
                offerings[offering_index].faculty_id, offerings[offering_index].semester);
        int already_surveyed = 0;
        for (int k = 0; k < *survey_count; k++) {
            if (strcmp(surveys[k].student_id, s.student_id) == 0 &&
                strcmp(surveys[k].offering_id, offering_id) == 0) {
                already_surveyed = 1;
                break;
            }
        }
        if (already_surveyed == 1) {
            continue;
        }
        char course_name[100] = "Unknown";
        for (int j = 0; j < course_count; j++) {
            if (strcmp(courses[j].course_id, s.enrollments[i].course_id) == 0) {
                strcpy(course_name, courses[j].name);
                break;
            }
        }
        printf("Rate this course (1-10): %s\n", course_name);
        int score;
        scanf("%d", &score);

        while (score < 1 || score > 10) {
            print_warning("Invalid score. Try again: ");
            scanf("%d", &score);
        }
        strcpy(surveys[*survey_count].student_id, s.student_id);
        strcpy(surveys[*survey_count].offering_id, offering_id);
        surveys[*survey_count].score = score;
        (*survey_count)++;
    }
    save_surveys(surveys, *survey_count);
}

void submit_homework(Homework homeworks[], int hw_count,
                     Offering offerings[], int offering_count) {
    printf("Enter offering course id to see homeworks: ");
    char course_id[50];
    scanf("%s", course_id);

    printf("Enter semester number: ");
    char semester_number[50];
    scanf("%s", semester_number);

    int offering_index = -1;
    for (int j = 0; j < offering_count; j++) {
        if (strcmp(offerings[j].course_id, course_id) == 0 &&
            strcmp(offerings[j].semester, semester_number) == 0) {
            offering_index = j;
            break;
        }
    }
    if (offering_index == -1) {
        print_error("Offering not found.\n");
        return;
    }
    char offering_id[160];
    sprintf(offering_id, "%s_%s_%s", offerings[offering_index].course_id,
            offerings[offering_index].faculty_id, offerings[offering_index].semester);
    int hw_index = -1;
    for (int k = 0; k < hw_count; k++) {
        if (strcmp(homeworks[k].offering_id, offering_id) == 0) {
            hw_index = k;
            break;
        }
    }
    if (hw_index == -1) {
        print_error("No homework found for this offering.\n");
        return;
    }
    Homework *hw = &homeworks[hw_index];
    float total_earned = 0;
    float score_percentage_q = hw->total_score / (float) hw->num_questions;
    for (int i = 0; i < hw->num_questions; i++) {
        printf("%s\n", hw->questions[i].text);
        printf("a) %s\n", hw->questions[i].option_a);
        printf("b) %s\n", hw->questions[i].option_b);
        printf("c) %s\n", hw->questions[i].option_c);
        printf("d) %s\n", hw->questions[i].option_d);
        printf("Your answer: ");
        char answer;
        scanf(" %c", &answer);

        while (answer != 'a' && answer != 'b' && answer != 'c' && answer != 'd') {
            print_warning("Invalid answer. Try again: ");
            scanf(" %c", &answer);
        }
        if (answer == hw->questions[i].correct) {
            total_earned += score_percentage_q;
        }
    }
    printf("Your score: %.2f / %.2f\n", total_earned, hw->total_score);
}

void submit_exam(Exam exams[], int exam_count,
                 Offering offerings[], int offering_count) {
    printf("Enter offering course id to exams: ");
    char course_id[50];
    scanf("%s", course_id);

    printf("Enter semester number: ");
    char semester_number[50];
    scanf("%s", semester_number);

    int offering_index = -1;
    for (int j = 0; j < offering_count; j++) {
        if (strcmp(offerings[j].course_id, course_id) == 0 &&
            strcmp(offerings[j].semester, semester_number) == 0) {
            offering_index = j;
            break;
        }
    }
    if (offering_index == -1) {
        print_error("Offering not found.\n");
        return;
    }
    char offering_id[160];
    sprintf(offering_id, "%s_%s_%s", offerings[offering_index].course_id,
        offerings[offering_index].faculty_id, offerings[offering_index].semester);
    int exam_index = -1;
    for (int k = 0; k < exam_count; k++) {
        if (strcmp(exams[k].offering_id, offering_id) == 0) {
            exam_index = k;
            break;
        }
    }
    if (exam_index == -1) {
        print_error("No exam found for this offering.\n");
        return;
    }
    Exam *exam = &exams[exam_index];
    float total_earned = 0;
    float score_percentage_q = exam->total_score / exam->num_questions;
    int has_descriptive = 0;
    for (int i = 0; i < exam->num_questions; i++) {
        printf("%s\n", exam->questions[i].text);
        if (exam->questions[i].type == MCQ) {
            printf("a) %s\n", exam->questions[i].option_a);
            printf("b) %s\n", exam->questions[i].option_b);
            printf("c) %s\n", exam->questions[i].option_c);
            printf("d) %s\n", exam->questions[i].option_d);
            printf("Your answer: ");
            char answer;
            scanf(" %c", &answer);

            if (answer == exam->questions[i].correct) {
                total_earned += score_percentage_q;
            }
        }
        else {
            printf("Your answer: ");
            char answer[300];
            scanf(" %[^\n]", answer);

            has_descriptive = 1;
        }
    }
    printf("Your score so far: %.2f / %.2f\n", total_earned, exam->total_score);
    if (has_descriptive) {
        print_success("Answers submitted. Descriptive questions will be graded by the instructor.\n");
    }
    else {
        print_success("Answers submitted.\n");
    }
}

void student_dashboard(int student_index, Student students[], int student_count,
                       Offering offerings[], int *offering_count,
                       Course courses[], int course_count,
                       Faculty faculty[], int faculty_count,
                       Homework homeworks[], int hw_count,
                       Exam exams[], int exam_count,
                       SurveyScore surveys[], int *survey_count,
                       Calendar *calendar) {
    int running = 1;
    while (running) {
        printf("Student\n");
        printf("%s, %s!\n", get_greeting(), students[student_index].first_name);
        printf("1. Offerings\n");
        printf("2. Courses\n");
        printf("3. Report card\n");
        printf("4. Enroll in thesis (PhD)\n");
        printf("5. Course surveys\n");
        printf("6. Submit homework\n");
        printf("7. Submit exam\n");
        printf("8. Log out\n");
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
                enroll_thesis(student_index, students, student_count, offerings,
                          offering_count, calendar);
                break;
            case 5:
                printf("Enter last semester number: ");
                char last_semester[50];
                scanf("%s", last_semester);
                run_surveys_for_student(student_index, students, surveys, survey_count,
                                    offerings, *offering_count, courses, course_count, last_semester);
                break;
            case 6:
                submit_homework(homeworks, hw_count, offerings, *offering_count);
                break;
            case 7:
                submit_exam(exams, exam_count, offerings, *offering_count);
                break;
            case 8:
                if (confirm_logout()) {
                running = 0;
                }
                break;
            default:
                print_error("Invalid choice. Try again!\n");
        }
    }
}