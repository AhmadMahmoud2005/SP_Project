#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <iomanip> // for std::setprecision
#include <sstream> // for std::ostringstream

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
        return sf::IntRect(left, top, step, textSize.y);
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
    float velocityY = 0.2f;

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
        velocityX = 0.05f;
    }

    void moveLeft(float deltaTime)
    {
        direction = -1;
        if (!isJumping)
        {
            runAnimation.update(deltaTime);
            sprite.setTextureRect(runAnimation.getCurrentFrameRect(direction));
        }
        velocityX = -0.05f;
    }

    void jump(float deltaTime)
    {
       velocityY = -0.2f;
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
    window.clear(sf::Color(150, 150, 150));

    // Running Texture
    sf::Texture runningText;
    runningText.loadFromFile("./assets/running.png");
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

    int score = 0;
    sf::Font font;
    font.loadFromFile("./assets/font.ttf");
    sf::Text text;
    text.setFont(font);
    text.setCharacterSize(50);
    text.setPosition(winWidth / 2 - 100, 10);

    sf::RectangleShape ground[2];
    int gap = 40;
    ground[0].setSize(sf::Vector2f(winWidth / 2 - gap, 50));
    ground[0].setPosition(0, 400);
    ground[0].setFillColor(sf::Color::White);
    ground[1].setSize(sf::Vector2f(winWidth / 2 - gap, 50));
    ground[1].setPosition(winWidth / 2 + gap, 400);
    ground[1].setFillColor(sf::Color::White);

    sf::Clock clock;
    float deltaTime;
    

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

        // Keyboard Controls:
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
        {
            window.close();
            std::cout << deltaTime << '\n';
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
                player1.setJump(jumpingText, jumpTextSize, 1);
                player1.jump(deltaTime);
            }
        }
        else if (player1.isJumping)
        {
            player1.velocityY += 0.98f * deltaTime;
        }
        else 
        {
            player1.velocityY = 0.1f;
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
        {
            if (player1.isWeaponed)
            {
                player1.shoot();
            }
            else
            {
                player1.setBox(boxingText, boxTextSize, 7);
                player1.box(deltaTime, player2);
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
            player2.velocityY = 0.1f;
        }


        window.clear(sf::Color(150, 150, 150));

        // draw everything here...
        window.draw(ground[0]);
        window.draw(ground[1]);
        window.draw(player1.sprite);
        window.draw(player2.sprite);
        text.setString("HP: " + std::to_string(player2.health));
        window.draw(text);

        player1.sprite.move(player1.velocityX, player1.velocityY);
        player2.sprite.move(player2.velocityX, player2.velocityY);
        window.display();
    }
}

