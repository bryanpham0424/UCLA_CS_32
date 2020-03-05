#include "StudentWorld.h"
#include "GameConstants.h"
#include "Actor.h"
#include <string>
using namespace std;

GameWorld* createStudentWorld(string assetPath)
{
	return new StudentWorld(assetPath);
}

// Students:  Add code to this file, StudentWorld.h, Actor.h and Actor.cpp

StudentWorld::StudentWorld(string assetPath)
: GameWorld(assetPath)
{
}

StudentWorld::~StudentWorld()
{
}

int StudentWorld::init()
{
    Socrates* addSoc;
    addSoc = new Socrates(this);
    currSoc = addSoc;
    objs.push_back(currSoc);

    setBactCount(0);
    int pits = getLevel();
    setPit(pits);
    for (int i = 0; i < pits; i++) {
       // bool flag = false;
        int x, y;
        x = randInt(0, VIEW_WIDTH);
        int circleBound = sqrt(pow(120, 2) - pow(x - 128, 2));
        y = randInt(-1 * circleBound + 128, circleBound + 128);
        //for (int j = 0; j < objs.size(); j++) {
        //    if (ifObjOverlap(x, y, objs[j]->getX(), objs[j]->getY()) == true && objs[j]->hasInvent() == true) {
        //        i--;
        //        flag = true;
        //        break;
        //    }

        //}
        //if (flag) {
        //    continue;
        //}
        Pit* addPit;
        addPit = new Pit(this, x, y);
        pushback4me(addPit);
    }

    int foods = min(getLevel() * 5, 25);
    for (int i = 0; i < foods; i++) {
        int x, y;
        x = randInt(0, VIEW_WIDTH);
        int circleBound = sqrt(pow(120, 2) - pow(x - 128, 2));
        y = randInt(-1 * circleBound + 128, circleBound + 128);
        for (int i = 0; i < objs.size(); i++) {
            if (ifObjOverlap(x, y, objs[i]->getX(), objs[i]->getY()) == true) {
                if (objs[i]->hasInvent() == true || objs[i]->isFood()) {
                    break;
                }
            }

        }
        Food* addFood;
        addFood = new Food(this, x , y);
        pushback4me(addFood);
    }

    int dirtAdd = max(180 - 20 * getLevel(), 20);
    dirtCount = dirtAdd;
   
   for (int i = 0; i < dirtCount; i++) {
        int x, y;
        x = randInt(0, VIEW_WIDTH);
        int circleBound = sqrt(pow(120, 2) - pow(x - 128, 2));
        y = randInt(-1 * circleBound + 128, circleBound + 128);
        Dirt* addDirt;
        addDirt = new Dirt(this,x, y);
        objs.push_back(addDirt);
    }

    return GWSTATUS_CONTINUE_GAME;
}

int StudentWorld::move()
{
    // This code is here merely to allow the game to build, run, and terminate after you hit enter.
    // Notice that the return value GWSTATUS_PLAYER_DIED will cause our framework to end the current level.
    setDisplayText();
    
    for (int i = 0; i < objs.size(); i++) {
        if (objs[i]->getStatus() == true) {
            objs[i]->doSomething();
           
            if (currSoc->getStatus() == false) {
                return GWSTATUS_PLAYER_DIED; 
            }
            if (getBact() == 0 && getPit() == 0) {
                return GWSTATUS_FINISHED_LEVEL;
            }
        }

    }

    
    int lifetimeAmount = max(randInt(0, 300 - 10 * getLevel() - 1), 50);
    int ChanceGoodie = max(510 - getLevel()*10, 250);
    int ChanceFungus = max(510 - getLevel()*10,200);
    Direction randDir = randInt(0, 359);
    int rand = randInt(0, ChanceGoodie);
    int randFung = randInt(0, ChanceFungus);
    double x = VIEW_RADIUS + VIEW_RADIUS * cos(randDir * (4 * atan(1)) / 180);
    double y = VIEW_RADIUS + VIEW_RADIUS * sin(randDir * (4 * atan(1)) / 180);
    if (rand == 0) {
        int type = randInt(1,10);
        if (type >= 1 && type < 7) {
            Goodie* addGoodie;
            addGoodie = new RestoreHealthGoodie(this, lifetimeAmount, x, y);
            pushback4me(addGoodie);
        }
        if (type >= 7 && type <= 9) {
            FlamethrowerGoodie* addFlame;
            addFlame = new FlamethrowerGoodie(this, lifetimeAmount, x, y);
            pushback4me(addFlame);
        }
        if (type == 10) {
            ExtraLifeGoodie* addExtra;
            addExtra = new ExtraLifeGoodie(this, lifetimeAmount, x, y);
            pushback4me(addExtra);
        }
    }
    if (randFung == 0) {
        Fungus* addFungus;
        addFungus = new Fungus(this, lifetimeAmount, x, y);
        pushback4me(addFungus);
    }
    deleteDeadActors();
    return GWSTATUS_CONTINUE_GAME;
}

