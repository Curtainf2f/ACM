/**
problem: http://www.fjutacm.com/Problem.jsp?pid=2492
Splay blog: https://tiger0132.blog.luogu.org/slay-notes
��������:
�ڲ�������
    rootΪָ�룬 xΪ��ֵ
    bool check(int root)�����ص�ǰ���Ϊ���ڵ�����㻹���ҽ�㣨0Ϊ���㣬1Ϊ�ҽ�㣩
    void pushUp(int root)����ת��ά�������Ϣ
    void rotate(int root)���ؼ���������ת���
    void splay(int root, int target = 0)��Splay���ģ���root�����ת��target�ӽ�㣬targetΪ0����ת������
    void find(int x): ����ֵΪx�Ľ����ת������
    int pre(int x)��Ѱ����ֵΪx�Ľ���ǰ����㣬����ָ��
    int succ(int x)��Ѱ����ֵΪx�Ľ��ĺ�̽ڵ㣬����ָ��
�ⲿ������
    void clear()�����ƽ����
    void insert(T x)��������ֵΪx����
    int rank(T x)��������ֵΪx����Ϊ�ڼ�С
    T preAns(T x)�����ظպñ���ֵxС�����Ƕ���
    T succAns(T x)�����ظպñ���ֵx������Ƕ���
    T kth(int k)�����ص�kС�����Ƕ���
    void remove(T x)��ɾ����ֵΪx�Ľ�㣬����ж��������-1
    T top(T x)���������ֵΪx�Ľ�㷵��x�����򷵻�������
    int getAllSize()������ƽ�������ж��ٸ���
**/

#include<stdio.h>
#include<algorithm>
#include<queue>
using namespace std;

typedef long long ll;
const ll MOD = 1000000;

template<typename T>
class Splay{
    const static int MAXN = 10003;
    const static T INF = 0x3f3f3f3f3f3f3f3fLL;
private:
    struct Node{
        int ch[2];
        int cnt, size, parent;
        T val;
    }node[MAXN];
    int treeroot, sign, allSize;
    queue<int> freeMemory;
    bool check(int root){ /// right return 1 else return 0
        return node[node[root].parent].ch[1] == root;
    }
    void pushUp(int root){
        node[root].size = node[node[root].ch[0]].size + node[node[root].ch[1]].size + node[root].cnt;
    }
    void rotate(int root){
        int father = node[root].parent, grandpa = node[father].parent, direction = check(root), child = node[root].ch[direction^1];
        node[father].ch[direction] = child; node[child].parent = father;
        node[grandpa].ch[check(father)] = root; node[root].parent = grandpa;
        node[root].ch[direction^1] = father; node[father].parent = root;
        pushUp(father); pushUp(root);
    }
    void splay(int root, int target = 0){ /// if target == 0 then root to treeroot
        while(node[root].parent != target){
            int father = node[root].parent, grandpa = node[father].parent;
            if(grandpa != target){
                if(check(root) == check(father)) rotate(father);
                else rotate(root);
            }
            rotate(root);
        }
        if(!target) treeroot = root;
    }
    void find(int x){
        if(!treeroot) return;
        int cur = treeroot;
        while(node[cur].ch[x > node[cur].val] && node[cur].val != x){
            cur = node[cur].ch[x > node[cur].val];
        }
        splay(cur);
    }
    int pre(int x){
        find(x);
        if(node[treeroot].val < x) return treeroot;
        if(!node[treeroot].ch[0]) return -1;
        int cur = node[treeroot].ch[0];
        while(node[cur].ch[1]){
            cur = node[cur].ch[1];
        }
        return cur;
    }
    int succ(int x){
        find(x);
        if(node[treeroot].val > x) return treeroot;
        if(!node[treeroot].ch[1]) return -1;
        int cur = node[treeroot].ch[1];
        while(node[cur].ch[0]){
            cur = node[cur].ch[0];
        }
        return cur;
    }
public:
    void clear(){
        sign = 0;
        insert(INF);
        insert(-INF);
        allSize = 0;
    }
    void insert(T x){
        allSize ++;
        int cur = treeroot, preroot = 0;
        while(cur && node[cur].val != x){
            preroot = cur;
            cur = node[cur].ch[x > node[cur].val];
        }
        if(cur){
            node[cur].cnt ++;
        }else{
            if(freeMemory.empty())
                cur = ++ sign;
            else{
                cur = freeMemory.front();
                freeMemory.pop();
            }
            if(preroot) node[preroot].ch[x > node[preroot].val] = cur;
            node[cur].val = x;
            node[cur].cnt = 1;
            node[cur].ch[0] = node[cur].ch[1] = 0;
            node[cur].size = 1;
            node[cur].parent = preroot;
        }
        splay(cur);
    }
    int rank(T x){
        find(x);
        return node[node[treeroot].ch[0]].size;
    }
    T preAns(T x){
        return node[pre(x)].val;
    }
    T succAns(T x){
        return node[succ(x)].val;
    }
    T kth(int k){
        k ++;
        int cur = treeroot;
        while(1){
            if(node[cur].ch[0] && k <= node[node[cur].ch[0]].size){
                cur = node[cur].ch[0];
            }else if(k > node[node[cur].ch[0]].size + node[cur].cnt){
                k -= node[node[cur].ch[0]].size + node[cur].cnt;
                cur = node[cur].ch[1];
            }else{
                return node[cur].val;
            }
        }
    }
    void remove(T x){
        allSize --;
        int last = pre(x), next = succ(x);
        splay(last), splay(next, last);
        int del = node[next].ch[0];
        if(node[del].cnt > 1){
            node[del].cnt --;
            splay(del);
        }else{
            freeMemory.push(node[next].ch[0]);
            node[next].ch[0] = 0;
        }
    }
    T top(T x){
        find(x);
        return node[treeroot].val;
    }
    int getAllSize(){
        return allSize;
    }
};

Splay<ll> splay;

int main(){
    int n;
    ll ans = 0;
    bool type = 1;
    scanf("%d", &n);
    splay.clear();
    while(n --){
        int a;
        ll b;
        scanf("%d%lld", &a, &b);
        if(a){
            if(type || splay.getAllSize() == 0){
                splay.insert(b);
                type = 1;
            }
            else{
                ll pre = splay.preAns(b), mid = splay.top(b), succ = splay.succAns(b);
                ll choose;
                if(abs(pre - b) <= abs(mid - b)){
                    choose = pre;
                }else{
                    choose = mid;
                }
                if(abs(choose - b) > abs(succ - b)){
                    choose = succ;
                }
                ans = (ans + abs(choose - b)) % MOD;
                splay.remove(choose);
            }
        }else{
            if(!type || splay.getAllSize() == 0){
                splay.insert(b);
                type = 0;
            }
            else{
                ll pre = splay.preAns(b), mid = splay.top(b), succ = splay.succAns(b);
                ll choose;
                if(abs(pre - b) <= abs(mid - b)){
                    choose = pre;
                }else{
                    choose = mid;
                }
                if(abs(choose - b) > abs(succ - b)){
                    choose = succ;
                }
                ans = (ans + abs(choose - b)) % MOD;
                splay.remove(choose);
            }
        }
    }
    printf("%lld\n", ans);
    return 0;
}
