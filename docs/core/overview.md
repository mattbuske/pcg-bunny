# Project Overview
## Overview
This project is a procedural content generation tool that uses evolutionary algorithms to generate new and unique bunnies. It requires the g++ package for compilation and is currently only supported on Linux distros. Users can quickly start the program by downloading the most recent compiled version of the project and running the binary that matches their OS. The output of the program will display a summary of the bunnies' characteristics and how they've evolved over the generations. The goal of the project is to reach an optimal ratio of 'fit' to 'unfit' bunnies using the set criteria. The project allows developers to quickly generate unique and interesting content for their projects without having to manually create each piece.

## Requirements
This project requires the g++ package for compilation and Linux distros are currently supported. Docker/Compose can also be used to build the project but it is not a requirement.
 
## Quick Start/Run
1. Download the most recent version of the project from the <a href="https://github.com/mattbuske/pcg-bunny/releases" target="_blank">Latest Release</a> 
2. Run the binary that matches your OS via the command line:
```SHELL
# Linux/Alpine
./pcg-bunnies
```
 
## Project Output
After running the project, you will see something similar to the following printed 50 times:
```SHELL
Generation (n) summary:
(d) Bunnies Died
(s) Bunnies Survived.
Of those that Survived:
(h) were Hopeful Monsters.
(b) were the Best of the Best.
```
where:

- n = Generation number
- d = The number of bunnies that were 'unfit' and 'died off'- unable to pass on their dna to the next generation
- s = The number of bunnies that were 'fit' and thus survived - giving them a chance to pass on their dna to the next generation
- h = The number of bunnies that are considered 'hopeful monsters' - bunnies that are considered almost the 'best of the best'
- b = The number of bunnies that are considered the best possible via the set criteria
 
The goal of the project is to reach a better ratio of 'fit' to 'unfit' bunnies with each generation. This project is not currently calibrated and can reach an acceptable number of 'fit' bunnies in few generations.
