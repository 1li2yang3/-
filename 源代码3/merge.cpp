#include"tree.h"

int main() {
    CatalogTree a;
    char op[10];
    char n[10];
    while (true) {
        memset(op, 0, sizeof(op));
        memset(n, 0, sizeof(n));
        gets(op);
        if(strcmp(op,"dir")==0){
            a.dir();
        }
        else if(strcmp(op,"cd")==0){
            a.cd();
        }
        else if(strcmp(op,"cd..")==0){
            a.cd_pre();
        }
        else if(op[0]=='c'&&op[1]=='d'&& strlen(op)>3){
            strncpy(n,op+3, strlen(op)-3);
            a.cd_str1(n);//cd /a/b  ==  cd a   cd b
        }
        else if(strlen(op)>6&&op[0]=='m'&&op[2]=='d'){
            strncpy(n,op+6, strlen(op)-6);
            a.mkdir(n);
        }
        else if(strlen(op)>7&&op[0]=='m'&&op[2]=='f'){
            strncpy(n,op+7, strlen(op)-7);
            a.mkfile(n);
        }
        else if(strlen(op)>7&&op[0]=='d'&&op[1]=='e'){
            strncpy(n,op+7, strlen(op)-7);
            a.Delete(n);
        }
        else if(strcmp(op,"save")==0){
            a.save();
        }
        else if(strcmp(op,"load")==0){
            a.load();
        }
        else if(strcmp(op,"quit")==0){
            break;
        }
        else
            cout<<"没有该操作"<<endl;
    }
    return 0;

}