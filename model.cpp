#include "model.h"

void Person::init_trace()
{
    return;
}

void Person::update_state()
{
    return;
}

void Person::change_target()
{
    return;
}

void Path::print()
{
    printf("[Log]: Path from %d to %d have %d trans part \n", pt_start, pt_end, pt_stages / 2);
    for (int i = 0; i < pt_stages; i++)
        printf("%d ", pt[i]);
    puts("");
}

Path::~Path()
{
    delete[] pt;
}

Person::~Person()
{
    delete path;
}

Maps::~Maps()
{
    delete[] transmap;
    delete[] trans_list;
    delete[] city_list;
}