#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include "maps.h"
#include "player.h"
using namespace sf;
using namespace std;


Texture texture;
int frameNums;
int currentFrame;
float switchTime;
float totalTime;
int top;
int left;
int step;





struct Weopon
{
    int damage;
    float timeOfResponing;
    Texture& texture;
    Sprite sprite;
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
struct Animation
{
    Texture texture;
    Vector2u textSize;
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

    IntRect getCurrentFrameRect(int direction)
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
        return IntRect(left, top, step, textSize.y);
    }
};
struct Player
{
    Sprite sprite;
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

    void setRun(Texture& texture, Vector2u& textSize, int frameNums)
    {
        runAnimation.texture = texture;
        runAnimation.textSize = textSize;
        runAnimation.frameNums = frameNums;
        sprite.setTexture(texture);
        sprite.setTextureRect(runAnimation.getCurrentFrameRect(direction));
    }

    void setJump(Texture& texture, Vector2u& textSize, int frameNums)
    {
        jumpAnimation.texture = texture;
        jumpAnimation.textSize = textSize;
        jumpAnimation.frameNums = frameNums;
        sprite.setTexture(texture);
        sprite.setTextureRect(jumpAnimation.getCurrentFrameRect(direction));
    }

    void setBox(Texture& texture, Vector2u& textSize, int frameNums)
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




