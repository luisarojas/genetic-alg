#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define GENE_POOL_SIZE 10

const char *ALPHABET = "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ!\"#$%&\'()*+,-./:;<=>?@[\\]^_`{|}~ ";

//---------PROTOTYPES---------
void test();
char *gen_string(int length);
int fitness(char *source, char *target);

/* We need to keep keys and values */
typedef struct candidate{
  char* dna;
  int fitness;
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
    int fitval = fitness(rand_dna, target); //TODO: get from fitness function
    candidate new_cand = {rand_dna, fitval}; //create a new candidate
    genepool[i] = new_cand; //add candidate to gene pool    
    printf("%s, %d\n", genepool[i].dna, genepool[i].fitness); //DEBUG
  }

  fitness("TESTaa", "TESTzz"); //TEMP TODO: delete

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

int fitness(char *source, char *target){
  //Calculates the difference between the source and target strings
  int fitval = 0;
  for(int i = 0; i < strlen(target); i++){
    int curr_fitval = abs(source[i] - target[i]);
    fitval += curr_fitval;
    //printf("source = %c | target = %c | diff = %d\n", source[i], target[i], curr_fitval);
  }
  //printf("TOTAL fitval = %d\n", fitval);
  return fitval;
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
