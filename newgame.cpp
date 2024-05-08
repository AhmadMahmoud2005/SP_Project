#include<iostream>
#include<SFML/Graphics.hpp>
#include<SFML/Audio.hpp>
#include<string>
#include<vector>
using namespace sf;
using namespace std;

// levels return values
const int MAIN_MENU_STATE = -1;
const int LEVEL_1_STATE = 0;
const int LEVEL_2_STATE = 1;
const int LEVEL_3_STATE = 2;
const int LEVEL_4_STATE = 3;
const int LEVEL_5_STATE = 4;
const int MAPS_MENU_STATE = 6;
int currentLevel = 0;

const int level1blocks = 2;
const int level2blocks = 10;
const int level3blocks = 11;
const int level4blocks = 5;

struct Bullet {
	float speed;
	Sprite bulletsprite;
	int magazin, moveto;
	float cooldownuse;
	int Damage;
};
struct Player
{
	Sprite sprite;
	int playertecture = 4;
	float currentframe = 1;
	float spritelength = 1003, spriteheight = 249;

	bool jumped = false, isWeaponed = false;

	Clock clock;

	int health = 10000;

	int droptype = -1;

	int last_key_pressed;

	vector<Bullet>bullets;
	bool canshoot = false;
	float shootcooldown;
	int index = -1;
	int currentmagazine = 0;

	float jumpcurrentframe = 0;
	float velocity = 0, acceleration = 0;

	int playernumber;
}player1, player2;
struct help {
	Sprite droptype; //drop
	RectangleShape targetshape; //block
	int type; // 0 , 1 , 2 , 3
};

vector<help>dropbag;

Sprite drops[4]; // 0 pistol , 1 rifle , 2 mini , 3 RPG 
Texture playerTecture[6], dropsTexture[8], menuText;
int currentwinner = 0;

// crown
Texture crown;
Sprite winnercrown;


RectangleShape cblocks[2], wblocks[10], dblocks[11], bblocks[6], menu, maps[4], mapsBack[4]; //maps blocks
Sprite castleb, castlef, wback, wfore, dground, dfore, bground, bfore;
Font font;
string mapNames[4];
Text names[4], fight[5];
bool play = false, canfight = false, defined = false;
int currenttext = 0;

RectangleShape createRectangle(int length, int width, int xposition, int yposition);
Sound menuSound;

void createSprite(Sprite& sprite, Texture& texture, float scalex, float scaley);

void setfontfight(Font& font);
void displayfontfight(RenderWindow& window, Clock& clock);
void victory(RenderWindow& window, Clock& clock);
void restorefontfight();

//castle blocks 1
void castleblocks(RectangleShape cblocks[]);

//wood blocks 2
void woodblocks(RectangleShape wblocks[]);

//desert blocks 3
void desertblocks(RectangleShape dblocks[]);

//ball blocks 4
void ballblocks(RectangleShape bblocks[]);


// player
void playerproperties();
void setplayertecture();
void animation(Player& player);
void movement(Player& player);
bool checkcollide(Player& player, RectangleShape blocks[], int levelblocks);
void jumping(Player& player, RectangleShape blocks[], int levelblocks);

// crown
void winner(Player& player);

// drops(weapons)
void setdrops();
void choosedrop(RectangleShape blocks[], Clock& timeradd, Clock& timerdelete, int levelblocks);
void dropfalling();
void dropcollision(Player& player);

// shooting
void cheakdrop(Player& player);
void shooting(Player& player);
void bulletcooldown(Player& player);
void movebullets(vector<Bullet>& bullets, Player& player2);

// levels
int MainMenu(RenderWindow& window, Clock& timer,Clock& clock);
int MapsMenu(RenderWindow& window, Clock& timer);
int level1(RenderWindow& window, Clock& timeradd, Clock& timerdelete, Clock& clock);
int level2(RenderWindow& window, Clock& timeradd, Clock& timerdelete, Clock& clock);
int level3(RenderWindow& window, Clock& timeradd, Clock& timerdelete, Clock& clock);
int level4(RenderWindow& window, Clock& timeradd, Clock& timerdelete, Clock& clock);

const unsigned WIN_WIDTH = 1900;
const unsigned WIN_HEIGHT = 1100;

