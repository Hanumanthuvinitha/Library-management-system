
EMPLOYEE* add_to_list(EMPLOYEE* head,EMPLOYEE* node)
{
    if(head==NULL)
    return node;
    EMPLOYEE* ptr=head;
    while(ptr->next!=NULL)
    {
        ptr=ptr->next;
    }
    ptr->next=node;
    return head;
}

void show_emp(EMPLOYEE* head)
{
    while(head!=NULL)
    {
        cout<<(head->emp_name)<<endl;
        head=head->next;
    }
    return;
}

STUDENT_TREE* add_user(char* stu_name,int id,char* adm_num)
{
    STUDENT* key=new STUDENT;
    strcpy(key->stu_name,stu_name);
    key->stu_id=id;
    strcpy(key->stu_adm_num,adm_num);
    stu_dup_flag=0;
    student_root=insert_stu_node(student_root,key);
    if(stu_dup_flag==1)
    return student_root;

    FILE* stu_fp=fopen(".\\txt_files\\student_info.txt","a");
    if(stu_fp==NULL){
        cout<<"Error in opening file in append mode"<<endl;
        exit(1);
    }

    if(fprintf(stu_fp,"%d,%s,%s,\n",id,adm_num,stu_name)>=0)
    cout<<"student database updated successfully"<<endl;
    else
    {
        cout<<"Error in updating the student database"<<endl;
    }
    fclose(stu_fp);
    return student_root;

}

BOOK_TREE* insert_new_book(int b_id,char *b_name,char *a_name,int rac,int quan)
{
    BOOK* new_book=new BOOK;
    new_book->book_id=b_id;
    strcpy(new_book->book_name,b_name);
    strcpy(new_book->author_name,a_name);
    new_book->rack=rac;
    new_book->quantity=quan;
    book_dup_flag=0;
    books_root_node=insert_node(books_root_node,new_book);
    if(book_dup_flag==1)
    return books_root_node;
    
    FILE* fp_book=fopen(".\\txt_files\\book.txt","a");

    if(fprintf(fp_book,"%d,%s,%s,%d,%d,\n",b_id,b_name,a_name,rac,quan)<0)
    cout<<"Error in updating the books database"<<endl;
    else
    cout<<"Books database updated successfully"<<endl;

    fclose(fp_book);
    return books_root_node;
}

int verify_book_details(BOOK_TREE* root,int book_id,char* b_name)
{
    if(root==NULL)
    {
        cout<<"No book with the id- "<<book_id<<"is available"<<endl;
        return 0;
    }
    if(root->b_key->book_id==book_id)
    {
        if(strcmp(root->b_key->book_name,b_name)==0)
        return 1;
        return 0;
    }
    if(root->b_key->book_id>book_id)
    {
        return verify_book_details(root->left,book_id,b_name);
    }
    return verify_book_details(root->right,book_id,b_name);

}

void issue_book(int b_id,char *b_name,int s_id,char* password)
{
    int verify;
    verify=verify_book_details(books_root_node,b_id,b_name);
    if(verify==0)
    {
        cout<<"check book id and book name\n";
        return;
    }

    verify=verify_user(student_root,s_id,password);
    if(verify==0)
    {
        cout<<"Incorrect username or password\n";
        return;
    }

    BOOK_ISSUE* node=new_issue_node(b_id,b_name,s_id);
    issue_root=insert_issue_node(issue_root,node);
    issue_dup_flag=2;
    if(issue_dup_flag==0)
    return;

    cout<<"Book issued"<<endl;
    //writing into file;
    FILE* fp_issue=fopen(".\\txt_files\\book_issue.txt","a");
    if(fp_issue==NULL)
    {
        cout<<"Error in opening issue_book file\n";
        exit(1);
    }
    fprintf(fp_issue,"%d,%s,%d,",b_id,b_name,s_id);
    fprintf(fp_issue,"%d-%d-%d,",(node->issue_date).day,(node->issue_date).month,(node->issue_date).year);
    fprintf(fp_issue,"%d-%d-%d,\n",(node->expiry_date).day,(node->expiry_date).month,(node->expiry_date).year);
    cout<<"Issue_book file updated successfully"<<endl;
    fclose(fp_issue);
    return;
}   

