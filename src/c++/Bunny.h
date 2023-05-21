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
 * @class Bunny
 * @brief A class that represents a bunny
 */
class Bunny {
public:
 	/**
   	 * @brief Public destructor for the Bunny class
   	 */
	~Bunny(){ delete dna; };

	/**
     * @brief Getter for the DNA of the bunny
	 *
     * @return The DNA of the bunny
     */
	DNA *getDNA() const { return dna; }

	/**
     * @brief Getter for the fitness of the bunny
	 *
     * @return The fitness of the bunny
     */
	int getFitness() const { return fitness; }

	/**
     * @brief Setter for the fitness of the bunny
	 *
     * @param fit The new fitness of the bunny
     */
	void setFitness(int fit) { fitness = fit; }
	
	/**
     * @brief Mate two bunnies to produce a new bunny
     *
	 * @param theLover The bunny to mate with
     * @return The resulting bunny from mating
     */
	Bunny *mate(Bunny *theLover);
	
	/**
     * @brief Get a random bunny
     *
     * @return A randomly generated bunny
     */
	static Bunny *getRandomBunny();
	
	/**
     * @brief Get the defense ability of the bunny
     *
     * @return The defense ability of the bunny
     */
	int getDefense() const;

   /**
     * @brief Get the strategy ability of the bunny
	 *
     * @return The strategy ability of the bunny
     */
	int getStrategy() const;

    /**
     * @brief Get the build ability of the bunny
	 *
     * @return The build ability of the bunny
     */
	int getBuild() const;

    /**
     * @brief Get the mutation ability of the bunny
	 *
     * @return The mutation ability of the bunny
     */
	int getMutation() const;

    /**
     * @brief Get the ability of the bunny
	 *
     * @return The ability of the bunny
     */
	int getAbility() const;

    /**
     * @brief Mutate the bunny
     */
	void mutate();

  	/**
   	 * @brief Print the bunny's information
   	 */
	void print();

	/**
     * @brief Copy the bunny
	 *
     * @return A copy of the bunny
     */
	Bunny *copy();

private:
	/**
     * @brief Private constructor for the Bunny class
     */
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