int main() {

	RenderWindow window(VideoMode(WIN_WIDTH, WIN_HEIGHT), "GAME", Style::Default);
	window.setFramerateLimit(60);
	Clock timeradd, timerdelete, timer;

	font.loadFromFile("./fonts/font.ttf");
	for (int i = 0; i < 5; i++) {
		fight[i].setFont(font);
	}
	setfontfight(font);

	// Main Menu
	menuText.loadFromFile("./backgrounds/stickfight.png");
	menu.setTexture(&menuText);
	menu.setSize(Vector2f(WIN_WIDTH, WIN_HEIGHT));

	//map  (1)
	//castle map1
	Texture castleback;
	castleback.loadFromFile("./backgrounds/castleb.png");
	mapsBack[0].setTexture(&castleback);
	createSprite(castleb, castleback, 1.6, 2);
	Texture castlefore;
	castlefore.loadFromFile("./backgrounds/castlefore.png");
	maps[0].setTexture(&castlefore);
	castlef.setTexture(castlefore);
	castleblocks(cblocks);

	//map (2)
	//wood 
	Texture wbackground;
	wbackground.loadFromFile("./backgrounds/wood.png");
	mapsBack[1].setTexture(&wbackground);
	createSprite(wback, wbackground, 1.67, 1.7);
	Texture wforeground;
	wforeground.loadFromFile("./backgrounds/woods.png");
	maps[1].setTexture(&wforeground);
	createSprite(wfore, wforeground, 0.84, 0.8);
	woodblocks(wblocks);

	//map  (3)
	//desert 
	Texture dback;
	dback.loadFromFile("./backgrounds/desertb.png");
	mapsBack[2].setTexture(&dback);
	createSprite(dground, dback, 1.5, 1.6);
	Texture desertfore;
	desertfore.loadFromFile("./backgrounds/desertf.png");
	maps[2].setTexture(&desertfore);
	createSprite(dfore, desertfore, 1.5, 1.55);
	dfore.setPosition(Vector2f(0, 0));
	desertblocks(dblocks);

	for (int i = 0; i < 11; i++) {
		dblocks->setFillColor(Color::White);
	}

	//map (4)
	 //ball 
	Texture bback;
	bback.loadFromFile("./backgrounds/ballback.png");
	mapsBack[3].setTexture(&bback);
	createSprite(bground, bback, 1.5, 1.5);
	Texture ball;
	ball.loadFromFile("./backgrounds/ballfore.png");
	maps[3].setTexture(&ball);
	createSprite(bfore, ball, 1.5, 1);
	bfore.setPosition(Vector2f(0, 330));
	ballblocks(bblocks);

	mapNames[0] = "\"Woods\"";
	mapNames[1] = "\"Castle\"";
	mapNames[2] = "\"Factory\"";
	mapNames[3] = "\"Easter\"";

	playerproperties();

	// crown
	crown.loadFromFile("crown.png");
	winnercrown.setTexture(crown);
	winnercrown.setScale(0.3, 0.3);

	setplayertecture();
	setdrops();

	// Sound Effects
	SoundBuffer menuBuffer;
	menuBuffer.loadFromFile("./sounds/battle-of-the-dragons-8037 (online-audio-converter.com).ogg");
	menuSound.setBuffer(menuBuffer);
	menuSound.play();

	// cout << "Health1" << " " << "Health2" << endl;
	int currentState = -1;
	Clock clock;

	while (window.isOpen()) {
		Event evnt;
		while (window.pollEvent(evnt)) {
			if (evnt.type == Event::Closed) {
				window.close();
			}
		}
		if (Mouse::isButtonPressed(Mouse::Left))
		{
			Vector2i mousePos = Mouse::getPosition(window);
			cout << mousePos.x << " " << mousePos.y << "\n";
		}
		switch (currentState) {
		case MAIN_MENU_STATE:
			currentState = MainMenu(window, timer, clock);
			// menuSound.play();
			break;
		case MAPS_MENU_STATE:
			currentState = MapsMenu(window, timer);
			break;
		case LEVEL_1_STATE:
			currentState = level1(window, timeradd, timeradd, clock);
			menuSound.pause();
			break;
		case LEVEL_2_STATE:
			currentState = level2(window, timeradd, timeradd, clock);
			menuSound.pause();
			break;
		case LEVEL_3_STATE:
			currentState = level3(window, timeradd, timeradd, clock);
			menuSound.pause();
			break;
		case LEVEL_4_STATE:
			currentState = level4(window, timeradd, timeradd, clock);
			menuSound.pause();
			break;
		}
	}
	return 0;
}

// Health bar 
void healthBar(RenderWindow& window)
{
	// Create a rectangle for the background of the health bar
    sf::RectangleShape background1(sf::Vector2f(510, 60));
    background1.setFillColor(sf::Color::White); // Gray color
    background1.setPosition(50, 50);
    // Create a rectangle for the actual health
    sf::RectangleShape health1(sf::Vector2f(player1.health / 2.0, 50));
	cout << player1.health << "\n";
    health1.setPosition(55, 55);
	if (player1.health <= 200) {
		health1.setFillColor(sf::Color::Red);
	} else if (player1.health <= 600) {
		health1.setFillColor(sf::Color::Yellow);
	} else {
		health1.setFillColor(sf::Color::Green);
	}

    sf::RectangleShape background2(sf::Vector2f(510, 60));
    background2.setFillColor(sf::Color::White); // Gray color
    background2.setPosition(WIN_WIDTH - 510, 50);

    sf::RectangleShape health2(sf::Vector2f(player2.health / 2.0, 50));
    health2.setPosition(WIN_WIDTH - 500, 55);
	if (player2.health <= 200) {
		health2.setFillColor(sf::Color::Red);
	} else if (player2.health <= 600) {
		health2.setFillColor(sf::Color::Yellow);
	} else {
		health2.setFillColor(sf::Color::Green);
	}

	window.draw(background1);
	window.draw(health1);
	window.draw(background2);
	window.draw(health2);
}

//font
void setfontfight(Font& font) {
	fight[0].setFont(font);
	fight[0].setCharacterSize(200);
	fight[0].setString("3");
	fight[0].setPosition(900, 200);
	fight[0].setFillColor(Color::White);
	fight[1].setFont(font);
	fight[1].setCharacterSize(200);
	fight[1].setString("2");
	fight[1].setPosition(900, 200);
	fight[1].setFillColor(Color::White);
	fight[2].setFont(font);
	fight[2].setCharacterSize(200);
	fight[2].setString("1");
	fight[2].setPosition(900, 200);
	fight[2].setFillColor(Color::White);
	fight[2].setFont(font);
	fight[3].setCharacterSize(200);
	fight[3].setString("FIGHT!");
	fight[3].setPosition(720, 200);
	fight[3].setFillColor(Color::White);
	fight[4].setCharacterSize(200);
	fight[4].setString("VICTORY!");
	fight[4].setPosition(700, 200);
	fight[4].setFillColor(Color::White);
}
void displayfontfight(RenderWindow& window, Clock& clock) {
	if (currenttext == 4) {
		currenttext = 0;
		canfight = true;
	}
	window.draw(fight[currenttext]);
	if (clock.getElapsedTime().asSeconds() >= 1) {
		fight[currenttext].setScale(0, 0);
		currenttext++;
		clock.restart();
	}
}
void victory(RenderWindow& window, Clock& clock) {
	window.draw(fight[currenttext]);
	if (clock.getElapsedTime().asSeconds() >= 1) {
		fight[5].setScale(0, 0);
		currenttext++;
		clock.restart();
	}
}
void restorefontfight() {
	fight[0].setScale(1, 1);
	fight[1].setScale(1, 1);
	fight[2].setScale(1, 1);
	fight[3].setScale(1, 1);
}

