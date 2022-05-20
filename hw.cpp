// TODO: better coding style

/*
* Space Shooter - a simple C++ game
* Sprout 2022 project 2
* inspired by Carlos Hernández Castañeda - 2016
*
*/
#include <stdlib.h> //Standard c and c++ libraries
#include <list>
#include <vector>
#include <string>
#include <iostream>
#include <thread> // for sleep
#include <chrono> // for sleep

using namespace std;
#define UP    72 // arrow keys' ascii numbers
#define LEFT  75
#define RIGHT 77
#define DOWN  80

char frame[80][25];

void PrintEverything(){
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
    DrawString(60,  1, "energy:   0");
    DrawString( 2, 24, "Player 1");
    DrawString(20, 24, "HP: 100");
    DrawString(30, 24, "bullet_power: 3");
    DrawString(50, 24, "Exp:  0");
    DrawString(60, 24, "energy:   0");
    PrintEverything();
    for (int i=2 ; i<79 ; i++) frame[i][12] = '_';
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
    PrintEverything();
}

void GameOverPlayer1WinsMessage(){ // When player1 wins the game you see this in screen
    int a_x = 30;
    int a_y = 11;
    int b_x = a_x + 23;
    int b_y = a_y + 4;
    DrawWindowFrame(a_x,a_y,b_x,b_y);
    DrawString(a_x+1, a_y+2, "   Player1 Wins !!!");
    PrintEverything();
}

void GameOverPlayer2WinsMessage(){ // When player2 wins the game you see this in screen
    int a_x = 30;
    int a_y = 11;
    int b_x = a_x + 23;
    int b_y = a_y + 4;
    DrawWindowFrame(a_x,a_y,b_x,b_y);
    DrawString(a_x+1, a_y+2, "   Player2 Wins !!!");
    PrintEverything();
}

void GameOverDrawMessage(){ // When player2 wins the game you see this in screen
    int a_x = 30;
    int a_y = 11;
    int b_x = a_x + 23;
    int b_y = a_y + 4;
    DrawWindowFrame(a_x,a_y,b_x,b_y);
    DrawString(a_x+1, a_y+2, "       Draw!");
    PrintEverything();
}

void SpecialMessage(){ // A special message for your special needs
    DrawWhiteSpace(1,1,80,24);
    DrawString(30, 11, "Thanks for playing! :3");
    PrintEverything();
}

class SpaceShip{
    private:
    int no; // player 1 or player 2
    int x; // x coordinate
    int y; // y coordinate
    int hp; // heart points
    int power; // energy points
    int energy; // cool down
    int exp; //experiment
    bool imDead; // is the ship dead?
    int shield_tick;
    int double_tick;
    
    public:
    int NO() { return no; }
    int X()  { return x; }
    int Y()  { return y; }
    int POWER() { return power; }
    int ENERGY() { return energy; }
    bool isDead() { return imDead; }
    int SHIELD() { return shield_tick; }
    int DOUBLE() { return double_tick; }

    SpaceShip(int _no){
        no = _no;
        x = 40;
        if (no == 1) y = 18;
        if (no == 2) y = 5;
        hp = 100; // I designed the game to have 100 lifes
        power = 3; // bullet power is 3
        energy = 0;
        exp = 0;
        imDead = false; // By default you are not dead
        shield_tick = -1;
        double_tick = -1;
    }
    
