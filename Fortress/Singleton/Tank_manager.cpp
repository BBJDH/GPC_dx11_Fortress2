#include "stdafx.h"
#include "Tank_manager.h"

Tank_manager::Tank_manager()
{
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
        tanks.push_back
        (
            Tank
            (
                { loc_x, 0 },
                Tank_SIZE,
                Tank_SIZE,
                "player " + std::to_string(i + 1),
                std::get<2>(_Button->player_set[i])
            )
        );
        tanks.back().ballistics_initialize(0, 0);
    }
}

void Tank_manager::clear()
{
	tanks.clear();
	std::vector<Tank>().swap(tanks);
}
