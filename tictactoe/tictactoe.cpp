#include "tictactoe.h"
extern double g_red, g_blue, g_green;

// Vertex Methods
Vertex::Vertex()
	:mX(0), mY(0)
{}
Vertex::Vertex(double x, double y)
{
	setX(x);
	setY(y);
}
bool Vertex::setX(double x)
{
	mX = x;
	return true;
}
bool Vertex::setY(double y)
{
	mY = y;
	return true;
}
double Vertex::getX()
{
	return mX;
}
double Vertex::getY()
{
	return mY;
}

// Parent Shape Methods
Shape::Shape()
{
	mV.setX(0);
	mV.setY(0);
}
Shape::Shape(Vertex v)
{
	setV(v);
}
void Shape::setColors(double red, double green, double blue)
{
	mRed = red;
	mGreen = green;
	mBlue = blue;
}
bool Shape::setV(Vertex v)
{
	mV = v;
	return true;
}
Vertex Shape::getV()
{
	return mV;
}
void Shape::save(std::ostream &os)
{
	os << mRed << " "
		<< mGreen << " "
		<< mBlue << " ";
}
void Shape::load(std::istream &is)
{
	is >> mRed >> mGreen >> mBlue;
}



//Rectangle Methods
Rectangle::Rectangle()
	:Shape(), mWidth(0), mHeight(0)
{}
Rectangle::Rectangle(Vertex v, double width, double height)
	: Shape(v), mWidth(width), mHeight(height)
{}
bool Rectangle::setWidth(double width)
{
	mWidth = width;
	return true;
}
bool Rectangle::setHeight(double height)
{
	mHeight = height;
	return true;
}
double Rectangle::getWidth()
{
	return mWidth;
}
double Rectangle::getHeight()
{
	return mHeight;
}
void Rectangle::save(std::ostream &os)
{
	os << "Rectangle "
		<< mV.getX() << " "
		<< mV.getY() << " "
		<< mWidth << " "
		<< mHeight << " ";
	Shape::save(os);
}
void Rectangle::load(std::istream &is)
{
	double x, y;
	is >> x >> y >> mWidth >> mHeight;
	mV.setX(x);
	mV.setY(y);
	Shape::load(is);
}
void Rectangle::draw()
{
	glColor3d(mRed, mGreen, mBlue);
	glBegin(GL_QUADS);
	glVertex2d(mV.getX(), mV.getY());
	glVertex2d(mV.getX() + mWidth, mV.getY());
	glVertex2d(mV.getX() + mWidth, mV.getY() + mHeight);
	glVertex2d(mV.getX(), mV.getY() + mHeight);
	glEnd();
}
void Rectangle::draw_lines()
{
	glBegin(GL_LINE_STRIP);
	glVertex2d(mV.getX(), mV.getY());
	glVertex2d(mV.getX() + mWidth, mV.getY());
	glVertex2d(mV.getX() + mWidth, mV.getY() + mHeight);
	glVertex2d(mV.getX(), mV.getY() + mHeight);
	glVertex2d(mV.getX(), mV.getY());
	glEnd();
}

//Button Methods
Button::Button()
	:Rectangle()
{
	mName[0] = 0;
}
Button::Button(Vertex v, double width, double height, const char *name)
	: Rectangle(v, width, height)
{
	setName(name);
	mIsClicked = false;
}
char *Button::getName()
{
	return mName;
}
bool Button::setName(const char *name)
{
	std::strcpy(mName, name);
	mName[std::strlen(mName) + 1] = 0;
	return true;
}
void Button::draw()
{
	if (mIsClicked)
	{
		setColors(0, 0, 0);
	}
	else
	{
		setColors(.4, .4, .4);
	}
	Rectangle::draw();
	glColor3d(1, 1, 1);  // 0-1 1 being full color
	DrawText(mV.getX() + 2, mV.getY() + 2, mName);

}
bool Button::isInside(Vertex v)
{
	if (v.getX() >= mV.getX() && v.getX() <= (mV.getX() + mWidth) && v.getY() >= mV.getY() && v.getY() <= (mV.getY() + mHeight))
	{
		return true;
	}
	return false;

}
void Button::setIsClicked(bool isClicked)
{
	mIsClicked = isClicked;
}
bool Button::getIsClicked()
{
	return mIsClicked;
}
void Button::setNum(int num)
{
	mNum = num;
}
int Button::getNum()
{
	return mNum;
}

//Circle Methods
Circle::Circle()
	:mR(0), Shape() {}
