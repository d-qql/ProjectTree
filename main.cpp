#include <iostream>
#include <limits>

using namespace std;

struct treeElem
{
    int id;
    unsigned char height;
    treeElem* left;
    treeElem* right;

    treeElem(int k) { id = k; left = right = NULL; height = 1; }
};
treeElem* root;
unsigned char height(treeElem* p)
{
    return p?p->height:0;
}

int balancefactor(treeElem* p)
{
    return height(p->right)-height(p->left);
}

void fixheight(treeElem* p)
{
    unsigned char hl = height(p->left);
    unsigned char hr = height(p->right);
    p->height = (hl>hr?hl:hr)+1;
}

treeElem* rotateright(treeElem* p)
{
    if(p==root){
        root=p->left;
    }
    treeElem* q = p->left;
    p->left = q->right;
    q->right = p;
    fixheight(p);
    fixheight(q);
    return q;
}

treeElem* rotateleft(treeElem* q)
{
    if(q == root){
        root=q->right;
    }
    treeElem* p = q->right;
    q->right = p->left;
    p->left = q;
    fixheight(q);
    fixheight(p);
    return p;
}

treeElem* balance(treeElem* p)
{
    fixheight(p);
    if( balancefactor(p)==2 )
    {
        if( balancefactor(p->right) < 0 )
            p->right = rotateright(p->right);
        return rotateleft(p);
    }
    if( balancefactor(p)==-2 )
    {
        if( balancefactor(p->left) > 0  )
            p->left = rotateleft(p->left);
        return rotateright(p);
    }
    return p;
}

treeElem* insert(treeElem* p, int k)
{
    if( !p ) return new treeElem(k);
    if( k<p->id )
        p->left = insert(p->left,k);
    else
        p->right = insert(p->right,k);
    return balance(p);
}

treeElem* findmin(treeElem* p)
{
    return p->left?findmin(p->left):p;
}

treeElem* removemin(treeElem* p)
{
    if( p->left==NULL )
        return p->right;
    p->left = removemin(p->left);
    return balance(p);
}

treeElem* remove(treeElem* p, int k)
{
    if( !p ) return NULL;
    if( k < p->id )
        p->left = remove(p->left,k);
    else if( k > p->id )
        p->right = remove(p->right,k);
    else //  k == p->id
    {
        treeElem* q = p->left;
        treeElem* r = p->right;
        delete p;
        if( !r ) return q;
        treeElem* min = findmin(r);
        min->right = removemin(r);
        min->left = q;
        return balance(min);
    }
    return balance(p);
}

void print_tree(struct treeElem* root) {
    if(root->left != NULL)
        print_tree(root->left);
    cout << "Value = " << root->id <<endl;
    if(root->right != NULL)
        print_tree(root->right);

}
void Print(treeElem *q, long n)
{
    long i;
    if (q)
    {
        Print(q->right, n+5);
        for (i = 0; i < n; i++)
            cout<<" ";
        cout<<q->id<<endl;
        Print(q->left, n+5);
    }
}
treeElem* findElem(treeElem* root, int id){
    if(id<root->id){
        findElem(root->left, id);
    }
    if(id>root->id){
        findElem(root->right, id);
    }
    return root;
}
void DeleteAll(treeElem *root)
{
    if (root->left!=NULL)
    {
        DeleteAll(root->left);
    }
    if (root->right!=NULL)
    {
        DeleteAll(root->right);
    }
    if(root!=NULL){
        delete root;

}

int main() {
    treeElem a(0);
     root =  &a;
    for(int i = 0; i<22; i++){
        insert(root, rand());
    }
    print_tree(root);
    Print(root, root->height);
    cout<<findElem(root, 0);
    DeleteAll(root);
    return 0;
}