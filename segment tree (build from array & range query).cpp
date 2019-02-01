#include <bits/stdc++.h>
using namespace std;
int n,m;
const int sz=1e5+9;
int l[sz],r[sz],q[sz];
int segtree[4*sz];
int cs[33][sz];
int a[sz];
int mx=(1<<30)-1;

void build(int node,int left,int right){
    if(left==right){
        segtree[node]=a[left];
        return;
    }
    int mid=(left+right)>>1;
    build(2*node,left,mid);
    build(2*node+1,mid+1,right);
    segtree[node]=segtree[2*node]&segtree[2*node+1];
}

int query(int node,int left,int right,int l,int r){
    if(right<l||left>r) return mx;
    if(l<=left&&r>=right) return segtree[node];
    int mid=(left+right)>>1;
    int lson=query(2*node,left,mid,l,r);
    int rson=query(2*node+1,mid+1,right,l,r);
    return lson&rson;
}

int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    scanf("%d %d",&n,&m);
    for(int i=0;i<m;i++){
        scanf("%d %d %d",&l[i],&r[i],&q[i]);
        for(int k=0;k<30;k++){
            if(q[i]&(1<<k)){
                cs[k][l[i]]++;
                cs[k][r[i]+1]--;
            }
        }
    }
    for(int k=0;k<30;k++){
        for(int i=1;i<=n;i++) cs[k][i]+=cs[k][i-1];
    }
    for(int i=1;i<=n;i++){
        for(int k=0;k<30;k++){
            if(cs[k][i]>0) a[i]|=(1<<k);
        }
    }
    build(1,1,n);
    for(int i=0;i<m;i++){
        if(query(1,1,n,l[i],r[i])!=q[i]){
            puts("NO");
            return 0;
        }
    }
    puts("YES");
    for(int i=1;i<=n;i++) printf("%d ",a[i]);
    return 0;
}
