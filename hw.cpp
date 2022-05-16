// TODO: don't let two players bump into each other.
// TODO: segmentation fault but I don't know why. (maybe about asteroid)
// TODO: add asteroid
// TODO: add obstacle



/*
* Space Shooter - a simple C++ game
* Sprout 2022 project 2
* inspired by Carlos Hernández Castañeda - 2016
*
*/
#include <stdlib.h> //Standard c and c++ libraries
#include <stdio.h>
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

void DrawWhiteSpace(int a_x, int a_y, int b_x, int b_y){ // To clean a certain space
    for(int i = a_x; i <= b_x; i++){
        for(int j = a_y; j <= b_y; j++) frame[i][j] = ' ';
    }
}

void DrawWindowFrame(int a_x, int a_y, int b_x, int b_y){ // This will draw a rectangular frame defined by two points
    DrawWhiteSpace(a_x,a_y,b_x,b_y);
    for(int i = a_x; i < b_x; i++){
        frame[i][a_y] = '_';
        frame[i][b_y-1] = '_';
    }
    for(int i = a_y+1; i < b_y; i++){
        frame[a_x][i] = '|';
        frame[b_x][i] = '|';
    }
}

void DrawString(int x, int y, string buf){
    int length = buf.size();
    for (int i=0 ; i<length ; i++) frame[x+i][y] = (char) buf.at(i);
}

void DrawGameLimits(){ // Draws the game limits, and information that doesn't have to be printed repeatedly
    DrawWindowFrame(1,2,79,23); // The default size of the Windows terminal is 25 rows x 80 columns
    DrawString( 2,  1, "Player 2");
    DrawString(20,  1, "HP: 100");
    DrawString(30,  1, "bullet_power: 3");
    DrawString(50,  1, "Exp:  0");
    DrawString(60,  1, "cooldown:   0");
    DrawString( 2, 24, "Player 1");
    DrawString(20, 24, "HP: 100");
    DrawString(30, 24, "bullet_power: 3");
    DrawString(50, 24, "Exp:  0");
    DrawString(60,  1, "cooldown:   0");
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
    DrawString(13, 12, "                 Press enter to start");
    DrawString(13, 13, "         inspired by Carlos Hernandez C. - 2016");
    printframe();
}

void GameOverPlayer1WinsMessage(){ // When player1 wins the game you see this in screen
    int a_x = 30;
    int a_y = 11;
    int b_x = a_x + 23;
    int b_y = a_y + 4;
    DrawWindowFrame(a_x,a_y,b_x,b_y);
    DrawString(a_x+1, a_y+2, "   Player1 Wins !!!");
    printframe();
}

void GameOverPlayer2WinsMessage(){ // When player2 wins the game you see this in screen
    int a_x = 30;
    int a_y = 11;
    int b_x = a_x + 23;
    int b_y = a_y + 4;
    DrawWindowFrame(a_x,a_y,b_x,b_y);
    DrawString(a_x+1, a_y+2, "   Player2 Wins !!!");
    printframe();
}

void GameOverDrawMessage(){ // When player2 wins the game you see this in screen
    int a_x = 30;
    int a_y = 11;
    int b_x = a_x + 23;
    int b_y = a_y + 4;
    DrawWindowFrame(a_x,a_y,b_x,b_y);
    DrawString(a_x+1, a_y+2, "       Draw!");
    printframe();
}

void SpecialMessage(){ // A special message for your special needs
    DrawWhiteSpace(1,1,80,24);
    DrawString(30, 11, "Thanks for playing! :3");
    printframe();
}

class SpaceShip{
    private:
    int no; // player 1 or player 2
    int x; // x coordinate
    int y; // y coordinate
    int hp; // heart points
    int power; // energy points
    int cd; // cool down
    int exp; //experiment
    bool imDead; // is the ship dead?
    
    public:
    int NO() { return no; }
    int X()  { return x; }
    int Y()  { return y; }
    int HP() { return hp; }
    int POWER() { return power; }
    int CD() {return cd; }

    bool isDead(){
        DrawSpaceShipInfo(); // It's annoying to die and still see a heart on the screen
        return imDead;
    }

    SpaceShip(int _no){
        no = _no;
        x = 40;
        if (no == 1) y = 18;
        if (no == 2) y = 5;
        hp = 100; // I designed the game to have 100 lifes
        power = 3; // bullet power is 3
        exp = 0;
        imDead = false; // By default you are not dead
    }
    
