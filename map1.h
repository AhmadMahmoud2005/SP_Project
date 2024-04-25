#pragma once





//desert map
FloatRect playerbounds = player1.sprite.getGlobalBounds();
if (playerbounds.intersects(block1.getGlobalBounds()))
{
    if (playerbounds.left < block1.getGlobalBounds().left)
    {
        velocityX = 0;
        player1.moveRight(10);
    }
    else if (playerbounds.left + playerbounds.width > block1.getGlobalBounds().left + block1.getGlobalBounds().width)
    {
        velocityX = 0;
    }

    else  if (playerbounds.top < block1.getGlobalBounds().top)
    {
        velocityY = 0;
        isGrounded = true;
    }
    else if (playerbounds.top + playerbounds.height > block1.getGlobalBounds().height)
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
            player1.moveRight(10);
        }
        else if (playerbounds.left + playerbounds.width > block2.getGlobalBounds().left + block2.getGlobalBounds().width)
        {
            velocityX = 0;


        }

        else  if (playerbounds.top < block2.getGlobalBounds().top)
        {
            velocityY = 0;
            isGrounded = true;
        }
        else if (playerbounds.top + playerbounds.height > block2.getGlobalBounds().top + block2.getGlobalBounds().height)
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
        player1.moveRight(10);
    }
    else if (playerbounds.left + playerbounds.width > block3.getGlobalBounds().left + block3.getGlobalBounds().width)
    {
        velocityX = 0;
    }

    else  if (playerbounds.top < block3.getGlobalBounds().top)
    {
        velocityY = 0;
        isGrounded = true;
    }
    else if (playerbounds.top + playerbounds.height > block3.getGlobalBounds().height) {
        isGrounded = false;
        velocityY = -velocityY;
    }

};

//block4

if (playerbounds.intersects(block4.getGlobalBounds()))
{
    if (playerbounds.left < block4.getGlobalBounds().left)
    {
        velocityX = 0;
        player1.moveRight(10);
    }
    else if (playerbounds.left + playerbounds.width > block2.getGlobalBounds().left + block4.getGlobalBounds().width)
    {
        velocityX = 0;
    }

    else  if (playerbounds.top < block4.getGlobalBounds().top)
    {
        velocityY = 0;
        isGrounded = true;

    }
    else if (playerbounds.top + playerbounds.height < block4.getGlobalBounds().top + block4.getGlobalBounds().height)
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
        player1.moveRight(10);
    }
    else if (playerbounds.left + playerbounds.width > block5.getGlobalBounds().left + block5.getGlobalBounds().width)
    {
        velocityX = 0;
    }

    else  if (playerbounds.top < block5.getGlobalBounds().top)
    {
        velocityY = 0;
        isGrounded = true;
    }
    else if (playerbounds.top + playerbounds.height < block5.getGlobalBounds().top + block5.getGlobalBounds().height)
    {
        isGrounded = false;
        velocityY = -velocityY;
    }
}


/ block6

f(playerbounds.intersects(block6.getGlobalBounds()))

if (playerbounds.left < block6.getGlobalBounds().left)
{
    velocityX = 0;
    player1.moveRight(10);
}
else if (playerbounds.left + playerbounds.width > block6.getGlobalBounds().left + block6.getGlobalBounds().width)
{
    velocityX = 0;
}

