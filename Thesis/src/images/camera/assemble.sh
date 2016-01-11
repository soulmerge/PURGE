#!/bin/bash

convert camera-global.png -resize 399x298 camera-global.tmp.png
convert camera-local.png -resize 399x300 camera-local.tmp.png
#montage -tile 1x2 -geometry 300x200 camera-global.tmp.png camera-local.tmp.png 1.png

WIDTH=$(identify -format %G camera-local.tmp.png)
WIDTH=${WIDTH%x*}

convert -size ${WIDTH}x1 xc:black h-line.png
montage -tile 1x4 -mode Concatenate camera-global.tmp.png h-line.png h-line.png camera-local.tmp.png 1.png

convert -size 2x600 xc:black v-line.png
montage -tile 3x1 -mode Concatenate 1.png v-line.png screenshot.png camera.png

rm 1.png h-line.png v-line.png *.tmp.png

#montage -tile 2x1 camera-global.tmp.png xc:black 1.tmp.png
#montage -tile 2x1 camera-local.tmp.png xc:black 2.tmp.png

#convert camera-local.png -resize 399x299 -background:white camera-local.tmp.png
#convert camera-global.png -resize 399x299 -background:white camera-global.tmp.png
