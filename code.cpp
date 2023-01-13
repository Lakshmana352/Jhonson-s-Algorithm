#include <bits/stdc++.h>
using namespace std;

#define ull   unsigned long long int
#define ll   long long int

//Time is in milli seconds..................................................................................................................//
//Prints -1 for every row if the graph if it is having a negative weight cycle...............................................................//

void printvec(vector<vector<ll>> &k,ll n)
{
    for(ll i=1;i<n;i++)
    {
        for(ll j=1;j<n;j++) cout << k[i][j] << " ";
        cout << endl;
    }
    return;
}

void printv(vector<ll> &k,ll n)
{
    for(ll i=0;i<n;i++) cout << k[i] << " ";cout << endl;return;
}

// void find_parents(vector<vector<ll>> &k,ll n)
// {
//     cout << "came " << endl;
//     vector<ll> p(n,0);
//     for(ll i=1;i<n;i++)
//     {
//         ll m = 999999,pa = -1;
//         for(ll j=1;j<n;j++)
//         {
//             if(k[j][i] < m) {m=k[j][i];pa = j;}
//         }
//         p[i]=pa;
//     }
//     printv(p,n);
//     return;
// }

//belmann ford algorithm.......................................//
ll bellmann_ford(vector<vector<ll>> &k,ll n,vector<ll> &d)
{
    d[0]=0;
    for(ll l=1;l<n;l++)
    {
        for(ll i=0;i<n;i++)
        {
            for(ll j=0;j<n;j++) 
            {
                if(k[i][j]!=999999) {if(d[i]+k[i][j]<d[j]) d[j]=d[i]+k[i][j];}
            }
        }
    }
    for(ll i=1;i<n;i++)
    {
        for(ll j=1;j<n;j++) 
        {
            if(k[i][j]!=999999) {if(d[i]+k[i][j]<d[j]) return 0;}
        }
    }

    for(ll i=1;i<n;i++)
    {
        for(ll j=1;j<n;j++)
        {
            if(k[i][j]!=999999) k[i][j]=k[i][j]+d[i]-d[j];
        }
    }
    return 1;
}
//bellmann ford algorithm completed..........................//

//dijkstra using arrays................................//
ll dijkstra_min(vector<ll> &v,vector<ll> &p,ll n)
{
    ll min = 999999,ind = -1;
    for(ll i=1;i<n;i++)
    {
        if(p[i]==0 && min>v[i]) {min = v[i];ind = i;}
    }
    return ind;
}

vector<ll> dijkstra_array(vector<vector<ll>> &k,ll n,ll s)
{
    vector<ll> v(n,999999),parent(n,-1),p(n,0);v[s]=0;
    for(ll i=1;i<n-1;i++)
    {
        ll min = dijkstra_min(v,p,n);
        // cout << i << " ";
        // cout << min << " " << v[min] << endl;
        if(min>0)
        {
            p[min]=1;
            for(ll j=1;j<n;j++)
            {
                if(k[min][j]!=999999 && v[j]>v[min]+k[min][j]) {
                    // cout << v[j] << " ";
                    v[j]=v[min]+k[min][j];parent[j]=min;
                    // cout << v[j] << " " << endl;
                }
            }
        }
        else continue;
    }
    // for(ll i=0;i<n-2;i++)
    // {
    //     cout << i << " ";
    // }
    return v;
}
//dijkstar using arrays completed......................//

//binary heap implementation and later dijkstra using binary heap...........................//
class binary
{
    public:
    ll size=0;
    vector<ll> barr,u,v;
};

ll parent(ll n) {return (n-1)/2;}
ll leftchild(ll n) {return (2*n + 1);}
ll rightchild(ll n) {return (2*n + 2);}

void shiftup(binary &heap,ll i)
{
    ll temp = i;
    while(temp>0 && heap.barr[parent(temp)]>heap.barr[temp])
    {
        swap(heap.barr[parent(temp)],heap.barr[temp]);
        swap(heap.u[parent(temp)],heap.u[temp]);
        swap(heap.v[parent(temp)],heap.v[temp]);
        temp = parent(temp);
    }
    return; 
}

void shiftdown(binary &heap,ll i)
{
    ll temp = i,m=999999,ind = -1;
    ll lf = leftchild(temp);
    if(lf<heap.size && m>heap.barr[lf]) {m=heap.barr[lf];ind = lf;}
    ll rf = rightchild(temp);
    if(rf<heap.size && m>heap.barr[rf]) {m=heap.barr[rf];ind = rf;}
    if(m!=999999 && heap.barr[i]>heap.barr[ind])
    {
        swap(heap.barr[i],heap.barr[ind]);
        swap(heap.u[i],heap.u[ind]);
        swap(heap.v[i],heap.v[ind]);
        shiftdown(heap,ind);
    }
    return;
}

