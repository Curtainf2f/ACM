#include <cstdio>
#include <queue>
#include <algorithm>
using namespace std;

const int MAXPOINT = 10005;
const int MAXEDGE = 20005;

class unionset
{
private:
    int Root_m[MAXPOINT], MemberofUnion_m[MAXPOINT];
    int SumofPoint_m, SumofUnion_m;
public:
    void Init(int SumofPoint){
        SumofPoint_m = SumofPoint;
        for(int i = 0; i < SumofPoint_m; i ++){
            Root_m[i] = i;
            MemberofUnion_m[i] = 1;
        }
        SumofUnion_m = SumofPoint_m;
    }
    int Find(int ElementX){
        int Boss = ElementX;
        while(Root_m[Boss] != Boss){ // Find Boss
            Boss = Root_m[Boss];
        }
        int Temp;
        while(ElementX != Boss){ // Compress
            Temp = Root_m[ElementX];
            Root_m[ElementX] = Boss;
            ElementX = Temp;
        }
        return Boss;
    }
    void Union(int ElementX, int ElementY){
        int BossX = Find(ElementX), BossY = Find(ElementY);
        if(BossX != BossY){
            Root_m[BossY] = BossX;
            MemberofUnion_m[BossX] += MemberofUnion_m[BossY];
            SumofUnion_m --;
        }
    }
    int GetSumofUnion(){
        return SumofUnion_m;
    }
}Union_g;

class graphics
{
private:
    struct edge
    {
        int To, Next;
    }Edge_m[MAXEDGE];
    int Sign_m, First_m[MAXPOINT], SumofPoint_m, Degree_m[MAXPOINT];
public:
    inline void Init(int SumofPoint){
        SumofPoint_m = SumofPoint;
        for (int i = 0; i <= SumofPoint_m; ++i){
            First_m[i] = -1;
            Degree_m[i] = 0;
        }
        Sign_m = 0;
    }
    inline void AddEdgeOne_Way(int Start, int End){
        Degree_m[End] ++;
        Edge_m[Sign_m].To = End;
        Edge_m[Sign_m].Next = First_m[Start];
        First_m[Start] = Sign_m ++;
    }
    int TopoSort(){ /// 0 OK 1 UNCERTAIN 2 CONFLICT
        queue<int> MaxNum;
        for(int i = 0; i < SumofPoint_m; i ++){
            if(!Degree_m[i] && Union_g.Find(i) == i){
                MaxNum.push(i);
            }
        }
        bool Uncertain = 0;
        int NumofCertain = Union_g.GetSumofUnion();
        while(!MaxNum.empty()){
            if(MaxNum.size() >= 2) Uncertain = 1;
            int Now = MaxNum.front();
            MaxNum.pop();
            NumofCertain --;
            for(int i = First_m[Now]; i != -1; i = Edge_m[i].Next){
                int To = Edge_m[i].To;
                Degree_m[To] --;
                if(Degree_m[To] == 0){
                    MaxNum.push(To);
                }
            }
        }
        if(NumofCertain) Uncertain = 1;
        for(int i = 0; i < SumofPoint_m; i ++){
            if(Degree_m[i]){
                return 2;
            }
        }
        if(Uncertain) return 1;
        return 0;
    }
}Graph_g;

struct opration
{
    int a, b;
    char opt;
}Opration_g[MAXEDGE];
int Top_g;

int main(int argc, char const *argv[])
{
    int n, m;
    while(~scanf("%d%d", &n, &m)){
        Union_g.Init(n);
        Graph_g.Init(n);
        Top_g = 0;
        while(m --){
            int a, b;
            char opt;
            scanf("%d %c%d", &a, &opt, &b);
            if(opt == '='){
                Union_g.Union(a, b);
            }else{
                Opration_g[Top_g].a = a;
                Opration_g[Top_g].b = b;
                Opration_g[Top_g++].opt = opt;
            }
        }
        for(int i = 0; i < Top_g; i ++){
            if(Opration_g[i].opt == '<'){
                Graph_g.AddEdgeOne_Way(Union_g.Find(Opration_g[i].b), Union_g.Find(Opration_g[i].a));
            }else{
                Graph_g.AddEdgeOne_Way(Union_g.Find(Opration_g[i].a), Union_g.Find(Opration_g[i].b));
            }
        }
        int Ans = Graph_g.TopoSort();
        if(Ans == 0){
            puts("OK");
        }else if(Ans == 1){
            puts("UNCERTAIN");
        }else{
            puts("CONFLICT");
        }
    }
    return 0;
}