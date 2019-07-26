#include <cstdio>
#include <algorithm>
using namespace std;

const int MAXN = 100005;

class segmentforest
{
private:
    int Data_m[MAXN];
    int Value_m[MAXN], NewEnd;
    struct node
    {
        int Left, Right, Sum;
    }Node_m[MAXN * 20];
    int Tree[MAXN], Sign_m, SumofPoint_m;
    inline int Getid(int x){
        return lower_bound(Value_m, Value_m + NewEnd, x) - Value_m; 
    }
    void InputDatas(){
        int SumofData = SumofPoint_m;
        int Temp[SumofData];
        for(int i = 0;i < SumofData; i ++){
            scanf("%d", &Data_m[i]);
            Temp[i] = Data_m[i];
        }
        sort(Temp, Temp + SumofData); // Discretization
        NewEnd = unique(Temp, Temp + SumofData) - Temp;
        for(int i = 0; i < NewEnd; i ++){
            Value_m[i] = Temp[i];
        }
    }
public:
    void Init(int SumofPoint){
        Sign_m = 0;
        SumofPoint_m = SumofPoint;
        InputDatas();
        Tree[0] = Build(0, NewEnd - 1);
        for(int i = 1; i <= SumofPoint; i ++){
            Tree[i] = Insert(0, NewEnd - 1, Tree[i-1], Getid(Data_m[i-1]), 1);
        }
    }
    int Build(int Left, int Right){
        int Get = Sign_m ++;
        Node_m[Get].Sum = 0;
        if(Left == Right) return Get;
        int Mid = (Left + Right) >> 1;
        Node_m[Get].Left = Build(Left, Mid);
        Node_m[Get].Right = Build(Mid + 1, Right);
        return Get;
    }
    int Insert(int Left, int Right, int Root, int Pos, int Value){
        int Get = Sign_m ++;
        Node_m[Get] = Node_m[Root];
        if(Left == Right){
            Node_m[Get].Sum += Value;
            return Get;
        }
        int Mid = (Left + Right) >> 1;
        if(Pos <= Mid){
            Node_m[Get].Left = Insert(Left, Mid, Node_m[Root].Left, Pos, Value);
        }else{
            Node_m[Get].Right = Insert(Mid + 1, Right, Node_m[Root].Right, Pos, Value);
        }
        Node_m[Get].Sum = Node_m[Node_m[Get].Left].Sum + Node_m[Node_m[Get].Right].Sum;
        return Get;
    }
    int Query(int TreeLeft, int TreeRight, int Left, int Right, int Kth){
        if(Left == Right){
            return Value_m[Left];
        }
        int Mid = (Left + Right) >> 1;
        int Cnt = Node_m[Node_m[TreeRight].Left].Sum - Node_m[Node_m[TreeLeft].Left].Sum;
        if(Kth <= Cnt){
            return Query(Node_m[TreeLeft].Left, Node_m[TreeRight].Left, Left, Mid, Kth);
        }else{
            return Query(Node_m[TreeLeft].Right, Node_m[TreeRight].Right, Mid + 1, Right, Kth - Cnt);
        }
    }
    inline int GetRightBorder(){
        return NewEnd - 1;
    }
    inline int GetTree(int x){
        return Tree[x];
    }
}SegForest;

int main(int argc, char const *argv[])
{
    int t;
    scanf("%d", &t);
    while(t --){
        int n, q;
        scanf("%d%d", &n, &q);
        SegForest.Init(n);
        while(q --){
            int s, t, k;
            scanf("%d%d%d", &s, &t, &k);
            printf("%d\n", SegForest.Query(SegForest.GetTree(s-1), SegForest.GetTree(t), 0, SegForest.GetRightBorder(), k));
        }
    }
    return 0;
}