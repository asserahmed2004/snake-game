#include <iostream>
#include <ctime>
#include <conio.h>
#include <Windows.h>
using namespace std;
//---------------properties---------------
struct map
{
    int width, height, fruitx, fruity;
};
struct snake
{
    int headx, heady, tail, tailx[100000], taily[100000];
    char dir;
};
struct player
{
    int bestscore = 0;
    int score = 0;
    bool lose = false;
};
//---------------declare variables-------------------
char command, menu_choose, ch, pause_choose;
int menu_move = 0, pause_move = 0;
bool rr = false;
map map1;
snake snake1;
player player1;

void losing_screen();
void winning_screen();
void pause();
//--------------shifting the tail-------------------
void shift_right(int arr[], int size)
{
    for (int i = size - 2; i >= 0; i--)
    {
        arr[i + 1] = arr[i];
    }
}
//---------------setting up the fruit----------------
void generate_fruit()
{
    srand(time(NULL));
    map1.fruitx = rand() % (map1.width - 2) + 1;  // 1 to 38
    map1.fruity = rand() % (map1.height - 2) + 1; // 1 to 38
}
//------------start up settings--------
void setup()
{
    //-------map start up------
    map1.width = 40;
    map1.height = 20;
    generate_fruit();
    //-------snake start up------
    snake1.headx = map1.width / 2;
    snake1.heady = map1.height / 2;
    snake1.tail = 0;
    //-------player start up------
    player1.score = 0;
    player1.lose = false;
}
//------------------draw the map-------------------
void draw()
{
    system("cls");
    for (int i = 0; i < map1.height; i++)
    {
        for (int j = 0; j < map1.width; j++)
        {
            if (i == 0 || i == map1.height - 1)
            {
                cout << "#"; // draw the horizintal sides
            }
            else if (j == 0 || j == map1.width - 1)
            {
                cout << "#"; // draw the vertical sides
            }
            else if (i == snake1.heady && j == snake1.headx)
            {
                cout << "O"; // draw the snake head
            }
            else if (i == map1.fruity && j == map1.fruitx)
            {
                cout << '*'; // draw the fruit
            }
            else
            {
                bool printed = false;
                for (int z = 0; z < snake1.tail; z++)
                {
                    if (snake1.tailx[z] == j && snake1.taily[z] == i)
                    {
                        cout << 'o';
                        printed = true;
                        break;
                    }
                }
                if (!printed)
                {
                    cout << " "; // draw the inner part of the rectangle
                }
            }
        }
        cout << endl;
    }
    cout << "your score is : " << player1.score << endl;
    cout << "your high score is : " << player1.bestscore << endl;
}
//------------------input--------------------------
void input()
{
    if (_kbhit())
    {
        char c = _getch();
        switch (c)
        {
        case 'w':
        case 'W':
            snake1.dir = 'w';
            break;
        case 's':
        case 'S':
            snake1.dir = 's';
            break;
        case 'd':
        case 'D':
            snake1.dir = 'd';
            break;
        case 'a':
        case 'A':
            snake1.dir = 'a';
            break;
        case 'p':
        case 'P':
            pause();
            break;
        }
    }
}

//------------------move--------------------------

void move()
{
    shift_right(snake1.tailx, 100000);
    shift_right(snake1.taily, 100000);
    snake1.tailx[0] = snake1.headx;
    snake1.taily[0] = snake1.heady;
    switch (snake1.dir)
    {
    case 'w':
    case 'W':
        snake1.heady--;
        break;
    case 's':
    case 'S':
        snake1.heady++;
        break;
    case 'd':
    case 'D':
        snake1.headx++;
        break;
    case 'a':
    case 'A':
        snake1.headx--;
        break;
    }

    /*{
        if (snake1.heady == map1.height) {
            snake1.heady = 1;
        }
        if (snake1.heady == 0) {
            snake1.heady = map1.height;
        }
        if (snake1.headx == map1.width) {
            snake1.headx = 1;
        }
        if (snake1.headx == 0) {
            snake1.headx = map1.width;
        }
    }//snake teleports when he hits the walls of map*/

    if (snake1.headx == map1.fruitx && snake1.heady == map1.fruity)
    {
        generate_fruit();
        player1.score += 1;
        snake1.tail++;
    } // generate fruit after eatting the first one , increase score , make tail taller
}
//-----------------winning-------------------------
void winning()
{
    int win = (map1.height * map1.width) - ((map1.width * 2) + (map1.height * 2)) - 4;
    if (player1.score >= win)
    {
        winning_screen();
    }
}