    void DrawSpaceShipInfo(){ // Displays HP and energy points, I aligned them with the labels printed in DrawGameLimits
        int print_y;
        if (no == 1) print_y = 24;
        if (no == 2) print_y = 1;
        
        DrawString(24, print_y, "   ");
        if      (hp >= 100) DrawString(24, print_y, to_string(hp));
        else if  (hp >= 10) DrawString(25, print_y, to_string(hp));
        else                DrawString(26, print_y, to_string(hp));
        
        DrawString(44, print_y, "  ");
        if (power >= 10) DrawString(44, print_y, to_string(power));
        else             DrawString(45, print_y, to_string(power));
                             
        DrawString(54, print_y, "   ");
        if      (exp >= 100) DrawString(54, print_y, to_string(exp));
        else if (exp >=  10) DrawString(55, print_y, to_string(exp));
        else                 DrawString(56, print_y, to_string(exp));
        
        DrawString(67, print_y, "    ");
        if      (energy >= 1000) DrawString(67, print_y, to_string(energy));
        else if (energy >=  100) DrawString(68, print_y, to_string(energy));
        else if (energy >=   10) DrawString(69, print_y, to_string(energy));
        else                 DrawString(70, print_y, to_string(energy));
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
        DrawSpaceShipInfo();
        if (hp <= 0) Explosion();
    }
    
    void Explosion(){ // When you lose a heart :c
        Draw();
        PrintEverything();
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        Erase();
        DrawString(x, y  , " * * ");
        DrawString(x, y+1, "* * *");
        DrawString(x, y+2, " * * ");
        PrintEverything();
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        Erase();
        DrawString(x, y  , "*   *");
        DrawString(x, y+1, " * * ");
        DrawString(x, y+2, "* * *");
        PrintEverything();
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        imDead = true;
    }
    
    bool CrashWithOpponent(SpaceShip ss, char direction){
        if (direction == 'a'){ // ss1 go left
            if ((x-1 == ss.X()+4) and (y <= ss.Y()+2) and (y+2 >= ss.Y())) return true;
        }else if (direction == 'd'){ // ss1 go right
            if ((x+5 == ss.X()) and (y <= ss.Y()+2) and (y+2 >= ss.Y())) return true;
        }else if (direction == 'w'){ // ss1 go up
            if ((y-1 == ss.Y()+2) and (x <= ss.X()+4) and (x+4 >= ss.X())) return true;
        }else if (direction == 's'){ // ss1 go down
            if ((y+3 == ss.Y()) and (x <= ss.X()+4) and (x+4 >= ss.X())) return true;
        }
        return false;
    }
    
    void Move(char key){ // The main function of the spaceship
        energy ++;
        if (double_tick == 0) power /= 2;
        if (shield_tick != -1) shield_tick --;
        if (double_tick != -1) double_tick --;
        //if(kbhit()){ // If you move the spaceship   //TODO: here
        if (true){
            Erase(); // Look I'm invisible
            //char key = getch(); // What did you type?   //TODO: here
            //char key;
            //cin.get(key);
            switch(key){ // Checks if the spaceship won't leave the game boundaries
                case LEFT:  if (x > 3)      x -= 1; break;
                case RIGHT: if (x + 4 < 77) x += 1; break;
                case UP:    if (y > 4)      y -= 1; break;
                case DOWN:  if (y + 2 < 20) y += 1; break;
                case 'a':   if (x != 3)      x -= 1; break;
                case 'd':   if (x + 4 != 77) x += 1; break;
                case 'w':   if ((y != 4) and (y != 13))        y -= 1; break;
                case 's':   if ((y + 2 != 20) and (y+2 != 11)) y += 1; break;
            }
        }
        Draw(); // The spaceship is drawn regardless if you moved it or not, if you did then it will appear in it's new position.
    }
    
    void shootbullet(){
        energy -= 5;
    }
    
    void AddExp(int addexp){
        exp += addexp;
        while (exp >= 100){
            exp -= 100;
            if (double_tick == -1) power += 1;
            if (double_tick != -1) power += 2;
        }
        DrawSpaceShipInfo();
    }
    
