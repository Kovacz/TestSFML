#include <SFML/Graphics.hpp>
using sf::Keyboard;
sf::View view;
void setPlayerCoordinateForView(float x, float y) {
	float tempX = x; float tempY = y;
	//if (x < 320) tempX = 320;
	//if (y < 240) tempY = 240;//������� �������
	if (y > 624) tempY = 624;//������ �������.��� ����� �����
	view.setCenter(tempX, tempY);
}

void viewmap(float time) { //������� ��� ����������� ������ �� �����. ��������� ����� sfml


	if (Keyboard::isKeyPressed(Keyboard::D)) {
		view.move(0.5*time, 0);//�������� ����� ������ (�� ����, ����� �� ������� ����� - �� ���� �����)
	}

	if (Keyboard::isKeyPressed(Keyboard::S)) {
		view.move(0, 0.5*time);//�������� ����� ���� (�� ����, ����� �� ������� ����� - �� ���� �����)
	}

	if (Keyboard::isKeyPressed(Keyboard::A)) {
		view.move(-0.5*time, 0);//�������� ����� ����� (�� ����, ����� �� ������� ����� - �� ���� �����)
	}
	if (Keyboard::isKeyPressed(Keyboard::W)) {
		view.move(0, -0.5*time);//�������� ����� ������ (�� ����, ����� �� ������� ����� - �� ���� �����)
	}


}