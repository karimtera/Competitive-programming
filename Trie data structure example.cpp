#include <bits/stdc++.h>
#define CHAR_SIZE 27
using namespace std;
char a[1509],b[29];
int k,n,ans;
bool f[26];

// D- Good Substrings (cf)

struct Trie{
	Trie* character[CHAR_SIZE];
	Trie(){
		for(int i=0;i<CHAR_SIZE;i++) this->character[i]=nullptr;
	}
};
Trie* head = new Trie();

int main(){
    scanf("%s%s",a,b);
    n=strlen(a);
    for(int i=0;i<26;i++){
        if(b[i]=='0') f[i]=1;
    }
    scanf("%d",&k);
    Trie* pp;
    for(int i=0;i<n;i++){
        pp=head;
        int cnt=0;
        for(int j=i;j<n;j++){
            int idx=a[j]-'a';
            cnt+=(f[idx]);
            if(cnt>k) break;
            if(pp->character[idx]==nullptr){
                pp->character[idx]= new Trie();
                ans++;
            }
            pp=(pp->character[idx]);
        }
    }
    printf("%d",ans);
	return 0;
}
