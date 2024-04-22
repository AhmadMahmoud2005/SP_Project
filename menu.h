#pragma once
#include <sfml/graphics.hpp>
using namespace sf;
using namespace std;
class menu
{
public :
	
	
	Text mainmenu[3];
	menu(float width, float hight);
	void draw(RenderWindow& window);
	void moveup();
	void movedown();
	void setselected(int n);
	int pressed() {
		return selected;
	}
	~menu();
private:
	int selected;
	Font font;

};

