# Steganography Using C (LSB Technique)

## Overview
This project implements image steganography in C using the Least Significant Bit (LSB) technique. It allows secret text messages to be hidden inside BMP image files and later extracted without causing noticeable changes to the image.

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
Clone the Repository: git clone https://github.com/gayathrikarasi-dev/steganography-c.git cd mp3-tag-reader

## Compile the Program
- gcc src/steganography.c -o steganography

## Run the Program
./mp3_tag_reader

## Encoding
- ./steganography -e beautiful.bmp secret.txt output.bmp

## Decoding
- ./steganography -d output.bmp output.txt

## Command-Line Options
- -e Encode secret data into image
- -d Decode secret data from image

## Notes
- BMP metadata is displayed before processing
- Original image is not modified directly
- Temporary file is used during encoding
- Sample image and text files are provided

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

## Screenshots

### Encode
<img width="1280" height="572" alt="image" src="https://github.com/user-attachments/assets/7e5ea01a-2027-4bf9-b7df-f0efe0fb6c89" />

### Decode
<img width="1345" height="334" alt="image" src="https://github.com/user-attachments/assets/43da3b42-22dd-45aa-ba36-6177718ac513" />


## Project Structure
steganography-c/
├── include/
│   ├── common.h
│   ├── encode.h
│   └── decode.h
├── src/
│   ├── main.c
│   ├── encode.c
│   └── decode.c
├── images/
│   ├── encode.png
│   └── decode.png
├── beautiful.bmp
├── secret.txt
├── output.bmp
├── output.txt
├── README.md
└── .gitignore