Circle::Circle(Vertex v, double r)
	: Shape(v)
{
	setR(r);
}
bool Circle::setR(double r)
{
	mR = r;
	return true;
}
double Circle::getR()
{
	return mR;
}
void Circle::draw()
{
	glColor3d(mRed, mGreen, mBlue);
	glBegin(GL_POLYGON);
	for (int i = 0; i<32; i++)
	{
		double theta = (double)i / 32.0 * 2.0 * 3.1415926;
		double x = mV.getX() + mR * cos(theta);
		double y = mV.getY() + mR * sin(theta);
		glVertex2d(x, y);
	}
	glEnd();

}
void Circle::draw_lines()
{
	glBegin(GL_LINE_STRIP);
	for (int i = 0; i<33; i++)
	{
		double theta = (double)i / 32.0 * 2.0 * 3.1415926;
		double x = mV.getX() + mR * cos(theta);
		double y = mV.getY() + mR * sin(theta);
		glVertex2d(x, y);
	}
	glEnd();
}
void Circle::save(std::ostream &os)
{
	os << "Circle "
		<< mV.getX() << " "
		<< mV.getY() << " "
		<< mR << " ";
	Shape::save(os);
}
void Circle::load(std::istream &is)
{
	double x, y;
	is >> x >> y >> mR;
	mV.setX(x);
	mV.setY(y);
	Shape::load(is);

}


Game::Game()
{
	mWon = "no";
	mWidth = 0;
	mHeight = 0;
	mActive = -1;
}
Game::Game(double width, double height)
{
	mSide = 1;
	mWon = "no";
	mActive = -1;
	mWidth = width;
	mHeight = height;
	mLines[0] = Rectangle(Vertex(200, 0), 20, 640);
	mLines[1] = Rectangle(Vertex(420, 0), 20, 640);
	mLines[2] = Rectangle(Vertex(0,200), 640, 20);
	mLines[3] = Rectangle(Vertex(0, 420), 640, 20);
	int i;
	for (i = 0; i < 4; i++)
	{
		mLines[i].setColors(0, 0, 0);
	}
	double inc = 220;
	double x = 0, y = 0;
	for (i = 1; i < 10; i++)
	{
		mButtons[i - 1] = upperButton(Vertex(x,y));
		if (i % 3 == 0)
		{
			y += inc;
			x = 0;
		}
		else
		{
			x += inc;
		}
		mButtons[i - 1].setNum(i - 1);
	}
}
void Game::draw()
{
	int i;
	for (i = 0; i < 4; i++)
	{
		mLines[i].draw();
	}
	for (i = 0; i < 9; i++)
	{
		mButtons[i].draw();
	}
	if (mSide == 1)
	{
		glColor3d(.35, .12, .6);
		DrawText(550, 750, "Turn: X");
	}
	else
	{
		glColor3d(.7, .25, 0);
		DrawText(550, 750, "Turn: O");
	}
	const char* tempWho;
	std::string who = mWon;
	if (mWon != "no")
	{
		if (mWon != "tie")
		{
			who += " won!";
			tempWho = who.c_str();
		}
		else
		{
			glColor3d(.5, .5, .5);
			tempWho = "It Was Tie";
		}
		if (mWon == "circle")
		{
			glColor3d(.7, .25, 0);
		}
		else if (mWon == "x")
		{
			glColor3d(.35, .12, .6);
		}
		DrawText(280, 675, tempWho);
	}

}
bool Game::clicked(Vertex v)
{
	
	int i, active;
	for (i = 0; i < 9; i++)
	{
		active = mButtons[i].clicked(v, mSide);
		if (active > -1)
		{
			mActive = active;
			mSide *= -1;
		}
	}

	if (mButtons[mActive].getWon() != "no")
	{
		for (i = 0; i < 9; i++)
		{
			if (mButtons[i].getWon() == "no")
			{
				mButtons[i].setCanPlay(true);
			}
		}
	}
	else
	{
		mButtons[mActive].setCanPlay(true);
	}
	//mButtons[mActive].setCanPlay(true);
	std::string who;
	for (i = 0; i < 8; i++)
	{
		who = didWin(mPossibleWins[i][0], mPossibleWins[i][1], mPossibleWins[i][2]);
		if (who != "no")
		{
			for (i = 0; i < 9; i++)
			{
				mButtons[i].setCanPlay(false);
			}
		}
	}
	if (who == "no")
	{
		bool isTie = true;
		int j;
		for (j = 0; j < 9; j++)
		{
			if (mButtons[j].getWon() == "no")
			{
				isTie = false;
			}
		}
		if (isTie)
		{
			mWon = "tie";
			for (i = 0; i < 9; i++)
			{
				mButtons[i].setCanPlay(false);
			}
			return true;
		}
	}

}
std::string Game::didWin(int x, int y, int z)
{
	if ((mButtons[x].getWon() == "circle" && mButtons[y].getWon() == "circle") && (mButtons[x].getWon() == "circle" && mButtons[z].getWon() == "circle"))
	{
		mWon = "circle";
	}
	else if ((mButtons[x].getWon() == "x" && mButtons[y].getWon() == "x") && (mButtons[x].getWon() == "x" && mButtons[z].getWon() == "x"))
	{
		mWon = "x";
	}
	else
	{
		mWon = "no";
	}
	return mWon;
}
std::string Game::getWon()
{
	return mWon;
}
void Game::someoneWon(std::string who)
{
	const char* tempWho;
	if (!(who == "tie"))
	{
		who += " won!";
		tempWho = who.c_str();
	}
	else
	{
		tempWho = "It Was Tie";
	}
	mButtons[mActive].setCanPlay(false);
	glColor3d(.5, .5, 0);
	DrawText(300, 700, tempWho);
}
void Game::save(std::ostream &os)
{
	os << mSide << " ";
	int i;
	for (i = 0; i < 9; i++)
	{
		mButtons[i].save(os);
	}
}
void Game::load(std::istream &is)
{
	is >> mSide;
	int i;
	for (i = 0; i < 9; i++)
	{
		mButtons[i].load(is);
	}
}

