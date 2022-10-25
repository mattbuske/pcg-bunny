# Build the Project
Download this repository to a location of your choosing in your development environment. Make sure you have g++ and all necessary dependencies installed on your system and then choose a build method below (all methods are relative to the root of the repository):
 
## Manual Compilation
To compile the project manually:
```SHELL
cd src
mkdir -p dist
g++ Bunny.cpp DNA.cpp main.cpp -g -o dist/pcg-bunnies
```
 
## Compile via Build Script
To compile the project from the build script:
```SHELL
cd src
./build-project
```
The compiled program will be placed in the /src/dist folder and will be named 'pcg-bunnies'.
 
## Compile via Docker Compose
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
