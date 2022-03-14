#pragma once
class Super_Special : public Guide_Missile
{
private:
	void ani_set() override;

public:
	Super_Special(_float2 const& pos, unsigned const width, unsigned const height);
	~Super_Special()override;
};