#include<iostream>
#include<SFML/Graphics.hpp>
#include<SFML/Audio.hpp>
#include<vector>
using namespace sf;
using namespace std;

// levels return values
const int MAIN_MENU_STATE = 0;
const int LEVEL_1_STATE = 1;
const int LEVEL_2_STATE = 2;
const int LEVEL_3_STATE = 3;
const int LEVEL_4_STATE = 4;
const int LEVEL_5_STATE = 5;

const int level1blocks = 2;
const int level2blocks = 10;
const int level3blocks = 11;
const int level4blocks = 6;

struct Bullet {
	float speed;
	Sprite bulletsprite;
	int magazin , moveto ;
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

	int last_key_pressed ;

	vector<Bullet>bullets;
	bool canshoot = false;
	float shootcooldown;
	int index = -1;
	int currentmagazine = 0;

	float jumpcurrentframe = 0;
	float velocity = 0, acceleration = 0;

	int playernumber;

	// Jump Animation
	/*Animation jumpAnimation;
	bool isJumping = false;
	*/



	/*void setRun(sf::Texture& texture, sf::Vector2u& textSize, int frameNums)
	{
		runAnimation.texture = texture;
		runAnimation.textSize = textSize;
		runAnimation.frameNums = frameNums;
		sprite.setTexture(texture);
		sprite.setTextureRect(runAnimation.getCurrentFrameRect(direction));
	}
	*/

	/*void setJump(sf::Texture& texture, sf::Vector2u& textSize, int frameNums)
	{
		jumpAnimation.texture = texture;
		jumpAnimation.textSize = textSize;
		jumpAnimation.frameNums = frameNums;
		sprite.setTexture(texture);
		sprite.setTextureRect(jumpAnimation.getCurrentFrameRect(direction));
	}
	*/

	/*void moveRight(float deltaTime)
	{
		direction = 1;
		if (!isJumping)
		{
			runAnimation.update(deltaTime);
			sprite.setTextureRect(runAnimation.getCurrentFrameRect(direction));
		}
		velocityX = 5.0f;
	}*/

	/*void moveLeft(float deltaTime)
	{
		direction = -1;
		if (!isJumping)
		{
			runAnimation.update(deltaTime);
			sprite.setTextureRect(runAnimation.getCurrentFrameRect(direction));
		}
		velocityX = -5.0f;
	}*/

	/*void jump(float deltaTime)
	{
		velocityY = -5.0f;
		isJumping = true;
		jumpAnimation.update(deltaTime);
	}*/

}player1, player2;
struct help {
	Sprite droptype; //drop
	RectangleShape targetshape; //block
	int type; // 0 , 1 , 2 , 3
};

vector<help>dropbag;

Sprite drops[4]; // 0 pistol , 1 rifle , 2 mini , 3 RPG 
Texture playerTecture[6], dropsTexture[8];

RectangleShape cblocks[2], wblocks[10], dblocks[11], bblocks[6]; //maps blocks
Sprite castleb, castlef, wback, wfore, dground, dfore, bground, bfore;

RectangleShape createRectangle(int length, int width, int xposition, int yposition);

void createSprite(Sprite& sprite ,Texture& texture, float scalex, float scaley);


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
void winner(Player& player, Sprite& winnercrown);

// drops(weapons)
void setdrops();
void choosedrop(RectangleShape blocks[], Clock& timeradd, Clock& timerdelete, int levelblocks);
void dropfalling();
void dropcollision(Player& player);

// shooting
void cheakdrop(Player& player);
void shooting(Player& player);
void bulletcooldown(Player& player);
void movebullets(vector<Bullet>& bullets ,Player& player2);

// levels
int MainMenu(RenderWindow& window);
int level1(RenderWindow& window, Clock& timeradd, Clock& timerdelete);
int level2(RenderWindow& window, Clock& timeradd, Clock& timerdelete);
int level3(RenderWindow& window, Clock& timeradd, Clock& timerdelete);
int level4(RenderWindow& window, Clock& timeradd, Clock& timerdelete);


