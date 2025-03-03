#include<iostream>
#include<bits/stdc++.h>
using namespace std;
enum Data_type { INT, CHAR };//定义数据类型
struct Data
{
    Data_type datatag;//数据标签，如果是数值则为INT，如果是字符则为CHAR
    union{
        int num;//储存数值
        char c;//储存变量或操作符
    };
};
struct binarynode//节点定义
{
    Data element;//储存数值或字符
    binarynode* leftchild= nullptr, * rightchild= nullptr;//左右孩子初始化
    binarynode(){
        leftchild = rightchild = nullptr;
    }
    binarynode(const Data& e){
        element = e;
        leftchild = rightchild = nullptr;
    }
    binarynode(const Data& e, binarynode* l, binarynode* r){
        element = e;
        leftchild = l;
        rightchild = r;
    }
};
class binarytree {
public:
    binarynode *root;//根节点
    bool judge_all_num=true;//判断树上是否存在变量，若存在则为false
    bool isoperator(char op) {//判断输入的字符是否是运算符，是则返回true
        if (op == '+' || op == '-' || op == '*' || op == '/' || op == '^')
            return true;
        else
            return false;
    }

    bool ReadExpr(string E) {//根据前缀表达式构造表达式二叉树
        stack<binarynode *> s;//栈s用于临时存放数据
        int length = E.length();
        root = new binarynode;
        if (length == 1) {//对于只有1个长度的情况单独判断
            if (isdigit(E[0])) {//如果是数值则构造成功
                root->element.datatag = INT;
                root->element.num = E[0] - '0';
                return true;
            } else {//一个长度的表达式不能为运算符
                cout << "输入错误" << endl;
                return false;
            }
        }
        for (int i = length - 1; i >= 0; i--) {//从后往前读取
            binarynode *p = new binarynode;
            if (isdigit(E[i])) {//如果是数值
                p->element.datatag = INT;
                p->element.num = E[i] - '0';
            } else {//如果是字符
                p->element.datatag = CHAR;
                p->element.num = E[i];
            }
            if (isoperator(E[i])) {//如果是运算符，则从栈中取出最近的两个节点将其赋给p的左右孩子
                p->leftchild = s.top();
                s.pop();
                p->rightchild = s.top();
                s.pop();
            }
            s.push(p);//将节点放入栈中
        }
        root = s.top();//将结果赋值给root
        s.pop();//结果出栈
        if (s.empty())//如果栈中无多余节点
            return true;
        else {
            cout << "存在多余输入" << endl;
            return false;
        }
    }

    bool pri_judge(char a,char b){//对两个运算符判断优先级,如果a优先级高则返回true
        if(!isoperator(a) || !isoperator(b))//
            return false;
        if(a=='^'){//乘幂优先级最高
            return true;
        }
        if(a=='*'||a=='/'){//加减比乘除优先级低
            if(b=='+'||b=='-')
                return true;
            else
                return false;
        }
        if(a=='-'&&b=='-')//同为-的话需要加上括号
            return true;
        return false;

    }

    void inorder(binarynode *r){//中序输出
        if(!r)//节点为空
            return;

        if(r->leftchild &&r ->leftchild->element.datatag==CHAR && pri_judge(r->element.c, r->leftchild->element.c)){//先遍历左孩子
            cout << "(";//如果r优先级较高则加上括号
            inorder(r->leftchild);
            cout << ")";
        }
        else
            inorder(r->leftchild);

        if (r->element.datatag == INT)//遍历自身
            cout << r->element.num;
        else
            cout << r->element.c;

        if(r->rightchild &&r ->rightchild->element.datatag==CHAR && pri_judge(r->element.c, r->rightchild->element.c)){//遍历右孩子
            cout << "(";
            inorder(r->rightchild);
            cout << ")";
        }
        else
            inorder(r->rightchild);

    }
    void WriteExpr(){//对中序输出函数进行封装
        cout<<"带括号的中缀表达式为：";
        inorder(root);
        cout<<endl;
    }



    void Assign(binarynode *r,char v,int c){//遍历整颗树，将v赋值为c
        if(!r)
            return;
        if(r->element.c==v){//如果找到v，则将其赋值为c
            r->element.datatag=INT;
            r->element.num=c;
        }
        Assign(r->leftchild,v,c);//遍历左右孩子
        Assign(r->rightchild,v,c);
    }



