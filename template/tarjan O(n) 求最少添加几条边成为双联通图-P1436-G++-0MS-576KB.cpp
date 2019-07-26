/**
problem: http://poj.org/problem?id=3177
tarjan blog: https://blog.csdn.net/reverie_mjp/article/details/51704523

v Ϊ��һ��㣬 uΪ��ǰ���
���low[v] > dfn[u] �� (u,v) Ϊ��
�����ʣ�µ����б߶�Ϊ�ţ������Ϊ���ṹ��
��Ҷ�ӽ������ʹ���Ϊ˫��ͨ����Ϊ���Ž�
���ԣ�
���(leaf + 1) / 2 ���߼���ʹͼ��Ϊ˫��ͨͼ
**/
#include<stdio.h>
#include<stack>
#include<algorithm>
using namespace std;

class Graphics{
    const static int MAXN = 5005;
    const static int MAXM = 10005 * 2;
private:
    struct Edge{
        int to, next;
        bool bridge;
    }edge[MAXM];
    struct Point{
        int dfn, low, color;
    }point[MAXN];
    int first[MAXN], sign, sumOfPoint, dfnNum, colorNum;
    bool vis[MAXN];
    stack<int> stk;
    void tarjan(int u, int pre = 0){
        point[u].low = dfnNum;
        point[u].dfn = dfnNum ++;
        vis[u] = true;
        stk.push(u);
        for(int i = first[u]; i != -1; i = edge[i].next){
            int to = edge[i].to;
            if(to == pre) continue; /// ������˫��ߣ���ֹ�ݹ��ԭ���ĵ�
            if(!point[to].dfn){
                tarjan(to, u);
                point[u].low = min(point[u].low, point[to].low);
                if(point[to].low > point[u].dfn){
                    edge[i].bridge = true;
                    edge[i^1].bridge = true;
                }
            }else if(vis[to]){
                point[u].low = min(point[to].dfn, point[u].low);
            }
        }
        if(point[u].dfn == point[u].low){
            vis[u] = false;
            point[u].color = ++ colorNum;
            while(stk.top() != u){
                point[stk.top()].color = colorNum;
                vis[stk.top()] = false;
                stk.pop();
            }
            stk.pop();
        }
    }
public:
    void init(int n){
        sumOfPoint = n;
        for(int i = 1; i <= n; i ++){
            first[i] = -1;
            vis[i] = 0;
        }
        sign = colorNum = 0;
        dfnNum = 1;
    }
    void addEdgeOneWay(int u, int v){
        edge[sign].to = v;
        edge[sign].next = first[u];
        edge[sign].bridge = false;
        first[u] = sign ++;
    }
    void addEdgeTwoWay(int u, int v){
        addEdgeOneWay(u, v);
        addEdgeOneWay(v, u);
    }
    void tarjanAllPoint(){
        for(int i = 1; i <= sumOfPoint; i ++){
            if(!point[i].dfn)
                tarjan(i);
        }
    }
    int getAns(){
        int *degree = new int[sumOfPoint+1];
        int ans = 0;
        for(int i = 1; i <= sumOfPoint; i ++){
            degree[i] = 0;
        }
        tarjanAllPoint();
        for(int i = 1; i <= sumOfPoint; i ++){
            for(int j = first[i]; j != -1; j = edge[j].next){
                int to = edge[j].to;
                if(edge[j].bridge){
                    degree[point[to].color] ++;
                }
            }
        }
        for(int i = 1; i <= sumOfPoint; i ++){
            if(degree[i] == 1){
                ans ++;
            }
        }
        delete []degree; return (ans + 1) / 2;
    }
}graph;

int main(){
    int f, r;
    scanf("%d%d", &f, &r);
    graph.init(f);
    while(r --){
        int a, b;
        scanf("%d%d", &a, &b);
        graph.addEdgeTwoWay(a, b);
    }
    printf("%d\n", graph.getAns());
    return 0;
}
