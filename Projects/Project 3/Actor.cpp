#include "Actor.h"
#include "StudentWorld.h"
#include <utility>

// Students:  Add code to this file, Actor.h, StudentWorld.h, and StudentWorld.cpp

Socrates::Socrates(StudentWorld* here, int posAngle, int x, int y): Actor(here,IID_PLAYER, x, y, 0, 0, true, false, 100) // cant use is damageable for This fucker
{
	sprayCharge = 20;
	flameCharge = 5;
	positionalAngle = 180;
}

Socrates::~Socrates()
{
}

void Socrates::doSomething()
{
	if (getStatus() == false) {
		return;
	}
	double x, y;
	int maxSpray = 20;
	int choice;
	if (getWorld()->getKey(choice)) {
		switch (choice) {
		case KEY_PRESS_LEFT:
			if (positionalAngle > 364) {
				positionalAngle -= 365;
			}
			positionalAngle -= 5;
			x = 128*cos((positionalAngle * (4 * atan(1))/180)) + 128;
			y = 128*sin((positionalAngle * (4 * atan(1))/180)) + 128;
			moveTo(x, y);
			setDirection(positionalAngle + 180);
			break;

		case KEY_PRESS_RIGHT:
			if (positionalAngle > 364) {
				positionalAngle -= 365;
			}
			positionalAngle += 5;
			x = 128*cos((positionalAngle * (4 * atan(1))/180)) + 128;
			y = 128*sin((positionalAngle * (4 * atan(1))/180)) + 128;
			moveTo(x, y);
			setDirection(positionalAngle + 180);
			break;
		case KEY_PRESS_ENTER:
			if (getFlame() > 0) {
				Direction socDir = getDirection();
				for (int i = 0; i < 16; i++) {
					Flame* addFlame;
					x = SPRITE_WIDTH * cos(socDir * (4 * atan(1)) / 180);
					y = SPRITE_WIDTH * sin(socDir * (4 * atan(1)) / 180);
					addFlame = new Flame(this->getWorld(), getX() + x, getY() + y, socDir);
					getWorld()->pushback4me(addFlame);
					socDir += 22;
				}
				incOrDecFlame(-1);
				getWorld()->playSound(SOUND_PLAYER_FIRE);
				break;
			}
			break;
		case KEY_PRESS_SPACE:
			if (getSpray() > 0) {
				DisinfectantSpray* addSpray;
				x = SPRITE_WIDTH * cos(getDirection() * (4 * atan(1)) / 180);
				y = SPRITE_WIDTH * sin(getDirection() * (4 * atan(1)) / 180);
				addSpray = new DisinfectantSpray(this->getWorld(), getX() + x, getY() + y, getDirection());
				getWorld()->pushback4me(addSpray);
				hasSprayed = true;
				incOrDecSpray(-1);
				getWorld()->playSound(SOUND_PLAYER_SPRAY);
				break;
			}
			break;
		}
		

	}
	else {
		if(!(hasSprayed) && getSpray() < 20)
			incOrDecSpray(1);
		hasSprayed = false;
	}
}

bool Socrates::isSocrates() const
{
	return true;
}

void Socrates::incOrDecFlame(int amount)
{
	flameCharge += amount;
}

void Socrates::incOrDecSpray(int amount)
{
	sprayCharge += amount;
}

int Socrates::getFlame() const
{
	return flameCharge;
}

int Socrates::getSpray() const
{
	return sprayCharge;
}

Actor::Actor(StudentWorld* here, int imageID, double startX, double startY, Direction dir, int depth, bool stat, bool dmg, int hp) : GraphObject(imageID,startX,startY,dir,depth)
{
	hitpoints = hp;
	currWorld = here;
	status = stat;
	isDamageable = dmg;
}

Actor::~Actor()
{
}

void Actor::setHealth(int amount)
{
	hitpoints = amount;
}

void Actor::reduceHp(int amount)
{
	hitpoints -= amount;
	if (hitpoints <= 0) {
		isNowDead();
	}
}

int Actor::getHp() const
{
	return hitpoints;
}

