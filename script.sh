#!bin/bash

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

rm -rf $dataDir
mkdir -p $dataDir
mkdir -p $vidDir
mkdir -p $imgDir
mkdir -p $textDir

# Download the video using yt-dlp
echo "Downloading video..."

ext=mp4
errorFile=data/errors.txt
yt-dlp -f "bestvideo[ext=$ext]+bestaudio[ext=$ext]/best[ext=$ext]" -o "$vidDir/%(title)s.%(ext)s" "$url" > /dev/null 2>$errorFile

# Check if the download was successful
if [ -f $vidDir/*.$ext ]; then
    echo "Video downloaded successfully."
else
    echo "Error downloading video. Check $errorFile for details."
    exit 1
fi