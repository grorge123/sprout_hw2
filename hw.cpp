

/*
* Space Shooter - a simple C++ game for Windows
* developed by Carlos Hernández Castañeda - 2016
*
*/
#include <stdlib.h> //Standard c and c++ libraries
//#include <conio.h>
#include <stdio.h>
//#include <windows.h> // To take control over the terminal
#include <list>
#include <string>
#include <iostream>
#include <thread> // for sleep
#include <chrono> // for sleep
#include <fcntl.h>
#include <curses.h>

using namespace std;
#define UP    72 // arrow keys' ascii numbers
#define LEFT  75
#define RIGHT 77
#define DOWN  80

char frame[80][25];

void printframe(){
    system("clear");
    for (int i=0 ; i<25 ; i++){
        for (int j=0 ; j<80 ; j++) cout << frame[j][i];
        cout << endl;
    }
}

void DrawWhiteSpace(int a_x, int a_y, int b_x, int b_y){ // To clean a certain space in the terminal
    for(int i = a_x; i < b_x; i++){
        for(int j = a_y; j < b_y; j++) frame[i][j] = ' ';
    }
}

void DrawWindowFrame(int a_x, int a_y, int b_x, int b_y){ // This will draw a rectangular frame defined by two points
    DrawWhiteSpace(a_x,a_y,b_x,b_y);
    for(int i = a_x; i < b_x; i++){
        frame[i][a_y] = '_';
        frame[i][b_y] = '_'; // 205
    }
    for(int i = a_y+1; i < b_y; i++){
        frame[a_x][i] = '|';
        frame[b_x][i] = '|'; // 186
    }
    //frame[a_x][a_y] = (char) 201;
    //frame[b_x][a_y] = (char) 187;
    //frame[a_x][b_y] = (char) 200;
    //frame[b_x][b_y] = (char) 188;
}

void DrawString(int x, int y, string buf){
    int length = buf.size();
    for (int i=0 ; i<length ; i++) frame[x+i][y] = (char) buf.at(i);
}

void DrawGameLimits(){ // Draws the game limits, and information that doesn't have to be printed repeatedly
    DrawWindowFrame(1,2,79,23); // The default size of the Windows terminal is 25 rows x 80 columns
    DrawString(2, 1, "HP: 3");
    DrawString(16, 1, "ENERGY: 0");
    DrawString(50, 1, "SCORE: 0");
    printframe();
}

void WelcomeMessage(){ // The main title, I tried to center it as best as I could
    int x = 13;
    int y = 6;
    DrawWindowFrame(1,2,79,23);
    DrawString(13, 6, " _____                    _____ _           _           ");
    DrawString(13, 7, "|   __|___ ___ ___ ___   |   __| |_ ___ ___| |_ ___ ___ ");
    DrawString(13, 8, "|__   | . | .'|  _| -_|  |__   |   | . | . |  _| -_|  _|");
    DrawString(13, 9, "|_____|  _|__,|___|___|  |_____|_|_|___|___|_| |___|_|  ");
    DrawString(13, 10, "      |_|");
    DrawString(13, 12, "                 Press enter to play");
    DrawString(13, 13, "         developed by Carlos Hernandez C. - 2016");
    printframe();
}

void GameOverDefeatMessage(){ // When you lose the game you see this in screen
    int a_x = 30;
    int a_y = 11;
    int b_x = a_x + 23;
    int b_y = a_y + 4;
    DrawWindowFrame(a_x,a_y,b_x,b_y);
    DrawString(a_x+1, a_y+2, "      DEFEAT!!!");
    printframe();
}

void GameOverVictoryMessage(){ // When you win the game you see this in screen
    int a_x = 30;
    int a_y = 11;
    int b_x = a_x + 23;
    int b_y = a_y + 4;
    DrawWindowFrame(a_x,a_y,b_x,b_y);
    DrawString(a_x+1, a_y+2, "      VICTORY!!!");
    printframe();
}

void SpecialMessage(){ // A special message for your special needs
    DrawWhiteSpace(1,1,80,24);
    DrawString(30, 11, "Thanks for playing! :3");
    printframe();
}

class SpaceShip{
    private:
    int x; // x coordinate
    int y; // y coordinate
    int hp; // heart points
    int energy; // energy points
    bool imDead; // is the ship dead?
    
    public:
    int X()  { return x; }
    int Y()  { return y; }
    int HP() { return hp; }

    bool isDead(){
        DrawSpaceShipInfo(); // It's annoying to die and still see a heart on the screen
        return imDead;
    }