void insert(binary &heap,ll data,ll u,ll v)
{
    if(heap.barr.size()==heap.size) {heap.barr.push_back(data);heap.u.push_back(u);heap.v.push_back(v);}
    else {heap.barr[heap.size] = data;heap.u[heap.size]=u;heap.v[heap.size]=v;}
    heap.size++;
    shiftup(heap,heap.size-1);
    return;
}

vector<ll> extractmin(binary &heap)
{
    ll temp = heap.barr[0],u = heap.u[0],v=heap.v[0];
    heap.barr[0]=heap.barr[heap.size-1];heap.u[0]=heap.u[heap.size-1];heap.v[0]=heap.v[heap.size-1];
    heap.size--;
    shiftdown(heap,0);
    vector<ll> ans={temp,u,v};
    return ans;
}

// vector<ll> dijkstra_binary(vector<vector<ll>> &k,ll n,ll s)
// {
//     vector<ll> dis(n,999999),comp(n,0);dis[s]=0;
//     binary heap;insert(heap,0);
//     map<ll,set<ll>> m;set<ll> ss;ss.insert(s);m[0]=ss;
//     for(ll i=1;i<n-1;i++)
//     {
//         ll min = -1;
//         while(true)
//         {
//             if(heap.size==0) break;
//             ll mi = extractmin(heap);
//             if(!m[mi].empty()) {
//                 min = *(m[mi].begin());m[mi].erase(min);}
//             if(min>0 && comp[min]==0) break;
//         }
//         if(min>0){
//             comp[min]=1;
//             for(ll i=1;i<n;i++){
//                 if(k[min][i]!=999999 && dis[i]>dis[min]+k[min][i]){
//                     dis[i]=dis[min]+k[min][i];
//                     m[dis[i]].insert(i);
//                     insert(heap,dis[i]);
//                 }
//             }
//         }
//     }
//     return dis;
// }

vector<ll> dijkstra_binary(vector<vector<ll>> &k,ll n,ll s)
{
    vector<ll> dis(n,999999);
    binary heap;insert(heap,0,s,s);
    while(heap.size)
    {
        vector<ll> ex = extractmin(heap);
        ll min = ex[0],u = ex[1],v = ex[2];
        if(dis[v]==999999)
        {
            dis[v] = min;
            for(ll i=1;i<n;i++)
            {
                if(k[v][i]!=999999 && dis[i]==999999) insert(heap,k[v][i]+dis[v],v,i);
            }
        }
    }
    return dis;
}
//binary heap related till dijkstar code completed..............................................//

//implemtation of binomial heap and dijkstra algorithm using binomial heap...................//
class bnode
{
    public:
    ll data,u,v,degree;
    bnode *sibling,*child;
};

// void printbheap(bnode **bheap)
// {
//     bnode *temp = *bheap;
//     if(!temp) cout << "EmPtY\n";
//     while(temp)
//     {
//         cout << "data: " << temp->data << " u: " << temp->u << " v: " << temp->v << endl;
//         temp = temp->sibling; 
//     }
// }
// void combine(bnode **p,bnode **c,bnode **prev)
// {
//     bnode *temp = c->
// }
void badjust(bnode **bheap)
{
    if((*bheap)==NULL) return;
    bnode *prev = NULL,*curr = (*bheap),*nex = curr->sibling;
    // cout << "curr: " << curr->degree << endl;
    // if(nex) cout << "nex: " << nex->degree << endl;
    while(curr)
    {
        if(!nex) curr = nex;
        else if(curr->degree != nex->degree)
        {
            prev = curr;
            curr = nex;
            if(nex) nex = nex->sibling;
        }
        else if(curr->degree == nex->degree && nex->sibling && nex->degree == nex->sibling->degree)
        {
            prev = curr;
            curr = nex;
            nex = nex->sibling; 
        }
        else if(curr->data < nex->data)
        {
            // combine(&curr,&nex);
            bnode *temp = curr->child;
            curr->sibling = nex->sibling;
            nex->sibling = NULL;
            if(temp)
            {
                while(temp->sibling) temp = temp->sibling;
                temp->sibling = nex;
            }
            else curr->child = nex;
            curr->degree++;
            nex = curr->sibling;
        }
        else{
            // cout << "else\n";
            // cout << "curr: " << curr->data << " nex: " << nex->data << endl;
            bnode *temp = nex->child;
            if(prev) prev->sibling = nex;
            else (*bheap) = nex;
            curr->sibling = NULL;
            if(temp){
                while(temp->sibling) temp = temp->sibling;
                temp->sibling = curr;
            }
            else nex->child = curr;
            nex->degree++;
            // printbheap(bheap);
            curr = nex;
            nex = nex->sibling; 
        }
    }
    // cout << "\nAfter adjust: " << endl;
    // printbheap(bheap);
    // cout << endl;
    return;
}

