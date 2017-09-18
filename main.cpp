#include <iostream>
#include <sstream>
#include <SFML/Graphics.hpp>
#define MTR_2PI_F 6.283185307179586f
#define MTR_RADIAN_F 57.295779513082320876798154814105f
#define step 100

using namespace sf;
using namespace std;

const float SCALE = 30.f;

b2Vec2 Gravity(0.f, 0.f);
b2World World(Gravity);

enum look
{
	right, left, down, up, downRight, upRight, upLeft, downLeft
};

class Entity
{
public:
	float x, y, frame, speed;
	int width, height;
	Texture texture;
	Sprite sprite;

	Entity(Image &image, float dx, float dy, int w, int h) : x(dx), y(dy), width(w), height(h), frame(0.f), speed(7.f)
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

	void update(RenderWindow &window, float deltaTime)
	{
		Vector2i totalMovement;
		totalMovement.x = Mouse::getPosition(window).x - sprite.getPosition().x;
		totalMovement.y = Mouse::getPosition(window).y - sprite.getPosition().y;
		Vector2f pos = window.mapPixelToCoords(totalMovement);

		pos /= std::sqrt(std::pow(pos.x, 2) + std::pow(pos.y, 2));

		if (lookAtMouse(pos.x, pos.y) == look::up)
		{
			animation(deltaTime, pos, 250);
		}
		else if (lookAtMouse(pos.x, pos.y) == look::down)
		{
			animation(deltaTime, pos, 750);
		}
		else if (lookAtMouse(pos.x, pos.y) == look::left)
		{
			animation(deltaTime, pos, 0);
		}
		else if (lookAtMouse(pos.x, pos.y) == look::right)
		{
			animation(deltaTime, pos, 500);
		}
		else if (lookAtMouse(pos.x, pos.y) == look::downRight)
		{
			animation(deltaTime, pos, 625);
		}
		else if (lookAtMouse(pos.x, pos.y) == look::upRight)
		{
			animation(deltaTime, pos, 375);
		}
		else if (lookAtMouse(pos.x, pos.y) == look::upLeft)
		{
			animation(deltaTime, pos, 125);
		}
		else if (lookAtMouse(pos.x, pos.y) == look::downLeft)
		{
			animation(deltaTime, pos, 875);
		}
	}

	float mtrAngle_f(float x, float y)
	{
		float dir;
		dir = acosf(x / sqrtf(powf(-x, 2.0f) + powf(-y, 2.0f)));
		if (y > 0.0f) { dir = MTR_2PI_F - dir; }
	
		return dir * MTR_RADIAN_F;
	}

	look lookAtMouse(float x, float y)
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
			return look::downRight;
		}
		if (direction > 22.5f && direction <= 67.5f)
		{
			return look::upRight;
		}
		if (direction > 90.5f && direction <= 170.5f)
		{
			return look::upLeft;
		}
		if (direction > 210.5f && direction <= 250.5f)
		{
			return look::downLeft;
		}
	}
};


bool intersects(float x11, float y11, float x12, float y12, float x21, float y21, float x22, float y22)
{

	float maxx1 = max(x11, x12), maxy1 = max(y11, y12);
	float minx1 = min(x11, x12), miny1 = min(y11, y12);
	float maxx2 = max(x21, x22), maxy2 = max(y21, y22);
	float minx2 = min(x21, x22), miny2 = min(y21, y22);

	if (minx1 > maxx2 || maxx1 < minx2 || miny1 > maxy2 || maxy1 < miny2)
		return false; // відрізки мають спільну вершину


	float dx1 = x12 - x11, dy1 = y12 - y11; 
	float dx2 = x22 - x21, dy2 = y22 - y21; 
	float dxx = x11 - x21, dyy = y11 - y21;
	float div, mul;


	if ((div = dy2 * dx1 - dx2 * dy1) == 0)
		return false; // відрізки паралельні
	if (div > 0) 
	{
		if ((mul = dx1  *dyy - dy1 * dxx) < 0 || mul > div)
			return false;
		if ((mul = dx2 * dyy - dy2 * dxx) < 0 || mul > div)
			return false;
	}

	if ((mul = -(dx1 * dyy - dy1 * dxx)) < 0 || mul > -div)
		return false;
	if ((mul = -(dx2 * dyy - dy2 * dxx)) < 0 || mul > -div)
		return false;

	return true;
}

