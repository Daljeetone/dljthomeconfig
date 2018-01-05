#!/bin/sh

astrisctl --probe $1 relay vbus 0
sleep 1
astrisctl --probe $1 relay dp2 1
sleep 1
astrisctl --probe $1 relay vbus 1