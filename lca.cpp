#include <bits/stdc++.h>
using namespace std;
const int sz=1e5+9;
int first[sz];
vector<int> eu;
int lst;
int height[sz];
int segtree[12*sz];
int visited[sz];
vector<int> v[sz];

// lowest common ancestor using euler paths
// o(n) preprocessing
// o(logn) for queries

void dfs(int idx ,int h=0){ // to construct the euler path vector 
    visited[idx]=1;
    height[idx]=h;
    first[idx]=eu.size();
    eu.push_back(idx);
    for(auto u:v[idx]){
        if(visited[u]) continue;
        dfs(u,h+1);
        eu.push_back(idx);
    }
}

void build(int node,int l,int r){ // to build the segment tree 
    if(l==r){
        segtree[node]=eu[l];
        return;
    }
    int mid=(l+r)>>1;
    int son=node<<1;
    build(son,l,mid);
    build(son+1,mid+1,r);
    if(height[segtree[son]]>height[segtree[son+1]]) segtree[node]=segtree[son+1];
    else segtree[node]=segtree[son];
}

int query(int node,int l,int r,int ql,int qr){ // to query on the segment tree
    if(l>qr||r<ql) return -1;
    if(l>=ql&&r<=qr) return segtree[node];
    int mid=(l+r)>>1;
    int son=node<<1;
    int d1=query(son,l,mid,ql,qr);
    int d2=query(son+1,mid+1,r,ql,qr);
    if(d1==-1) return d2;
    else if(d2==-1) return d1;
    if(height[d1]>height[d2]) return d2;
    else return d1;
}

int lca(int v1,int v2){ // to get the lca
    int A=first[v1];
    int B=first[v2];
    if(A>B) swap(A,B);
    return query(1,0,lst,A,B);
}

int n,q;
int p;
int a[3];

int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    scanf("%d %d",&n,&q);
    for(int i=2;i<=n;i++){
        scanf("%d",&p);
        v[p].push_back(i);
        v[i].push_back(p);
    }
    dfs(1);
    lst=eu.size()-1;
    build(1,0,lst);
    while(q--){
        scanf("%d %d %d",&a[0],&a[1],&a[2]);
        cout<<lca(a[0],a[1]);
    }
    return 0;
}
