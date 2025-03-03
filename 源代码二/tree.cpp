#include<iostream>
#include<bits/stdc++.h>
using namespace std;
enum Data_type { INT, CHAR };//������������
struct Data
{
    Data_type datatag;//���ݱ�ǩ���������ֵ��ΪINT��������ַ���ΪCHAR
    union{
        int num;//������ֵ
        char c;//��������������
    };
};
struct binarynode//�ڵ㶨��
{
    Data element;//������ֵ���ַ�
    binarynode* leftchild= nullptr, * rightchild= nullptr;//���Һ��ӳ�ʼ��
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
    binarynode *root;//���ڵ�
    bool judge_all_num=true;//�ж������Ƿ���ڱ�������������Ϊfalse
    bool isoperator(char op) {//�ж�������ַ��Ƿ�������������򷵻�true
        if (op == '+' || op == '-' || op == '*' || op == '/' || op == '^')
            return true;
        else
            return false;
    }

    bool ReadExpr(string E) {//����ǰ׺���ʽ������ʽ������
        stack<binarynode *> s;//ջs������ʱ�������
        int length = E.length();
        root = new binarynode;
        if (length == 1) {//����ֻ��1�����ȵ���������ж�
            if (isdigit(E[0])) {//�������ֵ����ɹ�
                root->element.datatag = INT;
                root->element.num = E[0] - '0';
                return true;
            } else {//һ�����ȵı��ʽ����Ϊ�����
                cout << "�������" << endl;
                return false;
            }
        }
        for (int i = length - 1; i >= 0; i--) {//�Ӻ���ǰ��ȡ
            binarynode *p = new binarynode;
            if (isdigit(E[i])) {//�������ֵ
                p->element.datatag = INT;
                p->element.num = E[i] - '0';
            } else {//������ַ�
                p->element.datatag = CHAR;
                p->element.num = E[i];
            }
            if (isoperator(E[i])) {//���������������ջ��ȡ������������ڵ㽫�丳��p�����Һ���
                p->leftchild = s.top();
                s.pop();
                p->rightchild = s.top();
                s.pop();
            }
            s.push(p);//���ڵ����ջ��
        }
        root = s.top();//�������ֵ��root
        s.pop();//�����ջ
        if (s.empty())//���ջ���޶���ڵ�
            return true;
        else {
            cout << "���ڶ�������" << endl;
            return false;
        }
    }

    bool pri_judge(char a,char b){//������������ж����ȼ�,���a���ȼ����򷵻�true
        if(!isoperator(a) || !isoperator(b))//
            return false;
        if(a=='^'){//�������ȼ����
            return true;
        }
        if(a=='*'||a=='/'){//�Ӽ��ȳ˳����ȼ���
            if(b=='+'||b=='-')
                return true;
            else
                return false;
        }
        if(a=='-'&&b=='-')//ͬΪ-�Ļ���Ҫ��������
            return true;
        return false;

    }

    void inorder(binarynode *r){//�������
        if(!r)//�ڵ�Ϊ��
            return;

        if(r->leftchild &&r ->leftchild->element.datatag==CHAR && pri_judge(r->element.c, r->leftchild->element.c)){//�ȱ�������
            cout << "(";//���r���ȼ��ϸ����������
            inorder(r->leftchild);
            cout << ")";
        }
        else
            inorder(r->leftchild);

        if (r->element.datatag == INT)//��������
            cout << r->element.num;
        else
            cout << r->element.c;

        if(r->rightchild &&r ->rightchild->element.datatag==CHAR && pri_judge(r->element.c, r->rightchild->element.c)){//�����Һ���
            cout << "(";
            inorder(r->rightchild);
            cout << ")";
        }
        else
            inorder(r->rightchild);

    }
    void WriteExpr(){//����������������з�װ
        cout<<"�����ŵ���׺���ʽΪ��";
        inorder(root);
        cout<<endl;
    }



    void Assign(binarynode *r,char v,int c){//��������������v��ֵΪc
        if(!r)
            return;
        if(r->element.c==v){//����ҵ�v�����丳ֵΪc
            r->element.datatag=INT;
            r->element.num=c;
        }
        Assign(r->leftchild,v,c);//�������Һ���
        Assign(r->rightchild,v,c);
    }



