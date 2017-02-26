#ifndef DNA_H
#define DNA_H

#include <cstdlib>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <iostream>
#include <vector>
#include <cmath>
#include <bitset>

using namespace std;

class DNA {
public:
	DNA(int blockSize, int numberBlocks, bool isBlank){
		bSize = blockSize;
		numBlocks = numberBlocks;
		bit = pow(2, blockSize) - 1;
		padBlockSize = (DNASIZE/blockSize) - numberBlocks;
		largestNum = pow(2, numBlocks * bSize) - 1;
		if(!isBlank){
			dna = getRandomDNA();
		} else {
			dna = 0x0;
		}
		
	};
	~DNA(){};
	
	unsigned short getDNA() const { return dna; }
	void setDNA(unsigned short d) { dna = d; }
	
	unsigned short getBlock(int bNumber);
	void setBlockNumber(int bNumber, int num);
	void mutate();
	
	void print();
	DNA *copy();
	DNA *makeDNA(unsigned short d);
	
private:
	DNA(unsigned short d, int blockSize, int numberBlocks){
		dna = d;
		bSize = blockSize;
		numBlocks = numberBlocks;
		bit = pow(2, blockSize) - 1;
		padBlockSize = (DNASIZE/blockSize) - numberBlocks;
		largestNum = pow(2, numBlocks * bSize) - 1;
		
	};
	unsigned short dna;
	int numBlocks;
	int bSize;
	int padBlockSize;
	int largestNum;
	unsigned short bit;
	
	const static int DNASIZE = 16;
	unsigned short getRandomDNA();
};

#endif