int main() {

	RenderWindow window(VideoMode(1900, 1100), "GAME", Style::Default);
	window.setFramerateLimit(60);
	Clock timeradd, timerdelete;

	//map  (1)
	//castle map1
	Texture castleback;
	castleback.loadFromFile("castleb.png");
	createSprite(castleb, castleback, 1.6, 2);
	Texture castlefore;
	castlefore.loadFromFile("castlefore.png");
	castlef.setTexture(castlefore);
	castleblocks(cblocks);

	//map (2)
	//wood 
	Texture wbackground;
	wbackground.loadFromFile("wood.png");
	createSprite(wback, wbackground, 1.67, 1.7);
	Texture wforeground;
	wforeground.loadFromFile("woods.png");
	createSprite(wfore , wforeground, 0.84, 0.8);
	woodblocks(wblocks);

   //map  (3)
   //desert 
	Texture dback;
	dback.loadFromFile("desertb.png");
	createSprite(dground, dback, 1.5, 1.6);
	Texture desertfore;
	desertfore.loadFromFile("desertf.png");
	createSprite(dfore, desertfore, 1.5, 1.55);
	dfore.setPosition(Vector2f(0, 0));
	woodblocks(dblocks);
	for (int i = 0; i < 11; i++) {
		dblocks->setFillColor(Color::White);
	}

	//map (4)
	 //ball 
	Texture bback;
	bback.loadFromFile("ballback.png");
	createSprite(bground, bback, 1.5, 1.5);
	Texture ball;
	ball.loadFromFile("ballfore.png");
	createSprite(bfore,ball, 1.5, 1);
	bfore.setPosition(Vector2f(0, 330));
	ballblocks(bblocks);


	playerproperties();
	/*
	player1.sprite.setPosition(100, 100);
	player1.sprite.setScale(1, 1);
	player1.sprite.setOrigin(125.375 / 2.00, 124.5 / 2.00);
	player1.sprite.setTexture(playerTecture[player1.playertecture]);
	player1.sprite.setTextureRect(IntRect(player1.spritelength / 9.00, 0, player1.spritelength / 9.00, player1.spriteheight));
	player1.playernumber = 1;

	player2.sprite.setPosition(1500, 100);
	player2.sprite.setScale(-1, 1);
	player2.sprite.setOrigin(125.375 / 2.00, 124.5 / 2.00);
	player2.sprite.setTexture(playerTecture[player1.playertecture]);
	player2.sprite.setTextureRect(IntRect(player1.spritelength / 9.00, 0, player1.spritelength / 9.00, player1.spriteheight));
	player2.playernumber = 2;
	*/

	// crown
	Texture crown;
	crown.loadFromFile("crown.png");
	Sprite winnercrown;
	winnercrown.setTexture(crown);
	winnercrown.setScale(0.3, 0.3);

	setplayertecture();
	setdrops();

	cout << "Health1" << " " << "Health2" << endl;

	int currentState = 0;

	while (window.isOpen()) {
		Event evnt;
		while (window.pollEvent(evnt)) {
			if (evnt.type == Event::Closed) {
				window.close();
			}
		}
		switch (currentState) {
		case MAIN_MENU_STATE:
			currentState = MainMenu(window);
			break;
		case LEVEL_1_STATE:
			currentState = level1(window, timeradd, timeradd);
			break;
		case LEVEL_2_STATE:
			currentState = level2(window, timeradd, timeradd);
			break;
		case LEVEL_3_STATE:
			currentState = level3(window, timeradd, timeradd);
			break;
		case LEVEL_4_STATE:
			currentState = level4(window, timeradd, timeradd);
			break;
		}
		//level2(window, timeradd, timeradd);
		/*	winner(player1, winnercrown);

			choosedrop(grounds, timeradd, timerdelete);
			dropfalling();
			dropcollision(player1);
			cheakdrop(player1);

			dropcollision(player2);
			cheakdrop(player2);

			//delay++;

			if (player1.playertecture != 4) {
				player1.isWeaponed = true;
			}
			if (player2.playertecture != 4) {
				player2.isWeaponed = true;
			}

			if (player1.jumped==false) {
				player1.sprite.setTexture(playerTecture[player1.playertecture]);
				player1.sprite.setTextureRect(IntRect(0, 0, player1.spritelength / 9.00, player1.spriteheight/2 ));
			}


			if (player2.jumped == false) {
				player2.sprite.setTexture(playerTecture[player2.playertecture]);
				player2.sprite.setTextureRect(IntRect(0, 0, player2.spritelength / 9.00, player2.spriteheight/2 ));
			}

			if (Keyboard::isKeyPressed(Keyboard::Right) && player1.sprite.getPosition().x < 1000) {
				player1.last_key_pressed = 1;
				movement(player1);
			}

			if (Keyboard::isKeyPressed(Keyboard::Left) && player1.sprite.getPosition().x > 0) {
				player1.last_key_pressed = -1;
				movement(player1);
				}

			if (player1.index>=0 && Keyboard::isKeyPressed(Keyboard::Space) && player1.canshoot) {
				shooting(player1);
			}

			bulletcooldown(player1);
			movebullets(player1.bullets,player2);

			jumping(player1, grounds);

			if (Keyboard::isKeyPressed(Keyboard::D) && player2.sprite.getPosition().x < 1000) {
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
			movebullets(player2.bullets,player1);

			jumping(player2, grounds);

			//cout << player1.bullets.size() << " " << player1.index<< endl;

			// jumping
			/*
			if (player1.sprite.getGlobalBounds().intersects(grounds[0].getGlobalBounds()) ||
				player1.sprite.getGlobalBounds().intersects(grounds[1].getGlobalBounds()) ||
				player1.sprite.getGlobalBounds().intersects(grounds[2].getGlobalBounds())) {
				v = 0;
				a = 0;
				if (ctrj == 7) {
					ctrj = 0;
				}
				if (Keyboard::isKeyPressed(Keyboard::Up)) {
					v = 6;
					if (player1.isWeaponed == false) {
						player1.jumped = true;
					}
					else {
						player1.jumped = false;
					}
				}
			}
			else {
				v -= 0.01 * a;
				a++;
			}
			player1.sprite.move(0, -v);
			if (delay % 7 == 0) {
				if (player1.jumped==true) {
					player1.sprite.setTexture(jump);
					player1.sprite.setTextureRect(IntRect(ctrj * 1024 / 8.00, 0, 128, 128));
					ctrj++;
					if (ctrj == 7) {
						player1.jumped = false;
					}
				}
			}


			window.clear();

			window.draw(background);

			for (int i = 0; i < 3; i++) {
				window.draw(grounds[i]);
			}

			window.draw(player1.sprite);
			window.draw(player2.sprite);
			window.draw(winnercrown);

			for (int i = 0; i < dropbag.size(); i++) {
				window.draw(dropbag[i].droptype);
			}
			for (int i = 0; i < player1.bullets.size(); i++) {
					window.draw(player1.bullets[i].bulletsprite);
			}
			for (int i = 0; i < player2.bullets.size(); i++) {
				window.draw(player2.bullets[i].bulletsprite);
			}

			window.display();

			*/
	}
		return 0;
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
	//ballground
	bblocks[0] = createRectangle(2000, 150, 0, 1020);
	//ball block1
	bblocks[1] = createRectangle(420, 150, 1500, 890);
	//ball block2
	bblocks[2] = createRectangle(280, 150, 470, 890);
	//ball block3
	bblocks[3] = createRectangle(300, 150, 810, 890);
	//ball block4
	bblocks[4] = createRectangle(275, 150, 1170, 890);
	//ball block5
	bblocks[5] = createRectangle(420, 150, 0, 890);
};

