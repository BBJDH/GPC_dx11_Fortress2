#pragma once



class Object
{
public:
	enum class Type {Tank,Missile,Item};

protected:
	//가속도 계산시 사용
	_float2	   pos0;
	_float2	   velocity0;
	float		   moving_time;

	//평시 사용
	_float2	   pos;
	unsigned const width;
	unsigned const height;
	float const	   speed;
	float		   velocity;
	float          moving_angle;
	float		   image_angle;
	bool		   falling;
	bool		   myturn;
	bool		   out;


	void assign(Object const& other_obj);

public:
	Object();
	virtual ~Object() =default;
	Object(_float2 const & pos, unsigned const width, unsigned const height);
	Object(_float2 const & pos, unsigned const width, unsigned const height,float const speed);
	Object(Object  const & obj);
	Object & operator =(Object const& other_obj );
	_float2 const getpos() const;
	unsigned const getwidth() const;
	unsigned const getheight() const;
	float const gettime() const;
	float const getimage_angle()const;
	bool is_falling()const;
	bool is_myturn()const;
	bool is_out()const;
	void moveto(_float2 const & pos);
	virtual void ballistics_equation(float const moving_time, float const wind=0);
	void ballistics_initialize(float const moving_angle, float const velocity);
	void stop_move(float const thetha);
	void setmyturn(bool myturn);

};