    void all_num(binarynode*r){//�������������ж������Ƿ���ڱ���
        if(!r)
            return;
        if(r->element.datatag==CHAR){//�����������ΪCHAR�Ҳ�Ϊ��������Ϊ����
            if(r->element.c!='+'&&r->element.c!='-'&&r->element.c!='*'&&r->element.c!='/'&&r->element.c!='^'){
                judge_all_num= false;
                return;
            }
        }
        all_num(r->leftchild);//�������Һ���
        all_num(r->rightchild);
    }
    int calculate(int a,int b,char op){//���㺯����������ֵ����������ؽ��
        if(op=='+')
            return a+b;
        else if(op=='-')
            return a-b;
        else if(op=='*')
            return a*b;
        else if(op=='/'){
            if(b==0){
                cout<<"��������Ϊ0"<<endl;
                return a;
            }
            else
                return a/b;
        }
        else if(op=='^')
            return pow(a,b);
    }
    int Value(binarynode* r){//��ֵ����
        if(r!= nullptr){
           if(r->leftchild== nullptr&&r->rightchild== nullptr&&r->element.datatag==INT)//�ݹ鵽Ҷ�ڵ㣬������ֵ
               return r->element.num;
            return calculate(Value(r->leftchild), Value(r->rightchild),r->element.c);//Ϊ������򷵻غ����Һ�������Ľ��
        }
    }
    void Value_calculate(){//��װ����ֵ����
        judge_all_num=true;
        all_num(root);
        if(!judge_all_num){
            cout<<"���ڱ������޷���ֵ"<<endl;
            return;
        }
        cout<<"��ֵ���㣺";
        inorder(root);
        cout<<"="<<Value(root)<<endl;
    }

    void CompoundExpr(char p,string E1,string E2){//�ϲ�������������������������ʽ
        binarytree c,d;//���������ʽ�ֱ������ö�����
        c.ReadExpr(E1);
        d.ReadExpr(E2);
        binarynode *z=new binarynode;
        z->element.datatag=CHAR;
        z->element.c=p;
        root=z;
        //root->element.datatag=CHAR;
        //root->element.c=p;//root��ֵΪp
        root->leftchild=c.root;//���������ĸ���root����
        root->rightchild=d.root;
    }

    void merge(binarynode * r){//�����ϲ�
        if(r->leftchild!= nullptr&&r->rightchild!= nullptr){
            if(r->leftchild->element.datatag==INT&&r->rightchild->element.datatag==INT){//���һ���ڵ�Ϊ����������Һ���Ϊ��ֵ����Ժϲ�
                int result= calculate(r->leftchild->element.num,r->rightchild->element.num,r->element.c);//������
                r->element.datatag=INT;//�ı���������
                r->element.num=result;//��ֵ
                delete r->leftchild;//ɾ�����Һ���
                delete r->rightchild;
                r->rightchild= nullptr;
                r->leftchild= nullptr;
            }
            else{
                merge(r->leftchild);//����������Ѱ������Ҫ��Ľڵ�
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
                        c->element.num=r->leftchild->element.num+r->rightchild->leftchild->element.num;//��ֵ�ϲ�
                        r->element.c=r->rightchild->element.c;//�ı������
                        r->leftchild=c;//����Ϊ�ϲ���Ľڵ�
                        r->rightchild=r->rightchild->rightchild;//�Һ���Ϊ����
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
        if(r->leftchild!= nullptr)//�ж��굱ǰ�ڵ���ж������ҽڵ�
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
        cout<<"�ϲ�������ı��ʽΪ��";
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
    cout<<"��1��ReadExpr(E)-���ַ����е���ʽ�����﷨��ȷ��ǰ׺���ʽ��������ʽE��"<<endl;
    cout<<"��2��WriteExpr(E)-�ô���������׺���ʽ������ʽE��"<<endl;
    cout<<"��3��Assign(V,c)-ʵ�ֶԱ���V�ĸ�ֵ��V=c��,�����ĳ�ֵΪ0��"<<endl;
    cout<<"��4��Value(E)-���������ʽE��ֵ��"<<endl;
    cout<<"��5��CompoundExpr(P,E1,E2)-����һ���µĸ��ϱ��ʽ��E1��P��E2����"<<endl;
    cout<<" (6) �ϲ���������MergeConst��E�����ϲ����ʽE�����г������㡣"<<endl;
    cout<<"��7���˳�."<<endl;
    while(1){

        cin>>op;
        switch (op) {
            case 1:
                cout<<"������ǰ׺���ʽ��";
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
                cout<<"������e1 p e2 "<<endl;
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