    SpaceShip(int _x, int _y){
        x = _x;
        y = _y;
        hp = 3; // I designed the game to have 3 lifes
        energy = 5; // And 5 energy points every life
        imDead = false; // By default you are not dead
    }
    
    void DrawSpaceShipInfo(){ // Displays HP and energy points, I aligned them with the labels printed in DrawGameLimits
        DrawString(5, 1, "     ");
        DrawString(5, 1, to_string(hp));
        DrawString(23, 1, "     ");
        DrawString(23, 1, to_string(energy));
    }
    
    void Erase(){ // This was our spaceship
        for (int i=0 ; i<3 ; i++) DrawString(x, y+i, "     ");
    }

    void Draw(){ // This is our spaceship
        Erase();
        frame[x+2][y] = (unsigned char) 30;
        frame[x+2][y+1] = (unsigned char) 4;
        frame[x][y+2] = (unsigned char) 17;
        frame[x+1][y+2] = (unsigned char) 30;
        frame[x+2][y+2] = (unsigned char) 223;
        frame[x+3][y+2] = (unsigned char) 30;
        frame[x+4][y+2] = (unsigned char) 16;
        DrawString(x, y  , "  *  ");
        DrawString(x, y+1, "  *  ");
        DrawString(x, y+2, "*****");
    }
    
    void Damage(){ // Triggered by the asteroids that hit the spaceship
        energy--;
        if(energy == 0) Explosion();
        else{
            Erase(); // You can omit this part, is meant to visually tell you that you were hit
            DrawString(x, y  , "  *  ");
            DrawString(x, y+1, "  *  ");
            DrawString(x, y+2, "*****");
            printframe();
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }
    }
    
    void Explosion(){ // When you lose a heart :c
        hp--;
        Erase();
        DrawString(x, y  , "  *  ");
        DrawString(x, y+1, "  *  ");
        DrawString(x, y+2, "*****");
        printframe();
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        Erase();
        DrawString(x, y  , " * * ");
        DrawString(x, y+1, "* * *");
        DrawString(x, y+2, " * * ");
        printframe();
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        Erase();
        DrawString(x, y  , "*   *");
        DrawString(x, y+1, " * * ");
        DrawString(x, y+2, "* * *");
        printframe();
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        if (hp > 0) energy = 5;
        else imDead = true;
    }
    
    void Move(char key){ // The main function of the spaceship
        //if(kbhit()){ // If you move the spaceship   //TODO: here
        if (true){
            Erase(); // Look I'm invisible
            //char key = getch(); // What did you type?   //TODO: here
            //char key;
            //cin.get(key);
            switch(key){ // Checks if the spaceship won't leave the game boundaries
                case LEFT:  if(x > 2)      x -= 1; break;
                case RIGHT: if(x + 4 < 77) x += 1; break;
                case UP:    if(y > 3)      y -= 1; break;
                case DOWN:  if(y + 2 < 22) y += 1; break;
                case 'a':   if(x > 2)      x -= 1; break;
                case 'd':   if(x + 4 < 77) x += 1; break;
                case 'w':   if(y > 3)      y -= 1; break;
                case 's':   if(y + 2 < 22) y += 1; break;
            }
        }
        Draw(); // The spaceship is drawn regardless if you moved it or not, if you did then it will appear in it's new position.
    }
};

class Asteroid{
    private:
    int x;
    int y;
    public:
    int X()  { return x; }
    int Y()  { return y; }

    Asteroid(int _x, int _y){
        x = _x;
        y = _y;
    }
    
    void Draw(){
        frame[x][y] = '*'; // Fear the asteroids!!
    }
    
    void Collision(SpaceShip &ss){ // The asteroid finds the spaceship
        if(((x >= ss.X()) && (x <= ss.X() + 5)) && ((y >= ss.Y()) && (y <= ss.Y() + 2))){ // Depending on the shape of the spaceship you have to tinker when the asteroid really hits you
            ss.Damage(); // The asteroid hurts
            frame[x][y] = ' '; // And the asteroid is "destroyed"
            x = rand()%74 + 3; // The truth is it just teleports to the top of the map
            y = 4;
        }else{
            frame[x][y] = ' ';
            y++;
            if(y > 22){ // If the asteroid goes too down in the map
                x = rand()%74 + 3; // It will be teleported to the top
                y = 4;
            }
            Draw();
        }
    }
};

class Bullet{
    private:
    int x;
    int y;
    public:
    int X()  { return x; }
    int Y()  { return y; }
    Bullet(int _x, int _y){
        x = _x;
        y = _y;
    }
    
