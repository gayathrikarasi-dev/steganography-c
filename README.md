# Steganography Using C (LSB Technique)

## Overview
- This project implements image steganography in C
- Uses Least Significant Bit (LSB) technique
- Hides secret text inside BMP images
- Allows decoding of hidden data without image distortion

## Features
- Encode secret messages into BMP images
- Decode hidden messages from encoded images
- Supports BMP image format
- Command-line based interface
- Sample files included for testing

## Concept Used
- Least Significant Bit (LSB) steganography
- Secret data stored in lower bits of pixel values
- Image appearance remains visually unchanged

## How to Run

### Clone the Repository
- git clone https://github.com/gayathrikarasi-dev/steganography-c.git
`cd steganography-c`

### Compile the Program
- gcc src/steganography.c -o steganography`

### Run the Program

## Encoding
- ./steganography -e beautiful.bmp secret.txt output.bmp`

## Decoding
- ./steganography -d output.bmp output.txt``

## Command-Line Options
- -e Encode secret data into image
- -d Decode secret data from image

## Notes
- BMP metadata is displayed before processing
- Original image is not modified directly
- Temporary file is used during encoding
- Sample image and text files are provided

## Project Structure
- steganography-c/
- include/
- common.h
- encode.h
- decode.h
- src/
- main.c
- encode.c
- decode.c
- images/
- encode.png
- decode.png
- beautiful.bmp
- secret.txt
- output.bmp
- output.txt
- README.md
- .gitignore

## Skills Learned
- C programming
- Binary file handling
- Bitwise operations
- Structures and pointers
- BMP file format
- Image steganography concepts

## Requirements
- GCC or any C compiler
- Linux or Windows operating system

## Sample Files
- beautiful.bmp Sample input image
- secret.txt Secret message file
- output.bmp Encoded image
- output.txt Decoded message file
