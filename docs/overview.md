# Project Overview

## Requirements
This project needs the g++ package for compilation. Docker/Compose is useful to build the project but not required. Currently, only Linux distros are supported.
 
## Quick Start/Run
Download the most recent compiled version of the project (<a href="https://github.com/mattbuske/pcg-bunny/releases" target="_blank">Latest Release</a>). Run the binary that matches your OS via the command line like so:
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
