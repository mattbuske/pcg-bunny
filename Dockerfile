# Base Image
FROM rockylinux:8.5 AS base

# Copy Over Build Scripts
COPY /src /src

# Set Working Directory
WORKDIR /src

# Run Command
RUN \
    # Update All
    dnf -y update-minimal && \
    # Install g++
    dnf -y install gcc-c++ && \
    # Build Program
    ./build-project && \
    # Move Compiled Program
    cp dist/pcg-bunnies /usr/sbin/pcg-bunnies && \
    # Clean up
    dnf clean all

# Final Layer
FROM rockylinux:8.5 AS final

# Copy from Base Layer
COPY --from=base /src /src
COPY --from=base /usr/sbin/pcg-bunnies /usr/sbin/pcg-bunnies

# Init Entry Point
ENTRYPOINT [ "/usr/sbin/init" ]