//-----------------losing-----------------
void losing()
{
    if (snake1.heady >= map1.height - 1 || snake1.heady <= 0 || snake1.headx >= map1.width - 1 || snake1.headx <= 0)
    {
        player1.lose = true;

    } // snake dies when he hits the walls of map
    if (snake1.tail > 0)
    {
        for (int i = 0; i < snake1.tail; i++)
        {
            if (snake1.headx == snake1.tailx[i] && snake1.heady == snake1.taily[i])
            {
                player1.lose = true;
            }
        }
    } // snake dies when he hits his tail
    losing_screen();
}

//-----------------------the game--------------------------
void the_game()
{

    while (!player1.lose)
    {
        draw();
        losing();
        winning();
        input();
        move();
        Sleep(50);
    }
}
//-----------------menu----------------------

void menu()
{
    while (menu_choose != '\r')
    {
        system("CLS");
        cout << "SNAKE GAME\n";
        for (int i = 0; i < 10; i++)
        {
            cout << "-";
        }
        cout << "\n";

        if (menu_move == 0)
        {
            {
                cout << "|-> START |\n";
            }
            {
                cout << "| Help |\n";
            }
            {
                cout << "| EXIT |\n";
            }
        }
        else if (menu_move == 1)
        {
            {
                cout << "| START |\n";
            }
            {
                cout << "|-> Help |\n";
            }
            {
                cout << "| EXIT |\n";
            }
        }
        else if (menu_move == 2)
        {
            {
                cout << "| START |\n";
            }
            {
                cout << "| Help |\n";
            }
            {
                cout << "|-> EXIT |\n";
            }
        }

        for (int i = 0; i < 10; i++)
        {
            cout << "-";
        }

        menu_choose = _getch();
        if (menu_choose == 'w' || menu_choose == 'W')
            menu_move--;
        else if (menu_choose == 's' || menu_choose == 'S')
            menu_move++;

        if (menu_move < 0)
            menu_move = 2;
        else if (menu_move > 2)
            menu_move = 0;
    }
    if (menu_move == 0)
    {
        setup();
        the_game();
    }
    else if (menu_move == 1)
    {
        system("cls");
        cout << "\n    press 'B' yo go back\n\n";
        cout << "                                                   DESCRIPTION\n";
        cout << "                                                   -----------\n";
        cout << "The player controls a long, thin creature, resembling a snake, which roams around on a bordered plane,\npicking up food (or some other item), trying to avoid hitting its own tail or the edges of the playing area.\nEach time the snake eats a piece of food, its tail grows longer, making the game increasingly difficult." << endl;
        cout << "------------------------------------------------------------------------------------------------------\n";
        cout << "                                                   CONTROLS\n";
        cout << "                                                   --------\n";
        cout << "press 'w' to move upwards" << endl;
        cout << "press 's' to move downwards" << endl;
        cout << "press 'd' to move to the right" << endl;
        cout << "press 'a' to move to the left" << endl;
        cout << "                                     ------------------------------------\n";
        menu_choose = _getch();
        if (menu_choose == 'b' || menu_choose == 'B')
        {
            menu();
        }
    }
    else
        exit(0);
}

/*void menu() {
    cout << "------------------" << endl;
    cout << "        SNAKE GAME" << endl;
    cout << "press 'S' to start the game" << endl;
    cout << "press 'H' to show the game help center" << endl;
    cout << "press 'Q' to exit the game" << endl;
    cout << "------------------" << endl;

    {
        char c = _getch();
        system("cls");
        switch (c)
        {
        case 's':
        case 'S': {
            setup();
            the_game();
            break;
        }
        case 'h' :
        case 'H' : {
            cout << "\n    press 'B' yo go back\n\n";
            cout << "                                                   DESCRIPTION\n";
            cout << "                                                   -----------\n";
            cout << "The player controls a long, thin creature, resembling a snake, which roams around on a bordered plane,\npicking up food (or some other item), trying to avoid hitting its own tail or the edges of the playing area.\nEach time the snake eats a piece of food, its tail grows longer, making the game increasingly difficult." << endl;
            cout << "------------------------------------------------------------------------------------------------------\n";
            cout << "                                                   CONTROLS\n";
            cout << "                                                   --------\n";
            cout << "press 'w' to move upwards" << endl;
            cout << "press 's' to move downwards" << endl;
            cout << "press 'd' to move to the right" << endl;
            cout << "press 'a' to move to the left" << endl;
            cout << "                                     ------------------------------------\n";
            char b = _getch();
            if (b == 'b' || b == 'B') {
                system("cls");
                menu();
            }
            break;
        }
        case 'q':
        case 'Q':
            exit(0);
        }
    }

}*/

