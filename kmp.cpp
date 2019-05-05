vector<int> prefix_function(string s) {
    int n=s.size();
    vector<int> pi(n);
    for (int i = 1; i < n; i++) {
        int j = pi[i-1];
        while (j > 0 && s[i] != s[j])
            j = pi[j-1];
        if (s[i] == s[j])
            j++;
        pi[i] = j;
    }
    return pi;
}


int kmp(string s,string pat){
    int n=s.size();
    int m=pat.size();
    int cnt=0;
    vector<int> lp=prefix_function(pat);
    for(int i=0,k=0;i<n;i++){
        while(k>0&&pat[k]!=s[i]) k=lp[k-1];
        if(pat[k]==s[i]) k++;
        if(k==m){
            cnt++; %% found occurance at position i-k
            k=lp[k-1];
        }
    }
    return cnt;
}
