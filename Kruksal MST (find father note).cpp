#include <bits/stdc++.h>
using namespace std;
#define x first
#define y second
#define mp make_pair
typedef pair<long long,pair<int,int>> edge;

int n,m;
long long a[int(2e5+9)],w;
int p[int(2e5+9)];

int findp(int a){
    return (a==p[a]?a:(p[a]=findp(p[a])));  // note that this is faster than the iterative method as this one assigns findp(p[a]) to p[a] directly
}

bool same(int a,int b){
    a=findp(a);
    b=findp(b);
    return a==b;
}


void unite(int a,int b){
    a=findp(a);
    b=findp(b);
    p[b]=a;
    return;
}

int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    scanf("%d %d",&n,&m);
    for(int i=1;i<=n;i++) scanf("%I64d",&a[i]);
    vector<edge> e(m);
    for(int i=0;i<m;i++) scanf("%d %d %I64d",&e[i].y.x,&e[i].y.y,&e[i].x);

    int z=min_element(a+1,a+n+1)-a;
    for(int i=1;i<=n;i++){
        if(i==z) continue;
        e.push_back(mp(a[i]+a[z],mp(i,z)));
    }
    sort(e.begin(),e.end());
    long long ans=0;
    for(int i=1;i<=n;i++) p[i]=i;
    for(auto u:e){
        int X=u.y.x;
        int Y=u.y.y;
        long long W=u.x;
        if(!same(X,Y)){
            ans+=W;
            unite(X,Y);
        }
    }
    printf("%I64d",ans);
    return 0;
}
