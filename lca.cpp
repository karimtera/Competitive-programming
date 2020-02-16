//    _____ _     _                _           _     _ _     _     
//    \_   \ |_  (_)___  __      _| |__   __ _| |_  (_) |_  (_)___ 
//     / /\/ __| | / __| \ \ /\ / / '_ \ / _` | __| | | __| | / __|
//  /\/ /_ | |_  | \__ \  \ V  V /| | | | (_| | |_  | | |_  | \__ \
//  \____/  \__| |_|___/   \_/\_/ |_| |_|\__,_|\__| |_|\__| |_|___/
//                                                                 
#include <bits/stdc++.h>
#define mp make_pair
#define pb push_back
#define f first
#define s second
#define all(x) x.begin(), x.end()
using namespace std;
typedef long long ll;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;
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
// also can get distance between any two nodes in tree in o(logn) for a query
// this is: https://codeforces.com/contest/1304/problem/E

void dfs(int idx ,int h=0){ // to construct the euler path vector and height array
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

void build(int node,int l,int r){ // to build the segment tree (get rmq on euler tour vector)
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

int distance(int v1,int v2){ // return distance between two nodes
	int LCA=lca(v1,v2);
	return height[v1]+height[v2]-(height[LCA]<<1);
}


int n,q;
int U,V;
int x,y,a,b,k;

int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    scanf("%d",&n);
    for(int i=2;i<=n;i++){
        scanf("%d %d",&U,&V);
        v[U].pb(V);
        v[V].pb(U);
    }
    dfs(1);
    lst=eu.size()-1;
    build(1,0,lst);
    scanf("%d",&q);
    while(q--){
        scanf("%d %d %d %d %d",&x,&y,&a,&b,&k);
        int d1=distance(a,b);
        int d2=distance(a,x)+distance(y,b)+1;
        int d3=distance(a,y)+distance(x,b)+1;
        bool b1=d1&1;
        bool b2=d2&1;
        bool b3=d3&1;
        bool K=k&1;
       	if((b1==K&&k>=d1)||(b2==K&&k>=d2)||(b3==K&&k>=d3)) puts("YES");
       	else puts("NO");
    }
    return 0;
}
