#pragma once
class Ion_Normal : public Missile
{

private:
	void ani_set()override;	//�ٲ�³���

public:
	Ion_Normal(_float2 const& pos, unsigned const width, unsigned const height);
	~Ion_Normal()override;
	void ballistics_equation(float const delta, float const wind = 0)override;

};