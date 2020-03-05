#ifndef STUDENTWORLD_H_
#define STUDENTWORLD_H_

#include "GameWorld.h"
#include <string>
#include <vector>

using Direction = int;
// Students:  Add code to this file, StudentWorld.cpp, Actor.h, and Actor.cpp
class Actor;
class Socrates;
class Bacterium;

class StudentWorld : public GameWorld
{
public:
    StudentWorld(std::string assetPath);
    virtual ~StudentWorld();
    virtual int init();
    virtual int move();
    virtual void cleanUp();

    std::string formatScore(int score);
    std::string formatText(int score, int lvl, int lives, int health, int sprays, int flames); 
    void setDisplayText();

  //helper functions
    void socratesCoords(double& x, double& y);
    void deleteDeadActors();
    bool damagedOrNot(Actor* check, int dmgAmount);
    bool bacteriumOverlap(Actor* check, int dmgAmount);
    bool bacteriumFoodOverlap(Actor* check);
    bool bacteriumCanMove(Actor* check);
    bool EColiMove(Actor* check, double& xfuture, double& yfuture);
    bool findClosestBact(Actor* check, Direction& angle);
    bool goodiePickup(Actor* check);
    bool ifMoveOverlap(double x1, double y1, double x2, double y2);
    bool ifObjOverlap(double x1, double y1, double x2, double y2);
    int getVecSize() const;
    
    void pushback4me(Actor* pass);

    int getPit() const;
    int getBact() const;
    
    void setPit(int amount);
    void setBactCount(int amount);
    void incBact();
    void decBact();
    void incPit();
    void decPit();

private:
    std::vector<Actor*> objs; 
    Socrates* currSoc;
    int dirtCount;
    int pitCount;
    int bacteriumCount;

};

#endif // STUDENTWORLD_H_
