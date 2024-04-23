#include "menu.h"
#include <SFML/Graphics.hpp>
#include <iostream>
using namespace sf;
using namespace std; 
menu::menu(float width, float hight) {
    font.loadFromFile("C:\\Users\\evoo\\source\\repos\\Sfml\\DragonHunter-9Ynxj.otf");
    mainmenu[0].setFont(font);
    mainmenu[0].setFillColor(Color(200, 28, 20));
    mainmenu[0].setString("play");
    mainmenu[0].setCharacterSize(90);
    mainmenu[0].setPosition(Vector2f(200, 200));

    mainmenu[1].setFont(font);
    mainmenu[1].setFillColor(Color::White);
    mainmenu[1].setString("History");
    mainmenu[1].setCharacterSize(90);
    mainmenu[1].setPosition(Vector2f(200, 400));

    mainmenu[2].setFont(font);
    mainmenu[2].setFillColor(Color::White);
    mainmenu[2].setString("Exit");
    mainmenu[2].setCharacterSize(90);
    mainmenu[2].setPosition(Vector2f(200, 600));

    selected = 0;
}
menu::~menu() {}
void menu::setselected(int n) {
    selected = n;
}
void menu::draw(RenderWindow& window) {
    for (size_t i = 0; i < 3; i++)
    {
        window.draw(mainmenu[i]);
    }
}
void menu::movedown() {
    if (selected + 1 <= 3)
    {
        mainmenu[selected].setFillColor(Color::White);
        selected++;

        if (selected == 3) {
            selected = 0;
        }
        mainmenu[selected].setFillColor(Color(200, 28, 20));
    }
}
void menu::moveup() {
    if (selected - 1 >= -1) {
        mainmenu[selected].setFillColor(Color::White);
        selected--;
    }
        if (selected == -1) {
            selected = 2;
        }
        
        mainmenu[selected].setFillColor(Color(200, 28, 20));
    }
  