int main()
{
	RenderWindow window(VideoMode(800, 600), "SFML works!");
	
	View view;
	view.reset(FloatRect(0, 0, 800, 600));

	Texture tile;
	tile.loadFromFile("textures/map/grassland/grassland.png");
	tile.setSmooth(true);

	Sprite floor(tile);
	floor.setTextureRect(IntRect(0, 0, 64, 32));
	floor.setOrigin(64 / 2, 32 / 2);

	Image hero_image;
	hero_image.loadFromFile("textures/heroes/lol.png");
	
	Entity player(hero_image, 0, 250, 125, 125);

	float x = 250.f;
	float y = 250.f;
	int width = 164;
	int height = 132;
	/////////Координати лівого верхнього кута
	float x1 = x;
	float y1 = y;
	/////////Координати правого верхнього кута
	float x2 = x + width;
	float y2 = y;
	/////////Координати нижнього лівого кута
	float x3 = x;
	float y3 = y + height;
	/////////Координати нижнього правого кута
	float x4 = x + width;
	float y4 = y + height;
	/////////Вершини в ізометрії
	Vector2f leftTop((x1 - y1), (x1 + y1) / 2);
	Vector2f rightTop((x2 - y2), (x2 + y2) / 2);
	Vector2f leftDown((x3 - y3), (x3 + y3) / 2);
	Vector2f rightDown((x4 - y4), (x4 + y4) / 2);
	float ix1 = x1 - y1,	 iy1 = (x1 + y1) / 2;
	float ix2 = x2 - y2,	 iy2 = (x2 + y2) / 2;
	float ix3 = x3 - y3,	 iy3 = (x3 + y3) / 2;
	float ix4 = x4 - y4,	 iy4 = (x4 + x4) / 2;
	/////////Візуалізація 
	Vertex vertices[] =
	{
		sf::Vertex(sf::Vector2f(leftTop), sf::Color::Red),
		sf::Vertex(sf::Vector2f(rightTop), sf::Color::Red),
		sf::Vertex(sf::Vector2f(rightDown), sf::Color::Red),
		sf::Vertex(sf::Vector2f(leftDown), sf::Color::Red)
	};


	Clock clock;
	float time = 0.f;
	 float deltaTime = 0.01f;

	float currentTime = clock.getElapsedTime().asSeconds();
	float accumulator = 0.f;
	////////////////////////////////////////
	while (window.isOpen())
	{
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

		while (accumulator >= deltaTime)
		{

			if (Mouse::isButtonPressed(Mouse::Right))
			{
				player.x = player.sprite.getPosition().x;
				player.y = player.sprite.getPosition().y;
				if (//intersects(player.x, player.y, (player.x + player.width), player.y, ix2, iy2, ix1, iy1)
				//|| intersects(player.x, player.y, player.x + (player.width/2), player.y, ix3, iy3, ix1, iy1)
				//|| intersects(player.x, player.y, (player.x + (player.width/2)), player.y, ix4, iy4, ix3, iy3)
				     intersects(player.x, player.y, (player.x + player.width), player.y, ix4, iy4, ix2, iy2)
				    )
					cout << "True" << endl;
				else
					cout << "False" << endl;

				player.update(window, deltaTime);
				
			
			}

			accumulator -= deltaTime;
			time += deltaTime;
		}

		view.setCenter(player.sprite.getPosition());
		window.setView(view);	
		window.clear(Color(77, 83, 140));
		window.draw(player.sprite);
		window.draw(vertices, 4, sf::Quads);

		window.display();
	}

	return 0;
}
