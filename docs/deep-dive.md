# Project Deep Dive
## Overview
This project is a simulation of bunny objects, where each bunny has a unique DNA that represents its attributes in binary form. The binary DNA of a bunny is composed of 5 blocks (10 bits) out of a total of 8 blocks (3 of which are padding) in a strand of 16 bits. The DNA of a bunny can be represented in hexadecimal notation as well. For example the dna of a bunny could potentially look like this:
```SHELL
# Binary
00 00 00 10 01 11 01 10
 
# Hexadecimal
0x276
```
 
## Bunny DNA
Each block of a bunny's DNA represents a different attribute type, as follows (reading from right to left):

- Ability
- Defense
- Mutation
- Build
- Strategy
 
Each block is composed of two bits, resulting in four possible values: 00, 01, 10, or 11. These values correspond to an index in a constant array of traits. Each index in this array represents a general trait type:

- 0 = Stealth
- 1 = Aggressive
- 2 = Defensive
- 3 = Ranged

The specific trait definitions are as follows:

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
 
For example, using the DNA strand "1001110110" (ignoring the padding), the attributes of the bunny would be:

- Ability (Block 1): 10 = Radiation
- Defense (Block 2): 01 = Thick Skin
- Mutation (Block 3): 11 = Massive Telepathic Brain
- Build (Block 4): 01 = Muscular
- Strategy (Block 5): 10 = Defensive

## Player DNA
The DNA of the player is used to determine the fitness score of the bunny DNA. The player DNA is composed of 4 blocks (8 bits) and can be represented in hexadecimal notation as well. Each block of player DNA corresponds to a specific attribute of the bunny DNA, as specified in the following table:
 
| Player DNA Block Index  | Bunny DNA Block Attribute Index |
| ---                     | ---                             |
| 0                       | 3                               |
| 1                       | 2                               |
| 2                       | 1                               |
| 3                       | 0                               |

 
The player DNA is decoded by converting each block to an integer value and adding 1 to it. For example, block 1 (binary `10`) is equal to 2 + 1 = 3.
 
## Evaluating the Bunny DNA
The fitness score of a bunny is calculated based on its comparison with the player DNA. The player DNA can change over time, which may affect the evolution of the bunnies and what constitutes a high fitness score.

Each block of the bunny DNA is converted to a fitness score by matching it with the corresponding block in the player DNA. The value of the attribute is first converted to the index value based on the player DNA, and then to a fitness score by multiplying it by 5.

For example, if the bunny DNA block one (Ability) is `1001110110` and the player DNA is `11010010`, the index value for block one is 2 (which corresponds to "Radiation"). This value matches player DNA block index 1 (or block 2), which has a value of `00` or 0. Adding 1 to this value gives a final score of 1, which is the fitness score for the "Ability" block of this bunny's DNA.

## Calculating the Total Fitness Score
To determine a bunny's total fitness score, the fitness score of each block of its DNA is added together. The resulting score is on a scale of 5-20, with a highest score of 20, mid-high score of 15, mid-low score of 10, and lowest score of 5.
 
## Generation and Evaluation Rules
1. Bunnies with the highest fitness scores, ranging from 18 to 20, are considered "Best of the Best."
2. Bunnies with moderate fitness scores, ranging from 12 to 17, are considered "Hopeful Monsters."
3. Bunnies with a fitness score of 11 or lower do not survive and are eliminated from the gene pool.
4. If not enough bunnies survive, new ones are generated with random DNA to replenish the gene pool.
5. Each generation has a chance for random mutations to occur in the offspring.
 