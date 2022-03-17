#pragma once
class Multi_Hit_Missile : public Missile
{
	//enum class Type 
	//{
	//	Circle, Ellipse
	//};
private:
	void check_state()override;
	void reduce();
public:
	Multi_Hit_Missile(std::string const & name, _float2 const& pos, unsigned const width, unsigned const height,
		_float2 const & missile_range, int const damage, Effect::Type const effect_type );
	~Multi_Hit_Missile()override;

};