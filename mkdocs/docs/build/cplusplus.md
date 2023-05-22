# C++

### Manual Compilation

To compile the project manually, navigate to the `c++/src` directory and run the following command:

```SHELL
mkdir -p dist
g++ Bunny.cpp DNA.cpp main.cpp -g -o dist/pcg-bunnies
```

This will create the `dist` directory and compile the project into an executable named `pcg-bunnies`.

### Compile via Build Script
Navigate to the `c++/src` directory and run the following command:

```SHELL
./build-project
```

This will run the provided build script and place the compiled program in the `c++/dist` folder with the name `pcg-bunnies`.

### Compile via Docker Compose

To compile the program using Docker Compose, run one of the following commands based on your Linux distribution from the `c++` directory:

```SHELL
# For regular Linux
docker-compose build --no-cache latest
# For Alpine Linux
docker-compose build --no-cache alpine
```

The resulting image will contain the compiled project in multiple locations:

- `/src/dist/pcg-bunnies` (all images)
- `/usr/sbin/pcg-bunnies` (linux images)
- `/sbin/pcg-bunnies` (Alpine images)

To compile for a new release of this project, use the development versions (labeled -dev) and manually run the build scripts in the container to generate the binaries.