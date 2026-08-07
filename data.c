//
// Created by intel one on 7/9/2026.
//

#include <stdio.h>
#include <string.h>
#include "data.h"
#include "utilities.h"

void save_students(Student students[], int count) {
    FILE *f = fopen("../data/students.json", "w");
    if (f == NULL) {
        printf("Error opening data/students.json\n");
        return;
    }
    fprintf(f, "[\n");
    for (int i = 0; i < count; i++) {
        fprintf(f, " {\n");
        fprintf(f, " \"first_name\": \"%s\", \n", students[i].first_name);
        fprintf(f, " \"last_name\": \"%s\", \n", students[i].last_name);
        fprintf(f, " \"student_id\": \"%s\", \n", students[i].student_id);
        fprintf(f, " \"entrance_year\": %d, \n", students[i].entrance_year);
        fprintf(f, " \"national_code\": \"%s\", \n", students[i].national_code);
        fprintf(f, " \"field\": \"%s\", \n", students[i].field);
        fprintf(f, " \"department\": \"%s\", \n", students[i].department);
        fprintf(f, " \"section\": \"%s\", \n", students[i].section);
        fprintf(f, " \"mentor\": \"%s\", \n", students[i].mentor);
        fprintf(f, " \"password\": \"%s\", \n", students[i].password);
        fprintf(f ," \"birthplace\": \"%s\", \n", students[i].security.birthplace);
        fprintf(f, " \"first_school\": \"%s\", \n", students[i].security.first_school);
        fprintf(f, " \"first_book\": \"%s\", \n", students[i].security.first_book);
        fprintf(f, " \"bike_color\": \"%s\", \n", students[i].security.bike_color);
        fprintf(f, " \"thesis_title\": \"%s\", \n", students[i].phd_thesis.title);
        fprintf(f, " \"thesis_abstract\": \"%s\", \n", students[i].phd_thesis.abstract);
        fprintf(f, " \"thesis_citations\": %d, \n", students[i].phd_thesis.citations);
        fprintf(f, " \"enrollments\": [\n");
        for (int j = 0; j < students[i].enrollment_count; j++) {
            fprintf(f, " {\"semester\": \"%s\", \"course_id\": \"%s\", \"grade\": %.2f}",
                students[i].enrollments[j].semester,
                students[i].enrollments[j].course_id,
                students[i].enrollments[j].grade);
            if (j < students[i].enrollment_count - 1) {
                fprintf(f, ",\n");
            }
            else {
                fprintf(f, "\n");
            }
        }
        fprintf(f, " ]\n");
        fprintf(f, " }");
        if (i < count - 1) {
            fprintf(f, ",\n");
        }
        else {
            fprintf(f, "\n");
        }
    }
    fprintf(f, "]\n");
    fclose(f);
}

