/**********************************************************************

File : vec4f.cpp
Author: Adam Petty
Date : 1/4/2019

Description
This is the implementation file the vec4f class. Refer to vec4f.h
for the interface.

**********************************************************************/

#include <iostream>
#include <cmath>
#include "vec4f.h"


std::ostream & operator<<(std::ostream & cout, const vec4f & v)
{
	cout << '<' << v.get_x() << ", "
	  	 << v.get_y() << ", " << v.get_z() << ", "
		 << v.get_w() << '>';
	return cout;
}


std::istream & operator>>(std::istream & cin, vec4f & v)
{
	double x, y, z, w;
	std::cin >> x >> y >> z >> w;
	v.set_x(x);
	v.set_y(y);
    v.set_z(z);
    v.set_w(w);
    return cin;
}


bool vec4f::operator==(const vec4f & v) const
{
	if (x_ == v.get_x() && y_ == v.get_y() && z_ == v.get_z()
		&& w_ == v.get_w())
	{
		return true;
	}
	else return false;
}


bool vec4f::operator!=(const vec4f & v) const
{
	if ((*this) == v)
	{
		return false;
	}
	else return true;
}


double vec4f::operator[](int i) const
{
	switch(i)
	{
		case 0:
		{
			return x_;
		}
		case 1:
		{
			return y_;
		}
		case 2:
		{
			return z_;
		}
		case 3:
		{
			return w_;
		}
		default:
		{
			break;
		}
	}
}


double & vec4f::operator[](int i)
{
	switch(i)
	{
		case 0:
		{
			return x_;
		}
		case 1:
		{
			return y_;
		}
		case 2:
		{
			return z_;
		}
		case 3:
		{
			return w_;
		}
		default:
		{
			break;
		}
	}
}


vec4f vec4f::operator+() const
{
	return (*this);
}


vec4f vec4f::operator-() const
{
	vec4f v;
	v.set_x(get_x() * -1);
	v.set_y(get_y() * -1);
	v.set_z(get_z() * -1);
	v.set_w(get_w() * -1);

	return v;
}


vec4f & vec4f::operator+=(const vec4f & v)
{
	set_x(get_x() + v.get_x());
	set_y(get_y() + v.get_y());
	set_z(get_z() + v.get_z());
	set_w(get_w() + v.get_w());
	return (*this);
}


vec4f vec4f::operator+(const vec4f & v) const
{
	return (vec4f(*this) += v);
}


vec4f & vec4f::operator-=(const vec4f & v)
{
	set_x(get_x() - v.get_x());
	set_y(get_y() - v.get_y());
	set_z(get_z() - v.get_z());
	set_w(get_w() - v.get_w());
	return (*this);
}


vec4f vec4f::operator-(const vec4f & v) const
{
	return (vec4f(*this) -= v);
}


vec4f & vec4f::operator*=(double c)
{
	x_ *= c;
	y_ *= c;
	z_ *= c;
	w_ *= c;

	return (*this);
}


vec4f vec4f::operator*(double c) const
{
	return (vec4f(*this) *= c);
}


vec4f & vec4f::operator/=(double c) 
{
	x_ /= c;
	y_ /= c;
    z_ /= c;
    w_ /= c;
	return (*this);
}


vec4f vec4f::operator/(double c) const
{
	return (vec4f(*this) /= c);
}


vec4f operator*(double c, const vec4f & v)
{
	return v * c;
}


double len(const vec4f & u)
{
	double len;
	double x, y, z;
	x = (u.get_x() * u.get_x());
	y = (u.get_y() * u.get_y());
    z = (u.get_z() * u.get_z());
	len =  sqrt (x + y + z);
	return len;
}


double dotprod(const vec4f & u, const vec4f & v)
{
	double product = 0;
	product = (u.get_x() * v.get_x()) + (u.get_y() * v.get_y());
	return product;
}


vec4f norm(const vec4f & u)
{
	vec4f v(u);
	double length = len(u);
	return (v / length);
}
