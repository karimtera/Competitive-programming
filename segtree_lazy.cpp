// i hope i get better                                                           
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
int n,m,L[sz],R[sz],X[sz],T[sz];
int a[sz],A[sz];
ll ans[sz];


int segtree[4*sz];
int lazy[4*sz];

// segment tree with lazy updates
// build: O(n)
// range update: O(logn)
// range query: O(logn)

// lazy[node]=1 or (marked with some update) means:
// 'node' is already updated, but the childern are not updated (we'll push the update when needed)

// note: we need to push the updates just in case we traverse to a node's childern

void push(int node,int l,int r){
	// push update query to 'node' childern
	// this requires:
	// 1) unmark lazy[node] (it means that our childern doesn't need to be updated)
	// 2) update segtree[son1], segtree[son2] (acutally update 'node' childern)
	// 3) mark lazy[son1], lazy[son2] (as 'node' grandsons will have a pending update) 
	if(!lazy[node]) return;
	int mid=(l+r)>>1;
	int son1=node<<1;
	int son2=son1+1;
	lazy[node]=0;
	lazy[son1]^=1;
	lazy[son2]^=1;
	segtree[son1]=(mid-l+1)-segtree[son1];
	segtree[son2]=(r-mid)-segtree[son2];
}

void build(int node,int l,int r){
	lazy[node]=0; // reset all the updates
	if(l==r){
		segtree[node]=a[l];
		return;
	}
	int mid=(l+r)>>1;
	int son1=node<<1;
	int son2=son1+1;
	build(son1,l,mid);
	build(son2,mid+1,r);
	segtree[node]=segtree[son1]+segtree[son2];	
}

void update(int node,int l,int r,int ql,int qr,int v){
	if(l>qr||r<ql) return; // node range is outside the query range
	if(l>=ql&&r<=qr){ // node range is all inside the query range
		segtree[node]=(r-l+1)-segtree[node];
		lazy[node]^=v;
		return;
	}
	// query range is partially inside the node range
	push(node,l,r); // push the update to my childern, as we traverse to them
	int mid=(l+r)>>1;
	int son1=node<<1;
	int son2=son1+1;
	update(son1,l,mid,ql,qr,v);
	update(son2,mid+1,r,ql,qr,v);
	segtree[node]=segtree[son1]+segtree[son2]; // update me as my childern are updated
}

int query(int node,int l,int r,int ql,int qr){
	if(l>qr||r<ql) return 0; // node range is outside the query range
	if(l>=ql&&r<=qr) return segtree[node]; // node range is all inside the query range
	// query range is partially inside the node range
	push(node,l,r); // push the update to my childern, as we traverse to them
	int mid=(l+r)>>1;
	int son1=node<<1;
	int son2=son1+1;
	int q1=query(son1,l,mid,ql,qr);
	int q2=query(son2,mid+1,r,ql,qr);
	return q1+q2;
}

int main(){
	/*
	cin>>n;
	for(int i=0;i<n;++i){
		cin>>A[i];
	}
	cin>>m;
	for(int i=0;i<m;++i){
		cin>>T[i]>>L[i]>>R[i];
		L[i]--;
		R[i]--;
		if(T[i]==2) cin>>X[i]; 
	}
	for(int i=0;i<21;++i){
		ll val=(1ll<<i);
		for(int j=0;j<n;++j){
			a[j]=(A[j]>>i)&1;
		}
		build(1,0,n-1);
		for(int j=0;j<m;++j){
			if(T[j]==1) ans[j]+=val*query(1,0,n-1,L[j],R[j]);
			else if((X[j]>>i)&1) update(1,0,n-1,L[j],R[j],1);
		}
	}
	for(int i=0;i<m;++i){
		if(T[i]==1) cout<<ans[i]<<'\n';
	}
	*/
	return 0;
}