int load_students(Student students[], int max_count) {
    FILE *f = fopen("../data/students.json", "r");
    if (f == NULL) {
        printf("Error opening data/students.json\n");
        return 0;
    }
    int count = -1;
    char line[300];
    while (fgets(line, sizeof(line), f) != NULL) {
        if (strstr(line, "\"first_name\"") != NULL) {
            if (count + 1 >= max_count) {
                break;
            }
            count++;
            students[count].enrollment_count = 0;
            students[count].phd_thesis.title[0] = '\0';
            students[count].phd_thesis.abstract[0] = '\0';
            students[count].phd_thesis.citations = 0;
            extract_string_value(line, "first_name", students[count].first_name);
        }
        else if (strstr(line, "\"last_name\"") != NULL) {
            extract_string_value(line, "last_name", students[count].last_name);
        }
        else if (strstr(line, "\"student_id\"") != NULL) {
            extract_string_value(line, "student_id", students[count].student_id);
        }
        else if (strstr(line, "\"entrance_year\"") != NULL) {
            students[count].entrance_year = (int) extract_number_value(line, "entrance_year");
        }
        else if (strstr(line, "\"national_code\"") != NULL) {
            extract_string_value(line, "national_code", students[count].national_code);
        }
        else if (strstr(line, "\"field\"") != NULL) {
            extract_string_value(line, "field", students[count].field);
        }
        else if (strstr(line, "\"department\"") != NULL) {
            extract_string_value(line, "department", students[count].department);
        }
        else if (strstr(line, "\"section\"") != NULL) {
            extract_string_value(line, "section", students[count].section);
        }
        else if (strstr(line, "\"mentor\"") != NULL) {
            extract_string_value(line, "mentor", students[count].mentor);
        }
        else if (strstr(line, "\"password\"") != NULL) {
            extract_string_value(line, "password", students[count].password);
        }
        else if (strstr(line, "\"birthplace\"") != NULL) {
            extract_string_value(line, "birthplace", students[count].security.birthplace);
        }
        else if (strstr(line, "\"first_school\"") != NULL) {
            extract_string_value(line, "first_school",students[count].security.first_school);
        }
        else if (strstr(line, "\"first_book\"") != NULL) {
            extract_string_value(line, "first_book",students[count].security.first_book);
        }
        else if (strstr(line, "\"bike_color\"") != NULL) {
            extract_string_value(line, "bike_color", students[count].security.bike_color);
        }
        else if (strstr(line, "\"thesis_title\"") != NULL) {
            extract_string_value(line, "thesis_title", students[count].phd_thesis.title);
        }
        else if (strstr(line, "\"thesis_abstract\"") != NULL) {
            extract_string_value(line, "thesis_abstract", students[count].phd_thesis.abstract);
        }
        else if (strstr(line, "\"thesis_citations\"") != NULL) {
            students[count].phd_thesis.citations = (int) extract_number_value(line, "thesis_citations");
        }
        else if (strstr(line, "\"course_id\"") != NULL && strstr(line, "\"semester\"") != NULL) {
            int j = students[count].enrollment_count;
            extract_string_value(line, "semester", students[count].enrollments[j].semester);
            extract_string_value(line, "course_id", students[count].enrollments[j].course_id);
            students[count].enrollments[j].grade = extract_number_value(line, "grade");
            students[count].enrollment_count++;
        }
    }
    fclose(f);
    return ++count;
}

void save_faculty(Faculty faculty[], int count) {
    FILE *f = fopen("../data/faculty.json", "w");
    if (f == NULL) {
        printf("Error opening data/faculty.json\n");
        return;
    }
    fprintf(f, "[\n");
    for (int i = 0; i < count; i++) {
        fprintf(f, " {\n");
        fprintf(f, " \"first_name\": \"%s\", \n", faculty[i].first_name);
        fprintf(f, " \"last_name\": \"%s\", \n", faculty[i].last_name);
        fprintf(f, " \"faculty_id\": \"%s\", \n", faculty[i].faculty_id);
        fprintf(f, " \"entrance_year\": %d, \n", faculty[i].entrance_year);
        fprintf(f, " \"national_code\": \"%s\", \n", faculty[i].national_code);
        fprintf(f, " \"field\": \"%s\", \n", faculty[i].field);
        fprintf(f, " \"department\": \"%s\", \n", faculty[i].department);
        fprintf(f, " \"last_degree\": \"%s\", \n", faculty[i].last_degree);
        fprintf(f, " \"password\": \"%s\" \n", faculty[i].password);
        fprintf(f, " }");
        if (i < count - 1) {
            fprintf(f, ",\n");
        }
        else {
            fprintf(f, "\n");
        }
    }
    fprintf(f, "]\n");
    fclose(f);
}

