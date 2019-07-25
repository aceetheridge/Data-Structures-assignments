#!/bin/bash
sudo docker run -it --mount type=bind,source="$(pwd)",target=/bridges arunravindran/bridges:debian

./export.sh