upperButton::upperButton()
	:Button(Vertex(0,0),0,0,"")
{
	mWon = "no";
	mCanPlay = true;
}
upperButton::upperButton(Vertex v)
	:Button(v, 200, 200, "")
{
	mWon = "no";
	setColors(.2, .2, .2);
	mCanPlay = true;
	mLines[0] = Rectangle(Vertex(mV.getX() + 60, mV.getY() + 3), 5, mHeight - 3);
	mLines[1] = Rectangle(Vertex(mV.getX() + 125, mV.getY() + 3), 5, mHeight - 3);
	mLines[2] = Rectangle(Vertex(mV.getX() + 3, mV.getY() + 60), mWidth - 9, 5);
	mLines[3] = Rectangle(Vertex(mV.getX() + 3, mV.getY() + 125), mWidth - 9, 5);
	int i;
	for (i = 0; i < 4; i++)
	{
		mLines[i].setColors(0, 0, 0);
	}
	double width = 0, height = 0;
	for (i = 1; i < 10; i++)
	{
		mButtons[i-1] = lowerButton(Vertex(mV.getX()+width, mV.getY()+height));
		if (i % 3 == 0)
		{
			height += 70;
			width = 0;
		}
		else
		{
			width += 70;
		}
		mButtons[i - 1].setNum(i - 1);
	}
}
int upperButton::clicked(Vertex v, int side)
{
	if (!mCanPlay)
	{
		return -1;
	}
	setCanPlay(false);
	int i, clicked = -1;
	for (i = 0; i < 9; i++)
	{
		if (mButtons[i].isInside(v, side))
		{
			clicked = i;
		}
	}
	for (i = 0; i < 8; i++)
	{
		didWin(mPossibleWins[i][0], mPossibleWins[i][1], mPossibleWins[i][2]);
	}
	if (mWon == "no")
	{
		bool isFull = true;
		for (i = 0; i < 9; i++)
		{
			if (!(mButtons[i].getIsCircle() || mButtons[i].getIsX()))
			{
				isFull = false;
			}
		}
		if (isFull)
		{
			mWon = "tie";
		}
	}
	return clicked;
}
void upperButton::draw()
{
	if (mWon == "circle")
	{
		setColors(.7, .25, 0);
	}
	if (mWon == "x")
	{
		setColors(.35, .12, .6);
	}
	if (mWon == "tie")
	{
		setColors(.5, .5, .5);
	}
	if (!mCanPlay)
	{
		Rectangle::draw();
	}
	int i;
	for (i = 0; i < 9; i++)
	{
		mButtons[i].draw();
	}
	for (i = 0; i < 4; i++)
	{
		mLines[i].draw();
	}
}
void upperButton::setCanPlay(bool canPlay)
{
	mCanPlay = canPlay;
}
bool upperButton::getCanPlay()
{
	return mCanPlay;
}
std::string upperButton::didWin(int x, int y, int z)
{
	if (mWon != "no")
	{
		return mWon;
	}
	if ((mButtons[x].getIsCircle() && mButtons[y].getIsCircle()) && (mButtons[x].getIsCircle() && mButtons[z].getIsCircle()))
	{
		mWon = "circle";
	}
	else if ((mButtons[x].getIsX() && mButtons[y].getIsX()) && (mButtons[x].getIsX() && mButtons[z].getIsX()))
	{
		mWon = "x";
	}
	else
	{
		mWon = "no";
	}
	return mWon;
}
std::string upperButton::getWon()
{
	return mWon;
}
void upperButton::setLower(int num, std::string who)
{

}
void upperButton::save(std::ostream &os)
{
	os << mCanPlay << " "
		<< mWon << " ";
	int i;
	for (i = 0; i < 9; i++)
	{
		mButtons[i].save(os);
	}
}
void upperButton::load(std::istream &is)
{
	is >> mCanPlay >> mWon;
	int i;
	for (i = 0; i < 9; i++)
	{
		mButtons[i].load(is);
	}
}

