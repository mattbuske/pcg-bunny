/**
 *	File: main.cpp - Main Source File 
 *	Author: Matt Buske
 *  Creation Date: 02/19/2014
 */

// Includes
#include <cstdlib>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <vector>
#include <stdint.h>
#include <time.h>
#include <bitset>

// Include the DNA Class Definition
#include "DNA.h"
// Include the Bunny Class Definition
#include "Bunny.h"

/**
 * Use Standard Namespace
 */
using namespace std;

/**
*
*  Bunnies!
*
*
* compile: g++ Bunny.cpp DNA.cpp main.cpp -g -o pcg-bunnies
*
**/

/**
 * Current Version
 */
const static string VERSION = "1.2.0";

const static int BLOCK_SIZE = 2;
const static int BLOCKS = 5;

static int generation = 0;

static int genSize = 50;
static int numGens = 50;

static DNA *playerDNA = new DNA(2, 4, true);

static vector<Bunny*> *bunnies = new vector<Bunny*>();
static vector<Bunny*> *dead = new vector<Bunny*>();
static vector<Bunny*> *survived = new vector<Bunny*>();
static vector<Bunny*> *newborns = new vector<Bunny*>();

void killAllDeadBunnies(){
	for (vector<Bunny*>::iterator it = dead->begin(); it != dead->end(); it++){
		Bunny *b = *it;
		if (b != NULL) delete b;
	}
	dead->clear();
}

void killAllSurvivedBunnies(){
	for (vector<Bunny*>::iterator it = survived->begin(); it != survived->end(); it++){
		Bunny *b = *it;
		if (b != NULL) delete b;
	}
	survived->clear();
}

void killAllNewbornBunnies(){
	for (vector<Bunny*>::iterator it = newborns->begin(); it != newborns->end(); it++){
		Bunny *b = *it;
		if (b != NULL) delete b;
	}
	newborns->clear();
}

void killAllBunnies(){
	killAllDeadBunnies();
	killAllSurvivedBunnies();
	killAllNewbornBunnies();
	for (vector<Bunny*>::iterator it = bunnies->begin(); it != bunnies->end(); it++){
		Bunny *b = *it;
		if (b != NULL) delete b;
	}
	bunnies->clear();
}

void cleanUp(){
	killAllBunnies();
	delete dead;
	delete bunnies;
	delete survived;
	delete newborns;
	delete playerDNA;
}

void mutate(Bunny *b) {
	int r = (rand() % 100) + 1;
	if (r > 25) return;
	b->mutate();
}
/*
Highest score = 4 * 5 = 20;
Mid-high score = 3 * 5 = 15;
Mid-Low score = 2 * 5 = 10;
Lowest score = 1 * 5 = 5;
between 5 and 20 for possible fitness scores.
between 18-20 for best case.
between 12-17 for hopeful Monsters
all others die.
*/

int convertFitnessScore(int score){
	if (score == 0) {
		return playerDNA->getBlock(3) + 1;
	} else if (score == 1){
		return playerDNA->getBlock(2) + 1;
	} else if (score == 2){
		return playerDNA->getBlock(1) + 1;
	} else {
		return playerDNA->getBlock(0) + 1;
	}
}

void fitness(Bunny *b){
	//highest fitness - all stealth.
	//Lowest fitness - defensive.
	int totalScore = 0;
	totalScore += convertFitnessScore(b->getDefense());
	totalScore += convertFitnessScore(b->getBuild());
	totalScore += convertFitnessScore(b->getMutation());
	totalScore += convertFitnessScore(b->getStrategy());
	totalScore += convertFitnessScore(b->getAbility());
	b->setFitness(totalScore);
}

bool canSurvive(Bunny *b) {
	if (b->getFitness() <= 11) {
		return false;
	}
	return true;
}

bool isHopefulMonster(int score){
	//cout << "HM SCORE: " << score << endl;
	return (score < 18 && score > 11);
}

vector<Bunny*> *generateInitialPopulation(){
	for (int i = 0; i < genSize; i++){
		Bunny *b = Bunny::getRandomBunny();
		mutate(b);
		bunnies->push_back(b);
	}
	return bunnies;
}

void runFitness() {
	int deadCount = 0; 
	int surviveCount = 0;
	int hopefullMonsterCount = 0; 
	int bestCount = 0;
	for (vector<Bunny*>::iterator it = bunnies->begin(); it != bunnies->end(); it++){
		Bunny *b = *it;
		fitness(b);
		//b->print();
		if (!canSurvive(b)) {
			dead->push_back(b);
			deadCount++;
		} else {
			survived->push_back(b);
			surviveCount++;
			if (isHopefulMonster(b->getFitness())) {
				hopefullMonsterCount++;
			} else {
				bestCount++;
				Bunny *t = b->copy();
				mutate(t);
				newborns->push_back(t);
			}
		}
		
	}
	cout << "Generation " << generation << " summary:" << endl;
	cout << deadCount << " Bunnies Died" << endl;
	cout << surviveCount << " Bunnies survived." << endl;
	cout << "Of those that survived: " << endl;
	cout << hopefullMonsterCount << " were hopeful Monsters." << endl;
	cout << bestCount << " were the Best of the Best." << endl << endl;
	bunnies->clear();
	//killAllDeadBunnies();
	dead->clear();
}

void forcedMating(){
	Bunny *mate1;
	Bunny *mate2;
	bool down = false;
	int count = newborns->size();
	int size = survived->size();
	mate1 = survived->at(0);
	int i = 1;
	while (count < genSize) {
		if(i < 0 || i >= size) break;
		
		mate2 = survived->at(i);
		newborns->push_back(mate1->mate(mate2));
		count++;
		mate1 = mate2;
		
		if (i == (size - 1)) down = true;
		if (i == 0) down = false;
		if (down) {
			i--;
		} else {
			i++;
		}
	}
	//killAllSurvivedBunnies();
	survived->clear();
	generation++;
	
}

void matureBunnies(){
	for (int i = 0; i < newborns->size(); i++){
		bunnies->push_back(newborns->at(i));
	}
	newborns->clear();
}

void mutateAll(){
	for (vector<Bunny*>::iterator it = bunnies->begin(); it != bunnies->end(); it++){
		Bunny *b = *it;
		mutate(b);
	}
}

void run(){
	
	while (generation < numGens){
		forcedMating();
		matureBunnies();
		mutateAll();
		runFitness();
	}
	for (vector<Bunny*>::iterator it = survived->begin(); it != survived->end(); it++){
		Bunny *b = *it;
		//b->print();
	}
}

int main(int argc, char** argv) {
	srand(time(NULL));
	playerDNA->setDNA(0xd2);
	bunnies = generateInitialPopulation();
	generation = 1;
	runFitness();
	run();
	//generation = 1;
	///playerDNA->setDNA(0xe7);
	//run();

	cleanUp();

}