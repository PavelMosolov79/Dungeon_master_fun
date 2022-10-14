#ifndef PLAYER_H
#define PLAYER_H
#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include <list>

using namespace sf;


class Entity 
{
	public:
	float dx, dy, x, y, w, h, speed, moveTimer;
	int health, playerScore, dir;
	bool life, isMove;
	Texture texture;
	Sprite sprite;
	String name;
	Entity(Image &image, float X, float Y,int W,int H,String Name)
	{
		x = X; y = Y; w = W; h = H; name = Name; moveTimer = 0;
		speed = 0; health = 100; dx = 0; dy = 0;
		life = true; isMove = false;
		texture.loadFromImage(image);
		sprite.setTexture(texture);
		sprite.setOrigin(w/2,h/2);
	}
	
	FloatRect getRect(){
		return FloatRect(x, y, w, h);
	}
};


class Player :public Entity 
{
public:
	enum { left, right, up, down, stay } state;
	int playerScore;
 	bool Shoot;
 	
	Player(Image &image, float X, float Y,int W,int H,String Name):Entity(image,X,Y,W,H,Name)
	{
		playerScore = Shoot = 0; state = stay;
		if (name == "Player1")
		{
			sprite.setTextureRect(IntRect(0,0,46,72));
		}
	}
	void control()
	{	
	   if (Keyboard::isKeyPressed && life == true)
	   {
		   if (Keyboard::isKeyPressed(Keyboard::Left)) 
		   {
				state = left; speed = 0.1;
		   }
		   if (Keyboard::isKeyPressed(Keyboard::Right)) 
		   {
				state = right; speed = 0.1;
		   }
		   if (Keyboard::isKeyPressed(Keyboard::Up)) 
		   {
				state = up; speed =0.1;
		   }
		   if (Keyboard::isKeyPressed(Keyboard::Down)) 
		   {
				state = down; speed =0.1;
		   }
			if (Keyboard::isKeyPressed(Keyboard::Space)) 
			{
			   Shoot = true;
			}
	   }
	} 
 
		void checkCollisionWithMap(float Dx, float Dy)
		{
			for (int i = y / 32; i < (y + h) / 32; i++) {
				for (int j = x / 32; j<(x + w) / 32; j++) {
					if (TileMap[i][j] == '0'||TileMap[i][j] == '1') {
						if (dy>0){y = i * 32 - h;}
						if (dy<0){y = i * 32 + 32;}
						if (dx>0){x = j * 32 - w;}
						if (dx<0){x = j * 32 + 32;}
					}
				}
			}
		}
		
		void update(float time)
		{
			control();
			switch (state)
			{
				case right: dx=speed; dy=0; break;
				case left: dx=-speed; dy=0; break;
				case up: dx=0; dy=-speed; break;
				case down: dx=0; dy=speed; break;	
			}
			x += dx*time;
			checkCollisionWithMap(dx, 0);
			y += dy*time;
			checkCollisionWithMap(0, dy);
			sprite.setPosition(x+w/2, y+h/2);
			if (health <= 0){ life = false; }
			if (!isMove){ speed = 0; }
		} 
};
 
 
class Enemy :public Entity{
public:
	Enemy(Image &image, float X, float Y,int W,int H,String Name):Entity(image,X,Y,W,H,Name)
	{ 
		if (name == "EasyEnemy")
		{
			sprite.setTextureRect(IntRect(0, 0, 98, 136));
		}
		
	}
 
	void checkCollisionWithMap(float Dx, float Dy)
	{
		for (int i = y / 32; i < (y + h) / 32; i++)
		for (int j = x / 32; j<(x + w) / 32; j++)
		{
			if (TileMap[i][j] == '0'||TileMap[i][j] == '1')
			{
				if (Dy>0){y = i * 32 - h;}
				if (Dy<0){y = i * 32 + 32;}
				if (Dx>0){ x = j * 32 - w;}
				if (Dx<0){ x = j * 32 + 32;}
			}
		}
	}
 
	void update(float time)
	{
		if (name == "EasyEnemy")
		{	
			x += dx*time;
			checkCollisionWithMap(dx, 0);
			y += dy*time;
			checkCollisionWithMap(0, dy);
			sprite.setPosition(x+w/2, y+h/2);
			if (health <= 0){ life = false; }
		}
	}
};

class Bullet :public Entity{
public:
	Bullet(Image &image, float X, float Y, int W, int H, String Name) :Entity(image, X, Y, W, H, Name){
		if (name == "EasyEnemy")
		{
			sprite.setTextureRect(IntRect(0, 0, 32, 32));
		}
		
		life = true;
	}
  
	void update(float time)
	{
		sprite.setPosition(x+w/2, y+h/2);
	}
};

#endif
