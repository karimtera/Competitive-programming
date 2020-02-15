// merge sort tree: segment tree which has vectors in each node
// usually used to get the number of distinct elements in a subarray
// create array prv, such that prv_i is the previous position of element array_i, o.w. prv_i=-1
// then build the tree with array prv
// now query over a range with number x, returns the number of distnict elements in this range that is less than x
// example: E. educational round 80 cf
// another trick used here:
// how to get number of elements greater than x in a prefix of an array? 
// use segment tree (called segtree2 here) on an array, such that array_i=1 if we process this element, o.w. array_i=0
// now query on sum over any range



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
const int sz=3e5+9;
int n,m;
int a[sz];
vector<int> pos[sz];
pii ans[sz];

bool done[sz];



int prv[sz];
vector<int> segtree[4*sz];
vector<int> em;


void build(int node,int l,int r){
	if(l==r){
		segtree[node].pb(prv[l]);
		return;
	}
	int mid=(l+r)>>1;
	int son1=node<<1;
	int son2=son1+1;
	build(son1,l,mid);
	build(son2,mid+1,r);
	segtree[node].resize(r-l+1);
	merge(all(segtree[son1]),all(segtree[son2]),segtree[node].begin());
}

int query(int node,int l,int r,int ql,int qr,int val){
	if(l>qr||r<ql) return 0;
	if(l>=ql&&r<=qr) return lower_bound(all(segtree[node]),val)-segtree[node].begin();
	int mid=(l+r)>>1;
	int son1=node<<1;
	int son2=son1+1;
	int q1=query(son1,l,mid,ql,qr,val);
	int q2=query(son2,mid+1,r,ql,qr,val);
	return q1+q2; 
}


int segtree2[4*sz];
int b[sz];

void update(int node,int l,int r,int pos,int val){
	if(l==r){
		segtree2[node]=b[l]=1;
		return;
	}
	int mid=(l+r)>>1;
	int son1=node<<1;
	int son2=son1+1;
	if(pos>=l&&pos<=mid) update(son1,l,mid,pos,val);
	else update(son2,mid+1,r,pos,val);
	segtree2[node]=segtree2[son1]+segtree2[son2];
}

int query2(int node,int l,int r,int ql,int qr){
	if(l>qr||r<ql) return 0;
	if(l>=ql&&r<=qr) return segtree2[node];
	int mid=(l+r)>>1;
	int son1=node<<1;
	int son2=son1+1;
	int q1=query2(son1,l,mid,ql,qr);
	int q2=query2(son2,mid+1,r,ql,qr);
	return q1+q2;
}



int main(){
	scanf("%d %d",&n,&m);
	for(int i=1;i<=n;i++) ans[i].f=ans[i].s=i;
	for(int i=0;i<m;i++){
		scanf("%d",&a[i]);
		ans[a[i]].f=1;
		pos[a[i]].pb(i);
	}
	for(int i=1;i<=n;i++){
		int curr=-1;
		for(auto u:pos[i]){
			prv[u]=curr;
			curr=u;
		}
		if(pos[i].empty()) em.pb(i);
	}
	build(1,0,m-1);
	for(int i=1;i<=n;i++){
		if(pos[i].empty()) continue;
		for(int j=0;j+1<pos[i].size();j++){
			int l=pos[i][j]+1;
			int r=pos[i][j+1]-1;
			if(l>r) continue;
			int res=query(1,0,m-1,l,r,l);
			ans[i].s=max(ans[i].s,res+1);	
		}
		int lst=pos[i].back()+1;
		if(lst<=m-1){
			int res=query(1,0,m-1,lst,m-1,lst);
			ans[i].s=max(ans[i].s,res+1);
		}
	}
	for(int i=0;i<m;i++){
		if(done[a[i]]) continue;
		update(1,1,n,a[i],1);
		int res=query2(1,1,n,a[i]+1,n);
		ans[a[i]].s=max(ans[a[i]].s,a[i]+res);
		done[a[i]]=1;
	}
	for(auto u:em){
		int res=query2(1,1,n,u+1,n);
		ans[u].s=max(ans[u].s,u+res);
	}
	for(int i=1;i<=n;i++) printf("%d %d\n",ans[i].f,ans[i].s);
	return 0;
}

