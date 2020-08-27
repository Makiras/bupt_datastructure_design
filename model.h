#ifndef _MODEL_H_
#define _MODEL_H_

#include <bits/stdc++.h>

/*
    High:   0.9, type = 3
    Mid:    0.5, type = 2
    Low:    0.2, type = 1
*/

struct City
{
    std::string c_name;
    int risk_type;
    int c_id;
};

struct Transportation
{
    std::string t_name;
    int t_type;
    int t_id;
    int t_st_city, t_ed_city;
    int t_st_time, t_ed_time;
    City *city_origin;
};

struct Path
{
    int pt_start;
    int pt_end;
    int pt_stages;
    int *pt;

    void print();
    ~Path();
};

struct Person
{
    std::string p_name;
    int p_start, p_end;
    int p_start_time;
    double p_risk;
    int p_stage;
    Path *path;

    void init_trace();
    void update_state();
    void change_target();
    ~Person();
};

struct Maps
{
    int n_city;
    int n_trans;
    std::vector<Transportation> *transmap;
    Transportation *trans_list;
    City *city_list;
    ~Maps();
};

#endif