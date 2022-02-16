#pragma once



class Object
{
public:
	enum class Type {Tank,Missile,Item};

protected:
	//���ӵ� ���� ���
	_float2	   pos0;
	_float2	   velocity0;
	float		   moving_time;

	//��� ���
	_float2	   pos;
	unsigned const width;
	unsigned const height;
	float		   velocity;
	float          moving_angle;
	float		   image_angle;
	bool		   falling;
	bool		   myturn;
	bool		   out;




	//for test
	_float2	   support_point;


	void assign(Object const& other_obj);

public:
	Object();
	Object(_float2 const & pos, unsigned const width, unsigned const height);
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
	void ballistics_equation(float const moving_time);
	void ballistics_initialize(float const moving_angle, float const velocity);
	void stop_move(float const thetha);
	void setmyturn(bool myturn);


	//for test
	_float2 const getsup_pos() const;
	void setsup_pos(_float2 const& pos);

};

