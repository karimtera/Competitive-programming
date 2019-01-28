#include <bits/stdc++.h>
using namespace std;
long long tree[int(4e5+9)][6];
long long k,ans;
int n,m,stidx[int(2e5+9)],ST;
void maxi(long long& a,long long b){a=max(a,b);}

long long query(int st,int en,int t){
    st+=ST; en+=ST;
    long long ret=0;
    while(st<=en){
        if(st&1) maxi(ret,tree[st++][t]);
        if((en&1)==0) maxi(ret,tree[en--][t]);
        st>>=1;
        en>>=1;
    }
    return ret;
}

void best(int st,int len){
    for(int j=0;j<m;j++){
        printf("%I64d ",query(st,st+len-1,j));
    }
}

bool ok(int len){
    for(int i=0;i+len-1<n;i++){
        bool f=1;
        long long sum=0;
        for(int j=0;j<m;j++){
            sum+=query(i,i+len-1,j);
            if(sum>k) {f=0;break;}
        }
        if(f){
            stidx[len]=i;
            return 1;
        }
    }
    return 0;
}

int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    scanf("%d %d %I64d",&n,&m,&k);
    int N=ceil(log2(n));
    ST=(1LL<<N);
    for(int i=ST;i<ST+n;i++){
        for(int j=0;j<m;j++) scanf("%I64d",&tree[i][j]);
    }
    for(int i=ST-1;i>0;i--){
        for(int j=0;j<m;j++) tree[i][j]=max(tree[i<<1][j],tree[(i<<1)+1][j]);
    }
    int st=0,en=n;
    while(st<en){
        int mid=(st+en+1)>>1;
        if(ok(mid)) st=mid;
        else en=mid-1;
    }
    best(stidx[st],st);
    //puts("");
    //for(int i=1;i<ST+n;i++) cout<<tree[i][0]<<" ";
    return 0;
}
