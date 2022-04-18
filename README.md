# The Search-Based Approach to Procedural Content Generation - PCG Bunnies!
 
This project demonstrates the [search-based approach](http://pcgbook.com/wp-content/uploads/chapter02.pdf) to procedural content generation utilizing evolutionary search algorithms (See the [PCG Book](https://pcgbook.com) for more info on procedural content generation and other approaches). This project evolves bunnies over a number of generations to achieve bunnies with desired traits.
 
## Contents:
1. [Requirements](#requirements)
2. [Quick Start/Run](#quick-startrun)
3. [Project Output](#project-output)
4. [Project Deep Dive](#project-deep-dive)
    1. [Bunny DNA](#bunny-dna)
    2. [Attribute Types](#attribute-types)
    3. [Player DNA](#player-dna)
    4. [Trait Defenitions](#trait-definitions)
    5. [Evaluating the Bunny DNA](#evaluating-the-bunny-dna)
    6. [Calculating the Total Fitness Score](#calculating-the-total-fitness-score)
    7. [Generation and Evaluation Rules](#generation-and-evaluation-rules)
5. [Build The Project](#build-the-project)
    1. [Manual Compilation](#manual-compilation)
    2. [Build Script](#compile-via-build-script)
    3. [Docker Compose](#compile-via-docker-compose)
 
## Requirements
This project needs the g++ package for compilation. Docker/Compose are useful to build the project but not required. Currently only linux distros are supported.
 
## Quick Start/Run
Download the most recent compiled version of the project [here](dist/README.md). Run the binary that matches your OS via the command line like so:
```SHELL
# Linux/Alpine
./pcg-bunnies
```
 
## Project Output
After running the project you will see something like this printed 50 times:
```SHELL
Generation (n) summary:
(d) Bunnies Died
(s) Bunnies survived.
Of those that survived:
(h) were hopeful Monsters.
(b) were the Best of the Best.
```
where:
- n = Generation number
- d = The number of bunnies that were 'unfit' and 'died off'- unable to pass on their dna to the next generation
- s = The number of bunnies that were 'fit' and thus survived - giving them a chance to pass on their dna to the next generation
- h = The number of bunnies that are considered 'hopeful monsters' - bunnies that are considered almost the 'best of the best'
- b = The number of bunnies that are considered the best possible via the set criteria
 
Each generation should get closer to a better ratio of 'fit' via 'unfit' bunnies. This project is not currently 'calibrated' so it reaches an acceptable number of 'fit' bunnies in very few generations.
 
## Project Deep Dive
The project consists of bunny objects, which each contain a dna object representing the bunnies' attributes represented in binary.
 
### Bunny DNA
The binary DNA of a bunny is only 5 blocks (or 10 bits) of 8 total blocks (3 of the 8 being padding) comprising a strand of 16 bits. The dna of a bunny could potentially look like this:
```SHELL
# Binary
00 00 00 10 01 11 01 10
 
# Hexadecimal
0x276
```
### Attribute Types
Each bunny dna block represents a different attribute type (starting right to left):

0. Block 1 - Ability
1. Block 2 - Defense
2. Block 3 - Mutation
3. Block 4 - Build
4. Block 5 - Strategy
 
As each block is made up of two bits each, there are four possible values, per block: 00, 01, 10, or 11. These possibilities map to an index in a constant array of traits. Each index in this array corresponds to a general trait type:

0. Stealth
1. Aggressive
2. Defensive
3. Ranged

### Trait Definitions
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
```SHELL
# DNA: 10 01 11 01 10
# Ability (Block 1): 10 = Radiation
# Defense (Block 2): 01 = Thick Skin
# Mutation (Block 3): 11 = Massive Telepathic Brain
# Build (Block 4): 01 = Muscular
# Strategy (Block 5): 10 = Defensive
```
### Player DNA
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
```SHELL
# DNA: 11 01 00 10
# Block 1: 10 = 2 +1 = 3
# Block 2: 00 = 0 +1 = 1
# Block 3: 01 = 1 +1 = 2
# Block 4: 11 = 3 +1 = 4
```
This means the attribute index can be converted to an integer value based on the player dna.
 
### Evaluating the Bunny DNA
The fitness score is compared to the strand of player dna- thus presenting the possibility of adaptive evolution of the bunnies. This means if the player DNA changes, the evolution of the bunnies and what constitutes fitness could change as well. How this works is the value of the attribute is converted to the value that is represented in the corresponding player dna. This value is the fitness score of the attribute. For example:
 
Compare Block one (Ability) of Bunny DNA (1001110110) to the Player DNA: (11010010) to get its fitness score.
 
Bunny DNA for Block one is '10' (which points to 'Radiation'), the index value being '2'. Using the table above, we see this corresponds to Player dna block index '1' (or block 2). Player dna Block 2 is '00', or 0. We add '1' to that value (in order to get an integer between 1-4) to get a final value of 1. This is the fitness score for the 'Ability' block of this Bunny's DNA.
 
### Calculating the Total Fitness Score
Depending on the player dna and bunny evaluated, each block of bunny dna would correspond to a fitness score. Then those values would be added together to determine the bunny's total fitness score. The fitness score scale (from 5-20) is as follows:
- Highest score = 4 * 5 = 20
- Mid-high score = 3 * 5 = 15
- Mid-Low score = 2 * 5 = 10
- Lowest score = 1 * 5 = 5
 
### Generation and Evaluation Rules:
1. 'Best of the Best' bunnies reside between 18-20.
2. 'Hopeful Monster' bunnies reside between 12-17.
3. Any bunnies with fitness scores 11 and below die off.
4. If there are not enough bunnies (i.e. too many die off) for a new generation, new ones are generated with random DNA to replenish the gene pool.
5. In every generation, there is a chance for random mutation in the offspring.
 
## Build the Project
Download this repository to a location of your choosing in your development environment. Make sure you have g++ and all necessary dependencies installed on your system and then choose a build method below (all methods start from inside the repo directory):
 
### Manual Compilation
To compile the project manually:
```SHELL
cd src
mkdir -p dist
g++ Bunny.cpp DNA.cpp main.cpp -g -o dist/pcg-bunnies
```
 
### Compile via Build Script
To compile the project from the build script:
```SHELL
cd src
./build-project
```
The compiled program will be placed in the /src/dist folder and will be named 'pcg-bunnies'.
 
### Compile via Docker Compose
To compile the program using docker compose:
```SHELL
# For regular linux- IE RockyLinux
docker-compose build --no-cache latest
# For Alpine linux
docker-compose build --no-cache alpine
```
 
The resulting image will contain the compiled project in more than one location (depending on the image):
- /src/dist/pcg-bunnies (all images)
- /usr/sbin/pcg-bunnies (linux images)
- /sbin/pcg-bunnies (Alpine images)
 
To compile for a new release of this project, use the development versions (labeled -dev) and manually run the build scripts in the container to generate the binaries.