int load_faculty(Faculty faculty[], int max_count) {
    FILE *f = fopen("../data/faculty.json", "r");
    if (f == NULL) {
        printf("Error opening data/faculty.json\n");
        return 0;
    }
    int count = -1;
    char line[300];
    while (fgets(line, sizeof(line), f) != NULL) {
        if (strstr(line, "\"first_name\"") != NULL) {
            if (count + 1 >= max_count) {
                break;
            }
            count++;
            extract_string_value(line, "first_name", faculty[count].first_name);
        }
        else if (strstr(line, "\"last_name\"") != NULL) {
            extract_string_value(line, "last_name", faculty[count].last_name);
        }
        else if (strstr(line, "\"faculty_id\"") != NULL) {
            extract_string_value(line, "faculty_id", faculty[count].faculty_id);
        }
        else if (strstr(line, "\"entrance_year\"") != NULL) {
            faculty[count].entrance_year = (int) extract_number_value(line, "entrance_year");
        }
        else if (strstr(line, "\"national_code\"") != NULL) {
            extract_string_value(line, "national_code", faculty[count].national_code);
        }
        else if (strstr(line, "\"field\"") != NULL) {
            extract_string_value(line, "field", faculty[count].field);
        }
        else if (strstr(line, "\"department\"") != NULL) {
            extract_string_value(line, "department", faculty[count].department);
        }
        else if (strstr(line, "\"last_degree\"") != NULL) {
            extract_string_value(line, "last_degree", faculty[count].last_degree);
        }
        else if (strstr(line, "\"password\"") != NULL) {
            extract_string_value(line, "password", faculty[count].password);
        }
    }
    fclose(f);
    return ++count;
}

void save_courses(Course courses[], int count) {
    FILE *f = fopen("../data/courses.json", "w");
    if (f == NULL) {
        printf("Error opening data/courses.json\n");
        return;
    }
    fprintf(f, "[\n");
    for (int i = 0; i < count; i++) {
        fprintf(f, " {\n");
        fprintf(f, " \"name\": \"%s\", \n", courses[i].name);
        fprintf(f, " \"course_id\": \"%s\", \n", courses[i].course_id);
        fprintf(f, " \"units\": %d, \n", courses[i].units);
        fprintf(f, " \"section\": \"%s\", \n", courses[i].section);
        fprintf(f, " \"field\": \"%s\", \n", courses[i].field);
        fprintf(f, " \"department\": \"%s\", \n", courses[i].department);
        fprintf(f, " \"prerequisites\": [");
        for (int j = 0; j < courses[i].prereq_count; j++) {
            fprintf(f, "\"%s\"", courses[i].prerequisites[j]);
            if (j < courses[i].prereq_count - 1) {
                fprintf(f, ", ");
            }
        }
        fprintf(f, "]\n");
        fprintf(f, " }");
        if (i < count - 1) {
            fprintf(f, ",\n");
        }
        else {
            fprintf(f, "\n");
        }
    }
    fprintf(f, "]\n");
    fclose(f);
}

int load_courses(Course courses[], int max_count) {
    FILE *f = fopen("../data/courses.json", "r");
    if (f == NULL) {
        printf("Error opening data/courses.json\n");
        return 0;
    }
    int count = -1;
    char line[300];
    while (fgets(line, sizeof(line), f) != NULL) {
        if (strstr(line, "\"name\"") != NULL) {
            if (count + 1 >= max_count) {
                break;
            }
            count++;
            extract_string_value(line, "name", courses[count].name);
        }
        else if (strstr(line, "\"course_id\"") != NULL) {
            extract_string_value(line, "course_id", courses[count].course_id);
        }
        else if (strstr(line, "\"units\"") != NULL) {
            courses[count].units = (int) extract_number_value(line, "units");
        }
        else if (strstr(line, "\"section\"") != NULL) {
            extract_string_value(line, "section", courses[count].section);
        }
        else if (strstr(line, "\"field\"") != NULL) {
            extract_string_value(line, "field", courses[count].field);
        }
        else if (strstr(line, "\"department\"") != NULL) {
            extract_string_value(line, "department", courses[count].department);
        }
        else if (strstr(line, "\"prerequisites\"") != NULL) {
            courses[count].prereq_count = extract_string_array(line, courses[count].prerequisites);
        }
    }
    fclose(f);
    return ++count;
}

