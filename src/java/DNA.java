package pcgbunny;

import java.util.Random;

/**
 *
 * @author matt
 */
public class DNA {

    private int dna;
    private int numBlocks;
    private int bSize;
    private int padBlockSize;
    private int largestNum;
    private int bit;

    private static final int DNASIZE = 16;

    public DNA(int blockSize, int numberBlocks, boolean isBlank) {
        bSize = blockSize;
        numBlocks = numberBlocks;
        bit = (int) (Math.pow(2, blockSize) - 1);
        padBlockSize = (DNASIZE / blockSize) - numberBlocks;
        largestNum = (int) (Math.pow(2, numBlocks * bSize) - 1);
        if (!isBlank) {
            dna = getRandomDNA();
        } else {
            dna = 0x0;
        }
    }

    private DNA(int d, int blockSize, int numberBlocks) {
        dna = d;
        bSize = blockSize;
        numBlocks = numberBlocks;
        bit = (int) (Math.pow(2, blockSize) - 1);
        padBlockSize = (DNASIZE / blockSize) - numberBlocks;
        largestNum = (int) (Math.pow(2, numBlocks * bSize) - 1);
    }

    public int getDNA() {
        return dna;
    }

    public void setDNA(int d) {
        this.dna = d;
    }

    public int getBlock(int bNumber) {
        int move = bNumber * bSize;
        int mask = bit << move;
        return (mask & dna) >> move;
    }

    public void setBlockNumber(int bNumber, int num) {
        int move = bNumber * bSize;
	int mask = bit << move;
	mask = ~mask & dna;
	int block = num;
	block <<= move;
	dna = block | mask;
    }

    public void mutate() {
        int nextInt = new Random(System.nanoTime()).nextInt();
        int r = ((nextInt % 100 + 1) / (numBlocks * bSize));
        int m = 0x01;
        m <<= r;
        dna |= m;
    }

    public void print() {
        System.out.println("DNA: " + dna + ", NumBlocks: "
                + numBlocks + ", Block Size: "
                + bSize + ", Pad Size: "
                + padBlockSize + ", LargestNum: " + largestNum);
        //System.out.println("DNA Strand: ");
    }

    public DNA copy() {
        return this.makeDNA(dna);
    }

    public DNA makeDNA(int d) {
        return new DNA(d, bSize, numBlocks);
    }

    private short getRandomDNA() {
        return (short) (new Random(System.nanoTime()).nextInt(Short.MAX_VALUE + 1) % this.largestNum);
    }

}
