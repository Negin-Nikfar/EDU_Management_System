//
// Created by intel one on 7/9/2026.
//

#ifndef EDU_PROJECT_DATA_H
#define EDU_PROJECT_DATA_H

#include <stdbool.h>

typedef struct SecurityAnswers {
    char birthplace[100];
    char first_school[100];
    char first_book[100];
    char bike_color[100];
} SecurityAnswers;

typedef struct EnrolledOffering {
    char semester[50];
    char course_id[50];
    float grade;
} EnrolledOffering;

typedef struct Thesis {
    char title[150];
    char abstract[1000];
    int  citations;
} Thesis;

typedef struct Student {
    char first_name[50];
    char last_name[50];
    char student_id[20];
    int  entrance_year;
    char national_code[20];
    char field[100];
    char department[100];
    char section[10];
    char mentor[100];
    char password[50];
    SecurityAnswers security;
    EnrolledOffering enrollments[50];
    int  enrollment_count;
    Thesis phd_thesis;
} Student;

typedef struct Faculty {
    char first_name[50];
    char last_name[50];
    char faculty_id[20];
    int  entrance_year;
    char national_code[20];
    char field[100];
    char department[100];
    char last_degree[50];
    char password[50];
} Faculty;

typedef struct Course {
    char name[50];
    char course_id[50];
    int  units;
    char prerequisites[10][20];
    int  prereq_count;
    char section[10];
    char field[100];
    char department[100];
} Course;

typedef struct Offering {
    char course_id[50];
    char faculty_id[50];
    char semester[50];
    int  capacity;
    int  enrolled_count;
    char department[100];
    char place[100];
} Offering;

typedef enum RequestType {
    OFFER_COURSE,
    REMOVE_OFFERING,
    ADD_CAPACITY
} RequestType;

typedef enum RequestStatus {
    PENDING,
    APPROVED,
    REJECTED
} RequestStatus;

typedef struct Request {
    int  id;
    RequestType type;
    char faculty_id[50];
    char course_id[50];
    char semester[50];
    int  extra_cap;
    char place[100];
    RequestStatus status;
} Request;

typedef struct Calendar {
    bool offering_active;
    bool unit_selection_active;
    bool class_exam_active;
    bool grade_recording_active;
} Calendar;

typedef struct MCQuestion {
    char text[100];
    char option_a[100];
    char option_b[100];
    char option_c[100];
    char option_d[100];
    char correct;
} MCQuestion;

typedef enum QuestionType {
    MCQ,
    DESCRIPTIVE
} QuestionType;

typedef struct ExamQuestion {
    QuestionType type;
    char text[100];
    char option_a[100];
    char option_b[100];
    char option_c[100];
    char option_d[100];
    char correct;
    char reference_answer[200];
} ExamQuestion;

typedef struct Homework {
    char offering_id[20];
    char title[100];
    float total_score;
    MCQuestion questions[20];
    int  num_questions;
} Homework;

typedef struct Exam {
    char offering_id[20];
    char title[100];
    float total_score;
    ExamQuestion questions[20];
    int  num_questions;
} Exam;

typedef struct SurveyScore {
    char student_id[20];
    char offering_id[50];
    int  score;
} SurveyScore;

void save_students(Student students[], int count);
int load_students(Student students[], int max_count);

void save_faculty(Faculty faculty[], int count);
int load_faculty(Faculty faculty[], int max_count);

void save_courses(Course courses[], int count);
int load_courses(Course courses[], int max_count);

void save_offerings(Offering offerings[], int count);
int load_offerings(Offering offerings[], int max_count);

void save_calendar(Calendar cal);
Calendar load_calendar();

void save_requests(Request requests[], int count);
int load_requests(Request requests[], int max_count);

#endif //EDU_PROJECT_DATA_H
