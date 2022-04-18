/**
 *	File: Bunny.h - Bunny Class Definition
 *	Author: Matt Buske
 *  Creation Date: 02/19/2014
 */

#ifndef BUNNY_H
#define BUNNY_H

// Includes
#include <cstdlib>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <iostream>
#include <vector>

// Include the DNA Class Definition
#include "DNA.h"

/**
 * Bunny Class Definition
 */
class Bunny {
public:
	/**
	 * Bunny Class Public Destructor
	 */
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