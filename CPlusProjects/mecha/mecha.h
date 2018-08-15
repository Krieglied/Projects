#pragma once
#include <string>
#include <iostream>
#include <cstdlib>
#include <time.h> 
#include "weapon.h"
// TODO: You will need to inherit your mecha from the class Mecha first... be sure to override the functions if you need to.

// Base Classes
class Mecha {
protected:
	std::string mechaName;
	std::string type;
	int deathBlossomChance;
	int everyoneChance;
	int linkedChance;
	int normalChance;
	bool overloaded;

	int hitPoints;// indicates total health remaining
	int heatSink; // indicates power per turn... this value should never be modified after it's set.
public:
	// Default constructor... subclass should handle construction
	Mecha() {}
	// You will want to either override this function to add weapon and specific stats... or just utilize it as is and create a new method inside your sub mecha
	virtual void display_main_stats() {
		std::cout << "Model: " << mechaName << std::endl;
		std::cout << "Type : " << type << std::endl;
	}
	/*
	Use this method if you want to determine how much damage your mecha takes
	This can be either really simple (just amount of damage enemy mech does to you...
	Or you can go in on this and do damage types and such.
	*/
	virtual int computeDamageReceived(int damagePts) {
		// generic code here

		return 0;
	}
	// Bare minimum... use this to see if your mech is dead yet
	virtual int getHP() {
		return hitPoints;
	}
	virtual void soakHeat(int heatAmount)
	{
		heatSink -= heatAmount;
		if (heatSink < 0)
		{
			std::cout << "Your mech has overheated.  You're out of action for a turn." << std::endl;
			heatSink = 15;
			overloaded = true;
		}
	}
	virtual void fireAllWeapons(float damageBonus, float heatBonus)
	{}
	virtual void releasePayload(Weapon& selected)
	{
		int result = 0;
		srand(time(NULL));
		if ((rand() % 10 + 1) <= normalChance)
		{
			selected.fireWeapon();
			soakHeat(selected.getHeat());
		}
		else if ((rand() % 10 + 1) <= (normalChance + linkedChance))
		{
			//linked weapon fire
		}
		else if ((rand() % 10 + 1) <= (normalChance + linkedChance + everyoneChance))
		{
			std::cout << "Bring Everyone.  Everyone? .... EVERYONE!!!!" << std::endl;
			fireAllWeapons(1, 0.75);
		}
		else
		{
			std::cout << "Initiating..... " << std::endl;
			//sleepfor
			std::cout << "Death Blossom" << std::endl;
			fireAllWeapons(1.5, 2);
		}
	}
};