// player
void playerproperties() {
	player1.sprite.setPosition(100, 100);
	player1.sprite.setScale(1, 1);
	player1.sprite.setOrigin(125.375 / 2.00, 124.5 / 2.00);
	player1.sprite.setTexture(playerTecture[player1.playertecture]);
	player1.sprite.setTextureRect(IntRect(player1.spritelength / 9.00, 0, player1.spritelength / 9.00, player1.spriteheight));
	player1.playernumber = 1;
	player1.last_key_pressed = 1;

	player2.sprite.setPosition(1500, 100);
	player2.sprite.setScale(-1, 1);
	player2.sprite.setOrigin(125.375 / 2.00, 124.5 / 2.00);
	player2.sprite.setTexture(playerTecture[player1.playertecture]);
	player2.sprite.setTextureRect(IntRect(player1.spritelength / 9.00, 0, player1.spritelength / 9.00, player1.spriteheight));
	player2.playernumber = 2;
	player2.last_key_pressed = -1;
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
	player.sprite.setTextureRect(IntRect((int)player.currentframe * player.spritelength / 8.00, 0, player.spritelength / 8.00, player.spriteheight/2));
}
void movement(Player& player) {
	player.sprite.move(5 * player.last_key_pressed, 0);
	player.sprite.setScale(0.7 * player.last_key_pressed, 0.7);
	if (player.jumped == false) {
		animation(player);
	}
}
bool checkcollide(Player& player, RectangleShape blocks[],int levelblocks ) {
	bool collide = false;
	for (int i = 0; i < levelblocks; i++) {
		if (player.sprite.getGlobalBounds().intersects(blocks[i].getGlobalBounds())) {
	if (player.sprite.getGlobalBounds().top < blocks[i].getGlobalBounds().top) {
		collide = true;
	}
	else if (player.sprite.getGlobalBounds().top+player.sprite.getGlobalBounds().height<blocks[i].getGlobalBounds().top+ blocks[i].getGlobalBounds().height)
	{
		collide = false;
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
	if (checkcollide(player, blocks,blocksnumber)) {
		player.velocity = 0;
		player.acceleration = 0;
		if (player.jumpcurrentframe >= 7) {
			player.jumpcurrentframe = 0;
		}
		if (player.playernumber == 1) {
			if (Keyboard::isKeyPressed(Keyboard::Up)) {
				player.velocity = 6;
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

				player.velocity = 6;
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
void winner(Player& player, Sprite& winnercrown) {
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
			winnercrown.setPosition(player.sprite.getPosition().x-17, player.sprite.getPosition().y - 55);
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
void choosedrop(RectangleShape blocks[] , Clock& timeradd , Clock& timerdelete, int levelblocks) {
	int indexdrop = rand() % 4,indexblock = rand() % levelblocks;
	help help;
	if (timeradd.getElapsedTime().asSeconds() >= 6) {
		help.droptype = drops[indexdrop];
		help.targetshape= blocks[indexblock];
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
			player.droptype=dropbag[i].type;
			dropbag.erase(dropbag.begin() + i);
		}
	}
}

// shooting
void cheakdrop(Player& player ) {
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
void movebullets(vector<Bullet>& bullets ,Player& player2) {
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

int MainMenu(RenderWindow& window) {
	window.clear();
	// Draw your main menu here
	window.display();

	// Example transition conditions
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1)) {
		return LEVEL_1_STATE;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2)) {
		return LEVEL_2_STATE;
	}
	else if (sf::Keyboard::isKeyPressed(Keyboard::Num3)) {
		return LEVEL_3_STATE;
	}
	else if (sf::Keyboard::isKeyPressed(Keyboard::Num4)) {
		return LEVEL_4_STATE;
	}

	// Return MainMenu state by default
	return MAIN_MENU_STATE;
}
int level1(RenderWindow& window, Clock& timeradd, Clock& timerdelete) {
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

	jumping(player1, cblocks,level1blocks);

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

	jumping(player2, cblocks,level1blocks);

	//cout << player1.bullets.size() << " " << player1.index<< endl;

	// jumping
	/*
	if (player1.sprite.getGlobalBounds().intersects(grounds[0].getGlobalBounds()) ||
		player1.sprite.getGlobalBounds().intersects(grounds[1].getGlobalBounds()) ||
		player1.sprite.getGlobalBounds().intersects(grounds[2].getGlobalBounds())) {
		v = 0;
		a = 0;
		if (ctrj == 7) {
			ctrj = 0;
		}
		if (Keyboard::isKeyPressed(Keyboard::Up)) {
			v = 6;
			if (player1.isWeaponed == false) {
				player1.jumped = true;
			}
			else {
				player1.jumped = false;
			}
		}
	}
	else {
		v -= 0.01 * a;
		a++;
	}
	player1.sprite.move(0, -v);
	if (delay % 7 == 0) {
		if (player1.jumped==true) {
			player1.sprite.setTexture(jump);
			player1.sprite.setTextureRect(IntRect(ctrj * 1024 / 8.00, 0, 128, 128));
			ctrj++;
			if (ctrj == 7) {
				player1.jumped = false;
			}
		}
	}
	*/

	window.clear();

	window.draw(castleb);
	for (int i = 0; i < 2; i++) {
		window.draw(cblocks[i]);
	}

	window.draw(player1.sprite);
	window.draw(player2.sprite);
	//window.draw(winnercrown);

	for (int i = 0; i < dropbag.size(); i++) {
		window.draw(dropbag[i].droptype);
	}
	for (int i = 0; i < player1.bullets.size(); i++) {
		window.draw(player1.bullets[i].bulletsprite);
	}
	for (int i = 0; i < player2.bullets.size(); i++) {
		window.draw(player2.bullets[i].bulletsprite);
	}

	window.draw(castlef);

	window.display();

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
		playerproperties();
		return MAIN_MENU_STATE;
	}

	return LEVEL_1_STATE;
}
int level2(RenderWindow& window, Clock& timeradd, Clock& timerdelete) {
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

	jumping(player1, wblocks,level2blocks);

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

	jumping(player2, wblocks,level2blocks);

	//cout << player1.bullets.size() << " " << player1.index<< endl;

	// jumping
	/*
	if (player1.sprite.getGlobalBounds().intersects(grounds[0].getGlobalBounds()) ||
		player1.sprite.getGlobalBounds().intersects(grounds[1].getGlobalBounds()) ||
		player1.sprite.getGlobalBounds().intersects(grounds[2].getGlobalBounds())) {
		v = 0;
		a = 0;
		if (ctrj == 7) {
			ctrj = 0;
		}
		if (Keyboard::isKeyPressed(Keyboard::Up)) {
			v = 6;
			if (player1.isWeaponed == false) {
				player1.jumped = true;
			}
			else {
				player1.jumped = false;
			}
		}
	}
	else {
		v -= 0.01 * a;
		a++;
	}
	player1.sprite.move(0, -v);
	if (delay % 7 == 0) {
		if (player1.jumped==true) {
			player1.sprite.setTexture(jump);
			player1.sprite.setTextureRect(IntRect(ctrj * 1024 / 8.00, 0, 128, 128));
			ctrj++;
			if (ctrj == 7) {
				player1.jumped = false;
			}
		}
	}
	*/

	window.clear();

	window.draw(wback);
	for (int i = 0; i < 10; i++) {
		window.draw(wblocks[i]);
	}

	window.draw(player1.sprite);
	window.draw(player2.sprite);
	//window.draw(winnercrown);

	for (int i = 0; i < dropbag.size(); i++) {
		window.draw(dropbag[i].droptype);
	}
	for (int i = 0; i < player1.bullets.size(); i++) {
		window.draw(player1.bullets[i].bulletsprite);
	}
	for (int i = 0; i < player2.bullets.size(); i++) {
		window.draw(player2.bullets[i].bulletsprite);
	}

	window.draw(wfore);

	window.display();

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
		playerproperties();
		return MAIN_MENU_STATE;
	}

	return LEVEL_2_STATE;
}
int level3(RenderWindow& window, Clock& timeradd, Clock& timerdelete) {
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

	jumping(player1, dblocks,level3blocks);

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

	jumping(player2, dblocks,level3blocks);

	//cout << player1.bullets.size() << " " << player1.index<< endl;

	// jumping
	/*
	if (player1.sprite.getGlobalBounds().intersects(grounds[0].getGlobalBounds()) ||
		player1.sprite.getGlobalBounds().intersects(grounds[1].getGlobalBounds()) ||
		player1.sprite.getGlobalBounds().intersects(grounds[2].getGlobalBounds())) {
		v = 0;
		a = 0;
		if (ctrj == 7) {
			ctrj = 0;
		}
		if (Keyboard::isKeyPressed(Keyboard::Up)) {
			v = 6;
			if (player1.isWeaponed == false) {
				player1.jumped = true;
			}
			else {
				player1.jumped = false;
			}
		}
	}
	else {
		v -= 0.01 * a;
		a++;
	}
	player1.sprite.move(0, -v);
	if (delay % 7 == 0) {
		if (player1.jumped==true) {
			player1.sprite.setTexture(jump);
			player1.sprite.setTextureRect(IntRect(ctrj * 1024 / 8.00, 0, 128, 128));
			ctrj++;
			if (ctrj == 7) {
				player1.jumped = false;
			}
		}
	}
	*/

	window.clear();

	window.draw(dground);
	for (int i = 0; i < 11; i++) {
		window.draw(dblocks[i]);
	}

	window.draw(player1.sprite);
	window.draw(player2.sprite);
	//window.draw(winnercrown);

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

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
		playerproperties();
		return MAIN_MENU_STATE;
	}

	window.display();
	return LEVEL_3_STATE;
}
int level4(RenderWindow& window, Clock& timeradd, Clock& timerdelete) {
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

	jumping(player1, bblocks,level4blocks);

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

	jumping(player2, bblocks,level4blocks);

	//cout << player1.bullets.size() << " " << player1.index<< endl;

	// jumping
	/*
	if (player1.sprite.getGlobalBounds().intersects(grounds[0].getGlobalBounds()) ||
		player1.sprite.getGlobalBounds().intersects(grounds[1].getGlobalBounds()) ||
		player1.sprite.getGlobalBounds().intersects(grounds[2].getGlobalBounds())) {
		v = 0;
		a = 0;
		if (ctrj == 7) {
			ctrj = 0;
		}
		if (Keyboard::isKeyPressed(Keyboard::Up)) {
			v = 6;
			if (player1.isWeaponed == false) {
				player1.jumped = true;
			}
			else {
				player1.jumped = false;
			}
		}
	}
	else {
		v -= 0.01 * a;
		a++;
	}
	player1.sprite.move(0, -v);
	if (delay % 7 == 0) {
		if (player1.jumped==true) {
			player1.sprite.setTexture(jump);
			player1.sprite.setTextureRect(IntRect(ctrj * 1024 / 8.00, 0, 128, 128));
			ctrj++;
			if (ctrj == 7) {
				player1.jumped = false;
			}
		}
	}
	*/

	window.clear();

	window.draw(bground);
	for (int i = 0; i < 6; i++) {
		window.draw(bblocks[i]);
	}

	window.draw(player1.sprite);
	window.draw(player2.sprite);
	//window.draw(winnercrown);

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

	window.display();

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
		playerproperties();
		return MAIN_MENU_STATE;
	}

	return LEVEL_4_STATE;
}
