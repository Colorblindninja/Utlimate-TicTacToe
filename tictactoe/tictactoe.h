#pragma once
#define _CRT_SECURE_NO_WARNINGS
#define CRTDBG_MAP_ALLOC
#ifdef _DEBUG
#ifndef DBG_NEW
#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
#define new DBG_NEW
#endif
#endif  // _DEBUG


#include <cstdlib>
#ifdef _WIN32
#include "glut.h"
#else
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#endif
#include <cmath>
#include <string>
#include <cstring>
#include <iostream>
#include <vector>
#include <fstream>

/*class Globs
{
public:
Globs();
//	Shape *Shapes[100];
int numShapes;
double screen_x, screen_y;
};
*/

class Vertex
{
public:
	Vertex();
	Vertex(double x, double y);
	bool setX(double x);
	bool setY(double y);
	double getX();
	double getY();

protected:
	double mX, mY;
};

class Shape
{
public:
	Shape();
	Shape(Vertex v);
	Vertex getV();
	bool setV(Vertex v);
	void setColors(double red, double green, double blue);
	virtual void draw() = 0;
	virtual void save(std::ostream &os);
	virtual void load(std::istream &is);

protected:
	Vertex mV;
	double mRed;
	double mGreen;
	double mBlue;
};

class Rectangle : public Shape
{
public:
	Rectangle();
	Rectangle(Vertex v, double width, double height);
	bool setWidth(double width);
	bool setHeight(double height);
	double getWidth();
	double getHeight();
	virtual void draw();
	void draw_lines();
	virtual void save(std::ostream &os);
	virtual void load(std::istream &is);

protected:
	double mWidth, mHeight;

};
class Button : public Rectangle
{
public:
	Button();
	Button(Vertex v, double width, double height, const char *name);
	void setNum(int num);
	int getNum();
	char *getName();
	bool setName(const char*name);
	virtual void draw();
	virtual bool isInside(Vertex v);
	void setIsClicked(bool isClicked);
	bool getIsClicked();
protected:
	int mNum;
	char mName[50];
	bool mIsClicked;
};



class Circle : public Shape
{
public:
	Circle();
	Circle(Vertex v, double r);
	bool setR(double r);
	double getR();
	virtual void draw();
	void draw_lines();
	virtual void save(std::ostream &os);
	virtual void load(std::istream &is);


protected:
	double mR;
};

class lowerButton : public Button
{
public:
	lowerButton();
	lowerButton(Vertex v);
	void setIsCircle(bool isClicked);
	bool getIsCircle();
	bool getIsX();
	void setIsX(bool x);
	virtual void draw();
	virtual bool isInside(Vertex v, int side);
	void save(std::ostream &os);
	void load(std::istream &is);
protected:
	bool mIsCricle;
	bool mIsX;
	Circle mCircle;
	Vertex mX[8]; // two points for each "rectangle" to make an X
};

class upperButton : public Button
{
public:
	upperButton();
	upperButton(Vertex v);
	void setCanPlay(bool canPlay);
	bool getCanPlay();
	std::string getWon();
	virtual void draw();
	int clicked(Vertex v, int side);
	std::string didWin(int x, int y, int z);
	void setLower(int num, std::string who);
	void save(std::ostream &os);
	void load(std::istream &is);
protected:
	bool mCanPlay;
	lowerButton mButtons[9];
	Rectangle mLines[8];
	std::string mWon;
	int mPossibleWins[8][3] = {
		{0,1,2},
		{3,4,5},
		{6,7,8},
		{0,3,6},
		{1,4,7},
		{2,5,8},
		{0,4,8},
		{2,4,6}
	};
};

class Game
{
public:
	Game();
	Game(double width, double height);
	void draw();
	std::string getWon();
	void someoneWon(std::string who);
	bool clicked(Vertex v);
	std::string didWin(int x, int y, int z);
	void save(std::ostream &os);
	void load(std::istream &is);
protected:
	double mWidth, mHeight;
	upperButton mButtons[9];
	Rectangle mLines[4];
	std::string mWon;
	int mActive;
	int mSide; // -1=circle, 1=X
	int mPossibleWins[8][3] = {
		{0,1,2},
		{3,4,5},
		{6,7,8},
		{0,3,6},
		{1,4,7},
		{2,5,8},
		{0,4,8},
		{2,4,6}
	};
};

void DrawText(double x, double y, const char *string);
void display();
void mouse(int mouse_button, int state, int x, int y);
void moveMouse(int x, int y);
void reshape(int w, int h);
void keyboard(unsigned char c, int x, int y);



