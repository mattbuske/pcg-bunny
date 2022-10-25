# Project Deep Dive
The project consists of bunny objects, which each contain a dna object representing the bunnies' attributes represented in binary.
 
## Bunny DNA
The binary DNA of a bunny is only 5 blocks (or 10 bits) of 8 total blocks (3 of the 8 being padding) comprising a strand of 16 bits. The dna of a bunny could potentially look like this:
```SHELL
# Binary
00 00 00 10 01 11 01 10
 
# Hexadecimal
0x276
```
## Attribute Types
Each bunny dna block represents a different attribute type (starting right to left):

- Block 1 - Ability
- Block 2 - Defense
- Block 3 - Mutation
- Block 4 - Build
- Block 5 - Strategy
 
As each block is made up of two bits each, there are four possible values, per block: 00, 01, 10, or 11. These possibilities map to an index in a constant array of traits. Each index in this array corresponds to a general trait type:

    0 = Stealth
    1 = Aggressive
    2 = Defensive
    3 = Ranged

## Trait Definitions
The trait definitions are as follows:

1. Ability
    0. Poison (00)
    1. Heat (01)
    2. Radiation (10)
    3. Spatial Distortion (11)

2. Defense
    0. Blends In (00)
    1. Thick Skin (01)
    2. Dodge (10)
    3. Run Away! (11)

3. Mutation
    0. Suction Cup Feet (00)
    1. Large Claws (01)
    2. Advanced Reflexes (10)
    3. Massive Telepathic Brain (11)

4. Build
    0. Small (00)
    1. Muscular (01)
    2. Toned (10)
    3. Fat (11)

5. Strategy
    0. Stealth (00)
    1. Aggressive (01)
    2. Defensive (10)
    3. Ranged (11)
 
Using the above we can determine the attributes of the above DNA strand (ignoring the padding) as follows:

    DNA: 10 01 11 01 10
    Ability (Block 1): 10 = Radiation
    Defense (Block 2): 01 = Thick Skin
    Mutation (Block 3): 11 = Massive Telepathic Brain
    Build (Block 4): 01 = Muscular
    Strategy (Block 5): 10 = Defensive

## Player DNA
The dna of a player is utilized to allow a custom mapping for tuning the fitness score and is only composed of 4 blocks for a strand of 8 bits. The dna of the player currently look like this:
```SHELL
# Binary
11 01 00 10
 
# Hexadecimal
0xd2
```
 
Every player dna block corresponds to the bunny dna attribute types for fitness score conversion per the table:
 
| Player DNA Block Index  | Bunny DNA Block Attribute Index |
| ---                     | ---                             |
| 0                       | 3                               |
| 1                       | 2                               |
| 2                       | 1                               |
| 3                       | 0                               |
 
We decode the player DNA simply by its integer value added by '1':

    DNA: 11 01 00 10
    Block 1: 10 = 2 +1 = 3
    Block 2: 00 = 0 +1 = 1
    Block 3: 01 = 1 +1 = 2
    Block 4: 11 = 3 +1 = 4

This means the attribute index can be converted to an integer value based on the player dna.
 
## Evaluating the Bunny DNA
The fitness score is compared to the strand of player dna- thus presenting the possibility of adaptive evolution of the bunnies. This means if the player DNA changes, the evolution of the bunnies and what constitutes fitness could change as well. How this works is the value of the attribute is converted to the value that is represented in the corresponding player dna. This value is the fitness score of the attribute. For example:
 
Compare Block one (Ability) of Bunny DNA (1001110110) to the Player DNA: (11010010) to get its fitness score.
 
Bunny DNA for Block one is '10' (which points to 'Radiation'), the index value being '2'. Using the table above, we see this corresponds to Player dna block index '1' (or block 2). Player dna Block 2 is '00', or 0. We add '1' to that value (in order to get an integer between 1-4) to get a final value of 1. This is the fitness score for the 'Ability' block of this Bunny's DNA.
 
## Calculating the Total Fitness Score
Depending on the player dna and bunny evaluated, each block of bunny dna would correspond to a fitness score. Then those values would be added together to determine the bunny's total fitness score. The fitness score scale (from 5-20) is as follows:

- Highest score = 4 * 5 = 20
- Mid-high score = 3 * 5 = 15
- Mid-Low score = 2 * 5 = 10
- Lowest score = 1 * 5 = 5
 
## Generation and Evaluation Rules:
1. 'Best of the Best' bunnies reside between 18-20.
2. 'Hopeful Monster' bunnies reside between 12-17.
3. Any bunnies with fitness scores 11 and below die off.
4. If there are not enough bunnies (i.e. too many die off) for a new generation, new ones are generated with random DNA to replenish the gene pool.
5. In every generation, there is a chance for random mutation in the offspring.
 