#include <SFML/Graphics.hpp>
#include <time.h>
#include <iostream>
#include <cassert>
#include "decl.h"
#include <clocale>  
#pragma execution_character_set("utf-8")
using namespace sf;
using namespace std;

bool create_textures(string sourse) {
	/** Функция принимает на вход значения:
	* sourse : string - путь до файла
	* и возвращает true если удалось создать текстуру из файла */
	bool c;
	Texture a;
		if (a.loadFromFile(sourse)) {
			c = true;
		}
		else {
			c = false;
		}
	return c;
}

int main()
{	/**функция в которой происходит загрузка текстур, отрисовка всех спрайтов и находится главный игровой цикл**/
	setlocale(LC_ALL, "Russian");
	srand(time(0));
	RenderWindow window(VideoMode(1023, 682), "Game!");
	
	Texture f;
	f.loadFromFile("data\\fon.jpg");
	Sprite fon(f);

	Texture p;
	p.loadFromFile("data\\player.png");
	Sprite player(p);
	player.setTextureRect(IntRect(0, 0, 64, 64));
	player.setPosition(480, 600);
	float frame = 0;

	Texture pr;
	pr.loadFromFile("data\\space.jpg");
	Sprite prod(pr);
	prod.setPosition(350, 200);
	float pd = 0;
	bool play = false;

	Texture bullet;
	bullet.loadFromFile("data\\hook.png");
	Sprite bull(bullet);
	bull.setPosition(-50, 0);
	bool mp = false;

	int l = 1;
	bool die = false;

	Texture am;
	am.loadFromFile("data\\antimage.png");
	Sprite antimage[7];
	int ay[7] = { 0 };
	for (int i = 0; i < 7; i++) {
		antimage[i].setTexture(am);
		ay[i] = rand() % 5;
		antimage[i].setPosition(175 * i, -150 - 100 * ay[i]);
	}
	Texture go;
	go.loadFromFile("data\\game_over.png");
	Sprite gameover(go);
	gameover.setPosition(450, 50);
	

	while (window.isOpen())
	{
		Vector2f pl = player.getPosition();

		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();

			if (event.type==Event::KeyPressed)
				if (event.key.code == Keyboard::Space) {
					if (!play && !die)
						play = true;
					else if (!play && die) {
						play = true;
						die = false;
						l = 1;
						for (int i = 0; i < 7; i++) {
							ay[i] = rand() % 5;
							antimage[i].setPosition(175 * i, -150 - 100 * ay[i]);
						}
					}
					else if (play && !mp) {
						bull.setPosition(pl.x + 15, pl.y - 60);
						mp = true;
					}
				}
		}

		if (play) {
			if (Keyboard::isKeyPressed(Keyboard::Right))
				if (pl.x < 1000)
					player.move(1.5, 0);
			if (Keyboard::isKeyPressed(Keyboard::Left))
				if (pl.x > 0)
					player.move(-1.5, 0);
			if (Keyboard::isKeyPressed(Keyboard::Up))
				if (pl.y > 5)
					player.move(0, -1.5);
			if (Keyboard::isKeyPressed(Keyboard::Down))
				if (pl.y < 650)
					player.move(0, 1.5);

			Vector2f bu = bull.getPosition();
			if (mp) {
				bull.move(0, -2);
				if (bu.y < -100)
					mp = false;
			}

			Vector2f ad[7];
			for (int i = 0; i < 7; i++) {
				antimage[i].move(0, 0.5);
				ad[i] = antimage[i].getPosition();
				if (ad[i].y > 850) {
					ay[i] = rand() % 5;
					antimage[i].setPosition(175 * i, -150 - 100 * ay[i]);
				}
				if (bull.getGlobalBounds().intersects(antimage[i].getGlobalBounds())) {
					ay[i] = rand() % 5;
					antimage[i].setPosition(175 * i, -150 - 100 * ay[i]);

					bull.setPosition(-50, 0);
				}
				if (player.getGlobalBounds().intersects(antimage[i].getGlobalBounds())) {
					l--;
					ay[i] = rand() % 5;
					antimage[i].setPosition(175 * i, -150 - 100 * ay[i]);
				}
				if (l == 0) {
					play = false;
					die = true;
				}
			}
		}

			frame += 0.01;
			if (frame < 1)
				player.setTextureRect(IntRect(0, 0, 64, 64));
			else if (frame > 1 && frame < 2)
				player.setTextureRect(IntRect(214, 0, 64, 64));
			else
				frame = 0;
				
			window.clear(Color::White);

			window.draw(fon);
			window.draw(bull);
			for (int i = 0; i < 7; i++)
				window.draw(antimage[i]);
			window.draw(player);
				
			if (!play) {
				pd += 0.005;
				if (pd > 0 && pd < 1)
					window.draw(prod);
				else if (pd > 2)
					pd = 0;
			}
			if (play || die) {
				if (die) {
					window.draw(gameover);
			}
		}
		
		window.display();
	}
	return 0;
	}