//rectangle function
RectangleShape createRectangle(int length, int width, int xposition, int yposition) {
	RectangleShape rectangle(Vector2f(length, width));
	rectangle.setPosition(xposition, yposition);
	rectangle.setFillColor(Color::Black);
	return rectangle;
};
//sprite function
void createSprite(Sprite& sprite, Texture& texture, float scalex, float scaley) {
	sprite.setTexture(texture);
	sprite.setScale(scalex, scaley);
};

//castle blocks 1
void castleblocks(RectangleShape cblocks[]) {
	//castle ground left
	cblocks[0] = createRectangle(700, 240, 0, 860);
	//castle ground right
	cblocks[1] = createRectangle(750, 250, 1170, 870);
};

//wood blocks 2
void woodblocks(RectangleShape wblocks[]) {
	//wood ground
	wblocks[0] = createRectangle(1739, 100, 98, 911);
	//wood middle level 1
	wblocks[1] = createRectangle(417, 250, 757, 735);
	//wood float 1 left
	wblocks[2] = createRectangle(200, 50, 53, 656);
	//wood float 1 right
	wblocks[3] = createRectangle(200, 50, 1680, 650);
	//wood float 2 left
	wblocks[4] = createRectangle(200, 40, 405, 530);
	//wood float 2 right
	wblocks[5] = createRectangle(203, 40, 1330, 530);
	//wood float 3 left
	wblocks[6] = createRectangle(152, 50, 759, 493);
	//wood float 3 right
	wblocks[7] = createRectangle(152, 50, 1022, 493);
	//wood ground left
	wblocks[8] = createRectangle(65, 100, 350, 818);
	//wood ground right
	wblocks[9] = createRectangle(65, 100, 1518, 818);
};

//desert blocks 3
void desertblocks(RectangleShape dblocks[]) {
	dblocks[0] = createRectangle(440, 100, 425, 577);
	//desert right float
	dblocks[1] = createRectangle(400, 100, 1130, 590);
	//desert floor
	dblocks[2] = createRectangle(95, 395, 910, 0);
	//desert tall ground
	dblocks[3] = createRectangle(1550, 80, 185, 980);
	//desert level 1 mid
	dblocks[4] = createRectangle(400, 80, 760, 900);
	//desert level 1 left
	dblocks[5] = createRectangle(235, 80, 195, 900);
	//desert level 1 right
	dblocks[6] = createRectangle(235, 80, 1490, 900);
	//desert level 2 left
	dblocks[7] = createRectangle(160, 80, 195, 820);
	//desert level 2 right
	dblocks[8] = createRectangle(160, 80, 1570, 820);
	//desert level 2 mid
	dblocks[9] = createRectangle(235, 80, 845, 820);
	//desert level 3 mid
	dblocks[10] = createRectangle(80, 80, 925, 740);
};

//ball blocks 4
void ballblocks(RectangleShape bblocks[]) {
	//ball block1
	bblocks[0] = createRectangle(390, 150, 1500, 880);
	//ball block2
	bblocks[1] = createRectangle(255, 150, 470, 890);
	//ball block3
	bblocks[2] = createRectangle(275, 150, 810, 890);
	//ball block4
	bblocks[3] = createRectangle(255, 150, 1170, 890);
	//ball block5
	bblocks[4] = createRectangle(405, 150, 0, 890);
	//ballground
	bblocks[5] = createRectangle(2000, 150, 0, 1020);
};

