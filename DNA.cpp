#include "dna.h"

unsigned short DNA::getBlock(int bNumber){
	int move = bNumber * bSize;
	unsigned short mask = bit << move;
	return (mask & dna) >> move;
}

unsigned short DNA::getRandomDNA(){
	return rand() % largestNum;
}

void DNA::print(){
	printf("DNA: %x, NumBlocks: %d, Block Size: %d, Pad Size: %d, LargestNum: %d - %x\n", 
				dna, numBlocks, bSize, padBlockSize, largestNum, largestNum);
				cout << "DNA Strand: " << bitset<10>(dna) << endl;
}

void DNA::mutate(){
	int r = ((rand() % 100 + 1) / (numBlocks * bSize));
	unsigned short m = 0x01;
	m <<= r;
	dna |= m;
}

DNA *DNA::copy(){
	return this->makeDNA(dna);
}

void DNA::setBlockNumber(int bNumber, int num){
	int move = bNumber * bSize;
	unsigned short mask = bit << move;
	mask = ~mask & dna;
	unsigned short block = num;
	block <<= move;
	dna = block | mask;
}

DNA *DNA::makeDNA(unsigned short d){
	return new DNA(d, bSize, numBlocks);
}