// #include "menu.h"
// #include <SFML/Graphics.hpp>
// #include <iostream>
// using namespace sf;
// using namespace std; 
// menu::menu(float width, float hight) {
//     font.loadFromFile("./fonts/DragonHunter-9Ynxj.otf");
//     mainmenu[0].setFont(font);
//     mainmenu[0].setFillColor(Color(200, 28, 20));
//     mainmenu[0].setString("play");
//     mainmenu[0].setCharacterSize(90);
//     mainmenu[0].setPosition(Vector2f(300, 100));

//     mainmenu[1].setFont(font);
//     mainmenu[1].setFillColor(Color::White);
//     mainmenu[1].setString("Maps");
//     mainmenu[1].setCharacterSize(90);
//     mainmenu[1].setPosition(Vector2f(300, 250));

//     mainmenu[2].setFont(font);
//     mainmenu[2].setFillColor(Color::White);
//     mainmenu[2].setString("Exit");
//     mainmenu[2].setCharacterSize(90);
//     mainmenu[2].setPosition(Vector2f(300, 400));

//     selected = 0;
// }
// menu::~menu() {}
// void menu::setselected(int n) {
//     selected = n;
// }
// int menu::getselected() {
//     return selected;
// }
// void menu::draw(RenderWindow& window) {
//     for (size_t i = 0; i < 3; i++)
//     {
//         window.draw(mainmenu[i]);
//     }
// }
// void menu::movedown() {
    
//     mainmenu[selected].setFillColor(Color::White);
//     selected = (selected + 1) % 3;
//     mainmenu[selected].setFillColor(Color(200, 28, 20));
// }
// void menu::moveup() {
//     mainmenu[selected].setFillColor(Color::White);
//     selected = (selected == 0) ? 2 : selected - 1;
//     mainmenu[selected].setFillColor(Color(200, 28, 20));
// }

#include <SFML/Graphics.hpp>
#include <iostream>
using namespace sf;
using namespace std;

class PauseMenu {
public:
    PauseMenu() {
        if (!font.loadFromFile("fonts/font.ttf")) {
            std::cerr << "Failed to load font\n";
        }

        resumeText.setFont(font);
        resumeText.setString("Resume");
        resumeText.setPosition(200, 100);

        mapsText.setFont(font);
        mapsText.setString("Maps");
        mapsText.setPosition(200, 150);

        exitText.setFont(font);
        exitText.setString("Exit");
        exitText.setPosition(200, 200);

        selectedItemIndex = 0;
        updateSelection();
    }

    void draw(sf::RenderWindow& window) {
        window.draw(resumeText);
        window.draw(mapsText);
        window.draw(exitText);
    }

    // Check if the mouse is over a text
    bool isMouseOver(sf::Text& text, sf::RenderWindow& window) {
        sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
        sf::FloatRect bounds = text.getGlobalBounds();
        return bounds.contains(mousePos);
    }

    // Check if the keyboard is over a text
    bool isKeyboardOver(sf::Text& text, sf::RenderWindow& window) {
        sf::Vector2i mousePos = sf::Mouse::getPosition(window);
        sf::FloatRect bounds = text.getGlobalBounds();
        return bounds.contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));
    }

    // Handle keyboard events
    void handleKeyPress(sf::RenderWindow& window, sf::Event::KeyEvent keyEvent) {
        if (keyEvent.code == sf::Keyboard::Return) {
            if (selectedItemIndex == 0) {
                // Resume game
                isVisible = false;
            } else if (selectedItemIndex == 2) {
                // Exit game
                window.close();
            }
        } else if (keyEvent.code == sf::Keyboard::Up) {
            moveUp();
        } else if (keyEvent.code == sf::Keyboard::Down) {
            moveDown();
        }
        updateSelection();
    }

    void moveUp() {
        if (selectedItemIndex > 0) {
            selectedItemIndex--;
        }
    }

    void moveDown() {
        if (selectedItemIndex < 2) {
            selectedItemIndex++;
        }
    }

    void updateSelection() {
        resumeText.setFillColor(sf::Color::Black);
        mapsText.setFillColor(sf::Color::Black);
        exitText.setFillColor(sf::Color::Black);

        switch (selectedItemIndex) {
            case 0:
                resumeText.setFillColor(sf::Color::Red);
                break;
            case 1:
                mapsText.setFillColor(sf::Color::Red);
                break;
            case 2:
                exitText.setFillColor(sf::Color::Red);
                break;
        }
    }

    bool isVisible = false;