void bmerge(bnode **bheap,bnode **temp)
{
    bnode *new_heap = NULL;
    if(!(*bheap)) {(*bheap) = (*temp);return;}
    if(!(*temp)) return;
    if((*bheap)->degree < (*temp)->degree)
    {
        new_heap = (*bheap);
        (*bheap) = (*bheap)->sibling;
        new_heap->sibling = NULL;
    }
    else{
        new_heap = (*temp);
        (*temp) = (*temp)->sibling;
        new_heap->sibling = NULL;
    }
    bnode *t = new_heap;
    while((*bheap)&&(*temp))
    {
        if((*bheap)->degree < (*temp)->degree)
        {
            t->sibling = (*bheap);
            (*bheap) = (*bheap)->sibling;
            t = t->sibling;t->sibling = NULL;
        }
        else{
            t->sibling = (*temp);
            (*temp) = (*temp)->sibling;
            t = t->sibling;t->sibling = NULL;
        }
    }
    while((*bheap))
    {
        // cout << "going to bh: \n";
        t->sibling = (*bheap);
        (*bheap) = (*bheap)->sibling;
        t = t->sibling;t->sibling = NULL;
        // cout << "completed\n";
    }
    // printbheap(&new_heap);
    // cout << "new\n";
    while((*temp))
    {
        t->sibling = (*temp);
        (*temp) = (*temp)->sibling;
        t = t->sibling;t->sibling = NULL;
    }
    (*bheap) = new_heap;
    // printbheap(bheap);
    // cout<< "b:\n";
    badjust(bheap);
    // cout << "merge:\n";
}

void binsert(bnode **bheap,ll data,ll u,ll v)
{
    bnode *temp = new bnode();
    temp->data = data;
    temp->degree = 0;
    temp->u = u;
    temp->v = v;
    temp->sibling = NULL;
    temp->child = NULL;
    if(*bheap == NULL) (*bheap) = temp;
    else bmerge(bheap,&temp);
    // cout << "went " << endl;
}

vector<ll> bextractmin(bnode **bheap)
{
    vector<ll> v(3,-1);
    if(*bheap == NULL) return v;
    bnode *prev = NULL,*curr = (*bheap),*nex = curr->sibling;
    // ll min = curr->data,u = curr->u,v = curr->v;
    bnode *m = curr,*mp = prev,*mn = nex;
    while(curr)
    {
        if(m->data>curr->data){
            mp = prev;mn = nex;m = curr;
        }
        prev = curr;
        curr = nex;
        if(nex) nex = nex->sibling;
    }
    if(mp) mp->sibling = mn;
    else (*bheap) = mn;
    m->sibling = NULL;
    bnode *temp = m->child;
    bmerge(bheap,&temp);
    v[0] = m->data;v[1] = m->u;v[2] = m->v;
    return v;
}

vector<ll> dijkstra_binomial(vector<vector<ll>> &k,ll n,ll s)
{
    vector<ll> dis(n,999999);
    // cout << "be\n";
    bnode *bheap = new bnode();bheap = NULL;
    // cout << "af\n";
    binsert(&bheap,0,s,s);
    // cout << "ai\n";
    while(bheap)
    {
        // cout << "going to loop\n";
        vector<ll> ex = bextractmin(&bheap);
        ll min = ex[0],u = ex[1],v = ex[2];
        // cout << "min: " << min << " u: " << u << " v: " << v << endl;
        if(dis[v]==999999)
        {
            dis[v] = min;
            for(ll i=1;i<n;i++)
            {
                // cout << "i: " << i << " v: " << v << endl;
                // cout << "k[v][i]: " << k[v][i] << endl;
                if(k[v][i]!=999999 && dis[i]==999999) binsert(&bheap,k[v][i]+dis[v],v,i);
                // printbheap(&bheap);
            }
        }
    }
    return dis;
}
//implementation completed...................................................................//