else  if (playerbounds.top < block6.getGlobalBounds().top)
{
    velocityY = 0;
    isGrounded = true;
}
else if (playerbounds.top + playerbounds.height < block6.getGlobalBounds().top + block6.getGlobalBounds().height)
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
                   player1.moveRight(10);
               }
               else if (playerbounds.left + playerbounds.width > block2.getGlobalBounds().left + block7.getGlobalBounds().width)
               {
                   velocityX = 0;
               }

               else  if (playerbounds.top < block7.getGlobalBounds().top)
               {
                   velocityY = 0;
                   isGrounded = true;
               }
               else if (playerbounds.top + playerbounds.height < block7.getGlobalBounds().top + block7.getGlobalBounds().height)
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
                   player1.moveRight(10);
               }
               else if (playerbounds.left + playerbounds.width > block8.getGlobalBounds().left + block8.getGlobalBounds().width)
               {
                   velocityX = 0;
               }

               else  if (playerbounds.top < block8.getGlobalBounds().top)
               {
                   velocityY = 0;
                   isGrounded = true;
               }
               else if (playerbounds.top + playerbounds.height < block8.getGlobalBounds().top + block8.getGlobalBounds().height)
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
                   player1.moveRight(10);
               }
               else if (playerbounds.left + playerbounds.width > block9.getGlobalBounds().left + block9.getGlobalBounds().width)
               {
                   velocityX = 0;
               }

               else  if (playerbounds.top < block9.getGlobalBounds().top)
               {
                   velocityY = 0;
                   isGrounded = true;
               }
               else if (playerbounds.top + playerbounds.height < block9.getGlobalBounds().top + block9.getGlobalBounds().height)
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
                   player1.moveRight(10);
               }
               else if (playerbounds.left + playerbounds.width > block10.getGlobalBounds().left + block10.getGlobalBounds().width)
               {
                   velocityX = 0;
               }
               else  if (playerbounds.top < block10.getGlobalBounds().top)
               {
                   velocityY = 0;
                   isGrounded = true;
               }
               else if (playerbounds.top + playerbounds.height > block10.getGlobalBounds().top + block10.getGlobalBounds().height)
               {
                   isGrounded = false;
                   velocityY = -velocityY;
               }
           }




           //block11

           if (playerbounds.intersects(block11.getGlobalBounds()))
           {
               if (playerbounds.left < block11.getGlobalBounds().left)

                   velocityX = 0;
               player1.moveRight(10);
           }
           else if (playerbounds.left + playerbounds.width > block11.getGlobalBounds().left + block11.getGlobalBounds().width)
           {
               velocityX = 0;
           }
           else  if (playerbounds.top < block11.getGlobalBounds().top)
           {
               velocityY = 0;
               isGrounded = true;
           }
           else if (playerbounds.top + playerbounds.height > block11.getGlobalBounds().top + block11.getGlobalBounds().height)
           {
               isGrounded = false;
               velocityY = -velocityY;
           }
                    }


                    //dfore


                    if (playerbounds.intersects(dfore.getGlobalBounds()))
                    {
                        if (playerbounds.left < dfore.getGlobalBounds().left)
                        {
                            velocityX = 0;
                            player1.moveRight(10);
                        }
                        else if (playerbounds.left + playerbounds.width > dfore.getGlobalBounds().left + dfore.getGlobalBounds().width)
                        {
                            velocityX = 0;
                        }

                        else  if (playerbounds.top < dfore.getGlobalBounds().top)
                        {
                            velocityY = 0;
                            isGrounded = true;
                        }
                        else if (playerbounds.top + playerbounds.height > dfore.getGlobalBounds().top + dfore.getGlobalBounds().height) {
                            isGrounded = false;
                            velocityY = -velocityY;
                        }
                    }





                    //dground


                    if (playerbounds.intersects(dground.getGlobalBounds()))
                    {
                        if (playerbounds.left < dground.getGlobalBounds().left)
                        {
                            velocityX = 0;
                            player1.moveRight(10);
                        }
                        else if (playerbounds.left + playerbounds.width > dground.getGlobalBounds().left + dground.getGlobalBounds().width)
                        {
                            velocityX = 0;
                        }
                        else  if (playerbounds.top < block11.getGlobalBounds().top)
                        {
                            velocityY = 0;
                            isGrounded = true;
                        }
                        else if (playerbounds.top + playerbounds.height > dground.getGlobalBounds().top + dground.getGlobalBounds().height)
                        {
                            isGrounded = false;
                            velocityY = -velocityY;
                        }
                    }
