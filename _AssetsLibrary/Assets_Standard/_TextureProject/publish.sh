#! /bin/sh

echo "Generating SpriteSheets..."

TP=/usr/local/bin/TexturePacker

${TP} *.tps

echo "Done!!!"

exit 0