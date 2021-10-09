//File: main.cpp

#include <iostream>
#include <GL/freeglut.h>
#include <cmath>
#include <list>
#include "mygllib3d/gl3d.h"
#include "vec4f.h"
#include "Body.h"

GLboolean light_on;
GLfloat light_ambient[4];
GLfloat light_diffuse[4];
GLfloat light_specular[4];
GLfloat light_position[4];

const double G = 6.67408e-11;
const char NAME[10][32] = {"SUN",
						  "MERCURY", "VENUS", "EARTH", "MARS",
						  "JUPITER", "SATURN", "URANUS", "NEPTUNE", "PLUTO"};
const double MASS[] = {1.989E30, 0.330E24, 4.87E24, 5.97E24, 0.64E24,
						1898E24, 568E24, 86.8E24, 102E24, 0.0146E24};
const double PERIHELION[] = {0, 46.0E9, 107.5E9, 147.1E9, 206.6E9,
						740.5E9, 1352.6E9, 2741.3E9, 4444.5E9, 4436.8E9};
const double APHELION[] = {0, 69.8E9, 108.9E9, 152.1E9, 249.2E9,
						816.6E9, 1514.5E9, 3003.6E9, 4545.7E9, 7375.9E9};
const double DIAMETER[] = {0, 4879E9, 12104E9, 12756E9, 6792E9,
						142984E9, 120536E9, 51118E9, 49528E9, 2370E9};
const double SEMI_MAJOR_AXIS[] = {0, 57.9E9, 108.2E9, 149.6E9, 227.9E9,
                        778.6E9, 1433.5E9, 2872.5E9, 4495.1E9, 5906.4E9};
                     
int NO = 8;
Body * body;
double dt = 80000;
std::list<vec4f> trail[10];

void rotate(double & x, double & z, double t)
{
	//rotate (x, z) by angle t.
	return;
}

void init_planets();
double gravitational_pull(double M1, double M2, double r);
double distance(vec4f u, vec4f v);
double perihelion_speed(Body sun, Body planet, double axis_length);


void init()
{
    mygllib::View & view = *(mygllib::SingletonView::getInstance());
    
    //camera settings 
    view.eyex() = 3.0f;
    view.eyey() = 50.0f;
    view.eyez() = 3.0f;
    
    view.fovy() = 90.0f;
    view.aspect() = 1.0f;
    view.set_projection();
	view.lookat();
    
	
}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	glDisable(GL_LIGHTING);
	mygllib::draw_axes();
    //mygllib::draw_xz_plane();
	glEnable(GL_LIGHTING);
	glPushMatrix();
	{
		glScalef(1e-10, 1e-10, 1e-10);
        for (int i = 0; i < NO; ++i)
		{	
			glPushMatrix();
	   		{   
                //keeps the sun centered
                if (i > 0) glTranslatef(body[i].p.get_x(), body[i].p.get_y(), body[i].p.get_z());
				glColor3f(1, 1, 1);
				glutSolidSphere(body[i].radius, 25, 25);

                glBegin(GL_LINE_STRIP);
                glColor3f(1, 1, 1);
                for (std::list<vec4f>::iterator p = trail[i].begin();
                     p != trail[i].end(); ++p)
                {
                    float x = (*p)[0];
                    float y = (*p)[1];
                    float z = (*p)[2];
                    glVertex3f(x, y, z);
                }
                glEnd();
                
			}
			glPopMatrix();
		}
	}
	glPopMatrix();

	glutSwapBuffers();
}

void animate(int value)
{
    vec4f F[10]; //F[i] is the gravitational force (vector) acting on body[i]
    for (int i = 0; i < NO; ++i)
    {

        F[i] = norm(-body[i].p + body[0].p);
        F[i] *= gravitational_pull(body[i].mass, body[0].mass, distance(body[0].p, body[i].p));    
        //F[i] = vec4f(0,0,0,1);
        for (int j = 0; j < NO; ++j)
        {
            if (j != i)
            {
                //TODO
            }
        }
    }
    

    // update the velocity and position of body[i]
    for (int i = 1; i < NO; ++i)
    {
        vec4f a = F[i] / body[i].mass;
        body[i].v = body[i].v + a * dt;
        body[i].p = body[i].p + body[i].v * dt;
        
        trail[i].push_front(body[i].p);
        if (trail[i].size() > 1000)
        {
            trail[i].pop_back();
        }
    }
    glutPostRedisplay();
    glutTimerFunc(1, animate, 1);

}


void init_planets()
{
    body = new Body[10];
    body[0].radius = 1E10;
    body[0].mass = MASS[0];


    for (int i = 1; i < NO; ++i)
    {
     
		body[i].mass = MASS[i];
		body[i].radius = (DIAMETER[i] / 2) * 0.001;
        body[i].p.set_x(body[0].radius + PERIHELION[i] + body[i].radius);
        body[i].p.set_y(0);
        body[i].p.set_z(0);   
        body[i].v.set_z(perihelion_speed(body[0], body[i], SEMI_MAJOR_AXIS[i]));
    }
}

double gravitational_pull(double M1, double M2, double r)
{
    return G * (M1 * M2) / (r * r);
}

double distance(vec4f u, vec4f v)
{
    double x, y, z;
    x = v.get_x() - u.get_x();
    y = v.get_y() - u.get_y();
    z = v.get_z() - u.get_z();
    return sqrt((x * x) + (y * y) + (z * z));
}

double perihelion_speed(Body sun, Body planet, double axis_length)
{
    double r = distance(sun.p, planet.p);
    return sqrt(G * sun.mass * ((2 / r) - (1 / axis_length))); 
}



int main(int argc, char ** argv)
{
    mygllib::init3d();	
	init();
    init_planets();
	glClearColor(0, 0, 0, 0);
	glClearDepth(1.0f);
	glEnable(GL_DEPTH_TEST);
	glShadeModel(GL_SMOOTH);
	glEnable(GL_NORMALIZE);
    
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_COLOR_MATERIAL);
    glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);

	glutDisplayFunc(display);
	glutReshapeFunc(mygllib::Reshape::reshape);
	glutKeyboardFunc(mygllib::Keyboard::keyboard);
	glutTimerFunc(1, animate, 1);
	glutMainLoop();

	return 0;
}
