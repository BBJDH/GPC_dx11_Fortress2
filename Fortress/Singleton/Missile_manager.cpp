#include "stdafx.h"
#include "Missile_manager.h"

Missile_manager::Missile_manager()
{

}

Missile_manager::~Missile_manager()
{
    clear();
}

void Missile_manager::create_missile( Tank const& tank)
{
    int const width = 20;
    int const height = 20;

    float angle;
    if (tank.get_side() == Tank::Side::Right)
    {
        angle = -tank.getimage_angle() / Radian
            + tank.getangle_min() + tank.getangle();
    }
    else
    {
        angle = (-tank.getimage_angle() / Radian + 180.0f)
            - (tank.getangle_min() + tank.getangle());
    }
    float const power = static_cast<float const>(tank.getpower());
    //60�й����� ����
    double cosval = cos(angle * Radian);
    double sinval = sin(angle * Radian);
    int min_x = static_cast<int>(width * cosval);
    int min_y = static_cast<int>(height * sinval);

    _float2 const position = { tank.getpos().x + min_x,tank.getpos().y - min_y };

    //����, �Ŀ�, �ִϸ��̼�, 
    switch (tank.get_tank_type())
    {
    case Tank::Tank_Type::Canon:
    {
        switch (tank.get_missile_type())
        {
        case Tank::Missile_Type::Normal:
        {
            missiles.push_back(new Missile("Canon/normal", position, width, height, { 78,65 }, 140, Effect::Type::Normal_Big));

            missiles.back()->ballistics_initialize(
                angle ,
                power * FIRE_MUL);
            missiles.back()->setmyturn(true);
            break;
        }
        case Tank::Missile_Type::Special:
        {
            missiles.push_back(new Missile("Canon/special", position, width, height, { 35,30 }, 420, Effect::Type::Normal_Small));

            missiles.back()->ballistics_initialize(
                angle ,
                power * FIRE_MUL);
            missiles.back()->setmyturn(true);
            break;
        }
        }
        return;
    }
    case Tank::Tank_Type::Super:
    {
        switch (tank.get_missile_type())
        {
        case Tank::Missile_Type::Normal:
        {
            for (int i=0; i<3; i++)
            {
                missiles.push_back(new Multi_Hit_Missile("Super/normal", position, width, height, {45,40}, 200, Effect::Type::Super_Normal));
                missiles.back()->ballistics_initialize(
                    angle-static_cast<float>(i),
                    (power + static_cast<float>(i*3)) * FIRE_MUL);
                missiles.back()->setmyturn(true);
            }
            break;
        }
        case Tank::Missile_Type::Special:
        {
            for (int i = 0; i < 3; i++)
            {
                for (int j = 0; j < 3; j++)
                {
                    missiles.push_back(new Guide_Missile("Super/special",position, width, height, 200, 1500, Effect::Type::Super_Special));
                    missiles.back()->ballistics_initialize(
                        angle - static_cast<float>(i*2 ),
                        (power + static_cast<float>(j*2 )) * FIRE_MUL);
                    missiles.back()->setmyturn(true);
                }
            }

            break;
        }
        }
        return;
    }
    case Tank::Tank_Type::Ion_Attacker:
    {
        switch (tank.get_missile_type())
        {
        case Tank::Missile_Type::Normal:
        {
            missiles.push_back(new Missile("Ion_Attacker/normal", position, width, height, {48,40},170, Effect::Type::Ion_Normal,Missile::Angle_Type::Angle));
            missiles.back()->ballistics_initialize(
                angle,
                power * FIRE_MUL);
            missiles.back()->setmyturn(true);
            break;
        }
        case Tank::Missile_Type::Special:
        {
            //missiles.push_back(new Missile("Ion_Attacker/special", position, width, height, { 66,50 }, 280, Effect::Type::Ion_Normal, Missile::Angle_Type::Angle));
            missiles.push_back(new Satellite_Missile("Ion_Attacker/special", position, width, height, { 66,50 }, 280, Effect::Type::Ion_Normal));
            missiles.back()->ballistics_initialize(
                angle,
                power * FIRE_MUL);
            missiles.back()->setmyturn(true);
            break;
        }
        }
        return;
    }
    }

}

void Missile_manager::create_missiles(Tank & tank)
{//��ġ, ����, �Ŀ�, ������

    int const power = tank.getpower();
    tank.set_power_record(power);
    create_missile(tank);

}

void Missile_manager::del_missile(Missile const * missile)
{
    delete missile;
    missile = nullptr;
}

void Missile_manager::clear()
{
    if (!missiles.empty())
    {   
        for (int i = 0; i < missiles.size(); i++)
        {
            if (missiles[i] != nullptr)
            {
                del_missile(missiles[i]);
            }
        }
	    missiles.clear();
	    std::vector<Missile*>().swap(missiles);
    }

}
