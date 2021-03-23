/***************************************
	cpp file for class "Brick".
***************************************/
#include "Brick.h"


void Brick::drawBrick()
{
	switch (shapeNum)
	{
	case 0:
		drawBrick0();
		break;
	case 1:
		drawBrick1();
		break;
	case 2:
		drawBrick2();
		break;
	case 3:
		drawBrick3();
		break;
	case 4:
		drawBrick4();
		break;
	case 5:
		drawBrick5();
		break;
	case 6:
		drawBrick6();
		break;
	}
	gotoxy(pos.getX(), pos.getY());
	for (Point i:type)
		i.draw(shape);
}

void Brick::drawBrick0()
{
	for (int i = 0; i < 4; i++)
		type[i].setPos(pos.getX() + i, pos.getY());
}
void Brick::drawBrick1()
{
	int count = 0;
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			if ((i == 0) || (j == 1))
				type[count++].setPos(pos.getX() + i, pos.getY() + j);
		}
	}
}
		
void Brick::drawBrick2()
{
	int count = 0;
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			if ((i == 2) || (j == 1))
				type[count++].setPos(pos.getX() + i, pos.getY() + j);
		}
	}
}
void Brick::drawBrick3()
{
	int count = 0;
	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 2; j++)
			type[count++].setPos(pos.getX() + i, pos.getY() + j);
	}
}
void Brick::drawBrick4()
{
	int count = 0;
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			if ((j == 0 && i > 0) || (j == 1 && i < 2))
				type[count++].setPos(pos.getX() + i, pos.getY() + j);
		}
	}
}
void Brick::drawBrick5()
{
	int count = 0;
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			if ((i == 1) || (j == 1))
				type[count++].setPos(pos.getX() + i, pos.getY() + j);
		}
	}
}
void Brick::drawBrick6()
{
	int count = 0;
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			if ((j == 0 && i < 2) || (j == 1 && i > 0))
				type[count++].setPos(pos.getX() + i, pos.getY() + j);
		}
	}
}

void Brick::setShape()
{
	srand(time(0));
	shapeNum = rand() % 100;
	shapeNum = shapeNum % 7;
}
