#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Map_1.h"
#include "menu.h"
#include "player_class.h"
#include <iostream>
#include <vector>
using namespace sf;

int main() {
	RenderWindow window(sf::VideoMode(1216, 672), "DungeonMaster");
	
	Image icon;
    icon.loadFromFile("Image/Guchi.png");
    window.setIcon(64,64,icon.getPixelsPtr());
		menu(window);//����� ����
		level1(window);//����� 1 ������
		menu(window);//����� ����
		level1(window);//����� 1 ������
		menu(window);//����� ����
		level1(window);//����� 1 ������
 return 0;
}