void StudentWorld::cleanUp()
{
    std::vector<Actor*>::iterator it = objs.begin();
    while (it != objs.end()) {
        delete (*it);
        it = objs.erase(it);
    }
    currSoc = nullptr;
}

std::string StudentWorld::formatScore(int score)
{
    std::string result;
    int zeros = 0;
    if (score < 0) {
        score *= (-1);
        std::string scores = to_string(score);
        zeros += (6 - scores.size());
        result += "-";
        for (int i = 0; i < zeros; i++) {
            result += "0";
        }
        result += scores;
        return result;
    }
    std::string scores = to_string(score);
    zeros += (6 - scores.size());
    for (int i = 0; i < zeros; i++) {
        result += "0";
    }
    result += scores;
    return result;
}

std::string StudentWorld::formatText(int score, int lvl, int lives, int health, int sprays, int flames)
{
    std::string formatted = formatScore(score);
    std::string s = "Score: ";
    s += formatted;
    s += " Level: ";
    s += to_string(lvl);
    s += " Lives: ";
    s += to_string(lives);
    s += " health: ";
    s += to_string(health);
    s += " Sprays: ";
    s += to_string(sprays);
    s += " Flames: ";
    s += to_string(flames);
    return s;
}

void StudentWorld::setDisplayText()
{
    int score = getScore();
    int lvl = getLevel();
    int lives = getLives();
    int health = currSoc->getHp();
    int sprays = currSoc->getSpray();
    int flames = currSoc->getFlame();

    std::string display = formatText(score, lvl, lives, health, sprays, flames);
    setGameStatText(display);

    return;
}

void StudentWorld::socratesCoords(double& x, double& y)
{
    x = currSoc->getX();
    y = currSoc->getY();
}

void StudentWorld::deleteDeadActors()
{
    for (vector<Actor*>::iterator it = objs.begin(); it != objs.end();) {
        if ((*it)->getStatus() == false) {
            delete (*it);
            it = objs.erase(it);
        }
        else
            it++;
    }
}

bool StudentWorld::damagedOrNot(Actor* check, int dmgAmount) 
{
    for (int i = 0; i < objs.size(); i++) {
        if (ifObjOverlap(check->getX(), check->getY(), objs[i]->getX(), objs[i]->getY()) == true && objs[i]->damageable() == true) {
            if (objs[i]->isBacterium() == true) {
                if (objs[i]->typeBact() == 1 || objs[i]->typeBact() == 2) {
                    playSound(SOUND_SALMONELLA_HURT);
                }
                if (objs[i]->typeBact() == 3) {
                    playSound(SOUND_ECOLI_HURT);
                }
            }
            objs[i]->takeDmg(dmgAmount);
            if (objs[i]->getHp() <= 0) {
                if (objs[i]->typeBact() == 1 || objs[i]->typeBact() == 2) {
                    playSound(SOUND_SALMONELLA_DIE);
                    decBact();
                    objs[i]->isNowDead();
                }
                if (objs[i]->typeBact() == 3) {
                    playSound(SOUND_ECOLI_DIE);
                    decBact();
                    objs[i]->isNowDead();
                }
            }
            return true;
        }
        
    }
    return false;
}

bool StudentWorld::bacteriumOverlap(Actor* check, int dmgAmount)
{
    if (ifObjOverlap(check->getX(), check->getY(), currSoc->getX(), currSoc->getY()) == true) {
        currSoc->reduceHp(dmgAmount);
        playSound(SOUND_PLAYER_HURT);
        if (currSoc->getHp() <= 0) {
            playSound(SOUND_PLAYER_DIE);
            decLives();
            currSoc->isNowDead();
        }
        return true;
    }
    return false;
}

bool StudentWorld::bacteriumFoodOverlap(Actor* check)
{
    for (int i = 0; i < objs.size(); i++) {
        if ((ifObjOverlap(check->getX(), check->getY(), objs[i]->getX(), objs[i]->getY())) == true && objs[i]->isFood() == true) {
            objs[i]->isNowDead();
            
            return true;
        }
    }
    return false;
}

