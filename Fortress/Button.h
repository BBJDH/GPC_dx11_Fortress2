#pragma once
template<typename T>
class Button
{
public:
	enum class State
	{
		Activated, Collide, Clicked_Up, Toggled
	};
	Quadrangle collide_box;
	//Engine::Rendering::Image::UI deactivated_image;
	//Engine::Rendering::Image::UI activated_image;
	//Engine::Rendering::Image::UI collide_image;
	Engine::Rendering::Image::UI image;
	std::string name;

	
private:
	State state;
	std::function<T(void)> click_function; //클릭시 동작할 함수포인터
	std::function<bool(void)> function_button_on;	//버튼을 활성화할 함수포인터
	std::function<bool(void)> function_button_toggle;	//버튼을 활성화할 함수포인터
	bool on;

private:
	void set_button_image();
	bool activated();

public:
	Button();
	Button(std::function<T(void)> const & function, std::string const& name);

	void init_image_size(float const button_w, float const button_h);
	void init_image_location(float const button_x, float const button_y);
	void check_state();
	//비활성화 상태라면 어떤 동작도 하지않음,
	//토글상태인지 아닌지는 활성화(activated )상태에서 나누어서 출력

	bool clicked();
	bool get_on();
	T execute() const;
	void set_on(bool value);
	void bind_click_func(std::function<T(void)> const & function);
	void bind_activated_func(std::function<bool(void)> const & function);
	void bind_toggled_func(std::function<bool(void)> const & function);
};

