

BOOK_TREE* new_book_node(BOOK* key){
    BOOK_TREE* node=new BOOK_TREE;
    node->b_key=key;
    node->left=NULL;
    node->right=NULL;
    node->height=1;
    return node;
}

int book_height(BOOK_TREE* node)
{
    if(node!=NULL)
    return node->height;
    return 0;
}

int balance(BOOK_TREE* node)
{
    if (node==NULL)
    {
        return 0;
    }
    return book_height(node->left)-book_height(node->right);
}
//rotations to balance the avl tree
BOOK_TREE* llrotate(BOOK_TREE* node)
{
    BOOK_TREE* temp=node->left;
    node->left=temp->right;
    temp->right=node;
    node->height=max(book_height(node->left),book_height(node->right))+1;
    temp->height=max(book_height(temp->left),book_height(temp->right))+1;
    return temp;

}

BOOK_TREE* rrrotate(BOOK_TREE* node)
{
    BOOK_TREE* temp=node->right;
    node->right=temp->left;
    temp->left=node;
    node->height=max(book_height(node->left),book_height(node->right))+1;
    temp->height=max(book_height(temp->left),book_height(temp->right))+1;
    return temp;
}

BOOK_TREE* lrrotate(BOOK_TREE* node)
{
    BOOK_TREE* temp=node->left;
    node->left=rrrotate(temp);
    return llrotate(node);
}

BOOK_TREE* rlrotate(BOOK_TREE* node)
{
    BOOK_TREE* temp=node->right;
    node->right=llrotate(temp);
    return rrrotate(node);
}

BOOK_TREE* insert_node(BOOK_TREE* root,BOOK* value)
{
    if(root==NULL)
    {
    root=new_book_node(value);
    return root;
    }
    if(value->book_id==root->b_key->book_id)
    {
        book_dup_flag=1;
        cout<<"Cannot insert the record with duplicate id"<<endl;
        return root;
    }
    if(value->book_id<root->b_key->book_id)
    {
        root->left=insert_node(root->left,value);
        root->height=max(book_height(root->left),book_height(root->right))+1;
    }
    else{
        root->right=insert_node(root->right,value);
        root->height=max(book_height(root->left),book_height(root->right))+1;
    }
    root=balance_tree(root);
    return root;
}

BOOK_TREE* balance_tree(BOOK_TREE* root)
{
    int bal=balance(root);
    if(root==NULL)
    {
        //cout<<"root NULL in balance tree \n";
        return root;
    }
    if(bal>1)
    {
        if(balance(root->left)>0)
        {
            root=llrotate(root);
        }
        else
        {
            root=lrrotate(root);
        }
    }
    else if(bal<-1)
    {
        if(balance(root->right)>0)
        {
            root=rlrotate(root);
        }
        else
        {
            root=rrrotate(root);
        }

    }
    return root;
}

void show_books(BOOK_TREE* root)
{
    if(root==NULL)
    return;
    show_books(root->left);
    cout<<root->b_key->book_id<<"-"<<root->b_key->book_name<<endl;
    show_books(root->right);
}