void save_offerings(Offering offerings[], int count) {
    FILE *f = fopen("../data/offerings.json", "w");
    if (f == NULL) {
        printf("Error opening data/offerings.json\n");
        return;
    }
    fprintf(f, "[\n");
    for (int i = 0; i < count; i++) {
        fprintf(f, " {\n");
        fprintf(f, " \"course_id\": \"%s\", \n", offerings[i].course_id);
        fprintf(f, " \"faculty_id\": \"%s\", \n", offerings[i].faculty_id);
        fprintf(f, " \"semester\": \"%s\", \n", offerings[i].semester);
        fprintf(f, " \"capacity\": %d, \n", offerings[i].capacity);
        fprintf(f, " \"enrolled_count\": %d, \n", offerings[i].enrolled_count);
        fprintf(f, " \"department\": \"%s\", \n", offerings[i].department);
        fprintf(f, " \"place\": \"%s\" \n", offerings[i].place);
        fprintf(f, " }");
        if (i < count - 1) {
            fprintf(f, ",\n");
        }
        else {
            fprintf(f, "\n");
        }
    }
    fprintf(f, "]\n");
    fclose(f);
}

int load_offerings(Offering offerings[], int max_count) {
    FILE *f = fopen("../data/offerings.json", "r");
    if (f == NULL) {
        printf("Error opening data/offerings.json\n");
        return 0;
    }
    int count = -1;
    char line[300];
    while (fgets(line, sizeof(line), f) != NULL) {
        if (strstr(line, "\"course_id\"") != NULL) {
            if (count + 1 >= max_count) {
                break;
            }
            count++;
            extract_string_value(line, "course_id", offerings[count].course_id);
        }
        else if (strstr(line, "\"faculty_id\"") != NULL) {
            extract_string_value(line, "faculty_id", offerings[count].faculty_id);
        }
        else if (strstr(line, "\"semester\"") != NULL) {
            extract_string_value(line, "semester", offerings[count].semester);
        }
        else if (strstr(line, "\"capacity\"") != NULL) {
            offerings[count].capacity = (int) extract_number_value(line, "capacity");
        }
        else if (strstr(line, "\"enrolled_count\"") != NULL) {
            offerings[count].enrolled_count = (int) extract_number_value(line, "enrolled_count");
        }
        else if (strstr(line, "\"department\"") != NULL) {
            extract_string_value(line, "department", offerings[count].department);
        }
        else if (strstr(line, "\"place\"") != NULL) {
            extract_string_value(line, "place", offerings[count].place);
        }
    }
    fclose(f);
    return ++count;
}

void save_calendar(Calendar cal) {
    FILE *f = fopen("../data/calendar.json", "w");
    if (f == NULL) {
        printf("Error opening data/calendar.json\n");
        return;
    }
    fprintf(f, "{\n");
    fprintf(f, " \"offering_active\": %d, \n", cal.offering_active);
    fprintf(f, " \"unit_selection_active\": %d, \n", cal.unit_selection_active );
    fprintf(f, " \"class_exam_active\": %d, \n", cal.class_exam_active );
    fprintf(f, " \"grade_recording_active\": %d\n", cal.grade_recording_active );
    fprintf(f, "}\n");
    fclose(f);
}

