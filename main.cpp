#include <iostream>

using namespace std;

class Treap
{
public:
    int k;
    int p;
    int src;
    //Treap *parent;
    Treap *left;
    Treap *right;
    Treap(int src, int x, int y, Treap *left = NULL, Treap *right = NULL/*, Treap *parent = NULL*/)
    {
        this->src = src;
        this->k = x;
        this->p = y;
        this->left = left;
        this->right = right;
        //this->parent = parent;
    }
    Treap *merge(Treap* a,Treap* b);
    void split(int x, Treap * &a, Treap * &b);
    Treap *add(int src, int x, int y);
    Treap *remove(int x);
    void print(int s);
};

Treap *Treap::merge(Treap *a, Treap *b) {
    if(a == NULL) return b;
    if(b == NULL) return a;
    if(a->p < b->p) {
        a->right = merge(a->right, b);
        return a;
    }
    else {
        b->left = merge(a, b->left);
        return b;
    }
}

void Treap::split(int x, Treap *&l, Treap *&r) {
    Treap *n = NULL;
    if(k <= x)
    {
        if(right == NULL)
            r = NULL;
        else
            right->split(k, n, r);
        l = new Treap(src, k, p, left, n);
    }
    else
    {
        if(left == NULL)
            l = NULL;
        else
            left->split(k, l, n);
        r = new Treap(src, k, p, n, right);
    }
}

Treap *Treap::add(int x, int y, int src) {
    Treap *l = NULL, *r = NULL;
    split(x,l,r);
    Treap *m = new Treap(src, x, y);
    return merge(merge(l,m),r);
}

Treap *Treap::remove(int x) {
    Treap *l = NULL, *m, *r = NULL;
    split(x - 1, l, r);
    r->split(x, m, r);
    delete m;
    return merge(l, r);
}

/*Treap *Build(int x[], int y[], int n)
{
    Treap* tree = new Treap(1, x[0], y[0]);
    Treap* last = tree;

    for (int i = 1; i < n; ++i)
    {
        if (last->p > y[i])
        {
            last->right = new Treap(i+1,x[i], y[i], NULL, NULL, last);
            last = last->right;
        }
        else
        {
            Treap *current = last;
            while (current->parent && current->p <= y[i])
                current = current->parent;
            if (current->p <= y[i])
                last = new Treap(i+1,x[i], y[i], current);
            else
            {
                last = new Treap(i+1, x[i], y[i], current->right, NULL, current);
                current->right = last;
            }
        }
    }

    while (last->parent)
        last = last->parent;
    return last;
}*/

void Treap::print(int src) {
   if(left != NULL)
        left->print(this->src);
    cout << src << " " << (left ? left->src : 0) << " " << (right ? right->src : 0) << endl;
    if(right != NULL)
        right->print(this->src);
}

int main() {
    int n;
    cin >> n;
    int a,b;
    cin >> a >> b;
    Treap *t = new Treap(1, a, b);
    for(int i = 2; i <= n; i++)
    {
        cin >> a >> b;
        t = t->add(a, b, i);
    }


    cout << "YES" << endl;
    t->print(0);

    return 0;
}
