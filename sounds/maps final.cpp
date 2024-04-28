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
//levels functions
int level_1(RenderWindow& window) {
    //map  (1)
        //castle map1
    Texture castleback;
    castleback.loadFromFile("castleb.png");
    Sprite castleb = createSprite(castleback, 1.6, 2);
    Texture castlefore;
    castlefore.loadFromFile("castlefore.png");
    Sprite castlef;
    castlef.setTexture(castlefore);
    RectangleShape cblocks[2];
    castleblocks(cblocks);
    //level 1 rendring
    window.clear();
    window.draw(castleb);
    for (int i = 0; i < 2; i++) {
        window.draw(cblocks[i]);
    }
    window.draw(castlef);
    window.display();
    int level = 1;
    return level;
};
int level_2(RenderWindow& window) {
    //map (2)
       //wood 
    Texture wbackground;
    wbackground.loadFromFile("wood.png");
    Sprite wback = createSprite(wbackground, 1.67, 1.7);
    Texture wforeground;
    wforeground.loadFromFile("woods.png");
    Sprite wfore = createSprite(wforeground, 0.84, 0.8);
    RectangleShape wblocks[10];
    woodblocks(wblocks);
    //level 2 rendreing
    window.clear();
    window.draw(wback);
    window.draw(wfore);
    window.display();
    int level = 2;
    return level;
};
int level_3(RenderWindow& window) {
    //map  (3)
    //desert 
    Texture dback;
    dback.loadFromFile("desertb.png");
    Sprite dground = createSprite(dback, 1.5, 1.6);
    Texture desertfore;
    desertfore.loadFromFile("desertf.png");
    Sprite dfore = createSprite(desertfore, 1.5, 1.55);
    dfore.setPosition(Vector2f(0, 0));
    RectangleShape dblocks[11];
    woodblocks(dblocks);
    window.clear();
    window.draw(dground);
    window.draw(dfore);
    window.display();
    int level = 3;
    return level;
}
int level_4(RenderWindow& window) {
    //map (4)
       //ball 
    Texture bback;
    bback.loadFromFile("ballback.png");
    Sprite bground = createSprite(bback, 1.5, 1.5);
    Texture ball;
    ball.loadFromFile("ballfore.png");
    Sprite bfore = createSprite(ball, 1.5, 1);
    bfore.setPosition(Vector2f(0, 330));
    RectangleShape bblocks[6];
    ballblocks(bblocks);
    window.clear();
    window.draw(bground);
    for(int i=0;i<6;i++)
    {
        window.draw(bblocks[i]);
    }
   
    window.draw(bfore);
        window.display();
       int level = 4;
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
//game loop(infinite loop)
    while (window.isOpen()) {
        while (window.pollEvent(event)) {

            int level = level_2(window);
            if (event.type == Event::Closed)
                window.close();

        }
        if (Mouse::isButtonPressed(Mouse::Left))
        {
            Vector2i mousepos = Mouse::getPosition(window);
            cout << mousepos.x << "\t" << mousepos.y << endl;


        }
    }
    return 0;
}