// player
void playerproperties() {
	player1.sprite.setPosition(100, 100);
	player1.sprite.setScale(0.7, 0.7);
	player1.sprite.setOrigin(125.375 / 2.00, 124.5 / 2.00);
	player1.spritelength = 1003;
	player1.spriteheight = 249;
	player1.playertecture = 4;
	player1.playernumber = 1;
	player1.last_key_pressed = 1;
	player1.velocity = 0;
	player1.acceleration = 0;
	player1.health = 1000;
	if (!player1.bullets.empty()) {
		player1.bullets.clear();
		player1.index -= player1.currentmagazine;
	}

	player2.sprite.setPosition(1500, 100);
	player2.sprite.setScale(-0.7, 0.7);
	player2.sprite.setOrigin(125.375 / 2.00, 124.5 / 2.00);
	player2.spritelength = 1003;
	player2.spriteheight = 249;
	player2.playertecture = 4;
	player2.playernumber = 2;
	player2.last_key_pressed = -1;
	player2.velocity = 0;
	player2.acceleration = 0;
	player2.health = 1000;
	if (!player2.bullets.empty()) {
		player2.bullets.clear();
		player2.index -= player2.currentmagazine;
	}

	dropbag.clear();
}
void setplayertecture() {
	playerTecture[0].loadFromFile("pistol.png");
	playerTecture[1].loadFromFile("AK.png");
	playerTecture[2].loadFromFile("MiniGun.png");
	playerTecture[3].loadFromFile("RPG.png");
	playerTecture[4].loadFromFile("walking.png");
	playerTecture[5].loadFromFile("jump.png");
}
void animation(Player& player) {
	float time = player.clock.getElapsedTime().asMicroseconds();
	player.clock.restart();
	time /= 1500;
	if (time > 20) {
		time = 20;
	}
	player.currentframe += 0.03 * time;
	if (player.currentframe > 8) {
		player.currentframe -= 7;
	}
	player.sprite.setTexture(playerTecture[player.playertecture]);
	player.sprite.setTextureRect(IntRect((int)player.currentframe * player.spritelength / 8.00, 0, player.spritelength / 8.00, player.spriteheight / 2));
}
void movement(Player& player) {
	player.sprite.move(5 * player.last_key_pressed, 0);
	player.sprite.setScale(0.7 * player.last_key_pressed, 0.7);
	if (player.jumped == false) {
		animation(player);
	}
}
bool checkcollide(Player& player, RectangleShape blocks[], int levelblocks) {
	bool collide = false;
	for (int i = 0; i < levelblocks; i++) {
		FloatRect playerBounds = player.sprite.getGlobalBounds();
		FloatRect blockBounds = blocks[i].getGlobalBounds();
		if (playerBounds.intersects(blockBounds)) {
			if ((playerBounds.left >= blockBounds.left + blockBounds.width - 20))
			{
				player.sprite.setPosition(blockBounds.left + blockBounds.width + playerBounds.width / 2, player.sprite.getPosition().y);
			}
			else if ((playerBounds.left + playerBounds.width <= blockBounds.left + 20))
			{
				player.sprite.setPosition(blockBounds.left - playerBounds.width / 2, player.sprite.getPosition().y);
			}
			else
			{
				if (playerBounds.top + playerBounds.height <= blockBounds.top + 20)
				{
					collide = true;
				}
				else if (playerBounds.top >= blockBounds.top + blockBounds.height - 20)
				{
					// collide = false;
					player.sprite.setPosition(player.sprite.getPosition().x, blockBounds.top + blockBounds.height + playerBounds.height / 2);
				}
			}
		}
	}
	return collide;
}
void jumping(Player& player, RectangleShape blocks[], int levelblocks) {
	int blocksnumber = levelblocks;
	float time = player.clock.getElapsedTime().asMicroseconds();
	player.clock.restart();
	time /= 1500;
	if (time > 20) {
		time = 20;
	}
	player.jumpcurrentframe += 0.01 * time;
	time /= 1500;
	if (checkcollide(player, blocks, blocksnumber)) {
		player.velocity = 0;
		player.acceleration = 0;
		if (player.jumpcurrentframe >= 7) {
			player.jumpcurrentframe = 0;
		}
		if (player.playernumber == 1) {
			if (Keyboard::isKeyPressed(Keyboard::Up)) {
				player.velocity = 10;
				if (player.isWeaponed == false) {
					player.jumped = true;
				}
				else {
					player.jumped = false;
				}
			}
		}
		else if (player.playernumber == 2) {
			if (Keyboard::isKeyPressed(Keyboard::W)) {
				player.velocity = 10;
				if (player.isWeaponed == false) {
					player.jumped = true;
				}
				else {
					player.jumped = false;
				}
			}
		}
	}
	else {
		player.velocity -= 0.01 * player.acceleration;
		player.acceleration++;
	}

	player.sprite.move(0, -player.velocity);
	if (player.jumped == true) {
		player.sprite.setTexture(playerTecture[5]);
		player.sprite.setTextureRect(IntRect((int)player.jumpcurrentframe * 1024 / 8.00, 0, 128, 128));
		if (player.jumpcurrentframe >= 7) {
			player.jumped = false;
		}
	}
	//cout << player.jumpcurrentframe << "  " << player.jumped << endl;
}

// crown
void winner(Player& player) {
	if (player.playertecture == 0) {
		if (player.last_key_pressed == 1) {
			winnercrown.setPosition(player.sprite.getPosition().x - 25, player.sprite.getPosition().y - 62);
		}
		else if (player.last_key_pressed == -1) {
			winnercrown.setPosition(player.sprite.getPosition().x - 2, player.sprite.getPosition().y - 62);
		}
	}
	else if (player.playertecture == 1) {
		if (player.last_key_pressed == 1) {
			winnercrown.setPosition(player.sprite.getPosition().x - 23, player.sprite.getPosition().y - 62);
		}
		else if (player.last_key_pressed == -1) {
			winnercrown.setPosition(player.sprite.getPosition().x - 2, player.sprite.getPosition().y - 62);
		}
	}
	else if (player.playertecture == 2) {
		if (player.last_key_pressed == 1) {
			winnercrown.setPosition(player.sprite.getPosition().x - 28, player.sprite.getPosition().y - 62);
		}
		else if (player.last_key_pressed == -1) {
			winnercrown.setPosition(player.sprite.getPosition().x, player.sprite.getPosition().y - 62);
		}
	}
	else if (player.playertecture == 3) {
		if (player.last_key_pressed == 1) {
			winnercrown.setPosition(player.sprite.getPosition().x - 12, player.sprite.getPosition().y - 62);
		}
		else if (player.last_key_pressed == -1) {
			winnercrown.setPosition(player.sprite.getPosition().x - 12, player.sprite.getPosition().y - 62);
		}
	}
	else {
		if (player.last_key_pressed == 1) {
			winnercrown.setPosition(player.sprite.getPosition().x - 8, player.sprite.getPosition().y - 55);
		}
		else if (player.last_key_pressed == -1) {
			winnercrown.setPosition(player.sprite.getPosition().x - 17, player.sprite.getPosition().y - 55);
		}
	}
}

