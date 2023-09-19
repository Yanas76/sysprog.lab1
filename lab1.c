#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_WORD 30

int main(){

    int lengthLimit = 30;
    int wordAmmount = 0;
    char word[MAX_WORD];
    char **results = NULL;
    char c;
    FILE *file = fopen ("file.txt", "r");
    
    if(file == NULL){
        printf("Error! No file found");
        return 1;
    }

    while(lengthLimit > 0){

        fseek(file, 0L, SEEK_SET);
        int i = 0;

        do{

            c = fgetc(file);
            if(('A' <= c && c <='Z') || ('a' <= c && c <= 'z')){

                if(i == MAX_WORD){
                    printf("Wrong word format!");
                    return 1;
                }

                word[i] = c;
                i++;

            }else{

                if(i == lengthLimit){

                    results = realloc(results, sizeof(char *) * (wordAmmount + 1)); 
                    results[wordAmmount] = strdup(word);
                    wordAmmount++;
                }
               
                i = 0;
                memset(word, 0, sizeof(word));
            }
           
        }while(c != EOF);
        
        i = 0;
        memset(word, 0, sizeof(word));
        lengthLimit--;
        
    }

    fclose(file);

    int *repeated = (int *)calloc(wordAmmount, sizeof(int));    

    for (int i = 0; i < wordAmmount; i++) {

        if (repeated[i] == 0) {

            for (int j = i + 1; j < wordAmmount; j++) {

                if (strcmp(results[i], results[j]) == 0) {
                    repeated[j] = 1; 
                }
            }
        }
    }

    printf("Words ordered by length:\n");
    for(int i = 0; i < wordAmmount; i++){

        if(repeated[i] == 0){
            printf("%s ",results[i]);
        }  
    }

    free(repeated);
    free(results);

    return 0;
}