#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <fstream>
using namespace sf;
using namespace std;
#include"menu.h"; 
int pagenumber = 1000;
void pname(RenderWindow& window, string& name);
void His(RenderWindow& window);
int main()
{
	RenderWindow window(VideoMode(1920, 1000), "Stick Fight");
	Texture picture;
	picture.loadFromFile("stickfight.png");
	Sprite background;
	background.setTexture(picture);
	menu menu(1920, 1000);
	string name;
	Music music;
	music.openFromFile("battle-of-the-dragons-8037 (online-audio-converter.com).ogg");
	music.play();
	while (true) {
		if (pagenumber == 1000) {
			while (window.isOpen())
			{
				Event event;
				while (window.pollEvent(event))
				{
					if (event.type == Event::Closed)
						window.close();
					break;
				}
				if (event.type == Event::KeyPressed) {
					if (event.key.code == Keyboard::Up) {
						menu.moveup();
					}

					if (event.key.code == Keyboard::Down) {
						menu.movedown();
					}
					if (event.key.code == Keyboard::Return) {
						if (menu.pressed() == 0) {
							pagenumber = 0;
						} if (menu.pressed() == 1) {
							pagenumber = 1;
						} if (menu.pressed() == 2) {
							pagenumber = -1;
						}

					}
				}


				window.clear();
				if (pagenumber != 1000) {
					break;
				}
				window.draw(background);
				menu.draw(window);
				window.display();
			}
			if (pagenumber == -1) {
				window.close();
				break;
			}
			if (pagenumber == 0) {
				pname(window, name);
			}
		}
	}
	return 0;

}
void pname(RenderWindow& window, string& name) {
	if (!name.empty()) {
		name.clear();
	}
	Texture pname1;
	pname1.loadFromFile("stickfight.png");
	Sprite bg;
	bg.setTexture(pname1);
	Font font;
	font.loadFromFile("C:\\Users\\evoo\\source\\repos\\Sfml\\DragonHunter-9Ynxj.otf");
	Text t1;
	Text t2;
	t1.setFont(font);
	t2.setFont(font);
	t1.setString("Enter your name");
	t1.setCharacterSize(70);
	t2.setCharacterSize(70);
	t1.setPosition(10, 10);
	t2.setPosition(10, 100);
	t1.setFillColor(Color::White);
	t2.setFillColor(Color::White);
	while (window.isOpen()) {
		Event event;
		while (window.pollEvent(event)) {
			if (event.type == Event::Closed) {
				window.close();
			}

			if (event.type == Event::TextEntered) {
				name += static_cast<char>(event.text.unicode);
			}
			if (Keyboard::isKeyPressed(Keyboard::BackSpace) && name.size() > 0) {
				name.resize(name.size() - 1);
			}
			if (Keyboard::isKeyPressed(Keyboard::Return) && name.size() > 1) {
				pagenumber = 3; //Game
				return;
			}
			if (Keyboard::isKeyPressed(Keyboard::Escape)) {
				pagenumber = 1000;
				return;
			}
		}
		t2.setString(name);
		window.clear();
		window.draw(bg);
		window.draw(t1);
		window.draw(t2);
		window.display();
	}
}
void His(RenderWindow& window) {
	Texture HistoryTex;
	HistoryTex.loadFromFile("stickfight.png");
	Sprite HistorySprit;
	HistorySprit.setTexture(HistoryTex);
	HistorySprit.setPosition(0, 0);
	Font font1;
	font1.loadFromFile("C:\\Users\\evoo\\source\\repos\\Sfml\\DragonHunter-9Ynxj.otf");
	Text text[100];

	for (int i = 0; i < 55; i++) {

		text[i].setFont(font1);

		text[i].setCharacterSize(50);

		text[i].setFillColor(Color::Green);
	}
	ifstream infile;
	infile.open("history.txt", ios::in);
	vector<string> lines;
	string line;
	while (getline(infile, line, '*')) {

		lines.push_back(line);
	}
	for (int i = 0; i < lines.size(); i++) {



		text[i].setString(lines[i]);

		text[i].setPosition(50, 100 * i);
	}
	while (window.isOpen()) {
		Event event;
		while (window.pollEvent(event)) {
			if (event.type == Event::Closed) {
				window.close();
			}

			if (Keyboard::isKeyPressed(Keyboard::Escape)) {
				pagenumber = 1000;
				return;
			}
			if (Keyboard::isKeyPressed(Keyboard::Key::Up)) {

				if (text[0].getPosition().y <= 5) {
					for (int i = 0; i < lines.size() + 10; i++) {
						text[i].move(0, -20);
					}
				}
			}
			if (Keyboard::isKeyPressed(Keyboard::Key::Down))
				if (text[(lines.size()) - 1].getPosition().y >= window.getPosition().y + 1000) {
					for (int i = 0; i < lines.size() + 10; i++) {
						text[i].move(0, -20);
					}
				}
		}
		cout << lines.size() << endl;
	}
	window.clear();
	window.draw(HistorySprit);
	for (int i = 0; i < lines.size(); i++)
	{
		window.draw(text[i]);
	}
	window.display();
}




//void PName(RenderWindow& window, String& name) {
//    if (!name.empty()) {
//        name.clear();
//    }
//    Texture picture;
//    picture.loadFromFile("stickfight.png");
//    Sprite background;
//    background.setTexture(picture);
//    Font font;
//    font.loadFromFile("C:\\Users\\evoo\\source\\repos\\Sfml\\DragonHunter-9Ynxj.otf");
//    Text t1;
//    Text t2;
//    t1.setFont(font);
//    t2.setFont(font);
//    t1.setString("Enter your name");
//    t1.setCharacterSize(90);
//    t2.setCharacterSize(90);
//    t1.setPosition(10, 10);
//    t2.setPosition(10, 100);
//    t1.setFillColor(Color(200, 28, 20));
//    t2.setFillColor(Color(200, 28, 20));
//    while (window.isOpen()) {
//        Event event;
//        while (window.pollEvent(event))
//        {
//            if (event.type == Event::Closed) {
//                window.close();
//            }
//
//
//            if (event.type == Event::TextEntered) {
//                name += static_cast<char>(event.text.unicode);
//            }
//            if (Keyboard::isKeyPressed(Keyboard::Backspace) && name.size() > 0) {
//                name.resize(name.size() - 1);
//            }
//            if (Keyboard::isKeyPressed(Keyboard::Return) && name.size() > 1) {
//                pagenumber = 3;
//                return;
//            }
//            if (Keyboard::isKeyPressed(Keyboard::Escape)) {
//                pagenumber = 1000;
//                return;
//            }
//        }
//        t2.setString(name);
//        window.clear();
//        window.draw(background);
//        window.draw(t1);
//        window.draw(t2);
//        window.display();
//    }
//}