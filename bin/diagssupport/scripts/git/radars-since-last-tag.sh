#!/bin/sh

git log `git tag -l | sort -t - -k1,1n -k2,2n | tail -n 1`..HEAD
