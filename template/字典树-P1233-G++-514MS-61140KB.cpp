#include <cstring>
#include <cstdio>
using namespace std;

const int maxn = 500005;

struct node
{
	bool isWord;
	char trans[22];
	int next[26];
	inline void reuse(){
		isWord = 0;
		for (int i = 0; i < 26; ++i)
		{
			next[i] = -1;
		}
	}
}Node[maxn];

class Trietree{
private:
	int root;
	int sign;
public:
	Trietree(){
		sign = 0;
		root = sign ++;
		Node[root].reuse();
	}
	void insert(char *a, char *b){
		int now = root;
		for (int i = 0; a[i] != '\0'; ++i){
			int cur = a[i] - 'a';
			if(Node[now].next[cur] == -1){
				Node[now].next[cur] = sign ++;
				Node[Node[now].next[cur]].reuse();
			}
			now = Node[now].next[cur];
		}
		Node[now].isWord = 1;
		strcpy(Node[now].trans, b);
	}
	void find(char *a){
		int now = root;
		for (int i = 0; a[i] != '\0'; ++i){
			int cur = a[i] - 'a';
			if(Node[now].next[cur] == -1){
				printf("%s", a);
				return ;
			}
			now = Node[now].next[cur];
		}
		if(Node[now].isWord)
			printf("%s", Node[now].trans);
		else
			printf("%s", a);
	}
}trie;

char a[500005], b[500005];
int main(int argc, char const *argv[])
{
	// freopen("E:\\in.txt", "r", stdin);
	while(~scanf("%s", a)){
		if(!strcmp(a, "START"))
			continue;
		else if(!strcmp(a, "END")){
			break;
		}
		scanf("%s", b);
		trie.insert(b, a);
	}
	getchar();
	int k = 0;
	while(gets(a)){
		if(!strcmp(a, "START"))
			continue;
		else if(!strcmp(a, "END")){
			break;
		}
		for (int i = 0; a[i] != '\0'; ++i)
		{
			if(a[i] < 'a' || a[i] > 'z'){
				b[k] = 0;
				// printf("test %s\n", b);
				trie.find(b);
				printf("%c", a[i]);
				k = 0;
			}else{
				b[k++] = a[i];
			}
		}
		putchar('\n');
	}
	return 0;
}