    void all_num(binarynode*r){//遍历二叉树，判断树中是否存在变量
        if(!r)
            return;
        if(r->element.datatag==CHAR){//如果数据类型为CHAR且不为操作符则为变量
            if(r->element.c!='+'&&r->element.c!='-'&&r->element.c!='*'&&r->element.c!='/'&&r->element.c!='^'){
                judge_all_num= false;
                return;
            }
        }
        all_num(r->leftchild);//遍历左右孩子
        all_num(r->rightchild);
    }
    int calculate(int a,int b,char op){//计算函数，根据数值和运算符返回结果
        if(op=='+')
            return a+b;
        else if(op=='-')
            return a-b;
        else if(op=='*')
            return a*b;
        else if(op=='/'){
            if(b==0){
                cout<<"除数不能为0"<<endl;
                return a;
            }
            else
                return a/b;
        }
        else if(op=='^')
            return pow(a,b);
    }
    int Value(binarynode* r){//求值运算
        if(r!= nullptr){
           if(r->leftchild== nullptr&&r->rightchild== nullptr&&r->element.datatag==INT)//递归到叶节点，返回数值
               return r->element.num;
            return calculate(Value(r->leftchild), Value(r->rightchild),r->element.c);//为运算符则返回和左右孩子运算的结果
        }
    }
    void Value_calculate(){//封装的求值函数
        judge_all_num=true;
        all_num(root);
        if(!judge_all_num){
            cout<<"存在变量，无法求值"<<endl;
            return;
        }
        cout<<"求值运算：";
        inorder(root);
        cout<<"="<<Value(root)<<endl;
    }

    void CompoundExpr(char p,string E1,string E2){//合并函数，传入运算符和两个表达式
        binarytree c,d;//用两个表达式分别构造两棵二叉树
        c.ReadExpr(E1);
        d.ReadExpr(E2);
        binarynode *z=new binarynode;
        z->element.datatag=CHAR;
        z->element.c=p;
        root=z;
        //root->element.datatag=CHAR;
        //root->element.c=p;//root的值为p
        root->leftchild=c.root;//将两课树的根与root连接
        root->rightchild=d.root;
    }

    void merge(binarynode * r){//初步合并
        if(r->leftchild!= nullptr&&r->rightchild!= nullptr){
            if(r->leftchild->element.datatag==INT&&r->rightchild->element.datatag==INT){//如果一个节点为运算符且左右孩子为数值则可以合并
                int result= calculate(r->leftchild->element.num,r->rightchild->element.num,r->element.c);//运算结果
                r->element.datatag=INT;//改变数据类型
                r->element.num=result;//赋值
                delete r->leftchild;//删除左右孩子
                delete r->rightchild;
                r->rightchild= nullptr;
                r->leftchild= nullptr;
            }
            else{
                merge(r->leftchild);//遍历整颗树寻找满足要求的节点
                merge(r->rightchild);
            }
        }
    }
    void merge1(binarynode *r){
        if(r->element.c=='+'&&r->leftchild!= nullptr&&r->rightchild!= nullptr){
            if(r->rightchild->leftchild!= nullptr&&r->rightchild->rightchild!= nullptr){
                if(r->leftchild->element.datatag==INT&&(r->rightchild->element.c=='+'||r->rightchild->element.c=='-')){
                    if(r->rightchild->leftchild->element.datatag==INT&&r->rightchild->rightchild->element.datatag==CHAR){
                        binarynode *c=new binarynode;//+2-5a
                        c->element.datatag=INT;
                        c->element.num=r->leftchild->element.num+r->rightchild->leftchild->element.num;//数值合并
                        r->element.c=r->rightchild->element.c;//改变运算符
                        r->leftchild=c;//左孩子为合并后的节点
                        r->rightchild=r->rightchild->rightchild;//右孩子为变量
                    }
                    else if(r->rightchild->leftchild->element.datatag==CHAR&&r->rightchild->rightchild->element.datatag==INT){
                        binarynode *c=new binarynode;
                        c->element.datatag=INT;
                        if(r->rightchild->element.c=='+')//+5+a3
                            c->element.num=r->leftchild->element.num+r->rightchild->rightchild->element.num;
                        if(r->rightchild->element.c=='-')//+5-a3
                            c->element.num=r->leftchild->element.num-r->rightchild->rightchild->element.num;
                        r->element.c=r->rightchild->element.c;
                        r->leftchild=c;
                        r->rightchild=r->rightchild->leftchild;
                    }
                }
            }
            else if(r->leftchild->leftchild!= nullptr&&r->leftchild->rightchild!= nullptr){
                if(r->rightchild->element.datatag==INT&&(r->leftchild->element.c=='+'||r->leftchild->element.c=='-')){
                    if(r->leftchild->leftchild->element.datatag==INT&&r->leftchild->rightchild->element.datatag==CHAR){//+-3a2
                        binarynode *c=new binarynode;
                        c->element.datatag=INT;
                        c->element.num=r->rightchild->element.num+r->leftchild->leftchild->element.num;
                        r->element.c=r->leftchild->element.c;
                        r->rightchild=r->leftchild->rightchild;
                        r->leftchild=c;
                    }
                    else if(r->leftchild->leftchild->element.datatag==CHAR&&r->leftchild->rightchild->element.datatag==INT){//+-a35
                        binarynode *c=new binarynode;
                        c->element.datatag=INT;
                        if(r->leftchild->element.c=='+')
                            c->element.num=r->rightchild->element.num + r->leftchild->rightchild->element.num;
                        if(r->leftchild ->element.c=='-')
                            c->element.num=r->rightchild->element.num - r->leftchild->rightchild->element.num;
                        r->element.c='+';
                        if(c->element.num<0){
                            r->element.c='-';
                            c->element.num= abs(c->element.num);
                        }
                        r->rightchild=c;
                        r->leftchild=r->leftchild->leftchild;
                    }
                }
            }
        }

        if(r->element.c=='-'&&r->leftchild!= nullptr&&r->rightchild!= nullptr){
            if(r->rightchild->leftchild!= nullptr&&r->rightchild->rightchild!= nullptr){
                if(r->leftchild->element.datatag==INT&&(r->rightchild->element.c=='+'||r->rightchild->element.c=='-')){//
                    if(r->rightchild->leftchild->element.datatag==INT&&r->rightchild->rightchild->element.datatag==CHAR){
                        binarynode *c=new binarynode;
                        c->element.datatag=INT;
                        c->element.num=r->leftchild->element.num+r->rightchild->leftchild->element.num;
                        r->element.c=r->rightchild->element.c;
                        r->leftchild=c;
                        r->rightchild=r->rightchild->rightchild;
                    }
                    else if(r->rightchild->leftchild->element.datatag==CHAR&&r->rightchild->rightchild->element.datatag==INT){//
                        binarynode *c=new binarynode;
                        c->element.datatag=INT;
                        if(r->rightchild->element.c=='+')
                            c->element.num=r->leftchild->element.num+r->rightchild->rightchild->element.num;
                        if(r->rightchild->element.c=='-')
                            c->element.num=r->leftchild->element.num-r->rightchild->rightchild->element.num;
                        r->element.c=r->rightchild->element.c;
                        r->leftchild=c;
                        r->rightchild=r->rightchild->leftchild;
                    }
                }
            }
            else if(r->leftchild->leftchild!= nullptr&&r->leftchild->rightchild!= nullptr){
                if(r->rightchild->element.datatag==INT&&(r->leftchild->element.c=='+'||r->leftchild->element.c=='-')){
                    if(r->leftchild->leftchild->element.datatag==INT&&r->leftchild->rightchild->element.datatag==CHAR){//            -+3a2
                        binarynode *c=new binarynode;
                        c->element.datatag=INT;
                        c->element.num=r->leftchild->leftchild->element.num-r->rightchild->element.num;
                        r->element.c=r->leftchild->element.c;
                        r->rightchild=r->leftchild->rightchild;
                        r->leftchild=c;
                    }
                    else if(r->leftchild->leftchild->element.datatag==CHAR&&r->leftchild->rightchild->element.datatag==INT){//              -+a32
                        binarynode *c=new binarynode;
                        c->element.datatag=INT;
                        if(r->leftchild->element.c=='+')
                            c->element.num= r->leftchild->rightchild->element.num-r->rightchild->element.num ;
                        if(r->leftchild ->element.c=='-')
                            c->element.num= r->leftchild->rightchild->element.num-r->rightchild->element.num;
                        r->element.c=r->leftchild->element.c;
                        r->rightchild=c;
                        r->leftchild=r->leftchild->leftchild;
                    }
                }
            }
        }
        if(r->leftchild!= nullptr)//判断完当前节点后判断其左右节点
            merge1(r->leftchild);
        if(r->rightchild!= nullptr)
            merge1(r->rightchild);

    }

