#pragma once
class Canon_Special : public Missile
{

private:
private:
	void ani_set()override;	//�ٲ�³���

public:
	Canon_Special(_float2 const& pos, unsigned const width, unsigned const height);
	~Canon_Special()override;
	void ani_render(float const delta)override; //check_state();
};