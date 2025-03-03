#include<iostream>
#include<bits/stdc++.h>
#include"tree.cpp"
using namespace std;
int times=0,tindex=0,tmax=10;//times为访问文件次数，tindex为缓冲区中数值的下标，tmax为缓冲区的大小

template<class T>
class buffer{//缓冲区
public:
    int *a;
    buffer(){
        a=new int[tmax];
    }
};

template<class T>
class Merge{
public:
    int Size;//size为输者树的数据个数
    string answer="b.txt";//储存结果的文件
    int NumberOfFile=0,NumberOfCombine=8;//NumberOfFile为需要归并的文件数量，NumberOfCombine为每次归并的文件数
    string origin_name="file-";//归并段命名
    Merge(int s){
        Size=s;
    }
    void make(string name){//作出归并段
        ifstream a(name,ios::in);//打开需要排序的文件
        assert(a.is_open());
        int num_all;
        a>>num_all;
        Node *z=new Node[Size];
        for(int i=0;i<Size;i++){//将数值传入数组
            a>>z[i].number;
            z[i].id=1;}
        losetree<Node>b(z,Size);
        while(1){//在文件不断向输者树输送数的过程中将输者树最顶端的元素存入新建立的文件
            if(a.eof())
                break;
            Node p;//将新值存入p
            a>>p.number;
            if(p.number>=b.winner().number)//判断新数的id大小
                p.id=b.winner().id;
            else{
                p.id=b.winner().id+1;
                NumberOfFile=max(NumberOfFile,p.id);
            }
            string file_name=origin_name+ to_string(b.winner().id);//根据数的id大小打开对应的文件
            ofstream c(file_name,ios::app);
            times++;//增加访存次数
            c<<b.winner().number<<" ";//存入数据
            c.close();
            b.reinit(p);//将文件中取出的数放入树中
        }
        while(1){//将树中剩余的数取出
            if(b.winner().number==MAX_INT)
                break;
            string file_name=origin_name+ to_string(b.winner().id);//根据数的id大小打开对应的文件
            ofstream c(file_name,ios::app);
            times++;
            c<<b.winner().number<<" ";
            Node p;
            p.number=MAX_INT,p.id=MAX_INT;
            b.reinit(p);//用MAX_INT填充输者树
            c.close();
        }
        cout<<NumberOfFile<<endl;
    }
    void combine();
};



