//#include "level.h"
//#include "view.h"
//
//int main()
//{
//	Level level;
//	level.LoadFromFile("map.tmx");
//
//	sf::RenderWindow window(sf::VideoMode(800, 600), "Test");
//	view.reset(sf::FloatRect(0, 0, 800, 600));
//
//	sf::Clock clock;
//	while (window.isOpen())
//	{
//		float time = clock.getElapsedTime().asMicroseconds();
//		clock.restart();
//		time = time / 800;
//
//		sf::Event event;
//		while (window.pollEvent(event))
//		{
//			if (event.type == sf::Event::Closed)
//				window.close();
//		}
//
//		viewmap(time);//функция скроллинга карты, передаем ей время sfml
//		window.setView(view);
//		window.clear(sf::Color(77, 83, 140));
//		level.Draw(window);//"оживляем" камеру в окне sfml
//		window.display();
//
//	}
//
//	return 0;
//}

#include <iostream>
#include <windows.h>
#include <SFML\Graphics.hpp>
#define MTR_2PI_F 6.283185307179586f
#define MTR_RADIAN_F 57.295779513082320876798154814105f

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

bool is_equal(double x, double y) 
{
	return std::fabs(x - y) < std::numeric_limits<double>::epsilon();
}

template <class Value>
int sign(Value Val)
{
	if (is_equal(Val, 0.))  return 0;
	if (Val >  0.)  return 1;
	else return -1;
}

look lookAtMouse(int x, int y)
{
<<<<<<< HEAD
	float direction = mtrAngle_f(x, y);
	if (direction > 337.5f && direction <= 0.0f)
=======
	if (x == 1 && y == 0)
>>>>>>> 8f5ce36c71c8adf43524508799483a198830a354
	{
		return look::right;
	}
	else if (direction > 270.5f && direction <= 290.0f)
	{
		return look::down;
	}
	else if (direction > 170.5f && direction <= 220.0f)
	{
		return look::left;
	}
	else if (direction > 67.5f && direction <= 90.0f)
	{
		return look::up;
	}
<<<<<<< HEAD
	else if (direction > 300.5f && direction <= 325.0f)
=======
	else if (x == 1 && y == 1)
>>>>>>> 8f5ce36c71c8adf43524508799483a198830a354
	{
		return look::downright;
	}
	else if (direction > 22.5f && direction <= 67.5f)
	{
		return look::upright;
	}
	else if (direction > 90.5f && direction <= 220.5f)
	{
		return look::upleft;
	}
	else if (direction > 220.5f && direction <= 290.5f)
	{
		return look::downleft;
	}
}

void MoveTo(Sprite hero_sprite)
{
	//Vector2i coords(Mouse::getPosition(window));
	//hero_sprite.setPosition( coords );
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


	double CurrentFrame = 0;
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

			if (totalMovement.x > 100)
			{
				totalMovement.x = 100;
			}
			if (totalMovement.y > 100)
			{
				totalMovement.y = 100;
			}
			if (totalMovement.x < -100)
			{
				totalMovement.x = -100;
			}
			if (totalMovement.y < -100)
			{
				totalMovement.y = -100;
			}


			double dir_x = sign(totalMovement.x);
			double dir_y = sign(totalMovement.y);

			cout << mtrAngle_f(totalMovement.x, totalMovement.y) << endl;

<<<<<<< HEAD
			if (lookAtMouse(totalMovement.x, totalMovement.y) == look::up)
=======
			if (lookAtMouse(dir_x, dir_y) == look::up)
>>>>>>> 8f5ce36c71c8adf43524508799483a198830a354
			{
				CurrentFrame += 0.005 * time;
				if (CurrentFrame > 8)
					CurrentFrame -= 8;
				hero_sprite.setTextureRect(IntRect(128 * int(CurrentFrame), 254, 128, 128));
				hero_sprite.move(totalMovement * time * 0.001f);
			}
			else if (lookAtMouse(totalMovement.x, totalMovement.y) == look::down)
			{
				CurrentFrame += 0.005*time;
				if (CurrentFrame > 8)
					CurrentFrame -= 8;
				hero_sprite.setTextureRect(IntRect(128 * int(CurrentFrame), 762, 128, 128));
				hero_sprite.move(totalMovement * time * 0.001f);
			}
			else if (lookAtMouse(totalMovement.x, totalMovement.y) == look::left)
			{
				CurrentFrame += 0.005*time;
				if (CurrentFrame > 8)
					CurrentFrame -= 8;
				hero_sprite.setTextureRect(IntRect(128 * int(CurrentFrame), 0, 128, 128));
				hero_sprite.move(totalMovement * time * 0.001f);
			}
			else if (lookAtMouse(totalMovement.x, totalMovement.y) == look::right)
			{
				CurrentFrame += 0.005*time;
				if (CurrentFrame > 8)
					CurrentFrame -= 8;
				hero_sprite.setTextureRect(IntRect(128 * int(CurrentFrame), 508, 128, 128));
				hero_sprite.move(totalMovement * time * 0.001f);
			}
			else if (lookAtMouse(dir_x, dir_y) == look::downright)
			{
				CurrentFrame += 0.005*time; 
				if (CurrentFrame > 8) 
					CurrentFrame -= 8;
				hero_sprite.setTextureRect(IntRect(128 * int(CurrentFrame), 635, 128, 128)); 
				hero_sprite.move(totalMovement * time * 0.001f);
			}
			else if (lookAtMouse(dir_x, dir_y) == look::upright)
			{
				CurrentFrame += 0.005 * time;
				if (CurrentFrame > 8)
					CurrentFrame -= 8;
				hero_sprite.setTextureRect(IntRect(128 * int(CurrentFrame), 381, 128, 128));
				hero_sprite.move(totalMovement * time * 0.001f);
			}
			else if (lookAtMouse(dir_x, dir_y) == look::upleft)
			{
				CurrentFrame += 0.005*time;
				if (CurrentFrame > 8)
					CurrentFrame -= 8;
				hero_sprite.setTextureRect(IntRect(128 * int(CurrentFrame), 127, 128, 128));
				hero_sprite.move(totalMovement * time * 0.001f);
			}
			else if (lookAtMouse(dir_x, dir_y) == look::downleft)
			{
				CurrentFrame += 0.005*time;
				if (CurrentFrame > 8)
					CurrentFrame -= 8;
				hero_sprite.setTextureRect(IntRect(128 * int(CurrentFrame), 889, 128, 128));
				hero_sprite.move(totalMovement * time * 0.001f);
			}
				
		}

		
		window.clear(Color::White);
		window.draw(hero_sprite);
		window.display();
	}

	return 0;
}