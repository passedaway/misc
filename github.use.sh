#!/bin/sh
git config --global user.name "passedaway"
git config --global user.email "changqing.1230@gmail.com"

#if version is git1.7.10 or newer, cache password
git config --global credential.helper cache
#modify the cached time, default is 15minutes
git config --global credential.helper 'cache --timeout=3600' #timeout is in seconds, this is 1 hour
