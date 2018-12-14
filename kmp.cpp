#include <bits/stdc++.h>
using namespace std;
string s;

vector<int> computeprefix(string pat){
    int m=pat.size();
    vector<int> longestPrefix(m);
    for(int i=1,k=0;i<m;i++){
        while(k>0&&pat[k]!=pat[i]) k=longestPrefix[k-1];
        if(pat[k]==pat[i]) longestPrefix[i]=++k;
        else longestPrefix[i]=k;
    }
    return longestPrefix;
}

bool kmp(string s,string pat){
    int n=s.size();
    int m=pat.size();
    vector<int> ans,lp=computeprefix(pat);
    for(int i=1,k=0;i<n;i++){
        while(k>0&&pat[k]!=s[i]) k=lp[k-1];
        if(pat[k]==s[i]) k++;
        if(k==m){
            return (i-m+1<n-m);
            k=lp[k-1];
        }
    }
    return 0;
}
