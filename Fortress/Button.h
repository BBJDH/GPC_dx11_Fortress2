#pragma once
template<typename T>
class Button
{
public:
	enum class State
	{
		Activated, Collide, Clicked_Up,
	};
	Quadrangle collide_box;
	Engine::Rendering::Image::UI deactivated_image;
	Engine::Rendering::Image::UI activated_image;
	Engine::Rendering::Image::UI collide_image;
	
private:
	State state;
	std::function<T(void)> click_function; //클릭시 동작할 함수포인터
	std::function<bool(void)> function_button_on;	//버튼을 활성화할 함수포인터
	

private:
	bool activated();

public:
	Button();
	Button(std::function<T(void)> const & function);
	//Button(std::string const& name, std::string const& clicked_name,
	//	float const location_x, float const location_y,
	//	float const length_x, float const length_y);
	void check_state();
	bool clicked();
	T execute() const;
	void bind_click_func(std::function<T(void)> const & function);
	void bind_activated_func(std::function<bool(void)> const & function);
};

