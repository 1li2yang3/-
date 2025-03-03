#include<iostream>
#include<math.h>
#include<cmath>
#include <cstdlib>
#include<Windows.h>
#include <ctime>
using namespace std;

int level_num[11]={0,0,0,0,0,0,0,0,0,0,0};
int all_num=0,action_num=0;


template<class K,class E>
struct skipNode//跳表节点类
{
    typedef pair<const K,E> pairType;
    int level=0;//节点级别
    pairType element;//节点数值
    skipNode<K,E> **next;//指向下一个节点的指针
    skipNode(const pairType& thePair,int size):element(thePair){//节点初始化
        next=new skipNode<K,E>* [size];
    }
};

template <class K,class E>
struct skipList
{
public:
    float cutOff;
    int levels;
    int dSize;
    int maxLevel;//最大层数
    K tailKey;//最大关键字
    skipNode<K,E>* headerNode;
    skipNode<K,E>* tailNode;
    skipNode<K,E>** last;
    skipList(K largeKey,int maxPairs,float prob);
    void initial(int a[],int n,float p);
    pair<const K,E>* find(const K& theKey) const;
    int level() const;
    skipNode<K,E>* search(const K& theKey) const;
    void insert(const pair<const K,E>& thePair);
    void erase(const K& theKey);
    void eraseThemin();
    void eraseThemax();
    void test(){//输出各级节点

        for(int i=0;i<=10;i++)
            level_num[i]=0;
        for(int i=0;i<=maxLevel;i++){
            skipNode<K,E>*pp;
            pp=headerNode->next[i];
            while(pp!=tailNode){
                if(pp->level>=i)
                    level_num[i]++;
                pp=pp->next[i];
            }
        }
        for(int i=0;i<10;i++){//每级节点数目
            cout<<i<<"num: "<<level_num[i]<<endl;
        }

        for(int i=0;i<=maxLevel;i++){//每级节点的元素值
            skipNode<K,E>*pp;
            pp=headerNode->next[i];
            cout<<"level:"<<i<<endl;
            while(pp!=tailNode){
                cout<<pp->element.first<<" "<<pp->level<<endl;
                pp=pp->next[i];
            }
        }
        cout<<endl;
    }

    void reset(float p);//重新整理
    int decide(){
        return all_num;
    }
};

template<class K,class E>
skipList<K,E>::skipList(K largeKey, int maxPairs, float prob) {//跳表定义
    cutOff=prob*RAND_MAX;
    maxLevel=(int) ceil(logf((float)maxPairs)/logf(1/prob))-1;
    levels=0;
    dSize=0;
    tailKey=largeKey;
    pair<K,E>tailPair;
    tailPair.first=tailKey;
    headerNode=new skipNode<K,E> (tailPair,maxLevel+1);
    tailNode=new skipNode<K,E>(tailPair,0);
    last=new skipNode<K,E> *[maxLevel+1];
    for(int i=0;i<=maxLevel;i++)
        headerNode->next[i]=tailNode;
}

template<class K,class E>
void skipList<K, E>::initial(int a[], int n,float p) {//跳表初始化
    //DWORD start_time = GetTickCount();
    skipNode<K,E>** Node;
    all_num=n;
    int b=1/p;
    int c=0;
    int array[n],num=0;
    pair<K,E> nodepair;
    Node=new skipNode<K, E> * [n+2];
    for(int i=0;i<n;i++){//先将节点层数初始化为0 1 0 1类型的
        c++;
        nodepair.first=a[i];
        if(c==b){
            c=0;
            Node[i]=new skipNode<K,E>(nodepair,maxLevel+1);
            Node[i]->level=1;
        }
        else
            Node[i]=new skipNode<K,E>(nodepair,0);
    }

    for(int i=0;i<n;i++){//找出最大层数
        int x=0,y=1;
        for(int j=1;j<=10;j++){
            y=y*b;
            x++;
            if(y==(i+1)){
                Node[i]->level=x;
                if(x>levels)
                    levels=x;
                break;
            }
        }
    }
    int zx=0;
    for(int i=1;i<=levels;i++){//对于每一层节点，每间隔一个点让下一个节点的的层数加1，即可实现严格跳表
        zx=0;
        for(int j=0;j<n;j++){
            if(Node[j]->level>=i)
                zx++;
            if(zx==2){
                Node[j]->level=i+1;
                zx=0;
            }
        }
    }

    maxLevel=levels;
    /*for(int i=n/2+1;i<n;i++){
        Node[i]->level=Node[n/2-(i-n/2)]->level;
    }

    for(int i=0;i<n;i++){
        cout<<Node[i]->element.first<<" "<<Node[i]->level<<endl;
    }*/

    for(int i=0;i<=levels;i++){//各等级节点连接
        num=0;
        for(int j=0;j<n;j++){
            if(Node[j]->level>=i){
                array[num]=j;
                num++;
            }
        }
        if(num==0)//如果该等级一个节点都没有，则进入下一级
            continue;
        else{//节点连接
            headerNode->next[i]=Node[array[0]];
            for(int j=0;j<(num-1);j++){
                Node[array[j]]->next[i]=Node[array[j+1]];
            }
            Node[array[num-1]]->next[i]=tailNode;
        }
    }

}

