#include <cstdio>
#include <algorithm>
#include <cmath>
using namespace std;

const int MAXN = 105;
const int MAXM = 105*105;


struct Point
{
    int x, y;
}point[MAXN];

double GetDistance(const Point &a, const Point &b){
    return sqrt((a.x - b.x) * (a.x - b.x) *1.0 + (a.y - b.y) * (a.y - b.y) * 1.0);
}

class UnionSet
{
private:
    int root[MAXN], sum[MAXN];
    int sumOfPoint, sumOfUnion;
public:
    void clear(int n){
        sumOfPoint = n;
        for(int i = 1; i <= n; i ++){
            root[i] = i;
            sum[i] = 1;
        }
        sumOfUnion = sumOfPoint;
    }
    int find(int x){
        int boss = x;
        while(root[boss] != boss){
            boss = root[boss];
        }
        int tmp;
        while(x != boss){
            tmp = root[x];
            root[x] = boss;
            x = tmp;
        }
        return boss;
    }
    void join(int x, int y){
        int bossX = find(x), bossY = find(y);
        if(bossX != bossY){
            if(sum[bossY] < sum[bossX]) swap(bossX, bossY);
            root[bossY] = bossX;
            sum[bossX] += sum[bossY];
            sumOfUnion --;
        }
    }
    int getSumOfUnion(){
        return sumOfUnion;
    }
}uf;

class Graphics{
private:
    int sumOfPoint, sumOfEdge;
    struct Edge
    {
        int u, v;
        double cost;
        bool friend operator < (const Edge &a, const Edge &b){
            return a.cost < b.cost;
        }
    }edge[MAXM];
public:
    void clear(int n){
        sumOfPoint = n;
    }
    void inputEdge(){
        sumOfEdge = 0;
        for(int i = 1; i <= sumOfPoint; i ++){
            for(int j = i + 1; j <= sumOfPoint; j ++){
                double Distance_t = GetDistance(point[i], point[j]);
                if(Distance_t >= 10 && Distance_t <= 1000){
                    edge[sumOfEdge].u = i;
                    edge[sumOfEdge].v = j;
                    edge[sumOfEdge++].cost = Distance_t;
                }
            }
        }
    }
    double kruskal(){
        double cost = 0;
        uf.clear(sumOfPoint);
        sort(edge, edge + sumOfEdge);
        for(int i = 0; i < sumOfEdge; i ++){
            if(uf.getSumOfUnion() == 1) break;
            int bossX = uf.find(edge[i].u), bossY = uf.find(edge[i].v);
            if(bossX != bossY){
                cost += edge[i].cost;
                uf.join(edge[i].u, edge[i].v);
            }
        }
        if(uf.getSumOfUnion() == 1)
            return cost;
        else
            return -1;
    }
}graph;

int main(int argc, char const *argv[])
{
    int t;
    scanf("%d", &t);
    while(t--){
        int n;
        scanf("%d", &n);
        graph.clear(n);
        for(int i = 1; i <= n; i ++){
            scanf("%d%d", &point[i].x, &point[i].y);
        }
        graph.inputEdge();
        double Ans = graph.kruskal() * 100;
        if(Ans < 0){
            puts("oh!");
        }else{
            printf("%.1f\n", Ans);
        }
    }
    return 0;
}
