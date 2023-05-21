package pcgbunny;

import java.util.ArrayList;
import java.util.Random;

/**
 *
 * @author
 */
public class PCGBunny {

    private static final int BLOCK_SIZE = 2;
    private static final int BLOCKS = 5;

    private static int generation = 0;

    private static final int genSize = 50;
    private static final int numGens = 50;

    private static final DNA playerDNA = new DNA(2, 4, true);

    private static ArrayList<Bunny> bunnies = new ArrayList<Bunny>();
    private static ArrayList<Bunny> dead = new ArrayList<Bunny>();
    private static ArrayList<Bunny> survived = new ArrayList<Bunny>();
    private static ArrayList<Bunny> newborns = new ArrayList<Bunny>();

    public static final Random R = new Random(System.nanoTime());

    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) {
        Random r = new Random(System.nanoTime());
        playerDNA.setDNA(0xd2);
        generateInitialPopulation();
        generation = 1;
        runFitness();
        run();
    }

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
    private static void clear() {
        bunnies.clear();
        dead.clear();
        survived.clear();
        newborns.clear();
    }

    private static void mutate(Bunny b) {
        int r = (R.nextInt() % 100) + 1;
        if (r > 25) {
            return;
        }
        b.mutate();
    }

    private static int convertFitnessScore(int score) {
        switch (score) {
            case 0:
                return playerDNA.getBlock(3) + 1;
            case 1:
                return playerDNA.getBlock(2) + 1;
            case 2:
                return playerDNA.getBlock(1) + 1;
            default:
                return playerDNA.getBlock(0) + 1;
        }
    }

    private static void fitness(Bunny b) {
        //highest fitness - all stealth.
        //Lowest fitness - defensive.
        int totalScore = 0;
        totalScore += convertFitnessScore(b.getDefense());
        totalScore += convertFitnessScore(b.getBuild());
        totalScore += convertFitnessScore(b.getMutation());
        totalScore += convertFitnessScore(b.getStrategy());
        totalScore += convertFitnessScore(b.getAbility());
        b.setFitness(totalScore);

    }

    private static boolean canSurvive(Bunny b) {
        return b.getFitness() > 11;
    }

    private static boolean isHopefulMonster(int score) {
        return (score < 18 && score > 11);
    }

    private static ArrayList<Bunny> generateInitialPopulation() {
        for (int i = 0; i < genSize; i++) {
            Bunny b = Bunny.getRandomBunny();
            mutate(b);
            bunnies.add(b);
        }
        return bunnies;
    }

    private static void runFitness() {
        int deadCount = 0;
        int surviveCount = 0;
        int hopefullMonsterCount = 0;
        int bestCount = 0;
        for (Bunny b : bunnies) {
            fitness(b);
            //b.print();
            if (!canSurvive(b)) {
                dead.add(b);
                deadCount++;
            } else {
                survived.add(b);
                surviveCount++;
                if (isHopefulMonster(b.getFitness())) {
                    hopefullMonsterCount++;
                } else {
                    bestCount++;
                    Bunny t = b.copy();
                    mutate(t);
                    newborns.add(t);
                }
            }
        }
        System.out.println("Generation " + generation + " summary:");
        System.out.println(deadCount + " Bunnies Died");
        System.out.println(surviveCount + " Bunnies survived.");
        System.out.println("Of those that survived: ");
        System.out.println(hopefullMonsterCount + " were hopeful Monsters.");
        System.out.println(bestCount + " were the Best of the Best.");
        System.out.println();
        bunnies.clear();
        dead.clear();
    }

    private static void forcedMating() {
        Bunny mate1;
        Bunny mate2;
        boolean down = false;
        int count = newborns.size();
        int size = survived.size();
        mate1 = survived.get(0);
        int i = 1;
        while (count < genSize) {
            if (i < 0 || i >= size) {
                break;
            }
            mate2 = survived.get(i);
            newborns.add(mate1.mate(mate2));
            count++;
            mate1 = mate2;
            if (i == (size - 1)) {
                down = true;
            }
            if (i == 0) {
                down = false;
            }
            if (down) {
                i--;
            } else {
                i++;
            }
        }
        survived.clear();
        generation++;

    }

    private static void matureBunnies() {
        newborns.forEach((b) -> {
            bunnies.add(b);
        });
	    newborns.clear();
    }

    private static void mutateAll() {
        bunnies.forEach((b) -> {
            mutate(b);
        });
    }

    private static void run() {

        while (generation < numGens){
            forcedMating();
            matureBunnies();
            mutateAll();
            runFitness();
	}
	//for (Bunny b : survived){
            //b.print();
	//}
    }
}
