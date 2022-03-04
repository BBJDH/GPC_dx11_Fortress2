#pragma once
class Canon_Special : public Missile
{

private:
private:
	//void check_state();  // ani_set_throw(),ani_set_boom() 사용
	void ani_set()override;	//바뀌는내용
	//void ani_set_boom(); //바뀌는내용

public:
	Canon_Special(_float2 const& pos, unsigned const width, unsigned const height);
	~Canon_Special()override;
	void ani_render(float const delta)override; //check_state();
};