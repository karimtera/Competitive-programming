#include <bits/stdc++.h>
#define x first
#define y second
using namespace std;
const int sz=1e6+9;
int n,m;
vector<pair<int,int>> q;
stack<pair<char,int>> s;
char a[sz];
int segtree[5*sz];
bool cl[sz];
int pos[sz];
int ans[sz];
int myr[sz],myl;

// based on tutorial: https://www.hackerearth.com/practice/data-structures/advanced-data-structures/segment-trees/tutorial/
// build: O(n)
// point update: O(logn)
// range query: O(logn)

// problem name: C. Sereja and Brackets
// problem link: https://codeforces.com/contest/380/problem/C

void build(int node,int left,int right){
    if(left==right){
        segtree[node]=cl[left];
        return;
    }
    int mid=(left+right)>>1;
    build(2*node,left,mid);
    build(2*node+1,mid+1,right);
    segtree[node]=segtree[2*node]+segtree[2*node+1];
}

void update(int node,int left,int right,int pos,int v){
    if(left==right){
        segtree[node]+=v;
        return;
    }
    int mid=(left+right)>>1;
    // check if the update position is in my left or right child
    if(pos>=left&&pos<=mid) update(2*node,left,mid,pos,v);
    else update(2*node+1,mid+1,right,pos,v);
    // update my node because one of my children is updated
    segtree[node]=segtree[2*node]+segtree[2*node+1];
}

int query(int node,int left,int right,int l,int r){
    // left, right are the node range
    // l, r are the query range
    //case 1: node range is all outside the query range
    if(left>r||right<l) return 0;
    // case 2: node range is all included in the query range
    if(left>=l&&right<=r) return segtree[node];
    // case 3: query range is partially included in the node range
    int mid=(left+right)>>1;
    int child1=query(2*node,left,mid,l,r);
    int child2=query(2*node+1,mid+1,right,l,r);
    return child1+child2;
}

int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    scanf("%s",a+1);
    n=strlen(a+1);
    for(int i=1;i<=n;i++){
        if(a[i]=='(') s.push(make_pair(a[i],i));
        else if(s.empty()) continue;
        else{
            pos[s.top().y]=i;
            cl[i]=1;
            s.pop();
        }
    }
    build(1,1,n);
    scanf("%d",&m);
    for(int i=0;i<m;i++){
        scanf("%d %d",&myl,&myr[i]);
        q.push_back(make_pair(myl,i));
    }
    sort(q.begin(),q.end());
    int st=1;
    for(int i=0;i<m;i++){
        auto u=q[i];
        while(u.x>st){
            if(!pos[st]){
                st++;
                continue;
            }
            update(1,1,n,pos[st],-1);
            st++;
        }
        ans[u.y]=query(1,1,n,1,myr[u.y]);
    }
    for(int i=0;i<m;i++) printf("%d\n",ans[i]<<1);
    return 0;
}
