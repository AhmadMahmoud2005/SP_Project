#include<SFML/Graphics.hpp>
#include<SFML/Audio.hpp>
#include<iostream>
using namespace std;
using namespace sf;
int main()

{
    
    //opening a window
    RenderWindow window(VideoMode(1900, 1100)," sfml tutorial");
    window.setFramerateLimit(60);
    window.setKeyRepeatEnabled(false);
    Event event;
    //events variables
    bool leftmouseclick= 0;
    int rectxposition=0;
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
    fblock2.setSize(Vector2f(700,90 ));
    fblock2.setFillColor(Color::Black);
    //factory block3
    RectangleShape fblock3;
    fblock3.setPosition(Vector2f(0, 917));
    fblock3.setSize(Vector2f(700, 90));
    fblock3.setFillColor(Color::Black);
   
    //sprite 
    int x = 0;
    Texture stick;
    stick.loadFromFile("spritesheet.png");
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
       
                //rendering
            window.clear();
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
                window.draw(ss);
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
            window.display();
        }
    
    return 0;
}