bool StudentWorld::bacteriumCanMove(Actor* check)
{
    double addx, addy;
    addx = 3 * cos(check->getDirection() * (4 * atan(1)) / 180);
    addy = 3 * sin(check->getDirection() * (4 * atan(1)) / 180);
    double futurex = (check->getX())  + addx;
    double futurey = (check->getY())  + addy;
    double hypot = sqrt(pow(futurex- 128, 2) + pow(futurey - 128, 2));
    if (hypot > 128) {
        return false;
    }
    for (int i = 0; i < objs.size(); i++) {
        if ((ifMoveOverlap(futurex, futurey, objs[i]->getX(), objs[i]->getY())) == true && objs[i]->isDirt() == true) {
            return false;
        }
    }
    check->moveTo(futurex, futurey);
    return true;
}

bool StudentWorld::EColiMove(Actor* check, double& xfuture, double& yfuture)
{
    for (int i = 0; i < objs.size(); i++) {
        if (objs[i]->isDirt() == true && ifMoveOverlap(xfuture, yfuture, objs[i]->getX(), objs[i]->getY()) == true) {
            return false;
        }
    }
    return true;
}

bool StudentWorld::findClosestBact(Actor* check, Direction& angle)
{
    std::vector<Actor*> food;
    for (int i = 0; i < objs.size(); i++) {
        if (objs[i]->isFood() == true) {
            food.push_back(objs[i]);
        }
    }
    if (food.empty()) {
        return false;
    }
    Actor* closest = food[0];
    double x = food[0]->getX();
    double y = food[0]->getY();
    double distance = sqrt(pow(x - check->getX(),2) + pow(y - check->getY(),2));
    for (int i = 0; i < food.size(); i++) {
        x = food[i]->getX();
        y = food[i]->getY();
        double compareDist;
        compareDist = sqrt(pow(x - check->getX(),2) + pow(y - check->getY(),2));
        if (compareDist < distance) {
            distance = compareDist;
            closest = food[i];
        }
        
    }

    if (distance > 128) {
        return false;
    }
    Direction val;
    val = atan2(closest->getY() - check->getY(), closest->getX() -check->getX())  * (180/(4*atan(1)));

    check->setDirection(val);
    angle = val;
    return true;
}

bool StudentWorld::goodiePickup(Actor* check)
{
    
        if (ifObjOverlap(check->getX(), check->getY(), currSoc->getX(), currSoc->getY())) {
            if (check->isGoodie() == true) {
                if (check->goodieType() == 1) {
                    increaseScore(250);
                    currSoc->setHealth(100);
                    playSound(SOUND_GOT_GOODIE);
                    return true;
                }
                if (check->goodieType() == 2) {
                    increaseScore(300);
                    currSoc->incOrDecFlame(5);
                    playSound(SOUND_GOT_GOODIE);
                    return true;
                }
                if (check->goodieType() == 3) {
                    increaseScore(500);
                    incLives();
                    playSound(SOUND_GOT_GOODIE);
                    return true;
                }
                if (check->goodieType() == 4) {
                    increaseScore(-50);
                    currSoc->reduceHp(20);
                    if (currSoc->getHp() <= 0) {
                        playSound(SOUND_PLAYER_DIE);
                        currSoc->isNowDead();
                        decLives();
                        return true;
                    }
                    playSound(SOUND_PLAYER_HURT);
                    return true;
                }
            }
        }
    return false;
}

bool StudentWorld::ifMoveOverlap(double x1, double y1, double x2, double y2)
{
    double euclidean = (SPRITE_WIDTH / 2);
    double dist = sqrt(pow(x2-x1,2) + pow(y2-y1,2));

    return(dist <= euclidean); //if true, blocked, otherwise false
}

bool StudentWorld::ifObjOverlap(double x1, double y1, double x2, double y2)
{
    double dist = sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
    return (dist <= SPRITE_WIDTH); //if true, overlap
}

int StudentWorld::getVecSize() const
{
    return objs.size();
}



void StudentWorld::pushback4me(Actor* pass)
{
    objs.push_back(pass);
}

int StudentWorld::getPit() const
{
    return pitCount;
}

int StudentWorld::getBact() const
{
    return bacteriumCount;
}

void StudentWorld::setPit(int amount)
{
    pitCount = amount;
}

void StudentWorld::setBactCount(int amount)
{
    bacteriumCount = amount;
}

void StudentWorld::incBact()
{
    bacteriumCount++;
}

void StudentWorld::decBact()
{
    bacteriumCount--;
}

void StudentWorld::incPit()
{
    pitCount++;
}

void StudentWorld::decPit()
{
    pitCount--;
}


