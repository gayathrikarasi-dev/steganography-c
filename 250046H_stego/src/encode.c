#include <stdio.h>
#include <string.h>
#include "encode.h"
//#include "types.h"

/* Get image size
 * Input: Image file ptr
 * Output: width * height * bytes per pixel (3 in our case)
 * Description: In BMP Image, width is stored in offset 18,
 * and height after that. size is 4 bytes
 */
unsigned int get_image_size_for_bmp(FILE *fptr_image)
{
    unsigned int width, height;  //width is stored at 18th index 
    // Seek to 18th byte
    fseek(fptr_image, 18, SEEK_SET);

    // Read the width (an int)
    fread(&width, sizeof(int), 1, fptr_image);
  //  printf("width = %u\n", width);

    // Read the height (an int)
    fread(&height, sizeof(int), 1, fptr_image);  //height is next to width
   // printf("height = %u\n", height);
    rewind(fptr_image);
    // Return image capacity
    return width * height * 3;
}

/* 
 * Get File pointers for i/p and o/p files
 * Inputs: Src Image file, Secret file and
 * Stego Image file
 * Output: FILE pointer for above files
 * Return Value: success or failure, on file errors
 */
Status open_files(EncodeInfo *encInfo)
{   
    printf("Opening required files \n");
    encInfo->src_image_fptr = fopen(encInfo->src_image_fname, "r"); //source file

    if (encInfo->src_image_fptr == NULL)
    {
    	perror("fopen");
    	fprintf(stderr, "ERROR: Unable to open file %s\n", encInfo->src_image_fname);

    	return failure;
    }
    printf("Opened %s\n",encInfo->src_image_fname);

    encInfo->secret_fptr = fopen(encInfo->secret_fname, "r"); //we read msg so read mode

    if (encInfo->secret_fptr == NULL)
    {
    	perror("fopen");
    	fprintf(stderr, "ERROR: Unable to open file %s\n", encInfo->secret_fname);

    	return failure;
    }
    printf("Opened %s\n",encInfo->secret_fname);

    encInfo->output_image_fptr = fopen(encInfo->output_image_fname, "w"); 

    if (encInfo->output_image_fptr == NULL)
    {
    	perror("fopen");
    	fprintf(stderr, "ERROR: Unable to open file %s\n", encInfo->output_image_fname);

    	return failure;
    }
    printf("Opened %s\n",encInfo->output_image_fname);
    printf("Completed opening files\n");
    return success;
}

Opr_type check_operation(char *option)
{
    if(!strcmp(option,"-e"))
        return encode;
    else if(!strcmp(option,"-d")) 
        return decode;
    else
        return unsupported;
}

Status do_encoding(char *argv[],EncodeInfo *encInfo){
    if(validate_encode_args(argv,encInfo)==failure)  //to validate arguments
        return failure;
    printf("##   Encoding Procedure Started  ##\n");    
    if(copy_bmp_header(encInfo)==failure)
        return failure;   
        
    if(encode_magic_string(MAGIC_STRING,encInfo)==failure)
        return failure; 

       
    if(encode_secret_file_extn(encInfo)==failure)
        return failure;        
       
    
    if(encode_secret_file_data(encInfo)==failure)
        return failure;    
            
    copy_remaining_img_data(encInfo);   
    printf("##   Encoding Done Successfully   ##\n"); 
    
}
//instead of encoding in same file we are creating another file and encoding in that
Status copy_bmp_header(EncodeInfo *encInfo){  //so first we are copying header 54 bytes
    char header[54];               
    rewind(encInfo->output_image_fptr);  //rewinding just to make sure the offset is at starting
    rewind(encInfo->src_image_fptr);
    fread(header,54,1,encInfo->src_image_fptr);  //usinf fread and fwrite to copy
    fwrite(header,54,1,encInfo->output_image_fptr);
    return success;
}
Status encode_magic_string(const char *magic_string, EncodeInfo *encInfo){
    //encoding length
    printf("Encoding Magic String Signature\n");
    char buffer[32];
    fread(buffer,32,1,encInfo->src_image_fptr);
    encode_4byte_to_lsb(strlen(MAGIC_STRING),buffer);
    fwrite(buffer,32,1,encInfo->output_image_fptr);
    //encoding the string
    for(int i=0;i<strlen(MAGIC_STRING);i++){
        char buffer2[8];
        fread(buffer2,8,1,encInfo->src_image_fptr);
        encode_1byte_to_lsb(MAGIC_STRING[i],buffer2);
        fwrite(buffer2,8,1,encInfo->output_image_fptr);
    }
    printf("Done\n");
    return success;
}
Status encode_secret_file_extn(EncodeInfo *encInfo){
     //encoding length
    printf("Encoding secret.txt file extension\n");  
    char buffer[32];
    fread(buffer,32,1,encInfo->src_image_fptr);   //taking 32 bytes from the original
    encode_4byte_to_lsb(encInfo->secret_extn_size,buffer); //encoding in them
    fwrite(buffer,32,1,encInfo->output_image_fptr);   //and them copying to new one
    //encoding the string
    for(int i=0;i<encInfo->secret_extn_size;i++){
        char buffer2[8];
        fread(buffer2,8,1,encInfo->src_image_fptr);
        encode_1byte_to_lsb(encInfo->secret_extn[i],buffer2);
        fwrite(buffer2,8,1,encInfo->output_image_fptr);
    }
    printf("Done\n");
    return success;

}
Status encode_secret_file_data(EncodeInfo *encInfo){
     //encoding length
    char buffer[32];
    printf("Encoding secret.txt file size\n"); 
    fread(buffer,32,1,encInfo->src_image_fptr);
    encode_4byte_to_lsb(encInfo->secret_file_size,buffer);
    fwrite(buffer,32,1,encInfo->output_image_fptr);
    printf("Done\n");
    //encoding the string
    printf("Encoding secret.txt file data\n");
    rewind(encInfo->secret_fptr);
    char ch;
    while(fread(&ch,1,1,encInfo->secret_fptr)){
        char buffer2[8];
        fread(buffer2,8,1,encInfo->src_image_fptr);
        encode_1byte_to_lsb(ch,buffer2);
        fwrite(buffer2,8,1,encInfo->output_image_fptr);
    }
    printf("Done\n"); 
    return success;
}
Status copy_remaining_img_data(EncodeInfo * encInfo){
    printf("Copying left over data\n");
    char ch;       //after encoding copying remaining data
    while(fread(&ch,1,1,encInfo->src_image_fptr)){
        fwrite(&ch,1,1,encInfo->output_image_fptr);
    }
    printf("Done\n");
    return success;
}
    
