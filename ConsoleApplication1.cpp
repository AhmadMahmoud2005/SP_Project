#include <SFML/Graphics.hpp>
#include<iostream>
using namespace std;
using namespace sf;

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
	float shootcooldown;
	int index = -1;

	// Run Animation
	/*Animation runAnimation;
	int direction = 1;
	float velocityX = 0.0f;
	float velocityY = 6.0f;
	*/

	// Jump Animation
	/*Animation jumpAnimation;
	bool isJumping = false;
	*/

	// Shooting Animaion
	bool isWeaponed = false;

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

	/*void setBox(sf::Texture& texture, sf::Vector2u& textSize, int frameNums)
	{
		boxAnimation.texture = texture;
		boxAnimation.textSize = textSize;
		boxAnimation.frameNums = frameNums;
		sprite.setTexture(texture);
		sprite.setTextureRect(boxAnimation.getCurrentFrameRect(direction));
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

	/*void box(float deltaTime, Player& other)
	{
		boxAnimation.update(deltaTime);
		sprite.setTextureRect(boxAnimation.getCurrentFrameRect(direction));
		if (sprite.getGlobalBounds().intersects(other.sprite.getGlobalBounds()))
		{
			other.health -= 1;
		}
	}*/
};
struct help {
    Sprite droptype; //drop
    RectangleShape targetshape; //block
    int type; // 0 , 1 , 2 , 3
    int indexdrop, indexblock;
};

vector<help>dropbag;
Sprite drops[4]; // 0 pistol , 1 rifle , 2 mini , 3 RPG
Texture playerTecture[5] , dropsTexture[8];
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


int main()
{
    RenderWindow window(VideoMode(1000, 1000), "game");
    window.setFramerateLimit(60);

	Clock timeradd, timerdelete;

	Player player1;
	player1.sprite.setPosition(50, 100);
	player1.sprite.setScale(0.7, 0.7);
	player1.sprite.setOrigin(125.375 / 2.00, 124.5 / 2.00);

    Texture bg , jump ;
    bg.loadFromFile("background.png");
	jump.loadFromFile("jump.png");
   

    RectangleShape background , grounds[3] ;
    background.setSize(Vector2f(1000, 1000));
    background.setPosition(0, 0);
    background.setTexture(&bg);

	grounds[0].setSize(Vector2f(170, 800));
	grounds[0].setPosition(0, 420);
	grounds[0].setFillColor(Color::Transparent);

	grounds[1].setSize(Vector2f(270, 100));
	grounds[1].setPosition(350, 425);
	grounds[1].setFillColor(Color::Transparent);

	grounds[2].setSize(Vector2f(170, 800));
	grounds[2].setPosition(830, 420);
	grounds[2].setFillColor(Color::Transparent);

	setplayertecture();
	setdrops();

	animation(player1);

	bool jumped=false , RPGpicked=false , grounded=false ;
	int a=0 , v=0 , delay=0 , ctrj = 0;
	int  last_key_pressed=1;

	while (window.isOpen())
	{
		choosedrop(grounds, timeradd, timerdelete);
		dropfalling();
		dropcollision(player1);

		if (grounded==false) {
			v += 0.01 * a;
			a++;
		}
		player1.sprite.move(0, v);

		Event evnt;
		while (window.pollEvent(evnt)) {
			if (evnt.type == Event::Closed) {
				window.close();
			}
		}
		if (Keyboard::isKeyPressed(Keyboard::Right)) {
			player1.sprite.move(5, 0);
			player1.sprite.setScale(0.7, 0.7);
			last_key_pressed = 1;
			if (jumped == false) {
				animation(player1);
			}

		}
		if (Keyboard::isKeyPressed(Keyboard::Left)) {
			player1.sprite.move(-5, 0);
			player1.sprite.setScale(-0.7, 0.7);
			last_key_pressed = 2;
			if (jumped == false) {
				animation(player1);
			}
		}
		if (player1.index >= 0 && Keyboard::isKeyPressed(Keyboard::A) && player1.canshoot) {
			player1.bullets[player1.index].bulletsprite.setPosition(player1.sprite.getPosition().x + 10, player1.sprite.getPosition().y - 40);
			player1.shootcooldown = player1.bullets[player1.index].cooldownuse;
			player1.bullets[player1.index].moveto = last_key_pressed;
			player1.index--;
			player1.canshoot = false;
		}
		cheakdrop(player1);
		bulletcooldown(player1);
		movebullets(player1.bullets);

		if (player1.sprite.getGlobalBounds().intersects(grounds[0].getGlobalBounds())||
			player1.sprite.getGlobalBounds().intersects(grounds[1].getGlobalBounds())||
			player1.sprite.getGlobalBounds().intersects(grounds[2].getGlobalBounds())){
			grounded = true;
			v = 0;
			a = 0;
		}
		else {
			grounded = false;
		}

        window.clear();

        window.draw(background);
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

        window.display();
    }
    return 0;
}

void setplayertecture() {
	playerTecture[0].loadFromFile("pistol.png");
	playerTecture[1].loadFromFile("AK.png");
	playerTecture[2].loadFromFile("MiniGun.png");
	playerTecture[3].loadFromFile("RPG.png");
	playerTecture[4].loadFromFile("walking.png");
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