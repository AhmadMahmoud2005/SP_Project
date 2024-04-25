#include<SFML/Graphics.hpp>
#include<SFML/Audio.hpp>
#include<iostream>
using namespace sf;
using namespace std;

const int MAIN_MENU_STATE = 0;
const int LEVEL_1_STATE = 1;
const int LEVEL_2_STATE = 2;

int showMainMenu(RenderWindow& window);
int playLevel1(RenderWindow& window);
int playLevel2(RenderWindow& window);



int main()
{
	RenderWindow window(VideoMode(1000, 1000),"GAME",Style::Default);
	window.setFramerateLimit(60);

	int currentState = MAIN_MENU_STATE;

	while (window.isOpen()) {

		Event evnt;

		while (window.pollEvent(evnt)) {
			if (evnt.type == Event::Closed) {
				window.close();
			}
		}
		switch (currentState) {
		case MAIN_MENU_STATE:
			currentState = showMainMenu(window);
			break;
		case LEVEL_1_STATE:
			currentState = playLevel1(window);
			break;
		case LEVEL_2_STATE:
			currentState = playLevel2(window);
			break;
		}
	}
	return 0;
}
int showMainMenu(RenderWindow& window) {
	Texture bg;
	bg.loadFromFile("stickfight.png");

	RectangleShape background;
	background.setTexture(&bg);
	background.setSize(Vector2f(1000, 1000));
	background.setPosition(0, 0);

	window.clear();
	// Draw your main menu here

	window.draw(background);

	window.display();

	// Example transition conditions
	if (Keyboard::isKeyPressed(Keyboard::Num1)) {
		return LEVEL_1_STATE;
	}
	else if (Keyboard::isKeyPressed(Keyboard::Num2)) {
		return LEVEL_2_STATE;
	}

	// Return MainMenu state by default
	return MAIN_MENU_STATE;
}
int playLevel1(RenderWindow& window) {
	Texture bg;
	bg.loadFromFile("l1.png");

	RectangleShape background;
	background.setTexture(&bg);
	background.setSize(Vector2f(1000, 1000));
	background.setPosition(0, 0);
	
	window.clear();
	// Draw your level 1 here

	window.draw(background);

	window.display();

	// Example transition condition
	if (Keyboard::isKeyPressed(Keyboard::Escape)) {
		return MAIN_MENU_STATE;
	}

	// Return Level1 state by default
	return LEVEL_1_STATE;
}
int playLevel2(RenderWindow& window) {
	Texture bg;
	bg.loadFromFile("background.png");

	RectangleShape background;
	background.setTexture(&bg);
	background.setSize(Vector2f(1000, 1000));
	background.setPosition(0, 0);

	window.clear();
	// Draw your level 2 here

	window.draw(background);

	window.display();

	// Example transition condition
	if (Keyboard::isKeyPressed(Keyboard::Escape)) {
		return MAIN_MENU_STATE;
	}

	// Return Level2 state by default
	return LEVEL_2_STATE;
}