Status encode_4byte_to_lsb(int data, char *buffer_32){
    for(int i=31;i>=0;i--){   // to encode 4 bytes to lsb
        buffer_32[31-i]=((data>>i)&1) | (buffer_32[31-i] &(~1));
    }
}
Status encode_1byte_to_lsb(char data, char *buffer_8){
    for(int i=7;i>=0;i--){  // to encode 1 byte to lsb
        buffer_8[7-i]=((data>>i)&1) | (buffer_8[7-i] &(~1));
    }
}
Status validate_encode_args(char *argv[],EncodeInfo *encInfo){
    char * ptr1=strstr(argv[2],".bmp");   //checking arg 2 is .bmp file or not
    if(ptr1==NULL){
        printf("Read and validation is not successfully done\n");
        return failure;
    }
    if(!strcmp(ptr1,".bmp")){
        encInfo->src_image_fname=argv[2];
        printf("Src file is .bmp file\n");
    }
    else{
        printf("Read and validation is not successfully done\n");
        return failure;
    }
    char * ptr2=strchr(argv[3],'.');
    if(ptr2==NULL){
        printf("Read and validation is not successfully done\n");
        return failure;
    }
    if(strcmp(ptr2,".")){
        encInfo->secret_fname=argv[3];
        int i=1;
        while(argv[3][i]){
            if(argv[3][i]=='.')
                break;
            i++;    
        }
        int j=0;
        while(argv[3][i]){
            encInfo->secret_extn[j]=argv[3][i];
            i++;j++;
        }
    }
    else{
        printf("Read and validation is not successfully done\n");
        return failure;
    }
    if(argv[4]==NULL){
        printf("Output file not mentioned.Creating output.bmp as default\n");
        encInfo->output_image_fname="output.bmp";
    }
    else {
        char * ptr=strstr(argv[4],".bmp");
        if(ptr==NULL){
            printf("Read and validation is not successfully done\n");
            return failure;
        }
        if(!strcmp(ptr,".bmp"))
            encInfo->output_image_fname=argv[4];
        else{
            printf("Read and validation is not successfully done\n");
            return failure;
        }  
    }
    if(open_files(encInfo)==failure)  //opening the necessary files
        return failure;
    if(check_capacity(encInfo)==failure)  //checking capacity of original file 
        return failure;               //weather it can fit the encoding data or not
    return success;    

}
Status check_capacity(EncodeInfo *encInfo){
    unsigned long int image_capacity=get_image_size_for_bmp(encInfo->src_image_fptr);
    printf("src image size=%lu\n",image_capacity);
    rewind(encInfo->src_image_fptr);
    unsigned int x=get_file_size(encInfo->secret_fptr);
    if(x==0){
        printf("Nothing to encode\n");
        return failure;
    }
    unsigned int encoded=(4+strlen(MAGIC_STRING)+4+strlen(encInfo->secret_extn)+4+x)*8;
    encInfo->secret_extn_size=strlen(encInfo->secret_extn);
    encInfo->secret_file_size=x;
    rewind(encInfo->secret_fptr);  //here we are seeing the size of original file and size of all encoding data
    printf("Checking for beautiful.bmp capacity to handle output.bmp\n");
    if(image_capacity<encoded)  //and comparing them 
        return failure; 
         //if original size is less it means that we cant encode properly
    printf("Done.Enough capacity is there\n");     
    return success;    
}
unsigned int get_file_size(FILE *fptr){ 
     //to get the size of file
    printf("Checking for secret.txt size\n");
    fseek(fptr,0,SEEK_END);
    if(ftell(fptr)==0){
        printf("Empty\n");
        return 0;
    }
    else   
        printf("Not empty\n");
    return ftell(fptr);
}