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
const int sz=1e5+9;
const ll A=911382323;
const ll B[2]={972663749,1000000321};

pll p[sz];

void pre(){
	// calcuates the values of A^i mod the 2 Bs
	p[0].f=p[0].s=1;
	for(int i=1;i<sz;i++){
		p[i].f=(p[i-1].s*A)%B[0];
		p[i].s=(p[i-1].s*A)%B[1];
	}
}

void hashit(string &str,pll hash[]){	
	// send the string, and the array to fill the hash (2nd dimension is for the 2 Bs)
	ll val=str[0]-'a'+1;
	hash[0].f=hash[0].s=val;
	for(int i=1;i<str.size();i++){
		val=str[i]-'a'+1;
		hash[i].f=(hash[i-1].f*A+val)%B[0];
		hash[i].s=(hash[i-1].s*A+val)%B[1];
	}	
}

pll range(pll hash[],int l,int r){
	// returns the substring hash value
	// send the string's hash table, and the indices of the substring
	pll ret;
	if(!l){
		ret.f=hash[r].f;
		ret.s=hash[r].s;
		return ret;
	} 
	ret.f=((hash[r].f-hash[l-1].f*p[r-l+1].f)%B[0]+B[0])%B[0];
	ret.s=((hash[r].s-hash[l-1].s*p[r-l+1].s)%B[1]+B[1])%B[1];
	return ret;
}

int n,k;
ll ans,a[sz];
string str;
pll h[sz],rh[sz],t[sz];

int main(){
	pre();
	// cin>>k>>n;
	// for(int i=0;i<k;i++){
	// 	cin>>str>>a[i];
	// 	hashit(str,t);
	// 	h[i]=t[n-1];
	// }
	return 0;
}
