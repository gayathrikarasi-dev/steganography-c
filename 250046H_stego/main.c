/*DOCUMENTAION:
NAME:Karasi Gayathri
DATE:23-10-2026
DESCRIPTION:Developed an image steganography application in C that securely hides
 secret text inside bitmap images using the Least Significant Bit (LSB) technique. 
 The project supports both encoding and decoding of messages through file handling 
 and bit manipulation, ensuring data confidentiality without noticeable image distortion.
 */
#include <stdio.h>
#include "encode.h"   //including both encode and decode header files
#include "decode.h"

int main(int argc, char *argv[])
{
    EncodeInfo encodeInfo;
    DecodeInfo decodeInfo;

    if( argc == 1 )  //if arguments are only 1 printing error and exting
    {
        printf("Invalid command line arguments\n");
        printf("Encoding: ./a.out -e <.bmp file> <.txt file> [output file]\n");
        printf("Decoding: ./a.out -d <.bmp file> [output file]\n");
	    return 0;
    }

    int opr = check_operation(argv[1]);   //checking operation encode or decode

    if( opr == encode )   //if encode 
    {
        if(argc <4 || argc>5){    //checking clas
            printf("Invalid command line arguments\n");
            printf("Encoding: ./a.out -e <.bmp file> <.txt file> [output file]\n");
            printf("Decoding: ./a.out -d <.bmp file> [output file]\n");
            return 0;
        }
        if(do_encoding(argv,&encodeInfo)==failure){  //if clas are correct number
        return 0;
        }
    }
    else if( opr == decode )  //if decoding
    {
        if(argc <3 || argc>4){
            printf("Invalid command line arguments\n");
            printf("Encoding: ./a.out -e <.bmp file> <.txt file> [output file]\n");
            printf("Decoding: ./a.out -d <.bmp file> [output file]\n");
            return 0;
        }
        if(do_decoding(argv,&decodeInfo)==failure){
        return 0;
        }
    }
    else
    {
	printf("Invalid option.\n");
    printf("Please enter either -e for encoding or -d for decoding\n");
    }
    return 0;
}