void Actor::newCoords(int dist, Direction dir)
{
	double addX = dist * cos(dir * (4 * atan(1) / 180));
	double addY = dist * sin(dir * (4 * atan(1) / 180));
	moveTo(getX()+addX, getY()+addY);
}



int Actor::goodieType() const
{
	return 0;
}

int Actor::typeBact() const
{
	return 0;
}

bool Actor::hasInvent() const
{
	return false;
}

bool Actor::isDirt() const
{
	return false;
}

bool Actor::isBacterium() const
{
	return false;
}

bool Actor::isSocrates() const
{
	return false;
}

bool Actor::isGoodie() const
{
	return false;
}

bool Actor::isFood() const
{
	return false;
}

void Actor::takeDmg(int value)
{
	reduceHp(value);
}

bool Actor::getStatus() const
{
	return status;
}

void Actor::isNowDead()
{
	status = false;
}

bool Actor::damageable() const
{
	return isDamageable;
}

bool Actor::hasHitPoints() const
{
	return false;
}

StudentWorld* Actor::getWorld()
{
	return currWorld;
}

Dirt::Dirt(StudentWorld* here, int x, int y) : Actor(here, IID_DIRT,x, y, 0, 1, true, true, 1)
{
}

Dirt::~Dirt()
{
}

void Dirt::doSomething()
{
	return;
}

bool Dirt::isDirt() const
{
	return true;
}


ActivatingObject::ActivatingObject(StudentWorld* here, int travdist, int imageID, double startX, double startY, Direction dir, int depth, bool status, bool dmg) : Actor(here, imageID, startX, startY, dir, depth, status, dmg, 1)
{
	travelDist = travdist;
}

ActivatingObject::~ActivatingObject()
{
}



void ActivatingObject::reduceTravDist(int amount)
{
	travelDist -= amount;
}

int ActivatingObject::getTravDist() const
{
	return travelDist;
}

Food::Food(StudentWorld* here, int x, int y): ActivatingObject(here, 0, IID_FOOD, x, y, 90, 1, true, false)
{

}

Food::~Food()
{
}

bool Food::isFood() const
{
	return true;
}

void Food::doSomething()
{
	return;
}

Flame::Flame(StudentWorld* here, int x, int y, Direction dir) : ActivatingObject(here, 32, IID_FLAME, x, y, dir, 1, true, false)
{
}

Flame::~Flame()
{
}

void Flame::doSomething()
{
	if (getStatus() != true) {
		return;
	}
	
	if (getWorld()->damagedOrNot(this, 5) == true) {
		isNowDead();
		return;
	}

	if (getTravDist() > 0) {
		newCoords(SPRITE_WIDTH, getDirection());
		reduceTravDist(SPRITE_WIDTH);
	}
	if (getTravDist() <= 0) {
		isNowDead();
	}

}

DisinfectantSpray::DisinfectantSpray(StudentWorld* here, int x, int y, Direction dir) : ActivatingObject(here, 112, IID_SPRAY, x, y, dir, 1, true, false)
{
}

DisinfectantSpray::~DisinfectantSpray()
{
}

void DisinfectantSpray::doSomething()
{
	if (getStatus() != true) {
		return;
	}
	if (getWorld()->damagedOrNot(this, 2) == true) {
		isNowDead();
		return;
	}
	if (getTravDist() > 0) {
		newCoords(SPRITE_WIDTH, getDirection());
		reduceTravDist(SPRITE_WIDTH);
	}
	if (getTravDist() <= 0) {
		isNowDead();
	}
	
}

Goodie::Goodie(StudentWorld* here, int life, int imageID, int x, int y, Direction dir, int depth, bool status, bool dmg) : ActivatingObject(here, 0, imageID, x ,y, dir, depth, status, dmg)
{
	lifetime = life;
}

Goodie::~Goodie()
{
}

bool Goodie::lifetimeOver()
{
	if (lifetime <= 0) {
		isNowDead();
		return true;
	}
	return false;
}

void Goodie::reduceLifetime(int amount)
{
	lifetime -= amount;
}

bool Goodie::isGoodie() const
{
	return true;
}

int Goodie::goodieType() const
{
	return 0;
}