template<class T>
void Merge<T>::combine()//归并段合并
{
    int num=NumberOfFile,file_empty=1,an,bn,fnum=0,dnum=NumberOfFile;//fnum储存需要打开的文件的下标，dnum是需要合并的文件数
    int anum=NumberOfFile;//anum为文件的最大下标
    buffer<int>t;
    while(1){
        tindex=0;
        if(dnum>NumberOfCombine){//如果当前需要合并的文件数大于k，则将k个文件合并
            string a[NumberOfCombine];
            ifstream* c = new ifstream[NumberOfCombine];
            int b[NumberOfCombine],d[NumberOfCombine];
            int j=fnum;
            for(int i=0;i<NumberOfCombine;i++){//打开需要合并的文件
                a[i]=origin_name+ to_string(j+1);
                j++;
                cout<<a[i]<<endl;
                c[i].open(a[i],ios::in);
            }
            times+=NumberOfCombine;
            fnum+=NumberOfCombine;
            string file_name=origin_name+ to_string(anum+1);//定义储存合并结果的文件名为file-anum+1
            ofstream file_answer(file_name,ios::app);
            anum++;
            dnum=dnum+1-NumberOfCombine;//需要合并的文件数为n+1-k
            for(int i=0;i<NumberOfCombine;i++){//从各个文件中取出一个数值储存在数组b上
                c[i]>>b[i];
                //cout<<b[i]<<endl;
            }
            losetree<int>tree(b,NumberOfCombine);
            while(1){
                file_empty=1;
                for(int i=0;i<NumberOfCombine;i++){
                    d[i]=0;
                    if(!c[i].eof()){
                        file_empty=0;
                        d[i]=1;
                    }
                }
                if(file_empty==1)//如果所有文件都为空，则退出
                    break;
                an=tree.winner();//an为输者树的最小值
                bn=tree.player2();//bn为最小值的下标，bn确定下一个数值从哪个文件取出
                if(c[bn].eof()){//如果该文件为空，则用man_int填充
                    tree.reinit(MAX_INT);
                }
                else{
                    c[bn]>>b[bn];//从c[bn]中取出一个数据
                    tree.reinit(b[bn]);
                    //file_answer<<an<<" ";
                    t.a[tindex]=an;//将结果填入缓冲区
                    tindex++;
                    if(tindex==tmax){//如果缓存区满了，则全部取出
                        for(int i=0;i<tindex;i++){
                            file_answer<<t.a[i]<<" ";
                        }
                        tindex=0;
                    }
                }
            }
            if(tindex!=0){//清空缓存区
                for(int i=0;i<tindex;i++){
                    file_answer<<t.a[i]<<" ";
                }
            }
            tindex=0;

            file_answer.close();
            cout<<"new file: "<<file_name<<endl;//归并出的新文件
            //cout<<"fnum:"<<fnum<<endl;
            cout<<endl;
            times++;
            for(int i=0;i<NumberOfCombine;i++){
                c[i].close();
            }
        }
        else{//如果需要归并的文件树小于等于k
            string a[dnum];//归并剩余文件
            ifstream* c = new ifstream[dnum];
            int b[dnum],d[dnum];
            int j=fnum;
            for(int i=0;i<dnum;i++){//打开需要归并的文件
                a[i]=origin_name+ to_string(j+1);
                j++;
                cout<<a[i]<<endl;
                c[i].open(a[i],ios::in);
            }
            times+=dnum+1;
            ofstream file_answer(answer,ios::app);//将结果储存在answer=b文件中
            for(int i=0;i<dnum;i++){
                c[i]>>b[i];
                //cout<<b[i]<<endl;
            }
            losetree<int>tree(b,dnum);
            while(1){//每次从输者树中取出最小值后，从对应的文件中取数填充，直到所有文件为空
                file_empty=1;
                for(int i=0;i<dnum;i++){
                    d[i]=0;
                    if(!c[i].eof()){
                        file_empty=0;
                        d[i]=1;
                    }
                }
                if(file_empty==1)
                    break;
                an=tree.winner();
                bn=tree.player2();
                if(c[bn].eof()){
                    tree.reinit(MAX_INT);
                }
                else{
                    c[bn]>>b[bn];//从文件取数
                    //cout<<bn<<" "<<b[bn]<<" "<<an<<endl;
                    tree.reinit(b[bn]);
                    //file_answer<<an<<" ";
                   t.a[tindex]=an;
                   tindex++;
                   if(tindex==tmax){//缓冲区满
                       for(int i=0;i<tindex;i++){
                           file_answer<<t.a[i]<<" ";
                       }
                       tindex=0;
                   }

                }
            }

            if(tindex!=0){//清空缓冲区
                for(int i=0;i<tindex;i++){
                    file_answer<<t.a[i]<<" ";
                }
            }
            tindex=0;

            file_answer.close();
            for(int i=0;i<dnum;i++){
                c[i].close();
            }
            break;
        }
    }
}



int main(){
    Merge<int> z(2);
    z.make("a.txt");
    cout<<"times in make:"<<times<<endl;
    z.combine();
    cout<<z.NumberOfFile<<endl;
    cout<<"times in all:"<<times<<endl;
    /*
    ifstream a("a.txt");
    assert(a.is_open());
    int b,num;
    a>>num;
    int c[num];
    for(int i=0;i<num;i++){
        a>>c[i];
    }
    losetree<int> d(c,num);
    cout<<d.winner()<<"  "<<d.player2()<<endl;
    a.close();*/
    return 0;
}

