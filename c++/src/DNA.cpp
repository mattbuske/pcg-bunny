/**
 *	File: DNA.cpp - DNA Class Implementation
 *	Author: Matt Buske
 *  Creation Date: 02/20/2014
 */

/*
 * Include the DNA Class Definition
 */
#include "DNA.h"

/**
 *	Get a DNA Block via it's Block Number
 *	Returns the portion of dna via it's block number
 */
unsigned short DNA::getBlock(int bNumber){
	int move = bNumber * bSize;
	unsigned short mask = bit << move;
	return (mask & dna) >> move;
}

/*
 *	Get Random DNA Segment
 *	Returns a 'random' internal DNA segment
 */
unsigned short DNA::getRandomDNA(){
	return rand() % largestNum;
}

/*
 *	Print Function
 *	Print the DNA Object information
 */
void DNA::print(){
	printf("DNA: %x, NumBlocks: %d, Block Size: %d, Pad Size: %d, LargestNum: %d - %x\n", 
				dna, numBlocks, bSize, padBlockSize, largestNum, largestNum);
				cout << "DNA Strand: " << bitset<10>(dna) << endl;
}

/*
 *	Mutate the DNA
 *	'Randomly' mutate the DNA strand
 */
void DNA::mutate(){
	int r = ((rand() % 100 + 1) / (numBlocks * bSize));
	unsigned short m = 0x01;
	m <<= r;
	dna |= m;
}

/*
 *	DNA Copy Function.
 *	Returns a Copy of the DNA Object
 */
DNA *DNA::copy(){
	return this->makeDNA(dna);
}

/*
 *	Set Block Number Function
 *	Sets the specific block number to a specific value
 */
void DNA::setBlockNumber(int bNumber, int num){
	int move = bNumber * bSize;
	unsigned short mask = bit << move;
	mask = ~mask & dna;
	unsigned short block = num;
	block <<= move;
	dna = block | mask;
}

/*
 *	New DNA Function
 *	Returns a new DNA object
 */
DNA *DNA::makeDNA(unsigned short d){
	return new DNA(d, bSize, numBlocks);
}