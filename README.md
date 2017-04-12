# iideaa-docker
[![Build Status](https://travis-ci.org/mariobarbareschi/iideaa-docker.svg?branch=master)](https://travis-ci.org/mariobarbareschi/iideaa-docker) [![](https://images.microbadger.com/badges/image/mariobarbareschi/iideaa.svg)](https://microbadger.com/images/mariobarbareschi/iideaa "Get your own image badge on microbadger.com")
------------

Docker image based on Arch-linux featuring IIDEAA tools

### Introduction to Bellerophon ###
------------

Bellerophon is a genetic optimization tools, used in the context of Approximate Computing. It is part of IIDEAA tools, developed to be used in conjunction with [clang-Chimera](https://github.com/ntonjeta/clang-chimera). Clang-Chimera provides code mutation, and Bellerophon uses genetic algorithm to find the Pareto-optimal solutions.

You can find more details about Bellerophon at [ntonjeta/bellerophon](https://github.com/mariobarbareschi/Bellerophon).

In order to try by yourself IIDEAA, just clone and make [Docker](https://www.docker.com) image by your own.

### How use container ###

Download and build container

    git clone https://github.com/ntonjeta/iidea-Docker
    cd iidea-Docker/
    docker build -t <name> .

Grab a coffee: it will take minutes for download and build everything.

Run container and mount volume

    docker run -dit -v /path/to/host/folder:/absolute/path/to/container/folder/ <container hash>

Attach to container

    docker attach <containerhash>

Now you have an interactive shell in wich you can use "clang-chimnera" and "bellerophon" tools. You can use a sharing volume with host machine for getting access to files outside the container.

#### Example ####
--------

You can test a simple example:

    docker run -it ...

The example use bit lenght reduction approximate technique, provided by [FLAP library](https://github.com/Ghost047/Fap).

### LICENSE ###
--------

* [GPLV3.0](https://www.gnu.org/licenses/licenses.html)

### Contributing ###
----------

Github is for social coding: if you want to write code, I encourage contributions through pull requests from forks of this repository.
