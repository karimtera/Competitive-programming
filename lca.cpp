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

void dfs(int idx ,int h=0){
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

void build(int node,int l,int r){
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

int query(int node,int l,int r,int ql,int qr){
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

int lca(int v1,int v2){
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
        int ans=0;
        for(int i=0;i<3;i++){
            for(int j=0;j<3;j++){
                if(i==j) continue;
                for(int k=0;k<3;k++){
                    if(k==j||k==i) continue;
                    int v1=a[i];
                    int v2=a[j];
                    int v3=a[k];
                    int lca1=lca(v1,v3);
                    int lca2=lca(v2,v3);
                    int d1=height[v3]-height[lca1]+1;
                    int d2=height[v3]-height[lca2]+1;
                    int tmp=min(d1,d2);
                    int lca12=lca(v1,v2);
                    if(lca1!=lca2||lca12==lca1){
                        ans=max(ans,tmp);
                        continue;
                    }
                    tmp+=(height[lca12]-height[lca1]);
                    ans=max(ans,tmp);
                }
            }
        }
        printf("%d\n",ans);
    }
    return 0;
}
