#!/bin/bash

if [ ! $# -eq 2 ]
then
	echo Arguments are not right
	exit 1
fi

dir_path=$(dirname "$1")
filename=$(basename "$1")
# Check if the directory exists
if [ -d "$dir_path" ]; then
  echo "Directory $dir_path already exists."
else
  # Create the directory and any necessary parent directories
  mkdir -p "$dir_path"
  if [ $? -eq 0 ]; then
    echo "Directory $dir_path created successfully."
  else
    echo "Failed to create directory $dir_path."
    exit 1
  fi
fi

# Create a new empty file or truncate if it already exists
> "$1"

if [ $? -eq 0 ]; then
  echo "File $1 created or truncated successfully."
else
  echo "Failed to create or truncate file $1."
  exit 1
fi

echo $2 > $1
