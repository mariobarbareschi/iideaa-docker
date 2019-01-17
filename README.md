# iideaa-docker
[![Build Status](https://travis-ci.org/andreaaletto/iideaa-docker.svg?branch=master)](https://travis-ci.org/andreaaletto/iideaa-docker)
------------

Docker image based on Ubuntu 18.04 featuring IIDEAA tools.

### How use container
------------

First of all you will need a [Docker](https://www.docker.com/) installation. If not present you can easily install it using the [convenience script](https://docs.docker.com/install/linux/docker-ce/ubuntu/).

```sh
$ curl -fsSL https://get.docker.com -o get-docker.sh
$ sudo sh get-docker.sh
$ sudo usermod -aG docker your-user
```

##### Download from Docker Hub

IIDEAA Docker has been pushed to Docker Hub. You can pull it from [here](https://hub.docker.com/r/andreaaletto/iideaa-docker).


##### Build your own image

If, instead, you prefer to build Docker image from scratch, use the following commands:

```sh
$ git clone https://github.com/andreaaletto/iideaa-docker
$ cd iideaa-docker
$ chmod +x build_iideaa_docker
$ ./build_iideaa_docker
```

Grab a coffee: it will take several minutes to download and build everything.

##### Run a container

Either if you pulled from Docker Hub or if you built from scratch, it is recomended to spawn a container with: 

```sh
$ ./run_iideaa_docker
```
    
This script will run the container with ***zsh*** as default shell and it will mount the folder ```/root/mnt``` of the container onto the folder ```/home/<user>/iideaa_shared``` of the host.

Now you have an interactive shell in which you can use **clang-chimera** and **bellerophon** tools. You can use the container folder ```/root/mnt``` to share data with host machine outside the container.

### Example 
--------

You can test IIDEAA looking at the project folder in ```/opt/projects```. In the following, **k-means** example will be considered. 

Execute Clang-Chimera:

```sh
# cd /opt/projects/k-means/chimera
# ./launch.sh
```
Now check the mutants in ```/opt/projects/k-means/chimera/output``` and run Bellerophon:

```sh
# cd ../bellerophon
# ./launch_bellerophon.sh
```
The output of Bellerophon will be displayed on terminal.

### Related repositories
--------

For further information about IIDEAA tools, please refer to the following repos:

- [Clang-Chimera](https://github.com/andreaaletto/clang-chimera) 
- [Bellerophon](https://github.com/andreaaletto/Bellerophon)

#### LICENSE
--------

* [GPLV3.0](https://www.gnu.org/licenses/licenses.html)

#### Contributing
----------

Github is for social coding: if you want to write code, I encourage contributions through pull requests from forks of this repository.
