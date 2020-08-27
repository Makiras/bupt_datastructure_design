#include <bits/stdc++.h>

using namespace std;

int main()
{
    ofstream out_map("big.txt", ios::out);
    int n = 10000, p = 0, t = 0, c = 0, cntm = 10000;
    int temp, temped, str, edr;
    out_map << "10000 " << endl;

    for (int i = 0; i < 10000; i++)
        out_map << i << "城 " << rand() % 3 + 1 << ' ' << i << endl;

    // 一级城市200航班
    for (int i = 0; i < 100; i++)
    {
        temp = rand() % 100;
        str = rand() % 20;
        edr = str + rand() % 4 + 1;
        out_map << "P" << p++ << " 3 " << cntm++ << ' ' << i << ' ' << temp << ' ' << str << ' ' << edr << endl;
        out_map << "P" << p++ << " 3 " << cntm++ << ' ' << temp << ' ' << i << ' ' << str << ' ' << edr << endl;
    }
    // 一级城市500列车
    for (int i = 0; i < 500; i++)
    {
        temp = rand() % 100;
        do
        {
            temped = rand() % 100;
        } while (temped == temp);
        str = rand() % 18;
        edr = str + rand() % 4 + 3;
        out_map << "T" << t++ << " 2 " << cntm++ << ' ' << temp << ' ' << temped << ' ' << str << ' ' << edr << endl;
    }
    //一级城市1000汽车
    for (int i = 0; i < 100; i++)
    {
        temp = i;
        for (int j = 0; j < 10; j++)
        {
            do
            {
                temped = rand() % 100;
            } while (temped == temp);
            str = rand() % 18;
            edr = str + rand() % 4 + 3;
            out_map << "C" << c++ << " 1 " << cntm++ << ' ' << temp << ' ' << temped << ' ' << str << ' ' << edr << endl;
        }
    }

    //二级城市连接一级城市
    for (int i = 0; i < 100; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            temp = i;
            temped = 100 + i * 9 + j;
            str = rand() % 18;
            edr = str + rand() % 4 + 3;
            out_map << "C" << c++ << " 1 " << cntm++ << ' ' << temp << ' ' << temped << ' ' << str << ' ' << edr << endl;
            out_map << "C" << c++ << " 1 " << cntm++ << ' ' << temped << ' ' << temp << ' ' << str << ' ' << edr << endl;
        }
    }
    //二级城市连接完全图
    for (int i = 0; i < 100; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            temp = 100 + i * 9 + j;
            for (int k = j + 1; k < 9; k++)
            {
                temped = 100 + i * 9 + k;
                str = rand() % 18;
                edr = str + rand() % 4 + 3;
                out_map << "C" << c++ << " 1 " << cntm++ << ' ' << temp << ' ' << temped << ' ' << str << ' ' << edr << endl;
                out_map << "C" << c++ << " 1 " << cntm++ << ' ' << temped << ' ' << temp << ' ' << str << ' ' << edr << endl;
            }
        }
    }
    //二级城市航班100线
    for (int i = 0; i < 100; i++)
    {
        temp = i;
        do
        {
            temped = rand() % 100;
        } while (temped == temp);
        temped = 100 + temped * 9 + rand() % 9;
        temp = 100 + temp * 9 + rand() % 9;
        str = rand() % 20;
        edr = str + rand() % 4 + 1;
        out_map << "P" << p++ << " 3 " << cntm++ << ' ' << temp << ' ' << temped << ' ' << str << ' ' << edr << endl;
    }
    //二级城市列车4500线
    for (int i = 0; i < 4500; i++)
    {
        temp = rand() % 100;
        do
        {
            temped = rand() % 100;
        } while (temped == temp);
        temped = 100 + temped * 9 + rand() % 9;
        temp = 100 + temp * 9 + rand() % 9;
        str = rand() % 18;
        edr = str + rand() % 4 + 3;
        out_map << "T" << t++ << " 2 " << cntm++ << ' ' << temp << ' ' << temped << ' ' << str << ' ' << edr << endl;
    }
    //二级城市汽车9000线
    for (int i = 0; i < 9000; i++)
    {
        temp = rand() % 100;
        do
        {
            temped = rand() % 100;
        } while (temped == temp);
        temped = 100 + temped * 9 + rand() % 9;
        temp = 100 + temp * 9 + rand() % 9;
        str = rand() % 16;
        edr = str + rand() % 8 + 1;
        out_map << "C" << c++ << " 1 " << cntm++ << ' ' << temp << ' ' << temped << ' ' << str << ' ' << edr << endl;
    }

    //三级城市连接二级城市
    for (int i = 0; i < 900; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            temp = i + 100;
            temped = 1000 + i * 10 + j;
            str = rand() % 20;
            edr = str + rand() % 4 + 1;
            out_map << "C" << c++ << " 1 " << cntm++ << ' ' << temp << ' ' << temped << ' ' << str << ' ' << edr << endl;
            out_map << "C" << c++ << " 1 " << cntm++ << ' ' << temped << ' ' << temp << ' ' << str << ' ' << edr << endl;
        }
    }
    //三级城市连接完全图
    for (int i = 0; i < 900; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            temp = 1000 + i * 10 + j;
            for (int k = j + 1; k < 10; k++)
            {
                temped = 1000 + i * 10 + k;
                str = rand() % 20;
                edr = str + rand() % 4 + 1;
                out_map << "C" << c++ << " 1 " << cntm++ << ' ' << temp << ' ' << temped << ' ' << str << ' ' << edr << endl;
                out_map << "C" << c++ << " 1 " << cntm++ << ' ' << temped << ' ' << temp << ' ' << str << ' ' << edr << endl;
            }
        }
    }
    //三级城市列车9000线
    for (int i = 0; i < 9000; i++)
    {
        temp = rand() % 900;
        do
        {
            temped = rand() % 900;
        } while (temped == temp);
        temped = 1000 + temped * 10 + rand() % 10;
        temp = 1000 + temp * 10 + rand() % 10;
        str = rand() % 18;
        edr = str + rand() % 4 + 3;
        out_map << "T" << t++ << " 2 " << cntm++ << ' ' << temp << ' ' << temped << ' ' << str << ' ' << edr << endl;
    }

    //全域随机900000车次
    for (int i = 0; i < 900000; i++)
    {
        temp = rand() % 10000;
        do
        {
            temped = rand() % 10000;
        } while (temped == temp);
        str = rand() % 16;
        edr = str + rand() % 7 + 2;
        out_map << "C" << c++ << " 1 " << cntm++ << ' ' << temp << ' ' << temped << ' ' << str << ' ' << edr << endl;
    }

    return 0;
}