#ifndef ACTOR_H_
#define ACTOR_H_

#include "GraphObject.h"
#include "StudentWorld.h"
#include "GameConstants.h"
// Students:  Add code to this file, Actor.cpp, StudentWorld.h, and StudentWorld.cpp

class Actor : public GraphObject {
public:
	Actor(StudentWorld* here, int imageID, double startX, double startY, Direction dir, int depth, bool stat, bool dmg, int hp);
	virtual ~Actor();
	//pure virtual functions
	virtual void doSomething() = 0;

	//other functions
	void setHealth(int amount);
	void reduceHp(int amount);
	int getHp() const;
	void newCoords(int dist, Direction dir);
	virtual int goodieType() const;
	virtual int typeBact() const;
	virtual bool hasInvent() const;
	virtual bool isDirt() const;
	virtual bool isBacterium() const;
	virtual bool isSocrates() const;
	virtual bool isGoodie() const;
	virtual bool isFood() const;
	virtual void takeDmg(int value);
	//Accessor

	bool getStatus() const;
	void isNowDead();
	bool damageable() const;
	virtual bool hasHitPoints() const; //Excluding Socrates
	StudentWorld* getWorld();

private:
	bool status;
	int hitpoints;
	bool isDamageable;
	StudentWorld* currWorld;
};

class Socrates : public Actor {
public:
	Socrates(StudentWorld* here, int posAngle = 180, int x = 0, int y = VIEW_HEIGHT/2);
	~Socrates();

	virtual void doSomething();
	virtual bool isSocrates() const;
	void incOrDecFlame(int amount);
	void incOrDecSpray(int amount);
	

	int getFlame() const;
	int getSpray() const;
private:
	int sprayCharge;
	int flameCharge;
	int positionalAngle;
	bool hasSprayed = false;
};

class Dirt : public Actor { // it's just dirt. Lmao
public:
	Dirt(StudentWorld* here, int x, int y);
	~Dirt();

	virtual void doSomething();
	virtual bool isDirt() const;
};

class ActivatingObject : public Actor {
public:
	ActivatingObject(StudentWorld* here, int travdist, int imageID, double startX, double startY, Direction dir, int depth, bool status, bool dmg);
	~ActivatingObject();
	virtual void doSomething() = 0;
	void reduceTravDist(int amount);
	int getTravDist() const;

private:
	int travelDist;
};

class Food : public ActivatingObject {
public:
	Food(StudentWorld*here, int x, int y);
	~Food();
	virtual bool isFood() const;
	virtual void doSomething();
};


class Flame : public ActivatingObject {
public:
	Flame(StudentWorld* here, int x, int y, Direction dir);
	~Flame();
	virtual void doSomething();
};

class DisinfectantSpray : public ActivatingObject {
public:
	DisinfectantSpray(StudentWorld* here, int x, int y, Direction dir);
	~DisinfectantSpray();
	virtual void doSomething();
};

class Goodie : public ActivatingObject {
public:
	Goodie(StudentWorld* here, int life, int imageID, int x, int y, Direction dir, int depth, bool status, bool dmg);
	~Goodie();
	bool lifetimeOver();
	void reduceLifetime(int amount);
	virtual bool isGoodie() const; // all goodies return true
	virtual int goodieType() const; //returns 1 for restore, 2 for flame, 3 for extra, 4 for fungus
	virtual void doSomething() = 0;
private:
	int lifetime;
};

class RestoreHealthGoodie : public Goodie {
public:
	RestoreHealthGoodie(StudentWorld* here, int life, int x, int y);
	~RestoreHealthGoodie();
	virtual int goodieType() const;
	virtual void doSomething(); 
};

class FlamethrowerGoodie : public Goodie {
public:
	FlamethrowerGoodie(StudentWorld* here, int life, int x, int y);
	~FlamethrowerGoodie();
	virtual int goodieType() const;
	virtual void doSomething(); //fix this shit too
};

class ExtraLifeGoodie : public Goodie {
public:
	ExtraLifeGoodie(StudentWorld* here, int life, int x, int y);
	~ExtraLifeGoodie();
	virtual int goodieType() const;
	virtual void doSomething();
};

class Fungus : public Goodie {
public:
	Fungus(StudentWorld* here, int life, int x, int y);
	~Fungus();
	virtual int goodieType() const;
	virtual void doSomething();
};

class Pit : public Actor {
public:
	Pit(StudentWorld* here, double x, double y);
	~Pit();

	virtual void doSomething();
	virtual bool hasInvent() const;
	bool hasEmittedAll();

	void decReg();
	void decAgg();
	void decEColi();

	int getReg() const;
	int getAgg() const;
	int getEColi() const;

private:
	int RegSalCount;
	int AggCount;
	int EColiCount;
};

class Bacterium : public Actor {
public:
	Bacterium(StudentWorld* here, int hp, int movePlan, int imageID, double startX, double startY, Direction dir, int depth, bool stat, bool dmg);
	~Bacterium();
	virtual void doSomething() = 0;


	virtual bool isBacterium() const;
	virtual int typeBact() const; // returns 0 for base class, 1 for RegSal, 2 for AggSal, 3 for EColi
	void setFoodEaten(int value);
	void increaseFood();
	void setMovementPlan(int value);
	void incOrDecmvmt(int value);

	int getFoodEaten() const;
	int getMovementPlan() const;
	virtual void takeDmg(int value); // Bryan plase come back and dont forget to implement the turn into food part


private:
	int movementPlan;
	int foodEaten;
	
};

class RegularSalmonella :public Bacterium {
public:
	RegularSalmonella(StudentWorld* here, int hp, int movePlan, int x, int y);
	~RegularSalmonella();
	virtual int typeBact() const;
	virtual void doSomething();
};

class AggressiveSalmonella :public Bacterium {
public:
	AggressiveSalmonella(StudentWorld* here, int hp, int movePlan, int x, int y);
	~AggressiveSalmonella();
	virtual int typeBact() const;
	virtual void doSomething(); // dont forget
};

class EColi : public Bacterium {
public:
	EColi(StudentWorld* here, int hp, int movePlan, int x, int y);
	~EColi();
	virtual int typeBact() const;
	virtual void doSomething();
};

#endif // ACTOR_H_
