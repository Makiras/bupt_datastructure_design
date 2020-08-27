#include "interface.h"

Maps *maps;
std::map<std::string, Person *> trace_list;

int init()
{

    std::ifstream in_map(MAP_FILE, std::ios::in);
    // read map file and alloc memory
    maps = new Maps;
    in_map >> maps->n_city >> maps->n_trans;
    maps->transmap = new std::vector<Transportation>[maps->n_city];
    maps->trans_list = new Transportation[maps->n_trans];
    maps->city_list = new City[maps->n_city];

    // read city info
    for (int i = 0; i < maps->n_city; i++)
        in_map >> maps->city_list[i].c_name >> maps->city_list[i].risk_type >> maps->city_list[i].c_id;

    // read trans info
    for (int i = 0; i < maps->n_trans; i++)
    {
        in_map >> maps->trans_list[i].t_name >> maps->trans_list[i].t_type >> maps->trans_list[i].t_id >>
            maps->trans_list[i].t_st_city >> maps->trans_list[i].t_ed_city >>
            maps->trans_list[i].t_st_time >> maps->trans_list[i].t_ed_time;
        // use Adjacency list for Map
        maps->trans_list[i].city_origin = &(maps->city_list[maps->trans_list[i].t_st_city]);
        maps->transmap[maps->trans_list[i].t_st_city].push_back(maps->trans_list[i]);
    }
    puts("INIT FINISED");
    return 0;
}

void destory()
{
    // free memory
    delete maps;
}

void new_person(std::string name, int startId, int endId, int startTime, int limitTime, char *&resStr)
{
    // view for backend
    std::cout << name << ' ' << startId << ' ' << endId << ' ' << startTime << ' ' << limitTime << ' ' << std::endl;
    Person *np = new Person;
    np->p_name = name;
    np->p_start = startId;
    np->p_end = endId;
    np->p_start_time = startTime % 24;

    // If this person has been submit, free the older one prevent memory leak
    if (trace_list.count(name) != 0)
        delete trace_list[name];
    trace_list[name] = np;  // hold person object for maintace
    std::cout << "TAG 1" << std::endl;
    if (limitTime == 0)
        calculate_shortest(maps->transmap, np, maps->n_city);
    else
        calculate_time_limit_DP(maps->transmap, np, maps->n_city, limitTime);
    std::cout << "TAG 2" << std::endl;

    // #############
    // #Json Encode#
    // #############

    rapidjson::Document resultJson;
    rapidjson::Value pt(rapidjson::kArrayType), tp;
    rapidjson::Value str_value(rapidjson::kStringType);
    rapidjson::Document::AllocatorType &allocator = resultJson.GetAllocator();
    resultJson.SetObject();
    str_value.SetString(name.c_str(), name.size());
    std::cout << "TAG 3" << std::endl;
    resultJson.AddMember("p_name", str_value, allocator)
        .AddMember("p_start", startId, allocator)
        .AddMember("p_end", endId, allocator)
        .AddMember("p_start_time", startTime, allocator)
        .AddMember("p_risk", np->p_risk, allocator)
        .AddMember("pt_stages", np->path->pt_stages, allocator);
    std::cout << "TAG 4" << std::endl;
    int nowT = startTime;
    for (int i = 0; i < np->path->pt_stages; i++)
    {
        std::cout<<np->path->pt_stages<<"\n"<<np->path->pt<<std::endl;
        if (np->path->pt[i] == np->p_end)
        {
            tp.SetObject()
                .AddMember("at", np->p_end, allocator)
                .AddMember("from", nowT, allocator)
                .AddMember("to", nowT, allocator);
            pt.PushBack(tp, allocator);
            break;
        }
        tp.SetObject();
        tp.AddMember("at", np->path->pt[i], allocator)
            .AddMember("from", nowT, allocator);
        std::cout<<i<<std::endl;
        if (maps->trans_list[np->path->pt[i + 1] - 10000].t_st_time < nowT % 24)
            nowT = (nowT / 24 + 1) * 24 + maps->trans_list[np->path->pt[i + 1] - 10000].t_st_time;
        else
            nowT = nowT / 24 * 24 + maps->trans_list[np->path->pt[i + 1] - 10000].t_st_time;
        std::cout<<i<<std::endl;
        tp.AddMember("to", nowT, allocator);
        pt.PushBack(tp, allocator);
        tp.SetObject()
            .AddMember("at", np->path->pt[i + 1], allocator)
            .AddMember("from", nowT, allocator);
        nowT = nowT / 24 * 24 + maps->trans_list[np->path->pt[i + 1] - 10000].t_ed_time;
        tp.AddMember("to", nowT, allocator);
        pt.PushBack(tp, allocator);
        i++;
    }
    std::cout << name << ' ' << startId << ' ' << endId << ' ' << startTime << ' ' << limitTime << ' ' << std::endl;
    resultJson.AddMember("pt", pt, allocator);
    rapidjson::StringBuffer buffer;
    rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
    resultJson.Accept(writer);
    std::string jsonStr = buffer.GetString();

    // allocate heap for longer lifecycle

    resStr = new char[strlen(jsonStr.c_str())];
    std::cout << jsonStr << std::endl;
    strcpy(resStr, jsonStr.c_str());
    std::cout << "TAG 5" << std::endl;
    return;
}

void delete_person(std::string name)
{
    // If not exsit
    if (trace_list.count(name) == 0)
        return;
    // or free and erase
    delete trace_list[name];
    trace_list.erase(name);
}

void get_map(char *&resStr)
{

    // #############
    // #Json Encode#
    // #############

    rapidjson::Document resultJson;
    rapidjson::Value pt1(rapidjson::kArrayType), pt2;
    rapidjson::Value str_value(rapidjson::kStringType);
    rapidjson::Document::AllocatorType &allocator = resultJson.GetAllocator();
    resultJson.SetObject();

    resultJson.AddMember("city", maps->n_city, allocator);
    for (int i = 0; i < maps->n_city; i++)
    {
        pt2.SetArray();
        str_value.SetString(maps->city_list[i].c_name.c_str(), maps->city_list[i].c_name.size());
        pt2.PushBack(str_value, allocator)
            .PushBack(maps->city_list[i].risk_type, allocator)
            .PushBack(maps->city_list[i].c_id, allocator);
        pt1.PushBack(pt2, allocator);
    }
    resultJson.AddMember("citys", pt1, allocator).AddMember("tran", maps->n_trans, allocator);
    pt1.SetArray();
    for (int i = 0; i < maps->n_trans; i++)
    {
        pt2.SetArray();
        str_value.SetString(maps->trans_list[i].t_name.c_str(), maps->trans_list[i].t_name.size());
        pt2.PushBack(str_value, allocator)
            .PushBack(maps->trans_list[i].t_type, allocator)
            .PushBack(maps->trans_list[i].t_id, allocator)
            .PushBack(maps->trans_list[i].t_st_city, allocator)
            .PushBack(maps->trans_list[i].t_ed_city, allocator)
            .PushBack(maps->trans_list[i].t_st_time, allocator)
            .PushBack(maps->trans_list[i].t_ed_time, allocator);
        pt1.PushBack(pt2, allocator);
    }
    resultJson.AddMember("trans", pt1, allocator);
    rapidjson::StringBuffer buffer;
    rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
    resultJson.Accept(writer);
    std::string jsonStr = buffer.GetString();

    // allocate heap for longer lifecycle
    resStr = new char[strlen(jsonStr.c_str())];
    strcpy(resStr, jsonStr.c_str());
    return;
}