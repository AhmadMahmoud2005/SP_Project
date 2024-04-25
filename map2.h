#pragma once



//WOOD MAP
//BLOCK 1
if (playerbounds.intersects(wblock1.getGlobalBounds()))
{
    if (playerbounds.left < wblock1.getGlobalBounds().left)
    {
        velocityX = 0;
        player1.moveRight(10);
    }
    else if (playerbounds.left + playerbounds.width > wblock1.getGlobalBounds().left + wblock1.getGlobalBounds().width)
    {
        velocityX = 0;
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

if (playerbounds.intersects(wblock1.getGlobalBounds()))
{
    if (playerbounds.left < wblock2.getGlobalBounds().left)
    {
        velocityX = 0;
        player1.moveRight(10);
    }
    else if (playerbounds.left + playerbounds.width > wblock2.getGlobalBounds().left + wblock2.getGlobalBounds().width)
    {
        velocityX = 0;
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
if (playerbounds.intersects(wblock3.getGlobalBounds()))
{
    if (playerbounds.left < wblock3.getGlobalBounds().left)
    {
        velocityX = 0;
        player1.moveRight(10);
    }

    else if (playerbounds.left + playerbounds.width > wblock3.getGlobalBounds().left + wblock3.getGlobalBounds().width)
    {
        velocityX = 0;
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


if (playerbounds.intersects(wblock4.getGlobalBounds()))
{
    if (playerbounds.left < wblock4.getGlobalBounds().left)
    {
        velocityX = 0;
        player1.moveRight(10);
    }
    else if (playerbounds.left + playerbounds.width > wblock4.getGlobalBounds().left + wblock4.getGlobalBounds().width)
    {
        velocityX = 0;
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

if (playerbounds.intersects(wblock5.getGlobalBounds()))
{
    if (playerbounds.left < wblock5.getGlobalBounds().left)
    {
        velocityX = 0;
        player1.moveRight(10);
    }
    else if (playerbounds.left + playerbounds.width > wblock5.getGlobalBounds().left + wblock5.getGlobalBounds().width)
    {
        velocityX = 0;
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


if (playerbounds.intersects(wblock6.getGlobalBounds())) {
    if (playerbounds.left < wblock6.getGlobalBounds().left)
    {
        velocityX = 0;
        player1.moveRight(10);
    }
    else if (playerbounds.left + playerbounds.width > wblock6.getGlobalBounds().left + wblock6.getGlobalBounds().width)
    {
        velocityX = 0;
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




if (playerbounds.intersects(wblock7.getGlobalBounds()))

{
    if (playerbounds.left < wblock7.getGlobalBounds().left)
    {
        velocityX = 0;
        player1.moveRight(10);
    }
    else if (playerbounds.left + playerbounds.width > wblock7.getGlobalBounds().left + wblock7.getGlobalBounds().width)
    {
        velocityX = 0;
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


if (playerbounds.intersects(wblock8.getGlobalBounds()))
{
    if (playerbounds.left < wblock8.getGlobalBounds().left)
    {
        velocityX = 0;
        player1.moveRight(10);
    }
    else if (playerbounds.left + playerbounds.width > wblock8.getGlobalBounds().left + wblock8.getGlobalBounds().width)
    {
        velocityX = 0;
    }

    else  if (playerbounds.top < wblock8.getGlobalBounds().top)
    {
        velocityY = 0;
        isGrounded = true;
    }
    else if (playerbounds.top + playerbounds.height > wblock8.getGlobalBounds().top + wblock8.getGlobalBounds().height)
    {
        isGrounded = false;
        velocityY = -velocityY;
    }

}
//block 9

if (playerbounds.intersects(wblock9.getGlobalBounds()))
{
    if (playerbounds.left < wblock9.getGlobalBounds().left)
    {
        velocityX = 0;
        player1.moveRight(10);
    }
    else if (playerbounds.left + playerbounds.width > wblock9.getGlobalBounds().left + wblock9.getGlobalBounds().width)
    {
        velocityX = 0;
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

if (playerbounds.intersects(ground.getGlobalBounds()))
{
    if (playerbounds.left < ground.getGlobalBounds().left)
    {
        velocityX = 0;
        player1.moveRight(10);
    }
    else if (playerbounds.left + playerbounds.width > ground.getGlobalBounds().left + ground.getGlobalBounds().width)
    {
        velocityX = 0;
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


if (playerbounds.intersects(woodlong.getGlobalBounds()))
{
    if (playerbounds.left < woodlong.getGlobalBounds().left)
    {
        velocityX = 0;
        player1.moveRight(10);
    }
    else if (playerbounds.left + playerbounds.width > woodlong.getGlobalBounds().left + woodlong.getGlobalBounds().width)
    {
        velocityX = 0;
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

if (playerbounds.intersects(fore.getGlobalBounds()))
{
    if (playerbounds.left < fore.getGlobalBounds().left)
    {
        velocityX = 0;
        player1.moveRight(10);
    }
    else if (playerbounds.left + playerbounds.width > fore.getGlobalBounds().left + fore.getGlobalBounds().width)
    {
        velocityX = 0;
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


if (playerbounds.intersects(fore.getGlobalBounds()))
{
    if (playerbounds.left < fore.getGlobalBounds().left)
    {
        velocityX = 0;
        player1.moveRight(10);
    }
    else if (playerbounds.left + playerbounds.width > fore.getGlobalBounds().left + fore.getGlobalBounds().width)
    {
        velocityX = 0;
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