//fibonacci heap implementation.................................................................//
class fnode
{
    public:
    ll data,degree,u,v;
    fnode *child,*parent,*left,*right;
};


void finsert(fnode **fheap,ll data,ll u,ll v)
{
    // cout << "running\n";
    fnode *temp = new fnode();
    temp->data = data;
    temp->degree = 0;
    temp->u = u;
    temp->v = v;
    temp->child = NULL;
    temp->parent = NULL;
    temp->left = temp;
    temp->right = temp;
    // cout << "completed\n";
    if((*fheap) == NULL) (*fheap) = temp;
    else 
    {
        (*fheap)->left->right = temp;
        temp->right = (*fheap);
        temp->left = (*fheap)->left;
        (*fheap)->left = temp;
        if((*fheap)->data > temp->data) (*fheap) = temp;
    }
}

void fmerge(fnode **fheap,fnode **t1,fnode **t2)
{
    //removing t2 from its original place...............//
    (*t2)->right->left = (*t2)->left;
    (*t2)->left->right = (*t2)->right;

    //assigning min and child if obeys the given condition..........//
    // if((*t1)->right == *t1) (*fheap) = (*t1);
    if((*t1)->child == NULL) (*t1)->child = (*t2);

    //making t1 as parent of t2.........................//
    (*t2)->right = (*t2);(*t2)->left = (*t2);
    (*t2)->parent = (*t1);

    //adding t2 to the child of the t1 as it will be the child.....//
    (*t2)->right = (*t1)->child;
    (*t2)->left = (*t1)->child->left;
    (*t1)->child->left->right = (*t2);
    (*t1)->child->left = (*t2);

    if ((*t2)->data < ((*t1)->child)->data)
        (*t1)->child = (*t2);
    
    (*t1)->degree++;
    return;
}

void fadjust(fnode **fheap)
{
    map<ll,fnode*> m;
    // if(!m[0]) cout << "Yes\n";
    fnode *temp = (*fheap);
    do{
        ll d = temp->degree;
        while(m[d])
        {
            fnode *t1 = m[d];
            if(temp->data > t1->data)
            {
                fnode *t = temp;
                temp = t1;
                t1 = t;
            }
            if(t1 == (*fheap)) (*fheap) = temp; 
            fmerge(fheap,&temp,&t1);
            if(temp->right == temp) (*fheap) = temp;
            m[d] = NULL;
            d++;
        }
        m[d] = temp;
        temp = temp->right;
    }
    while(temp != (*fheap));(*fheap) = NULL;
    for(auto &c:m)
    {
        if(c.second)
        {
            c.second->right = c.second;
            c.second->left = c.second;
            if((*fheap))
            {
                (*fheap)->left->right = c.second;
                c.second->right = (*fheap);
                c.second->left = (*fheap)->left;
                (*fheap)->left = c.second;
                if((*fheap)->data > c.second->data) (*fheap) = c.second;
            }
            else (*fheap) = c.second;
        }
    }
}


vector<ll> extractmin(fnode **fheap)
{
    vector<ll> v(3,-1);
    if((*fheap)==NULL) return v;
    else{
        v[0] = (*fheap)->data;v[1] = (*fheap)->u;v[2] = (*fheap)->v;
        fnode *temp = (*fheap),*t = temp,*it = NULL;
        if((*fheap)->child)
        {
            it = temp->child;
            do{
                t = it->right;
                (*fheap)->left->right = it;
                it->right = (*fheap);
                it->left = (*fheap)->left;
                (*fheap)->left = it;
                if(it->data < (*fheap)->data) (*fheap) = it;
                it->parent = NULL;
                it = t;
            }
            while(t != temp->child);
        }
        temp->left->right = temp->right;
        temp->right->left = temp->left;
        if(temp==temp->right && temp->child == NULL) (*fheap)=NULL;
        else{
            (*fheap) = temp->right;
            fadjust(fheap);
        }
    }
    return v;
}

vector<ll> dijkstra_fibonacci(vector<vector<ll>> &k,ll n,ll s)
{
    vector<ll> dis(n,999999);
    // cout << "be\n";
    fnode *fheap = NULL;
    // cout << "af\n";
    finsert(&fheap,0,s,s);
    // cout << "ai\n";
    while(fheap)
    {
        // cout << "going to loop\n";
        vector<ll> ex = extractmin(&fheap);
        ll min = ex[0],u = ex[1],v = ex[2];
        // cout << "min: " << min << " u: " << u << " v: " << v << endl;
        if(dis[v]==999999)
        {
            dis[v] = min;
            for(ll i=1;i<n;i++)
            {
                if(k[v][i]!=999999 && dis[i]==999999) finsert(&fheap,k[v][i]+dis[v],v,i);
            }
        }
    }
    return dis;
}
//fibonacci heap implementation completed......................................................//
 