private:
    sf::Font font;
    sf::Text resumeText, mapsText, exitText;
    int selectedItemIndex;
};
struct Bullet {
	float speed;
	Sprite bulletsprite;
	int magazin, moveto;
	float cooldownuse;
};
struct Player{

	Sprite sprite;
	int playertecture = 4;
	float currentframe = 0;
	float spritelength = 1003, spriteheight = 249;
	Clock clock;

	int health = 10000;
	int droptype = -1;

	vector<Bullet>bullets;
	bool canshoot = false;
	bool grounded = false;
	float shootcooldown;
	int index = -1;
	
	bool isWeaponed = false; // Shooting Animaion
};
struct help {
    Sprite droptype; //drop
    RectangleShape targetshape; //block
    int type; // 0 , 1 , 2 , 3
    int indexdrop, indexblock;
};

vector<help>dropbag;
Sprite drops[4]; // 0 pistol , 1 rifle , 2 mini , 3 RPG
Texture playerTecture[6] , dropsTexture[8];
int indexdrop, indexblock;


void setplayertecture();
void animation(Player& player);

void setdrops();
void choosedrop(RectangleShape grounds[], Clock& timeradd, Clock& timerdelete);
void dropfalling();
void dropcollision(Player& player);

void cheakdrop(Player& player);
void bulletcooldown(Player& player);
void movebullets(vector<Bullet>& bullets);


