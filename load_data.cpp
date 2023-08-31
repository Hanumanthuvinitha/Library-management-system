
BOOK_TREE* load_book_data(){
    
    FILE* fp=fopen(".\\txt_files\\book.txt","r");
    if(fp==NULL)
    {
        cout<<"ERROR in opening book.txt file\n";
        exit(1);
    }
    char str[200];
    char* token;
    char delim[2]=",";
    BOOK_TREE* book_root=NULL;

    while(fgets(str,100,fp)!=NULL)
    {
        BOOK* new_node=new BOOK;

        //splitting the string using strtok function and assigning data;
        token=strtok(str,delim);
        new_node->book_id=atoi(token);

        token = strtok(NULL, delim);
        strcpy(new_node->book_name,token);

        token = strtok(NULL, delim);
        strcpy(new_node->author_name,token);

        token = strtok(NULL, delim);
        new_node->rack=atoi(token);
        
        token = strtok(NULL, delim);
        new_node->quantity=atoi(token);

        //insert the node
        book_root=insert_node(book_root,new_node);
    }
    fclose(fp);
    return book_root;
}

STUDENT_TREE* load_stu_data()
{
    FILE* fp2=fopen(".\\txt_files\\student_info.txt","r");
    char* tokenn;
    char str[150];
    char delim[2]=",";
    STUDENT_TREE* stu_root=NULL;
    while(fgets(str,100,fp2)!=NULL)
    {
        STUDENT* stu_node=new STUDENT;
        tokenn=strtok(str,delim);
        stu_node->stu_id=atoi(tokenn);
        tokenn=strtok(NULL,delim);
        strcpy(stu_node->stu_adm_num,tokenn);
        tokenn=strtok(NULL,delim);
        strcpy(stu_node->stu_name,tokenn);
        stu_root=insert_stu_node(stu_root,stu_node);
    }
    fclose(fp2);
    return stu_root;
    
}

EMPLOYEE* make_emp_list()
{
    EMPLOYEE* head=new EMPLOYEE;
    head=NULL;
    char str_emp[100];
    char delim[2]=",";
    char* token;
    FILE* fp_emp=fopen(".\\txt_files\\lib_emp.txt","r");
    if(fp_emp==NULL)
    {
        cout<<"error in loading employee file\n";
        exit(1);
    }
    while(fgets(str_emp,100,fp_emp)!=NULL)
    {
        EMPLOYEE* new_node=new EMPLOYEE;
        token=strtok(str_emp,delim);
        new_node->emp_id=atoi(token);
        token=strtok(NULL,delim);
        strcpy(new_node->emp_password,token);
        token=strtok(NULL,delim);
        strcpy(new_node->emp_name,token);
        new_node->next=NULL;
        head=add_to_list(head,new_node);
    }
    fclose(fp_emp);
    return head;
}

BOOK_ISSUE_TREE* load_book_issue()
{
    FILE* fp3=fopen(".\\txt_files\\book_issue.txt","r");
    char* tokenn;
    char str[150];
    char delim[2]=",";
    char b_name[150];
    char idate[20];
    char edate[20];
    int b_id,s_id;
    BOOK_ISSUE* node=NULL;
    while(fgets(str,100,fp3)!=NULL)
    {
        tokenn=strtok(str,delim);
        b_id=atoi(tokenn);
        tokenn=strtok(NULL,delim);
        strcpy(b_name,tokenn);
        tokenn=strtok(NULL,delim);
        s_id=atoi(tokenn);
        tokenn=strtok(NULL,delim);
        strcpy(idate,tokenn);
        tokenn=strtok(NULL,delim);
        strcpy(edate,tokenn);
        node=add_issue_node(b_id,b_name,s_id,idate,edate);
        issue_root=insert_issue_node(issue_root,node);
    }
    fclose(fp3);
    return issue_root;
}
