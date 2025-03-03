#include<bits/stdc++.h>
using namespace std;

int point1[35],point2[35];//����Ŵ�����λ��
struct Edge{//�ߵĶ���
    int parent=0,degreeFromParent=0;//���ڵ� ˥��
    Edge(int p,int d){
        parent=p;
        degreeFromParent=d;
    }
};

class graph{
public:
    int n,m,d;//���� ���� ���ѹ��
    vector<Edge>* edge;//�ڽӱ߼�
    bool* vis;//�ж��Ƿ����
    int* degreeToLeaf;//��Ҷ�ڵ��˥��
    int* indegree;//���
    int ans1,ans2;//���ַ������
    graph(string str);//���ݶ�ȡ
    int res1();
    int res2();
};

graph::graph(string str) {//���ļ���ȡ����
    ifstream file(str,ios::in);
    file>>n>>m>>d;//��ȡ���� ���� ���ѹ��
    vis=new bool [n+2];
    degreeToLeaf=new int[n+2];
    indegree=new int [n+2];
    for(int i=0;i<n+2;i++){//��ʼ��
        vis[i]=false;
        degreeToLeaf[i]=0;
        indegree[i]=0;
    }
    edge=new vector<Edge>[n+2];
    int a,b,c;
    while(m--){
        file>>a>>b>>c;
        edge[b].emplace_back(a,c);//����ͼ
        indegree[a]++;
    }
    file.close();
}

int::graph::res1(){//���ر����Ľ��
    ans1 = 1e9;
    for (int i = 0; i < 35; i++) point1[i] = 0;
    int* enumerate = new int[n + 1];//ö��
    for (int i = 1; i <= n; i++)enumerate[i] = 0;//Ϊ1���зŴ���
    for (int i = 0; i < pow(2, n); i++) {//2^n�ֿ��ܽ��
        int cnt = 0, x = i, now_ans = 0;//cnt���ڼ�����now_ans��¼�м����Ŵ���
        while (cnt < n) {//������ת��Ϊ�������
            if (x & 1) now_ans++;
            enumerate[++cnt] = x & 1;
            x /= 2;
        }
        if (now_ans > ans1)//��֦
            continue;
        int* ind = new int[n + 1];
        queue<int>que;

        for (int j = 1; j <= n; j++) {//��ʼ�����ݲ��ڶ����в���Ҷ�ڵ�
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
                degreeToLeaf[temp] = 0;//���Ϊ1��˵����ǰ�зŴ��������䵽Ҷ�ӵ�˥������Ϊ0
            for (auto& j : edge[temp]) {
                degreeToLeaf[j.parent] = max(degreeToLeaf[j.parent], degreeToLeaf[temp] + j.degreeFromParent);//���¸��ڵ��˥��
                if (degreeToLeaf[j.parent] > d) {//�ý��������
                    now_ans = 1e9;
                    break;
                }
                ind[j.parent]--;
                if (!vis[j.parent] && !ind[j.parent]) {//û�з��ʹ������Ϊ0
                    que.push(j.parent);
                    vis[j.parent] = 1;
                }
            }
            if (now_ans == 1e9)
                break;
        }
        if (ans1 > now_ans) {
            ans1 = min(ans1, now_ans);
            for (int i = 1; i <= n; i++) point1[i] = enumerate[i];//point1[i]����Ŵ���λ��
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
    for(int i=1;i<=n;i++){//��ʼ��
        vis[i]=0;
        degreeToLeaf[i]=0;
        ind[i]=indegree[i];
        if (indegree[i] == 0) {//Ҷ�ڵ�
            que.push(i);
            vis[i] = 1;
        }
    }


    while (!que.empty()) {//��Ҷ�ڵ㿪ʼ����ÿһ���ڵ�
        int temp = que.front();
        que.pop();

        for (auto& i : edge[temp]) {
            if (degreeToLeaf[temp] + i.degreeFromParent > d) {//�ڵ�ǰ����÷Ŵ���
                ans2++;
                degreeToLeaf[temp] = 0;
                point2[temp] = 1;
                break;
            }
        }

        for (auto& i : edge[temp]) {
            degreeToLeaf[i.parent] = max(degreeToLeaf[i.parent], i.degreeFromParent + degreeToLeaf[temp]);//���¸��ڵ��˥��
            ind[i.parent]--;
            if (ind[i.parent] == 0 && vis[i.parent] == 0) que.push(i.parent);//������Ϊ0��δ������������
        }
    }

    delete[]ind;
    return ans2;
}

