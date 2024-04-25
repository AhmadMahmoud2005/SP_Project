#pragma once

//castle map

   //castleb
if (playerbounds.intersects(castleb.getGlobalBounds()))
{
    if (playerbounds.left < castleb.getGlobalBounds().left)
    {
        velocityX = 0;
        player1.moveRight(10);
    }
    else if (playerbounds.left + playerbounds.width > castleb.getGlobalBounds().left + castleb.getGlobalBounds().width)
    {
        velocityX = 0;
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

if (playerbounds.intersects(blockl.getGlobalBounds()))
{
    if (playerbounds.left < blockl.getGlobalBounds().left)
    {
        velocityX = 0;
        player1.moveRight(10);
    }
    else if (playerbounds.left + playerbounds.width > blockl.getGlobalBounds().left + blockl.getGlobalBounds().width)
    {
        velocityX = 0;

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

if (playerbounds.intersects(blockr.getGlobalBounds()))
{
    if (playerbounds.left < blockr.getGlobalBounds().left)
    {
        velocityX = 0;
        player1.moveRight(10);
    }
    else if (playerbounds.left + playerbounds.width > blockr.getGlobalBounds().left + blockr.getGlobalBounds().width)
    {
        velocityX = 0;

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
if (playerbounds.intersects(castlef.getGlobalBounds()))
{
    if (playerbounds.left < castlef.getGlobalBounds().left)
    {
        velocityX = 0;
        player1.moveRight(10);
    }
    else if (playerbounds.left + playerbounds.width > castlef.getGlobalBounds().left + castlef.getGlobalBounds().width)
    {
        velocityX = 0;

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
