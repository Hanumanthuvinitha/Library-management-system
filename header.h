#ifndef HEADER_H
#define HEADER_H

 #include <stdio.h>
#include <iostream>
#include <conio.h>
#include <string.h>
#include <stdlib.h>
#include <bits/stdc++.h>
#include <fstream> 
#include <time.h>

#define NAME_LEN 30
#define BOOK_NAME_LEN 80
#define DSGN_LEN 50

using namespace std;
//*************//
//date format for issue date...
typedef struct date_format{
    int day;
    int month;
    int year;
}DATE;

//***************//
//student information
typedef struct student_node{
    char stu_name[NAME_LEN];
    int stu_id;
    char stu_adm_num[8];
}STUDENT;

typedef struct student_tree{
    STUDENT* s_key;
    struct student_tree* left;
    struct student_tree* right;
    int height;
}STUDENT_TREE;

//***********//
//employee node
typedef struct emp_node{
    char emp_name[NAME_LEN];
    int emp_id;
    char emp_password[10];
    struct emp_node* next;
}EMPLOYEE;

//**************//
//book node
typedef struct book{
    int book_id;
    char book_name[BOOK_NAME_LEN];
    char author_name[NAME_LEN];
    int rack;
    int quantity;
}BOOK;

// avl tree for storing books data;
typedef struct book_tree{
    BOOK* b_key;
    struct book_tree* left;
    struct book_tree* right;
    int height;
}BOOK_TREE;

//**************//
//book issue information
typedef struct book_issue{
     int book_id;
    char book_name[BOOK_NAME_LEN];
    int stu_id;
    DATE issue_date;
    DATE expiry_date;
    struct book_issue* next;
}BOOK_ISSUE;

// avl tree for book issue data
typedef struct book_issue_tree{
    BOOK_ISSUE* head;
    struct book_issue_tree* left;
    struct book_issue_tree* right;
    int height;
}BOOK_ISSUE_TREE;

//*************//
//storing all root nodes
typedef struct node{
    STUDENT_TREE* s_node;
    BOOK_ISSUE_TREE* i_node;
    BOOK_TREE* b_node;
}ROOT_NODES;

//global variables
BOOK_TREE* books_root_node=NULL;
STUDENT_TREE* student_root=NULL;
BOOK_ISSUE_TREE* issue_root=NULL;
EMPLOYEE* emp_root=NULL;
int status_emp;
int status_user;
int userID;
int stu_dup_flag=0;
int book_dup_flag=0;
int issue_dup_flag=0;
char password[8];
//utility functions to store data about books available in library in avl tree
//book.cpp
BOOK_TREE* new_book_node(BOOK*);
int book_height(BOOK_TREE*);
int balance(BOOK_TREE*);
BOOK_TREE* llrotate(BOOK_TREE*);
BOOK_TREE* rrrotate(BOOK_TREE*);
BOOK_TREE* lrrotate(BOOK_TREE*);
BOOK_TREE* rlrotate(BOOK_TREE*);
BOOK_TREE* insert_node(BOOK_TREE*,BOOK*);
BOOK_TREE* balance_tree(BOOK_TREE*);
void show_books(BOOK_TREE*);

//student.cpp
STUDENT_TREE* new_student_node(STUDENT*);
int stu_tree_height(STUDENT_TREE*);
int balance_stu_tree(STUDENT_TREE*);
STUDENT_TREE* llrotate_stu_rec(STUDENT_TREE*);
STUDENT_TREE* rrrotate_stu_rec(STUDENT_TREE*);
STUDENT_TREE* lrrotate_stu_rec(STUDENT_TREE*);
STUDENT_TREE* rlrotate_stu_rec(STUDENT_TREE*);
STUDENT_TREE* insert_stu_node(STUDENT_TREE*,STUDENT*);
STUDENT_TREE* balance_student_tree(STUDENT_TREE*);
void show_students(STUDENT_TREE*);
STUDENT_TREE* inorder_succ(STUDENT_TREE*);
STUDENT_TREE* delete_leaf_node(STUDENT_TREE*,STUDENT_TREE*);

//book issue functions
//issue_book.cpp
BOOK_ISSUE* new_issue_node(int,char book_name[BOOK_NAME_LEN],int);
int delete_book_rec(BOOK_ISSUE*,int);
void split_date(char*,int&,int&,int& );
BOOK_ISSUE* add_issue_node(int,char*,int,char*,char*);
BOOK_ISSUE_TREE* new_issue_tree_node(BOOK_ISSUE*);
int add_to_issue_list(BOOK_ISSUE*,BOOK_ISSUE*);
int issue_tree_ht(BOOK_ISSUE_TREE*);
int balance_factor_issue(BOOK_ISSUE_TREE*);
BOOK_ISSUE_TREE*  ll_rotate_issue(BOOK_ISSUE_TREE*);
BOOK_ISSUE_TREE* rr_rotate_issue(BOOK_ISSUE_TREE*);
BOOK_ISSUE_TREE* lrrotate_issue(BOOK_ISSUE_TREE*);
BOOK_ISSUE_TREE* rlrotate_issue(BOOK_ISSUE_TREE*);
BOOK_ISSUE_TREE* insert_issue_node(BOOK_ISSUE_TREE*,BOOK_ISSUE*);
BOOK_ISSUE_TREE* balance_book_issue_tree(BOOK_ISSUE_TREE*);
BOOK_ISSUE_TREE* inorder_issue_succ(BOOK_ISSUE_TREE*);
BOOK_ISSUE_TREE* delete_leaf_node_issue(BOOK_ISSUE_TREE*,BOOK_ISSUE_TREE*);
BOOK_ISSUE_TREE* delete_issue_node(BOOK_ISSUE_TREE*,BOOK_ISSUE_TREE*);
void update_issue_file(int,int);
void update_expiry_date_in_file(int,int,BOOK_ISSUE*);

//emp_functions.cpp
//Utility functions to do Librarian responsibiliies
EMPLOYEE* add_to_list(EMPLOYEE* ,EMPLOYEE* );
void show_emp(EMPLOYEE*);
STUDENT_TREE* add_user(char* ,int, char*);
BOOK_TREE* insert_new_book(int,char*,char*,int,int);
int verify_book_details(BOOK_TREE*,int,char*);
void issue_book(int,char*,int);
void return_book(BOOK_ISSUE_TREE*,int,int);
void update_edate(BOOK_ISSUE*,int);
void renew_book(BOOK_ISSUE_TREE*,int,int);
STUDENT_TREE* delete_student_rec(STUDENT_TREE*,int,char*);
void update_student_file(int);

//student_functions.cpp
void search_book_by_book_id(BOOK_TREE*,int);
int search_book_by_bname(BOOK_TREE*,char*);
int search_book_by_aname(BOOK_TREE*,char*);
void show_issue_list(BOOK_ISSUE*);
void show_issued_books(BOOK_ISSUE_TREE*,int);

//load data
BOOK_TREE* load_book_data();
STUDENT_TREE* load_stu_data();
EMPLOYEE* make_emp_list();
BOOK_ISSUE_TREE* load_book_issue();

//input_action.cpp
int verify_user(STUDENT_TREE*,int,char*);
int verify_emp(EMPLOYEE*,int,char*);
void login_display();


#endif