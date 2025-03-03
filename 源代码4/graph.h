#include<bits/stdc++.h>
using namespace std;

int point1[35],point2[35];//储存放大器的位置
struct Edge{//边的定义
    int parent=0,degreeFromParent=0;//父节点 衰减
    Edge(int p,int d){
        parent=p;
        degreeFromParent=d;
    }
};

class graph{
public:
    int n,m,d;//点数 边数 最大压力
    vector<Edge>* edge;//邻接边集
    bool* vis;//判断是否访问
    int* degreeToLeaf;//到叶节点的衰减
    int* indegree;//入度
    int ans1,ans2;//两种方案结果
    graph(string str);//数据读取
    int res1();
    int res2();
};

graph::graph(string str) {//打开文件读取数据
    ifstream file(str,ios::in);
    file>>n>>m>>d;//读取点数 边数 最大压力
    vis=new bool [n+2];
    degreeToLeaf=new int[n+2];
    indegree=new int [n+2];
    for(int i=0;i<n+2;i++){//初始化
        vis[i]=false;
        degreeToLeaf[i]=0;
        indegree[i]=0;
    }
    edge=new vector<Edge>[n+2];
    int a,b,c;
    while(m--){
        file>>a>>b>>c;
        edge[b].emplace_back(a,c);//反向建图
        indegree[a]++;
    }
    file.close();
}

int::graph::res1(){//返回遍历的结果
    ans1 = 1e9;
    for (int i = 0; i < 35; i++) point1[i] = 0;
    int* enumerate = new int[n + 1];//枚举
    for (int i = 1; i <= n; i++)enumerate[i] = 0;//为1则有放大器
    for (int i = 0; i < pow(2, n); i++) {//2^n种可能结果
        int cnt = 0, x = i, now_ans = 0;//cnt用于计数，now_ans记录有几个放大器
        while (cnt < n) {//将数据转化为放置情况
            if (x & 1) now_ans++;
            enumerate[++cnt] = x & 1;
            x /= 2;
        }
        if (now_ans > ans1)//剪枝
            continue;
        int* ind = new int[n + 1];
        queue<int>que;

        for (int j = 1; j <= n; j++) {//初始化数据并在队列中插入叶节点
            ind[j] = indegree[j];
            degreeToLeaf[j] = 0;
            vis[j] = 0;
            if (ind[j] == 0) {
                que.push(j);
                vis[j] = 1;
            }
        }

        while (!que.empty()) {
            int temp = que.front();
            que.pop();
            if (enumerate[temp] == 1)
                degreeToLeaf[temp] = 0;//如果为1，说明当前有放大器，将其到叶子的衰减量置为0
            for (auto& j : edge[temp]) {
                degreeToLeaf[j.parent] = max(degreeToLeaf[j.parent], degreeToLeaf[temp] + j.degreeFromParent);//更新父节点的衰减
                if (degreeToLeaf[j.parent] > d) {//该结果不可行
                    now_ans = 1e9;
                    break;
                }
                ind[j.parent]--;
                if (!vis[j.parent] && !ind[j.parent]) {//没有访问过且入度为0
                    que.push(j.parent);
                    vis[j.parent] = 1;
                }
            }
            if (now_ans == 1e9)
                break;
        }
        if (ans1 > now_ans) {
            ans1 = min(ans1, now_ans);
            for (int i = 1; i <= n; i++) point1[i] = enumerate[i];//point1[i]储存放大器位置
        }
    }

    delete[]enumerate;
    return ans1;


}

int::graph::res2(){
    ans2=0;
    int* ind = new int[n + 1];
    queue<int>que;
    for (int i = 0; i < 35; i++) point2[i] = 0;
    for(int i=1;i<=n;i++){//初始化
        vis[i]=0;
        degreeToLeaf[i]=0;
        ind[i]=indegree[i];
        if (indegree[i] == 0) {//叶节点
            que.push(i);
            vis[i] = 1;
        }
    }


    while (!que.empty()) {//从叶节点开始遍历每一个节点
        int temp = que.front();
        que.pop();

        for (auto& i : edge[temp]) {
            if (degreeToLeaf[temp] + i.degreeFromParent > d) {//在当前点放置放大器
                ans2++;
                degreeToLeaf[temp] = 0;
                point2[temp] = 1;
                break;
            }
        }

        for (auto& i : edge[temp]) {
            degreeToLeaf[i.parent] = max(degreeToLeaf[i.parent], i.degreeFromParent + degreeToLeaf[temp]);//更新父节点的衰减
            ind[i.parent]--;
            if (ind[i.parent] == 0 && vis[i.parent] == 0) que.push(i.parent);//如果入度为0且未访问则放入队列
        }
    }

    delete[]ind;
    return ans2;
}

