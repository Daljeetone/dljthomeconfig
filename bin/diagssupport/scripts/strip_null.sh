#!/bin/sh

tr < $1 -d '\000' > $1.stripped
