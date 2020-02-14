# Prepare workspace on the local machine for docker

``` shell
cd /home/name/to/work/dir
git clone git@gitlab.devel.hbm.com:next/next-firmare
```

``` shell
git pull --recurse-submodules
```

The doker container containes the minimal build environment. The $HOME
inside the container is /buildbot. We change this behaviour and
overwrite it with our settings from local machine.

``` shell
docker run -v /home/name:/buildbot -t -i gitlab.hbm.com:5555/docker/next bash
```

``` shell
buildbot@2fa09a4e2f5b:~$ cd ~/to/work/dir/next-firmare
buildbot@2fa09a4e2f5b:~$ MACHINE=hbk-frame-g1 . setup-environment build-frame-eval
buildbot@2fa09a4e2f5b:~$ bitbake hbk-frame
```
