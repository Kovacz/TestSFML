#include <iostream>
#include <SFML\Graphics.hpp>

using namespace sf; 
using namespace std;

enum look
{
	right, left, down, up, downright, upright, upleft, downleft
};

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
	if (x == 1 && y == 0)
	{
		return look::right;
	}
	else if (x == -1 && y == 0)
	{
		return look::left;
	}
	else if (x == 0 && y == 1)
	{
		return look::down;
	}
	else if (x == 0 && y == -1)
	{
		return look::up;
	}
	else if (x == 1 && y == 1)
	{
		return look::downright;
	}
	else if (x == 1 && y == -1)
	{
		return look::upright;
	}
	else if (x == -1 && y == -1)
	{
		return look::upleft;
	}
	else if (x == -1 && y == 1)
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
		double time = clock.getElapsedTime().asMicroseconds(); 
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

			double dir_x = sign(totalMovement.x);
			double dir_y = sign(totalMovement.y);

			cout << dir_x << " " << dir_y << endl;

			if (lookAtMouse(dir_x, dir_y) == look::up)
			{
				CurrentFrame += 0.005*time;
				if (CurrentFrame > 8)
					CurrentFrame -= 8;
				hero_sprite.setTextureRect(IntRect(128 * int(CurrentFrame), 254, 128, 128));
				hero_sprite.move(totalMovement * (1.f / 1000.f));
			}
			else if (lookAtMouse(dir_x, dir_y) == look::down)
			{
				CurrentFrame += 0.005*time;
				if (CurrentFrame > 8)
					CurrentFrame -= 8;
				hero_sprite.setTextureRect(IntRect(128 * int(CurrentFrame), 762, 128, 128));
				hero_sprite.move(totalMovement * (1.f / 1000.f));
			}
			else if (lookAtMouse(dir_x, dir_y) == look::left)
			{
				CurrentFrame += 0.005*time;
				if (CurrentFrame > 8)
					CurrentFrame -= 8;
				hero_sprite.setTextureRect(IntRect(128 * int(CurrentFrame), 0, 128, 128));
				hero_sprite.move(totalMovement * (1.f / 1000.f));
			}
			else if (lookAtMouse(dir_x, dir_y) == look::right)
			{
				CurrentFrame += 0.005*time;
				if (CurrentFrame > 8)
					CurrentFrame -= 8;
				hero_sprite.setTextureRect(IntRect(128 * int(CurrentFrame), 508, 128, 128));
				hero_sprite.move(totalMovement * (1.f / 1000.f));
			}
			else if (lookAtMouse(dir_x, dir_y) == look::downright)
			{
				CurrentFrame += 0.005*time; 
				if (CurrentFrame > 8) 
					CurrentFrame -= 8;
				hero_sprite.setTextureRect(IntRect(128 * int(CurrentFrame), 635, 128, 128)); 
				hero_sprite.move(totalMovement * (1.f / 1000.f));
			}
			else if (lookAtMouse(dir_x, dir_y) == look::upright)
			{
				CurrentFrame += 0.005*time;
				if (CurrentFrame > 8)
					CurrentFrame -= 8;
				hero_sprite.setTextureRect(IntRect(128 * int(CurrentFrame), 381, 128, 128));
				hero_sprite.move(totalMovement * (1.f / 1000.f));
			}
			else if (lookAtMouse(dir_x, dir_y) == look::upleft)
			{
				CurrentFrame += 0.005*time;
				if (CurrentFrame > 8)
					CurrentFrame -= 8;
				hero_sprite.setTextureRect(IntRect(128 * int(CurrentFrame), 127, 128, 128));
				hero_sprite.move(totalMovement * (1.f / 1000.f));
			}
			else if (lookAtMouse(dir_x, dir_y) == look::downleft)
			{
				CurrentFrame += 0.005*time;
				if (CurrentFrame > 8)
					CurrentFrame -= 8;
				hero_sprite.setTextureRect(IntRect(128 * int(CurrentFrame), 889, 128, 128));
				hero_sprite.move(totalMovement * (1.f / 1000.f));
			}
				
		}

		
		window.clear(Color::White);
		window.draw(hero_sprite);
		window.display();
	}

	return 0;
}