// drops(weapons)
void setdrops() {
	dropsTexture[0].loadFromFile("pistolW.png");
	dropsTexture[1].loadFromFile("AKW.png");
	dropsTexture[2].loadFromFile("MiniW.png");
	dropsTexture[3].loadFromFile("RPGW.png");
	dropsTexture[4].loadFromFile("pistol bullet.png");
	for (int i = 0; i < 4; i++) {
		drops[i].setTexture(dropsTexture[i]);
	}
	for (int i = 0; i < 4; i++) {
		drops[i].setScale(0.5, 0.5);
	}
}
void choosedrop(RectangleShape blocks[], Clock& timeradd, Clock& timerdelete, int levelblocks) {
	int indexdrop = rand() % 4, indexblock = rand() % levelblocks;
	help help;
	if (timeradd.getElapsedTime().asSeconds() >= 6) {
		help.droptype = drops[indexdrop];
		help.targetshape = blocks[indexblock];
		help.type = indexdrop;
		help.droptype.setPosition(blocks[indexblock].getPosition().x, -100);
		dropbag.push_back(help);
		timeradd.restart();
	}if (timerdelete.getElapsedTime().asSeconds() >= 10) {
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
			if (!player.bullets.empty()) {
				player.bullets.clear();
				player.index -= player.currentmagazine;
			}
			player.droptype = dropbag[i].type;
			dropbag.erase(dropbag.begin() + i);
		}
	}
}

