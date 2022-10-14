#include <SFML/Graphics.hpp>
#include "Map.h"
#include "player_class.h"
#include <sstream>
#include <locale.h>
#include <iostream>
#include <list>
#include <vector>
#include <windows.h>

using namespace sf;

void level1(RenderWindow & window) 
{
	setlocale(LC_ALL, "Russian");
	
	Font font;
	font.loadFromFile("Font/font.ttf");
	
	Text text("", font, 20);
	text.setStyle(Text::Bold);
	
	Text text2("", font, 50);
	text2.setStyle(Text::Bold);
	
	Texture button_1, button_2, button_1press, button_2press;
	button_1.loadFromFile("Image/Sprite-button_restart.png");
	button_2.loadFromFile("Image/Sprite-button_endgame.png");
	button_1press.loadFromFile("Image/Sprite-button_restart_press.png");
	button_2press.loadFromFile("Image/Sprite-button_endgame_press.png");
	Sprite but_1(button_1), but_2(button_2), but_1_pr(button_1press), but_2_pr(button_2press);
	bool isMen = true;
	int NumMenu = 0;
	but_1.setPosition(500, 100);
	but_2.setPosition(500, 220);
	
	Music Level_1;
	Level_1.openFromFile("Music/level_1_MP3.ogg");
	Level_1.setVolume(5.f);
	Level_1.setLoop(true);
	Level_1.play();
	
	SoundBuffer Klick_button;
	Klick_button.loadFromFile("Music/Klick_button.WAV");
	Sound Button(Klick_button);
	
	Image map_image;
	map_image.loadFromFile("Image/Sprite-newtekstyre2.png");
	Texture map;
	map.loadFromImage(map_image);
	Sprite s_map;
	s_map.setTexture(map);
	
	Image heroImage;
	heroImage.loadFromFile("Image/Sprite.png");
 
	Image easyEnemyImage;
	easyEnemyImage.loadFromFile("Image/Sprite-monster.png");
	
	Image BombImage;
	BombImage.loadFromFile("Image/Sprite-bomb.png");
 	
	Player p(heroImage, 558, 264, 50, 72,"Player1");
	////////////////////////ÒÎÒÀËÜÍÛÉ ÏÈÇÄÅÖ/////////////////////////
	Enemy easyEnemy(easyEnemyImage, 300, 300, 98, 136,"EasyEnemy");
	Enemy easyEnemy2(easyEnemyImage, 500, 500, 98, 136,"EasyEnemy");
	Bullet bomb(BombImage, 558, 264, 32, 32,"EasyEnemy");
	
	float CurrentFrame=0;
	float CurrentFrameMob=0;
	float CurrentFrameMob2=0;
	Clock clock;
	Clock gameTimeClock;
	int gameTime = 0;	
	bool right = true;
	bool left = false;
	bool up = false;
	bool down = false;
	bool right2 = false;
	bool left2 = false;
	bool up2 = true;
	bool down2 = false;
	bool BOMB = false;
	const int steps=500;
	int sled=0;
	const int steps2=500;
	int sled2=0;

	while (isMen) {
		if(p.health == 0) {
			p.life = false;
		}
		float time = clock.getElapsedTime().asMicroseconds();
		if (p.life) gameTime=gameTimeClock.getElapsedTime().asSeconds();
		clock.restart();
		time = time / 800;
		Event event;
		while (window.pollEvent(event)) {
			if (event.type == Event::Closed){
				window.close();
				Level_1.stop();
			}
		}

		if (Keyboard::isKeyPressed(Keyboard::Space)) 
		{
			BOMB = true;
			bomb.x = p.x;
			bomb.y = p.y + 32;
		}
		
		if (p.life) {
			if (Keyboard::isKeyPressed(Keyboard::Left)) {
				CurrentFrame += 0.005*time;
				if (CurrentFrame > 3) CurrentFrame -= 3;
				p.sprite.setTextureRect(IntRect(57*int(CurrentFrame),226,50,75));
			}
			if (Keyboard::isKeyPressed(Keyboard::Right)) {
				CurrentFrame += 0.005*time;
				if (CurrentFrame > 3) CurrentFrame -= 3;
				p.sprite.setTextureRect(IntRect(49*int(CurrentFrame),0,50,70));
			}
			if (Keyboard::isKeyPressed(Keyboard::Up)) {
				CurrentFrame += 0.005*time;
				if (CurrentFrame > 3) CurrentFrame -= 3;
				p.sprite.setTextureRect(IntRect(55*int(CurrentFrame),147,56,72));
			}
			if (Keyboard::isKeyPressed(Keyboard::Down)) {
				CurrentFrame += 0.005*time;
				if (CurrentFrame > 3) CurrentFrame -= 3;
				p.sprite.setTextureRect(IntRect(55*int(CurrentFrame),73,55,71));
			}
		}
		
		if(easyEnemy.getRect().intersects(p.getRect())) {
			easyEnemy.life = false;
			p.health = p.health - 50;
			easyEnemy.x = 0;
			easyEnemy.y = 0;
			p.x -= 30;
			p.y -= 30;
			p.playerScore -= 20;
		}
		if(easyEnemy.getRect().intersects(bomb.getRect())) {
			easyEnemy.health -= 50;
			easyEnemy.x -= 20;
			easyEnemy.y -= 20;
			bomb.x = 0;
			bomb.y = 0;
			p.playerScore += 40;
			BOMB = false;
		}
		if(easyEnemy2.getRect().intersects(bomb.getRect())) {
			easyEnemy2.health -= 50;
			easyEnemy.x -= 20;
			easyEnemy.y -= 20;
			bomb.x = 0;
			bomb.y = 0;
			p.playerScore += 40;
			BOMB = false;
		}
		if(easyEnemy2.getRect().intersects(p.getRect())) {
			easyEnemy2.life = false;
			p.health = p.health - 50;
			easyEnemy2.x = 0;
			easyEnemy2.y = 0;
			p.x -= 30;
			p.y -= 30;
			p.playerScore -= 20;
		}
		
		if(right) {
			++sled;
			if(easyEnemy2.x>p.x || sled>=steps) {
				sled=steps;
			}	
		}
		if(left) {
			++sled;
			if(easyEnemy2.x<p.x || sled>=steps) {
				sled=steps;
			}	
		}
		if(up) {
			++sled;
			if(easyEnemy2.y<p.y || sled>=steps) {
				sled=steps;
			}	
		}
		if(down) {
			++sled;
			if(easyEnemy2.y>p.y || sled>=steps) {
				sled=steps;
			}	
		}
		if(sled>=steps) {
			sled=0;
			if(!right && easyEnemy2.x<p.x-10) {
				easyEnemy2.dx=0.06;
				easyEnemy2.dy=0;
				
				right2 = true;
				left2 = false;
				up2 = false;
				down2 = false;
			}else if(!left && easyEnemy2.x>p.x+10) {
				easyEnemy2.dx=-0.06;
				easyEnemy2.dy=0;
				right2 = false;
				left2 = true;
				up2 = false;
				down2 = false;
			} 
			else if(!up && easyEnemy2.y>p.y+10) {
				easyEnemy2.dy=-0.06;
				easyEnemy2.dx=0;
				right2 = false;
				left2 = false;
				up2 = true;
				down2 = false;
			}
			else if(!down && easyEnemy2.y<p.y-10) {
				easyEnemy2.dy=0.06;
				easyEnemy2.dx=0;
				right = false;
				left = false;
				up = false;
				down = true;
			}
		}

		if(right) {
			++sled2;
			if(easyEnemy.x>p.x || sled2>=steps2) {
				sled2=steps2;
			}	
		}
		if(left) {
			++sled2;
			if(easyEnemy.x<p.x || sled2>=steps2) {
				sled2=steps2;
			}	
		}
		if(up) {
			++sled2;
			if(easyEnemy.y<p.y || sled2>=steps2) {
				sled2=steps2;
			}	
		}
		if(down) {
			++sled2;
			if(easyEnemy.y>p.y || sled2>=steps2) {
				sled2=steps2;
			}	
		}
		if(sled2>=steps2) {
			sled2=0;
			if(!right && easyEnemy.x<p.x-10) {
				easyEnemy.dx=0.06;
				easyEnemy.dy=0;
				
				right = true;
				left = false;
				up = false;
				down = false;
			}else if(!left && easyEnemy.x>p.x+10) {
				easyEnemy.dx=-0.06;
				easyEnemy.dy=0;
				right = false;
				left = true;
				up = false;
				down = false;
			} 
			else if(!up && easyEnemy.y>p.y+10) {
				easyEnemy.dy=-0.06;
				easyEnemy.dx=0;
				right = false;
				left = false;
				up = true;
				down = false;
			}
			else if(!down && easyEnemy.y<p.y-10) {
				easyEnemy.dy=0.06;
				easyEnemy.dx=0;
				right = false;
				left = false;
				up = false;
				down = true;
			}
		}
		
		if(easyEnemy.life) {
			if(left == true) {
				CurrentFrameMob += 0.005*time;
				if (CurrentFrameMob > 3) CurrentFrameMob -= 3;
				easyEnemy.sprite.setTextureRect(IntRect(104*int(CurrentFrameMob),138,99,132));	
			} 
			if(right == true) {
				CurrentFrameMob += 0.005*time;
				if (CurrentFrameMob > 3) CurrentFrameMob -= 3;
				easyEnemy.sprite.setTextureRect(IntRect(104*int(CurrentFrameMob),0,99,132));
			}

			if(up == true) {
				CurrentFrameMob += 0.005*time;
				if (CurrentFrameMob > 3) CurrentFrameMob -= 3;
				easyEnemy.sprite.setTextureRect(IntRect(99*int(CurrentFrameMob),421,99,132));	
			}
			if(down == true) {
				CurrentFrameMob += 0.005*time;
				if (CurrentFrameMob > 3) CurrentFrameMob -= 3;
				easyEnemy.sprite.setTextureRect(IntRect(98*int(CurrentFrameMob),271,99,132));	
			}
		}
		
		if(easyEnemy2.life) {
			if(left2 == true) {
				CurrentFrameMob2 += 0.005*time;
				if (CurrentFrameMob2 > 3) CurrentFrameMob2 -= 3;
				easyEnemy2.sprite.setTextureRect(IntRect(104*int(CurrentFrameMob2),138,99,132));	
			} 
			if(right2 == true) {
				CurrentFrameMob2 += 0.005*time;
				if (CurrentFrameMob2 > 3) CurrentFrameMob2 -= 3;
				easyEnemy2.sprite.setTextureRect(IntRect(104*int(CurrentFrameMob2),0,99,132));
			}

			if(up2 == true) {
				CurrentFrameMob2 += 0.005*time;
				if (CurrentFrameMob2 > 3) CurrentFrameMob2 -= 3;
				easyEnemy2.sprite.setTextureRect(IntRect(99*int(CurrentFrameMob2),421,99,132));	
			}
			if(down2 == true) {
				CurrentFrameMob2 += 0.005*time;
				if (CurrentFrameMob2 > 3) CurrentFrameMob2 -= 3;
				easyEnemy2.sprite.setTextureRect(IntRect(98*int(CurrentFrameMob2),271,99,132));	
			}
		}
	if(easyEnemy.life == false && easyEnemy2.life == false) {
		p.life = false;
	}
		
	if(p.life == true) {
		p.update(time);
	}
	if(easyEnemy.life == true) {
		easyEnemy.update(time);	
	}	
	if(easyEnemy2.life == true) {
		easyEnemy2.update(time);	
	}
 	bomb.update(time);
	window.clear();
	for (int i=0; i<HEIGHT_MAP; i++)
		for (int j=0; j<WIDTH_MAP; j++)
		{
			if (TileMap[i][j] == ' ') s_map.setTextureRect(IntRect(0, 0, 32, 32));
			if (TileMap[i][j] == '5') s_map.setTextureRect(IntRect(128, 32, 32, 32));
			if (TileMap[i][j] == '3') s_map.setTextureRect(IntRect(64, 0, 96, 32));
			if (TileMap[i][j] == '4') s_map.setTextureRect(IntRect(96, 32, 128, 64));
			if (TileMap[i][j] == '6') s_map.setTextureRect(IntRect(128, 0, 160, 32));
			if (TileMap[i][j] == '7') s_map.setTextureRect(IntRect(160, 0, 192, 32));
			if (TileMap[i][j] == '8') s_map.setTextureRect(IntRect(192, 0, 224, 32));
			if (TileMap[i][j] == '9') s_map.setTextureRect(IntRect(224, 0, 256, 32));
			if (TileMap[i][j] == 'q') s_map.setTextureRect(IntRect(96, 0, 128, 32));
			if (TileMap[i][j] == 'w') s_map.setTextureRect(IntRect(0,32, 32, 64));
			if (TileMap[i][j] == 'r') s_map.setTextureRect(IntRect(32,32, 64, 64));
			if (TileMap[i][j] == 'e') s_map.setTextureRect(IntRect(64, 32, 96, 64));
			if (TileMap[i][j] == '1') s_map.setTextureRect(IntRect(0, 0, 32, 32));
			if (TileMap[i][j] == '0') s_map.setTextureRect(IntRect (32, 0, 64, 32));
			s_map.setPosition(j*32, i*32);
			window.draw(s_map);
		}
		
	if(p.life == true) {
		std::ostringstream playerHealthString,gameTimeString,playerscore;
		playerHealthString << p.health; gameTimeString << gameTime; playerscore << p.playerScore;
		text.setString("HP: " + playerHealthString.str()+"\nÈãðîâîå âðåìÿ: "+gameTimeString.str()+"\nÎ÷êè: "+playerscore.str());
		text.setPosition(10,25);
		window.draw(text);
	} else {
		std::ostringstream playerHealthString,gameTimeString,playerscore;
		playerHealthString << p.health; gameTimeString << gameTime; playerscore << p.playerScore;
		text2.setString("HP: " + playerHealthString.str()+"\nÈãðîâîå âðåìÿ: "+gameTimeString.str()+"\nÎ÷êè: "+playerscore.str());
		text2.setPosition(500,300);
		window.draw(text2);
		but_1.setTexture(button_1);
		but_2.setTexture(button_2);
		
		if (IntRect(500, 100, 256, 64).contains(Mouse::getPosition(window))) { but_1.setTexture(button_1press); }
		if (IntRect(500, 220, 256, 64).contains(Mouse::getPosition(window))) { but_2.setTexture(button_2press);	}
		
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
			if (NumMenu == 1) {Sleep(2200); isMen = false; Level_1.stop();}
			if (NumMenu == 2) {Sleep(2200); window.close(); Level_1.stop(); isMen = false; }
		}
		window.draw(but_1);
		window.draw(but_2);
	}
		
	if(easyEnemy.life == true) {	
		window.draw(easyEnemy.sprite);	
	}
	
	if(BOMB == true && p.life == true) {
		window.draw(bomb.sprite);	
	}
	
	if(easyEnemy2.life == true) {
		window.draw(easyEnemy2.sprite);	
	}
	
	if(p.life == true) {
		window.draw(p.sprite);
	}
	
	window.display();
 }
}