Calendar load_calendar() {
    Calendar cal;
    cal.offering_active = false;
    cal.unit_selection_active = false;
    cal.class_exam_active = false;
    cal.grade_recording_active = false;

    FILE *f = fopen("../data/calendar.json", "r");
    if (f == NULL) {
        return cal;
    }
    char line[300];
    while (fgets(line, sizeof(line), f) != NULL) {
        if (strstr(line, "\"offering_active\"") != NULL) {
            cal.offering_active = (int) extract_number_value(line, "offering_active");
        }
        else if (strstr(line, "\"unit_selection_active\"") != NULL) {
            cal.unit_selection_active = (int) extract_number_value(line, "unit_selection_active");
        }
        else if (strstr(line, "\"class_exam_active\"") != NULL) {
            cal.class_exam_active = (int) extract_number_value(line, "class_exam_active");
        }
        else if (strstr(line, "\"grade_recording_active\"") != NULL) {
            cal.grade_recording_active = (int) extract_number_value(line, "grade_recording_active");
        }
    }
    fclose(f);
    return cal;
}

void save_requests(Request requests[], int count) {
    FILE *f = fopen("../data/requests.json", "w");
    if (f == NULL) {
        printf("Error opening data/requests.json\n");
        return;
    }
    fprintf(f, "[\n");
    for (int i = 0; i < count; i++) {
        fprintf(f, "{\n");
        fprintf(f, "\"id\": %d, \n", requests[i].id);
        fprintf(f, "\"type\": %d, \n", requests[i].type);
        fprintf(f, "\"faculty_id\": \"%s\", \n", requests[i].faculty_id);
        fprintf(f, "\"course_id\": \"%s\", \n", requests[i].course_id);
        fprintf(f, "\"semester\": \"%s\", \n", requests[i].semester);
        fprintf(f, "\"extra_cap\": %d, \n", requests[i].extra_cap);
        fprintf(f, "\"place\": \"%s\", \n", requests[i].place);
        fprintf(f, "\"status\": %d \n", requests[i].status);
        fprintf(f, " }");
        if (i < count - 1) {
            fprintf(f, ",\n");
        }
        else {
            fprintf(f, "\n");
        }
    }
    fprintf(f, "]\n");
    fclose(f);
}

int load_requests(Request requests[], int max_count) {
    FILE *f = fopen("../data/requests.json", "r");
    if (f == NULL) {
        printf("Error opening data/requests.json\n");
        return 0;
    }
    int count = -1;
    char line[300];
    while (fgets(line, sizeof(line), f) != NULL) {
        if (strstr(line, "\"id\"") != NULL) {
            if (count + 1 >= max_count) {
                break;
            }
            count++;
            requests[count].id = (int) extract_number_value(line, "id");
        }
        else if (strstr(line, "\"type\"") != NULL) {
            requests[count].type = (RequestType) extract_number_value(line, "type");
        }
        else if (strstr(line, "\"faculty_id\"") != NULL) {
            extract_string_value(line, "faculty_id", requests[count].faculty_id);
        }
        else if (strstr(line, "\"course_id\"") != NULL) {
            extract_string_value(line, "course_id", requests[count].course_id);
        }
        else if (strstr(line, "\"semester\"") != NULL) {
            extract_string_value(line, "semester", requests[count].semester);
        }
        else if (strstr(line, "\"extra_cap\"") != NULL) {
            requests[count].extra_cap = (int) extract_number_value(line, "extra_cap");
        }
        else if (strstr(line, "\"place\"") != NULL) {
            extract_string_value(line, "place", requests[count].place);
        }
        else if (strstr(line, "\"status\"") != NULL) {
            requests[count].status = (RequestStatus) extract_number_value(line, "status");
        }
    }
    fclose(f);
    return ++count;
}

void save_surveys(SurveyScore surveys[], int count) {
    FILE *f = fopen("../data/surveys.json", "w");
    if (f == NULL) {
        printf("Error opening data/surveys.json\n");
        return;
    }
    fprintf(f, "[\n");
    for (int i = 0; i < count; i++)
    {
        fprintf(f, "{\"student_id\": \"%s\", \"offering_id\": \"%s\", \"score\": %d}",
                surveys[i].student_id, surveys[i].offering_id, surveys[i].score);
        if (i < count - 1) {
            fprintf(f, ",\n");
        }
        else {
            fprintf(f, "\n");
        }
    }
    fprintf(f, "]\n");
    fclose(f);
}

