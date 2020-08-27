#include "algorithm.h"
#include "config.h"
#include "interface.h"
#include "model.h"
#include <bits/stdc++.h>
#include <windows.h>

int main()
{
    init();
    std::string p_name;
    int p_start;
    int p_end;
    int p_start_time;
    int p_time_limit = 18;

    std::cin >> p_name >> p_start >> p_end >> p_start_time;
    int t1 = GetTickCount();
    char *resStr;
    new_person(p_name,
               (p_start),
               (p_end),
               (p_start_time),
               (p_time_limit),
               resStr);
    std::cout << GetTickCount() - t1 << std::endl;
    std::cout << "resStr" << std::endl;
    std::cout << resStr << std::endl;
    std::cout << p_name << " " << p_start << " " << p_end << " " << p_start_time << std::endl;
    delete[] resStr;

    destory();
    return 0;
}
