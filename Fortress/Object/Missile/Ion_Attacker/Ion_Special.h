#pragma once
class Ion_Special : public Missile
{
	//enum class Type 
	//{
	//	Circle, Ellipse
	//};
private:
private:
	void ani_set()override;
	//void ani_set_boom();
public:
	Ion_Special(_float2 const& pos, unsigned const width, unsigned const height);

	~Ion_Special()override;
	//void ani_render(float const delta)override;
};