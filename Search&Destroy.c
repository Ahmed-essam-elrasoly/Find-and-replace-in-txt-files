//07-10-2020
//Author: Ahmed Elrasoly
//Search & Destroy v 1.0
/*This Calculator Application calculates simple math operations and trigonometric functions
this program accepts math problems in a linear form
*/
//preprocessors
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <conio.h>
#if _WIN32
    #define clrscr system("cls");
#elif __APPLE__
    #define clrscr system("clear");
#elif __linux__
    #define clrscr system("clear");
#endif

//prototypes
FILE *openfile(void);
void find_all ( FILE *target_filePtr);
void replace_all(FILE *target_filePtr);
char path[] = "";

void main (void){
    FILE *original_filePtr;
    original_filePtr = openfile();
    puts("");
    puts("to search enter 'f'\nto replace enter 'r'");
    char opt = getchar();
    if (opt == 'f' || opt == 'F' || opt == 'r' || opt == 'R'){
        if (opt == 'f' || opt == 'F'){
            find_all(original_filePtr);
        }//end if
        if (opt == 'r' || opt == 'R'){
            replace_all(original_filePtr);
        }//end if
    }//end if
    else{
        fflush(stdin);
        puts("invalid input\nPress enter to continue");
        getchar();
        clrscr;
        fflush(stdin);
        main();
    }//end else*/

}//end main


FILE *openfile (void)
{
    FILE *demoPtr;
    puts("Enter either full path(including file's name)\n\t\t--or--\nthe file name only (then the file will be created at the program's directory)");
    gets(path);
    if ((strlen(path) < 1) || !strpbrk(path, "0123456789qwertyuioplkjhgfdsazxcvbnmQWERTYUIOPLKJHGFDSAZXCVBNM")){
        puts("invalid name\nPress enter to continue");
        getchar();
        clrscr;
        fflush(stdin);
        main();
    }//end if
    char *dotPtr;
    dotPtr = strchr(path, '.');
    if(dotPtr == NULL ){
        strcat(path, ".txt");
    }
    else{
        char ext[] = {*dotPtr, *(dotPtr+1), *(dotPtr+2), *(dotPtr+3), '\0'};
        if(strcmp(ext, ".txt")){
            puts("unable to deal with such file type");
            puts("Press enter to continue");
            getchar();
            clrscr;
            fflush(stdin);
            main();
        }//end if
    }//end else
    if (( demoPtr = fopen(path, "r") ) == NULL) {
        printf("%s\n", strerror(2));
        getchar();
        clrscr;
        fflush(stdin);
        main();
    }//end if
    else{
        puts("File is opened");
    }//end else
    return demoPtr;
}//end openfile

void find_all ( FILE *target_filePtr) {
    puts("enter the string to be found: ");
    char to_be_found [63];
    fflush(stdin);
    gets(to_be_found);
    fseek(target_filePtr,0,SEEK_END);
    size_t len = ftell(target_filePtr);
    rewind(target_filePtr);
    unsigned int found = 0;
    unsigned int shift = 1;
    SHIFT:
    while(!feof(target_filePtr)){
        char dummy[strlen(to_be_found)+1];
        fread(dummy, ((len - ftell(target_filePtr)) >= strlen(to_be_found)) ? strlen(to_be_found) : (len - ftell(target_filePtr)+1), 1, target_filePtr);
        strcat(dummy, "");
        //printf("\n%s\t%d\t%d\t%lu\t%u\n",dummy, shift, found, ftell(target_filePtr), len);
        if  (len == ftell(target_filePtr)){break;}//end if
        if (!strcmp(dummy,to_be_found)){
            found ++;
            strcpy(dummy, "");
        }//end if
    }//end while*/
    //printf("%d\t%d\n", (len-shift), (len-shift) % strlen(to_be_found));
    if(shift < strlen(to_be_found)){
        //printf("%d\n", shift);
        rewind(target_filePtr);
        fseek(target_filePtr,shift,SEEK_SET);
        shift++;
        goto SHIFT;
    }//end for
    printf("%s is found %d times.\n Press Enter to continue", to_be_found, found);
    fclose(target_filePtr);
    getchar();
    clrscr;
    fflush(stdin);
    main();
}//end findall

void replace_all (FILE *target_filePtr) {
    puts("enter the string to be found: ");
    char to_be_replaced [63];
    fflush(stdin);
    gets(to_be_replaced);
    puts("enter the replacing string: ");
    char replacing [63];
    fflush(stdin);
    gets(replacing);
    fseek(target_filePtr,0,SEEK_END);
    size_t len = ftell(target_filePtr);
    rewind(target_filePtr);
    unsigned int found = 0;
    unsigned int shift = 1;
    FILE *tempfilePtr;
    tempfilePtr = fopen("ModifiedFile.txt", "w");
    rewind(tempfilePtr);
    int index[len+1];
    int index_id = 0;
    SHIFT:
    while(!feof(target_filePtr)){
        size_t element_size;
        //printf("%d\\|/%d\n",len - ftell(target_filePtr), (len - ftell(target_filePtr)));
        if ((len - ftell(target_filePtr)) >= strlen(to_be_replaced)) {
            element_size = strlen(to_be_replaced);
        }
        else {
            element_size = (len - ftell(target_filePtr));
        }
        char dummy[element_size];
        fread(dummy, element_size, 1, target_filePtr);
        dummy[element_size] = '\0';
        printf("\n[%s]\t%s\t%d\t%d\t%lu\t%u\t%u\n",dummy, to_be_replaced, shift, found, ftell(target_filePtr), len, element_size);
        if (!strcmp(dummy,to_be_replaced)){
            memset(dummy,'*',strlen(replacing));
            dummy[strlen(replacing)] = '\0';
            //printf("\n\n[%s]\n\n",dummy);
            fwrite(dummy, strlen(dummy), 1, tempfilePtr);
            index[index_id] = ftell(tempfilePtr)-strlen(dummy);
            //fseek(tempfilePtr, (strlen(dummy)+2), SEEK_END);
            //strcpy(dummy, "");
            found++;
           // printf("\n%d\t%d\n",found ,index[index_id]);
            index_id++;
        }//end if
        else{
            fwrite(dummy, strlen(dummy), 1, tempfilePtr);
        }
        if  (len == ftell(target_filePtr)){puts("..."); break;}//end if

    }//end while
   // printf("%d\n", (len-shift));
    if(shift < strlen(to_be_replaced)){
        //printf("%d\n", shift);
        rewind(target_filePtr);
        rewind(tempfilePtr);
        fseek(target_filePtr,shift,SEEK_SET);
        fseek(tempfilePtr,shift/*-(index_id * strlen(replacing))*/,SEEK_SET);
        shift++;
        goto SHIFT;
    }//end if
    //fclose(target_filePtr);
    for (unsigned int i = 0; i <= index_id; i++){
        //printf("")
        fseek(tempfilePtr, index[i], SEEK_SET);
        fwrite(replacing, strlen(replacing), 1, tempfilePtr);
    }

    printf("%s is found and replaced %d times.\nCheck \"ModifiedFile.txt\"\n", to_be_replaced, found);
    puts(":)\n please Press Enter to continue");
    getchar();
    clrscr;
    fflush(stdin);
    main();
}//end relaceall

