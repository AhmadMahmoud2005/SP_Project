#pragma once



//ball map
                       //bground
if (playerbounds.intersects(bground.getGlobalBounds()))
{
    if (playerbounds.left < bground.getGlobalBounds().left)
    {
        velocityX = 0;
        player1.moveRight(10);
    }
    else if (playerbounds.left + playerbounds.width > bground.getGlobalBounds().left + bground.getGlobalBounds().width)
    {
        velocityX = 0;
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
if (playerbounds.intersects(balllong.getGlobalBounds()))
{
    if (playerbounds.left < balllong.getGlobalBounds().left)
    {
        velocityX = 0;
        player1.moveRight(10);
    }
    else if (playerbounds.left + playerbounds.width > balllong.getGlobalBounds().left + balllong.getGlobalBounds().width)
    {
        velocityX = 0;
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
if (playerbounds.intersects(bfore.getGlobalBounds())) {
    if (playerbounds.left < bfore.getGlobalBounds().left)
    {
        velocityX = 0;
        player1.moveRight(10);
    }
    else if (playerbounds.left + playerbounds.width > bfore.getGlobalBounds().left + bfore.getGlobalBounds().width)
    {
        velocityX = 0;
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

if (playerbounds.intersects(bblock1.getGlobalBounds()))
{
    if (playerbounds.left < bblock1.getGlobalBounds().left)
    {
        velocityX = 0;
        player1.moveRight(10);
    }
    else if (playerbounds.left + playerbounds.width > bblock1.getGlobalBounds().left + bblock1.getGlobalBounds().width)
    {
        velocityX = 0;
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
if (playerbounds.intersects(bblock2.getGlobalBounds())) {
    if (playerbounds.left < bblock2.getGlobalBounds().left)
    {
        velocityX = 0;
        player1.moveRight(10);
    }
    else if (playerbounds.left + playerbounds.width > bblock2.getGlobalBounds().left + bblock2.getGlobalBounds().width)
    {
        velocityX = 0;
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

if (playerbounds.intersects(bblock3.getGlobalBounds()))
{
    if (playerbounds.left < bblock3.getGlobalBounds().left)
    {
        velocityX = 0;
        player1.moveRight(10);
    }
    else if (playerbounds.left + playerbounds.width > bblock3.getGlobalBounds().left + bblock3.getGlobalBounds().width)
    {
        velocityX = 0;
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

if (playerbounds.intersects(bblock4.getGlobalBounds()))
{
    if (playerbounds.left < bblock4.getGlobalBounds().left)
    {
        velocityX = 0;
        player1.moveRight(10);
    }
    else if (playerbounds.left + playerbounds.width > bblock4.getGlobalBounds().left + bblock4.getGlobalBounds().width)
    {
        velocityX = 0;
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