# Prepare workspace on the local machine for docker

``` shell
cd /home/name/to/work/dir
git clone git@gitlab.devel.hbm.com:ngt/stator-yocto
```

``` shell
git pull --recurse-submodules
```

The doker container containes the minimal build environment. The $HOME
inside the container is /buildbot. We change this behaviour and
overwrite it with our settings from local machine.

``` shell
docker run -v /home/faix:/buildbot -t -i gitlab.hbm.com:5555/docker/yocot:v1 bash
```

``` shell
buildbot@2fa09a4e2f5b:~$ cd ~/to/work/dir/next-firmare
buildbot@2fa09a4e2f5b:~$ MACHINE=atlas . setup-environment build-atlas
buildbot@2fa09a4e2f5b:~$ bitbake sdimage
```