RestoreHealthGoodie::RestoreHealthGoodie(StudentWorld* here, int life, int x, int y) : Goodie(here, life, IID_RESTORE_HEALTH_GOODIE, x, y, 0, 1, true, true)
{
}

RestoreHealthGoodie::~RestoreHealthGoodie()
{
}

int RestoreHealthGoodie::goodieType() const
{
	return 1;
}

void RestoreHealthGoodie::doSomething()
{
	if (getStatus() != true) {
		return;
	}
	if (lifetimeOver() == false) { 
		
		if (getWorld()->goodiePickup(this) == true) {
			
			getWorld()->playSound(SOUND_GOT_GOODIE);
			isNowDead();
			return;
		}
		reduceLifetime(1);
	}
	
}

FlamethrowerGoodie::FlamethrowerGoodie(StudentWorld* here, int life, int x, int y): Goodie(here, life, IID_FLAME_THROWER_GOODIE, x ,y, 0, 1, true, true)
{
}

FlamethrowerGoodie::~FlamethrowerGoodie()
{
}

int FlamethrowerGoodie::goodieType() const
{
	return 2;
}

void FlamethrowerGoodie::doSomething()
{
	if (getStatus() != true) {
		return;
	}
	if (lifetimeOver() == false) {

		if (getWorld()->goodiePickup(this) == true) {

			getWorld()->playSound(SOUND_GOT_GOODIE);
			isNowDead();
			return;
		}
		reduceLifetime(1);
	}

}

ExtraLifeGoodie::ExtraLifeGoodie(StudentWorld* here, int life, int x, int y) : Goodie(here, life, IID_EXTRA_LIFE_GOODIE, x, y, 0, 1, true, true)
{
}

ExtraLifeGoodie::~ExtraLifeGoodie()
{
}

int ExtraLifeGoodie::goodieType() const
{
	return 3;
}

void ExtraLifeGoodie::doSomething()
{
	if (getStatus() != true) {
		return;
	}
	if (lifetimeOver() == false) {

		if (getWorld()->goodiePickup(this) == true) {

			getWorld()->playSound(SOUND_GOT_GOODIE);
			isNowDead();
			return;
		}
		reduceLifetime(1);
	}

}

Fungus::Fungus(StudentWorld* here, int life, int x, int y): Goodie(here, life, IID_FUNGUS, x, y, 0, 1, true, true)
{
}

Fungus::~Fungus()
{
}

int Fungus::goodieType() const
{
	return 4;
}

void Fungus::doSomething()
{
	if (getStatus() != true) {
		return;
	}
	if (lifetimeOver() == false) {

		if (getWorld()->goodiePickup(this) == true) {
			isNowDead();
			return;
		}
		reduceLifetime(1);
	}

}


Bacterium::Bacterium(StudentWorld* here, int hp, int movePlan, int imageID, double startX, double startY, Direction dir, int depth, bool stat, bool dmg) : Actor(here, imageID, startX, startY, dir, depth, stat, dmg, hp)
{
	
	movementPlan = movePlan;
	foodEaten = 0;
}

Bacterium::~Bacterium()
{
}

bool Bacterium::isBacterium() const
{
	return true;
}

int Bacterium::typeBact() const
{
	return 0;
}

void Bacterium::setFoodEaten(int value)
{
	foodEaten = value;
}

void Bacterium::increaseFood()
{
	foodEaten += 1;
}

void Bacterium::setMovementPlan(int value)
{
	movementPlan = value;
}

void Bacterium::incOrDecmvmt(int value)
{
	movementPlan += value;
}

int Bacterium::getFoodEaten() const
{
	return foodEaten;
}

int Bacterium::getMovementPlan() const
{
	return movementPlan;
}

void Bacterium::takeDmg(int value)
{
	reduceHp(value);
	if (getHp() <= 0) {
		int rand = randInt(0,1);
		if (rand == 0) {
			Food* addFood;
			addFood = new Food(getWorld(), this->getX(), this->getY());
			getWorld()->pushback4me(addFood);
		}
		isNowDead();
		getWorld()->decBact();
		getWorld()->increaseScore(100);
	}
}

