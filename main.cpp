#include <iostream>
#include <sstream>
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

class Player
{
public:
	vector<Object> obj;
	float dx, dy, x, y, speed, frame;
	int width, height;
	bool on_ground;
	Texture texture;
	Sprite sprite;
	Font font;
	Text text;
public:
	Player(Image &image, float px, float py, int w, int h, Level &level) : x(px), y(py), width(w), height(h), speed(0.001f), on_ground(false), frame(0.0), text("", font, 20)
	{
		dx = dy = 0;
		texture.loadFromImage(image);
		sprite.setTexture(texture);
		sprite.setOrigin(w / 2, h / 2);
		sprite.setPosition(px, py);
		obj = level.GetAllObjects();//инициализируем.получаем все объекты для взаимодействия персонажа с картой
		sprite.setTextureRect(IntRect(500, 750, w, h));
	}

	FloatRect getRect() //ф-ция получения прямоугольника. его коорд,размеры (шир,высот).
	{	
		return FloatRect(x, y, width, height);//эта ф-ция нужна для проверки столкновений 
	}

	float mtrAngle_f(float x, float y)
	{
		float dir;
		dir = acosf( x / sqrtf(powf(-x, 2.0f) + powf(-y, 2.0f)) );
		if (y > 0.0f)	{ dir = MTR_2PI_F - dir; }
			
		return dir * MTR_RADIAN_F;
	}

	void animation(float &time, Vector2f &totalMovement, int scale)
	{
		//if (totalMovement.x != 0 && totalMovement.y != 0)
		//{
		frame += 0.005 * time;
		if (frame > 8)
			frame -= 8;
		sprite.setTextureRect(IntRect(127 * int(frame), scale, width, height));
		sprite.move(totalMovement * time * speed);
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
		if (direction > 170.5f && direction <= 210.0f)
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
		if (direction > 90.5f && direction <= 170.5f)
		{
			return look::upleft;
		}
		if (direction > 210.5f && direction <= 250.5f)
		{
			return look::downleft;
		}
	}

	void checkCollisionWithMap(float Dx, float Dy)
	{
		
		for (int i = 0; i < obj.size(); i++)
		{
			//cout << getRect().intersects(obj[i].rect) << endl;
			if (getRect().intersects(obj[i].rect))
			{
				if (obj[i].name == "solid")
				{
					cout << "YES" << endl;
					//if (lookAtMouse(Dx, Dy) == look::up) { y = obj[i].rect.top - height;  dy = 0; on_ground = true;   }
					//if (Dy < 0) { y = obj[i].rect.top + obj[i].rect.height;   dy = 0; }
					//if (Dx > 0) { x = obj[i].rect.left - width; }
					//if (Dx < 0) { x = obj[i].rect.left + obj[i].rect.width; }
				}
				if (obj[i].name == "grass")
					cout << "No" << endl;
			}
		}
	}
};


int main()
{
	RenderWindow window(VideoMode(800, 600), "SFML works!");
	View view;
	view.reset(FloatRect(0, 0, 800, 600));

	Level level;
	level.LoadFromFile("map.tmx");

	Image hero_image;
	hero_image.loadFromFile("textures/heroes/lol.png");

	Player player(hero_image, 250, 250, 125, 125, level);

	Clock clock;

	while (window.isOpen())
	{
		float time = clock.getElapsedTime().asMicroseconds();
		clock.restart();
		time = time / 800;

		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();
		}
		if (Mouse::isButtonPressed(Mouse::Right))
		{

			Vector2i totalMovement;
			totalMovement.x = Mouse::getPosition(window).x - player.sprite.getPosition().x;
			totalMovement.y = Mouse::getPosition(window).y - player.sprite.getPosition().y;
			Vector2f pos = window.mapPixelToCoords(totalMovement);

			player.checkStep(pos);

			float dx, dy = player.speed;

			player.checkCollisionWithMap(pos.x, pos.y);
			//player.checkCollisionWithMap(0, dy);

			if (player.lookAtMouse(pos.x, pos.y) == look::up)
			{
				player.animation(time, pos, 250);
			}
			else if (player.lookAtMouse(pos.x, pos.y) == look::down)
			{
				player.animation(time, pos, 750);
			}
			else if (player.lookAtMouse(pos.x, pos.y) == look::left)
			{
				player.animation(time, pos,   0);
			}
			else if (player.lookAtMouse(pos.x, pos.y) == look::right)
			{
				player.animation(time, pos, 500);
			}
			else if (player.lookAtMouse(pos.x, pos.y) == look::downright)
			{
				player.animation(time, pos, 625);
			}
			else if (player.lookAtMouse(pos.x, pos.y) == look::upright)
			{
				player.animation(time, pos, 375);
			}
			else if (player.lookAtMouse(pos.x, pos.y) == look::upleft)
			{
				player.animation(time, pos, 125);
			}
			else if (player.lookAtMouse(pos.x, pos.y) == look::downleft)
			{
				player.animation(time, pos, 875);
			}

		}

		view.setCenter(player.sprite.getPosition());
		window.setView(view);

		window.clear(Color(77, 83, 140));
		level.Draw(window);

		window.draw(player.sprite);
		window.display();
	}

	return 0;
}