// shooting
void cheakdrop(Player& player) {
	if (player.droptype == -1) {
		return;
	}
	else {
		// 0 pistol , 1 rifle , 2 mini , 3 RPG 
		if (player.droptype == 0) {
			Bullet Bullet;
			Bullet.bulletsprite.setTexture(dropsTexture[4]);
			//Bullet.bulletsprite.setPosition(-100, -100); runtime error
			Bullet.cooldownuse = 10;
			Bullet.speed = 15;
			Bullet.Damage = 20;
			Bullet.magazin = 15;
			player.currentmagazine = 15;
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
			//Bullet.bulletsprite.setPosition(-100, -100); runtime error
			Bullet.cooldownuse = 4;
			Bullet.speed = 15;
			Bullet.Damage = 50;
			Bullet.magazin = 90;
			player.currentmagazine = 90;
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
			//Bullet.bulletsprite.setPosition(-100, -100); runtime error
			Bullet.cooldownuse = 2;
			Bullet.speed = 15;
			Bullet.Damage = 12;
			Bullet.magazin = 200;
			player.currentmagazine = 200;
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
			//Bullet.bulletsprite.setPosition(-100, -100); runtime error
			Bullet.cooldownuse = 10;
			Bullet.speed = 15;
			Bullet.Damage = 100;
			Bullet.magazin = 3;
			player.currentmagazine = 3;
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
void shooting(Player& player) {
	if (player.playertecture == 2) {
		player.bullets[player.index].bulletsprite.setPosition(player.sprite.getPosition().x + 10, player.sprite.getPosition().y - 20);
	}
	else {
		player.bullets[player.index].bulletsprite.setPosition(player.sprite.getPosition().x + 10, player.sprite.getPosition().y - 40);
	}
	player.shootcooldown = player.bullets[player.index].cooldownuse;
	player.bullets[player.index].moveto = player.last_key_pressed;
	player.index--;
	player.currentmagazine--;
	player.canshoot = false;
}
void bulletcooldown(Player& player) {
	if (player.shootcooldown > 0 && player.canshoot == false) {
		player.shootcooldown -= 0.5;
	}
	if (player.shootcooldown <= 0 && player.canshoot == false) {
		player.canshoot = true;
	}
}
void movebullets(vector<Bullet>& bullets, Player& player2) {
	for (int i = 0; i < bullets.size(); i++) {
		//move to left
		if (bullets[i].moveto == -1) {
			bullets[i].bulletsprite.move(-1 * bullets[i].speed, 0);
		}
		//move to right
		if (bullets[i].moveto == 1) {
			bullets[i].bulletsprite.move(1 * bullets[i].speed, 0);
		}
		if (bullets[i].bulletsprite.getPosition().x >= 1950 ||
			bullets[i].bulletsprite.getPosition().x <= -50) {
			bullets.erase(bullets.begin() + i);
		}
		else if (bullets[i].bulletsprite.getGlobalBounds().intersects(player2.sprite.getGlobalBounds())) {
			player2.health -= bullets[i].Damage;
			bullets.erase(bullets.begin() + i);
		}
	}
}

int MainMenu(RenderWindow& window, Clock& timer,Clock& clock) {
	Text playButton;
	Text mapsButton;
	Text exitButton;
	static int selectedOption = 0;

	playButton.setString("Play");
	playButton.setFont(font);
	playButton.setCharacterSize(50);
	playButton.setPosition(250, 250);
	playButton.setFillColor(sf::Color::White);

	mapsButton.setString("Maps");
	mapsButton.setFont(font);
	mapsButton.setCharacterSize(50);
	mapsButton.setPosition(250, 350);
	mapsButton.setFillColor(sf::Color::White);

	exitButton.setString("Exit");
	exitButton.setFont(font);
	exitButton.setCharacterSize(50);
	exitButton.setPosition(250, 450);
	exitButton.setFillColor(sf::Color::White);

	float time = timer.getElapsedTime().asSeconds();
	if (Keyboard::isKeyPressed(Keyboard::Up) && !(0.2 >= time)) {
		timer.restart();
		selectedOption = (selectedOption - 1 + 3) % 3;
	}
	else if (Keyboard::isKeyPressed(Keyboard::Down) && !(0.2 >= time))
	{
		timer.restart();
		selectedOption = (selectedOption + 1) % 3;
	}

	if (selectedOption == 0) {
		playButton.setFillColor(sf::Color::Red);
	}
	else if (selectedOption == 1) {
		mapsButton.setFillColor(sf::Color::Red);
	}
	else {
		exitButton.setFillColor(sf::Color::Red);
	}

	window.clear();
	window.draw(menu);
	window.draw(playButton);
	window.draw(mapsButton);
	window.draw(exitButton);
	window.display();

	// Example transition conditions
	if (Keyboard::isKeyPressed(Keyboard::Enter) && !(0.2 >= time)) {
		if (selectedOption == 0) {
			// Handle play button press
			timer.restart();
			clock.restart();
			play = true;
			return currentLevel;
		}
		else if (selectedOption == 1) {
			// Handle maps button press
			timer.restart();
			clock.restart();
			return MAPS_MENU_STATE;
		}
		else {
			// Handle exit button press
			window.close();
		}
	}

	// Return MainMenu state by default
	return MAIN_MENU_STATE;
}
int MapsMenu(RenderWindow& window, Clock& timer)
{
	for (int i = 0; i < 4; i++)
	{
		maps[i].setSize(Vector2f(500, 400));
		maps[i].setPosition(Vector2f((WIN_WIDTH - 500) / 2.0, (WIN_HEIGHT - 400) / 2.0));
		mapsBack[i].setSize(Vector2f(500, 400));
		mapsBack[i].setPosition(Vector2f((WIN_WIDTH - 500) / 2.0, (WIN_HEIGHT - 400) / 2.0));
		maps[i].setOutlineColor(Color::White);
		maps[i].setOutlineThickness(7);
		names[i].setString(mapNames[i]);
		names[i].setFont(font);
		names[i].setFillColor(Color::White);
		names[i].setCharacterSize(50);
		names[i].setPosition((WIN_WIDTH - 500) / 2.0 + 80, 570);
	}
	window.clear();
	window.draw(menu);
	window.draw(mapsBack[currentLevel]);
	window.draw(maps[currentLevel]);
	window.draw(names[currentLevel]);
	window.display();

	float time = timer.getElapsedTime().asSeconds();
	if (Keyboard::isKeyPressed(Keyboard::Escape))
	{
		return MAIN_MENU_STATE;
	}
	else if (Keyboard::isKeyPressed(Keyboard::Right) && !(0.2 >= time))
	{
		timer.restart();
		currentLevel = (currentLevel + 1) % 4;
	}
	else if (Keyboard::isKeyPressed(Keyboard::Left) && !(0.2 >= time))
	{
		timer.restart();
		currentLevel = (currentLevel - 1 + 4) % 4;
	}
	else if (Keyboard::isKeyPressed(Keyboard::Enter) && !(0.2 >= time))
	{
		timer.restart();
		return currentLevel;
	}
	return MAPS_MENU_STATE;
}
int level1(RenderWindow& window, Clock& timeradd, Clock& timerdelete,Clock& clock) {
	if (canfight) {
		choosedrop(cblocks, timeradd, timerdelete, level1blocks);
		dropfalling();
		dropcollision(player1);
		cheakdrop(player1);

		dropcollision(player2);
		cheakdrop(player2);


		if (player1.playertecture != 4) {
			player1.isWeaponed = true;
		}
		if (player2.playertecture != 4) {
			player2.isWeaponed = true;
		}

		if (player1.jumped == false) {
			player1.sprite.setTexture(playerTecture[player1.playertecture]);
			player1.sprite.setTextureRect(IntRect(0, 0, player1.spritelength / 9.00, player1.spriteheight / 2));
		}


		if (player2.jumped == false) {
			player2.sprite.setTexture(playerTecture[player2.playertecture]);
			player2.sprite.setTextureRect(IntRect(0, 0, player2.spritelength / 9.00, player2.spriteheight / 2));
		}

		if (Keyboard::isKeyPressed(Keyboard::Right) && player1.sprite.getPosition().x < 1900) {
			player1.last_key_pressed = 1;
			movement(player1);
		}

		if (Keyboard::isKeyPressed(Keyboard::Left) && player1.sprite.getPosition().x > 0) {
			player1.last_key_pressed = -1;
			movement(player1);
		}

		if (player1.index >= 0 && Keyboard::isKeyPressed(Keyboard::Space) && player1.canshoot) {
			shooting(player1);
		}

		bulletcooldown(player1);
		movebullets(player1.bullets, player2);

		jumping(player1, cblocks, level1blocks);

		if (Keyboard::isKeyPressed(Keyboard::D) && player2.sprite.getPosition().x < 1900) {
			player2.last_key_pressed = 1;
			movement(player2);
		}

		if (Keyboard::isKeyPressed(Keyboard::A) && player2.sprite.getPosition().x > 0) {
			player2.last_key_pressed = -1;
			movement(player2);
		}

		if (player2.index >= 0 && Keyboard::isKeyPressed(Keyboard::F) && player2.canshoot) {
			shooting(player2);
			cout << player1.health << " " << player2.health << endl;
		}

		bulletcooldown(player2);
		movebullets(player2.bullets, player1);

		jumping(player2, cblocks, level1blocks);
	}
	window.clear();

	window.draw(castleb);
	window.draw(castlef);
	for (int i = 0; i < 2; i++) {
		window.draw(cblocks[i]);
	}

	if (canfight) {
		window.draw(player1.sprite);
		window.draw(player2.sprite);
		healthBar(window);
	}

	for (int i = 0; i < dropbag.size(); i++) {
		window.draw(dropbag[i].droptype);
	}
	for (int i = 0; i < player1.bullets.size(); i++) {
		window.draw(player1.bullets[i].bulletsprite);
	}
	for (int i = 0; i < player2.bullets.size(); i++) {
		window.draw(player2.bullets[i].bulletsprite);
	}

	if(!canfight)
	displayfontfight(window, clock);

	window.display();

	if (play) {
		if (player1.health <= 0) {
			currentwinner = 2;
			clock.restart();
			canfight = false;
			playerproperties();
			restorefontfight();
			return LEVEL_2_STATE;
		}
		else if (player2.health <= 0) {
			currentwinner = 1;
			clock.restart();
			canfight = false;
			playerproperties();
			restorefontfight();
			return LEVEL_2_STATE;
		}
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
		play = false;
		canfight = false;
		clock.restart();
		playerproperties();
		restorefontfight();
		return MAIN_MENU_STATE;
	}

	return LEVEL_1_STATE;
}
int level2(RenderWindow& window, Clock& timeradd, Clock& timerdelete,Clock& clock) {
	if (canfight) {
		if (play) {
			if (currentwinner == 1) {
				winner(player1);
			}
			else if (currentwinner == 2) {
				winner(player2);
			}
		}

		choosedrop(wblocks, timeradd, timerdelete, level2blocks);
		dropfalling();
		dropcollision(player1);
		cheakdrop(player1);

		dropcollision(player2);
		cheakdrop(player2);


		if (player1.playertecture != 4) {
			player1.isWeaponed = true;
		}
		if (player2.playertecture != 4) {
			player2.isWeaponed = true;
		}

		if (player1.jumped == false) {
			player1.sprite.setTexture(playerTecture[player1.playertecture]);
			player1.sprite.setTextureRect(IntRect(0, 0, player1.spritelength / 9.00, player1.spriteheight / 2));
		}


		if (player2.jumped == false) {
			player2.sprite.setTexture(playerTecture[player2.playertecture]);
			player2.sprite.setTextureRect(IntRect(0, 0, player2.spritelength / 9.00, player2.spriteheight / 2));
		}

		if (Keyboard::isKeyPressed(Keyboard::Right) && player1.sprite.getPosition().x < 1900) {
			player1.last_key_pressed = 1;
			movement(player1);
		}

		if (Keyboard::isKeyPressed(Keyboard::Left) && player1.sprite.getPosition().x > 0) {
			player1.last_key_pressed = -1;
			movement(player1);
		}

		if (player1.index >= 0 && Keyboard::isKeyPressed(Keyboard::Space) && player1.canshoot) {
			shooting(player1);
		}

		bulletcooldown(player1);
		movebullets(player1.bullets, player2);

		jumping(player1, wblocks, level2blocks);

		if (Keyboard::isKeyPressed(Keyboard::D) && player2.sprite.getPosition().x < 1900) {
			player2.last_key_pressed = 1;
			movement(player2);
		}

		if (Keyboard::isKeyPressed(Keyboard::A) && player2.sprite.getPosition().x > 0) {
			player2.last_key_pressed = -1;
			movement(player2);
		}

		if (player2.index >= 0 && Keyboard::isKeyPressed(Keyboard::F) && player2.canshoot) {
			shooting(player2);
			cout << player1.health << " " << player2.health << endl;
		}

		bulletcooldown(player2);
		movebullets(player2.bullets, player1);

		jumping(player2, wblocks, level2blocks);
	}
	window.clear();

	window.draw(wback);
	window.draw(wfore);
	
	for (int i = 0; i < 10; i++) {
		window.draw(wblocks[i]);
	}

	if (canfight) {
		window.draw(player1.sprite);
		window.draw(player2.sprite);
		healthBar(window);
	}

	if (play&&canfight) {
		window.draw(winnercrown);
	}

	for (int i = 0; i < dropbag.size(); i++) {
		window.draw(dropbag[i].droptype);
	}
	for (int i = 0; i < player1.bullets.size(); i++) {
		window.draw(player1.bullets[i].bulletsprite);
	}
	for (int i = 0; i < player2.bullets.size(); i++) {
		window.draw(player2.bullets[i].bulletsprite);
	}

	if (!canfight)
	displayfontfight(window,clock);

	window.display();

	if (play) {
		if (player1.health <= 0) {
			currentwinner = 2;
			clock.restart();
			canfight = false;
			playerproperties();
			restorefontfight();
			return LEVEL_3_STATE;
		}
		else if (player2.health <= 0) {
			currentwinner = 1;
			clock.restart();
			canfight = false;
			playerproperties();
			restorefontfight();
			return LEVEL_3_STATE;
		}
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
		play = false;
		canfight = false;
		clock.restart();
		playerproperties();
		restorefontfight();
		return MAIN_MENU_STATE;
	}

	return LEVEL_2_STATE;
}
int level3(RenderWindow& window, Clock& timeradd, Clock& timerdelete,Clock& clock) {
	if (canfight) {
		if (play) {
			if (currentwinner == 1) {
				winner(player1);
			}
			else if (currentwinner == 2) {
				winner(player2);
			}
		}

		choosedrop(dblocks, timeradd, timerdelete, level3blocks);
		dropfalling();
		dropcollision(player1);
		cheakdrop(player1);

		dropcollision(player2);
		cheakdrop(player2);


		if (player1.playertecture != 4) {
			player1.isWeaponed = true;
		}
		if (player2.playertecture != 4) {
			player2.isWeaponed = true;
		}

		if (player1.jumped == false) {
			player1.sprite.setTexture(playerTecture[player1.playertecture]);
			player1.sprite.setTextureRect(IntRect(0, 0, player1.spritelength / 9.00, player1.spriteheight / 2));
		}


		if (player2.jumped == false) {
			player2.sprite.setTexture(playerTecture[player2.playertecture]);
			player2.sprite.setTextureRect(IntRect(0, 0, player2.spritelength / 9.00, player2.spriteheight / 2));
		}

		if (Keyboard::isKeyPressed(Keyboard::Right) && player1.sprite.getPosition().x < 1900) {
			player1.last_key_pressed = 1;
			movement(player1);
		}

		if (Keyboard::isKeyPressed(Keyboard::Left) && player1.sprite.getPosition().x > 0) {
			player1.last_key_pressed = -1;
			movement(player1);
		}

		if (player1.index >= 0 && Keyboard::isKeyPressed(Keyboard::Space) && player1.canshoot) {
			shooting(player1);
		}

		bulletcooldown(player1);
		movebullets(player1.bullets, player2);

		jumping(player1, dblocks, level3blocks);

		if (Keyboard::isKeyPressed(Keyboard::D) && player2.sprite.getPosition().x < 1900) {
			player2.last_key_pressed = 1;
			movement(player2);
		}

		if (Keyboard::isKeyPressed(Keyboard::A) && player2.sprite.getPosition().x > 0) {
			player2.last_key_pressed = -1;
			movement(player2);
		}

		if (player2.index >= 0 && Keyboard::isKeyPressed(Keyboard::F) && player2.canshoot) {
			shooting(player2);
			cout << player1.health << " " << player2.health << endl;
		}

		bulletcooldown(player2);
		movebullets(player2.bullets, player1);

		jumping(player2, dblocks, level3blocks);
	}

	window.clear();

	window.draw(dground);
	for (int i = 0; i < 11; i++) {
		window.draw(dblocks[i]);
	}

	if (canfight) {
		window.draw(player1.sprite);
		window.draw(player2.sprite);
		healthBar(window);
	}

	if (play&&canfight) {
		window.draw(winnercrown);
	}

	for (int i = 0; i < dropbag.size(); i++) {
		window.draw(dropbag[i].droptype);
	}
	for (int i = 0; i < player1.bullets.size(); i++) {
		window.draw(player1.bullets[i].bulletsprite);
	}
	for (int i = 0; i < player2.bullets.size(); i++) {
		window.draw(player2.bullets[i].bulletsprite);
	}

	window.draw(dfore);


	if (!canfight)
		displayfontfight(window, clock);

	window.display();

	if (play) {
		if (player1.health <= 0) {
			currentwinner = 2;
			clock.restart();
			canfight = false;
			playerproperties();
			restorefontfight();
			return LEVEL_4_STATE;
		}
		else if (player2.health <= 0) {
			currentwinner = 1;
			clock.restart();
			canfight = false;
			playerproperties();
			restorefontfight();
			return LEVEL_4_STATE;
		}
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
		play = false;
		canfight = false;
		clock.restart();
		playerproperties();
		restorefontfight();
		return MAIN_MENU_STATE;
	}

	return LEVEL_3_STATE;
}
int level4(RenderWindow& window, Clock& timeradd, Clock& timerdelete,Clock& clock) {
	if (canfight) {
		if (play) {
			if (currentwinner == 1) {
				winner(player1);
			}
			else if (currentwinner == 2) {
				winner(player2);
			}
		}

		choosedrop(bblocks, timeradd, timerdelete, level4blocks);
		dropfalling();
		dropcollision(player1);
		cheakdrop(player1);

		dropcollision(player2);
		cheakdrop(player2);


		if (player1.playertecture != 4) {
			player1.isWeaponed = true;
		}
		if (player2.playertecture != 4) {
			player2.isWeaponed = true;
		}

		if (player1.jumped == false) {
			player1.sprite.setTexture(playerTecture[player1.playertecture]);
			player1.sprite.setTextureRect(IntRect(0, 0, player1.spritelength / 9.00, player1.spriteheight / 2));
		}


		if (player2.jumped == false) {
			player2.sprite.setTexture(playerTecture[player2.playertecture]);
			player2.sprite.setTextureRect(IntRect(0, 0, player2.spritelength / 9.00, player2.spriteheight / 2));
		}

		if (Keyboard::isKeyPressed(Keyboard::Right) && player1.sprite.getPosition().x < 1900) {
			player1.last_key_pressed = 1;
			movement(player1);
		}

		if (Keyboard::isKeyPressed(Keyboard::Left) && player1.sprite.getPosition().x > 0) {
			player1.last_key_pressed = -1;
			movement(player1);
		}

		if (player1.index >= 0 && Keyboard::isKeyPressed(Keyboard::Space) && player1.canshoot) {
			shooting(player1);
		}

		bulletcooldown(player1);
		movebullets(player1.bullets, player2);

		jumping(player1, bblocks, level4blocks + 1);

		if (Keyboard::isKeyPressed(Keyboard::D) && player2.sprite.getPosition().x < 1900) {
			player2.last_key_pressed = 1;
			movement(player2);
		}

		if (Keyboard::isKeyPressed(Keyboard::A) && player2.sprite.getPosition().x > 0) {
			player2.last_key_pressed = -1;
			movement(player2);
		}

		if (player2.index >= 0 && Keyboard::isKeyPressed(Keyboard::F) && player2.canshoot) {
			shooting(player2);
			cout << player1.health << " " << player2.health << endl;
		}

		bulletcooldown(player2);
		movebullets(player2.bullets, player1);

		jumping(player2, bblocks, level4blocks + 1);
	}
	
	window.clear();

	window.draw(bground);
	for (int i = 0; i < 6; i++) {
		window.draw(bblocks[i]);
	}

	if (canfight) {
		window.draw(player1.sprite);
		window.draw(player2.sprite);
		healthBar(window);
	}

	if (play&&canfight) {
		window.draw(winnercrown);
	}

	for (int i = 0; i < dropbag.size(); i++) {
		window.draw(dropbag[i].droptype);
	}
	for (int i = 0; i < player1.bullets.size(); i++) {
		window.draw(player1.bullets[i].bulletsprite);
	}
	for (int i = 0; i < player2.bullets.size(); i++) {
		window.draw(player2.bullets[i].bulletsprite);
	}

	window.draw(bfore);


	if (!canfight)
		displayfontfight(window, clock);

	window.display();

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
		play = false;
		canfight = false;
		clock.restart();
		playerproperties();
		restorefontfight();
		return MAIN_MENU_STATE;
	}

	return LEVEL_4_STATE;
}