RegularSalmonella::RegularSalmonella(StudentWorld* here, int hp, int movePlan, int x, int y): Bacterium(here, hp, movePlan, IID_SALMONELLA, x, y, 90, 0, true, true)
{
}

RegularSalmonella::~RegularSalmonella()
{
}

int RegularSalmonella::typeBact() const
{
	return 1;
}

void RegularSalmonella::doSomething()
{

	if (getStatus() != true) {
		return;
	}
	if (getWorld()->bacteriumOverlap(this, 1) == true) {
		if (getMovementPlan() > 0) {
			incOrDecmvmt(-3);
			if (getWorld()->bacteriumCanMove(this) == false) {
				int rand = randInt(0, 359);
				Direction newDir = rand;
				setDirection(newDir);
				setMovementPlan(10);
				return;
			}
		}

	}
	if (getFoodEaten() == 3) {
		double newx, newy;
		if (getX() > (VIEW_WIDTH / 2)) {
			newx = getX() - (SPRITE_WIDTH / 2);
		}
		if (getX() < VIEW_WIDTH / 2) {
			newx = getX() + (SPRITE_WIDTH / 2);
		}
		else {
			newx = getX();
		}
		if (getY() > (VIEW_HEIGHT / 2)) {
			newy = getY() - (SPRITE_WIDTH / 2);
		}
		if (getY() < VIEW_HEIGHT / 2) {
			newy = getY() + (SPRITE_WIDTH / 2);
		}
		else {
			newy = getY();
		}
		RegularSalmonella* addRS;
		addRS = new RegularSalmonella(getWorld(), 4, 0, newx, newy);
		getWorld()->pushback4me(addRS);
		getWorld()->incBact();
		setFoodEaten(0);

		if (getMovementPlan() > 0) {
			incOrDecmvmt(-3);
			if (getWorld()->bacteriumCanMove(this) == false) {
				int rand = randInt(0, 359);
				Direction newDir = rand;
				setDirection(newDir);
				setMovementPlan(10);
				return;
			}
		}
	}

	if (getWorld()->bacteriumFoodOverlap(this) == true) {
		increaseFood();
	}

	if (getMovementPlan() > 0) {
		incOrDecmvmt(-3);
		if (getWorld()->bacteriumCanMove(this) == false) {
			int rand = randInt(0, 359);
			Direction newDir = rand;
			setDirection(newDir);
			setMovementPlan(10);
			return;
		}

	}

	Direction closest;
	
	if (getWorld()->findClosestBact(this, closest) == true) {
		if (getWorld()->bacteriumCanMove(this) == false) {
			Direction randDir;
			randDir = randInt(0, 359);
			setDirection(randDir);
			setMovementPlan(10);
			return;
		}
		else {
			return;
		}

	}
	if (getWorld()->bacteriumCanMove(this) == false) {
		Direction randDir;
		randDir = randInt(0, 359);
		setDirection(randDir);
		setMovementPlan(10);
		return;
	}
	else {
		
		return;
	}
	

}

Pit::Pit(StudentWorld* here, double x, double y) : Actor(here, IID_PIT ,x, y, 0, 1, true, false, 1)
{
	RegSalCount = 5;
	AggCount = 3;
	EColiCount = 2;
}

Pit::~Pit()
{
}

void Pit::doSomething()
{
	if (hasEmittedAll() == true) {
		isNowDead();
		getWorld()->decPit();
	}
	else {
		int bactChoice = randInt(1, 50);
		if (bactChoice == 1) {
			int bactleft = 0;
			if (RegSalCount > 0) {
				bactleft++;
			}
			if (AggCount > 0) {
				bactleft++;
			}
			if (EColiCount > 0) {
				bactleft++;
			}
			int randChoice = randInt(1, bactleft);
			switch (randChoice) {
			case 1:
				if (getReg() > 0) {
					RegularSalmonella* addReg;
					addReg = new RegularSalmonella(getWorld(), 4, 0, getX(), getY());
					getWorld()->pushback4me(addReg);
					getWorld()->playSound(SOUND_BACTERIUM_BORN);
					getWorld()->incBact();
					decReg();
					break;
				}
			case 2:
				if (getAgg() > 0) {
					AggressiveSalmonella* addReg;
					addReg = new AggressiveSalmonella(getWorld(), 10, 0, getX(), getY());
					getWorld()->pushback4me(addReg);
					getWorld()->playSound(SOUND_BACTERIUM_BORN);
					getWorld()->incBact();
					decAgg();
					break;
				}

			case 3:
				if (getEColi() > 0) {
					EColi* addReg;
					addReg = new EColi(getWorld(), 5, 0, getX(), getY());
					getWorld()->pushback4me(addReg);
					getWorld()->playSound(SOUND_BACTERIUM_BORN);
					getWorld()->incBact();
					decEColi();
					break;
				}
			default:
				break;
			}
		}
		
	}

}

