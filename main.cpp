#include <iostream>
#include <sstream>
#include <cmath>
#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>
#define PI 3.14159265358979f
#define MTR_2PI_F 6.283185307179586f
#define MTR_RADIAN_F 57.295779513082320876798154814105f
#define step 100

const int HEIGHT_MAP = 25;
const int WIDTH_MAP = 40;
const int tile_size = 32;

using namespace sf;
using namespace std;

enum look
{
	right, left, down, up, downRight, upRight, upLeft, downLeft
};

String TileMap[HEIGHT_MAP] = {
	"0000000000000000000000000000000000000000",
	"0                                      0",
	"0   s                                  0",
	"0                                      0",
	"0                                      0",
	"0                                      0",
	"0                                      0",
	"0                                      0",
	"0                                      0",
	"0                                      0",
	"0                                      0",
	"0                                      0",
	"0                                      0",
	"0                                      0",
	"0                                      0",
	"0                                      0",
	"0                                      0",
	"0                                      0",
	"0                                      0",
	"0                                      0",
	"0                                      0",
	"0                                      0",
	"0                                      0",
	"0                                      0",
	"0000000000000000000000000000000000000000",
};

class Entity
{
public:
	float x, y, frame, speed, angle;
	int width, height;
	bool isMove;
	Texture texture;
	Sprite sprite;

	Entity(Image &image, float dx, float dy, int w, int h) : x(dx), y(dy), width(w), height(h), frame(0.f), speed(7.f), isMove(false)
	{
		texture.loadFromImage(image);
		sprite.setTexture(texture);
		//sprite.setOrigin(w / 2.f, h / 2.f);
		sprite.setPosition(dx, dy);
		sprite.setTextureRect(IntRect(500, 750, w, h));
	}

	FloatRect getRect() {
		return FloatRect(x, y, width, height);
	}

	void animation(float &time, Vector2f &totalMovement, int scale)
	{
		frame += time * speed;
		if (frame > 8)
			frame -= 8;
		sprite.setTextureRect(IntRect(127 * int(frame), scale, width, height));
		sprite.move(totalMovement );
	}

	void update(Vector2f mouseCoords, float deltaTime)
	{
		x = sprite.getPosition().x;
		y = sprite.getPosition().y;

		float distance = sqrt(pow(mouseCoords.x - x, 2) + pow(mouseCoords.y - y, 2));
		float angleInRadians = atan2(mouseCoords.y - y, mouseCoords.x - x);
		angle = angleInRadians * 180 / PI;

		Vector2f movement = Vector2f(cos(angleInRadians), sin(angleInRadians));

		const float DEAD_ZONE = 2;
		if (distance > DEAD_ZONE) {

			int scale_values[] = {
				/* right*/        500,
				/* left*/           0,
				/* down*/         750,
				/* up*/           250,
				/* downRight*/    625,
				/* upRight*/      375,
				/* upLeft*/       125,
				/* downLeft*/     875
			};

			animation(deltaTime, movement, scale_values[lookAtMouse(angle)]);

		} else { 
			isMove = false; 
			cout << "G" << endl; 
		}
	}

	look lookAtMouse(float angle)
	{
		int breaking_values[][2] = {
			{ -160, look::left },
			{ -120, look::upLeft },
			{ -80 , look::up },
			{ -30 , look::upRight },
			{  30 , look::right },
			{  70 , look::downRight },
			{  120, look::down },
			{  160, look::downLeft },
			{  180, look::left }
		};

		if (angle > -180.f) {
			for (int i = 0; i < sizeof(breaking_values) / sizeof(breaking_values[0]); ++i) {
				if (static_cast<int>(angle) <= breaking_values[i][0]) { 
					return static_cast<look>(breaking_values[i][1]);
				}
			}
		} else {
			cout << "Error" << endl;
		}
	}

	void interactionWithMap()
	{
		for (int i = y / tile_size; i < (y + height) / tile_size; ++i) {
			for (int j = x / tile_size; j < (x + width) / tile_size; ++j) {
				if (TileMap[i][j] == '0') {
					if (lookAtMouse(angle) == look::down) {
						sprite.setPosition(sprite.getPosition().x, i * tile_size - height);
					}
					if (lookAtMouse(angle) == look::up) {
						sprite.setPosition(sprite.getPosition().x, i * tile_size + tile_size);
					}
					if (lookAtMouse(angle) == look::right) {
						sprite.setPosition(j * tile_size - width, sprite.getPosition().y);
					}
					if (lookAtMouse(angle) == look::left) {
						sprite.setPosition(j * tile_size + tile_size, sprite.getPosition().y);
					}
				}
				if (TileMap[i][j] == 's') { 
					TileMap[i][j] = ' ';
				}
			}
		}
	}
};


int main()
{
	RenderWindow window(VideoMode(800, 600), "SFML works!");
	//window.setFramerateLimit(60);

	View view;
	view.reset(FloatRect(0, 0, 800, 600));
	Image hero_image;
	hero_image.loadFromFile("textures/heroes/lol.png");
	Image map_image;
	map_image.loadFromFile("textures/map/map.png");
	Texture map;
	map.loadFromImage(map_image);
	Sprite s_map;
	s_map.setTexture(map);
	
	Entity player(hero_image, 250, 250, 125, 125);

	Clock clock;
	float time = 0.f;
	float deltaTime = 0.01f;

	float currentTime = clock.getElapsedTime().asSeconds();
	float accumulator = 0.f;

	float tempX = 0.f, tempY = 0.f;
	Vector2f pos;
	////////////////////////////////////////
	while (window.isOpen()) {
		Vector2i mouseCoord = Mouse::getPosition(window);
		Vector2f pixelPos = window.mapPixelToCoords(mouseCoord);
		////////////////////////////////////
		Event event;
		while (window.pollEvent(event)) {
			if (event.type == Event::Closed) {
				window.close();
			}
		}
		////////////////////////////////////
		float newTime = clock.getElapsedTime().asSeconds();
		float frameTime = newTime - currentTime;
		currentTime = newTime;
		accumulator += frameTime;
		////////////////////////////////////
		while (accumulator >= deltaTime) {

			if (Mouse::isButtonPressed(Mouse::Right)) {
				player.isMove = true;
				pos = pixelPos;
			}

			if (player.isMove) {
				player.update(pos, deltaTime);
			}

			player.interactionWithMap();

			accumulator -= deltaTime;
			time += deltaTime;
		}

		view.setCenter(player.sprite.getPosition());
		window.setView(view);	
		window.clear(Color(77, 83, 140));

		////////////////////////////////////
		for (int i = 0; i < HEIGHT_MAP; i++) {
			for (int j = 0; j < WIDTH_MAP; j++) {
				if (TileMap[i][j] == ' ') {
					s_map.setTextureRect(IntRect(0, 0, tile_size, tile_size));
				}
				if (TileMap[i][j] == 's') {
					s_map.setTextureRect(IntRect(tile_size, 0, tile_size, tile_size));
				}
				if (TileMap[i][j] == '0') {
					s_map.setTextureRect(IntRect(64, 0, tile_size, tile_size));
				}
				s_map.setPosition(static_cast<float>(j * tile_size), static_cast<float>(i * tile_size));
				window.draw(s_map);
			}
		}
		////////////////////////////////////
		window.draw(player.sprite);

		window.display();
		//cout << "FPS: " <<  1.f / frameTime << endl;
	}

	return 0;
}