lowerButton::lowerButton()
	:Button(Vertex(0,0), 0, 0, "")
{
	mIsCricle = false;
	mIsX = false;
}
lowerButton::lowerButton(Vertex v)
	: Button(v, 60, 60, "")
{
	mIsCricle = false;
	mIsX = false;
	mCircle = Circle(Vertex(mV.getX() + (mWidth / 2)-5, mV.getY() + (mHeight / 2)-5), mHeight/2 -1);
	mX[3] = Vertex(mV.getX(), mV.getY() + 2); //1's bottom left point
	mX[2] = Vertex(mV.getX() + 8, mV.getY() + 2); // 1's bottom right
	mX[1] = Vertex(mV.getX() + (mWidth - 10), mV.getY() + (mHeight - 2)); //1's top right point
	mX[0] = Vertex(mV.getX() + (mWidth - 18), mV.getY() + (mHeight - 2)); //1's top left

	mX[6] = Vertex(mV.getX() + (mWidth - 10), mV.getY() + 2); // 2's bottom right point
	mX[4] = Vertex(mV.getX(), mV.getY() + (mHeight - 2)); //2's top left
	mX[7] = Vertex(mV.getX() + (mWidth - 18), mV.getY() + 2); // 2's bottom left point
	mX[5] = Vertex(mV.getX() + 8, mV.getY() + (mHeight - 2)); //2's top right

	mCircle.setColors(1, .35, 0);
}
void lowerButton::draw()
{
	if (mIsCricle && !mIsX)
	{
		mCircle.draw();
	}
	else if (mIsX && !mIsCricle)
	{
		int i;
		glColor3d(.5, .2, .9);
		glBegin(GL_QUADS);
		for (i = 0; i < 4; i++)
		{
			glVertex2d(mX[i].getX(), mX[i].getY());
		}
		glEnd();
		glBegin(GL_QUADS);
		for (i = 4; i < 8; i++)
		{
			glVertex2d(mX[i].getX(), mX[i].getY());
		}
		glEnd();
	}
	else
	{
		return;
	}
}
void lowerButton::setIsCircle(bool isCircle)
{
	mIsCricle = isCircle;
}
bool lowerButton::getIsCircle()
{
	return mIsCricle;
}
void lowerButton::setIsX(bool x)
{
	mIsX = x;
}
bool lowerButton::getIsX()
{
	return mIsX;
}
bool lowerButton::isInside(Vertex v, int side)
{
	if (mIsClicked == true)
	{
		return false;
	}
	if (Button::isInside(v) && side == -1)
	{
		mIsCricle = true;
		mIsClicked = true;
		return true;
	}
	else if (Button::isInside(v) && side == 1)
	{
		mIsX = true;
		mIsClicked = true;
		return true;
	}
	else
	{
		return false;
	}
}
void lowerButton::save(std::ostream &os)
{
	os << mIsCricle << " "
		<< mIsX << " ";
}
void lowerButton::load(std::istream &is)
{
	is >> mIsCricle >> mIsX;
}


void DrawText(double x, double y, const char *string)
{
	void *font = GLUT_BITMAP_TIMES_ROMAN_24;

	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);

	int len, i;
	glRasterPos2d(x, y);
	len = (int)strlen(string);
	for (i = 0; i < len; i++)
	{
		glutBitmapCharacter(font, string[i]);
	}

	glDisable(GL_BLEND);
}