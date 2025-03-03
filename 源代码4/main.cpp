#include "graph.h"

#include<windows.h>
#pragma comment( lib,"winmm.lib" )
using namespace std;

int main(){
    string str_basic="C:\\Users\\32379\\Desktop\\input\\input";

    string output1="C:\\Users\\32379\\Desktop\\output\\output1.txt";
    string out_t1="C:\\Users\\32379\\Desktop\\output\\t1.txt";
    ofstream f_out1(output1,ios::out);
    ofstream f_t1(out_t1,ios::out);

    for(int i=1;i<=100;i++){//测试方案1并储存结果
        string str=str_basic+ to_string(i)+".txt";//测试100个样例
        graph g(str);

        LARGE_INTEGER t1, t2, tc;
        QueryPerformanceFrequency(&tc);
        QueryPerformanceCounter(&t1);//计算时间

        int r1=g.res1();

        QueryPerformanceCounter(&t2);
        double time_1=1000*(t2.QuadPart - t1.QuadPart)*1.0 / tc.QuadPart;//微秒会出现比较抽象的结果，不好画图，将单位转化为毫秒

        //printf("%f\n", (t2.QuadPart - t1.QuadPart)*1.0 / tc.QuadPart);
        //cout<<r1<<"\n";
        f_out1<<r1<<"\n";
        f_t1<<time_1<<"\n";
    }
    f_out1.close();

    string output2="C:\\Users\\32379\\Desktop\\output\\output2.txt";
    string out_t2="C:\\Users\\32379\\Desktop\\output\\t2.txt";
    ofstream f_out2(output2,ios::out);
    ofstream f_t2(out_t2,ios::out);

    for(int i=1;i<=100;i++){//测试方案2并储存结果
        string str=str_basic+ to_string(i)+".txt";
        graph g(str);

        LARGE_INTEGER t1, t2, tc;
        QueryPerformanceFrequency(&tc);
        QueryPerformanceCounter(&t1);

        int r2=g.res2();

        QueryPerformanceCounter(&t2);
        double time_2=1000*(t2.QuadPart - t1.QuadPart)*1.0 / tc.QuadPart;//微秒会出现比较抽象的结果，不好画图，将单位转化为毫秒

        //cout<<r2<<"\n";
        f_out2<<r2<<"\n";
        f_t2<<time_2<<"\n";
    }
    f_out2.close();



    return 0;

}
