BOOK_ISSUE* new_issue_node(int book_id,char book_name[BOOK_NAME_LEN],int stu_id)
{
    BOOK_ISSUE* node=new BOOK_ISSUE;
    node->book_id=book_id;
    node->stu_id=stu_id;
    strcpy(node->book_name,book_name);
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    (node->issue_date).day=tm.tm_mday;
    (node->issue_date).month=tm.tm_mon+1;
    (node->issue_date).year=tm.tm_year+1900;
    tm.tm_mday += 15;
    mktime(&tm);
    (node->expiry_date).day=tm.tm_mday;
    (node->expiry_date).month=tm.tm_mon+1;
    (node->expiry_date).year=tm.tm_year+1900;
    node->next=NULL;
    return node;
}

int delete_book_rec(BOOK_ISSUE* head,int b_id)
{
    BOOK_ISSUE* ptr=head;
    while(head->book_id!=b_id)
    {
        ptr=head;
        head=head->next;
    }
    if(head==NULL)
    {
        cout<<"You have not been issued the book(head==NULL)\n";
        return 1;
    }
    if(head->next==NULL)
    return 0;
    ptr->next=head->next;
    return 1;
    

}

void split_date(char* idate,int& day,int& month,int& year)
{
    char* token;
    token=strtok(idate,"-");
    day=atoi(token);
    token=strtok(NULL,"-");
    month=atoi(token);
    token=strtok(NULL,"-");
    year=atoi(token);
    return;
}

BOOK_ISSUE* add_issue_node(int b_id,char* b_name,int s_id,char* idate,char* edate)
{
    BOOK_ISSUE* node=new BOOK_ISSUE;
    node->book_id=b_id;
    node->stu_id=s_id;
    strcpy(node->book_name,b_name);
    char* token;
    int day,month,year;
    split_date(idate,day,month,year);
    (node->issue_date).day=day;
    (node->issue_date).month=month;
    (node->issue_date).year=year;
    split_date(edate,day,month,year);
    (node->expiry_date).day=day;
    (node->expiry_date).month=month;
    (node->expiry_date).year=year;
    return node;
}

BOOK_ISSUE_TREE* new_issue_tree_node(BOOK_ISSUE* key){
    BOOK_ISSUE_TREE* node=new BOOK_ISSUE_TREE;
    node->head=key;
    node->left=NULL;
    node->right=NULL;
    node->height=1;
    return node;
}

int add_to_issue_list(BOOK_ISSUE* head,BOOK_ISSUE* node)
{
    while(head->next!=NULL)
    {
        if(head->book_id==node->book_id)
        {
        cout<<"This book was already issued to you\n";
        return 0;
        }
        head=head->next;
    }
    head->next=node;
    return 1;
}
int issue_tree_ht(BOOK_ISSUE_TREE* node)
{
    if(node!=NULL)
    return node->height;
    return 0;
}

int balance_factor_issue(BOOK_ISSUE_TREE* node)
{
    if (node==NULL)
    return 0;
    return issue_tree_ht(node->left)-issue_tree_ht(node->right);
}

//rotations to balance the avl tree
BOOK_ISSUE_TREE*  ll_rotate_issue(BOOK_ISSUE_TREE* node)
{
    BOOK_ISSUE_TREE* temp=node->left;
    node->left=temp->right;
    temp->right=node;
    node->height=max(issue_tree_ht(node->left),issue_tree_ht(node->right))+1;
    temp->height=max(issue_tree_ht(temp->left),issue_tree_ht(temp->right))+1;
    return temp;

}

BOOK_ISSUE_TREE* rr_rotate_issue(BOOK_ISSUE_TREE* node)
{
    BOOK_ISSUE_TREE* temp=node->right;
    node->right=temp->left;
    temp->left=node;
    node->height=max(issue_tree_ht(node->left),issue_tree_ht(node->right))+1;
    temp->height=max(issue_tree_ht(temp->left),issue_tree_ht(temp->right))+1;
    return temp;
}

BOOK_ISSUE_TREE* lrrotate_issue(BOOK_ISSUE_TREE* node)
{
    BOOK_ISSUE_TREE* temp=node->left;
    node->left=rr_rotate_issue(temp);
    return  ll_rotate_issue(node);
}

BOOK_ISSUE_TREE* rlrotate_issue(BOOK_ISSUE_TREE* node)
{
    BOOK_ISSUE_TREE* temp=node->right;
    node->right= ll_rotate_issue(temp);
    return rr_rotate_issue(node);
}

BOOK_ISSUE_TREE* insert_issue_node(BOOK_ISSUE_TREE* root,BOOK_ISSUE* value)
{
    if(root==NULL)
    {
        //cout<<"root NULL\n";
        root=new_issue_tree_node(value);
        return root;
    }
    if(value->stu_id==root->head->stu_id)
    {
        issue_dup_flag=add_to_issue_list(root->head,value);
        return root;
    }
    if(value->stu_id<root->head->stu_id)
    {
        root->left=insert_issue_node(root->left,value);
        //root->left->height=max(issue_tree_ht(root->left->left),issue_tree_ht(root->left->right))+1;
        root->height=max(issue_tree_ht(root->left),issue_tree_ht(root->right))+1;
        
    }
    else{
        root->right=insert_issue_node(root->right,value);
        //root->right->height=max(issue_tree_ht(root->right->left),issue_tree_ht(root->right->right))+1;
        root->height=max(issue_tree_ht(root->left),issue_tree_ht(root->right))+1;
    }
    root=balance_book_issue_tree(root);
    return root;
}