    void DrawSpaceShipInfo(){ // Displays HP and energy points, I aligned them with the labels printed in DrawGameLimits
        int print_y;
        if (no == 1) print_y = 24;
        if (no == 2) print_y = 1;
        DrawString(24, print_y, "   ");
        
        if      (hp >= 100) DrawString(24, print_y, to_string(hp));
        else if  (hp >= 10) DrawString(25, print_y, to_string(hp));
        else                DrawString(26, print_y, to_string(hp));
        DrawString(44, print_y, to_string(power));
                             DrawString(54, print_y, "   "); // to prevent from something like 1000->999 or 100->99
        if      (exp >= 100) DrawString(54, print_y, to_string(exp));
        else if (exp >=  10) DrawString(55, print_y, to_string(exp));
        else                 DrawString(56, print_y, to_string(exp));
                             DrawString(69, print_y, "   "); // to prevent from something like 1000->999 or 100->99
        if      (cd >= 1000) DrawString(69, print_y, to_string(cd));
        else if (cd >=  100) DrawString(70, print_y, to_string(cd));
        else if (cd >=   10) DrawString(71, print_y, to_string(cd));
        else                 DrawString(72, print_y, to_string(cd));
    }
    
    void Erase(){ // This was our spaceship
        for (int i=0 ; i<3 ; i++) DrawString(x, y+i, "     ");
    }

    void Draw(){ // This is our spaceship
        Erase();
        if (no == 1){
            DrawString(x, y  , "  *  ");
            DrawString(x, y+1, "  *  ");
            DrawString(x, y+2, "*****");
        }else{
            DrawString(x, y  , "*****");
            DrawString(x, y+1, "  *  ");
            DrawString(x, y+2, "  *  ");
        }
    }
    
    void Damage(int power){ // Triggered by the asteroids or bullets that hit the spaceship
        hp -= power;
        if(hp <= 0) Explosion();
        else{
            Draw();
            printframe();
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }
    }
    
    void Explosion(){ // When you lose a heart :c
        Draw();
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
        imDead = true;
    }
    
    void Move(char key){ // The main function of the spaceship
        cd ++;
        //if(kbhit()){ // If you move the spaceship   //TODO: here
        if (true){
            Erase(); // Look I'm invisible
            //char key = getch(); // What did you type?   //TODO: here
            //char key;
            //cin.get(key);
            switch(key){ // Checks if the spaceship won't leave the game boundaries
                case LEFT:  if(x > 2)      x -= 1; break;
                case RIGHT: if(x + 4 < 77) x += 1; break;
                case UP:    if(y > 4)      y -= 1; break;
                case DOWN:  if(y + 2 < 20) y += 1; break;
                case 'a':   if(x > 2)      x -= 1; break;
                case 'd':   if(x + 4 < 77) x += 1; break;
                case 'w':   if(y > 4)      y -= 1; break;
                case 's':   if(y + 2 < 20) y += 1; break;
            }
        }
        Draw(); // The spaceship is drawn regardless if you moved it or not, if you did then it will appear in it's new position.
    }
    
    void shootbullet(){
        cd = cd - 3;
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
        frame[x][y] = 'x'; // Fear the asteroids!!
    }
    
