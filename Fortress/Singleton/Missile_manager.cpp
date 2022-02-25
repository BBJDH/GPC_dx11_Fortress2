#include "stdafx.h"
#include "Missile_manager.h"

Missile_manager::Missile_manager()
{
}

void Missile_manager::clear()
{
	missiles.clear();
	std::vector<Missile>().swap(missiles);
}
