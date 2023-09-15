using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace pcg_bunny {

    public class Bunny {

        private readonly String[] ABILITY = {
            "Poison",
            "Heat",
            "Radiation",
            "Spacial Distortion"
        };

        private readonly String[] DEFENSE = {
            "Blends In",
            "Thick Skin",
            "Dodge",
            "Run Away!"
        };

        private readonly String[] STRATEGY = {
            "Stealth",
            "Aggressive",
            "Defensive",
            "Ranged"
        };

        private readonly String[] MUTATION = {
            "Suction Cup Feet",
            "Large Claws",
            "Advanced Reflexes",
            "Massive Telepathic Brain"
        };

        private readonly String[] BUILD = {
            "Small",
            "Muscular",
            "Toned",
            "Fat"
        };
    
        private const int PAD_BLOCK_SIZE = 3;
        private const int BLOCK_SIZE = 2;
        private const int BLOCKS = 5;

        private const int S = 4;
        private const int B = 3;
        private const int M = 2;
        private const int D = 1;
        private const int A = 0;


        private const int M1 = 0x333;
        private const int M2 = 0xcc;

        private int fitness;
        private DNA dna;

        /*Bunny DNA = (pad = 3 blocks (6 bits)). Then: 
        *			5th block is Strategy,
        *			4th block is Build,
        *			3rd block is Mutation,
        *			2nd block is Defense,
        *			1st block is Ability.
        */
        /*
            Weak against (2)Ranged and (1)Stealth
            Strong against (2)Aggressive and (1)Defensive.
            Type 00 - "Stealth" - 4 points
            Type 01 - "Aggressive" - 2 points
            Type 10 - "Defensive" - 1 points
            Type 11 - "Ranged" - 3 points
            Highest score = 4 * 5 = 20;
            Mid-high score = 3 * 5 = 15;
            Mid-Low score = 2 * 5 = 10;
            Lowest score = 1 * 5 = 5;
            between 5 and 20 for possible fitness scores.
            between 16-20 for best case.
            between 11-15 for hopeful Monsters
            all others die.
        */

        private Bunny() {
            this.dna = GetRandomDNA();
        }

        private Bunny(DNA d) {
            this.dna = d;
        }

        public DNA GetDNA() {
            return this.dna;
        }

        public int GetFitness() {
            return fitness;
        }

        public void SetFitness(int fitness) {
            this.fitness = fitness;
        }

        public Bunny Mate(Bunny theLover) {
            int b1 = dna.GetDNA();
            int b2 = theLover.GetDNA().GetDNA();
            return new Bunny(dna.MakeDNA((M1 & b1) | (M2 & b2)));
        }

        public static Bunny GetRandomBunny() {
            return new Bunny();
        }

        public int GetDefense() {
            return dna.GetBlock(D);
        }

        public int GetStrategy() {
            return dna.GetBlock(S);
        }

        public int GetBuild() {
            return dna.GetBlock(B);
        }

        public int GetMutation() {
            return dna.GetBlock(M);
        }

        public int GetAbility() {
            return dna.GetBlock(A);
        }

        public void Mutate() {
            dna.Mutate();
        }

        public override string ToString() {
            return "Bunny: - Fitness Score: " + fitness
                    + "Ability - " + ABILITY[GetAbility()]
                    + "Defense - " + DEFENSE[GetDefense()]
                    + "Mutation - " + MUTATION[GetMutation()]
                    + "Strategy - " + STRATEGY[GetStrategy()]
                    + "Build - " + BUILD[GetBuild()];
        }

        public void Print() {
            Console.WriteLine(this.ToString());
        }

        public Bunny Copy() {
            return new Bunny(this.dna);
        }

        private DNA GetRandomDNA() {
            return new DNA(BLOCK_SIZE, BLOCKS, false);
        }

        private void SetDNA(DNA newDNA) {
            this.dna = newDNA;
        }

    }
}
