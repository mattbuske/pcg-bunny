/**
 *	File: Bunny.cpp - Bunny Class Implementation
 *	Author: Matt Buske
 *  Creation Date: 02/19/2014
 */

/**
 * Include the Bunny Class Definition
 */
#include "Bunny.h"

/**
 * Set The Defaults
 */
const int PAD_BLOCK_SIZE(3);
const int BLOCK_SIZE(2);
const int BLOCKS(5);

/*
*	Bunny DNA = (pad = 3 blocks (6 bits)). Then: 
*			5th block is Strategy,
*			4th block is Build,
*			3rd block is Mutation,
*			2nd block is Defense,
*			1st block is Ability.
*/

/*


Weak against (2)Ranged and (1)Stealth
Strong against (2)Aggressive and (1)Defensive.


Type 00 - "Stealth" - 4 points
Type 01 - "Aggressive" - 2 points
Type 10 - "Defensive" - 1 points
Type 11 - "Ranged" - 3 points

Highest score = 4 * 5 = 20;
Mid-high score = 3 * 5 = 15;
Mid-Low score = 2 * 5 = 10;
Lowest score = 1 * 5 = 5;
between 5 and 20 for possible fitness scores.
between 16-20 for best case.
between 11-15 for hopeful Monsters
all others die.
*/

const int S(4);
const int B(3);
const int M(2);
const int D(1);
const int A(0); 

const string Bunny::ABILITY[] = { "Poison",
								  "Heat",
								  "Radiation",
								  "Spatial Distortion"};
									
const string Bunny::DEFENSE[] = { "Blends In",
								  "Thick Skin",
								  "Dodge",
								  "Run Away!"};
									   
const string Bunny::STRATEGY[] = { "Stealth",
								   "Aggressive",
								   "Defensive",
								   "Ranged"};
								   
const string Bunny::MUTATION[] = { "Suction Cup Feet",
								   "Large Claws",
								   "Advanced Reflexes",
								   "Massive Telepathic Brain"};
								   
const string Bunny::BUILD[] = { "Small",
								"Muscular",
								"Toned",
								"Fat"};
								
Bunny *Bunny::getRandomBunny(){
	return new Bunny();
}

void Bunny::mutate(){
	dna->mutate();
}

DNA *Bunny::getRandomDNA(){
	DNA *d = new DNA(BLOCK_SIZE, BLOCKS, false);
	return d;
}

Bunny *Bunny::mate(Bunny *theLover){
	unsigned short b1 = dna->getDNA();
	unsigned short b2 = theLover->getDNA()->getDNA();
	return new Bunny(dna->makeDNA( (m1 & b1) | (m2 & b2) ));
}

Bunny *Bunny::copy(){
	return new Bunny(dna);
}

int Bunny::getAbility() const {
	return dna->getBlock(A);
}

int Bunny::getDefense() const {
	return dna->getBlock(D);
}

int Bunny::getMutation() const {
	return dna->getBlock(M);
}

int Bunny::getBuild() const {
	return dna->getBlock(B);
}

int Bunny::getStrategy() const {
	return dna->getBlock(S);
}

void Bunny::print(){
	cout << "Bunny: - Fitness Score: " << fitness << endl;
	cout << "Ability - " << ABILITY[getAbility()] << endl;
	cout << "Defense - " << DEFENSE[getDefense()] << endl;
	cout << "Mutation - " << MUTATION[getMutation()] << endl;
	cout << "Strategy - " << STRATEGY[getStrategy()] << endl;
	cout << "Build - " << BUILD[getBuild()] << endl << endl;
	//dna->print();
	
}