BOOK_ISSUE_TREE* balance_book_issue_tree(BOOK_ISSUE_TREE* root)
{
    if(root==NULL)
    return root;
    if(balance_factor_issue(root)>1)
    {
        if(balance_factor_issue(root->left)>0)
        {
            root= ll_rotate_issue(root);
        }
        else
        {
            root=lrrotate_issue(root);
        }
    }
    else if(balance_factor_issue(root)<-1)
    {
        if(balance_factor_issue(root->right)>0)
        {
            root=rlrotate_issue(root);
        }
        else
        {
            root=rr_rotate_issue(root);
        }

    }
    return root;
}


BOOK_ISSUE_TREE* inorder_issue_succ(BOOK_ISSUE_TREE* node)
{
    if(node->left==NULL)
    return node;
    return inorder_issue_succ(node->left);
}

BOOK_ISSUE_TREE* delete_leaf_node_issue(BOOK_ISSUE_TREE* root,BOOK_ISSUE_TREE* node)
{
    if(root==node)
    {
        return NULL;
    }
    root->left=delete_leaf_node_issue(root->left,node);
    return root;
}

BOOK_ISSUE_TREE* delete_issue_node(BOOK_ISSUE_TREE* issue_root,BOOK_ISSUE_TREE* root)
{
        if(root->left==NULL || root->right==NULL)
        {
            BOOK_ISSUE_TREE* temp=root->right?root->right:root->left;
            if(temp==NULL)
            return temp;
            *root=*temp;
            return root;
        }
        BOOK_ISSUE_TREE* temp=inorder_issue_succ(root->right);
        root->head=temp->head;
        root->right=delete_leaf_node_issue(root,temp);
        root->height=max(issue_tree_ht(root->left),issue_tree_ht(root->right))+1;
        root=balance_book_issue_tree(root);
        return root;
        
}


void update_issue_file(int book_id,int stu_id)
{
    FILE* fp_issue=fopen(".\\txt_files\\book_issue.txt","r");
    FILE* fp_issue_dup=fopen(".\\txt_files\\book_issue_dup.txt","a");
    char book_issued[150];
    char new_str[150];
    char* token;
    while(fgets(book_issued,150,fp_issue)!=NULL)
    {
        strcpy(new_str,book_issued);
        token=strtok(book_issued,",");
        if(book_id!=atoi(token))
        fputs(new_str,fp_issue_dup);
        else{
            token=strtok(NULL,",");
            token=strtok(NULL,",");
            if(stu_id!=atoi(token))
            fputs(new_str,fp_issue_dup);

        }
    }
    fclose(fp_issue);
    fclose(fp_issue_dup);
    FILE* fp_issue_=fopen(".\\txt_files\\book_issue.txt","w");
    fclose(fp_issue_);
    FILE* fp_issue2=fopen(".\\txt_files\\book_issue.txt","a");
    FILE* fp_issue_dup2=fopen(".\\txt_files\\book_issue_dup.txt","r");
    while(fgets(book_issued,150,fp_issue_dup2)!=NULL){
        fputs(book_issued,fp_issue2);
    }
    fclose(fp_issue2);
    fclose(fp_issue_dup2);
    FILE* fp_issuedup_=fopen(".\\txt_files\\book_issue_dup.txt","w");
    fclose(fp_issuedup_);
    return;
}

void update_expiry_date_in_file(int book_id,int stu_id,BOOK_ISSUE* head)
{
    FILE* fp_issue=fopen(".\\txt_files\\book_issue.txt","r");
    FILE* fp_issue_dup=fopen(".\\txt_files\\book_issue_dup.txt","a");
    char book_issued[150];
    char new_str[150];
    char* token;
    char* book_name;
    while(fgets(book_issued,150,fp_issue)!=NULL)
    {
        strcpy(new_str,book_issued);
        token=strtok(book_issued,",");
        if(book_id!=atoi(token))
        fputs(new_str,fp_issue_dup);
        else{
            book_name=strtok(NULL,",");
            token=strtok(NULL,",");
            if(stu_id!=atoi(token))
            fputs(new_str,fp_issue_dup);
            else
            {
                fprintf(fp_issue_dup,"%d,%s,%s,",book_id,book_name,token);
                token=strtok(NULL,",");
                fprintf(fp_issue_dup,"%s,",token);
                while(head->book_id!=book_id)
                head=head->next;
                fprintf(fp_issue_dup,"%d-%d-%d,\n",(head->expiry_date).day,(head->expiry_date).month,(head->expiry_date).year);
            }
        }
    }
    fclose(fp_issue);
    fclose(fp_issue_dup);
    FILE* fp_issue_=fopen(".\\txt_files\\book_issue.txt","w");
    fclose(fp_issue_);
    FILE* fp_issue2=fopen(".\\txt_files\\book_issue.txt","a");
    FILE* fp_issue_dup2=fopen(".\\txt_files\\book_issue_dup.txt","r");
    while(fgets(book_issued,150,fp_issue_dup2)!=NULL){
        fputs(book_issued,fp_issue2);
    }
    fclose(fp_issue2);
    fclose(fp_issue_dup2);
    FILE* fp_issuedup_=fopen(".\\txt_files\\book_issue_dup.txt","w");
    fclose(fp_issuedup_);
    return;
}