    void GetProp(char proptype){
        //  a for hp (20 and 50), b for exp (50 and 100), c for energy (20 and 100), d for shield (30 and 100 ticks), e for double (50 and 100 tick)
        if (proptype == 'a') hp += 10;
        if (proptype == 'A') hp += 30;
        if (hp > 100) hp = 100;
        if (proptype == 'b') AddExp(50);
        if (proptype == 'B') AddExp(100);
        if (proptype == 'c') energy += 50;
        if (proptype == 'C') energy += 100;
        if (proptype == 'd') shield_tick = 50;
        if (proptype == 'D') shield_tick = 100;
        if ((proptype == 'e') or (proptype == 'E')){
            if (double_tick == -1) power *= 2;
        }
        if (proptype == 'e') double_tick = 50;
        if (proptype == 'E') double_tick = 100;
    }
};

class Asteroid{
    private:
    int x;
    int y;
    char direction;
    public:
    int X()  { return x; }
    int Y()  { return y; }

    Asteroid(int _x, int _y, char _direction){
        x = _x;
        y = _y;
        direction = _direction;
    }
    
    bool isOut(){
        if ((y <= 2) or (y >= 22)){ // If the bullet reaches the top or bottom of the map
            frame[x][y] = '_'; // It disappears
            return true; // And informs the ame that it should no longer exist :c
        }
        if ((x <= 1) or (x >= 79)){
            frame[x][y] = '|';
            return true;
        }
        return false;
    }
    
    void MoveAndDraw(){
        if (y != 12) frame[x][y] = ' ';
        if (y == 12) frame[x][y] = '_';
        if (direction == 'a') x --;
        if (direction == 'd') x ++;
        if (direction == 'w') y --;
        if (direction == 's') y ++;
        frame[x][y] = 'o'; // The shape of the asteroid
    }
    
    bool Collision(SpaceShip *ss){ // The bullet finds the spaceship
        if( (x >= ss->X()) && (x <= ss->X() + 4) && (y >= ss->Y()) && (y <= ss->Y() + 2) ){ // Depending on the shape of the spaceship you have to tinker when the bullet really hits you
            if (ss -> SHIELD() == -1){
                ss->Damage(3); // The bullet hurts
                //printf("%d hit by asteroid at %d %d", ss.NO(), x, y);
                frame[x][y] = 'X';
                PrintEverything();
                std::this_thread::sleep_for(std::chrono::milliseconds(100));
            }
            if (y != 12) frame[x][y] = ' '; // And the asteroid is "destroyed"
            if (y == 12) frame[x][y] = '_';
            return true;
        }
        return false;
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
    
    void MoveAndDraw(){
        if (y != 12) frame[x][y] = ' '; // It disappears
        if (y == 12) frame[x][y] = '_';
        if (no == 1) y--;
        if (no == 2) y++;
        frame[x][y] = '.'; // The shape of the bullet
    }
    
    bool Collision(SpaceShip *ss){ // The bullet finds the spaceship
        if( (x >= ss->X()) && (x <= ss->X() + 4) && (y >= ss->Y()) && (y <= ss->Y() + 2) && (no != ss->NO()) ){ // Depending on the shape of the spaceship you have to tinker when the bullet really hits you
            if (ss -> SHIELD() == -1){
                ss->Damage(power); // The bullet hurts
                //printf("%d hit by asteroid at %d %d", ss.NO(), x, y);
                frame[x][y] = 'X';
                PrintEverything();
                std::this_thread::sleep_for(std::chrono::milliseconds(100));
            }
            frame[x][y] = ' '; // And the asteroid is "destroyed"
            return true;
        }
        return false;
    }
};

class Prop{
    private:
    int x;
    int y;
    char type;
    int tick;
    //  a for hp (20 and 50), b for exp (50 and 100), c for energy (20 and 100), d for shield (30 and 100 ticks), e for double (50 and 100 tick)
    public:
    int TYPE()  { return type; }
    
    Prop(int _x, int _y, char _type){
        x = _x;
        y = _y;
        type = _type;
        tick = 200;
    }
    
    bool isOut(){
        if (tick <= 0){
            frame[x][y] = ' ';
            return true;
        }
        return false;
    }
    
