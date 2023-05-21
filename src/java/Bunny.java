package pcgbunny;

/**
 *
 * @author matt
 */
public class Bunny {

    private static final String ABILITY[] = {
        "Poison",
        "Heat",
        "Radiation",
        "Spacial Distortion"
    };

    private static final String DEFENSE[] = {
        "Blends In",
        "Thick Skin",
        "Dodge",
        "Run Away!"
    };

    private static final String STRATEGY[] = {
        "Stealth",
        "Aggressive",
        "Defensive",
        "Ranged"
    };

    private static final String MUTATION[] = {
        "Suction Cup Feet",
        "Large Claws",
        "Advanced Reflexes",
        "Massive Telepathic Brain"
    };

    private static final String BUILD[] = {
        "Small",
        "Muscular",
        "Toned",
        "Fat"
    };
    
    private static final int PAD_BLOCK_SIZE = 3;
    private static final int BLOCK_SIZE = 2;
    private static final int BLOCKS = 5;
    
    private static final int S = 4;
    private static final int B = 3;
    private static final int M = 2;
    private static final int D = 1;
    private static final int A = 0;
    
    
    private static final int M1 = 0x333;
    private static final int M2 = 0xcc;

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
    
    private Bunny(){
        this.dna = getRandomDNA();
    }
    
    private Bunny(DNA d) {
        this.dna = d;
    }
    
    public DNA getDNA() {
        return this.dna;
    }
    
    public int getFitness() {
        return fitness;
    }
    
    public void setFitness(int fitness) {
        this.fitness = fitness;
    }
    
    public Bunny mate(Bunny theLover) {
        int b1 = dna.getDNA();
	int b2 = theLover.getDNA().getDNA();
	return new Bunny(dna.makeDNA((M1 & b1) | (M2 & b2)));
    }
    
    public static Bunny getRandomBunny() {
        return new Bunny();
    }
    
    public int getDefense(){
        return dna.getBlock(D);
    }
    
    public int getStrategy(){
        return dna.getBlock(S);
    }
    
    public int getBuild(){
        return dna.getBlock(B);
    }
    
    public int getMutation(){
        return dna.getBlock(M);
    }
    
    public int getAbility(){
        return dna.getBlock(A);
    }
    
    public void mutate() {
        dna.mutate();
    }
    
    public void print() {
        System.out.println("Bunny: - Fitness Score: " + fitness);
        System.out.println("Ability - " + ABILITY[getAbility()]);
        System.out.println("Defense - " + DEFENSE[getDefense()]);
        System.out.println("Mutation - " + MUTATION[getMutation()]);
        System.out.println("Strategy - " + STRATEGY[getStrategy()]);
        System.out.println("Build - " + BUILD[getBuild()]);
        System.out.println();
    }
    
    public Bunny copy() {
        return new Bunny(this.dna);
    }
    
    private DNA getRandomDNA(){
        return new DNA(BLOCK_SIZE, BLOCKS, false);
    }
    
    private void setDNA(DNA newDNA) {
        this.dna = newDNA;
    }

    
    
    
}
