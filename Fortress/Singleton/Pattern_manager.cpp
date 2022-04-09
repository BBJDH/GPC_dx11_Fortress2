#include "stdafx.h"
#include "Pattern_manager.h"


Pattern_manager::Pattern_manager() 
{
    pattern_name = pattern_name_list[rand() % 2];
    int i = 0;
}

Pattern_manager::~Pattern_manager()
{
}

void Pattern_manager::assign_pattern(float const delta)
{
    interval += delta;
    if (interval > pattern_gen_time)
    {
        _float2 pattern_pos;
        Patterns* target = nullptr;
        rand_pos(pattern_pos);
        recycle_pattern(pattern_name, pattern_pos);
        interval = 0;

        //std::cout <<  "Patterns size : "<<patterns.size() << std::endl;

    }
}

void Pattern_manager::rand_pos(_float2& pos)
{
    float const out_value = 50.0f;
    switch (static_cast<Side>(rand() % 3))
    {
    case Side::Up:
    {
        pos = { static_cast<float>(rand() % MAPSIZE_W), -out_value };
        break;
    }
    case Side::Left:
    {
        pos = { -out_value, static_cast<float>(rand() % (MAPSIZE_H - 100)) };
        break;
    }
    case Side::Right:
    {
        pos = { MAPSIZE_W + out_value, static_cast<float>(rand() % (MAPSIZE_H - 100)) };
        break;
    }

    }
    int i = 0;

}



void Pattern_manager::recycle_pattern(std::string const& name, _float2 const& pos)
{
    Patterns* poolObj = nullptr;

    if (patterns.size() == 0)//최초 객체 생성
    {

        patterns.push_back(poolObj = new (std::nothrow) Patterns(name, pos));
        //if (poolObj == nullptr)
        //    std::cout << "pattern alloc fail!" << std::endl;
        poolObj->ballistics_initialize(0, 0);

        return ;
    }

    for (auto elem : patterns) //재사용 가능한 객체를 찾는다
    {
        if (elem->check_recyclable())
        {
            poolObj = elem;
            break;
        }
    }

    if (poolObj == nullptr) //객체가 모두 사용중일때
    {
        patterns.push_back(poolObj = new (std::nothrow) Patterns(name, pos));

        //if (poolObj == nullptr)
        //    std::cout << "pattern alloc fail!" << std::endl;
        poolObj->ballistics_initialize(0, 0);

        return ;
    }
    assert(poolObj != nullptr);
    poolObj->recycle(name, pos);     //객체 재사용
    poolObj->ballistics_initialize(0, 0);

    return ;
}

void Pattern_manager::ballistics(float const delta)
{
    if (!patterns.empty())
    {
        for (size_t i = 0; i < patterns.size(); i++)
        {
            if (!patterns[i]->check_recyclable())
            {
                patterns[i]->ballistics_equation(delta, _Turn->get_wind());
                //화면밖으로 나가면 제거
                if (patterns[i]->is_out())
                    patterns[i]->set_recycle_able();
            }
        }
    }
}
