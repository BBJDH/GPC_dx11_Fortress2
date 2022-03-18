#pragma once
class Effect : public Object
{
public:
	enum class State
	{
		Playing, Delete
	};
	enum class Type
	{
		Normal_Big, Normal_Small, Super_Normal, Super_Special,
		Ion_Normal, Ion_Special, Ion, Satellite_Active
	};

protected:
	//사운드 여기에 추가
	Engine::Rendering::Animation::Component animation;
	std::string const name;
	State state;
	float playtime;

protected:
public:
	Effect(std::string const & location, _float2 const & position,
		_float2 const& size, float const duration);
	virtual ~Effect()=default;
	void check_state();
	void render();
	State get_state();
};