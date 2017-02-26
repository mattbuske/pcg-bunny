#ifndef BUNNY_H
#define BUNNY_H

#include <cstdlib>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <iostream>
#include <vector>

#include "DNA.h"

class Bunny {
public:
	~Bunny(){ delete dna; };

	DNA *getDNA() const { return dna; }
	int getFitness() const { return fitness; }
	void setFitness(int fit) { fitness = fit; }
	
	Bunny *mate(Bunny *theLover);
	
	static Bunny *getRandomBunny();
	
	int getDefense() const;
	int getStrategy() const;
	int getBuild() const;
	int getMutation() const;
	int getAbility() const;
	void mutate();
	void print();
	Bunny *copy();

private:
	Bunny(){
		dna = getRandomDNA();
	};
	Bunny(DNA *d){
		dna = d;
	};
	DNA *dna;
	int fitness;
	
	static const string ABILITY[];
	static const string DEFENSE[];
	static const string STRATEGY[];
	static const string MUTATION[];
	static const string BUILD[];
	static const unsigned short m1 = 0x333;
	static const unsigned short m2 = 0xcc;
	
	
	int getRandomNum();
	DNA *getRandomDNA();
	void setDNA(DNA *newDNA) { dna = newDNA; }
	
};

#endif