//-------------------restart-----------------------------

void restart()
{

    while (ch != 'q')
    {
        if (!rr)
        {
            ch = _getch();
        }
        else
        {
            ch = 'r';
            rr = false;
        }
        if (ch == 'r' || ch == 'R')
        {
            player1.lose = false;
            setup();
            the_game();
        }
        else if (ch == 'Q' || ch == 'q')
        {
            exit(0);
        }
    }
}
//------------draw game over screen--------

void losing_screen()
{
    if (player1.lose == true)
    {
        system("cls");
        player1.bestscore = max(player1.bestscore, player1.score);
        cout << "your score is : " << player1.score << endl;
        cout << "your high score is : " << player1.bestscore << endl;
        cout << "----------------------\n";
        cout << "GAME OVER" << endl;
        cout << "press 'R' to restart" << endl;
        cout << "press 'Q' to exit" << endl;
        cout << "----------------------\n";
        restart();
    }
}
//------------draw winning screen--------

void winning_screen()
{
    if (player1.lose == false)
    {
        system("cls");
        player1.bestscore = max(player1.bestscore, player1.score);
        cout << "your score is : " << player1.score << endl;
        cout << "your high score is : " << player1.bestscore << endl;
        cout << "----------------------\n";
        cout << "YOU WON" << endl;
        cout << "press 'R' to restart" << endl;
        cout << "press 'Q' to exit" << endl;
        cout << "----------------------\n";
        restart();
    }
}
//------------pause menu-------------------
void pause()
{
    pause_choose = 'p';
    while (pause_choose != '\r')
    {
        system("cls");
        if (pause_move == 0)
        {
            cout << "SNAKE GAME\n";
            cout << "---------------------------" << endl;
            cout << "-> CONTINUE" << endl;
            cout << " RESTART" << endl;
            cout << " HELP" << endl;
            cout << " EXIT" << endl;
            cout << "---------------------------" << endl;
        }
        else if (pause_move == 1)
        {
            cout << "SNAKE GAME\n";
            cout << "---------------------------" << endl;
            cout << " CONTINUE" << endl;
            cout << "-> RESTART" << endl;
            cout << " HELP" << endl;
            cout << " EXIT" << endl;
            cout << "---------------------------" << endl;
        }
        else if (pause_move == 2)
        {
            cout << "SNAKE GAME\n";
            cout << "---------------------------" << endl;
            cout << " CONTINUE" << endl;
            cout << " RESTART" << endl;
            cout << "-> HELP" << endl;
            cout << " EXIT" << endl;
            cout << "---------------------------" << endl;
        }
        else if (pause_move == 3)
        {
            cout << "SNAKE GAME\n";
            cout << "---------------------------" << endl;
            cout << " CONTINUE" << endl;
            cout << " RESTART" << endl;
            cout << " HELP" << endl;
            cout << "-> EXIT" << endl;
            cout << "---------------------------" << endl;
        }
        pause_choose = _getch();
        if (pause_choose == 'w' || pause_choose == 'W')
            pause_move--;
        else if (pause_choose == 's' || pause_choose == 'S')
            pause_move++;

        if (pause_move < 0)
            pause_move = 3;
        else if (pause_move > 3)
            pause_move = 0;
    }
    if (pause_move == 1)
        rr = true;
    system("cls");
    switch (pause_move)
    {
    case 0:
        the_game();
        break;
    case 1:
        restart();
        break;
    case 2:
    {
        cout << "\n    press 'B' yo go back\n\n";
        cout << "                                                   DESCRIPTION\n";
        cout << "                                                   -----------\n";
        cout << "The player controls a long, thin creature, resembling a snake, which roams around on a bordered plane,\npicking up food (or some other item), trying to avoid hitting its own tail or the edges of the playing area.\nEach time the snake eats a piece of food, its tail grows longer, making the game increasingly difficult." << endl;
        cout << "------------------------------------------------------------------------------------------------------\n";
        cout << "                                                   CONTROLS\n";
        cout << "                                                   --------\n";
        cout << "press 'w' to move upwards" << endl;
        cout << "press 's' to move downwards" << endl;
        cout << "press 'd' to move to the right" << endl;
        cout << "press 'a' to move to the left" << endl;
        cout << "                                     ------------------------------------\n";
        char b = _getch();
        if (b == 'b' || b == 'B')
        {
            system("cls");
            pause();
        }
        break;
    }
    case 3:
        exit(0);

    default:
        pause();
    }
}
int main()
{

    menu();
    losing_screen();
    system("pause");
    return 0;
}