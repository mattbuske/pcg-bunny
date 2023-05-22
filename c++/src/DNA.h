/**
 *	File: DNA.h - DNA Class Definition
 *	Author: Matt Buske
 *  Creation Date: 02/20/2014
 */
#ifndef DNA_H
#define DNA_H

// Includes
#include <cstdlib>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <iostream>
#include <vector>
#include <cmath>
#include <bitset>

/**
 * Use Standard Namespace
 */
using namespace std;

/**
 * @class DNA
 * @brief The DNA class represents a string of DNA that consists of blocks of bits. The blocks have a defined size, and the number of blocks can be specified when creating an instance of this class.
 */
class DNA {
public:
	/**
	 * @brief Public Constructor
	 * 
	 * @param blockSize the size of each block of DNA
	 * @param numberBlocks the number of blocks in the DNA string
	 * @param isBlank determines whether the DNA string should be initialized with random data or as an empty string
	 */
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
	/**
	 * @brief Public Destructor
	 */
	~DNA(){};
	
	/**
	* @brief Getter for the DNA string
	* 
	* @return the DNA string as an unsigned short value
	*/
	unsigned short getDNA() const { return dna; }
	/**
	* @brief Setter for the DNA string
	* 
	* @param d the new DNA string value to set
	*/
	void setDNA(unsigned short d) { dna = d; }
	/**
	* @brief Gets the data of a block of DNA by its number
	* 
	* @param bNumber the number of the block to get
	* @return the data of the specified block as an unsigned short value
	*/
	unsigned short getBlock(int bNumber);
	/**
	* @brief Sets the data of a block of DNA by its number
	* 
	* @param bNumber the number of the block to set
	* @param num the new data value for the specified block
	*/
	void setBlockNumber(int bNumber, int num);
	/**
	* @brief Mutates the DNA string by randomly changing the value of one of its blocks
	*/
	void mutate();
	/**
	* @brief Prints the DNA string
	*/
	void print();
	/**
	* @brief Creates a copy of the current DNA object
	*
	* @return a pointer to a new DNA object that is a copy of the current object
	*/
	DNA *copy();
	/**
	* @brief Creates a new DNA object with a specified DNA string value
	* 
	* @param d the DNA string value to use for the new DNA object
	* @return a pointer to the new DNA object
	*/
	DNA *makeDNA(unsigned short d);
	
private:
	/**
	 * @brief Private Constructor
	 * 
	 * @param d the DNA value as an unsigned short
	 * @param blockSize the size of each block
	 * @param numberBlocks the number of blocks
	 */
	DNA(unsigned short d, int blockSize, int numberBlocks){
		dna = d;
		bSize = blockSize;
		numBlocks = numberBlocks;
		bit = pow(2, blockSize) - 1;
		padBlockSize = (DNASIZE/blockSize) - numberBlocks;
		largestNum = pow(2, numBlocks * bSize) - 1;
		
	};
	/**
     * @brief The DNA value
     */
	unsigned short dna;
	/**
     * @brief The number of blocks
     */
	int numBlocks;
	/**
     * @brief The size of each block
     */
	int bSize;
	/**
     * @brief The number of padded blocks
     */
	int padBlockSize;
	/**
     * @brief The largest number representable by `numBlocks` blocks of size `bSize`
     */
	int largestNum;
	/**
     * @brief The bit representation of a block of size `bSize`
     */
	unsigned short bit;

	/**
     * @brief The size of the DNA value
     */
	const static int DNASIZE = 16;

	/**
     * @brief Generates a random DNA value as an unsigned short
     * 
     * @return The random DNA value as an unsigned short
     */
	unsigned short getRandomDNA();
};

#endif