bool Pit::hasInvent() const
{
	return true;
}

bool Pit::hasEmittedAll()
{
	if (getReg() == 0 && getAgg() == 0 && getEColi() == 0) {
		return true;
	}
	return false;
}

void Pit::decReg()
{
	RegSalCount--;
}

void Pit::decAgg()
{
	AggCount--;
}

void Pit::decEColi()
{
	EColiCount--;
}

int Pit::getReg() const
{
	return RegSalCount;
}

int Pit::getAgg() const
{
	return AggCount;
}

int Pit::getEColi() const
{
	return EColiCount;
}

EColi::EColi(StudentWorld* here, int hp, int movePlan, int x, int y) : Bacterium(here, hp, movePlan, IID_ECOLI, x, y, 90, 0, true, true)
{
}

EColi::~EColi()
{
}

int EColi::typeBact() const
{
	return 3;
}

void EColi::doSomething()
{
	if (getStatus() != true) {
		return;
	}
	const double PI = 4 * atan(1);
	if (getWorld()->bacteriumOverlap(this, 4) == true) {
		double x1, y1, socx, socy;
		x1 = getX();
		y1 = getY();
		getWorld()->socratesCoords(socx,socy);
		double distance = sqrt(pow(x1-socx, 2) + pow(y1-socy,2));
		if (distance <= 256) {
			Direction newDir = atan2(y1-socy, x1-socx) * (180.00 /( 4 * atan(1)));
			double xmove, ymove;
			for (int i = 0; i < 10; i++) {
				xmove = getX() + 2*cos(newDir * (4 * atan(1) / 180.00));
				ymove = getY() + 2*sin(newDir * (4 * atan(1) / 180.00));
				if (getWorld()->EColiMove(this, xmove, ymove) == true) {
					setDirection(newDir);
					moveTo(xmove, ymove);
					return;
				}
				newDir += 10;
			}
		}
	}
	if (getFoodEaten() == 3) {
		double newx, newy;
		if (getX() > (VIEW_WIDTH / 2)) {
			newx = getX() - (SPRITE_WIDTH / 2);
		}
		else {
			newx = getX() + (SPRITE_WIDTH / 2);
		}
		if (getY() > (VIEW_HEIGHT / 2)) {
			newy = getY() - (SPRITE_WIDTH / 2);
		}
		else {
			newy = getY() + (SPRITE_WIDTH / 2);
		}
		EColi* addEColi;
		addEColi = new EColi(getWorld(), 5, 0, newx, newy);
		getWorld()->pushback4me(addEColi);
		getWorld()->incBact();
		setFoodEaten(0);
	}
	double x1, y1, socx, socy;
	x1 = getX();
	y1 = getY();
	getWorld()->socratesCoords(socx, socy);
	double distance = sqrt(pow(x1 - socx, 2) + pow(y1 - socy, 2));
	if (distance <= 256) {
		Direction newDir = atan2(socy - y1 , socx - x1 ) * (180.00 / (4 * atan(1)));
		double xmove, ymove;
		for (int i = 0; i < 10; i++) {
			xmove = getX() + 2 * cos(newDir * (4 * atan(1) / 180.00));
			ymove = getY() + 2 * sin(newDir * (4 * atan(1) / 180.00));
			if (getWorld()->EColiMove(this, xmove, ymove) == true) {
				
				moveTo(xmove, ymove);
				return;
			}
			newDir += 10;
		}
	}
	if (getWorld()->bacteriumFoodOverlap(this) == true) {
		increaseFood();
	}

}

