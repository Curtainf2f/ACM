#include <cstdio>
#include <algorithm>
#include <queue>
using namespace std;

const int MAXPOINT = 2005;
const int MAXEDGE = 2000005;

class graphics{
private:
    struct edge
    {
        int To, Next;
    }Edge_m[MAXEDGE];
    int First_m[MAXPOINT], Sign_m, SumofPoint_m, Link[MAXPOINT];
    bool Visit_m[MAXPOINT];
    bool Found(int x){
        for(int i = First_m[x]; i != -1; i = Edge_m[i].Next){
            int To = Edge_m[i].To;
            if(!Visit_m[To]){
                Visit_m[To] = 1;
                if(!Link[To] || Found(Link[To])){
                    Link[To] = x;
                    return 1;
                }
            }
        }
        return 0;
    }
public:
    void Init(int SumofPoint){
        SumofPoint_m = SumofPoint;
        for(int i = 0; i <= SumofPoint; i ++){
            First_m[i] = -1;
            // Link[i] = 0;
        }
        Sign_m = 0;
    }
    inline void AddEdgeOne_Way(int Start, int End){
        Edge_m[Sign_m].To = End;
        Edge_m[Sign_m].Next = First_m[Start];
        First_m[Start] = Sign_m ++;
    }
    inline void AddEdgeTwo_Way(int Start, int End){
        AddEdgeOne_Way(Start, End);
        AddEdgeOne_Way(End, Start);
    }
    int Hungarian(int MatchRange){
        int Ans = 0;
        for (int i = 0; i <= MatchRange; ++i){
            for (int j = 0; j <= SumofPoint_m; ++j){
                Visit_m[j] = 0;
            }
            if(Found(i)){
                Ans ++;
            }
        }
        return Ans;
    }
    bool BiPartiesJudge(){
        int Color[SumofPoint_m + 1];
        for(int i = 0; i <= SumofPoint_m; i ++){
            Color[i] = 0;
        }
        queue<int> Bfs;
        for(int i = 1; i <= SumofPoint_m; i ++){
            if(Color[i])
                continue;
            Bfs.push(i);
            Color[i] = 1;
            while(!Bfs.empty()){
                int Now = Bfs.front();
                Bfs.pop();
                for(int i = First_m[Now]; i != -1; i = Edge_m[i].Next){
                    int To = Edge_m[i].To;
                    if(!Color[To]){
                        Color[To] = 3 - Color[Now];
                        Bfs.push(To);
                    }else if(Color[To] != 3 - Color[Now]){
                        return false;
                    }
                }
            }
        }
        return true;
    }
}Graph;

int main(int argc, char const *argv[])
{
    int t;
    scanf("%d", &t);
    for(int Cas = 1; Cas <= t; Cas ++){
        int n, q, a, b;
        scanf("%d%d", &n, &q);
        Graph.Init(n);
        while(q --){
            scanf("%d%d", &a, &b);
            Graph.AddEdgeTwo_Way(a, b);
        }
        printf("Scenario #%d:\n%s\n\n", Cas, Graph.BiPartiesJudge() ? "No suspicious bugs found!" : "Suspicious bugs found!");
    }
    return 0;
}