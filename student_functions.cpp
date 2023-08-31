void search_book_by_book_id(BOOK_TREE* root,int book_id)
{
    if(root==NULL)
    {
        cout<<"No book with the id- "<<book_id<<"is available"<<endl;
        return;
    }
    if(root->b_key->book_id==book_id)
    {
        cout<<"Book id - "<<root->b_key->book_id<<endl;
        cout<<"Book name - "<<(root->b_key->book_name)<<endl;
        cout<<"Author name - "<<(root->b_key->author_name)<<endl;
        cout<<(root->b_key->quantity)<<" copies available in rack number "<<root->b_key->rack<<endl;
        return;
    }
    if(root->b_key->book_id>book_id)
    {
        return search_book_by_book_id(root->left,book_id);
    }
    return search_book_by_book_id(root->right,book_id);

}

int search_book_by_bname(BOOK_TREE* root,char* b_name)
{
    if(root==NULL)
    return 0;
    if(strcmp(root->b_key->book_name,b_name)==0)
    {
        search_book_by_book_id(root,root->b_key->book_id);
        return 1;
    }
    int i=search_book_by_bname(root->left,b_name);
    if(i==0)
    return search_book_by_bname(root->right,b_name);
    return 1;
}
int search_book_by_aname(BOOK_TREE* root,char* a_name)
{
    if(root==NULL)
    return 0;
    if(strcmp(root->b_key->author_name,a_name)==0)
    {
        cout<<a_name<<" a_name"<<endl;
        cout<<"author name"<<root->b_key->author_name<<endl;
        search_book_by_book_id(root,root->b_key->book_id);
        return 1;
    }
    int i=search_book_by_aname(root->left,a_name);
    if(i==0)
    return search_book_by_aname(root->right,a_name);
    return 1;
}
void show_issue_list(BOOK_ISSUE* head)
{
    while(head!=NULL)
    {
        cout<<"book-ID - "<<head->book_id<<endl;
        cout<<"book name - "<<head->book_name<<endl;
        cout<<"Issue Date - "<<(head->issue_date).day<<"-"<<(head->issue_date).month<<"-"<<(head->issue_date).year<<endl;
        cout<<"Expiry Date - "<<(head->expiry_date).day<<"-"<<(head->expiry_date).month<<"-"<<(head->expiry_date).year<<endl;
        head=head->next;
    }
    return;
}

void show_issued_books(BOOK_ISSUE_TREE* root,int stu_id)
{
    if(root==NULL)
    {
        cout<<"Student with "<<stu_id<<" issued no books"<<endl;
        return;
    }
    if(root->head->stu_id==stu_id)
    {
        show_issue_list(root->head);
        return;
    }
    if(stu_id<root->head->stu_id)
    return show_issued_books(root->left,stu_id);
    else
    return show_issued_books(root->right,stu_id);
}

void calculate_fine(BOOK_ISSUE_TREE* root,int s_id,int b_id)
{
    if(root==NULL)
    {
        cout<<"Student with "<<s_id<<" issued no books"<<endl;
        return;
    }
    if(root->head->stu_id==s_id)
    {
        BOOK_ISSUE* ptr=root->head;
        while(ptr->book_id!=b_id && ptr!=NULL)
        {
            ptr=ptr->next;
        }
        if(ptr==NULL)
        {cout<<"You have not been issued this book\n";
        return;}
        time_t t = time(NULL);
        struct tm tm = *localtime(&t);
        int fine1=(tm.tm_mday)-((ptr->expiry_date).day);
        int fine2=(tm.tm_mon+1)-((ptr->expiry_date).month);
        if(fine1<=0)
        {cout<<"fine=0"<<endl;
        return;}
        cout<<"fine = "<<((fine2*30)+(fine1))*2<<endl;
        return;
    }
    if(s_id<root->head->stu_id)
    return calculate_fine(root->left,s_id,b_id);
    else
    return calculate_fine(root->right,s_id,b_id);
}