int load_surveys(SurveyScore surveys[], int max_count) {
    FILE *f = fopen("../data/surveys.json", "r");
    if (f == NULL) {
        printf("Error opening data/surveys.json\n");
        return 0;
    }
    int count = -1;
    char line[300];
    while (fgets(line, sizeof(line), f) != NULL) {
        if (strstr(line, "\"student_id\"") != NULL) {
            if (count + 1 >= max_count) {
                break;
            }
            count++;
            extract_string_value(line, "student_id", surveys[count].student_id);
            extract_string_value(line, "offering_id", surveys[count].offering_id);
            surveys[count].score = (int) extract_number_value(line, "score");
        }
    }
    fclose(f);
    return ++count;
}

void save_homeworks(Homework homeworks[], int count) {
    FILE *f = fopen("../data/homeworks.json", "w");
    if (f == NULL) {
        printf("Error opening data/homeworks.json\n");
        return;
    }
    fprintf(f, "[\n");
    for (int i = 0; i < count; i++) {
        fprintf(f, " {\n");
        fprintf(f, "  \"offering_id\": \"%s\",\n", homeworks[i].offering_id);
        fprintf(f, "  \"title\": \"%s\",\n", homeworks[i].title);
        fprintf(f, "  \"total_score\": %.2f,\n", homeworks[i].total_score);
        fprintf(f, "  \"num_questions\": %d,\n", homeworks[i].num_questions);
        fprintf(f, "  \"questions\": [\n");
        for (int j = 0; j < homeworks[i].num_questions; j++) {
            fprintf(f, "   {\"text\": \"%s\", \"option_a\": \"%s\", \"option_b\": \"%s\", "
                    "\"option_c\": \"%s\", \"option_d\": \"%s\", \"correct\": \"%c\"}",
                    homeworks[i].questions[j].text, homeworks[i].questions[j].option_a,
                    homeworks[i].questions[j].option_b, homeworks[i].questions[j].option_c,
                    homeworks[i].questions[j].option_d, homeworks[i].questions[j].correct);
            if (j < homeworks[i].num_questions - 1) {
                fprintf(f, ",\n");
            }
            else {
                fprintf(f, "\n");
            }
        }
        fprintf(f, "  ]\n");
        fprintf(f, " }");
        if (i < count - 1) {
            fprintf(f, ",\n");
        }
        else {
            fprintf(f, "\n");
        }
    }
    fprintf(f, "]\n");
    fclose(f);
}

int load_homeworks(Homework homeworks[], int max_count) {
    FILE *f = fopen("../data/homeworks.json", "r");
    if (f == NULL) {
        printf("Error opening data/homeworks.json\n");
        return 0;
    }
    int count = -1;
    char line[300];
    while (fgets(line, sizeof(line), f) != NULL) {
        if (strstr(line, "\"offering_id\"") != NULL) {
            if (count + 1 >= max_count) {
                break;
            }
            count++;
            homeworks[count].num_questions = 0;
            extract_string_value(line, "offering_id", homeworks[count].offering_id);
        }
        else if (strstr(line, "\"title\"") != NULL) {
            extract_string_value(line, "title", homeworks[count].title);
        }
        else if (strstr(line, "\"total_score\"") != NULL) {
            homeworks[count].total_score = extract_number_value(line, "total_score");
        }
        else if (strstr(line, "\"text\"") != NULL) {
            int q = homeworks[count].num_questions;
            extract_string_value(line, "text", homeworks[count].questions[q].text);
            extract_string_value(line, "option_a", homeworks[count].questions[q].option_a);
            extract_string_value(line, "option_b", homeworks[count].questions[q].option_b);
            extract_string_value(line, "option_c", homeworks[count].questions[q].option_c);
            extract_string_value(line, "option_d", homeworks[count].questions[q].option_d);
            char temp[10];
            extract_string_value(line, "correct", temp);
            homeworks[count].questions[q].correct = temp[0];
            homeworks[count].num_questions++;
        }
    }
    fclose(f);
    return ++count;
}

