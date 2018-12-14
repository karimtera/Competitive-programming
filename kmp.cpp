vector<int> computeprefix(vector<int> pat){
    int m=pat.size();
    vector<int> longestPrefix(m);
    for(int i=1,k=0;i<m;i++){
        while(k>0&&pat[k]!=pat[i]) k=longestPrefix[k-1];
        if(pat[k]==pat[i]) longestPrefix[i]=++k;
        else longestPrefix[i]=k;
    }
    return longestPrefix;
}

int kmp(vector<int> s,vector<int>pat){
    int n=s.size();
    int m=pat.size();
    int cnt=0;
    vector<int> ans,lp=computeprefix(pat);
    //for(int u:lp) printf("%d ",u);
    for(int i=0,k=0;i<n;i++){
        while(k>0&&pat[k]!=s[i]) k=lp[k-1];
        if(pat[k]==s[i]) k++;
        if(k==m){
            cnt++;
            k=lp[k-1];
        }
    }
    return cnt;
}
