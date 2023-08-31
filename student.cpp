STUDENT_TREE* new_student_node(STUDENT* key){
    STUDENT_TREE* node=new STUDENT_TREE;
    node->s_key=key;
    node->left=NULL;
    node->right=NULL;
    node->height=1;
    return node;
}

int stu_tree_height(STUDENT_TREE* node)
{
    if(node!=NULL)
    return node->height;
    return 0;
}

int balance_stu_tree(STUDENT_TREE* node)
{
    if (node==NULL)
    return 0;
    return stu_tree_height(node->left)-stu_tree_height(node->right);
}

//rotations to balance the avl tree
STUDENT_TREE*  llrotate_stu_rec(STUDENT_TREE* node)
{
    STUDENT_TREE* temp=node->left;
    node->left=temp->right;
    temp->right=node;
    node->height=max(stu_tree_height(node->left),stu_tree_height(node->right))+1;
    temp->height=max(stu_tree_height(temp->left),stu_tree_height(temp->right))+1;
    return temp;

}

STUDENT_TREE* rrrotate_stu_rec(STUDENT_TREE* node)
{
    STUDENT_TREE* temp=node->right;
    node->right=temp->left;
    temp->left=node;
    node->height=max(stu_tree_height(node->left),stu_tree_height(node->right))+1;
    temp->height=max(stu_tree_height(temp->left),stu_tree_height(temp->right))+1;
    return temp;
}

STUDENT_TREE* lrrotate_stu_rec(STUDENT_TREE* node)
{
    STUDENT_TREE* temp=node->left;
    node->left=rrrotate_stu_rec(temp);
    return  llrotate_stu_rec(node);
}

STUDENT_TREE* rlrotate_stu_rec(STUDENT_TREE* node)
{
    STUDENT_TREE* temp=node->right;
    node->right= llrotate_stu_rec(temp);
    return rrrotate_stu_rec(node);
}

STUDENT_TREE* insert_stu_node(STUDENT_TREE* root,STUDENT* value)
{
    if(root==NULL)
    {
    root=new_student_node(value);
    return root;
    }
    if(value->stu_id==root->s_key->stu_id)
    {
        stu_dup_flag=1;
        cout<<"Cannot insert the record with duplicate id"<<endl;
        return root;
    }
    if(value->stu_id<root->s_key->stu_id)
    {
        root->left=insert_stu_node(root->left,value);
        root->height=max(stu_tree_height(root->left),stu_tree_height(root->right))+1;
        
    }
    else{
        root->right=insert_stu_node(root->right,value);
        root->height=max(stu_tree_height(root->left),stu_tree_height(root->right))+1;
    }
    root=balance_student_tree(root);
    return root;
}

STUDENT_TREE* balance_student_tree(STUDENT_TREE* root)
{
    if(root==NULL)
    return root;
    if(balance_stu_tree(root)>1)
    {
        if(balance_stu_tree(root->left)>0)
        {
            root= llrotate_stu_rec(root);
        }
        else
        {
            root=lrrotate_stu_rec(root);
        }
    }
    else if(balance_stu_tree(root)<-1)
    {
        if(balance_stu_tree(root->right)>0)
        {
            root=rlrotate_stu_rec(root);
        }
        else
        {
            root=rrrotate_stu_rec(root);
        }

    }
    return root;
}

void show_students(STUDENT_TREE* root)
{
    if(root==NULL)
    {
       return;
    }
    show_students(root->left);
    cout<<root->s_key->stu_id<<"-"<<root->s_key->stu_name<<endl;
    show_students(root->right);
    return;
}
STUDENT_TREE* inorder_succ(STUDENT_TREE* node)
{
    if(node->left==NULL)
    return node;
    return inorder_succ(node->left);
}
STUDENT_TREE* delete_leaf_node(STUDENT_TREE* root,STUDENT_TREE* node)
{
    if(root==node)
    {
        return NULL;
    }
    root->left=delete_leaf_node(root->left,node);
    return root;
}
