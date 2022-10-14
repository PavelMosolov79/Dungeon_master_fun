#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <windows.h>
using namespace sf;

void menu(RenderWindow & window) 
{
	Music bgMusic;
	bgMusic.openFromFile("Music/glavnoe_menu_MP3.ogg");
	bgMusic.play();
	bgMusic.setVolume(10.f);
	
	SoundBuffer Klick_button;
	Klick_button.loadFromFile("Music/Klick_button.WAV");
	Sound Button(Klick_button);

	Texture menuBackground,
			menuBackground2,
			eye,
			eye2, 
			button_1, 
			button_2, 
			button_1press, 
			button_2press, 
			fire1, 
			fire2, 
			fire3;
	button_1.loadFromFile("Image/Sprite-button_newgame.png");
	button_2.loadFromFile("Image/Sprite-button_endgame.png");
	button_1press.loadFromFile("Image/Sprite-button_newgame_press.png");
	button_2press.loadFromFile("Image/Sprite-button_endgame_press.png");
	fire1.loadFromFile("Image/Sprite-fire_1.png");
	fire2.loadFromFile("Image/Sprite-fire_2.png");
	fire3.loadFromFile("Image/Sprite-fire_3.png");
	menuBackground.loadFromFile("Image/Sprite-mainpage(-fire).png");
	menuBackground2.loadFromFile("Image/Sprite-mainpage(-fire2).png");
	eye.loadFromFile("Image/eye.png");
	eye2.loadFromFile("Image/eye2.png");
	Sprite but_1(button_1), 
			but_2(button_2), 
			but_1_pr(button_1press), 
			but_2_pr(button_2press), 
			fi1(fire1), fi2(fire2), fi3(fire3),
			menuBg(menuBackground),
			menuBg2(menuBackground2),
			Eye(eye),
			Eye2(eye2);
	bool isMenu = 1;
	int NumMenu = 0;
	but_1.setPosition(100, 100);
	but_2.setPosition(100, 190);
	fi1.setPosition(150, 570);
	fi2.setPosition(150, 570);
	fi3.setPosition(150, 570);
	menuBg.setPosition(0, 0); 
	menuBg2.setPosition(0, 0);
	Eye.setPosition(0, 0);
	Eye2.setPosition(0, 0);
	
	int x=0, rand=0;
	
	while (isMenu)
	{
		x++; rand++;
		Event event; //объект event
		while(window.pollEvent(event))
		{
			if(event.type==Event::Event::Closed)
			{
				bgMusic.stop();
				window.close();
			}
		}
		NumMenu = 0;
 		but_1.setTexture(button_1);
		but_2.setTexture(button_2);
		fi1.setTexture(fire1);
		
		if (IntRect(100, 100, 256, 64).contains(Mouse::getPosition(window))) { but_1.setTexture(button_1press); }
		if (IntRect(100, 190, 256, 64).contains(Mouse::getPosition(window))) { but_2.setTexture(button_2press);	}
		
		if(event.type==Event::MouseButtonPressed)
		{
			if(	but_1.getGlobalBounds().contains(Mouse::getPosition(window).x,Mouse::getPosition(window).y))
			{
				but_1.setTexture(button_1press);
				Button.play();
				NumMenu=1;
			} 
			if(	but_2.getGlobalBounds().contains(Mouse::getPosition(window).x,Mouse::getPosition(window).y))
			{
				but_2.setTexture(button_2press);
				Button.play();
				NumMenu=2;
			}	
		}
		if (Mouse::isButtonPressed(Mouse::Left))
		{
			if (NumMenu == 1) {/*Sleep(2300);*/ isMenu = false; bgMusic.stop();}
			if (NumMenu == 2) {Sleep(2300); window.close(); bgMusic.stop(); isMenu = false; }
		}
		if(rand>0 && rand<3000) {
			window.draw(Eye);
		}
		if(rand>3001 && rand<6000) {
			window.draw(Eye2);
		}
		if(rand>6001 && rand<9000) {
			window.draw(menuBg);
		}
		if(rand>9001 && rand<10000) {
			window.draw(menuBg2);
		}
		window.draw(but_1);
		window.draw(but_2);
		if(x>0 && x<500) {
			window.draw(fi1);
		} 
		if(x>501 && x<1000) {
			window.draw(fi2);
		}
		if(x>1001 && x<1500) {
			window.draw(fi3);
		}
		if(rand==10000) {
			rand=rand-10000;
		}
		if(x==1500){
			x=x-1500;
		}
		window.display();
	}
}