template<class K,class E>
pair<const K,E>* skipList<K,E>::find(const K& theKey) const
{
    if(theKey>=tailKey){
        cout<<"the data is too large"<<endl;
        return NULL;
    }
    skipNode<K,E>* beforeNode=headerNode;
    for(int i=levels;i>=0;i--)//查找
        while(beforeNode->next[i]->element.first<theKey) {
            action_num++;
            beforeNode = beforeNode->next[i];
        }

    if(beforeNode->next[0]->element.first==theKey){
        cout<<"success "<<beforeNode->next[0]->element.first<<endl;
        return &beforeNode->next[0]->element;
    }
    cout<<"failure"<<endl;
    return NULL;
}

template<class K,class E>
int skipList<K,E>::level() const//返回随机层数
{
    int lev=0;
    while (rand()<=cutOff)
        lev++;
    return (lev<=maxLevel) ? lev : maxLevel;
}

template<class K,class E>
skipNode<K,E>* skipList<K,E>::search(const K& theKey) const{//查找并跟新last
    skipNode<K,E>* beforeNode=headerNode;
    for(int i=levels;i>=0;i--){
        while(beforeNode->next[i]->element.first<theKey) {
            beforeNode = beforeNode->next[i];
            action_num++;
        }
        last[i]=beforeNode;//last为每一层左边最靠近被查节点的节点
    }
    return beforeNode->next[0];
}

template<class K,class E>
void skipList<K,E>::insert(const pair<const K, E> &thePair) {//插入
    if(thePair.first>=tailKey){
        cout<<"insert error"<<endl;
        return ;
    }
    skipNode<K,E>* theNode= search(thePair.first);
    if(theNode->element.first==thePair.first){//已经存在
        theNode->element.second=thePair.second;
        return ;
    }
    int theLevel=level();
    if(theLevel>levels){//比当前最大层数大，加一层
        theLevel=++levels;
        last[theLevel]=headerNode;
    }
    skipNode<K,E>* newNode=new skipNode<K,E>(thePair,theLevel+1);
    newNode->level=theLevel;
    for(int i=0;i<=theLevel;i++){//插入
        action_num++;
        newNode->next[i]=last[i]->next[i];
        last[i]->next[i]=newNode;
    }

    dSize++;
    all_num++;
    return ;
}

template<class K,class E>
void skipList<K,E>::erase(const K& theKey){//删除
    if(theKey>=tailKey)
        return ;
    skipNode<K,E>* theNode= search(theKey);
    if(theNode->element.first!=theKey)
        return ;
    for(int i=0;i<=levels&&last[i]->next[i]==theNode;i++) {//删除
        last[i]->next[i] = theNode->next[i];
        action_num++;
    }
    while(levels>0&&headerNode->next[levels]==tailNode) {//更新链表级
        levels--;
        action_num++;
    }
    delete theNode;
    dSize--;
    all_num--;
}

template<class K,class E>
void skipList<K,E>::eraseThemin() {//删除第一个
    erase(headerNode->next[0]->element.first);
}

template<class K,class E>
void skipList<K,E>::eraseThemax() {//删除最后一个
    skipNode<K,E>* cc=headerNode;
    while(cc->next[0]!=tailNode){
        cc=cc->next[0];
    }
    erase(cc->element.first);
}

template<class K,class E>
void skipList<K,E>::reset(float p) {
    int num=0;
    skipNode<K,E>* cc=headerNode->next[0];
    while(cc!=tailNode){
        num++;
        cc=cc->next[0];
        action_num++;
    }
    int a[num];
    cc=headerNode->next[0];
    for(int i=0;i<num;i++){//将所有节点存在数组里
        a[i]=cc->element.first;
        cc=cc->next[0];
        action_num++;
    }
    this->initial(a,num,p);//利用数组初始化
    cout<<"reset success"<<endl;
}

