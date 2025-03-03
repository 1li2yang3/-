#include<bits/stdc++.h>

using namespace std;

struct TreeNode {
    bool flag_file;//判断是文件还是目录
    char fileName[10];//名称
    struct TreeNode *parent;//父节点指针
    struct TreeNode *head;//子节点头
    struct TreeNode *next;//子节点
};

class CatalogTree {
public:
    TreeNode* root;//根
    TreeNode* currentPosition;//当前位置
    CatalogTree(){//构造函数，初始化根
        TreeNode* p = (struct TreeNode*)malloc(sizeof(struct TreeNode));
        memset(p->fileName, 0, sizeof(p->fileName));
        p->fileName[0] = '/';
        p->flag_file = false;
        p->head = NULL;
        p->parent = NULL;
        p->next = NULL;
        root=p;
        currentPosition=root;
    }
    void mkdir(char *name){
        if(name[0]!='/'){//相对路径
            TreeNode* p;
            TreeNode* t=currentPosition;
            for (p = t->head; p != NULL; p =p->next) {//遍历，判断该名是否存在
                if (strcmp(p->fileName, name) == 0) {
                    cout <<"文件或目录已存在"<< endl;
                    return;
                }
            }
            p=(TreeNode*)malloc(sizeof(struct TreeNode));
            p->parent = t;
            p->head = NULL;
            p->flag_file = false;
            strcpy(p->fileName, name);
            p->next = t->head;
            t->head = p;
        }
        else{//绝对路径
            TreeNode* p;
            TreeNode* t = root;
            const char *fenge = "/";
            char *lujing;
            char * str=name;
            char * n1;
            lujing = strtok(str, fenge);//分割出每个层次的文件名称
            bool flag;
            while (lujing){//当还存在文件名时，既路径未结束
                flag = false;
                p=t->head;
                while(p!=NULL){
                    if (strcmp(p->fileName, lujing) == 0&&p->flag_file == false) {//查找目录
                        t = p;
                        flag = true;
                        break;
                    }
                    p=p->next;
                }
                if (flag == false ) {//到达路径
                    break;
                }
                lujing = strtok(NULL, fenge);//继续分隔下一个
                if(lujing)
                    n1=lujing;
            }
            currentPosition = t;//找到路径
            mkdir(n1);//新建文件
        }
    }
    void mkfile(char *name){
        if(name[0]!='/'){
            TreeNode* temp;
            TreeNode* t=currentPosition;
            for (temp = t->head; temp != NULL; temp = temp->next) {
                if (strcmp(temp->fileName, name) == 0 ) {
                    cout <<"文件或目录已存在"<< endl;
                    return;
                }
            }
            temp = (TreeNode*)malloc(sizeof(struct TreeNode));
            temp->parent = t;
            temp->head = NULL;
            temp->flag_file = true;
            strcpy(temp->fileName, name);
            temp->next = t->head;
            t->head = temp;
        }
        else{
            TreeNode* p;
            TreeNode* t = root;
            const char *fenge = "/";
            char *lujing;
            char * str=name;
            char * n1;
            lujing = strtok(str, fenge);//分割出每个层次的文件名称
            bool flag;
            while (lujing){//当还存在文件名时，既路径未结束
                flag = false;
                p=t->head;
                while(p!=NULL){
                    if (strcmp(p->fileName, lujing) == 0&&p->flag_file == false) {//查找目录
                        t = p;
                        flag = true;
                        break;
                    }
                    p=p->next;
                }
                if (flag == false ) {
                    break;
                }
                lujing = strtok(NULL, fenge);//继续分隔下一个
                if(lujing)
                    n1=lujing;
            }
            currentPosition = t;//找到路径
            mkfile(n1);//新建目录
        }

    }
    void dir(){
        TreeNode* t = currentPosition;
        TreeNode* p=t->head;
        while(p!=NULL){//遍历输出子节点
            if(p->flag_file)
                cout<<p->fileName<<".f"<<endl;
            else
                cout<<p->fileName<<".d"<<endl;
            p=p->next;
        }
    }
    void cd_out(TreeNode* p){
        if (p== root) {//如果是根则结束
            cout<<"/";
            return;
        }
        else{
            cd_out( p->parent);//先输出父节点再输出子节点
            cout<<p->fileName<<"/";
        }
    }

    void cd(){//输出当前路径
        TreeNode* p = currentPosition;
        cd_out(p);
    }

