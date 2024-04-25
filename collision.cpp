#include <SFML/Graphics.hpp>
#include <iostream>
using namespace std;
using namespace sf;

FloatRect playerbounds = player1.sprite.getGlobalBounds();
FloatRect blockbounds = block.getGlobalBounds();

void handlecollision(playerbounds, blockbounds) {
	if (playerbounds.intersect(blockbounds))
	{
		if (playerbounds.left < blockbounds.left)
		{
			velocityX = 0;
			player1.moveRight(10, 0);
		}
		else if (playerbounds.left + playerbounds.width < blockbounds.left + blockbounds.width)
		{
			velocityX = 0;
		}
		else if (playerbounds.top < blockbounds.top)
		{
			velocityY = 0;

		}
		else if (playerbounds.top + playerbounds.hight < blockbounds.top + blockbounds.hight)
		{
			velocityY = -50;

		}
	}



}
