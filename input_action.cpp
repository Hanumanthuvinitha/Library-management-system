int verify_user(STUDENT_TREE* root,int id,char* password)
{
    if(root==NULL)
    {
        return 0;
    }
    if(root->s_key->stu_id==id)
    {
        if(strcmp(root->s_key->stu_adm_num,password)==0)
        {
            return 1;
        }
        return 0;
    }
    if(root->s_key->stu_id>id)
    return verify_user(root->left,id,password);
    return verify_user(root->right,id,password);
}
int verify_emp(EMPLOYEE* root,int id,char* password)
{
    if(root==NULL)
    {
        return 0;
    }
    if(root->emp_id==id)
    {
        if(strcmp(root->emp_password,password)==0)
        return 1;
        return 0;
    }
    return verify_emp(root->next,id,password);
}
char sname[NAME_LEN];
void login_display()
{
    int user_action;
    int user;
    login:
    cout<<"*******LOGIN*********\n";
    cout<<"user_id"<<endl;
    cin>>userID;
    cout<<"password(Adm_Number)"<<endl;
    cin>>password;
    cout<<"enter 1.Student and 2.Library Employee"<<endl;
    cin>>user;
    switch(user)
    {
        case 1:
            status_user=verify_user(student_root,userID,password);
            if(status_user==0)
            {
                cout<<"Invalid username or Password\n";
                goto login;
            }
    
            while(true)
            {
                cout<<"*********STUDENT FUNCTIONS**********"<<endl;
                cout<<"*    CHOOSE NUMBER ACCORDINGLY     *"<<endl;
                cout<<"* 1.search books by book_id        *"<<endl;
                cout<<"* 2.search books by book_name      *"<<endl;
                cout<<"* 3.search books by author_name    *"<<endl;
                cout<<"* 4.view all the books available   *"<<endl;
                cout<<"* 5.books issued by the student    *"<<endl;
                cout<<"* 6.Calculate Fine                 *"<<endl;
                cout<<"* 7.Exit                           *"<<endl;
                cout<<"************************************"<<endl;
                cin>>user_action;

                switch(user_action)
                {
                    case 1:
                        int bid;
                        cout<<"Book id\n";
                        cin>>bid;
                        search_book_by_book_id(books_root_node,bid);
                        break;
                    case 2:
                        char book_name[70];
                        cout<<"Enter book name(spelling and spaces should be proper)\n";
                        fflush(stdin);
                        scanf("%[^\n]s",book_name);
                        if(search_book_by_bname(books_root_node,book_name)==0)
                        cout<<"No books with this name are available\n";
                        break;
                    case 3:
                        char a_name[NAME_LEN];
                        cout<<"Enter author name(spelling and spaces should be proper)\n";
                        fflush(stdin);
                        scanf("%[^\n]s",a_name);
                        if(search_book_by_aname(books_root_node,a_name)==0)
                        cout<<"No book by the given author name are available\n";
                        break;
                    case 4:
                        show_books(books_root_node);
                        break;
                    case 5:
                        int id;
                        cout<<"student id"<<endl;
                        cin>>id;
                        show_issued_books(issue_root,id);
                        break;
                    case 6:
                        int sids;
                        int bids;
                        cout<<"student id"<<endl;
                        cin>>sids;
                        cout<<"book id\n";
                        cin>>bids;
                        calculate_fine(issue_root,sids,bids);
                        break;
                    case 7:
                        exit(1);
                        break;
                    default:
                        cout<<"choose appropriate Number\n";
                        break;
                }
            }
            break;
        case 2:
            status_emp=verify_emp(emp_root,userID,password);
            if(status_emp==0)
            {
                cout<<"Invalid username or Password\n";
                goto login;
            }

            while(true)
            {
                cout<<"*********LIBRARIAN FUNCTIONS********"<<endl;
                cout<<"*    CHOOSE NUMBER ACCORDINGLY     *"<<endl;
                cout<<"* 1.Add new students               *"<<endl;
                cout<<"* 2.Add new books                  *"<<endl;
                cout<<"* 3.Issue the book                 *"<<endl;
                cout<<"* 4.Return the book                *"<<endl;
                cout<<"* 5.Renew the book                 *"<<endl;
                cout<<"* 6.Delete student record          *"<<endl;
                cout<<"* 7.Show Students(Users)           *"<<endl;
                cout<<"* 8.Exit                           *"<<endl;
                cout<<"************************************"<<endl;
                cin>>user_action;
            
            switch(user_action)
            {
                case 1:
                    
                    char adm[8];
                    int id;
                    cout<<"Enter Student Details"<<endl;
                    cout<<"Student name"<<endl;
                    fflush(stdin);
                    scanf("%[^\n]s",sname);
                    cout<<"Student id"<<endl;
                    cin>>id;
                    cout<<"Admission Number"<<endl;
                    fflush(stdin);
                    scanf("%[^\n]s",adm);
                    student_root=add_user(sname,id,adm);
                    if(stu_dup_flag==0)
                    cout<<"User Added Successfully"<<endl;
                    break;
                case 2:
                    int book_id;
                    char book_name[BOOK_NAME_LEN];
                    char author_name[NAME_LEN];
                    int rack;
                    int quantity;
                    cout<<"BOOK DETAILS"<<endl;
                    cout<<"book id\n";
                    cin>>book_id;
                    cout<<"Book name\n";
                    fflush(stdin);
                    scanf("%[^\n]s",book_name);
                    cout<<"author name\n";
                    fflush(stdin);
                    scanf("%[^\n]s",author_name);
                    cout<<"rack Number\n";
                    cin>>rack;
                    cout<<"quantity"<<endl;
                    cin>>quantity;
                    books_root_node=insert_new_book(book_id,book_name,author_name,rack,quantity);
                    if(book_dup_flag==0)
                    cout<<"New book added successfully"<<endl;
                    break;
                case 3:
                    int id_book;
                    char name_of_book[BOOK_NAME_LEN];
                    int id_stu;
                    char pw[10];
                    cout<<"enter student id"<<endl;
                    cin>>id_stu;
                    cout<<"Enter book id"<<endl;
                    cin>>id_book;
                    cout<<"Book name"<<endl;
                    fflush(stdin);
                    scanf("%[^\n]s",name_of_book);
                    cout<<"Password of student"<<endl;
                    fflush(stdin);
                    scanf("%[^\n]s",pw);
                    issue_book(id_book,name_of_book,id_stu,pw);
                    break;
                case 4:
                    int book_id_;
                    int stu_id;
                    cout<<"Enter id of book you want to return \n";
                    cin>>book_id_;
                    cout<<"Enter student id\n";
                    cin>>stu_id;
                    return_book(issue_root,book_id_,stu_id);
                    break;
                case 5:
                    int book_ids;
                    int student_id;
                    cout<<"Enter id of book you want to renew\n";
                    cin>>book_ids;
                    cout<<"Enter student id\n";
                    cin>>student_id;
                    renew_book(issue_root,book_ids,student_id);
                    break;
                case 6:
                    int stud_id;
                    char password[9];
                    cout<<"student id\n";
                    cin>>stud_id;
                    cout<<"Password\n";
                    fflush(stdin);
                    scanf("%[^\n]s",password);
                    student_root=delete_student_rec(student_root,stud_id,password);
                    break;
                case 7:
                    show_students(student_root);
                    break;
                case 8:
                    exit(1);
                    break;
                default:
                    cout<<"choose appropriate Number\n";
                    break;
            }
    }
    break;
    default:
        cout<<"Choose the action appropriately\n";
        break;

    }
}