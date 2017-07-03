## How to create and publish the image

* Create the 'default' Docker machine
* Open the Docker Terminal
* Execute 'BuildDockerImage.sh'
* Then:
```
docker login # A Docker Hub account is required
docker tag tud_cppp echtzeitsysteme/tud_cppp
docker push echtzeitsysteme/tud_cppp
```

# How to start over
(cf. here: https://stackoverflow.com/questions/31909979/docker-machine-no-space-left-on-device)
Sometime you may get a "no space left on device" error.
In this case, the VM may be polluted.

There are serveral ways to obtain more memory.

(1) Pruning
```
# Removes everything that can be removed (e.g., unused images)
docker system prune 
```

(2) Recreating the VM

```
docker-machine rm default
docker-machine create --driver virtualbox --virtualbox-disk-size "100100" default # 100GB of space
docker-machine env default
```

(3) List and remove dangling images
```
docker volume rm $(docker volume ls -qf dangling=true)
```

(4) List and remove unused images
```
docker rmi $(docker images | grep "^<none>" | awk "{print $3}")
```