    int main()
    {

        // create the window
        const int winWidth = 700, winHeight = 500;
        RenderWindow window(VideoMode(winWidth, winHeight), "My window");
        window.clear(Color(150, 150, 150));

        //inside the main;
        Texture runningText;
        Texture jumpingText;
        Texture boxingText;
        Font font;
        int score;
        Text text;
        int gap;
        Texture gunText;
        float deltaTime;
        Sprite weopon;
        //colllision
        bool isGrounded = false;









        //maps
        // //events variables
        bool leftmouseclick = 0;
        int rectxposition = 0;
        int rectyposition = 0;

        //castle map1
        Texture castleback;
        castleback.loadFromFile("castleb.png");
        Sprite castleb;
        castleb.setTexture(castleback);
        castleb.setScale(1.6, 2);
        Texture castlefore;
        castlefore.loadFromFile("castlefore.png");
        Sprite castlef;
        castlef.setTexture(castlefore);

        //ground left
        RectangleShape blockl;
        blockl.setSize(Vector2f(700, 240));
        blockl.setPosition(Vector2f(0, 860));
        blockl.setFillColor(Color::Black);

        //ground right
        RectangleShape blockr;
        blockr.setSize(Vector2f(700, 250));
        blockr.setPosition(Vector2f(1170, 870));
        blockr.setFillColor(Color::Black);

        //wood map2
        Texture back;
        back.loadFromFile("wood.png");
        Sprite ground;
        ground.setTexture(back);
        ground.setScale(1.67, 1.7);
        Texture tree;
        tree.loadFromFile("woods.png");
        Sprite fore;
        fore.setTexture(tree);
        fore.setScale(0.84, 0.8);

        //wood ground
        RectangleShape woodlong;
        woodlong.setPosition(Vector2f(98, 911));
        woodlong.setSize(Vector2f(1739, 100));
        woodlong.setFillColor(Color::Black);
        //wood middle level 1
        RectangleShape wblock1;
        wblock1.setPosition(Vector2f(757, 735));
        wblock1.setSize(Vector2f(417, 250));
        wblock1.setFillColor(Color::Black);
        //wood float 1 l
        RectangleShape wblock2;
        wblock2.setPosition(Vector2f(53, 656));
        wblock2.setSize(Vector2f(200, 50));
        wblock2.setFillColor(Color::Black);
        //wood float 1 r
        RectangleShape wblock3;
        wblock3.setPosition(Vector2f(1680, 650));
        wblock3.setSize(Vector2f(200, 50));
        wblock3.setFillColor(Color::Black);
        //wood float 2 l
        RectangleShape wblock4;
        wblock4.setPosition(Vector2f(405, 530));
        wblock4.setSize(Vector2f(200, 40));
        wblock4.setFillColor(Color::Black);
        //wood float 2 l
        RectangleShape wblock5;
        wblock5.setPosition(Vector2f(1330, 530));
        wblock5.setSize(Vector2f(203, 40));
        wblock5.setFillColor(Color::Black);
        //wood float 3 l
        RectangleShape wblock6;
        wblock6.setPosition(Vector2f(759, 493));
        wblock6.setSize(Vector2f(152, 50));
        wblock6.setFillColor(Color::Black);
        //wood float 3 r
        RectangleShape wblock7;
        wblock7.setPosition(Vector2f(1022, 493));
        wblock7.setSize(Vector2f(152, 50));
        wblock7.setFillColor(Color::Black);
        //wood ground l
        RectangleShape wblock8;
        wblock8.setPosition(Vector2f(350, 818));
        wblock8.setSize(Vector2f(65, 100));
        wblock8.setFillColor(Color::Black);
        //wood ground r
        RectangleShape wblock9;
        wblock9.setPosition(Vector2f(1518, 818));
        wblock9.setSize(Vector2f(65, 100));
        wblock9.setFillColor(Color::Black);


        //desert map3
        Texture dback;
        dback.loadFromFile("desertb.png");
        Sprite dground;
        dground.setTexture(dback);
        dground.setScale(1.5, 1.6);
        Texture desertfore;
        desertfore.loadFromFile("desertf.png");
        Sprite dfore;
        dfore.setTexture(desertfore);
        dfore.setPosition(Vector2f(0, 0));
        dfore.setScale(1.5, 1.55);
        //desert blocks
        //left float
        RectangleShape block1;
        block1.setSize(Vector2f(440, 100));
        block1.setPosition(Vector2f(425, 577));
        block1.setFillColor(Color::Transparent);
        //right float
        RectangleShape block2;
        block2.setSize(Vector2f(400, 100));
        block2.setPosition(Vector2f(1130, 590));
        block2.setFillColor(Color::Transparent);
        //floor
        RectangleShape block3;
        block3.setSize(Vector2f(95, 395));
        block3.setPosition(Vector2f(910, 0));
        block3.setFillColor(Color::Transparent);
        //tall ground
        RectangleShape block4;
        block4.setSize(Vector2f(1550, 80));
        block4.setPosition(Vector2f(185, 980));
        block4.setFillColor(Color::Transparent);
        //level 1 m
        RectangleShape block5;
        block5.setSize(Vector2f(400, 80));
        block5.setPosition(Vector2f(760, 900));
        block5.setFillColor(Color::Transparent);
        //level 1 l
        RectangleShape block6;
        block6.setSize(Vector2f(235, 80));
        block6.setPosition(Vector2f(195, 900));
        block6.setFillColor(Color::Transparent);
        //level 1 r
        RectangleShape block7;
        block7.setSize(Vector2f(235, 80));
        block7.setPosition(Vector2f(1490, 900));
        block7.setFillColor(Color::Transparent);
        //level 2 l
        RectangleShape block8;
        block8.setSize(Vector2f(160, 80));
        block8.setPosition(Vector2f(195, 820));
        block8.setFillColor(Color::Transparent);
        //level 2 r
        RectangleShape block9;
        block9.setSize(Vector2f(160, 80));
        block9.setPosition(Vector2f(1570, 820));
        block9.setFillColor(Color::Transparent);
        //level 2 m
        RectangleShape block10;
        block10.setSize(Vector2f(235, 80));
        block10.setPosition(Vector2f(845, 820));
        block10.setFillColor(Color::Transparent);
        //level 3 m
        RectangleShape block11;
        block11.setSize(Vector2f(80, 80));
        block11.setPosition(Vector2f(925, 740));
        block11.setFillColor(Color::Transparent);

        //ball map 4
        Texture bback;
        bback.loadFromFile("ballback.png");
        Sprite bground;
        bground.setTexture(bback);
        bground.setScale(1.5, 1.5);
        Texture ball;
        ball.loadFromFile("ballfore.png");
        Sprite bfore;
        bfore.setTexture(ball);
        bfore.setPosition(Vector2f(0, 330));
        bfore.setScale(1.5, 1);
        //ballground
        RectangleShape balllong;
        balllong.setPosition(Vector2f(0, 1020));
        balllong.setSize(Vector2f(2000, 150));
        balllong.setFillColor(Color::Black);
        //ball block1
        RectangleShape bblock1;
        bblock1.setPosition(Vector2f(1500, 890));
        bblock1.setSize(Vector2f(420, 150));
        bblock1.setFillColor(Color::Black);
        //ball block2
        RectangleShape bblock2;
        bblock2.setPosition(Vector2f(470, 890));
        bblock2.setSize(Vector2f(280, 150));
        bblock2.setFillColor(Color::Black);
        //ball block3
        RectangleShape bblock3;
        bblock3.setPosition(Vector2f(810, 890));
        bblock3.setSize(Vector2f(300, 150));
        bblock3.setFillColor(Color::Black);
        //ball block4
        RectangleShape bblock4;
        bblock4.setPosition(Vector2f(1170, 890));
        bblock4.setSize(Vector2f(275, 150));
        bblock4.setFillColor(Color::Black);
        //ball block5
        RectangleShape bblock5;
        bblock5.setPosition(Vector2f(0, 890));
        bblock5.setSize(Vector2f(420, 150));
        bblock5.setFillColor(Color::Black);

        //factory map 5
        Texture factoryback;
        factoryback.loadFromFile("factoryback.png");
        Sprite factorybackg;
        factorybackg.setTexture(factoryback);
        factorybackg.setScale(1.5, 1.7);
        Texture factoryfore;
        factoryfore.loadFromFile("factoryfore.png");
        Sprite factoryforeg;
        factoryforeg.setTexture(factoryfore);
        factoryforeg.setScale(0.745, 0.7);

        //factory block1
        RectangleShape fblock1;
        fblock1.setPosition(Vector2f(645, 590));
        fblock1.setSize(Vector2f(635, 90));
        fblock1.setFillColor(Color::Black);
        //factory block2
        RectangleShape fblock2;
        fblock2.setPosition(Vector2f(1255, 917));
        fblock2.setSize(Vector2f(700, 90));
        fblock2.setFillColor(Color::Black);
        //factory block3
        RectangleShape fblock3;
        fblock3.setPosition(Vector2f(0, 917));
        fblock3.setSize(Vector2f(700, 90));
        fblock3.setFillColor(Color::Black);




        // Running Texture
        Texture runningText;
        runningText.loadFromFile("./assets/running.png");
        Vector2u runTextSize = runningText.getSize();
        // Jumping Texture
        Texture jumpingText;
        jumpingText.loadFromFile("./assets/jumping.png");
        Vector2u jumpTextSize = jumpingText.getSize();
        // Box Texture
        Texture boxingText;
        boxingText.loadFromFile("./assets/boxing.png");
        Vector2u boxTextSize = boxingText.getSize();

        Player player1, player2;
        player1.setRun(runningText, runTextSize, 9);
        player1.sprite.setPosition(50, 50);

        player2.setRun(runningText, runTextSize, 9);
        player2.direction = -1;
        player2.sprite.setPosition(winWidth - 100, 50);

        int score = 0;
        Font font;
        font.loadFromFile("./assets/font.ttf");
        Text text;
        text.setFont(font);
        text.setCharacterSize(50);
        text.setPosition(winWidth / 2 - 100, 10);


        Texture gunText;
        gunText.loadFromFile("./assets/weopon.png");
        Weopon gun = { 1, 3.0f, gunText };
        Sprite weopon; weopon.setTexture(gunText);

        float deltaTime;
        Clock clock, timer;

        // Game Loop
        while (window.isOpen())
        {
            deltaTime = clock.restart().asSeconds();

            Event event;
            while (window.pollEvent(event))
            {
                if (event.type == Event::Closed)
                    window.close();
            }

            // Keyboard Controls:
            if (Keyboard::isKeyPressed(Keyboard::Escape))
            {
                window.close();
            }

            // Player 1
            if (Keyboard::isKeyPressed(Keyboard::Right))
            {
                player1.moveRight(deltaTime);
            }
            else if (Keyboard::isKeyPressed(Keyboard::Left))
            {
                player1.moveLeft(deltaTime);
            }
            else
            {
                player1.velocityX = 0.0f;
            }




            if (Keyboard::isKeyPressed(Keyboard::Space))
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



            void setRun(Texture & texture, Vector2u & textSize, int frameNums)
                ; {}

            void setJump(Texture & texture, Vector2u & textSize, int frameNums)
                ; {}

            void setBox(Texture & texture, Vector2u & textSize, int frameNums)
                ; {}


            void moveRight(float deltaTime)
                ; {}

            void moveLeft(float deltaTime)
                ; {}

            void jump(float deltaTime)
                ; {}

            void box(float deltaTime, Player & other)
                ; {};

            void shoot()

                ; {}


            void update(float deltaTime) {

            };

        }
        //check them later
        //collisons 
        //desert map
        FloatRect playerbounds = player1.sprite.getGlobalBounds();
        if (playerbounds.intersects(block1.getGlobalBounds()))
        {
            if (playerbounds.left < block1.getGlobalBounds().left)
            {
                velocityX = 0;
                player1.sprite.setPosition(player1.sprite.getPosition().y && player1.sprite.getPosition().x - 5);
            }
            else if (playerbounds.left + playerbounds.width > block1.getGlobalBounds().left + block1.getGlobalBounds().width)
            {
                player1.direction.x = -abs(player1.direction.x);

            else  if (playerbounds.top < block1.getGlobalBounds().top)
            {
                velocityY = 0;
                isGrounded = true;
            }
            else if (playerbounds.top + playerbounds.hight < block1.getGlobalBounds().top + block1.getGlobalBounds().hight)
            {
                isGrounded = false;
                velocityY = -velocityY;
            }
            //block2

            if (playerbounds.intersects(block2.getGlobalBounds()))
            {
                if (playerbounds.left < block2.getGlobalBounds().left)
                {
                    velocityX = 0;
                    player1.sprite.setPosition(player1.sprite.getPosition().y && player1.sprite.getPosition().x - 5);
                }
                else if (playerbounds.left + playerbounds.width > block2.getGlobalBounds().left + block2.getGlobalBounds().width)
                {
                    player1.direction.x = -abs(player1.direction.x);

                else  if (playerbounds.top < block2.getGlobalBounds().top)
                {
                    velocityY = 0;
                    isGrounded = true;
                }
                else if (playerbounds.top + playerbounds.hight < block2.getGlobalBounds().top + block2.getGlobalBounds().hight)
                {
                    isGrounded = false;
                    velocityY = -velocityY;
                }
                }

                //block3

                if (playerbounds.intersects(block3.getGlobalBounds()))
                {
                    if (playerbounds.left < block3.getGlobalBounds().left)
                    {
                        velocityX = 0;
                        player1.sprite.setPosition(player1.sprite.getPosition().y && player1.sprite.getPosition().x - 5);
                    }
                    else if (playerbounds.left + playerbounds.width > block3.getGlobalBounds().left + block3.getGlobalBounds().width)
                    {
                        player1.direction.x = -abs(player1.direction.x);

                    else  if (playerbounds.top < block3.getGlobalBounds().top)
                    {
                        velocityY = 0;
                        isGrounded = true;
                    }
                    else if (playerbounds.top + playerbounds.hight < block3.getGlobalBounds().top + block3.getGlobalBounds().hight)
                    {
                        isGrounded = false;
                        velocityY = -velocityY;
                    }
                    }

                    //block4

                    if (playerbounds.intersects(block4.getGlobalBounds()))
                    {
                        if (playerbounds.left < block4.getGlobalBounds().left)
                        {
                            velocityX = 0;
                            player1.sprite.setPosition(player1.sprite.getPosition().y && player1.sprite.getPosition().x - 5);
                        }
                        else if (playerbounds.left + playerbounds.width > block2.getGlobalBounds().left + block4.getGlobalBounds().width)
                        {
                            player1.direction.x = -abs(player1.direction.x);

                        else  if (playerbounds.top < block4.getGlobalBounds().top)
                        {
                            velocityY = 0;
                            isGrounded = true;
                        }
                        else if (playerbounds.top + playerbounds.hight < block4.getGlobalBounds().top + block4.getGlobalBounds().hight)
                        {
                            isGrounded = false;
                            velocityY = -velocityY;
                        }
                        }

                        //block5

                        if (playerbounds.intersects(block5.getGlobalBounds()))
                        {
                            if (playerbounds.left < block5.getGlobalBounds().left)
                            {
                                velocityX = 0;
                                player1.sprite.setPosition(player1.sprite.getPosition().y && player1.sprite.getPosition().x - 5);
                            }
                            else if (playerbounds.left + playerbounds.width > block5.getGlobalBounds().left + block5.getGlobalBounds().width)
                            {
                                player1.direction.x = -abs(player1.direction.x);

                            else  if (playerbounds.top < block5.getGlobalBounds().top)
                            {
                                velocityY = 0;
                                isGrounded = true;
                            }
                            else if (playerbounds.top + playerbounds.hight < block5.getGlobalBounds().top + block5.getGlobalBounds().hight)
                            {
                                isGrounded = false;
                                velocityY = -velocityY;
                            }
                            }


                            //block6

                            if (playerbounds.intersects(block6.getGlobalBounds()))
                            {
                                if (playerbounds.left < block6.getGlobalBounds().left)
                                {
                                    velocityX = 0;
                                    player1.sprite.setPosition(player1.sprite.getPosition().y && player1.sprite.getPosition().x - 5);
                                }
                                else if (playerbounds.left + playerbounds.width > block6.getGlobalBounds().left + block6.getGlobalBounds().width)
                                {
                                    player1.direction.x = -abs(player1.direction.x);

                                else  if (playerbounds.top < block6.getGlobalBounds().top)
                                {
                                    velocityY = 0;
                                    isGrounded = true;
                                }
                                else if (playerbounds.top + playerbounds.hight < block6.getGlobalBounds().top + block6.getGlobalBounds().hight)
                                {
                                    isGrounded = false;
                                    velocityY = -velocityY;
                                }
                                }


                                //block7

                                if (playerbounds.intersects(block7.getGlobalBounds()))
                                {
                                    if (playerbounds.left < block7.getGlobalBounds().left)
                                    {
                                        velocityX = 0;
                                        player1.sprite.setPosition(player1.sprite.getPosition().y && player1.sprite.getPosition().x - 5);
                                    }
                                    else if (playerbounds.left + playerbounds.width > block2.getGlobalBounds().left + block7.getGlobalBounds().width)
                                    {
                                        player1.direction.x = -abs(player1.direction.x);

                                    else  if (playerbounds.top < block7.getGlobalBounds().top)
                                    {
                                        velocityY = 0;
                                        isGrounded = true;
                                    }
                                    else if (playerbounds.top + playerbounds.hight < block7.getGlobalBounds().top + block7.getGlobalBounds().hight)
                                    {
                                        isGrounded = false;
                                        velocityY = -velocityY;
                                    }
                                    }





                                    //block8

                                    if (playerbounds.intersects(block8.getGlobalBounds()))
                                    {
                                        if (playerbounds.left < block8.getGlobalBounds().left)
                                        {
                                            velocityX = 0;
                                            player1.sprite.setPosition(player1.sprite.getPosition().y && player1.sprite.getPosition().x - 5);
                                        }
                                        else if (playerbounds.left + playerbounds.width > block8.getGlobalBounds().left + block8.getGlobalBounds().width)
                                        {
                                            player1.direction.x = -abs(player1.direction.x);

                                        else  if (playerbounds.top < block8.getGlobalBounds().top)
                                        {
                                            velocityY = 0;
                                            isGrounded = true;
                                        }
                                        else if (playerbounds.top + playerbounds.hight < block8.getGlobalBounds().top + block8.getGlobalBounds().hight)
                                        {
                                            isGrounded = false;
                                            velocityY = -velocityY;
                                        }
                                        }
                                        //block9

                                        if (playerbounds.intersects(block9.getGlobalBounds()))
                                        {
                                            if (playerbounds.left < block9.getGlobalBounds().left)
                                            {
                                                velocityX = 0;
                                                player1.sprite.setPosition(player1.sprite.getPosition().y && player1.sprite.getPosition().x - 5);
                                            }
                                            else if (playerbounds.left + playerbounds.width > block9.getGlobalBounds().left + block9.getGlobalBounds().width)
                                            {
                                                player1.direction.x = -abs(player1.direction.x);

                                            else  if (playerbounds.top < block9.getGlobalBounds().top)
                                            {
                                                velocityY = 0;
                                                isGrounded = true;
                                            }
                                            else if (playerbounds.top + playerbounds.hight < block9.getGlobalBounds().top + block9.getGlobalBounds().hight)
                                            {
                                                isGrounded = false;
                                                velocityY = -velocityY;
                                            }
                                            }







                                            //block10

                                            if (playerbounds.intersects(block10.getGlobalBounds()))
                                            {
                                                if (playerbounds.left < block10.getGlobalBounds().left)
                                                {
                                                    velocityX = 0;
                                                    player1.sprite.setPosition(player1.sprite.getPosition().y && player1.sprite.getPosition().x - 5);
                                                }
                                                else if (playerbounds.left + playerbounds.width > block10.getGlobalBounds().left + block10.getGlobalBounds().width)
                                                {
                                                    player1.direction.x = -abs(player1.direction.x);

                                                else  if (playerbounds.top < block10.getGlobalBounds().top)
                                                {
                                                    velocityY = 0;
                                                    isGrounded = true;
                                                }
                                                else if (playerbounds.top + playerbounds.hight < block10.getGlobalBounds().top + block10.getGlobalBounds().hight)
                                                {
                                                    isGrounded = false;
                                                    velocityY = -velocityY;
                                                }
                                                }




                                                //block11

                                                if (playerbounds.intersects(block11.getGlobalBounds()))
                                                {
                                                    if (playerbounds.left < block11.getGlobalBounds().left)
                                                    {
                                                        velocityX = 0;
                                                        player1.sprite.setPosition(player1.sprite.getPosition().y && player1.sprite.getPosition().x - 5);
                                                    }
                                                    else if (playerbounds.left + playerbounds.width > block11.getGlobalBounds().left + block11.getGlobalBounds().width)
                                                    {
                                                        player1.direction.x = -abs(player1.direction.x);

                                                    else  if (playerbounds.top < block11.getGlobalBounds().top)
                                                    {
                                                        velocityY = 0;
                                                        isGrounded = true;
                                                    }
                                                    else if (playerbounds.top + playerbounds.hight < block11.getGlobalBounds().top + block11.getGlobalBounds().hight)
                                                    {
                                                        isGrounded = false;
                                                        velocityY = -velocityY;
                                                    }
                                                    }





                                                    if (playerbounds.intersects(dfore.getGlobalBounds()))
                                                    {
                                                        if (playerbounds.left < dfore.getGlobalBounds().left)
                                                        {
                                                            velocityX = 0;
                                                            player1.sprite.setPosition(player1.sprite.getPosition().y && player1.sprite.getPosition().x - 5);
                                                        }
                                                        else if (playerbounds.left + playerbounds.width > dfore.getGlobalBounds().left + dfore.getGlobalBounds().width)
                                                        {
                                                            player1.direction.x = -abs(player1.direction.x);

                                                        else  if (playerbounds.top < block11.getGlobalBounds().top)
                                                        {
                                                            velocityY = 0;
                                                            isGrounded = true;
                                                        }
                                                        else if (playerbounds.top + playerbounds.hight < dfore.getGlobalBounds().top + dfore.getGlobalBounds().hight)
                                                        {
                                                            isGrounded = false;
                                                            velocityY = -velocityY;
                                                        }
                                                        }








                                                        if (playerbounds.intersects(dground.getGlobalBounds()))
                                                        {
                                                            if (playerbounds.left < dground.getGlobalBounds().left)
                                                            {
                                                                velocityX = 0;
                                                                player1.sprite.setPosition(player1.sprite.getPosition().y && player1.sprite.getPosition().x - 5);
                                                            }
                                                            else if (playerbounds.left + playerbounds.width > dground.getGlobalBounds().left + dground.getGlobalBounds().width)
                                                            {
                                                                player1.direction.x = -abs(player1.direction.x);

                                                            else  if (playerbounds.top < block11.getGlobalBounds().top)
                                                            {
                                                                velocityY = 0;
                                                                isGrounded = true;
                                                            }
                                                            else if (playerbounds.top + playerbounds.hight < dground.getGlobalBounds().top + dground.getGlobalBounds().hight)
                                                            {
                                                                isGrounded = false;
                                                                velocityY = -velocityY;
                                                            }
                                                            }


                                                            //WOOD MAP
                                                        //BLOCK 1
                                                            if (playerbounds.intersects(wblock1.getGlobalBounds())
                                                            {
                                                                if (playerbounds.left < wblock1.getGlobalBounds().left)
                                                                {
                                                                    velocityX = 0;
                                                                    player1.sprite.setPosition(player1.sprite.getPosition().y && player1.sprite.getPosition().x - 5);
                                                                }
                                                                else if (playerbounds.left + playerbounds.width > wblock1.getGlobalBounds().left + wblock1.getGlobalBounds().width)
                                                                {
                                                                    player1.direction.x = -abs(player1.direction.x);
                                                                }

                                                                else  if (playerbounds.top < wblock1.getGlobalBounds().top)
                                                                {
                                                                    velocityY = 0;
                                                                    isGrounded = true;
                                                                }
                                                                else if (playerbounds.top + playerbounds.height < wblock1.getGlobalBounds().top + wblock1.getGlobalBounds().height)
                                                                {
                                                                    isGrounded = false;
                                                                    velocityY = -velocityY;
                                                                }

                                                            }







                                                            //block2

                                                            if (playerbounds.intersects(wblock1.getGlobalBounds())
                                                            {
                                                                if (playerbounds.left < wblock2.getGlobalBounds().left)
                                                                {
                                                                    velocityX = 0;
                                                                    player1.sprite.setPosition(player1.sprite.getPosition().y && player1.sprite.getPosition().x - 5);
                                                                }
                                                                else if (playerbounds.left + playerbounds.width > wblock2.getGlobalBounds().left + wblock2.getGlobalBounds().width)
                                                                {
                                                                    player1.direction.x = -abs(player1.direction.x);
                                                                }

                                                                else  if (playerbounds.top < wblock2.getGlobalBounds().top)
                                                                {
                                                                    velocityY = 0;
                                                                    isGrounded = true;
                                                                }
                                                                else if (playerbounds.top + playerbounds.height < wblock2.getGlobalBounds().top + wblock2.getGlobalBounds().height)
                                                                {
                                                                    isGrounded = false;
                                                                    velocityY = -velocityY;
                                                                }

                                                            }




                                                            //block 3
                                                            if (playerbounds.intersects(wblock3.getGlobalBounds())
                                                            {
                                                                if (playerbounds.left < wblock3.getGlobalBounds().left)
                                                                {
                                                                    velocityX = 0;
                                                                    player1.sprite.setPosition(player1.sprite.getPosition().y && player1.sprite.getPosition().x - 5);



                                                                else if (playerbounds.left + playerbounds.width > wblock3.getGlobalBounds().left + wblock3.getGlobalBounds().width)
                                                                {
                                                                    player1.direction.x = -abs(player1.direction.x);
                                                                }

                                                                else  if (playerbounds.top < wblock3.getGlobalBounds().top)
                                                                {
                                                                    velocityY = 0;
                                                                    isGrounded = true;
                                                                }
                                                                else if (playerbounds.top + playerbounds.height < wblock3.getGlobalBounds().top + wblock3.getGlobalBounds().height)
                                                                {
                                                                    isGrounded = false;
                                                                    velocityY = -velocityY;
                                                                }
                                                                }

                                                                //block4


                                                                if (playerbounds.intersects(wblock4.getGlobalBounds())
                                                                {
                                                                    if (playerbounds.left < wblock4.getGlobalBounds().left)
                                                                    {
                                                                        velocityX = 0;
                                                                        player1.sprite.setPosition(player1.sprite.getPosition().y && player1.sprite.getPosition().x - 5);
                                                                    }
                                                                    else if (playerbounds.left + playerbounds.width > wblock4.getGlobalBounds().left + wblock4.getGlobalBounds().width)
                                                                    {
                                                                        player1.direction.x = -abs(player1.direction.x);
                                                                    }

                                                                    else  if (playerbounds.top < wblock4.getGlobalBounds().top)
                                                                    {
                                                                        velocityY = 0;
                                                                        isGrounded = true;
                                                                    }
                                                                    else if (playerbounds.top + playerbounds.height < wblock4.getGlobalBounds().top + wblock4.getGlobalBounds().height)
                                                                    {
                                                                        isGrounded = false;
                                                                        velocityY = -velocityY;
                                                                    }

                                                                }


                                                                //block 5

                                                                if (playerbounds.intersects(wblock5.getGlobalBounds())
                                                                {
                                                                    if (playerbounds.left < wblock5.getGlobalBounds().left)
                                                                    {
                                                                        velocityX = 0;
                                                                        player1.sprite.setPosition(player1.sprite.getPosition().y && player1.sprite.getPosition().x - 5);
                                                                    }
                                                                    else if (playerbounds.left + playerbounds.width > wblock5.getGlobalBounds().left + wblock5.getGlobalBounds().width)
                                                                    {
                                                                        player1.direction.x = -abs(player1.direction.x);
                                                                    }

                                                                    else  if (playerbounds.top < wblock5.getGlobalBounds().top)
                                                                    {
                                                                        velocityY = 0;
                                                                        isGrounded = true;
                                                                    }
                                                                    else if (playerbounds.top + playerbounds.height < wblock5.getGlobalBounds().top + wblock5.getGlobalBounds().height)
                                                                    {
                                                                        isGrounded = false;
                                                                        velocityY = -velocityY;
                                                                    }

                                                                }
                                                                //block6


                                                                if (playerbounds.intersects(wblock6.getGlobalBounds())
                                                                {
                                                                    if (playerbounds.left < wblock6.getGlobalBounds().left)
                                                                    {
                                                                        velocityX = 0;
                                                                        player1.sprite.setPosition(player1.sprite.getPosition().y && player1.sprite.getPosition().x - 5);
                                                                    }
                                                                    else if (playerbounds.left + playerbounds.width > wblock6.getGlobalBounds().left + wblock6.getGlobalBounds().width)
                                                                    {
                                                                        player1.direction.x = -abs(player1.direction.x);
                                                                    }

                                                                    else  if (playerbounds.top < wblock6.getGlobalBounds().top)
                                                                    {
                                                                        velocityY = 0;
                                                                        isGrounded = true;
                                                                    }
                                                                    else if (playerbounds.top + playerbounds.height < wblock6.getGlobalBounds().top + wblock6.getGlobalBounds().height)
                                                                    {
                                                                        isGrounded = false;
                                                                        velocityY = -velocityY;
                                                                    }

                                                                }


                                                                //block 7




                                                                if (playerbounds.intersects(wblock7.getGlobalBounds())
                                                                {
                                                                    if (playerbounds.left < wblock7.getGlobalBounds().left)
                                                                    {
                                                                        velocityX = 0;
                                                                        player1.sprite.setPosition(player1.sprite.getPosition().y && player1.sprite.getPosition().x - 5);
                                                                    }
                                                                    else if (playerbounds.left + playerbounds.width > wblock7.getGlobalBounds().left + wblock7.getGlobalBounds().width)
                                                                    {
                                                                        player1.direction.x = -abs(player1.direction.x);
                                                                    }

                                                                    else  if (playerbounds.top < wblock7.getGlobalBounds().top)
                                                                    {
                                                                        velocityY = 0;
                                                                        isGrounded = true;
                                                                    }
                                                                    else if (playerbounds.top + playerbounds.height < wblock7.getGlobalBounds().top + wblock7.getGlobalBounds().height)
                                                                    {
                                                                        isGrounded = false;
                                                                        velocityY = -velocityY;
                                                                    }

                                                                }

                                                                //block 8


                                                                if (playerbounds.intersects(wblock8.getGlobalBounds())
                                                                {
                                                                    if (playerbounds.left < wblock8.getGlobalBounds().left)
                                                                    {
                                                                        velocityX = 0;
                                                                        player1.sprite.setPosition(player1.sprite.getPosition().y && player1.sprite.getPosition().x - 5);
                                                                    }
                                                                    else if (playerbounds.left + playerbounds.width > wblock8.getGlobalBounds().left + wblock8.getGlobalBounds().width)
                                                                    {
                                                                        player1.direction.x = -abs(player1.direction.x);
                                                                    }

                                                                    else  if (playerbounds.top < wblock8.getGlobalBounds().top)
                                                                    {
                                                                        velocityY = 0;
                                                                        isGrounded = true;
                                                                    }
                                                                    else if (playerbounds.top + playerbounds.height < wblock8.getGlobalBounds().top + wblock8.getGlobalBounds().height)
                                                                    {
                                                                        isGrounded = false;
                                                                        velocityY = -velocityY;
                                                                    }

                                                                }
                                                                //block 9

                                                                if (playerbounds.intersects(wblock9.getGlobalBounds())
                                                                {
                                                                    if (playerbounds.left < wblock9.getGlobalBounds().left)
                                                                    {
                                                                        velocityX = 0;
                                                                        player1.sprite.setPosition(player1.sprite.getPosition().y && player1.sprite.getPosition().x - 5);
                                                                    }
                                                                    else if (playerbounds.left + playerbounds.width > wblock9.getGlobalBounds().left + wblock9.getGlobalBounds().width)
                                                                    {
                                                                        player1.direction.x = -abs(player1.direction.x);
                                                                    }

                                                                    else  if (playerbounds.top < wblock9.getGlobalBounds().top)
                                                                    {
                                                                        velocityY = 0;
                                                                        isGrounded = true;
                                                                    }
                                                                    else if (playerbounds.top + playerbounds.height < wblock9.getGlobalBounds().top + wblock9.getGlobalBounds().height)
                                                                    {
                                                                        isGrounded = false;
                                                                        velocityY = -velocityY;
                                                                    }

                                                                }


                                                                //ground

                                                                if (playerbounds.intersects(ground.getGlobalBounds())
                                                                {
                                                                    if (playerbounds.left < ground.getGlobalBounds().left)
                                                                    {
                                                                        velocityX = 0;
                                                                        player1.sprite.setPosition(player1.sprite.getPosition().y && player1.sprite.getPosition().x - 5);
                                                                    }
                                                                    else if (playerbounds.left + playerbounds.width > ground.getGlobalBounds().left + ground.getGlobalBounds().width)
                                                                    {
                                                                        player1.direction.x = -abs(player1.direction.x);
                                                                    }

                                                                    else  if (playerbounds.top < ground.getGlobalBounds().top)
                                                                    {
                                                                        velocityY = 0;
                                                                        isGrounded = true;
                                                                    }
                                                                    else if (playerbounds.top + playerbounds.height < ground.getGlobalBounds().top + ground.getGlobalBounds().height)
                                                                    {
                                                                        isGrounded = false;
                                                                        velocityY = -velocityY;
                                                                    }

                                                                }


                                                                if (playerbounds.intersects(woodlong.getGlobalBounds())
                                                                {
                                                                    if (playerbounds.left < woodlong.getGlobalBounds().left)
                                                                    {
                                                                        velocityX = 0;
                                                                        player1.sprite.setPosition(player1.sprite.getPosition().y && player1.sprite.getPosition().x - 5);
                                                                    }
                                                                    else if (playerbounds.left + playerbounds.width > woodlong.getGlobalBounds().left + woodlong.getGlobalBounds().width)
                                                                    {
                                                                        player1.direction.x = -abs(player1.direction.x);
                                                                    }

                                                                    else  if (playerbounds.top < woodlong.getGlobalBounds().top)
                                                                    {
                                                                        velocityY = 0;
                                                                        isGrounded = true;
                                                                    }
                                                                    else if (playerbounds.top + playerbounds.height < woodlong.getGlobalBounds().top + woodlong.getGlobalBounds().height)
                                                                    {
                                                                        isGrounded = false;
                                                                        velocityY = -velocityY;
                                                                    }

                                                                }

                                                                //fore

                                                                if (playerbounds.intersects(fore.getGlobalBounds())
                                                                {
                                                                    if (playerbounds.left < fore.getGlobalBounds().left)
                                                                    {
                                                                        velocityX = 0;
                                                                        player1.sprite.setPosition(player1.sprite.getPosition().y && player1.sprite.getPosition().x - 5);
                                                                    }
                                                                    else if (playerbounds.left + playerbounds.width > fore.getGlobalBounds().left + fore.getGlobalBounds().width)
                                                                    {
                                                                        player1.direction.x = -abs(player1.direction.x);
                                                                    }

                                                                    else  if (playerbounds.top < fore.getGlobalBounds().top)
                                                                    {
                                                                        velocityY = 0;
                                                                        isGrounded = true;
                                                                    }
                                                                    else if (playerbounds.top + playerbounds.height < fore.getGlobalBounds().top + fore.getGlobalBounds().height)
                                                                    {
                                                                        isGrounded = false;
                                                                        velocityY = -velocityY;
                                                                    }

                                                                }

                                                                //fore


                                                                if (playerbounds.intersects(fore.getGlobalBounds())
                                                                {
                                                                    if (playerbounds.left < fore.getGlobalBounds().left)
                                                                    {
                                                                        velocityX = 0;
                                                                        player1.sprite.setPosition(player1.sprite.getPosition().y && player1.sprite.getPosition().x - 5);
                                                                    }
                                                                    else if (playerbounds.left + playerbounds.width > fore.getGlobalBounds().left + fore.getGlobalBounds().width)
                                                                    {
                                                                        player1.direction.x = -abs(player1.direction.x);
                                                                    }

                                                                    else  if (playerbounds.top < fore.getGlobalBounds().top)
                                                                    {
                                                                        velocityY = 0;
                                                                        isGrounded = true;
                                                                    }
                                                                    else if (playerbounds.top + playerbounds.height < fore.getGlobalBounds().top + fore.getGlobalBounds().height)
                                                                    {
                                                                        isGrounded = false;
                                                                        velocityY = -velocityY;
                                                                    }

                                                                }




                                                                //ball map
                                                                //bground
                                                                if (playerbounds.intersects(bground.getGlobalBounds())
                                                                {
                                                                    if (playerbounds.left < bground.getGlobalBounds().left)
                                                                    {
                                                                        velocityX = 0;
                                                                        player1.sprite.setPosition(player1.sprite.getPosition().y && player1.sprite.getPosition().x - 5);
                                                                    }
                                                                    else if (playerbounds.left + playerbounds.width > bground.getGlobalBounds().left + bground.getGlobalBounds().width)
                                                                    {
                                                                        player1.direction.x = -abs(player1.direction.x);
                                                                    }

                                                                    else  if (playerbounds.top < bground.getGlobalBounds().top)
                                                                    {
                                                                        velocityY = 0;
                                                                        isGrounded = true;
                                                                    }
                                                                    else if (playerbounds.top + playerbounds.height < bground.getGlobalBounds().top + bground.getGlobalBounds().height)
                                                                    {
                                                                        isGrounded = false;
                                                                        velocityY = -velocityY;
                                                                    }

                                                                }


                                                                //balllong
                                                                if (playerbounds.intersects(balllong.getGlobalBounds())
                                                                {
                                                                    if (playerbounds.left < balllong.getGlobalBounds().left)
                                                                    {
                                                                        velocityX = 0;
                                                                        player1.sprite.setPosition(player1.sprite.getPosition().y && player1.sprite.getPosition().x - 5);
                                                                    }
                                                                    else if (playerbounds.left + playerbounds.width > balllong.getGlobalBounds().left + balllong.getGlobalBounds().width)
                                                                    {
                                                                        player1.direction.x = -abs(player1.direction.x);
                                                                    }

                                                                    else  if (playerbounds.top < balllong.getGlobalBounds().top)
                                                                    {
                                                                        velocityY = 0;
                                                                        isGrounded = true;
                                                                    }
                                                                    else if (playerbounds.top + playerbounds.height < balllong.getGlobalBounds().top + balllong.getGlobalBounds().height)
                                                                    {
                                                                        isGrounded = false;
                                                                        velocityY = -velocityY;
                                                                    }

                                                                }

                                                                //bfore
                                                                if (playerbounds.intersects(bfore.getGlobalBounds())
                                                                {
                                                                    if (playerbounds.left < bfore.getGlobalBounds().left)
                                                                    {
                                                                        velocityX = 0;
                                                                        player1.sprite.setPosition(player1.sprite.getPosition().y && player1.sprite.getPosition().x - 5);
                                                                    }
                                                                    else if (playerbounds.left + playerbounds.width > bfore.getGlobalBounds().left + bfore.getGlobalBounds().width)
                                                                    {
                                                                        player1.direction.x = -abs(player1.direction.x);
                                                                    }

                                                                    else  if (playerbounds.top < bfore.getGlobalBounds().top)
                                                                    {
                                                                        velocityY = 0;
                                                                        isGrounded = true;
                                                                    }
                                                                    else if (playerbounds.top + playerbounds.height < bfore.getGlobalBounds().top + bfore.getGlobalBounds().height)
                                                                    {
                                                                        isGrounded = false;
                                                                        velocityY = -velocityY;
                                                                    }

                                                                }

                                                                //bblock1

                                                                if (playerbounds.intersects(bblock1.getGlobalBounds())
                                                                {
                                                                    if (playerbounds.left < bblock1.getGlobalBounds().left)
                                                                    {
                                                                        velocityX = 0;
                                                                        player1.sprite.setPosition(player1.sprite.getPosition().y && player1.sprite.getPosition().x - 5);
                                                                    }
                                                                    else if (playerbounds.left + playerbounds.width > bblock1.getGlobalBounds().left + bblock1.getGlobalBounds().width)
                                                                    {
                                                                        player1.direction.x = -abs(player1.direction.x);
                                                                    }

                                                                    else  if (playerbounds.top < bblock1.getGlobalBounds().top)
                                                                    {
                                                                        velocityY = 0;
                                                                        isGrounded = true;
                                                                    }
                                                                    else if (playerbounds.top + playerbounds.height < bblock1.getGlobalBounds().top + bblock1.getGlobalBounds().height)
                                                                    {
                                                                        isGrounded = false;
                                                                        velocityY = -velocityY;
                                                                    }

                                                                }

                                                                //bblock2
                                                                if (playerbounds.intersects(bblock2.getGlobalBounds())
                                                                {
                                                                    if (playerbounds.left < bblock2.getGlobalBounds().left)
                                                                    {
                                                                        velocityX = 0;
                                                                        player1.sprite.setPosition(player1.sprite.getPosition().y && player1.sprite.getPosition().x - 5);
                                                                    }
                                                                    else if (playerbounds.left + playerbounds.width > bblock2.getGlobalBounds().left + bblock2.getGlobalBounds().width)
                                                                    {
                                                                        player1.direction.x = -abs(player1.direction.x);
                                                                    }

                                                                    else  if (playerbounds.top < bblock2.getGlobalBounds().top)
                                                                    {
                                                                        velocityY = 0;
                                                                        isGrounded = true;
                                                                    }
                                                                    else if (playerbounds.top + playerbounds.height < bblock2.getGlobalBounds().top + bblock2.getGlobalBounds().height)
                                                                    {
                                                                        isGrounded = false;
                                                                        velocityY = -velocityY;
                                                                    }

                                                                }

                                                                //bblock3

                                                                if (playerbounds.intersects(bblock3.getGlobalBounds())
                                                                {
                                                                    if (playerbounds.left < bblock3.getGlobalBounds().left)
                                                                    {
                                                                        velocityX = 0;
                                                                        player1.sprite.setPosition(player1.sprite.getPosition().y && player1.sprite.getPosition().x - 5);
                                                                    }
                                                                    else if (playerbounds.left + playerbounds.width > bblock3.getGlobalBounds().left + bblock3.getGlobalBounds().width)
                                                                    {
                                                                        player1.direction.x = -abs(player1.direction.x);
                                                                    }

                                                                    else  if (playerbounds.top < bblock3.getGlobalBounds().top)
                                                                    {
                                                                        velocityY = 0;
                                                                        isGrounded = true;
                                                                    }
                                                                    else if (playerbounds.top + playerbounds.height < bblock3.getGlobalBounds().top + bblock3.getGlobalBounds().height)
                                                                    {
                                                                        isGrounded = false;
                                                                        velocityY = -velocityY;
                                                                    }

                                                                }

                                                                //bblock4

                                                                if (playerbounds.intersects(bblock4.getGlobalBounds())
                                                                {
                                                                    if (playerbounds.left < bblock4.getGlobalBounds().left)
                                                                    {
                                                                        velocityX = 0;
                                                                        player1.sprite.setPosition(player1.sprite.getPosition().y && player1.sprite.getPosition().x - 5);
                                                                    }
                                                                    else if (playerbounds.left + playerbounds.width > bblock4.getGlobalBounds().left + bblock4.getGlobalBounds().width)
                                                                    {
                                                                        player1.direction.x = -abs(player1.direction.x);
                                                                    }

                                                                    else  if (playerbounds.top < bblock4.getGlobalBounds().top)
                                                                    {
                                                                        velocityY = 0;
                                                                        isGrounded = true;
                                                                    }
                                                                    else if (playerbounds.top + playerbounds.height < bblock4.getGlobalBounds().top + bblock4.getGlobalBounds().height)
                                                                    {
                                                                        isGrounded = false;
                                                                        velocityY = -velocityY;
                                                                    }

                                                                }

                                                                //bblock5

                                                                if (playerbounds.intersects(bblock5.getGlobalBounds())
                                                                {
                                                                    if (playerbounds.left < bblock5.getGlobalBounds().left)
                                                                    {
                                                                        velocityX = 0;
                                                                        player1.sprite.setPosition(player1.sprite.getPosition().y && player1.sprite.getPosition().x - 5);
                                                                    }
                                                                    else if (playerbounds.left + playerbounds.width > bblock5.getGlobalBounds().left + bblock5.getGlobalBounds().width)
                                                                    {
                                                                        player1.direction.x = -abs(player1.direction.x);
                                                                    }

                                                                    else  if (playerbounds.top < bblock5.getGlobalBounds().top)
                                                                    {
                                                                        velocityY = 0;
                                                                        isGrounded = true;
                                                                    }
                                                                    else if (playerbounds.top + playerbounds.height < bblock5.getGlobalBounds().top + bblock5.getGlobalBounds().height)
                                                                    {
                                                                        isGrounded = false;
                                                                        velocityY = -velocityY;
                                                                    }

                                                                }



                                                                //factory map
                                                                //factorybackg
                                                                if (playerbounds.intersects(factorybackg.getGlobalBounds())
                                                                {
                                                                    if (playerbounds.left < factorybackg.getGlobalBounds().left)
                                                                    {
                                                                        velocityX = 0;
                                                                        player1.sprite.setPosition(player1.sprite.getPosition().y && player1.sprite.getPosition().x - 5);
                                                                    }
                                                                    else if (playerbounds.left + playerbounds.width > factorybackg.getGlobalBounds().left + factorybackg.getGlobalBounds().width)
                                                                    {
                                                                        player1.direction.x = -abs(player1.direction.x);
                                                                    }

                                                                    else  if (playerbounds.top < factorybackg.getGlobalBounds().top)
                                                                    {
                                                                        velocityY = 0;
                                                                        isGrounded = true;
                                                                    }
                                                                    else if (playerbounds.top + playerbounds.height < factorybackg.getGlobalBounds().top + factorybackg.getGlobalBounds().height)
                                                                    {
                                                                        isGrounded = false;
                                                                        velocityY = -velocityY;
                                                                    }

                                                                }

                                                                //factoryforeg
                                                                if (playerbounds.intersects(factoryforeg.getGlobalBounds())
                                                                {
                                                                    if (playerbounds.left < factoryforeg.getGlobalBounds().left)
                                                                    {
                                                                        velocityX = 0;
                                                                        player1.sprite.setPosition(player1.sprite.getPosition().y && player1.sprite.getPosition().x - 5);
                                                                    }
                                                                    else if (playerbounds.left + playerbounds.width > factoryforeg.getGlobalBounds().left + factoryforeg.getGlobalBounds().width)
                                                                    {
                                                                        player1.direction.x = -abs(player1.direction.x);
                                                                    }

                                                                    else  if (playerbounds.top < factoryforeg.getGlobalBounds().top)
                                                                    {
                                                                        velocityY = 0;
                                                                        isGrounded = true;
                                                                    }
                                                                    else if (playerbounds.top + playerbounds.height < factoryforeg.getGlobalBounds().top + factoryforeg.getGlobalBounds().height)
                                                                    {
                                                                        isGrounded = false;
                                                                        velocityY = -velocityY;
                                                                    }

                                                                }

                                                                //fblock1
                                                                if (playerbounds.intersects(fblock1.getGlobalBounds())
                                                                {
                                                                    if (playerbounds.left < fblock1.getGlobalBounds().left)
                                                                    {
                                                                        velocityX = 0;
                                                                        player1.sprite.setPosition(player1.sprite.getPosition().y && player1.sprite.getPosition().x - 5);
                                                                    }
                                                                    else if (playerbounds.left + playerbounds.width > fblock1.getGlobalBounds().left + fblock1.getGlobalBounds().width)
                                                                    {
                                                                        player1.direction.x = -abs(player1.direction.x);
                                                                    }

                                                                    else  if (playerbounds.top < factorybackg.getGlobalBounds().top)
                                                                    {
                                                                        velocityY = 0;
                                                                        isGrounded = true;
                                                                    }
                                                                    else if (playerbounds.top + playerbounds.height < fblock1.getGlobalBounds().top + fblock1.getGlobalBounds().height)
                                                                    {
                                                                        isGrounded = false;
                                                                        velocityY = -velocityY;
                                                                    }

                                                                }
                                                                //fblock2
                                                                if (playerbounds.intersects(fblock2.getGlobalBounds())
                                                                {
                                                                    if (playerbounds.left < fblock2.getGlobalBounds().left)
                                                                    {
                                                                        velocityX = 0;
                                                                        player1.sprite.setPosition(player1.sprite.getPosition().y && player1.sprite.getPosition().x - 5);
                                                                    }
                                                                    else if (playerbounds.left + playerbounds.width > fblock2.getGlobalBounds().left + fblock2.getGlobalBounds().width)
                                                                    {
                                                                        player1.direction.x = -abs(player1.direction.x);
                                                                    }

                                                                    else  if (playerbounds.top < fblock2.getGlobalBounds().top)
                                                                    {
                                                                        velocityY = 0;
                                                                        isGrounded = true;
                                                                    }
                                                                    else if (playerbounds.top + playerbounds.height < fblock2.getGlobalBounds().top + fblock2.getGlobalBounds().height)
                                                                    {
                                                                        isGrounded = false;
                                                                        velocityY = -velocityY;
                                                                    }

                                                                }//fblock3
                                                                if (playerbounds.intersects(fblock3.getGlobalBounds())
                                                                {
                                                                    if (playerbounds.left < fblock3.getGlobalBounds().left)
                                                                    {
                                                                        velocityX = 0;
                                                                        player1.sprite.setPosition(player1.sprite.getPosition().y && player1.sprite.getPosition().x - 5);
                                                                    }
                                                                    else if (playerbounds.left + playerbounds.width > fblock3.getGlobalBounds().left + fblock3.getGlobalBounds().width)
                                                                    {
                                                                        player1.direction.x = -abs(player1.direction.x);
                                                                    }

                                                                    else  if (playerbounds.top < fblock3.getGlobalBounds().top)
                                                                    {
                                                                        velocityY = 0;
                                                                        isGrounded = true;
                                                                    }
                                                                    else if (playerbounds.top + playerbounds.height < fblock3.getGlobalBounds().top + fblock3.getGlobalBounds().height)
                                                                    {
                                                                        isGrounded = false;
                                                                        velocityY = -velocityY;
                                                                    }

                                                                }
                                                                //castle map

                                                                   //castleb
                                                                if (playerbounds.intersects(castleb.getGlobalBounds())
                                                                {
                                                                    if (playerbounds.left < castleb.getGlobalBounds().left)
                                                                    {
                                                                        velocityX = 0;
                                                                        player1.sprite.setPosition(player1.sprite.getPosition().y && player1.sprite.getPosition().x - 5);
                                                                    }
                                                                    else if (playerbounds.left + playerbounds.width > castleb.getGlobalBounds().left + castleb.getGlobalBounds().width)
                                                                    {
                                                                        player1.direction.x = -abs(player1.direction.x);
                                                                    }

                                                                    else  if (playerbounds.top < castleb.getGlobalBounds().top)
                                                                    {
                                                                        velocityY = 0;
                                                                        isGrounded = true;
                                                                    }
                                                                    else if (playerbounds.top + playerbounds.height < castleb.getGlobalBounds().top + castleb.getGlobalBounds().height)
                                                                    {
                                                                        isGrounded = false;
                                                                        velocityY = -velocityY;
                                                                    }

                                                                } //blockl

                                                                if (playerbounds.intersects(blockl.getGlobalBounds())
                                                                {
                                                                    if (playerbounds.left < blockl.getGlobalBounds().left)
                                                                    {
                                                                        velocityX = 0;
                                                                        player1.sprite.setPosition(player1.sprite.getPosition().y && player1.sprite.getPosition().x - 5);
                                                                    }
                                                                    else if (playerbounds.left + playerbounds.width > blockl.getGlobalBounds().left + blockl.getGlobalBounds().width)
                                                                    {
                                                                        player1.direction.x = -abs(player1.direction.x);
                                                                    }

                                                                    else  if (playerbounds.top < blockl.getGlobalBounds().top)
                                                                    {
                                                                        velocityY = 0;
                                                                        isGrounded = true;
                                                                    }
                                                                    else if (playerbounds.top + playerbounds.height < blockl.getGlobalBounds().top + blockl.getGlobalBounds().height)
                                                                    {
                                                                        isGrounded = false;
                                                                        velocityY = -velocityY;
                                                                    }

                                                                }
                                                                //blockr

                                                                if (playerbounds.intersects(blockr.getGlobalBounds())
                                                                {
                                                                    if (playerbounds.left < blockr.getGlobalBounds().left)
                                                                    {
                                                                        velocityX = 0;
                                                                        player1.sprite.setPosition(player1.sprite.getPosition().y && player1.sprite.getPosition().x - 5);
                                                                    }
                                                                    else if (playerbounds.left + playerbounds.width > blockr.getGlobalBounds().left + blockr.getGlobalBounds().width)
                                                                    {
                                                                        player1.direction.x = -abs(player1.direction.x);
                                                                    }

                                                                    else  if (playerbounds.top < blockr.getGlobalBounds().top)
                                                                    {
                                                                        velocityY = 0;
                                                                        isGrounded = true;
                                                                    }
                                                                    else if (playerbounds.top + playerbounds.height < blockr.getGlobalBounds().top + blockr.getGlobalBounds().height)
                                                                    {
                                                                        isGrounded = false;
                                                                        velocityY = -velocityY;
                                                                    }

                                                                }

                                                                //castlef
                                                                if (playerbounds.intersects(castlef.getGlobalBounds())
                                                                {
                                                                    if (playerbounds.left < castlef.getGlobalBounds().left)
                                                                    {
                                                                        velocityX = 0;
                                                                        player1.sprite.setPosition(player1.sprite.getPosition().y && player1.sprite.getPosition().x - 5);
                                                                    }
                                                                    else if (playerbounds.left + playerbounds.width > castlef.getGlobalBounds().left + castlef.getGlobalBounds().width)
                                                                    {
                                                                        player1.direction.x = -abs(player1.direction.x);
                                                                    }

                                                                    else  if (playerbounds.top < castlef.getGlobalBounds().top)
                                                                    {
                                                                        velocityY = 0;
                                                                        isGrounded = true;
                                                                    }
                                                                    else if (playerbounds.top + playerbounds.height < castlef.getGlobalBounds().top + castlef.getGlobalBounds().height)
                                                                    {
                                                                        isGrounded = false;
                                                                        velocityY = -velocityY;
                                                                    }

                                                                }
                                                                window.clear(Color(150, 150, 150));

                                                                // draw everything here...
                                                                  //1
                                                              /*castle map
                                                                window.draw(castleb);
                                                                window.draw(blockl);
                                                                window.draw(blockr);
                                                                window.draw(castlef);
                                                              */

                                                              //2
                                                              //desert map
                                                                window.draw(dground);
                                                                window.draw(dfore);
                                                                window.draw(block1);
                                                                window.draw(block2);
                                                                window.draw(block3);
                                                                window.draw(block4);
                                                                window.draw(block5);
                                                                window.draw(block6);
                                                                window.draw(block7);
                                                                window.draw(block8);
                                                                window.draw(block9);
                                                                window.draw(block10);
                                                                window.draw(block11);


                                                                //3
                                                                /*ball map
                                                                   window.draw(bground);
                                                                   window.draw(balllong);
                                                                   window.draw(bblock1);
                                                                   window.draw(bblock2);
                                                                   window.draw(bblock3);
                                                                   window.draw(bblock4);
                                                                   window.draw(bblock5);
                                                                   window.draw(bfore);
                                                                  */

                                                                  //4
                                                                  /*wood map
                                                                    window.draw(ground);
                                                                    window.draw(fore);
                                                                    window.draw(fore);
                                                                    window.draw(woodlong);
                                                                    window.draw(wblock1);
                                                                    window.draw(wblock2);
                                                                    window.draw(wblock3);
                                                                    window.draw(wblock4);
                                                                    window.draw(wblock5);
                                                                    window.draw(wblock6);
                                                                    window.draw(wblock7);
                                                                    window.draw(wblock8);
                                                                    window.draw(wblock9);
                                                                  */
                                                                  //window.draw(fore);
                                                               //5
                                                               /*factory
                                                                   window.draw(factorybackg);
                                                                   window.draw(factoryforeg);
                                                                   window.draw(fblock1);
                                                                   window.draw(fblock2);
                                                                   window.draw(fblock3);
                                                                */

                                                                window.draw(player1.sprite);
                                                                window.draw(player2.sprite);
                                                                text.setString("HP: " + std::to_string(player2.health));
                                                                window.draw(text);

                                                                if (gun.timeOfResponing <= timer.getElapsedTime().asSeconds())
                                                                {
                                                                    gun.isRender = true;
                                                                    gun.render(winWidth);
                                                                    timer.restart();
                                                                }
                                                                else if (gun.isRender)
                                                                {
                                                                    window.draw(gun.sprite);
                                                                    gun.sprite.move(0, gun.velocityY);
                                                                }
                                                                //rendering
                                                                window.clear();




                                                                player1.sprite.move(player1.velocityX, player1.velocityY);
                                                                player2.sprite.move(player2.velocityX, player2.velocityY);
                                                                window.display();
                                                            }
                                                        }