void save_exams(Exam exams[], int count) {
    FILE *f = fopen("../data/exams.json", "w");
    if (f == NULL) {
        printf("Error opening data/exams.json\n");
        return;
    }
    fprintf(f, "[\n");
    for (int i = 0; i < count; i++) {
        fprintf(f, " {\n");
        fprintf(f, "  \"offering_id\": \"%s\",\n", exams[i].offering_id);
        fprintf(f, "  \"title\": \"%s\",\n", exams[i].title);
        fprintf(f, "  \"total_score\": %.2f,\n", exams[i].total_score);
        fprintf(f, "  \"num_questions\": %d,\n", exams[i].num_questions);
        fprintf(f, "  \"questions\": [\n");
        for (int j = 0; j < exams[i].num_questions; j++) {
            fprintf(f, "   {\"type\": %d, \"text\": \"%s\",",
                    exams[i].questions[j].type,exams[i].questions[j].text);
            if (exams[i].questions[j].type == MCQ) {
                fprintf(f, "\"option_a\": \"%s\", \"option_b\": \"%s\", "
                        "\"option_c\": \"%s\", \"option_d\": \"%s\", \"correct\": \"%c\"}",
                        exams[i].questions[j].option_a, exams[i].questions[j].option_b,
                        exams[i].questions[j].option_c, exams[i].questions[j].option_d,
                        exams[i].questions[j].correct);
            }
            else {
                fprintf(f, "\"reference_answer\": \"%s\"}",
                        exams[i].questions[j].reference_answer);
            }
            if (j < exams[i].num_questions - 1) {
                fprintf(f, ",\n");
            }
            else {
                fprintf(f, "\n");
            }
        }
        fprintf(f, "  ]\n");
        fprintf(f, " }");
        if (i < count - 1) {
            fprintf(f, ",\n");
        }
        else {
            fprintf(f, "\n");
        }
    }
    fprintf(f, "]\n");
    fclose(f);
}

int load_exams(Exam exams[], int max_count) {
    FILE *f = fopen("../data/exams.json", "r");
    if (f == NULL) {
        printf("Error opening data/exams.json\n");
        return 0;
    }
    int count = -1;
    char line[300];
    while (fgets(line, sizeof(line), f) != NULL) {
        if (strstr(line, "\"offering_id\"") != NULL) {
            if (count + 1 >= max_count) {
                break;
            }
            count++;
            exams[count].num_questions = 0;
            extract_string_value(line, "offering_id", exams[count].offering_id);
        }
        else if (strstr(line, "\"title\"") != NULL) {
            extract_string_value(line, "title", exams[count].title);
        }
        else if (strstr(line, "\"total_score\"") != NULL) {
            exams[count].total_score = extract_number_value(line, "total_score");
        }
        else if ( strstr(line, "\"type\"") != NULL && strstr(line, "\"text\"") != NULL) {
            int q = exams[count].num_questions;
            exams[count].questions[q].type = (QuestionType) extract_number_value(line, "type");
            extract_string_value(line, "text", exams[count].questions[q].text);
            if (exams[count].questions[q].type == MCQ) {
                extract_string_value(line, "option_a", exams[count].questions[q].option_a);
                extract_string_value(line, "option_b", exams[count].questions[q].option_b);
                extract_string_value(line, "option_c", exams[count].questions[q].option_c);
                extract_string_value(line, "option_d", exams[count].questions[q].option_d);
                char temp[10];
                extract_string_value(line, "correct", temp);
                exams[count].questions[q].correct = temp[0];
            }
            else {
                extract_string_value(line, "reference_answer", exams[count].questions[q].reference_answer);
            }
            exams[count].num_questions++;
        }
    }
    fclose(f);
    return ++count;
}
