using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace pcg_bunny {
    public class PCGBunny
    {

        private const int BLOCK_SIZE = 2;
        private const int BLOCKS = 5;

        private static int generation = 0;

        private const int genSize = 50;
        private const int numGens = 50;

        private static DNA playerDNA = new DNA(2, 4, true);

        private static List<Bunny> bunnies = new();
        private static List<Bunny> dead = new();
        private static List<Bunny> survived = new();
        private static List<Bunny> newborns = new();

        private static Random R = new();

        /*
        Highest score = 4 * 5 = 20;
        Mid-high score = 3 * 5 = 15;
        Mid-Low score = 2 * 5 = 10;
        Lowest score = 1 * 5 = 5;
        between 5 and 20 for possible fitness scores.
        between 19-20 for best case.
        between 11-18 for hopeful Monsters
        all others die.
         */

        public PCGBunny() { }

        public void Run(int dna) {
            playerDNA.SetDNA(dna);
            GenerateInitialPopulation();
            generation = 1;
            RunFitness();
            Run();
        }

        private static void Run()
        {
            while (generation < numGens)
            {
                ForcedMating();
                MatureBunnies();
                MutateAll();
                RunFitness();
            }
        }

        private static void Clear()
        {
            bunnies.Clear();
            dead.Clear();
            survived.Clear();
            newborns.Clear();
        }

        private static void Mutate(Bunny b)
        {
            int r = (R.Next() % 100) + 1;
            if (r > 25)
            {
                return;
            }
            b.Mutate();
        }

        private static int ConvertFitnessScore(int score)
        {
            switch (score)
            {
                case 0:
                    return playerDNA.GetBlock(3) + 1;
                case 1:
                    return playerDNA.GetBlock(2) + 1;
                case 2:
                    return playerDNA.GetBlock(1) + 1;
                default:
                    return playerDNA.GetBlock(0) + 1;
            }
        }

        private static void Fitness(Bunny b)
        {
            //highest fitness - all stealth.
            //Lowest fitness - defensive.
            int totalScore = 0;
            totalScore += ConvertFitnessScore(b.GetDefense());
            totalScore += ConvertFitnessScore(b.GetBuild());
            totalScore += ConvertFitnessScore(b.GetMutation());
            totalScore += ConvertFitnessScore(b.GetStrategy());
            totalScore += ConvertFitnessScore(b.GetAbility());
            b.SetFitness(totalScore);

        }

        private static bool CanSurvive(Bunny b)
        {
            return b.GetFitness() > 11;
        }
        
        private static bool IsHopefulMonster(int score)
        {
            return (score < 18 && score > 11);
        }

        private static List<Bunny> GenerateInitialPopulation()
        {
            for (int i = 0; i < genSize; i++)
            {
                Bunny b = Bunny.GetRandomBunny();
                Mutate(b);
                bunnies.Add(b);
            }
            return bunnies;
        }

        private static void RunFitness()
        {
            int deadCount = 0;
            int surviveCount = 0;
            int hopefullMonsterCount = 0;
            int bestCount = 0;
            foreach (Bunny b in bunnies)
            {
                Fitness(b);
                //b.Print();
                if (!CanSurvive(b))
                {
                    dead.Add(b);
                    deadCount++;
                }
                else
                {
                    survived.Add(b);
                    surviveCount++;
                    if (IsHopefulMonster(b.GetFitness()))
                    {
                        hopefullMonsterCount++;
                    }
                    else
                    {
                        bestCount++;
                        Bunny t = b.Copy();
                        Mutate(t);
                        newborns.Add(t);
                    }
                }
            }
            Console.WriteLine("Generation " + generation + " summary:");
            Console.WriteLine(deadCount + " Bunnies Died");
            Console.WriteLine(surviveCount + " Bunnies survived.");
            Console.WriteLine("Of those that survived: ");
            Console.WriteLine(hopefullMonsterCount + " were hopeful Monsters.");
            Console.WriteLine(bestCount + " were the Best of the Best.");
            Console.WriteLine();
            bunnies.Clear();
            dead.Clear();
        }

        private static void ForcedMating()
        {
            Bunny mate1;
            Bunny mate2;
            bool down = false;
            int count = newborns.Count;
            int size = survived.Count;
            mate1 = survived[0];
            int i = 1;
            while (count < genSize)
            {
                if (i < 0 || i >= size)
                {
                    break;
                }
                mate2 = survived[i];
                newborns.Add(mate1.Mate(mate2));
                count++;
                mate1 = mate2;
                if (i == (size - 1))
                {
                    down = true;
                }
                if (i == 0)
                {
                    down = false;
                }
                if (down)
                {
                    i--;
                }
                else
                {
                    i++;
                }
            }
            survived.Clear();
            generation++;

        }

        private static void MatureBunnies()
        {
            foreach (Bunny b in newborns) {
                bunnies.Add(b);
            }
            newborns.Clear();
        }

        private static void MutateAll()
        {
            foreach(Bunny b in bunnies) {
                Mutate(b);
            }
        }

    }
}
