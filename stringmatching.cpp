// i hope i get better                                                           
#include <bits/stdc++.h>
#define mp make_pair
#define pb push_back
#define f first
#define s second
#define all(x) x.begin(), x.end()
using namespace std;
typedef long long ll;
typedef vector<int> vi;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;
const int sz=1e6+9;
int n,m;
string s,p;

vi prefix_function(string pat){
	int m=pat.size();
	vi ret(m);
	ret[0]=0;
	for(int i=1;i<m;i++){
		int j=ret[i-1];
		while(j>0&&pat[j]!=pat[i]) j=ret[j-1];
		j+=(pat[j]==pat[i]);
		ret[i]=j;
	}
	return ret;
}

int main(){
	cin>>s>>p;
	n=s.size();
	m=p.size();
	vi pi=prefix_function(p);
	int ans=0;
	int j=0;
	for(int i=0;i<n;i++){
		while(j>0&&s[i]!=p[j]) j=pi[j-1];
		j+=(s[i]==p[j]);
		if(j==m){
			ans++;
			j=pi[j-1];
		}
	}
	cout<<ans;
	return 0;
}