int main()
{
    ll tt,run;cin >> run;cin >> tt;
    vector<ll> time;ll ts = tt;
    while(tt--)
    {
        ll n,dr,num;cin >> n >> dr;
        vector<vector<ll>> v,temp;
        for(ll i=0;i<=n;i++)
        {
            vector<ll> k;
            for(ll j=0;j<=n;j++)
            {
                if(i==0) k.push_back(0);
                else if(j==0) k.push_back(999999);
                else{
                    cin >> num;k.push_back(num);
                }
            }
            v.push_back(k);
        }
        temp = v;
        // find_parents(v,n+1);
        // vector<ll> parent(n+1,0);
        // printv(parent,n);
        // printvec(v,n+1);
        vector<ll> d(n+1,999999);
        clock_t start = clock();
        if(bellmann_ford(temp,n+1,d))
        {
            vector<vector<ll>> ans;
            // printvec(temp,n+1);
            // printv(d,n+1);
            if(run==1)
            {
                vector<ll> s(n+1,0);
                ans.push_back(s);
                for(ll i=1;i<=n;i++)
                {
                    // cout << "For source " << i << endl;
                    s = dijkstra_array(temp,n+1,i);
                    // printv(s,n+1);
                    ans.push_back(s);
                }
                // cout << "Ans array: " << endl;
                // printvec(ans,n+1);
                for(ll i=1;i<=n;i++)
                {
                    for(ll j=1;j<=n;j++)
                    {
                        if(ans[i][j]!=999999) ans[i][j]=ans[i][j]-d[i]+d[j];
                    }
                }
                printvec(ans,n+1);
                // cout << "printing done" << endl;
            }
            else if(run==2)
            {
                vector<ll> s(n+1,0);
                ans.push_back(s);
                for(ll i=1;i<=n;i++)
                {
                    // cout << "For source " << i << endl;
                    s = dijkstra_binary(temp,n+1,i);
                    // printv(s,n+1);
                    ans.push_back(s);
                }
                // cout << "Ans array: " << endl;
                // printvec(ans,n+1);
                for(ll i=1;i<=n;i++)
                {
                    for(ll j=1;j<=n;j++)
                    {
                        if(ans[i][j]!=999999) ans[i][j]=ans[i][j]-d[i]+d[j];
                    }
                }
                printvec(ans,n+1);
            }
            else if(run==3)
            {
                vector<ll> s(n+1,0);
                ans.push_back(s);
                for(ll i=1;i<=n;i++)
                {
                    // cout << "For source " << i << endl;
                    s = dijkstra_binomial(temp,n+1,i);
                    // printv(s,n+1);
                    ans.push_back(s);
                }
                // cout << "Ans array: " << endl;
                // printvec(ans,n+1);
                for(ll i=1;i<=n;i++)
                {
                    for(ll j=1;j<=n;j++)
                    {
                        if(ans[i][j]!=999999) ans[i][j]=ans[i][j]-d[i]+d[j];
                    }
                }
                printvec(ans,n+1);
            }
            else
            {
                vector<ll> s(n+1,0);
                ans.push_back(s);
                for(ll i=1;i<=n;i++)
                {
                    // cout << "For source " << i << endl;
                    s = dijkstra_fibonacci(temp,n+1,i);
                    // printv(s,n+1);
                    ans.push_back(s);
                }
                // cout << "Ans array: " << endl;
                // printvec(ans,n+1);
                for(ll i=1;i<=n;i++)
                {
                    for(ll j=1;j<=n;j++)
                    {
                        if(ans[i][j]!=999999) ans[i][j]=ans[i][j]-d[i]+d[j];
                    }
                }
                printvec(ans,n+1);
            }
            // cout << "time:" << end-start << endl;
        }
        else
        {
            // vector<ll> s;
            for(ll i=0;i<n;i++) cout << "-1\n";
            // vector<vector<ll>> ans;
            // for(ll i=0;i<n+1;i++) ans.push_back(s);
            // printvec(ans,n+1);
        }
        clock_t end = clock();
        time.push_back(end-start);
        // printv(parent,n+1);
    }
    for(ll i=0;i<ts;i++) cout << time[i] << " ";cout << endl;
    return 0;
}
