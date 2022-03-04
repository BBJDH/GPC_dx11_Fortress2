#pragma once
class Canon_Normal : public Missile
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
	Canon_Normal(_float2 const& pos, unsigned const width, unsigned const height);

	~Canon_Normal()override;
	//void ani_render(float const delta)override;
};