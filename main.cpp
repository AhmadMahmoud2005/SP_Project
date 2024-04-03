#include <SFML/Graphics.hpp>
#include <iostream>

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
    int direction = 1;
    // Run Animation
    Animation runAnimation;

    // Jump Animation
    Animation jumpAnimation;
    bool isJumping = false;
    float jumpHeight = 100.0f;
    float velocityX = 0.0f;
    float velocityY = 0.2f;

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
       sprite.setTextureRect(jumpAnimation.getCurrentFrameRect(direction));
    }
};

int main()
{
    // create the window
    sf::RenderWindow window(sf::VideoMode(700, 500), "My window");
    window.clear(sf::Color(150, 150, 150));

    Player player1;
    // Running Texture
    sf::Texture runningText;
    runningText.loadFromFile("./assets/running.png");
    sf::Vector2u runTextSize = runningText.getSize();
    player1.setRun(runningText, runTextSize, 9);

    // Jumping Texture
    sf::Texture jumpingText;
    jumpingText.loadFromFile("./assets/jumping.png");
    sf::Vector2u jumpTextSize = jumpingText.getSize();

    sf::RectangleShape rect1(sf::Vector2f(500, 50));
    rect1.setPosition(0, 400);
    rect1.setFillColor(sf::Color::White);

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

        // Keyboard Controls
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

        if (player1.sprite.getGlobalBounds().intersects(rect1.getGlobalBounds()))
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

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
        {
            window.close();
        }

        window.clear(sf::Color(150, 150, 150));

        // draw everything here...
        window.draw(rect1);
        window.draw(player1.sprite);

        player1.sprite.move(player1.velocityX, player1.velocityY);
        window.display();
    }

    return 0;
}