    bool isOut(){
        if(y <= 3){ // If the bullet reaches the top of the map
            frame[x][y] = ' '; // It disappears
            return true; // And informs the ame that it should no longer exist :c
        }else return false;
    }
    
    void Move(){
        frame[x][y] = ' ';
        y--;
        frame[x][y] = '.'; // The shape of the bullet
    }
};

bool isshoot(SpaceShip ss, list<Asteroid*> Asteroid, list<Bullet*>){
    if (rand()%2 == 0) return true;
    else return false;
}

char HowToMove(SpaceShip ss, list<Asteroid*> Asteroid, list<Bullet*>){
    int temp = rand()%5;
    if (temp == 0) return 'a';
    if (temp == 1) return 's';
    if (temp == 2) return 'd';
    if (temp == 3) return 'w';
    if (temp == 4) return 'x';
    return 'x';
}

int main(){
    srand(time(NULL));
    system("clear");
    DrawWhiteSpace(0, 0, 79, 24);
    WelcomeMessage();
    //getch();   //TODO: here
    char key;
    key = getchar();
    char temp;
    
    DrawGameLimits();
    //fcntl(0, F_SETFL, O_NONBLOCK);

    list<Bullet*> Bullets; // We will use a dynamic list for the bullets in the game
    list<Bullet*>::iterator bullet; // And an iterator for the list

    list<Asteroid*> Asteroids; // The same goes for the asteroids
    list<Asteroid*>::iterator asteroid;

    for(int i = 0; i < 10; i++) Asteroids.push_back(new Asteroid(rand()%78 + 1, rand()%4 + 3)); // Pick as many asteroids as you want. They are randomly placed in the map but not too low

    SpaceShip ss = SpaceShip(40,20); // Here our adventure begins
    int score = 0; // Your score :3

    while(!ss.isDead() && score != 100){ // If you die or reach 100 points the game ends
        // if(kbhit()){
        bool shoot = isshoot(ss, Asteroids, Bullets);
        if (shoot == true) Bullets.push_back(new Bullet(ss.X() + 2, ss.Y() - 1)); // If you press the space bar you add a bullet to the bullet list
        
        for(bullet = Bullets.begin(); bullet != Bullets.end(); bullet++){ // For every bullet that is in space
            (*bullet)->Move();
            if((*bullet)->isOut()){ // If the bullet reached the end of the map
                delete(*bullet); // It gets deleted
                bullet = Bullets.erase(bullet);
            }
        }
        for(asteroid = Asteroids.begin(); asteroid != Asteroids.end(); asteroid++) (*asteroid)->Collision(ss); // Every asteroid checks if the spaceship shares it's coordinates :3
        for(asteroid = Asteroids.begin(); asteroid != Asteroids.end(); asteroid++){
            for(bullet = Bullets.begin(); bullet != Bullets.end(); bullet++){ // asteroid-bullet collision
                int astX = (*asteroid)->X(); //Coordinates of the asteroid
                int astY = (*asteroid)->Y();
                int bulX = (*bullet)->X(); // Coordinates of the bullet
                int bulY = (*bullet)->Y();
                if((astX == bulX) && ((astY == bulY) || (astY + 1 == bulY))){ //Chances are that in the Y axis they never reach the same value, that case must be considered
                    frame[bulX][bulY] = ' '; // Makes the bullet invisible
                    frame[astX][astY] = 'X';
                    frame[astX][astY] = ' '; // I still have my doubts in this part, but it tries to signal a collision, sometimes the X remains theme...
                    delete(*bullet); // You delete the bullet
                    bullet = Bullets.erase(bullet);
                    delete(*asteroid);// And the asteroid
                    asteroid = Asteroids.erase(asteroid);
                    Asteroids.push_back(new Asteroid(rand()%78 + 1, rand()%4 + 3)); // in order to not reduce the number of asteroids I add one everytime one is destroyed
                    score += 10; // And you get 10 points for a job well done :3
                }
            }
        }
        key = HowToMove(ss, Asteroids, Bullets);
        ss.Move(key);
        if (score != 0) DrawString(56, 1, to_string(score));
        printframe();
        std::this_thread::sleep_for(std::chrono::milliseconds(30)); // This is essential, otherwise the game would be unplayable
    }
    if(!ss.isDead()) GameOverVictoryMessage();// If you died
    else GameOverDefeatMessage(); // If you won
    std::this_thread::sleep_for(std::chrono::milliseconds(2000));
    SpecialMessage(); // Surprise
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    return 0;
}
