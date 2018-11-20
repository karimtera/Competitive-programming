#include <bits/stdc++.h>
using namespace std;
int n,a[int(1e5+9)];
int tail[int(1e5+9)];

// Solution to codeforces div2 D. Bubble Sort Graph (round 198)

int lis_nlogn(int A[],int s){ // s is the size of array A
    // this function finds the lis (strictly increasing)
    if(s==0) return 0;
    int l=0;
    tail[l++]=A[0];
    for(int i=1;i<s;i++){
        if(A[i]>tail[l-1]) tail[l++]=A[i];
        else{
            int idx=find(tail,tail+l,A[i])-tail;
            if(idx!=l) continue;
            else{
                idx=upper_bound(tail,tail+l,A[i])-tail;
                tail[idx]=A[i];
            }
        }
    }
    return l;
}

int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    scanf("%d",&n);
    for(int i=0;i<n;i++) scanf("%d",&a[i]);
    printf("%d",lis_nlogn(a,n));
    return 0;
}
