#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
using namespace std;
using namespace sf;

struct Animation 
{
    sf::Texture texture;
    sf::Vector2u textSize;
    int frameNums;
    int currentFrame = 0;
    float switchTime = 0.05f;
    float totalTime = 0.0f;

    void update(float deltaTime)
    {
        totalTime += deltaTime;
        if (totalTime >= switchTime)
        {
            totalTime -= switchTime;
            currentFrame = (currentFrame + 1) % frameNums;
        }
    }

    sf::IntRect getCurrentFrameRect(int direction)
    {
        int top = 0; // Assuming the Animation frames are in a single row
        int left;
        if (direction < 0)
        {
            left = (frameNums - currentFrame) * (textSize.x / frameNums);
        }
        else 
        {
            left = currentFrame * (textSize.x / frameNums);
        }
        int step = direction * (textSize.x / frameNums);
        return sf::IntRect(left, top, step, textSize.y / 2);
    }
};

struct Weopon 
{
    int damage;
    float timeOfResponing;
    sf::Texture& texture;
    sf::Sprite sprite;
    bool isRender = false;
    float velocityY = 0.1f;
    int posX;

    void render(int winWidth)
    {
        winWidth -= texture.getSize().x;
        posX = rand() % winWidth;
        sprite.setTexture(texture);
        sprite.setPosition(posX, 10);
    }
};

struct Player 
{
    sf::Sprite sprite;
    int health = 10000;
    
    // Run Animation
    Animation runAnimation;
    int direction = 1;
    float velocityX = 0.0f;
    float velocityY = 6.0f;

    // Jump Animation
    Animation jumpAnimation;
    bool isJumping = false;

    // Boxing Animation
    Animation boxAnimation;

    // Shooting Animaion
    bool isWeaponed = false;

    void setRun(sf::Texture& texture, sf::Vector2u& textSize, int frameNums)
    {
        runAnimation.texture = texture;
        runAnimation.textSize = textSize;
        runAnimation.frameNums = frameNums;
        sprite.setTexture(texture);
        sprite.setTextureRect(runAnimation.getCurrentFrameRect(direction));
    }

    void setJump(sf::Texture& texture, sf::Vector2u& textSize, int frameNums)
    {
        jumpAnimation.texture = texture;
        jumpAnimation.textSize = textSize;
        jumpAnimation.frameNums = frameNums;
        sprite.setTexture(texture);
        sprite.setTextureRect(jumpAnimation.getCurrentFrameRect(direction));
    }

    void setBox(sf::Texture& texture, sf::Vector2u& textSize, int frameNums)
    {
        boxAnimation.texture = texture;
        boxAnimation.textSize = textSize;
        boxAnimation.frameNums = frameNums;
        sprite.setTexture(texture);
        sprite.setTextureRect(boxAnimation.getCurrentFrameRect(direction));
    }

    void moveRight(float deltaTime)
    {
        direction = 1;
        if (!isJumping)
        {
            runAnimation.update(deltaTime);
            sprite.setTextureRect(runAnimation.getCurrentFrameRect(direction));
        }
        velocityX = 5.0f;
    }

    void moveLeft(float deltaTime)
    {
        direction = -1;
        if (!isJumping)
        {
            runAnimation.update(deltaTime);
            sprite.setTextureRect(runAnimation.getCurrentFrameRect(direction));
        }
        velocityX = -5.0f;
    }

    void jump(float deltaTime)
    {
       velocityY = -5.0f;
       isJumping = true;
       jumpAnimation.update(deltaTime);
    }

    void box(float deltaTime, Player& other)
    {
        boxAnimation.update(deltaTime);
        sprite.setTextureRect(boxAnimation.getCurrentFrameRect(direction));
        if (sprite.getGlobalBounds().intersects(other.sprite.getGlobalBounds()))
        {
            other.health -= 1;
        }
    }

    void shoot()
    {

    }
};

