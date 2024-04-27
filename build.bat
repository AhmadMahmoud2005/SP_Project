g++ -c ConsoleApplication1.cpp menu.cpp
g++ ConsoleApplication1.o menu.cpp -o sfml-app -lsfml-graphics -lsfml-window -lsfml-system
./sfml-app