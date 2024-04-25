#pragma once


//factory map
                                              //factorybackg
if (playerbounds.intersects(factorybackg.getGlobalBounds()))
{
    if (playerbounds.left < factorybackg.getGlobalBounds().left)
    {
        velocityX = 0;
        player1.moveRight(10);
    }
    else if (playerbounds.left + playerbounds.width > factorybackg.getGlobalBounds().left + factorybackg.getGlobalBounds().width)
    {
        velocityX = 0;
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
if (playerbounds.intersects(factoryforeg.getGlobalBounds()))
{
    if (playerbounds.left < factoryforeg.getGlobalBounds().left)
    {
        velocityX = 0;
        player1.moveRight(10);
    }
    else if (playerbounds.left + playerbounds.width > factoryforeg.getGlobalBounds().left + factoryforeg.getGlobalBounds().width)
    {
        velocityX = 0;
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
if (playerbounds.intersects(fblock1.getGlobalBounds()))
{
    if (playerbounds.left < fblock1.getGlobalBounds().left)
    {
        velocityX = 0;
        player1.moveRight(10);
    }
    else if (playerbounds.left + playerbounds.width > fblock1.getGlobalBounds().left + fblock1.getGlobalBounds().width)
    {
        velocityX = 0;
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
if (playerbounds.intersects(fblock2.getGlobalBounds())) {
    if (playerbounds.left < fblock2.getGlobalBounds().left)
    {
        velocityX = 0;
        player1.moveRight(10);
    }
    else if (playerbounds.left + playerbounds.width > fblock2.getGlobalBounds().left + fblock2.getGlobalBounds().width)
    {
        velocityX = 0;
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
if (playerbounds.intersects(fblock3.getGlobalBounds()))
{
    if (playerbounds.left < fblock3.getGlobalBounds().left)
    {
        velocityX = 0;
        player1.moveRight(10);
    }
    else if (playerbounds.left + playerbounds.width > fblock3.getGlobalBounds().left + fblock3.getGlobalBounds().width)
    {
        velocityX = 0;
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