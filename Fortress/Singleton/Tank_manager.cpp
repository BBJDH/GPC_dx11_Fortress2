#include "stdafx.h"
#include "Tank_manager.h"


Tank_manager::Tank_manager()
{
}

Tank_manager::~Tank_manager()
{
    clear();
}

void Tank_manager::create_tank(_float2 const & position, std::string const& player_name, Tank::Tank_Type const tank_name, Color const color)
{
    //위치, 탱크 이름, 플레이어 이름, 색상
    int  tank_size = 50;

    switch (tank_name)
    {
    case Tank::Tank_Type::Canon:
    {
        tanks.push_back
        (
            new (std::nothrow) Canon
            (
                position,
                50,
                50,
                player_name,
                "Canon",
                color
            )
        );
        break;
    }
    case Tank::Tank_Type::Super:
    {
        tanks.push_back
        (
            new (std::nothrow) Super
            (
                position,
                50,
                50,
                player_name,
                "Super",
                color
            )
        );
        break;
    }
    case Tank::Tank_Type::Ion_Attacker:
    {
        tanks.push_back
        (
            new (std::nothrow) Ion_Attacker
            (
                position,
                50,
                50,
                player_name,
                "Ion_Attacker",
                color
            )
        );
        break;
    }
    case Tank::Tank_Type::Multi_Missile:
    {
        tanks.push_back
        (
            new (std::nothrow) Multi_Missile
            (
                position,
                50,
                50,
                player_name,
                "Multi_Missile",
                color
            )
        );
        break;
    }
    case Tank::Tank_Type::Carrot:
    {
        tanks.push_back
        (
            new (std::nothrow) Carrot
            (
                position,
                50,
                50,
                player_name,
                "Carrot",
                color
            )
        );
        break;
    }
    case Tank::Tank_Type::Missile_Tank:
    {
        tanks.push_back
        (
            new (std::nothrow) Missile_Tank
            (
                position,
                50,
                50,
                player_name,
                "Missile_Tank",
                color
            )
        );
        break;
    }
    case Tank::Tank_Type::Secwind:
    {
        tanks.push_back
        (
            new (std::nothrow) Secwind
            (
                position,
                50,
                50,
                player_name,
                "Secwind",
                color
            )
        );
        break;
    }
    case Tank::Tank_Type::Laser:
    {
        tanks.push_back
        (
            new (std::nothrow) Laser
            (
                position,
                50,
                50,
                player_name,
                "Laser",
                color
            )
        );
        break;
    }
    }
    //if(tanks.back() == nullptr)
    //    std::cout << "tank alloc fail!" << std::endl;


    tanks.back()->ballistics_initialize(0, 0);
}

void Tank_manager::create_tanks()
{
    //unsigned player = PLAYERS;
    unsigned player = static_cast<unsigned>(_Button->player_set.size());
    //Random r(10, MAPSIZE_W - 10, PLAYERS);
    int const rand_mul = MAPSIZE_W / player; //플레이어수만큼 구역을 나누고 좌우 10픽셀 만큼 좁힌다
    Random r(0, player - 1, player);
    for (unsigned i = 0; i < player; i++)
    {
        //float const loc_x = static_cast<float>(r.GetResult(i));
        float const loc_x = (static_cast<float>(r.GetResult(i) * rand_mul + (rand() % rand_mul) + 10));
        create_tank
        (
            { loc_x ,0},
            "player " + std::to_string(i + 1),
            std::get<1>(_Button->player_set[i]),
            std::get<2>(_Button->player_set[i])
        );
    }
}

void Tank_manager::del_tank(Tank const* tank)
{
    delete tank;
    tank = nullptr;
}

void Tank_manager::clear()
{
    if (!tanks.empty())
    {
        for (int i = 0; i < tanks.size(); i++)
        {
            if (tanks[i] != nullptr)
            {
                del_tank(tanks[i]);
            }
        }
        tanks.clear();
        std::vector<Tank*>().swap(tanks);
    }

}
