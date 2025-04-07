#!bin/bash

clear

# Verify that the number of arguments is correct
if [ $# -ne 1 ]; then
    echo "The script requires exactly one argument: the YouTube video URL"
    exit 1
fi

url=$1

# Check if the provided argument is a valid YouTube URL
if ! [[ $url =~ ^https?://(www\.)?(youtube\.com|youtu\.be)/.+$ ]]; then
    echo "The YouTube link is not valid: $url"
    exit 1
fi

echo "Script started at $(date)..."

# Create directories if they don't exist
dataDir=data
vidDir=data/vid
imgDir=data/images
textDir=data/textFiles
errorDir=data/errors

rm -rf $dataDir
mkdir -p $dataDir
mkdir -p $vidDir
mkdir -p $imgDir
mkdir -p $textDir
mkdir -p $errorDir

# Download the video using yt-dlp
echo "Downloading video..."

ext=mp4
ytDlpErrorFile=data/ytDlpErrors.txt
yt-dlp -f "bestvideo[ext=$ext]+bestaudio[ext=$ext]/best[ext=$ext]" -o "$vidDir/%(title)s.%(ext)s" "$url" > /dev/null 2>$ytDlpErrorFile

# Check if the download was successful
if [ -f $vidDir/*.$ext ]; then
    echo "Video downloaded successfully."
else
    echo "Error downloading video. Check $ytDlpErrorFile for details."
    exit 1
fi

# Transform video to images
echo "Transforming video to images..."

fps=1
ffmpegErrorFile=data/ffmpegErrors.txt
ffmpeg -i "$vidDir/"*.$ext -vf fps=$fps "$imgDir/%06d.jpg" > /dev/null 2>$ffmpegErrorFile

# Check if the transformation was successful
testFile=$imgDir/000001.jpg

if [ -f $testFile ]; then
    echo "Video transformed to images successfully."
else
    echo "Error transforming video to images. Check $ffmpegErrorFile for details."
    exit 1
fi

# Resize images
echo "Resizing images..."

resizeErrorFile=data/resizeErrors.txt
mogrify -resize 200x200\> "$imgDir/*.jpg" > /dev/null 2>$resizeErrorFile

# Check if the resizing was successful
if [ -f $testFile ]; then
    echo "Images resized successfully."
else
    echo "Error resizing images. Check $resizeErrorFile for details."
    exit 1
fi