void selectionSort(int a[],int n){//排序
    bool sorted=false;
    for(int size=n;!sorted&&(size>1);size--){
        int indexOfMax=0;
        sorted=true;
        for(int i=1;i<size;i++)
            if(a[indexOfMax]<=a[i])indexOfMax=i;
            else sorted=false;
        int x=a[size-1];
        a[size-1]=a[indexOfMax];
        a[indexOfMax]=x;
    }
}


int main(){
    /*
    int c[1000];
    srand(time(nullptr));
    for(int i=0;i<1000;i++){

        c[i]=rand()%3000;
    }
    selectionSort(c,1000);
    for(int i=0;i<=999;i++){
        cout<<i<<" "<<c[i]<<" ";
    }
    cout<<endl;*/


    skipList<int ,int>a(3000,1200,0.5);


    int b[50];
    for(int i=0;i<50;i++){
        b[i]=i+1;
    }
    a.initial(b,50,0.5);
    a.test();
    /*
    a.search(31);
    cout<<action_num<<endl;


    a.find(10);
    a.erase(10);
    a.find(10);
    a.find(51);
    pair<int,int>ca(51,51);
    a.insert(ca);
    a.find(51);
    a.test();
    a.reset(0.5);
    a.test();*/


    /*
    pair<int,int>p1(54,51);//插入测试
    pair<int,int>p2(52,51);
    pair<int,int>p3(56,51);
    pair<int,int>p4(58,51);
    pair<int,int>p5(59,51);
    pair<int,int>p6(70,51);
    pair<int,int>p7(74,51);
    pair<int,int>p8(78,51);
    a.insert(p1);
    a.insert(p2);
    a.insert(p3);
    a.insert(p4);
    a.insert(p5);
    a.insert(p6);
    a.insert(p7);
    a.insert(p8);
    a.test();
    a.reset(0.5);
    a.test();*/



    a.erase(10);//删除测试
    a.erase(14);
    a.erase(16);
    a.erase(26);
    a.erase(30);
    a.erase(42);
    a.eraseThemin();
    a.eraseThemax();
    a.test();
    a.reset(0.5);
    a.test();



    /*
    a.initial(c,1000,0.5);//1000个随机数
    a.test();
    DWORD start_time = GetTickCount();
    for(int i=0;i<=100;i++){
        action_num=0;
        //a.erase(rand()%3000);
        //a.find(rand()%3000);
        //pair<int,int>d(rand()%3000,rand()%3000);
        //a.insert(d);
        //cout<<action_num<<endl;
        //if(action_num>=10)
            //a.reset(0.5);
    }
    DWORD end_time = GetTickCount();
    cout << "The run time is:" << (end_time - start_time) << "ms!" << endl;*/



    /*
    int d[50],e[500];//时间对比
    for(int i=0;i<50;i++){
        d[i]=i;
    }
    for(int i=0;i<500;i++){
        e[i]=i;
    }
    skipList<int ,int>x(5000,1000000,0.5);
    x.initial(d,50,0.5);
    DWORD start_time_1 = GetTickCount();
    for(int i=0;i<=500000;i++){
        action_num=0;
        x.search(rand()%50);
        //pair<int,int>s(rand()%5000,rand()%50);
        //x.insert(s);
        //DWORD start_time_2 = GetTickCount();;
        //x.search(rand()%50);
        //DWORD end_time_2 = GetTickCount();
        //if((end_time_2 - start_time_2)>=2){//如果时间超过10ms则重构
         //   cout<<"time used: "<<(end_time_2 - start_time_2)<<endl;
           // x.reset(0.5);
       // }
       if(action_num>all_num/10){
           x.reset(0.5);
       }

    }
    DWORD end_time_1 = GetTickCount();
    cout << "The run time for d[50] is:" << (end_time_1 - start_time_1) << "ms!" << endl;


    skipList<int ,int>y(5000,1000000,0.5);
    y.initial(e,500,0.5);
    DWORD start_time_3 = GetTickCount();
    for(int i=0;i<=500000;i++){

        //DWORD start_time_2 = GetTickCount();;
        //pair<int,int>s(rand()%500,rand()%500);
        //y.insert(s);
        //y.search(rand()%500);
        //DWORD end_time_2 = GetTickCount();
        //if((end_time_2 - start_time_2)>=10){
         //   cout<<"time used: "<<(end_time_2 - start_time_2)<<endl;;
        //    y.reset(0.5);
        //}
        action_num=0;
        //pair<int,int>s(rand()%5000,rand()%50);
        //y.insert(s);
        y.search(rand()%500);
        if(action_num>all_num/10){
            y.reset(0.5);
        }
    }
    DWORD end_time_3 = GetTickCount();
    cout << "The run time for e[500] is:" << (end_time_3 - start_time_3) << "ms!" << endl;*/

    return 0;

}

