#!/bin/sh
echo "It is morning? Please answer yes or no"
read timeofday

case "$timeofday" in
    "yes" | "y" | "Yes" | "YES" ) echo "Good morning";;
    "n*" | "N*") echo "Good afternoon";;
    *) echo "Sorry, answer is not recognised";;
esac