void return_book(BOOK_ISSUE_TREE* i_root,int book_id,int stu_id)
{
    if(i_root==NULL)
    {
        cout<<"You have not been issued this book(issue root=NULL)\n";
        return;
    }
    if(i_root->head->stu_id==stu_id)
    {
        int del=delete_book_rec(i_root->head,book_id);
        update_issue_file(book_id,stu_id);
        if(del==1)
        return;

        if(del==0)
        {
        issue_root=delete_issue_node(issue_root,i_root);
        return;
        }
    }

    if(i_root->head->stu_id>stu_id)
    {
        return return_book(i_root->left,book_id,stu_id);
    }
    {
    return return_book(i_root->right,book_id,stu_id);
    }
}

void update_edate(BOOK_ISSUE* head,int book_id)
{
    if(head==NULL)
    {
        cout<<"You have not been issued this book"<<endl;
        return;
    }
    if(head->book_id==book_id)
    {
        time_t t = time(NULL);
        struct tm tm = *localtime(&t);
        tm.tm_mday += 15;
        mktime(&tm);
        (head->expiry_date).day=tm.tm_mday;
        (head->expiry_date).month=tm.tm_mon+1;
        (head->expiry_date).year=tm.tm_year+1900;
        return;
    }
    return update_edate(head->next,book_id);
}

void renew_book(BOOK_ISSUE_TREE* i_root,int book_id,int stu_id)
{
    if(i_root==NULL)
    {
        cout<<"You have not been issued this book(issue root=NULL)\n";
        return;
    }
    if(i_root->head->stu_id==stu_id)
    {
        update_edate(i_root->head,book_id);
        update_expiry_date_in_file(book_id,stu_id,i_root->head);
        return;
    }
    if(i_root->head->stu_id>stu_id)
    {
        return renew_book(i_root->left,book_id,stu_id);
    }
    if(i_root->head->stu_id<stu_id)
    {
    return renew_book(i_root->right,book_id,stu_id);
    }
}

STUDENT_TREE* delete_student_rec(STUDENT_TREE* root,int stu_id,char* password)
{
    if(root==NULL)
    {
        cout<<"No student record with the id "<<stu_id<<endl;
        return root;
    }
    if(root->s_key->stu_id==stu_id)
    {
        if(strcmp(root->s_key->stu_adm_num,password)!=0)
        {
            cout<<"Incorrect password"<<endl;
            return root;
        }
        else{
            update_student_file(stu_id);
        }
        if(root->left==NULL || root->right==NULL)
        {
            STUDENT_TREE* temp=root->right?root->right:root->left;
            if(temp==NULL)
            return temp;
            *root=*temp;
            return root;
        }
        STUDENT_TREE* temp=inorder_succ(root->right);
        root->s_key=temp->s_key;
        root->right=delete_leaf_node(root,temp);
        root->height=max(stu_tree_height(root->left),stu_tree_height(root->right))+1;
        root=balance_student_tree(root);
        return root;
        
    }
    if(root->s_key->stu_id>stu_id)
    {
    root->left=delete_student_rec(root->left,stu_id,password);
    return root;
    }
    if(root->s_key->stu_id<stu_id)
    {
        root->right=delete_student_rec(root->right,stu_id,password);
        return root;
    }
    return NULL;
    
}

void update_student_file(int stu_id)
{
    FILE* fp_stu=fopen(".\\txt_files\\student_info.txt","r");
    FILE* fp_stu_dup=fopen(".\\txt_files\\student_info_dup.txt","a");
    char stu_rec[150];
    char new_str[150];
    char* token;
    while(fgets(stu_rec,150,fp_stu)!=NULL)
    {
        strcpy(new_str,stu_rec);
        token=strtok(stu_rec,",");
    
        if(atoi(token)!=stu_id)
        {
            fputs(new_str,fp_stu_dup);
        }
    }
    fclose(fp_stu);
    fclose(fp_stu_dup);
    FILE* fp_stu_=fopen(".\\txt_files\\student_info.txt","w");
    fclose(fp_stu_);
    FILE* fp_stu2=fopen(".\\txt_files\\student_info.txt","a");
    FILE* fp_stu_dup2=fopen(".\\txt_files\\student_info_dup.txt","r");
    while(fgets(stu_rec,150,fp_stu_dup2)!=NULL){
        fputs(stu_rec,fp_stu2);
    }
    fclose(fp_stu2);
    fclose(fp_stu_dup2);
    FILE* fp_stu_dup_=fopen(".\\txt_files\\student_info_dup.txt","w");
    fclose(fp_stu_dup_);
    cout<<"Student file updated successfully\n";
    return;
}
