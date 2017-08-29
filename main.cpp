#include "level.h"
#include "view.h"

int main()
{
	Level level;
	level.LoadFromFile("map.tmx");

	sf::RenderWindow window(sf::VideoMode(800, 600), "Test");
	view.reset(sf::FloatRect(0, 0, 800, 600));

	sf::Clock clock;
	while (window.isOpen())
	{
		float time = clock.getElapsedTime().asMicroseconds();
		clock.restart();
		time = time / 800;

		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		viewmap(time);//функция скроллинга карты, передаем ей время sfml
		window.setView(view);
		window.clear(sf::Color(77, 83, 140));
		level.Draw(window);//"оживляем" камеру в окне sfml
		//window.clear();
		window.display();

	}

	return 0;
}