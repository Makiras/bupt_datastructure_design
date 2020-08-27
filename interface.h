#include "algorithm.h"
#include "config.h"
#include "model.h"
#include "rapidjson/document.h"
#include "rapidjson/stringbuffer.h"
#include "rapidjson/writer.h"
#include <bits/stdc++.h>

int init();
void destory();
void new_person(std::string name, int startId, int endId, int startTime, int limitTime, char *&resStr);
void delete_person(std::string name);
void get_map(char* &resStr);