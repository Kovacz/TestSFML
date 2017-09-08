#include <iostream>
#include <windows.h>
#include <SFML\Graphics.hpp>
#define MTR_2PI_F 6.283185307179586f
#define MTR_RADIAN_F 57.295779513082320876798154814105f
#define step 100

using namespace sf; 
using namespace std;

enum look
{
	right, left, down, up, downright, upright, upleft, downleft
};

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
	CurrentFrame += 0.005 * time;
	if (CurrentFrame > 8)
		CurrentFrame -= 8;
	hero_sprite.setTextureRect(IntRect(128 * int(CurrentFrame), scale, 128, 128));
	hero_sprite.move(totalMovement* time * 0.001f);
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
	if (direction > 270.5f && direction <= 290.0f)
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
	if (direction > 220.5f && direction <= 290.5f)
	{
		return look::downleft;
	}
}

int main()
{
	RenderWindow window(VideoMode(800, 600), "SFML works!");

	Texture hero_texture;
	hero_texture.loadFromFile("textures/heroes/lol.png");

	Sprite hero_sprite;
	hero_sprite.setTexture(hero_texture);
	hero_sprite.setTextureRect(IntRect(900, 765, 127, 127));
	hero_sprite.setOrigin(50, 50);
	hero_sprite.setPosition(250, 250);
	hero_sprite.setRotation(0);


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
			
			Vector2f totalMovement;
			totalMovement.x = Mouse::getPosition(window).x - hero_sprite.getPosition().x;
			totalMovement.y = Mouse::getPosition(window).y - hero_sprite.getPosition().y;

			cout << mtrAngle_f(totalMovement.x, totalMovement.y) << endl;


			if (lookAtMouse(totalMovement.x, totalMovement.y) == look::up)
			{
				animation(CurrentFrame, time, hero_sprite, totalMovement, 254);
			}
			else if (lookAtMouse(totalMovement.x, totalMovement.y) == look::down)
			{
				animation(CurrentFrame, time, hero_sprite, totalMovement, 762);
			}
			else if (lookAtMouse(totalMovement.x, totalMovement.y) == look::left)
			{
				animation(CurrentFrame, time, hero_sprite, totalMovement, 0);
			}
			else if (lookAtMouse(totalMovement.x, totalMovement.y) == look::right)
			{
				animation(CurrentFrame, time, hero_sprite, totalMovement, 508);
			}
			else if (lookAtMouse(totalMovement.x, totalMovement.y) == look::downright)
			{
				animation(CurrentFrame, time, hero_sprite, totalMovement, 635);
			}
			else if (lookAtMouse(totalMovement.x, totalMovement.y) == look::upright)
			{
				animation(CurrentFrame, time, hero_sprite, totalMovement, 381);
			}
			else if (lookAtMouse(totalMovement.x, totalMovement.y) == look::upleft)
			{
				animation(CurrentFrame, time, hero_sprite, totalMovement, 127);
			}
			else if (lookAtMouse(totalMovement.x, totalMovement.y) == look::downleft)
			{
				animation(CurrentFrame, time, hero_sprite, totalMovement, 889);
			}
				
		}

		
		window.clear(Color::White);
		window.draw(hero_sprite);
		window.display();
	}

	return 0;
}
