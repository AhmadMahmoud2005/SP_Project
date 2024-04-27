#include<SFML/Graphics.hpp>
#include<SFML/Audio.hpp>
#include<iostream>
using namespace std;
using namespace sf;
//rectangle function
RectangleShape createRectangle(int length, int width, int xposition, int yposition) {
    RectangleShape rectangle(Vector2f(length, width));
    rectangle.setPosition(xposition, yposition);
    rectangle.setFillColor(Color::Black);
    return rectangle;
};
//sprite function
Sprite createSprite(Texture& texture, float scalex, float scaley) {
    Sprite sprite(texture);
    sprite.setScale(scalex, scaley);
    return sprite;
};
int level_1(RenderWindow& window, int &level) {
    //map  (1)
        //castle map1
    Texture castleback;
    castleback.loadFromFile("castleb.png");
    Sprite castleb = createSprite(castleback, 1.6, 2);
    Texture castlefore;
    castlefore.loadFromFile("castlefore.png");
    Sprite castlef;
    castlef.setTexture(castlefore);

    //castle ground left
    RectangleShape blockl = createRectangle(700, 240, 0, 860);
    //castle ground right
    RectangleShape blockr = createRectangle(750, 250, 1170, 870);

    //level 1 rendring
    window.clear();
    window.draw(castleb);
    window.draw(blockl);
    window.draw(blockr);
    window.draw(castlef);
    window.display();
    level = 1;
    return level;
};
int level_2(RenderWindow& window, int& level) {
    //map (2)
       //wood 
    Texture wbackground;
    wbackground.loadFromFile("wood.png");
    Sprite wback = createSprite(wbackground, 1.67, 1.7);
    Texture wforeground;
    wforeground.loadFromFile("woods.png");
    Sprite wfore = createSprite(wforeground, 0.84, 0.8);
    //wood ground
    RectangleShape wground = createRectangle(1739, 100, 98, 911);
    //wood middle level 1
    RectangleShape wblock1 = createRectangle(417, 250, 757, 735);
    //wood float 1 left
    RectangleShape wblock2 = createRectangle(200, 50, 53, 656);
    //wood float 1 right
    RectangleShape wblock3 = createRectangle(200, 50, 1680, 650);
    //wood float 2 left
    RectangleShape wblock4 = createRectangle(200, 40, 405, 530);
    //wood float 2 right
    RectangleShape wblock5 = createRectangle(203, 40, 1330, 530);
    //wood float 3 left
    RectangleShape wblock6 = createRectangle(152, 50, 759, 493);
    //wood float 3 right
    RectangleShape wblock7 = createRectangle(152, 50, 1022, 493);
    //wood ground left
    RectangleShape wblock8 = createRectangle(65, 100, 350, 818);
    //wood ground right
    RectangleShape wblock9 = createRectangle(65, 100, 1518, 818);
    
    //level 2 rendreing
    window.clear();
    window.draw(wback);
    window.draw(wfore);
    window.display();
    level = 2;
    return level;
};
int level_3(RenderWindow& window, int& level) {
    //map  (3)
    //desert 
    Texture dback;
    dback.loadFromFile("desertb.png");
    Sprite dground = createSprite(dback, 1.5, 1.6);
    Texture desertfore;
    desertfore.loadFromFile("desertf.png");
    Sprite dfore = createSprite(desertfore, 1.5, 1.55);
    dfore.setPosition(Vector2f(0, 0));
    //desert blocks
    //desert left float
    RectangleShape dblock1 = createRectangle(440, 100, 425, 577);
    //desert right float
    RectangleShape dblock2 = createRectangle(400, 100, 1130, 590);
    //desert floor
    RectangleShape dblock3 = createRectangle(95, 395, 910, 0);
    //desert tall ground
    RectangleShape dblock4 = createRectangle(1550, 80, 185, 980);
    //desert level 1 mid
    RectangleShape dblock5 = createRectangle(400, 80, 760, 900);
    //desert level 1 left
    RectangleShape dblock6 = createRectangle(235, 80, 195, 900);
    //desert level 1 right
    RectangleShape dblock7 = createRectangle(235, 80, 1490, 900);
    //desert level 2 left
    RectangleShape dblock8 = createRectangle(160, 80, 195, 820);
    //desert level 2 right
    RectangleShape dblock9 = createRectangle(160, 80, 1570, 820);
    //desert level 2 mid
    RectangleShape dblock10 = createRectangle(235, 80, 845, 820);
    //desert level 3 mid
    RectangleShape dblock11 = createRectangle(80, 80, 925, 740);
    window.clear();
    window.draw(dground);
    window.draw(dfore);
    window.display();
    level = 3;
    return level;
}
int level_4(RenderWindow& window, int& level) {
    //map (4)
       //ball 
    Texture bback;
    bback.loadFromFile("ballback.png");
    Sprite bground = createSprite(bback, 1.5, 1.5);
    Texture ball;
    ball.loadFromFile("ballfore.png");
    Sprite bfore = createSprite(ball, 1.5, 1);
    bfore.setPosition(Vector2f(0, 330));
    //ballground
    RectangleShape balllong = createRectangle(2000, 150, 0, 1020);
    //ball block1
    RectangleShape bblock1 = createRectangle(420, 150, 1500, 890);
    //ball block2
    RectangleShape bblock2 = createRectangle(280, 150, 470, 890);
    //ball block3
    RectangleShape bblock3 = createRectangle(300, 150, 810, 890);
    //ball block4
    RectangleShape bblock4 = createRectangle(275, 150, 1170, 890);
    //ball block5
    RectangleShape bblock5 = createRectangle(420, 150, 0, 890);

    window.clear();
    window.draw(bground);
    window.draw(bblock1);
    window.draw(bblock2);
    window.draw(bblock3);
    window.draw(bblock4);
    window.draw(bblock5);
    window.draw(balllong);
    window.draw(bfore);
        window.display();
        level = 4;
    return level;
};
int main(){
     //opening a window
    RenderWindow window(VideoMode(1900, 1100)," sfml tutorial");
    window.setFramerateLimit(60);
    window.setKeyRepeatEnabled(false);
    Event event;
    //events variables
    bool leftmouseclick= 0;
    int rectxposition=0;
    int rectyposition = 0;
    int levelnum;
    int level = level_2(window,levelnum);




    //sprite 
    int x = 0;
    Texture stick;
    stick.loadFromFile("RPG blue.png");
    Sprite ss;
    ss.setTexture(stick);
    ss.setTextureRect(IntRect (x*128,3*128, 128, 128));
    ss.setOrigin(128 / 2, 128 / 2);
    ss.setPosition(Vector2f(300, 820));
    ss.setScale(0.8, 0.8);
//game loop(infinite loop)
    while (window.isOpen()) {
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed)
                window.close();

            if (Keyboard::isKeyPressed(Keyboard::Right) ) {
                ss.move(20, 0);
                ss.setTextureRect(IntRect(x * 128, 4 * 128, 128, 128));
                x++;
                x %= 7;
                ss.setScale(1, 1);

            }
            if (Keyboard::isKeyPressed(Keyboard::Left)) {
                ss.move(-20, 0);
                ss.setTextureRect(IntRect(x * 128, 4 * 128, 128, 128));
                x++;
                x %= 7;
                ss.setScale(-1, 1);
            }
        }
        if (Mouse::isButtonPressed(Mouse::Left))
        {
            Vector2i mousepos=Mouse::getPosition(window);
            cout << mousepos.x << "\t" << mousepos.y << endl;
        }
        window.clear();
        window.draw(ss);
        window.display();
          
        }
    
    return 0;
}
