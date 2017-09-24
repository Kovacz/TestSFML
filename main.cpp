#include <iostream>
#include <sstream>
#include <cmath>
#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>
#define PI 3.14159265358979f
#define MTR_2PI_F 6.283185307179586f
#define MTR_RADIAN_F 57.295779513082320876798154814105f
#define step 100

using namespace sf;
using namespace std;

enum look
{
	right, left, down, up, downRight, upRight, upLeft, downLeft
};

class Entity
{
public:
	float x, y, frame, speed;
	int width, height;
	bool isMove;
	Texture texture;
	Sprite sprite;

	Entity(Image &image, float dx, float dy, int w, int h) : x(dx), y(dy), width(w), height(h), frame(0.f), speed(7.f), isMove(false)
	{
		texture.loadFromImage(image);
		sprite.setTexture(texture);
		sprite.setOrigin(w / 2.f, h / 2.f);
		sprite.setPosition(dx, dy);
		sprite.setTextureRect(IntRect(500, 750, w, h));
	}

	void animation(float &time, Vector2f &totalMovement, int scale)
	{
		frame += time * speed;
		if (frame > 8)
			frame -= 8;
		sprite.setTextureRect(IntRect(127 * int(frame), scale, width, height));
		sprite.move(totalMovement);
	}

	void update(Vector2f mouseCoords, float deltaTime)
	{
		x = sprite.getPosition().x;
		y = sprite.getPosition().y;

		float distance = sqrt(pow(mouseCoords.x - x, 2) + pow(mouseCoords.y - y, 2));
		float angleInRadians = atan2(mouseCoords.y - y, mouseCoords.x - x);
		float angle = angleInRadians * 180 / PI;

		Vector2f movement = Vector2f(cos(angleInRadians), sin(angleInRadians));

		const float DEAD_ZONE = 2;
		if (distance > DEAD_ZONE)
		{
			if (lookAtMouse(angle) == look::up)
			{
				animation(deltaTime, movement, 250);
			}
			else if (lookAtMouse(angle) == look::down)
			{
				animation(deltaTime, movement, 750);
			}
			else if (lookAtMouse(angle) == look::left)
			{
				animation(deltaTime, movement, 0);
			}
			else if (lookAtMouse(angle) == look::right)
			{
				animation(deltaTime, movement, 500);
			}
			else if (lookAtMouse(angle) == look::downRight)
			{
				animation(deltaTime, movement, 625);
			}
			else if (lookAtMouse(angle) == look::upRight)
			{
				animation(deltaTime, movement, 375);
			}
			else if (lookAtMouse(angle) == look::upLeft)
			{
				animation(deltaTime, movement, 125);
			}
			else if (lookAtMouse(angle) == look::downLeft)
			{
				animation(deltaTime, movement, 875);
			}
		}
		else { isMove = false; cout << "G" << endl; }
	}

	look lookAtMouse(float angle)
	{
		if (angle > -30.f && angle <= 30.f)
		{
			return look::right;
		}
		if (angle > 70.f && angle <= 120.f)
		{
			return look::down;
		}
		if (angle > 160.f && angle <= 180.f)
		{
			return look::left;
		}
		if (angle > -180.f && angle <= -160.f)
		{
			return look::left;
		}
		if (angle > -120.f && angle <= -80.f)
		{
			return look::up;
		}
		if (angle > 30.f && angle <= 70.f)
		{
			return look::downRight;
		}
		if (angle > -80.f && angle <= -30.f)
		{
			return look::upRight;
		}
		if (angle > -160.f && angle <= -120.f)
		{
			return look::upLeft;
		}
		if (angle > 120.f && angle <= 160.f)
		{
			return look::downLeft;
		}
	}
};


int main()
{
	RenderWindow window(VideoMode(800, 600), "SFML works!");
	//window.setFramerateLimit(60);

	View view;
	view.reset(FloatRect(0, 0, 800, 600));

	Texture tile;
	tile.loadFromFile("textures/map/grassland/grassland.png");
	tile.setSmooth(true);

	Sprite floor(tile);
	floor.setPosition(350, 250);
	floor.setTextureRect(IntRect(0, 0, 64, 32));

	Image hero_image;
	hero_image.loadFromFile("textures/heroes/lol.png");
	
	Entity player(hero_image, 0, 250, 125, 125);

	Clock clock;
	float time = 0.f;
	float deltaTime = 0.01f;

	float currentTime = clock.getElapsedTime().asSeconds();
	float accumulator = 0.f;

	float tempX = 0.f, tempY = 0.f;
	Vector2f pos;
	////////////////////////////////////////
	while (window.isOpen())
	{
		Vector2i mouseCoord = Mouse::getPosition(window);
		Vector2f pixelPos = window.mapPixelToCoords(mouseCoord);
		////////////////////////////////////
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();
		}
		////////////////////////////////////
		float newTime = clock.getElapsedTime().asSeconds();
		float frameTime = newTime - currentTime;
		currentTime = newTime;
		accumulator += frameTime;
		////////////////////////////////////
		while (accumulator >= deltaTime)
		{

			if (Mouse::isButtonPressed(Mouse::Right))
			{
				player.isMove = true;
				pos = pixelPos;
			}

			if (player.isMove)
			{
				player.update(pos, deltaTime);
			}


			accumulator -= deltaTime;
			time += deltaTime;
		}

		view.setCenter(player.sprite.getPosition());
		window.setView(view);	
		window.clear(Color(77, 83, 140));
		window.draw(floor);
		window.draw(player.sprite);

		window.display();
		//cout << "FPS: " <<  1.f / frameTime << endl;
	}

	return 0;
}
