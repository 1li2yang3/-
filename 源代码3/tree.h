#include<bits/stdc++.h>

using namespace std;

struct TreeNode {
    bool flag_file;//�ж����ļ�����Ŀ¼
    char fileName[10];//����
    struct TreeNode *parent;//���ڵ�ָ��
    struct TreeNode *head;//�ӽڵ�ͷ
    struct TreeNode *next;//�ӽڵ�
};

class CatalogTree {
public:
    TreeNode* root;//��
    TreeNode* currentPosition;//��ǰλ��
    CatalogTree(){//���캯������ʼ����
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
        if(name[0]!='/'){//���·��
            TreeNode* p;
            TreeNode* t=currentPosition;
            for (p = t->head; p != NULL; p =p->next) {//�������жϸ����Ƿ����
                if (strcmp(p->fileName, name) == 0) {
                    cout <<"�ļ���Ŀ¼�Ѵ���"<< endl;
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
        else{//����·��
            TreeNode* p;
            TreeNode* t = root;
            const char *fenge = "/";
            char *lujing;
            char * str=name;
            char * n1;
            lujing = strtok(str, fenge);//�ָ��ÿ����ε��ļ�����
            bool flag;
            while (lujing){//���������ļ���ʱ����·��δ����
                flag = false;
                p=t->head;
                while(p!=NULL){
                    if (strcmp(p->fileName, lujing) == 0&&p->flag_file == false) {//����Ŀ¼
                        t = p;
                        flag = true;
                        break;
                    }
                    p=p->next;
                }
                if (flag == false ) {//����·��
                    break;
                }
                lujing = strtok(NULL, fenge);//�����ָ���һ��
                if(lujing)
                    n1=lujing;
            }
            currentPosition = t;//�ҵ�·��
            mkdir(n1);//�½��ļ�
        }
    }
    void mkfile(char *name){
        if(name[0]!='/'){
            TreeNode* temp;
            TreeNode* t=currentPosition;
            for (temp = t->head; temp != NULL; temp = temp->next) {
                if (strcmp(temp->fileName, name) == 0 ) {
                    cout <<"�ļ���Ŀ¼�Ѵ���"<< endl;
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
            lujing = strtok(str, fenge);//�ָ��ÿ����ε��ļ�����
            bool flag;
            while (lujing){//���������ļ���ʱ����·��δ����
                flag = false;
                p=t->head;
                while(p!=NULL){
                    if (strcmp(p->fileName, lujing) == 0&&p->flag_file == false) {//����Ŀ¼
                        t = p;
                        flag = true;
                        break;
                    }
                    p=p->next;
                }
                if (flag == false ) {
                    break;
                }
                lujing = strtok(NULL, fenge);//�����ָ���һ��
                if(lujing)
                    n1=lujing;
            }
            currentPosition = t;//�ҵ�·��
            mkfile(n1);//�½�Ŀ¼
        }

    }
    void dir(){
        TreeNode* t = currentPosition;
        TreeNode* p=t->head;
        while(p!=NULL){//��������ӽڵ�
            if(p->flag_file)
                cout<<p->fileName<<".f"<<endl;
            else
                cout<<p->fileName<<".d"<<endl;
            p=p->next;
        }
    }
    void cd_out(TreeNode* p){
        if (p== root) {//����Ǹ������
            cout<<"/";
            return;
        }
        else{
            cd_out( p->parent);//��������ڵ�������ӽڵ�
            cout<<p->fileName<<"/";
        }
    }

    void cd(){//�����ǰ·��
        TreeNode* p = currentPosition;
        cd_out(p);
    }

    void cd_pre(){
        if (currentPosition == root) {
            cout<<"�Ѿ�������ڵ�"<<endl;
            return;
        }
        currentPosition = currentPosition->parent;//ֱ�Ӹ�ֵ����
    }
    void cd_str1(char *str){
        TreeNode* p;
        if (str[0] == '/') {//����·��
            TreeNode* t = root;
            const char *fenge = "/";
            char *lujing;
            lujing = strtok(str, fenge);//�ָ��ÿ����ε��ļ�����
            bool flag;
            while (lujing){//���������ļ���ʱ����·��δ����
                flag = false;
                p=t->head;
                while(p!=NULL){
                    if (strcmp(p->fileName, lujing) == 0&&p->flag_file == false) {//����Ŀ¼
                        t = p;
                        flag = true;
                        break;
                    }
                    p=p->next;
                }
                if (flag == false ) {//û���ҵ������
                    cout<<"·������"<<endl;
                    return;
                }
                lujing = strtok(NULL, fenge);//�����ָ���һ��
            }
            currentPosition = t;
        }
        else {//���·�� ������ͬ��
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
                    cout<<"·������"<<endl;
                    return;
                }
                lujing = strtok(NULL, fenge);
            }
            currentPosition = t;
        }
    }

    void delete1( TreeNode* t){//ɾ��
        TreeNode* p;
        if (t->flag_file) {//�ļ�
            p = t->parent->head;
            if (p == t) {//ɾ��ͷ�ڵ�
                t->parent->head = p->next;
                free(t);
                return;
            }
            p=t->head;
            while (p!=NULL){//ɾ����ͷ�ڵ�
                if(p->next==t){
                    p->next=t->next;
                    free(t);
                    return;
                }
                p=p->next;
            }
        }
        else {
            if (t->head == NULL) {//��Ŀ¼
                if (t->parent->head == t) {//ɾ��ͷ�ڵ�
                    t->parent->head = t->next;
                }
                else{//ɾ����ͷ�ڵ�
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
                while (t->head != NULL) {//�ǿ�Ŀ¼
                    p=t->head;
                    while (p!=NULL){//��ÿ������һ���ڵ㿪ʼɾ ɾ���ӽڵ��ɾ�����ڵ�
                        if (p->next == NULL) {
                            delete1( p);
                            break;
                        }
                        p=p->next;
                    }
                }
                delete1(t);//���ڵ��ɾ��
            }
        }
    }

    void Delete(char *str){//ɾ������
        TreeNode* t;
        bool flag=false;
        t=currentPosition->head;
        while (t!=NULL){//����
            if (strcmp(t->fileName, str) == 0) {
                flag = true;
                break;
            }
            t=t->next;
        }
        if (flag == false) {
            cout<<"�ļ���Ŀ¼������"<<endl;
            return;
        }
        delete1( t);
    }

    void save(){//����
        FILE* file = fopen("a.txt", "w");
        if (file == NULL) {
            cout<<"�ļ���ʧ��"<<endl;
            return;
        }
        save1(this->root, 0 , file);
        fclose(file);
    }
    void save1(TreeNode* D, int chengchi, FILE *file){//���溯��
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
            if (!D->flag_file){//���ΪĿ¼����Ŀ¼�ĺ���ҲҪ���棬��μ�1
                p=D->head;
                while (p!=NULL){
                    save1(p, chengchi + 1 , file);
                    p=p->next;
                }
            }
        }
    }
    void load(){//��ȡ
        FILE *file = fopen("a.txt", "r");
        if (file == NULL) {
            cout<<"�ļ���ʧ��"<<endl;
            return;
        }
        load1(currentPosition,"/" , 0, file);
        fclose(file);
        cd_str1("/");
    }
    void load1(TreeNode* D ,char *preDir, int prechengchi, FILE *file){//ÿ�ζ�ȡһ��
        char line[10],type[3],name[10];
        memset(line, 0, sizeof(line));
        memset(type, 0, sizeof(type));
        memset(name, 0, sizeof(name));
        fgets(line, sizeof(line), file);
        if (strlen(line) == 0) return;//��ȡ����
        strncpy(type, line + strlen(line) - 3, 2);
        int i;
        int chengchi = 0;
        for (i = 0; line[i] == '\t'; i++) {//�жϲ��
            chengchi++;
        }
        if (i == 0) load1( D , "/", 0 , file);
        else
        {
            strncpy(name, line + chengchi, strlen(line) - 4 - chengchi);
            if (chengchi > prechengchi) {//�����ǰһ����δ�˵���������ӽڵ� ����ǰһ��Ŀ¼���½��ļ���Ŀ¼
                cd_str1(preDir);
            }
            else if (chengchi < prechengchi)//�����ǰһ�����С������Ҫ�����С�Ĳ�� ���븸�ڵ�
                for (int j = chengchi; j < prechengchi; j++) {
                    cd_pre();
                }
            if (strcmp(type, ".d") == 0){
                mkdir(name);
            }
            else {
                mkfile(name);
            }
            load1(currentPosition,name, chengchi, file);//��ȡ��һ��
        }
    }
    ~CatalogTree() {//����
        delete1( root);
    };
};







