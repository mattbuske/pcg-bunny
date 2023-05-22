using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.ConstrainedExecution;
using System.Text;
using System.Threading.Tasks;

/**
 *
 * @author matt
 */
namespace pcg_bunny {
    public class DNA {
        private int dna;
        private int numBlocks;
        private int bSize;
        private int padBlockSize;
        private int largestNum;
        private int bit;

        private const int DNASIZE = 16;

        public DNA(int blockSize, int numberBlocks, bool isBlank) {
            bSize = blockSize;
            numBlocks = numberBlocks;
            bit = (int)(Math.Pow(2, blockSize) - 1);
            padBlockSize = (DNASIZE / blockSize) - numberBlocks;
            largestNum = (int)(Math.Pow(2, numBlocks * bSize) - 1);
            if (!isBlank) {
                dna = this.GetRandomDNA();
            }
            else {
                dna = 0x0;
            }
        }

        private DNA(int d, int blockSize, int numberBlocks) {
            dna = d;
            bSize = blockSize;
            numBlocks = numberBlocks;
            bit = (int)(Math.Pow(2, blockSize) - 1);
            padBlockSize = (DNASIZE / blockSize) - numberBlocks;
            largestNum = (int)(Math.Pow(2, numBlocks * bSize) - 1);
        }

        public int GetBlock(int bNumber) {
            int move = bNumber * bSize;
            int mask = bit << move;
            return (mask & dna) >> move;
        }

        public void SetBlockNumber(int bNumber, int num) {
            int move = bNumber * bSize;
            int mask = bit << move;
            mask = ~mask & dna;
            int block = num;
            block <<= move;
            dna = block | mask;
        }

        public void Mutate() {
            int nextInt = new Random().Next();
            int r = ((nextInt % 100 + 1) / (numBlocks * bSize));
            int m = 0x01;
            m <<= r;
            dna |= m;
        }

        public int GetDNA() {
            return dna;
        }

        public void SetDNA(int d) {
            this.dna = d;
        }

        public DNA Copy() {
            return this.MakeDNA(dna);
        }

        public DNA MakeDNA(int d) {
            return new DNA(d, bSize, numBlocks);
        }

        public override string ToString() {
            return "DNA: " + dna + ", NumBlocks: "
                + numBlocks + ", Block Size: "
                + bSize + ", Pad Size: "
                + padBlockSize + ", LargestNum: " + largestNum;
        }

        public void Print() {
            Console.WriteLine(this.ToString());
        }

        private short GetRandomDNA() {
            return (short)(new Random().Next(Int16.MaxValue + 1) % this.largestNum);
        }

    }
}
