#include "algorithm.h"

struct path_node
{
    long long lst;
    int now;
    int lst_trans_id;
    int now_time;
    double now_risk;
};

// higher risk, lower opt
bool operator<(const path_node &x, const path_node &y)
{
    return x.now_risk > y.now_risk;
}

// Just Minimal Risk, do not care about time.
void calculate_shortest(std::vector<Transportation> *transmap, Person *person, int n_city)
{
    // printf("CalSPFA %d", n_city);
    path_node *minst = new path_node[n_city];
    // record minimal trace
    std::priority_queue<path_node> spfa;
    minst[person->p_start] = (path_node){-1, person->p_start, -1, person->p_start_time, 0};
    for (int i = 0; i < n_city; i++)
        minst[i].now_risk = INT_MAX;
    minst[person->p_start].now_risk = 0;
    spfa.push(minst[person->p_start]);
    // initial start point, count time at 0:00, -1 means the first point
    int temp_time;
    double temp_risk;
    //  temp variables

    puts("[INFO]: Start Caculate Route");

    while (!spfa.empty())
    {
        // puts("[INFO]: Start SPFA Iter");
        path_node now_p = spfa.top();
        spfa.pop();
        if (now_p.now == person->p_end)
            continue;
        // took the minimal risk point
        for (auto i = transmap[now_p.now].begin(); i != transmap[now_p.now].end(); i++)
        {
            // std::cout << now_p.now << ' ' << i->t_st_time << std::endl;
            if (i->t_st_time < now_p.now_time % 24)
                temp_time = (now_p.now_time / 24 + 1) * 24 + i->t_ed_time; // stay for a day
            else
                temp_time = (now_p.now_time / 24) * 24 + i->t_ed_time; // start in the same day
            temp_risk = (temp_time - now_p.now_time) * risk_city[i->city_origin->risk_type] +
                        (i->t_ed_time - i->t_st_time) * risk_trans[i->t_type] +
                        now_p.now_risk; // cacl the risk
            if (temp_risk < minst[i->t_ed_city].now_risk ||
                (temp_risk == minst[i->t_ed_city].now_risk && temp_time < minst[i->t_ed_city].now_time))
            // lower risk or lower cost
            {
                minst[i->t_ed_city] = (path_node){now_p.now, i->t_ed_city, i->t_id, temp_time, temp_risk};
                spfa.push(minst[i->t_ed_city]);
            }
            else
                continue;
        }
    }
    Path *result = new Path;
    // If reachable
    if (minst[person->p_end].now_risk != INT_MAX)
    {
        result->pt_start = person->p_start;
        result->pt_end = person->p_end;
        std::stack<int> path_log;
        int now_ptr = result->pt_end;
        // From last to first, use stack for reversing
        while (now_ptr != result->pt_start)
        {
            path_log.push(minst[now_ptr].now);
            path_log.push(minst[now_ptr].lst_trans_id);
            now_ptr = minst[now_ptr].lst;
            // move to the front
        }
        now_ptr = 0;
        result->pt = new int[path_log.size() + 1];
        // alloc mem for Path record result
        result->pt_stages = path_log.size() + 1;
        (result->pt)[0] = result->pt_start;
        while (!path_log.empty())
        {
            (result->pt)[++now_ptr] = path_log.top();
            path_log.pop();
        }
        person->p_risk = minst[person->p_end].now_risk;
        person->p_stage = 0;
    }
    else
        result->pt_stages = 0;
        // If no route, stages needs to be 0, or it may be undefined number

    person->path = result;
    delete[] minst;
    return;
};

void calculate_time_limit_DP(const std::vector<Transportation> *transmap, Person *person,
                             int n_city, int time_limit)
{
    path_node(*minst)[2000] = new path_node[n_city][2000];
    time_limit += person->p_start_time;
    // record minimal trace
    std::priority_queue<path_node> spfa;
    minst[person->p_start][person->p_start_time] = (path_node){-1, person->p_start, -1, person->p_start_time, 0};
    for (int i = 0; i < n_city; i++)
        for (int j = 0; j < 2000; j++)
            minst[i][j].now_risk = INT_MAX;
    minst[person->p_start][person->p_start_time].now_risk = 0;
    spfa.push(minst[person->p_start][person->p_start_time]);
    // initial start point, count time at 0:00, -1 means the first point
    int temp_time;
    double temp_risk;
    //  temp variables
    while (!spfa.empty())
    {
        path_node now_p = spfa.top();
        spfa.pop();
        if (now_p.now == person->p_end || now_p.now_risk > minst[now_p.now][now_p.now_time].now_risk)
            continue;
        // took the minimal risk point
        for (auto i = transmap[now_p.now].begin(); i != transmap[now_p.now].end(); i++)
        {
            if (i->t_st_time < now_p.now_time % 24)
                temp_time = (now_p.now_time / 24 + 1) * 24 + i->t_ed_time; // stay for a day
            else
                temp_time = (now_p.now_time / 24) * 24 + i->t_ed_time; // start in the same day
            temp_risk = (temp_time - now_p.now_time) * risk_city[i->city_origin->risk_type] +
                        (i->t_ed_time - i->t_st_time) * risk_trans[i->t_type] +
                        now_p.now_risk; // cacl the risk
            if (temp_risk < minst[i->t_ed_city][temp_time].now_risk && temp_time <= time_limit)
            // lower risk or lower cost
            {
                minst[i->t_ed_city][temp_time] = (path_node){(now_p.now << 16) + now_p.now_time, i->t_ed_city, i->t_id, temp_time, temp_risk};
                spfa.push(minst[i->t_ed_city][temp_time]);
            }
            else
                continue;
        }
    }

    // Find the minimal path in time
    int reachable = -1;
    for (int i = person->p_start_time; i <= time_limit; i++)
    {
        // if not reachable for now and still not reachable
        if (reachable == -1 && minst[person->p_end][i].now_risk == INT_MAX)
            continue;
        // if it's reachable for now but has more risk
        if (reachable != -1 && minst[person->p_end][reachable].now_risk <= minst[person->p_end][i].now_risk)
            continue;
        reachable = i;
    }

    //trace the path
    Path *result = new Path;
    if (reachable != -1)
    {
        result->pt_start = person->p_start;
        result->pt_end = person->p_end;
        person->p_risk = minst[person->p_end][reachable].now_risk;
        std::stack<int> path_log;
        int now_ptr = result->pt_end, temp_ptr;
        while (now_ptr != result->pt_start)
        {
            path_log.push(minst[now_ptr][reachable].now);
            path_log.push(minst[now_ptr][reachable].lst_trans_id);
            // Use bit opreation for saving memory, detail in design_doc
            temp_ptr = minst[now_ptr][reachable].lst >> 16;
            reachable = minst[now_ptr][reachable].lst & 65535; // last point time
            now_ptr = temp_ptr;
        }
        now_ptr = 0;
        result->pt = new int[path_log.size() + 1];
        result->pt_stages = path_log.size() + 1;
        (result->pt)[0] = result->pt_start;
        while (!path_log.empty())
        {
            (result->pt)[++now_ptr] = path_log.top();
            path_log.pop();
        }
        person->p_stage = 0;
    }
    else
        result->pt_stages = 0;

    person->path = result;
    delete[] minst;
    return;
};