int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML Pause Menu");
    window.setFramerateLimit(60);

    Clock timeradd, timerdelete;

	Player player1;
	player1.sprite.setPosition(50, 100);
	player1.sprite.setScale(0.7, 0.7);
	player1.sprite.setOrigin(125.375 / 2.00, 124.5 / 2.00);

    Texture bg[4], jump, menuBg;
    bg[0].loadFromFile("./backgrounds/factoryback.png");
    bg[1].loadFromFile("./backgrounds/ballback.png");
    bg[2].loadFromFile("./backgrounds/ballfore.png");
    bg[3].loadFromFile("./backgrounds/woods.png");
    menuBg.loadFromFile("./backgrounds/wood.png");
	jump.loadFromFile("./sprites/jump.png");
   
    RectangleShape backgrounds[4], menuBackground, grounds[3];
	for (int i = 0; i < 4; i++)
	{
		backgrounds[i].setSize(Vector2f(1000, 1000));
		backgrounds[i].setPosition(0, 0);
    	backgrounds[i].setTexture(&bg[i]);
	}
    menuBackground.setSize(Vector2f(1000, 1000));
    menuBackground.setPosition(0, 0);
    menuBackground.setTexture(&menuBg);

	grounds[0].setSize(Vector2f(170, 800));
	grounds[0].setPosition(0, 420);
	grounds[0].setFillColor(Color::White);

	grounds[1].setSize(Vector2f(270, 100));
	grounds[1].setPosition(350, 425);
	grounds[1].setFillColor(Color::White);

	grounds[2].setSize(Vector2f(170, 800));
	grounds[2].setPosition(830, 420);
	grounds[2].setFillColor(Color::White);

	setplayertecture();
	setdrops();

	animation(player1);

	bool jumped=false , RPGpicked=false;
	int a=0, delay=0 , ctrj = 0;
	float vx=0, vy=0;
	int last_key_pressed=1;
	bool inMainMenu = true, inMapMenu = false;
	int selectedMap = 0;

    PauseMenu pauseMenu;

    bool isPaused = false;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
            else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
                isPaused = !isPaused; // Toggle pause state
                pauseMenu.isVisible = isPaused; // Show/hide pause menu
            } else if (event.type == sf::Event::KeyPressed && isPaused) {
                pauseMenu.handleKeyPress(window, event.key);
            }
        }

        window.clear(sf::Color::White);

        if (!player1.grounded) {
				vy += 0.01 * a;
				a++;
			}

			if (Keyboard::isKeyPressed(Keyboard::Right)) {
				vx = 5.0f;
				player1.sprite.setScale(0.7, 0.7);
				last_key_pressed = 1;
				if (jumped == false) {
					animation(player1);
				}
			}
			else if (Keyboard::isKeyPressed(Keyboard::Left)) {
				vx = -5.0f;
				player1.sprite.setScale(-0.7, 0.7);
				last_key_pressed = 2;
				if (jumped == false) {
					animation(player1);
				}
			}
			else {
				vx = 0.0f;
			}

			if (player1.index >= 0 && Keyboard::isKeyPressed(Keyboard::A) && player1.canshoot) {
				player1.bullets[player1.index].bulletsprite.setPosition(player1.sprite.getPosition().x + 10, player1.sprite.getPosition().y - 40);
				player1.shootcooldown = player1.bullets[player1.index].cooldownuse;
				player1.bullets[player1.index].moveto = last_key_pressed;
				player1.index--;
				player1.canshoot = false;
			}

			if (player1.sprite.getGlobalBounds().intersects(grounds[0].getGlobalBounds())||
				player1.sprite.getGlobalBounds().intersects(grounds[1].getGlobalBounds())||
				player1.sprite.getGlobalBounds().intersects(grounds[2].getGlobalBounds())){
				player1.grounded = true;
				vy = 0;
				a = 0;
				if (Keyboard::isKeyPressed(Keyboard::Up))
				{
					vy = -5.0f;
				}
			}
			else {
				player1.grounded = false;
				animation(player1);
			}
			cheakdrop(player1);
			bulletcooldown(player1);
			movebullets(player1.bullets);

            if (isPaused) {
                pauseMenu.draw(window);
            }
            else
            {
                window.draw(backgrounds[selectedMap]);
                for (int i = 0; i < 3; i++) {
                    window.draw(grounds[i]);
                }
                for (int i = 0; i < dropbag.size(); i++) {
                    window.draw(dropbag[i].droptype);
                }
                for (int i = 0; i < player1.bullets.size(); i++) {
                    window.draw(player1.bullets[i].bulletsprite);
                }
                window.draw(player1.sprite);
                player1.sprite.move(vx, vy);
            }
            window.display();
		}

    return 0;
}



  
void setplayertecture() {
	playerTecture[0].loadFromFile("./sprites/pistol.png");
	playerTecture[1].loadFromFile("./sprites/AK.png");
	playerTecture[2].loadFromFile("./sprites/MiniGun.png");
	playerTecture[3].loadFromFile("./sprites/RPG.png");
	playerTecture[4].loadFromFile("./sprites/walking.png");
	playerTecture[5].loadFromFile("./sprites/jump.png");
}
void animation(Player& player) {
	float time = player.clock.getElapsedTime().asMicroseconds();
	player.clock.restart();
	time /= 1500;
	if (time > 20) {
		time = 20;
	}
	player.currentframe += 0.03 * time;
	if (player.currentframe > 7) {
		player.currentframe -= 7;
	}
	player.sprite.setTexture(playerTecture[player.playertecture]);
	player.sprite.setTextureRect(IntRect((int)player.currentframe * player.spritelength / 8.00, 0, player.spritelength / 8.00, player.spriteheight / 2.00));
}
void setdrops() {
	dropsTexture[0].loadFromFile("./sprites/pistolW.png");
	dropsTexture[1].loadFromFile("./sprites/AKW.png");
	dropsTexture[2].loadFromFile("./sprites/MiniW.png");
	dropsTexture[3].loadFromFile("./sprites/RPGW.png");
	dropsTexture[4].loadFromFile("./sprites/pistol bullet.png");
	for (int i = 0; i < 4; i++) {
		drops[i].setTexture(dropsTexture[i]);
	}
	for (int i = 0; i < 4; i++) {
		drops[i].setScale(0.5, 0.5);
	}
}
void choosedrop(RectangleShape grounds[], Clock& timeradd, Clock& timerdelete) {
	indexdrop = rand() % 4, indexblock = rand() % 3;
	help help;
	if (timeradd.getElapsedTime().asSeconds() >= 6) {
		help.droptype = drops[indexdrop];
		help.targetshape = grounds[indexblock];
		help.type = indexdrop;
		help.droptype.setPosition(grounds[indexblock].getPosition().x , -100);
		dropbag.push_back(help);
		timeradd.restart();
	}if (timerdelete.getElapsedTime().asSeconds() >= 20) {
		if (!dropbag.empty()) {
			dropbag.erase(dropbag.begin());
			timerdelete.restart();
		}
	}
}
void dropfalling() {
	for (int i = 0; i < dropbag.size(); i++) {
		dropbag[i].droptype.move(0, 5);
		if (dropbag[i].droptype.getGlobalBounds().intersects(dropbag[i].targetshape.getGlobalBounds())) {
			dropbag[i].droptype.move(0, -5);
		}
	}
}
void dropcollision(Player& player) {
	for (int i = 0; i < dropbag.size(); i++) {
		if (!dropbag.empty() && player.sprite.getGlobalBounds().intersects(dropbag[i].droptype.getGlobalBounds())) {
			player.droptype = dropbag[i].type;
			dropbag.erase(dropbag.begin() + i);
		}
	}
}
void cheakdrop(Player& player) { 
	// 0 pistol , 1 AK , 2 mini , 3 RPG
	if (player.droptype == -1) {
		// if (player.grounded)
		// 	player.playertecture = 4;
		// else
		// 	player.playertecture = 5;
		return;
	}
	else {
		if (player.droptype == 0) {
			Bullet Bullet;
			Bullet.bulletsprite.setTexture(dropsTexture[4]);
			Bullet.cooldownuse = 10;
			Bullet.speed = 15;
			Bullet.magazin = 5;
			player.canshoot = true;
			for (int i = 0; i < Bullet.magazin; i++) {
				player.bullets.push_back(Bullet);
				player.index++;
			}
			player.playertecture = player.droptype;
			player.spritelength = 938;
			player.spriteheight = 230;
		}
		else if (player.droptype == 1) {
			Bullet Bullet;
			Bullet.bulletsprite.setTexture(dropsTexture[4]);
			Bullet.cooldownuse = 5;
			Bullet.speed = 15;
			Bullet.magazin = 10;
			player.canshoot = true;
			for (int i = 0; i < Bullet.magazin; i++) {
				player.bullets.push_back(Bullet);
				player.index++;
			}
			player.playertecture = player.droptype;
			player.spritelength = 1108;
			player.spriteheight = 225;
		}
		else if (player.droptype == 2) {
			Bullet Bullet;
			Bullet.bulletsprite.setTexture(dropsTexture[4]);
			Bullet.cooldownuse = 2;
			Bullet.speed = 15;
			Bullet.magazin = 50;
			player.canshoot = true;
			for (int i = 0; i < Bullet.magazin; i++) {
				player.bullets.push_back(Bullet);
				player.index++;
			}
			player.playertecture = player.droptype;
			player.spritelength = 1129;
			player.spriteheight = 221;
		}
		else if (player.droptype == 3) {
			Bullet Bullet;
			Bullet.bulletsprite.setTexture(dropsTexture[4]);
			Bullet.cooldownuse = 10;
			Bullet.speed = 15;
			Bullet.magazin = 1;
			player.canshoot = true;
			for (int i = 0; i < Bullet.magazin; i++) {
				player.bullets.push_back(Bullet);
				player.index++;
			}
			player.playertecture = player.droptype;
			player.spritelength = 1016;
			player.spriteheight = 226;
		}
		player.droptype = -1;
	}
}
void bulletcooldown(Player& player) {
	if (player.shootcooldown > 0 && player.canshoot == false) {
		player.shootcooldown -= 0.5;
	}
	if (player.shootcooldown <= 0 && player.canshoot == false) {
		player.canshoot = true;
	}
}
void movebullets(vector<Bullet>& bullets) {
	for (int i = 0; i < bullets.size(); i++) {
		//move to left
		if (bullets[i].moveto == 2) {
			bullets[i].bulletsprite.move(-1 * bullets[i].speed, 0);
		}
		//move to right
		if (bullets[i].moveto == 1) {
			bullets[i].bulletsprite.move(1 * bullets[i].speed, 0);
		}
		if (bullets[i].bulletsprite.getPosition().x >= 1010 ||
			bullets[i].bulletsprite.getPosition().x <= -50) {
			bullets.erase(bullets.begin() + i);
		}
	}
}