int main()
{
    // create the window
    const int winWidth = 700, winHeight = 500;
    sf::RenderWindow window(sf::VideoMode(winWidth, winHeight), "My window");
    window.setFramerateLimit(60);

    // Health Code
    int x = 50 ; // the var for the rect
    bool damage = false ; // the click state   
    int health_points = 6 ; // in this example the health points => 6
    Texture Health_bar; // setting a texture
    Health_bar.loadFromFile("./sprites/health.png"); // the image of the texture
    Sprite bar; // setting a sprite that will have the texture within it 
    bar.setTexture(Health_bar); // connecting the the sprite to the texture
    bar.setTextureRect(IntRect( 0 ,0 , 50 , 20)); // cuting the part that i will use in the bar
    bar.setScale(Vector2f(3,3));//the scale of the bar 
    Sprite health ; // the same sprite
    health.setTexture(Health_bar); // the green line cooordinate 50 , 98 , 145 ,  193 , 241 , 289 
    health.setScale(Vector2f(3,3)); // scale
    Font health_num ;
    health_num.loadFromFile("./fonts/Glitch inside.otf");
    Text health_points_num ;
    health_points_num.setFont(health_num);
    String word = to_string (health_points) ;
    
    // Background
    sf::Texture ballBackground;
    ballBackground.loadFromFile("./backgrounds/ballback.png");
    sf::Sprite ballBack;
    ballBack.setTexture(ballBackground);
    float scaleX = window.getSize().x / (float)ballBackground.getSize().x;
    float scaleY = window.getSize().y / (float)ballBackground.getSize().y;
    ballBack.setScale(scaleX, scaleY);

    // Running Texture
    sf::Texture runningText;
    runningText.loadFromFile("./sprites/pistol.png");
    sf::Vector2u runTextSize = runningText.getSize();
    // Jumping Texture
    sf::Texture jumpingText;
    jumpingText.loadFromFile("./assets/jumping.png");
    sf::Vector2u jumpTextSize = jumpingText.getSize();
    // Box Texture
    sf::Texture boxingText;
    boxingText.loadFromFile("./assets/boxing.png");
    sf::Vector2u boxTextSize = boxingText.getSize();

    Player player1, player2;
    player1.setRun(runningText, runTextSize, 9);
    player1.sprite.setPosition(50, 50);

    player2.setRun(runningText, runTextSize, 9);
    player2.direction = -1;
    player2.sprite.setPosition(winWidth - 100, 50);

    // int score = 0;
    // sf::Font font;
    // font.loadFromFile("./fonts/font.ttf");
    // sf::Text text;
    // text.setFont(font);
    // text.setCharacterSize(50);
    // text.setPosition(winWidth / 2 - 100, 10);

    sf::RectangleShape ground[2];
    int gap = 40;
    ground[0].setSize(sf::Vector2f(winWidth / 2 - gap, 50));
    ground[0].setPosition(0, 400);
    ground[0].setFillColor(sf::Color::White);
    ground[1].setSize(sf::Vector2f(winWidth / 2 - gap, 50));
    ground[1].setPosition(winWidth / 2 + gap, 400);
    ground[1].setFillColor(sf::Color::White);
    
    float deltaTime;
    sf::Clock clock, timer;

    // Game Loop
    while (window.isOpen())
    {
        deltaTime = clock.restart().asSeconds();

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // Health Code
        if ( health_points > -1 ) {
       String word = to_string(health_points);
    	health_points_num.setString(word + "%") ; }
       if ( health_points < 7 && health_points > -1  ) {
       health.setTextureRect(IntRect( x ,45 , 50 , 20)) ; } // the health	  
    	// this is not for your project but ahmed had asked me how to set up a one click to attack

        // Keyboard Controls:
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
        {
            window.close();
        }

        // Player 1
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        {
            player1.moveRight(deltaTime);
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        {
            player1.moveLeft(deltaTime);
        }
        else 
        {
            player1.velocityX = 0.0f;
        }

        if (player1.sprite.getGlobalBounds().intersects(ground[0].getGlobalBounds()) || player1.sprite.getGlobalBounds().intersects(ground[1].getGlobalBounds()))
        {
            player1.isJumping = false;
            player1.velocityY = 0.0f;
            player1.setRun(runningText, runTextSize, 9);
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
            {
                player1.setRun(runningText, runTextSize, 9);
                player1.jump(deltaTime);
            }
        }
        else if (player1.isJumping)
        {
            player1.velocityY += 10.0f * deltaTime;
        }
        else 
        {
            player1.velocityY = 10.0f;
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && !damage)
        {
            if (player1.isWeaponed)
            {
                player1.shoot();
            }
            else
            {
                player1.setRun(runningText, runTextSize, 9);
                // player1.box(deltaTime, player2);
                damage = true ;
                health_points = health_points - 1;  
                x = x + 48;
            }
        }

        // Player 2
        if (player2.sprite.getGlobalBounds().intersects(ground[0].getGlobalBounds()) || player2.sprite.getGlobalBounds().intersects(ground[1].getGlobalBounds()))
        {
            player2.isJumping = false;
            player2.velocityY = 0.0f;
            player2.setRun(runningText, runTextSize, 9);
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
            {
                player2.setJump(jumpingText, jumpTextSize, 1);
                player2.jump(deltaTime);
            }
        }
        else if (player2.isJumping)
        {
            player2.velocityY += 0.98f * deltaTime;
        }
        else 
        {
            player2.velocityY = 5.0f;
        }

        window.clear(Color::Transparent);

        // draw everything here...
        window.draw(ballBack);
        window.draw(ground[0]);
        window.draw(ground[1]);
        window.draw(player1.sprite);
        window.draw(player2.sprite);
        window.draw(health);
        window.draw(bar); 
        window.draw(health_points_num);
        // text.setString("HP: " + std::to_string(player2.health));
        // window.draw(text);

        player1.sprite.move(player1.velocityX, player1.velocityY);
        player2.sprite.move(player2.velocityX, player2.velocityY);
        window.display();
    }
}

// =======
// #include <SFML/Graphics.hpp>
// #include <SFML/Audio.hpp>
// #include <iostream>
// #include <fstream>
// using namespace sf;
// using namespace std;
// #include"menu.h"; 
// int pagenumber = 1000;
// void pname(RenderWindow& window, string& name);
// void His(RenderWindow& window);
// int main()
// {
// 	RenderWindow window(VideoMode(1920, 1000), "Stick Fight");
// 	Texture picture;
// 	picture.loadFromFile("stickfight.png");
// 	Sprite background;
// 	background.setTexture(picture);
// 	menu menu(1920, 1000);
// 	string name;
// 	Music music;
// 	music.openFromFile("battle-of-the-dragons-8037 (online-audio-converter.com).ogg");
// 	music.play();
// 	while (true) {
// 		if (pagenumber == 1000) {
// 			while (window.isOpen())
// 			{
// 				Event event;
// 				while (window.pollEvent(event))
// 				{
// 					if (event.type == Event::Closed)
// 						window.close();
// 					break;
// 				}
// 				if (event.type == Event::KeyPressed) {
// 					if (event.key.code == Keyboard::Up) {
// 						menu.moveup();
// 					}

// 					if (event.key.code == Keyboard::Down) {
// 						menu.movedown();
// 					}
// 					if (event.key.code == Keyboard::Return) {
// 						if (menu.pressed() == 0) {
// 							pagenumber = 0;
// 						} if (menu.pressed() == 1) {
// 							pagenumber = 1;
// 						} if (menu.pressed() == 2) {
// 							pagenumber = -1;
// 						}

// 					}
// 				}


// 				window.clear();
// 				if (pagenumber != 1000) {
// 					break;
// 				}
// 				window.draw(background);
// 				menu.draw(window);
// 				window.display();
// 			}
// 			if (pagenumber == -1) {
// 				window.close();
// 				break;
// 			}
// 			if (pagenumber == 0) {
// 				pname(window, name);
// 			}
// 		}
// 	}
// 	return 0;

// }
// void pname(RenderWindow& window, string& name) {
// 	if (!name.empty()) {
// 		name.clear();
// 	}
// 	Texture pname1;
// 	pname1.loadFromFile("stickfight.png");
// 	Sprite bg;
// 	bg.setTexture(pname1);
// 	Font font;
// 	font.loadFromFile("C:\\Users\\evoo\\source\\repos\\Sfml\\DragonHunter-9Ynxj.otf");
// 	Text t1;
// 	Text t2;
// 	t1.setFont(font);
// 	t2.setFont(font);
// 	t1.setString("Enter your name");
// 	t1.setCharacterSize(70);
// 	t2.setCharacterSize(70);
// 	t1.setPosition(10, 10);
// 	t2.setPosition(10, 100);
// 	t1.setFillColor(Color::White);
// 	t2.setFillColor(Color::White);
// 	while (window.isOpen()) {
// 		Event event;
// 		while (window.pollEvent(event)) {
// 			if (event.type == Event::Closed) {
// 				window.close();
// 			}

// 			if (event.type == Event::TextEntered) {
// 				name += static_cast<char>(event.text.unicode);
// 			}
// 			if (Keyboard::isKeyPressed(Keyboard::BackSpace) && name.size() > 0) {
// 				name.resize(name.size() - 1);
// 			}
// 			if (Keyboard::isKeyPressed(Keyboard::Return) && name.size() > 1) {
// 				pagenumber = 3; //Game
// 				return;
// 			}
// 			if (Keyboard::isKeyPressed(Keyboard::Escape)) {
// 				pagenumber = 1000;
// 				return;
// 			}
// 		}
// 		t2.setString(name);
// 		window.clear();
// 		window.draw(bg);
// 		window.draw(t1);
// 		window.draw(t2);
// 		window.display();
// 	}
// }
// void His(RenderWindow& window) {
// 	Texture HistoryTex;
// 	HistoryTex.loadFromFile("stickfight.png");
// 	Sprite HistorySprit;
// 	HistorySprit.setTexture(HistoryTex);
// 	HistorySprit.setPosition(0, 0);
// 	Font font1;
// 	font1.loadFromFile("C:\\Users\\evoo\\source\\repos\\Sfml\\DragonHunter-9Ynxj.otf");
// 	Text text[100];

// 	for (int i = 0; i < 55; i++) {

// 		text[i].setFont(font1);

// 		text[i].setCharacterSize(50);

// 		text[i].setFillColor(Color::Green);
// 	}
// 	ifstream infile;
// 	infile.open("history.txt", ios::in);
// 	vector<string> lines;
// 	string line;
// 	while (getline(infile, line, '*')) {

// 		lines.push_back(line);
// 	}
// 	for (int i = 0; i < lines.size(); i++) {



// 		text[i].setString(lines[i]);

// 		text[i].setPosition(50, 100 * i);
// 	}
// 	while (window.isOpen()) {
// 		Event event;
// 		while (window.pollEvent(event)) {
// 			if (event.type == Event::Closed) {
// 				window.close();
// 			}

// 			if (Keyboard::isKeyPressed(Keyboard::Escape)) {
// 				pagenumber = 1000;
// 				return;
// 			}
// 			if (Keyboard::isKeyPressed(Keyboard::Key::Up)) {

// 				if (text[0].getPosition().y <= 5) {
// 					for (int i = 0; i < lines.size() + 10; i++) {
// 						text[i].move(0, -20);
// 					}
// 				}
// 			}
// 			if (Keyboard::isKeyPressed(Keyboard::Key::Down))
// 				if (text[(lines.size()) - 1].getPosition().y >= window.getPosition().y + 1000) {
// 					for (int i = 0; i < lines.size() + 10; i++) {
// 						text[i].move(0, -20);
// 					}
// 				}
// 		}
// 		cout << lines.size() << endl;
// 	}
// 	window.clear();
// 	window.draw(HistorySprit);
// 	for (int i = 0; i < lines.size(); i++)
// 	{
// 		window.draw(text[i]);
// 	}
// 	window.display();
// }




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