AggressiveSalmonella::AggressiveSalmonella(StudentWorld* here, int hp, int movePlan, int x, int y) : Bacterium(here, hp , movePlan, IID_SALMONELLA, x, y, 90, 0, true, true)
{
}

AggressiveSalmonella::~AggressiveSalmonella()
{
}

int AggressiveSalmonella::typeBact() const
{
	return 2;
}

void AggressiveSalmonella::doSomething()
{
	if (getStatus() != true) {
		return;
	}
	double x1, y1, socx, socy;
	x1 = getX();
	y1 = getY();
	getWorld()->socratesCoords(socx, socy);
	double distance = sqrt(pow(x1 - socx, 2) + pow(y1 - socy, 2));
	if (distance <= 72) {
		Direction newDir;
		newDir = atan2(socy - y1, socx - x1) * (180 / (4 * atan(1)));
		setDirection(newDir);
		if (getWorld()->bacteriumCanMove(this) == false) {
			if (getWorld()->bacteriumOverlap(this, 2) == true) {
				return;
			}
			if (getFoodEaten() > 3) {
				double newx, newy;
				if (getX() > VIEW_WIDTH / 2) {
					newx = getX() - SPRITE_WIDTH / 2;
				}
				if (getX() < VIEW_WIDTH / 2) {
					newx = getX() + SPRITE_WIDTH / 2;
				}
				else {
					newx = getX();
				}
				if (getY() > VIEW_HEIGHT / 2) {
					newy = getY() - SPRITE_WIDTH / 2;
				}
				if (getY() < VIEW_HEIGHT / 2) {
					newy = getY() + SPRITE_WIDTH / 2;
				}
				else {
					newy = getY();
				}
				AggressiveSalmonella* addAgg;
				addAgg = new AggressiveSalmonella(getWorld(), 10, 0, newx, newy);
				getWorld()->pushback4me(addAgg);
				getWorld()->incBact();
				setFoodEaten(0);
				return;
			}
			if (getWorld()->bacteriumFoodOverlap(this) == true) {
				increaseFood();

			}
		}
		if (getMovementPlan() > 0) {
				incOrDecmvmt(-3);
				if (getWorld()->bacteriumCanMove(this) == false) {
						Direction newDir;
						newDir = randInt(0, 359);
						setDirection(newDir);
						setMovementPlan(10);
						return;
				}
				else {
					return;
				}
		}
			
		
	}
	if (getFoodEaten() > 3) {
		double newx, newy;
		if (getX() > VIEW_WIDTH / 2) {
			newx = getX() - SPRITE_WIDTH / 2;
		}
		if (getX() < VIEW_WIDTH / 2) {
			newx = getX() + SPRITE_WIDTH / 2;
		}
		else {
			newx = getX();
		}
		if (getY() > VIEW_HEIGHT / 2) {
			newy = getY() - SPRITE_WIDTH / 2;
		}
		if (getY() < VIEW_HEIGHT / 2) {
			newy = getY() + SPRITE_WIDTH / 2;
		}
		else {
			newy = getY();
		}
		AggressiveSalmonella* addAgg;
		addAgg = new AggressiveSalmonella(getWorld(), 10, 0, newx, newy);
		getWorld()->pushback4me(addAgg);
		getWorld()->incBact();
		setFoodEaten(0);
		return;
	}
	if (getWorld()->bacteriumFoodOverlap(this) == true) {
		increaseFood();

	}
	Direction closest;

	if (getWorld()->findClosestBact(this, closest) == true) {
		if (getWorld()->bacteriumCanMove(this) == false) {
			Direction randDir;
			randDir = randInt(0, 359);
			setDirection(randDir);
			setMovementPlan(10);
			return;
		}
		else {
			return;
		}

	}
	if (getWorld()->bacteriumCanMove(this) == false) {
		Direction randDir;
		randDir = randInt(0, 359);
		setDirection(randDir);
		setMovementPlan(10);
		return;
	}
	else {

		return;
	}


}