    void cd_pre(){
        if (currentPosition == root) {
            cout<<"已经到达根节点"<<endl;
            return;
        }
        currentPosition = currentPosition->parent;//直接赋值即可
    }
    void cd_str1(char *str){
        TreeNode* p;
        if (str[0] == '/') {//绝对路径
            TreeNode* t = root;
            const char *fenge = "/";
            char *lujing;
            lujing = strtok(str, fenge);//分割出每个层次的文件名称
            bool flag;
            while (lujing){//当还存在文件名时，既路径未结束
                flag = false;
                p=t->head;
                while(p!=NULL){
                    if (strcmp(p->fileName, lujing) == 0&&p->flag_file == false) {//查找目录
                        t = p;
                        flag = true;
                        break;
                    }
                    p=p->next;
                }
                if (flag == false ) {//没有找到则结束
                    cout<<"路径错误"<<endl;
                    return;
                }
                lujing = strtok(NULL, fenge);//继续分隔下一个
            }
            currentPosition = t;
        }
        else {//相对路径 与上面同理
            const char *fenge = "/";
            char *lujing;
            TreeNode* t = currentPosition;
            lujing = strtok(str, fenge);
            bool flag;
            while (lujing){
                flag = false;
                p=t->head;
                while (p!=NULL){
                    if (strcmp(p->fileName, lujing) == 0&&p->flag_file == false) {
                        t = p;
                        flag = true;
                        break;
                    }
                    p=p->next;
                }
                if (flag == false) {
                    cout<<"路径错误"<<endl;
                    return;
                }
                lujing = strtok(NULL, fenge);
            }
            currentPosition = t;
        }
    }

    void delete1( TreeNode* t){//删除
        TreeNode* p;
        if (t->flag_file) {//文件
            p = t->parent->head;
            if (p == t) {//删除头节点
                t->parent->head = p->next;
                free(t);
                return;
            }
            p=t->head;
            while (p!=NULL){//删除非头节点
                if(p->next==t){
                    p->next=t->next;
                    free(t);
                    return;
                }
                p=p->next;
            }
        }
        else {
            if (t->head == NULL) {//空目录
                if (t->parent->head == t) {//删除头节点
                    t->parent->head = t->next;
                }
                else{//删除非头节点
                    p=t->parent->head;
                    while (p!=NULL){
                        if (p->next == t) {
                            p->next = t->next;
                            break;
                        }
                        p=p->next;
                    }
                }
                free(t);
            }
            else {
                while (t->head != NULL) {//非空目录
                    p=t->head;
                    while (p!=NULL){//从每层的最后一个节点开始删 删完子节点后删除父节点
                        if (p->next == NULL) {
                            delete1( p);
                            break;
                        }
                        p=p->next;
                    }
                }
                delete1(t);//父节点的删除
            }
        }
    }

    void Delete(char *str){//删除函数
        TreeNode* t;
        bool flag=false;
        t=currentPosition->head;
        while (t!=NULL){//查找
            if (strcmp(t->fileName, str) == 0) {
                flag = true;
                break;
            }
            t=t->next;
        }
        if (flag == false) {
            cout<<"文件或目录不存在"<<endl;
            return;
        }
        delete1( t);
    }

    void save(){//保存
        FILE* file = fopen("a.txt", "w");
        if (file == NULL) {
            cout<<"文件打开失败"<<endl;
            return;
        }
        save1(this->root, 0 , file);
        fclose(file);
    }
    void save1(TreeNode* D, int chengchi, FILE *file){//保存函数
        TreeNode* p;
        if (D!=NULL) {
            for (int i = 0; i < chengchi; i++)
                fprintf(file , "\t");
            if (D->flag_file) {
                fprintf(file, "%s .f\n", D->fileName);
            }
            else {
                fprintf(file, "%s .d\n", D->fileName);
            }
            if (!D->flag_file){//如果为目录，则目录的孩子也要保存，层次加1
                p=D->head;
                while (p!=NULL){
                    save1(p, chengchi + 1 , file);
                    p=p->next;
                }
            }
        }
    }
    void load(){//读取
        FILE *file = fopen("a.txt", "r");
        if (file == NULL) {
            cout<<"文件打开失败"<<endl;
            return;
        }
        load1(currentPosition,"/" , 0, file);
        fclose(file);
        cd_str1("/");
    }
    void load1(TreeNode* D ,char *preDir, int prechengchi, FILE *file){//每次读取一行
        char line[10],type[3],name[10];
        memset(line, 0, sizeof(line));
        memset(type, 0, sizeof(type));
        memset(name, 0, sizeof(name));
        fgets(line, sizeof(line), file);
        if (strlen(line) == 0) return;//读取结束
        strncpy(type, line + strlen(line) - 3, 2);
        int i;
        int chengchi = 0;
        for (i = 0; line[i] == '\t'; i++) {//判断层次
            chengchi++;
        }
        if (i == 0) load1( D , "/", 0 , file);
        else
        {
            strncpy(name, line + chengchi, strlen(line) - 4 - chengchi);
            if (chengchi > prechengchi) {//如果比前一个层次大，说明是它的子节点 进入前一个目录以新建文件或目录
                cd_str1(preDir);
            }
            else if (chengchi < prechengchi)//如果比前一个层次小，则需要进入较小的层次 进入父节点
                for (int j = chengchi; j < prechengchi; j++) {
                    cd_pre();
                }
            if (strcmp(type, ".d") == 0){
                mkdir(name);
            }
            else {
                mkfile(name);
            }
            load1(currentPosition,name, chengchi, file);//读取下一行
        }
    }
    ~CatalogTree() {//析构
        delete1( root);
    };
};







