#include <SFML/Graphics.hpp>
using sf::Keyboard;
sf::View view;
void setPlayerCoordinateForView(float x, float y) {
	float tempX = x; float tempY = y;
	//if (x < 320) tempX = 320;
	//if (y < 240) tempY = 240;//верхнюю сторону
	if (y > 624) tempY = 624;//нижнюю стороню.для новой карты
	view.setCenter(tempX, tempY);
}

void viewmap(float time) { //функция для перемещения камеры по карте. принимает время sfml


	if (Keyboard::isKeyPressed(Keyboard::D)) {
		view.move(0.5*time, 0);//скроллим карту вправо (см урок, когда мы двигали героя - всё тоже самое)
	}

	if (Keyboard::isKeyPressed(Keyboard::S)) {
		view.move(0, 0.5*time);//скроллим карту вниз (см урок, когда мы двигали героя - всё тоже самое)
	}

	if (Keyboard::isKeyPressed(Keyboard::A)) {
		view.move(-0.5*time, 0);//скроллим карту влево (см урок, когда мы двигали героя - всё тоже самое)
	}
	if (Keyboard::isKeyPressed(Keyboard::W)) {
		view.move(0, -0.5*time);//скроллим карту вправо (см урок, когда мы двигали героя - всё тоже самое)
	}


}