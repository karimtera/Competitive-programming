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
const int sz=1e6+9;
const ll A=911382323;
const ll B[2]={972663749,1000000321};

ll p[sz][2];

void pre(){
	// calcuates the values of A^i mod the 2 Bs
	p[0][0]=p[0][1]=1;
	for(int i=1;i<sz;i++){
		p[i][0]=(p[i-1][0]*A)%B[0];
		p[i][1]=(p[i-1][1]*A)%B[1];
	}
}

void hashit(string &str,ll hash[][2]){	
	// send the string, and the array to fill the hash (2nd dimension is for the 2 Bs)
	ll val=str[0]-'a'+1;
	hash[0][0]=hash[0][1]=val;
	for(int i=1;i<str.size();i++){
		val=str[i]-'a'+1;
		hash[i][0]=(hash[i-1][0]*A+val)%B[0];
		hash[i][1]=(hash[i-1][1]*A+val)%B[1];
	}	
}

pll range(ll hash[][2],int l,int r){
	// returns the substring hash value
	// send the string's hash table, and the indices of the substring
	pll ret;
	if(!l){
		ret.f=hash[r][0];
		ret.s=hash[r][1];
		return ret;
	} 
	ret.f=((hash[r][0]-hash[l-1][0]*p[r-l+1][0])%B[0]+B[0])%B[0];
	ret.s=((hash[r][1]-hash[l-1][1]*p[r-l+1][1])%B[1]+B[1])%B[1];
	return ret;
}


/*
string str;
ll h[sz][2];
int n;

bool can(int x){
	auto pre=range(h,0,x-1);
	auto suf=range(h,n-x,n-1);
	if(pre!=suf) return 0;
	pll tmp;
	for(int i=1;i<n-x;i++){
		tmp=range(h,i,i+x-1);
		if(tmp==pre) return 1;
	}
	return 0;
}
*/

int main(){
	pre();
	/*
	cin>>str;
	n=str.size();
	hashit(str,h);
	for(int i=n-2;i>0;i--){
		if(can(i)){
			for(int j=0;j<i;j++) cout<<str[j];
			return 0;
		}
	}
  cout<<"Just a legend";
  */
  return 0;
}
