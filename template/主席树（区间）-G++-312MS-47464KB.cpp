#include <stdio.h>
#include <algorithm>
using namespace std;

typedef long long ll;

class segmentforest
{
    const static int MAXN = 100005;
private:
    struct node
    {
        int Left, Right;
        ll Sum, Lazy;
    }Node[MAXN * 20];
    int Tree[MAXN], Sign, SumofPoint, NowTime;
    inline void PushUp(int Root){
        Node[Root].Sum = Node[Node[Root].Left].Sum + Node[Node[Root].Right].Sum;
    }
    int Update(int NowLeft, int NowRight, int Root, int DirLeft, int DirRight, ll Value){
        int Get = Sign ++;
        Node[Get] = Node[Root];
        Node[Get].Sum += (DirRight - DirLeft + 1) * Value;
        if(NowLeft == DirLeft && NowRight == DirRight){
            Node[Get].Lazy += Value;
            return Get;
        }
        int Mid = (NowLeft + NowRight) >> 1;
        if(DirRight <= Mid){
            Node[Get].Left = Update(NowLeft, Mid, Node[Root].Left, DirLeft, DirRight, Value);
        }else if(DirLeft > Mid){
            Node[Get].Right = Update(Mid + 1, NowRight, Node[Root].Right, DirLeft, DirRight, Value);
        }else{
            Node[Get].Left = Update(NowLeft, Mid, Node[Root].Left, DirLeft, Mid, Value);
            Node[Get].Right = Update(Mid + 1, NowRight, Node[Root].Right, Mid + 1, DirRight, Value);
        }
        return Get;
    }
public:
    void Init(int SumofPoint){
        Sign = 0;
        this->SumofPoint = SumofPoint;
        Tree[0] = Build(0, SumofPoint-1);
        NowTime = 0;
    }
    int Build(int Left, int Right){
        int Get = Sign ++;
        Node[Get].Lazy = 0;
        if(Left == Right){
            scanf("%lld", &Node[Get].Sum);
            return Get;
        }
        int Mid = (Left + Right) >> 1;
        Node[Get].Left = Build(Left, Mid);
        Node[Get].Right = Build(Mid + 1, Right);
        PushUp(Get);
        return Get;
    }
    int Insert(int NowLeft, int NowRight, int Root, int DirLeft, int DirRight, ll Value){
        Tree[++NowTime] = Update(NowLeft, NowRight, Root, DirLeft, DirRight, Value);
    }
    ll Query(int Left, int Right, int Root, int DirLeft, int DirRight, ll Lazy){
        if(Left >= DirLeft && Right <= DirRight){
            return Node[Root].Sum + Lazy * (Right - Left + 1);
        }
        int Mid = (Left + Right) >> 1;
        if(DirRight <= Mid){
            return Query(Left, Mid, Node[Root].Left, DirLeft, DirRight, Lazy + Node[Root].Lazy);
        }else if(DirLeft > Mid){
            return Query(Mid + 1, Right, Node[Root].Right, DirLeft, DirRight, Lazy + Node[Root].Lazy);
        }else{
            return Query(Left, Mid, Node[Root].Left, DirLeft, Mid, Lazy + Node[Root].Lazy) + Query(Mid + 1, Right, Node[Root].Right, Mid + 1, DirRight, Lazy + Node[Root].Lazy);
        }
    }
    int GetTreeRoot(int DirTree){
        return Tree[DirTree];
    }
    int GetTime(){
        return NowTime;
    }
    inline void TimeSet(int Time){
        if(Time == NowTime) return ;
        NowTime = Time;
        Sign = Tree[NowTime+1];
    }
}SegForest;

int main(int argc, char const *argv[])
{
    int n, m, l, r, t, x, Case = 1;
    ll k;
    char opt;
    while(~scanf("%d", &n)){
        printf("Case %d:\n", Case ++);
        SegForest.Init(n);
        scanf("%d", &m);
        while(m --){
            scanf(" %c", &opt);
            if(opt == 'A'){
                scanf("%d%d%lld", &l, &r, &k);
                SegForest.Insert(0, n-1, SegForest.GetTreeRoot(SegForest.GetTime()), l-1, r-1, k);
            }else if(opt == 'B'){
                scanf("%d%d%d", &t, &l, &r);
                printf("%lld\n", SegForest.Query(0, n-1, SegForest.GetTreeRoot(t), l-1, r-1, 0));
            }else if(opt == 'C'){
                scanf("%d", &x);
                SegForest.TimeSet(x);
            }
        }
    }
    return 0;
}
