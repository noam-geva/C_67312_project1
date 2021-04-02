#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//magic numbers
const int kLenOfAlphabet = 26;
const int kNumArgs = 5;

int Cipher(int curr, int shift){
    int ret = curr;
    if ('A' <= curr && curr <= 'Z') {
        ret = (curr - 'A' + shift) % kLenOfAlphabet +'A';
    }
    else if ('a' <= curr && curr <= 'z') {
        ret = (curr - 'a' + shift) % kLenOfAlphabet +'a';
    }
    return ret;
    }

int CheckValidity(int num_of_args, char *argv[]){
    int ret = 0;
    if (num_of_args != kNumArgs){
        fprintf( stderr,"Usage: cipher <encode|decode> <k> <source path file> <output path file>\n");
        ret = EXIT_FAILURE;
    }
    int shift = atoi(argv[2]);
    if ( shift < 0) //as stated in the project description PDF we may assume integers for K.
    {
        fprintf( stderr,"The given shifts value is invalid\n");
        ret = EXIT_FAILURE;
    }
    else if (shift == 0){
        if (!strcmp(argv[2], "0")){
            fprintf( stderr,"The given shifts value is invalid\n");
            ret = EXIT_FAILURE;
        }
    }
    int com_en = strcmp(argv[1], "encode");
    int con_de = strcmp(argv[1], "decode");
    if (com_en && con_de){
        fprintf( stderr,"The given command is invalid\n");
        ret = EXIT_FAILURE;
    }
    return ret;
}


int main(int argc, char *argv[]){
    if (CheckValidity(argc,argv) == EXIT_FAILURE){
        return  EXIT_FAILURE;
    }
    FILE *file_in;
    FILE *file_out;
    file_in = fopen(argv[3],"r");
    file_out = fopen(argv[4],"w");
    if ((file_in==NULL)||(file_out==NULL)){
        fprintf( stderr,"The given file is invalid\n");
        return  EXIT_FAILURE;
    }
    int str_cmp = strcmp(argv[1],"encode");
    int curr;
    int shift = atoi(argv[2]) % kLenOfAlphabet;
    int effective_shift = (!str_cmp) ? shift : kLenOfAlphabet - shift;
    while (EOF != (curr = fgetc(file_in))){
        fputc(Cipher(curr, effective_shift), file_out);
    }
    fclose(file_out);
    return 0;
}