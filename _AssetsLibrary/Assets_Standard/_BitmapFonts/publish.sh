#! /bin/sh

echo "Generating SpriteSheets..."

TP=/usr/local/bin/TexturePacker

${TP} _TextureProjects/*.tps

echo "Copying Files..."

for file in ./BMF_SD/*
do
if test -f $file
then
    cp ${file%.*}.fnt ../Assets/Assets/SD
fi
done

for file in ./BMF_HD/*
do
if test -f $file
then
    cp ${file%.*}.fnt ../Assets/Assets/HD
fi
done

for file in ./BMF_HDR/*
do
if test -f $file
then
    cp ${file%.*}.fnt ../Assets/Assets/HDR
fi
done


exit 0