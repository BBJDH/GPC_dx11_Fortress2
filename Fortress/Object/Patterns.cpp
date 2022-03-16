#include "stdafx.h"
#include "Patterns.h"

Patterns::Patterns(std::string const& name, _float2 const& pos) :Object{ pos ,100,100,1 },
name{ name }, recyclable{false}
{
	ani.Duration = 1.0f;
	ani.Length = Vector<2>(width, height);
}
bool Patterns::check_recyclable()
{
	return recyclable;
}
void Patterns::render()
{
	std::string location = "Animation/Patterns/" + name;
	ani.Name = location.c_str();
	ani.Location = { this->pos.x - MAPSIZE_W / 2,MAPSIZE_H / 2 - this->pos.y };
	ani.Repeatable = true;
	ani.Render();
}

void Patterns::recycle(std::string const& name, _float2 const& pos)
{
	this->name = name;
	this->pos = pos;
	this->out = false;
	recyclable = false;
}

void Patterns::set_recycle_able()
{
	recyclable = true;
}



Patterns::~Patterns()
{
}
