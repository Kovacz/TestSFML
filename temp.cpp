//#include <iostream>
//#include <SFML\Graphics.hpp>
//
//using namespace sf;
//
//int main()
//{
//	RenderWindow window(sf::VideoMode(800, 600), "Test Game");
//
//	Texture hero_texture;
//	hero_texture.loadFromFile("textures/hero.png");
//
//	Sprite hero_sprite;
//	hero_sprite.setTexture(hero_texture);
//	hero_sprite.setTextureRect(sf::IntRect(0, 192, 96, 96));
//	hero_sprite.setPosition(50, 25);
//
//	double CurrentFrame = 0;
//	Clock clock;
//
//	while (window.isOpen())
//	{
//		double time = clock.getElapsedTime().asMicroseconds(); //дать прошедшее время в микросекундах
//		clock.restart();   //перезагружает время
//		time = time / 800; //скорость игры
//
//		Event event;
//		while (window.pollEvent(event))
//		{
//			if (event.type == Event::Closed)
//				window.close();
//		}
//
//		if (Keyboard::isKeyPressed(Keyboard::A))
//		{
//			CurrentFrame += 0.005 * time; //служит для прохождения по "кадрам". переменная доходит до трех суммируя произведение времени и скорости. изменив 0.005 можно изменить скорость анимации
//			if (CurrentFrame > 3) CurrentFrame -= 3; //проходимся по кадрам с первого по третий включительно. если пришли к третьему кадру - откидываемся назад.
//			hero_sprite.setTextureRect(IntRect(96 * int(CurrentFrame), 96, 96, 96)); //проходимся по координатам Х. получается 96,96*2,96*3 и опять 96
//			hero_sprite.move(-0.1*time, 0);//происходит само движение персонажа влево
//		}
//
//		if (Keyboard::isKeyPressed(Keyboard::D))
//		{
//			CurrentFrame += 0.005*time; //служит для прохождения по "кадрам". переменная доходит до трех суммируя произведение времени и скорости. изменив 0.005 можно изменить скорость анимации
//			if (CurrentFrame > 3) CurrentFrame -= 3; //проходимся по кадрам с первого по третий включительно. если пришли к третьему кадру - откидываемся назад.
//			hero_sprite.setTextureRect(IntRect(96 * int(CurrentFrame), 192, 96, 96)); //проходимся по координатам Х. получается 96,96*2,96*3 и опять 96
//
//			hero_sprite.move(0.1*time, 0);//происходит само движение персонажа вправо
//
//		}
//
//		if (Keyboard::isKeyPressed(Keyboard::W))
//		{
//			CurrentFrame += 0.005*time; //служит для прохождения по "кадрам". переменная доходит до трех суммируя произведение времени и скорости. изменив 0.005 можно изменить скорость анимации
//			if (CurrentFrame > 3) CurrentFrame -= 3; //проходимся по кадрам с первого по третий включительно. если пришли к третьему кадру - откидываемся назад.
//			hero_sprite.setTextureRect(IntRect(96 * int(CurrentFrame), 288, 96, 96)); //проходимся по координатам Х. получается 96,96*2,96*3 и опять 96
//			hero_sprite.move(0, -0.1*time);//происходит само движение персонажа вверх
//		}
//
//		if (Keyboard::isKeyPressed(Keyboard::S))
//		{
//			CurrentFrame += 0.005*time; //служит для прохождения по "кадрам". переменная доходит до трех суммируя произведение времени и скорости. изменив 0.005 можно изменить скорость анимации
//			if (CurrentFrame > 3) CurrentFrame -= 3; //проходимся по кадрам с первого по третий включительно. если пришли к третьему кадру - откидываемся назад.
//			hero_sprite.setTextureRect(IntRect(96 * int(CurrentFrame), 0, 96, 96)); //проходимся по координатам Х. получается 96,96*2,96*3 и опять 96
//			hero_sprite.move(0, 0.1*time);//происходит само движение персонажа вниз
//		}
//
//		window.clear();
//		window.draw(hero_sprite);
//		window.display();
//	}
//
//	return 0;
//}