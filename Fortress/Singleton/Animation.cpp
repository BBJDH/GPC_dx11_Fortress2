#include "stdafx.h"
#include "Animation.h"

Animation::Animation()
{
    initialize();
}

void Animation::initialize()
{
	ani_missile.Name = "Animation/Bomb/bomb";
	ani_missile.Length = Vector<2>(Missile_SIZE, Missile_SIZE);
	ani_missile.Duration = 0.5f;
	ani_missile.Repeatable = true;

    ani_tank.Length = Vector<2>(Tank_SIZE, Tank_SIZE);
    set_tank_normal();


	
}

void Animation::render_object(Object const& obj, Obj_Type const type)
{
    Engine::Rendering::Animation::Component* p_anime = nullptr;
    switch (type)
    {
    case Obj_Type::Missile:
    {
        p_anime = &ani_missile;
        break;
    }

    default:
        return;
    }
    p_anime->Location = { obj.getpos().x-MAPSIZE_W/2,MAPSIZE_H/2-obj.getpos().y };
    p_anime->Angle = -obj.getimage_angle()/Radian;
    p_anime->Render();
}

void Animation::render_tank(Tank const& tank)
{
    if (tank.get_side() == Tank::Side::Left)
        ani_tank.Flipped = true;
    else
        ani_tank.Flipped = false;

    switch (tank.get_state())
    {
    case Tank::State::Nomal:
    {   
        set_tank_normal();
        break;
    }   
    case Tank::State::Steady:
    {   
        set_tank_steady();
        break;
    }   
    case Tank::State::Fire:
    {    
        set_tank_fire();
        break;
    }    
    case Tank::State::Move:
    {   
        set_tank_move();
        break;
    }   
    case Tank::State::Stop:
    {   
        set_tank_stop();
        break;
    }   
    case Tank::State::Fall:
    {  
        set_tank_fall();
        break;
    }  
    case Tank::State::Dead:
    {
        set_tank_dead();
        break;
    }
    default:
        break;
    }

    ani_tank.Location = { tank.getpos().x - MAPSIZE_W / 2,MAPSIZE_H / 2 - tank.getpos().y };
    ani_tank.Angle = -tank.getimage_angle() / Radian;
    ani_tank.Render();
}

void Animation::render_tanks(std::vector<Tank> const& tank)
{
    if (!tank.empty())
    {
        for (size_t i = 0; i < tank.size(); i++)
        {
            render_tank(tank[i]);
        }
    }
}

void Animation::render_missile(std::vector<Missile> const& missile)
{
    if (!missile.empty())
    {
        for (size_t i = 0; i < missile.size(); i++)
        {
            render_object(missile[i], Animation::Obj_Type::Missile);
        }
    }
}

void Animation::set_tank_normal()
{
    ani_tank.Name = "Animation/Canon/nomal";
    ani_tank.Duration = 2.0f;
    ani_missile.Repeatable = true;
}

void Animation::set_tank_steady()
{
    ani_tank.Name = "Animation/Canon/steady";
    ani_tank.Duration = 0.25f;
    ani_missile.Repeatable = true;
}

void Animation::set_tank_fire()
{
    ani_tank.Name = "Animation/Canon/fire";
    ani_tank.Duration = 0.25f;
    ani_missile.Repeatable = false;
}

void Animation::set_tank_move()
{
    ani_tank.Name = "Animation/Canon/move";
    ani_tank.Duration = 0.5f;
    ani_missile.Repeatable = true;
}

void Animation::set_tank_stop()
{
    set_tank_normal();
}

void Animation::set_tank_fall()
{
    set_tank_move();
}

void Animation::set_tank_dead()
{
    ani_tank.Name = "Animation/Canon/dead";
    ani_tank.Duration = 1.0f;
    ani_missile.Repeatable = true;
}
