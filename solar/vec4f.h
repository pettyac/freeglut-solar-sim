/*****************************************************************************
File : vec4f.h
Author: Adam Petty
Date : 1/4/2019
Description
This is the header file of the vec4f class.

Each vec4f object models a 2-dimensional vector with double coordinates. The
methods and operators supported are described below. In the following, u, v,
and w are vec4f objects while c, d are doubles.

vec4f(x,y)     - Constructor. This sets the x and y values of u to values of
                 parameters x and y respectively. The default values are 0,0
                 respectively.

std::cout << u - Prints vector u. The format is "<x, y>" where x and y
                 are the x and y values of u.
std::cin >> u  - Input for u.

u.get_x()      - Returns the x value of vec4f oject u.
u.get_y()      - Returns the y value of vec4f oject u.
u.set_x(x0)    - Sets the x value of u to the value of x0.
u.set_y(y0)    - Sets the y value of u to the value of y0.
u[i]           - Returns the x value or a reference to the x value of u
                 if i is 0; otherwise the y value or reference to the y
				 value is returned.

u == v         - Returns true iff the respective x, y values of u and v are
                 the same.
u != v         - The boolean opposite of (u == v)
u = v          - Copies the x,y values of v to u.

+u             - Returns a copy of u.
u += v         - Increments the x and y values of u by the x and y values
                 of v respectively. A reference to u is returned so that
                 you can also execute (u += v) += w.
u + v          - Returns the vector sum of u and v.

-u             - Return the negative of u, i.e., the vec4f object returned
                 has x,y values which are the negative of the x,y values of
                 u.
u -= v         - Decrements the x and y values of u by the x and y values
                 of v. A reference to u is returned so that you can also
                 execute (u -= v) -= w).
u - v          - Returns the vector difference of u and v.

u *= c         - Multiplies the x,y values of u by double c and set the
                 x,y values to these new values (respectively). A
                 reference to u is returned so that you can also execute
                 (u *= c) *= d.

u * c          - Returns the vector scalar product of vector u by double
                 c, i.e., a vec4f object is returned where the x,y values
                 of this new vec4f object are the x,y values of u
                 multiplied by c.

c * u          - Similar to u * c.


u /= c         - Divides the x,y values of u by double c and set the x,y
                 values to these new values (respectively). A reference
                 to u is returned so that you can also execute
                 (u /= c) /= d.
u / c          - Returns the vector scalar product of vector u by the double 
                 (1/c).

len(u)         - Returns the length of vector u as a double. This is the
                 square root of x*x + y*y where x and y are the x,y values
                 in u. Note that this is a non-memnber function.

u.len()        - Same as len(u) except that this is a method.

dotprod(u, v)  - Returns the dot product of vectors u and v as a double.

norm(u)        - Return the normalized vector of u, i.e., this function
                 returns u / len(u), a vector of length 1 going in the
                 same direction as u.

******************************************************************************/
#ifndef VEC4F_H
#define VEC4F_H

#include <iostream>

class vec4f
{
public:
	vec4f()
		: x_(0), y_(0), z_(0), w_(0)
	{}

    vec4f(double x, double y, double z, double w = 1)
        : x_(x), y_(y), z_(z), w_(w)
    {}
	vec4f(const vec4f & v)
		: x_(v.x_), y_(v.y_), z_(v.z_), w_(v.w_)
	{}

    bool operator==(const vec4f &) const;
    bool operator!=(const vec4f &) const;
    
    double get_x() const { return x_; } 
    double get_y() const { return y_; }
    double get_z() const { return z_; }
    double get_w() const { return w_; }
    
	void set_x(double x) { x_ = x; }
    void set_y(double y) { y_ = y; }
	void set_z(double z) { z_ = z; }
	void set_w(double w) { w_ = w; }
    
    double operator[](int) const;
    double & operator[](int);
    
    vec4f operator+() const;
    vec4f & operator+=(const vec4f &);
    vec4f operator+(const vec4f &) const;
    
    vec4f operator-() const;
    vec4f & operator-=(const vec4f &);
    vec4f operator-(const vec4f &) const;
    
    vec4f & operator*=(double);
    vec4f operator*(double) const;
    
    vec4f & operator/=(double);
    vec4f operator/(double) const;

private:
    double x_, y_, z_, w_;
};
                 
vec4f operator*(double, const vec4f &);
double len(const vec4f &);
double dotprod(const vec4f &, const vec4f &);
vec4f norm(const vec4f &);

std::ostream & operator<<(std::ostream &, const vec4f &);
std::istream & operator>>(std::istream &, vec4f &);


#endif

