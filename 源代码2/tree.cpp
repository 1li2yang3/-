#include<iostream>
using namespace std;
const int MAX_INT = 2147483647;
struct Node{//用于归并的节点类
    int id=0,number;
    bool operator<(const Node& a)const{//重载小于
        if(id!=a.id)
            return id<a.id;
        else
            return number<a.number;
    }
};

template<class T>
class losetree
{
public:
    losetree(T* a,int num){//输者树的构造
        number=num;
        player=new T[2 * num]();//这里两倍便于选出每次的输者，后一办是叶节点，前一半是内部节点
        winer=new int[num * 2]();//记录每次赢者的下标
        loser=new T[num]();
        for (int i=number; i<2*number; i++)//叶节点赋初值
        {
            player[i]=a[i-number];
            winer[i]=i;
        }
        for (int i=number-1;i>0;i--)//根据后一半叶节点给内部节点赋初值
        {
            if(player[2*i]<player[2*i+1])
            {
                player[i]=player[2*i];//记录赢者的值
                loser[i]=player[2*i+1];//记录输者的值
                winer[i]=winer[2*i];//记录赢者的下标
            }
            else
            {
                player[i]=player[2*i+1];
                loser[i]=player[2*i];
                winer[i]=winer[2*i+1];
            }
        }
        loser[0] = player[winer[1]];//记录最小值
    }
    T winner(){
        return loser[0];//loser[0]中存储的是最小值
    }
    int player2(){
        return winer[1]-number;//最小值的下标
    }
    void reinit(T element){//输者树重构
        player[winer[1]] = element;//将最小值换成新值
        for (int i = winer[1] / 2; i > 0; i = i / 2)//从最小值的父亲开始往上重新比赛
        {
            if (player[2 * i] < player[2 * i + 1])
            {
                player[i] = player[2 * i];
                loser[i] = player[2 * i + 1];
                winer[i] = winer[2 * i];
            }
            else
            {
                player[i] = player[2 * i + 1];
                loser[i] = player[2 * i];
                winer[i] = winer[2 * i + 1];
            }
        }
        loser[0] = player[winer[1]];         //记录最小值
    }
private:
    int number;
    T* loser;      //输者树节点数组
    int* winer;    //记录每次的赢者下标
    T* player;     //赢者树节点数组，记录每次赢者的值
};


