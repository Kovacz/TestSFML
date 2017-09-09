#include <iostream>
#include <windows.h>
#include <SFML\Graphics.hpp>
#include "level.h"
#define MTR_2PI_F 6.283185307179586f
#define MTR_RADIAN_F 57.295779513082320876798154814105f
#define step 100

using namespace sf; 
using namespace std;

enum look
{
	right, left, down, up, downright, upright, upleft, downleft
};

FloatRect getRect(float x, float y, float w, float h)
{//ф-ция получения прямоугольника. его коорд,размеры (шир,высот).
	return FloatRect(x, y, w, h);//эта ф-ция нужна для проверки столкновений 
}

//void checkCollisionWithMap(float &Dx, float &Dy, Object &object, Sprite &hero)
//{
//	float x = hero.getPosition().x;
//	float y = hero.getPosition().y;
//	float w = 125;
//	float h = 125;
//	bool onGround = false;
//
//		if (getRect(x, y, w, h).intersects(object.rect))//проверяем пересечение игрока с объектом
//		{
//			if (object.name == "solid")//если встретили препятствие
//			{
//				if (Dy>0) { y = object.rect.top - h;  dy = 0; onGround = true; }
//				if (Dy<0) { y = object.rect.top + object.rect.height;   dy = 0; }
//				if (Dx>0) { x = object.rect.left - w; }
//				if (Dx<0) { x = object.rect.left + object.rect.width; }
//			}
//		}
//}

float mtrAngle_f(float x, float y)
{
	float dir;

	dir = acosf(x / sqrtf(powf(-x, 2.0f) + powf(-y, 2.0f)));
	if (y > 0.0f)
		dir = MTR_2PI_F - dir;

	return dir * MTR_RADIAN_F;
}

void animation(float &CurrentFrame, float &time, Sprite &hero_sprite, Vector2f &totalMovement, int scale)
{
	//if (totalMovement.x != 0 && totalMovement.y != 0)
	//{

		CurrentFrame += 0.005 * time;
		if (CurrentFrame > 8)
			CurrentFrame -= 8;
		hero_sprite.setTextureRect(IntRect(127 * int(CurrentFrame), scale, 125, 125));
		hero_sprite.move(totalMovement* time * 0.001f);

		
	//}
}

void checkStep(Vector2f &totalMovement)
{
	if (totalMovement.x > step)
	{
		totalMovement.x = step;
	}
	if (totalMovement.y > step)
	{
		totalMovement.y = step;
	}
	if (totalMovement.x < -step)
	{
		totalMovement.x = -step;
	}
	if (totalMovement.y < -step)
	{
		totalMovement.y = -step;
	}
}

look lookAtMouse(int x, int y)
{
	float direction = mtrAngle_f(x, y);
	if (direction > 337.5f && direction <= 0.0f)
	{
		return look::right;
	}
	if (direction > 250.5f && direction <= 300.0f)
	{
		return look::down;
	}
	if (direction > 170.5f && direction <= 220.0f)
	{
		return look::left;
	}
	if (direction > 67.5f && direction <= 90.0f)
	{
		return look::up;
	}
	if (direction > 300.5f && direction <= 325.0f)
	{
		return look::downright;
	}
	if (direction > 22.5f && direction <= 67.5f)
	{
		return look::upright;
	}
	if (direction > 90.5f && direction <= 220.5f)
	{
		return look::upleft;
	}
	if (direction > 220.5f && direction <= 250.5f)
	{
		return look::downleft;
	}
}

int main()
{
	RenderWindow window(VideoMode(800, 600), "SFML works!");
	View view;
	view.reset(FloatRect(0, 0, 800, 600));

	Level level;
	level.LoadFromFile("map.tmx");

	Texture hero_texture;
	hero_texture.loadFromFile("textures/heroes/lol.png");

	Sprite hero_sprite;
	hero_sprite.setTexture(hero_texture);
	hero_sprite.setTextureRect(IntRect(500, 750, 125, 125));
	hero_sprite.setOrigin(50, 50);
	hero_sprite.setPosition(250, 250);

	//Object object;

	float CurrentFrame = 0;
	Clock clock;
	while ( window.isOpen() )
	{
		float time = clock.getElapsedTime().asMicroseconds(); 
		clock.restart();   
		time = time / 800; 

		Event event;
		while ( window.pollEvent(event) )
		{
			if ( event.type == Event::Closed )
				window.close();
		}
		if ( Mouse::isButtonPressed(Mouse::Right) )
		{
			
			Vector2i totalMovement;
			totalMovement.x = Mouse::getPosition(window).x - hero_sprite.getPosition().x;
			totalMovement.y = Mouse::getPosition(window).y - hero_sprite.getPosition().y;
			Vector2f pos = window.mapPixelToCoords(totalMovement);

			float x = pos.x;
			float y = pos.y;

			float direction = mtrAngle_f(pos.x, pos.y);

			cout << direction << endl;

			checkStep(pos);

			if (lookAtMouse(pos.x, pos.y) == look::up)
			{
				animation(CurrentFrame, time, hero_sprite, pos, 250);
			}
			else if (lookAtMouse(pos.x, pos.y) == look::down)
			{
				animation(CurrentFrame, time, hero_sprite, pos, 750);
			}
			else if (lookAtMouse(pos.x, pos.y) == look::left)
			{
				animation(CurrentFrame, time, hero_sprite, pos, 0);
			}
			else if (lookAtMouse(pos.x, pos.y) == look::right)
			{
				animation(CurrentFrame, time, hero_sprite, pos, 500);
			}
			else if (lookAtMouse(pos.x, pos.y) == look::downright)
			{
				animation(CurrentFrame, time, hero_sprite, pos, 625);
			}
			else if (lookAtMouse(pos.x, pos.y) == look::upright)
			{
				animation(CurrentFrame, time, hero_sprite, pos, 375);
			}
			else if (lookAtMouse(pos.x, pos.y) == look::upleft)
			{
				animation(CurrentFrame, time, hero_sprite, pos, 125);
			}
			else if (lookAtMouse(pos.x, pos.y) == look::downleft)
			{
				animation(CurrentFrame, time, hero_sprite, pos, 875);
			}
				
		}

		view.setCenter(hero_sprite.getPosition());
		window.setView(view);

		window.clear(Color(77, 83, 140));
		level.Draw(window);

		window.draw(hero_sprite);
		window.display();
	}

	return 0;
}
