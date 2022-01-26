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



	
}

void Animation::render_object(Object const& obj, Obj_Type const type)
{
    Engine::Rendering::Animation::Component * p_anime = nullptr;
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

void Animation::render_tanks(std::vector<Tank> & tank)
{
    if (!tank.empty())
    {
        for (size_t i = 0; i < tank.size(); i++)
        {
            tank[i].ani_render(Engine::Time::Get::Delta());
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
