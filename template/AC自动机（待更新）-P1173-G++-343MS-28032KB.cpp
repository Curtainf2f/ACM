#include <cstdio>
#include <queue>
using namespace std;

const int maxn = 10000005;

struct node
{
    int next[26];
    int Word;
    int fail;
    void init(){
        for (int i = 0; i < 26; ++i){
            next[i] = -1;
        }
        Word = 0;
    } 
}Node[maxn];

class TrieTree
{
private:
    int root;
    int sign;
public:
    void init(){
        sign = 0;
        root = sign ++;
        Node[root].init();
    }
    void insert(char *str){
        int now = root;
        for (int i = 0; str[i] != '\0'; ++i){
            int cur = str[i] - 'a';
            if(Node[now].next[cur] == -1){
                Node[sign].init();
                Node[now].next[cur] = sign ++;
            }
            now = Node[now].next[cur];
        }
        Node[now].Word ++;
    }
    void build_fail(){
        queue<int> bfs;
        bfs.push(root);
        Node[root].fail = -1;
        while(!bfs.empty()){
        	int now = bfs.front();
        	bfs.pop();
        	for (int i = 0; i < 26; ++i){
        		if(Node[now].next[i] != -1){
        			if(now == root){
        				Node[Node[now].next[i]].fail = root;
        			}
        			else{
        				int temp = Node[now].fail;
        				while(temp != -1){
        					if(Node[temp].next[i] != -1){
        						 Node[Node[now].next[i]].fail = Node[temp].next[i];
        						 break;
        					}
        					temp = Node[temp].fail;
        				}
        				if(temp == -1) Node[Node[now].next[i]].fail = root;
        			}
        			bfs.push(Node[now].next[i]);
        		}
        	}
        }
    }
    int kmp_search(char *text){
        int ans = 0;
        int now = root;
        for (int i = 0; text[i] != '\0'; ++i){
            int cur = text[i] - 'a';
            while(Node[now].next[cur] == -1 && now != root) now = Node[now].fail;
            if(Node[now].next[cur] != -1)
                now = Node[now].next[cur];
            int temp = now;
            while(temp != root){
                if(Node[temp].Word >= 0){
                    ans += Node[temp].Word;
                    Node[temp].Word = -1;
                }else break;
                temp = Node[temp].fail;
            }
        }
        return ans;
    }
    void test(){
        queue<int> bfs;
        bfs.push(root);
        while(!bfs.empty()){
            int now = bfs.front();
        	printf("now = %d fail = %d\n", now, Node[now].fail);
            bfs.pop();
            for (int i = 0; i < 26; ++i){
                if(Node[now].next[i] != -1){
                    bfs.push(Node[now].next[i]);
                }
            }
        }
    }
}trie;

char s[1000005], p[55];
int main(int argc, char const *argv[])
{
    int t;
    scanf("%d", &t);
    while(t--){
        trie.init();
        int n;
        scanf("%d", &n);
        for (int i = 0; i < n; ++i){
            scanf("%s", p);
            trie.insert(p);
        }
        trie.build_fail();
        // trie.test();
        scanf("%s", s);
        printf("%d\n", trie.kmp_search(s));
    }
    return 0;
}