    void Collision(SpaceShip &ss){ // The asteroid finds the spaceship
        if( (x >= ss.X()) && (x <= ss.X() + 5) && (y >= ss.Y()) && (y <= ss.Y() + 2) ){ // Depending on the shape of the spaceship you have to tinker when the asteroid really hits you
            ss.Damage(1); // The asteroid hurts
            printf("%d hit by asteroid at %d %d", ss.NO(), x, y);
            frame[x][y] = ' '; // And the asteroid is "destroyed"
            x = rand()%74 + 3; // The truth is it just teleports to the top of the map
            y = 4;
        }else{
            frame[x][y] = ' ';
            y++;
            if (y >= 22){ // If the asteroid goes too down in the map
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
    int no; // 1 if shot by player 1; 2 if shot by player 2
    int power;
    public:
    int X()  { return x; }
    int Y()  { return y; }
    int NO() { return no;}
    int POWER() {return power; }
    Bullet(SpaceShip ss){ // a new bullet shot by ss
        if (ss.NO() == 1){
            no = 1;
            x = ss.X() + 2;
            y = ss.Y() - 1;
        }
        if (ss.NO() == 2){
            no = 2;
            x = ss.X() + 2;
            y = ss.Y() + 3;
        }
        power = ss.POWER();
    }
    
    bool isOut(){
        if ((y <= 3) or (y >= 21)){ // If the bullet reaches the top or bottom of the map
            frame[x][y] = ' '; // It disappears
            if ((y == 2) or (y == 22)) frame[x][y] = '_'; // bound
            return true; // And informs the ame that it should no longer exist :c
        }else return false;
    }
    
    void Move(){
        frame[x][y] = ' ';
        if (no == 1) y--;
        if (no == 2) y++;
        frame[x][y] = '.'; // The shape of the bullet
    }
    
    bool Collision(SpaceShip &ss){ // The bullet finds the spaceship
        if( (x >= ss.X()) && (x <= ss.X() + 5) && (y >= ss.Y()) && (y <= ss.Y() + 2) && (no != ss.NO()) ){ // Depending on the shape of the spaceship you have to tinker when the bullet really hits you
            ss.Damage(power); // The bullet hurts
            //printf("%d hit by asteroid at %d %d", ss.NO(), x, y);
            frame[x][y] = ' '; // And the asteroid is "destroyed"
            return true;
        }
        return false;
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

    list<Bullet*> Bullets; // We will use a dynamic list for the bullets in the game
    list<Bullet*>::iterator bullet; // And an iterator for the list

    list<Asteroid*> Asteroids; // The same goes for the asteroids
    list<Asteroid*>::iterator asteroid;
    
    //for(int i = 0; i < 10; i++) Asteroids.push_back(new Asteroid(rand()%78 + 1, rand()%4 + 3)); // Pick as many asteroids as you want. They are randomly placed in the map but not too low

    SpaceShip ss1 = SpaceShip(1); // Here our adventure begins
    SpaceShip ss2 = SpaceShip(2);
    printframe();
    int tick = 0;

    while(!ss1.isDead() && !ss2.isDead() && tick < 10000){ // If you die or reach 100 points the game ends
        
        tick += 1;
        // if(kbhit()){
        // If you ahoot a bullet then you add a bullet to the bullet list
        bool shoot1 = isshoot(ss1, Asteroids, Bullets);
        if ((shoot1 == true) && (ss1.CD() >= 3)){
            Bullets.push_back(new Bullet(ss1));
            ss1.shootbullet();
        }
        bool shoot2 = isshoot(ss2, Asteroids, Bullets);
        if ((shoot2 == true) && (ss2.CD() >= 3)){
            Bullets.push_back(new Bullet(ss2));
            ss2.shootbullet();
        }
        
        // For every bullet that is in space
        for(bullet = Bullets.begin(); bullet != Bullets.end(); bullet++){
            (*bullet)->Move();
            if((*bullet)->isOut()){ // If the bullet reached the end of the map
                delete(*bullet); // It gets deleted
                bullet = Bullets.erase(bullet);
            }
        }
        
        // Every asteroid checks if the spaceship shares it's coordinates :3
        for(asteroid = Asteroids.begin(); asteroid != Asteroids.end(); asteroid++){
            (*asteroid)->Collision(ss1);
            (*asteroid)->Collision(ss2);
        }
        
        for(bullet = Bullets.begin(); bullet != Bullets.end(); bullet++){
            if ( ((*bullet)->Collision(ss1)) or ((*bullet)->Collision(ss2)) ){
                delete(*bullet);
                bullet = Bullets.erase(bullet);
            }
        }
        
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
                    //score += 10; // And you get 10 points for a job well done :3
                }
            }
        }
        
        key = HowToMove(ss1, Asteroids, Bullets);
        ss1.Move(key);
        key = HowToMove(ss2, Asteroids, Bullets);
        ss2.Move(key);
        printframe();
        std::this_thread::sleep_for(std::chrono::milliseconds(100)); // This is essential, otherwise the game would be unplayable
    }
    if (ss1.isDead()) GameOverPlayer2WinsMessage(); // If player1 died
    else if (ss2.isDead()) GameOverPlayer1WinsMessage(); // If player2 died
    else{
        if (ss1.HP() > ss2.HP()) GameOverPlayer1WinsMessage();
        if (ss1.HP() < ss2.HP()) GameOverPlayer2WinsMessage();
        if (ss1.HP() == ss2.HP()) GameOverDrawMessage();
    }
    std::this_thread::sleep_for(std::chrono::milliseconds(2000));
    //SpecialMessage(); // Surprise
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    return 0;
}
