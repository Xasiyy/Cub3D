#!/bin/bash

Xvfb :99 -screen 0 1024x768x24 &
sleep 1

DISPLAY=:99 ./cub3D maps/valid_subject.cub &

x11vnc -display :99 -forever -shared -nopw -rfbport 5900 -quiet &

exec websockify --web=/usr/share/novnc/ 3000 localhost:5900