    void MoveAndDraw(){
        tick --;
        frame[x][y] = type;
    }
    
    bool Collision(SpaceShip *ss){ // The bullet finds the spaceship
        if( (x >= ss->X()) && (x <= ss->X() + 4) && (y >= ss->Y()) && (y <= ss->Y() + 2) ){ // Depending on the shape of the spaceship you have to tinker when the bullet really hits you
            ss->GetProp(type); // The bullet hurts
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

void GenerateAsteroid(list <Asteroid*> *Asteroids, int tick){
    if (tick == 0) return;
    int temp, probability_inverse = 300000/tick; // probability = (float) (tick) / 200000
    for (int i=4 ; i<=20 ; i++){
        temp = rand() % probability_inverse;
        if (temp == 0) Asteroids -> push_back(new Asteroid(2, i, 'd'));
        temp = rand() % probability_inverse;
        if (temp == 0) Asteroids -> push_back(new Asteroid(78, i, 'a'));
    }
    for (int i=3 ; i<=77 ; i++){
        temp = rand() % probability_inverse;
        if (temp == 0) Asteroids -> push_back(new Asteroid(i, 3, 's'));
        temp = rand() % probability_inverse;
        if (temp == 0) Asteroids -> push_back(new Asteroid(i, 21, 'w'));
    }
    return;
}

void GenerateProps(list <Prop*> *Props, int tick){
    int temp = rand() % 50000;
    if ((temp <= tick) and (temp <= 500)){
        int x1 = rand() % 75 + 3, x2 = rand() % 75 + 3;
        int y1 = rand() % 8 + 4,  y2 = rand() % 8 + 13;
        char type;
        //temp = rand() % 1000;
        //if (temp <= tick) type = temp % 5 + 'A';
        //if (temp > tick) type = temp % 5 + 'a';
        type = temp % 5 + 'A';
        Props -> push_back(new Prop(x1, y1, type));
        Props -> push_back(new Prop(x2, y2, type));
    }
}

template <typename T>
void Move(T *Things){
    typename T::iterator thing;
    for(thing = Things->begin() ; thing != Things->end() ; thing++){
        (*thing)->MoveAndDraw();
        if ( (*thing)->isOut() ){ // If the bullet reaches the end of the map or hit a player
            delete(*thing);
            thing = Things -> erase(thing);
        }
    }
    return;
}

template <typename T>
void CollisionWithSpaceship(T *Things, SpaceShip *ss){
    typename T::iterator thing;
    for(thing = Things->begin() ; thing != Things->end() ; thing++){
        if ( (*thing)->Collision(ss) ){ // If the bullet reaches the end of the map or hit a player
            delete(*thing);
            thing = Things -> erase(thing);
        }
    }
    return;
}

vector <int> AddExperience(list <Asteroid *> *Asteroids, list <Bullet *> *Bullets){
    vector <int> answer(2, 0);
    for(list <Asteroid *>::iterator asteroid = Asteroids->begin(); asteroid != Asteroids->end(); asteroid++){
        for(list <Bullet *>::iterator bullet = Bullets->begin(); bullet != Bullets->end(); bullet++){ // asteroid-bullet collision
            int astX = (*asteroid)->X(), astY = (*asteroid)->Y(); // Coordinates of the asteroid
            int bulX = (*bullet)->X(), bulY = (*bullet)->Y(); // Coordinates of the bullet
            if((astX == bulX) && (astY == bulY)){ //Chances are that in the Y axis they never reach the same value, that case must be considered
                if (bulY != 12) frame[bulX][bulY] = ' '; // Makes the bullet invisible
                if (bulY == 12) frame[bulX][bulY] = '_';
                frame[astX][astY] = 'X';
                PrintEverything();
                std::this_thread::sleep_for(std::chrono::milliseconds(100));
                if (astY != 12) frame[astX][astY] = ' '; // I still have my doubts in this part, but it tries to signal a collision, sometimes the X remains theme...
                if (astY == 12) frame[astX][astY] = '_';
                answer.at((*bullet)->NO()-1) += 20;
                    
                delete(*bullet); // You delete the bullet
                bullet = Bullets -> erase(bullet);
                delete(*asteroid);// And the asteroid
                asteroid = Asteroids -> erase(asteroid);
                if (bullet == Bullets->end()) break;
                if (asteroid == Asteroids->end()) return answer;
            }
        }
    }
    return answer;
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
    list<Asteroid*> Asteroids; // The same goes for the asteroids
    list<Prop*> Props;
    SpaceShip ss1 = SpaceShip(1); // Here our adventure begins
    SpaceShip ss2 = SpaceShip(2);
    
    PrintEverything();
    int tick = 0;

    while(!ss1.isDead() && !ss2.isDead()){ // If a player die then quit the while loop
        tick ++;
        GenerateAsteroid(&Asteroids, tick);  // randomly generate some asteroids at the edges of the screen.
        GenerateProps(&Props, tick);
        // if(kbhit()){
        // If you ahoot a bullet then you add a bullet to the bullet list
        bool shoot1 = isshoot(ss1, Asteroids, Bullets);
        if ((shoot1 == true) && (ss1.ENERGY() >= 5)){
            Bullets.push_back(new Bullet(ss1));
            ss1.shootbullet();
        }
        bool shoot2 = isshoot(ss2, Asteroids, Bullets);
        if ((shoot2 == true) && (ss2.ENERGY() >= 5)){
            Bullets.push_back(new Bullet(ss2));
            ss2.shootbullet();
        }
        
        Move(&Props);
        
        vector <int> addexp;
        // Move bullets
        Move(&Bullets);
        CollisionWithSpaceship(&Bullets, &ss1);
        CollisionWithSpaceship(&Bullets, &ss2);
        addexp = AddExperience(&Asteroids, &Bullets);
        ss1.AddExp(addexp.at(0));
        ss2.AddExp(addexp.at(1));
        if ((ss1.isDead() == true) or (ss2.isDead() == true)) break;
        
        Move(&Asteroids);
        CollisionWithSpaceship(&Asteroids, &ss1);
        CollisionWithSpaceship(&Asteroids, &ss2);
        addexp = AddExperience(&Asteroids, &Bullets);
        ss1.AddExp(addexp.at(0));
        ss2.AddExp(addexp.at(1));
        if ((ss1.isDead() == true) or (ss2.isDead() == true)) break;
        
        char direction1 = HowToMove(ss1, Asteroids, Bullets);
        if (ss1.CrashWithOpponent(ss2, direction1) == false) ss1.Move(direction1);
        CollisionWithSpaceship(&Bullets, &ss1);
        CollisionWithSpaceship(&Asteroids, &ss1);
        CollisionWithSpaceship(&Props, &ss1);
        if ((ss1.isDead() == true) or (ss2.isDead() == true)) break;
        
        char direction2 = HowToMove(ss2, Asteroids, Bullets);
        if (ss2.CrashWithOpponent(ss1, direction2) == false) ss2.Move(direction2);
        CollisionWithSpaceship(&Bullets, &ss2);
        CollisionWithSpaceship(&Asteroids, &ss2);
        CollisionWithSpaceship(&Props, &ss2);
        if ((ss1.isDead() == true) or (ss2.isDead() == true)) break;
        
        PrintEverything();
        std::this_thread::sleep_for(std::chrono::milliseconds(30)); // This is essential, otherwise the game would be unplayable
    }
    if (ss1.isDead() && ss2.isDead()) GameOverDrawMessage(); // Two players die at the same time.
    else if (ss2.isDead()) GameOverPlayer1WinsMessage(); // If player2 died
    else GameOverPlayer2WinsMessage(); // If player1 died
    cout << tick << endl;
    return 0;
}
