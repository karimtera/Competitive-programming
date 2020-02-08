#include <bits/stdc++.h>
using namespace std;
const int sz=2e5+1,sz2=1<<26;
int n,k;
int p[sz];
int q[sz];
vector<int> v[sz],vr[sz];
vector<int> myl;
bool visited[sz];
char ans[sz];
int cnt;

void dfs1(int i){
    visited[i]=1;
    for(auto u:v[i]){
        if(visited[u]) continue;
        dfs1(u);
    }
    myl.push_back(i); // add a node after being completely processed
}

void dfs2(int i){
    visited[i]=1;
    for(auto u:vr[i]){ // loop on reversed edges
        if(visited[u]) continue;
        dfs2(u);
    }
    // you have a new element in the current scc
}

int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    for(int i=1;i<=n;i++){
        if(!visited[i]) dfs1(i);
    }
    memset(visited,0,sizeof(visited));
    for(int i=myl.size()-1;i>=0;i--){
        int u=myl[i];
        if(visited[u]) continue;
        dfs2(u);
        cnt++;
    }
    return 0;
}
