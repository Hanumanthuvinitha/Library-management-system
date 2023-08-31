#include "header.h"
#include "book.cpp"
#include "student.cpp"
#include "load_data.cpp"
#include "emp_functions.cpp"
#include "issue_book.cpp"
#include "student_functions.cpp"
#include "input_action.cpp"


//********LIBRARY MANAGEMENT SYSTEM*****//
//**************************************//
int main()
{
    //load the data
    books_root_node=load_book_data();
    student_root=load_stu_data();
    issue_root=load_book_issue();
    emp_root=make_emp_list();

    //menu
    login_display();
    return 0;
}

