#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define GENE_POOL_SIZE 10

const char *ALPHABET = "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ!\"#$%&\'()*+,-./:;<=>?@[\\]^_`{|}~ ";

//---------PROTOTYPES---------
void test();
char *gen_string(int length);

/* We need to keep keys and values */
typedef struct candidate{
    char* dna;
    float fitness;
} candidate;

//---------MAIN---------
int main() {
  srand(time(NULL));
  char *target = "Hello, World!";
  int target_len = strlen(target);  

  //Generate the gene pool
  candidate genepool[GENE_POOL_SIZE];
  for(int i = 0; i < GENE_POOL_SIZE; i++){
    //genepool[i] = gen_string(target_len); //generate random string
    char *rand_dna = gen_string(target_len); //create a random dna
    int fitval = 0; //TODO: get from fitness function
    candidate new_cand = {rand_dna, fitval}; //create a new candidate
    genepool[i] = new_cand; //add candidate to gene pool
    
    printf("%s\n", genepool[i].dna); //DEBUG
  }

  //test();
  return 0;
}

//---------UTILITY FUNCTIONS---------

char *gen_string(int length){
  //Generates a random string of the given length
  char *rand_string = (char *) malloc(length); //Allocate memory for the string to be returned
  int alphabet_len = strlen(ALPHABET); //Get the length of the alphabet

  //Iterate length amount of times
  for(int i = 0; i < length; i++){    
    int rand_index = rand() % alphabet_len; //generate random index
    rand_string[i] = ALPHABET[rand_index];  //get random character from the alphabet
  }  
  //printf("%s\n", rand_string); //DEBUG
  return rand_string;
}

//---------TEST---------

void test(){

  /* int len = strlen(ALPHABET); */
  /* printf("len = %d\n", len); */
  /* for(int i = 0; i < len; i++){ */
  /*   printf("%c\n",ALPHABET[i]); */
  /* } */
  //printf("\n");
  
}