    void MergeConst(){
        merge(root);
        merge(root);
        merge(root);
        merge(root);
        merge(root);
        merge(root);
        merge1(root);
        merge1(root);
        merge1(root);
        merge1(root);
        cout<<"合并常数后的表达式为：";
        inorder(root);
        cout<<endl;
    }




//+-+a/31*6/-522+^24^25     *+2-3a+b*34        2-(5-4)   -2-54     -+a/31*2/-422
};

int main(){
    binarytree a;
    char v;
    int c=0;
    string Expression;
    int op;
    string e1,e2;
    char p;
    cout<<"（1）ReadExpr(E)-以字符序列的形式输入语法正确的前缀表达式并构造表达式E。"<<endl;
    cout<<"（2）WriteExpr(E)-用带括弧的中缀表达式输出表达式E。"<<endl;
    cout<<"（3）Assign(V,c)-实现对变量V的赋值（V=c）,变量的初值为0。"<<endl;
    cout<<"（4）Value(E)-对算术表达式E求值。"<<endl;
    cout<<"（5）CompoundExpr(P,E1,E2)-构造一个新的复合表达式（E1）P（E2）。"<<endl;
    cout<<" (6) 合并常数操作MergeConst（E）—合并表达式E中所有常数运算。"<<endl;
    cout<<"（7）退出."<<endl;
    while(1){

        cin>>op;
        switch (op) {
            case 1:
                cout<<"请输入前缀表达式：";
                cin>>Expression;
                a.ReadExpr(Expression);
                break;
            case 2:
                a.WriteExpr();
                break;
            case 3:
                cin>>v>>c;
                a.Assign(a.root,v,c);
                break;
            case 4:
                a.Value_calculate();
                break;
            case 5:
                cout<<"请输入e1 p e2 "<<endl;
                cin>>e1>>p>>e2;
                a.CompoundExpr(p,e1,e2);
                a.WriteExpr();
                break;
            case 6:
                a.MergeConst();
                break;
            case 7:
                return 0;

        }
    }



    return 0;
}