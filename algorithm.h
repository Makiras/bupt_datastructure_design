#ifndef _ALGO_H_
#define _ALGO_H_

#include "config.h"
#include "model.h"
#include <bits/stdc++.h>

// CREATE NEW PATH[]
extern void calculate_shortest(std::vector<Transportation> *transmap, Person *person, int n_city);
extern void calculate_time_limit_DP(const std::vector<Transportation> *transmap, Person *person,
                                int n_city, int time_limit);

#endif