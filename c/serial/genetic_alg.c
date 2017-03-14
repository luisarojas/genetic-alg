#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

const char *ALPHABET = "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ!\"#$%&\'()*+,-./:;<=>?@[\\]^_`{|}~ ";

/* We need to keep keys and values */
typedef struct{
  char* dna;
  int fitness;
} candidate;

//---------PROTOTYPES---------
void test();
char *gen_string(int length);
int fitness(char *source, char *target);
int candidate_comparitor(const void *arg1, const void *arg2);
candidate get_rand_parent(candidate genepool[], int GENE_POOL_SIZE);
void print_candidate(candidate cand);
char *my_crossover_dna(candidate parent1, candidate parent2);
void *mutate_single_dna(char *source);

//---------MAIN---------
int main() {
  srand(time(NULL)); //Seed the random time
  char *target = "Hello, World!"; //Set the target
  int target_len = strlen(target); //Get target length
  const int GENE_POOL_SIZE = 10; //Set the size of the gene pool

  //Generate the gene pool
  candidate genepool[GENE_POOL_SIZE];
  for(int i = 0; i < GENE_POOL_SIZE; i++){
    //genepool[i] = gen_string(target_len); //generate random string
    char *rand_dna = gen_string(target_len); //create a random dna
    int fitval = fitness(rand_dna, target); //TODO: get from fitness function
    candidate new_cand = {rand_dna, fitval}; //create a new candidate
    genepool[i] = new_cand; //add candidate to gene pool    
  }

  //TODO: Infinite While Loop
  int generation = 0;
  while(1){
    generation++;
    //Sort the genepool by fitness
    qsort(genepool, GENE_POOL_SIZE, sizeof(candidate), candidate_comparitor);
    printf("[GEN %d] ", generation); print_candidate(genepool[0]); //DEBUGING

    if(genepool[0].fitness == 0){
      //Target Reached
      printf("TARGET = %s\n", target);
      break;
    }else{
      //Select two random parents
      candidate parent1 = get_rand_parent(genepool, GENE_POOL_SIZE);
      candidate parent2 = get_rand_parent(genepool, GENE_POOL_SIZE);

      //Create child by corssing over the two parents
      char *child_dna = my_crossover_dna(parent1, parent1);
      int child_fitval = fitness(child_dna, target);
      candidate child = {child_dna, child_fitval};
      //printf("CHILD: "); print_candidate(child);

      //Check if the child is better than the worst person in the genepool
      candidate lowest_cand = genepool[GENE_POOL_SIZE -1 ];
      if(child.fitness < lowest_cand.fitness){
	genepool[GENE_POOL_SIZE -1 ] = child;
      }
    }
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

candidate get_rand_parent(candidate genepool[], int GENE_POOL_SIZE){
  const int FIT_PARENT_PROB = 90;
  
  int rand_index = 0;
  float random_float = (float)rand()/(float)RAND_MAX; //Random float 0-1
  rand_index = random_float * (GENE_POOL_SIZE/2); //Random int from: 0 - (GENE_POOL_SIZE - 1)
  
  if(rand()% 100 >= FIT_PARENT_PROB){
    rand_index += (GENE_POOL_SIZE/2);
  }
  //printf("rand_index = %d\n", rand_index);
  return genepool[rand_index];
}

void print_candidate(candidate cand){
  printf("%s : [%d] \n", cand.dna, cand.fitness);
}

char *my_crossover_dna(candidate parent1, candidate parent2){
  int length = strlen(parent1.dna);
  char *child = (char *) malloc(length);
  for(int i = 0; i < length; i++){
    int chance = rand() % 2; //50-50 chance
    if(chance == 1){
      child[i] = parent1.dna[i];
    }else{
      child[i] = parent2.dna[i];      
    }
  }

  mutate_single_dna(child);
  //printf("%s\n", child);
  return child;
}

void *mutate_single_dna(char *source){
  int rand_i = rand()%strlen(source);
  source[rand_i] = source[rand_i] + (rand()%20 - 10);
}

//---------CANDIDATE COMPARITOR---------
int candidate_comparitor(const void *arg1, const void *arg2){
  const candidate *c1 = (candidate *)arg1;
  const candidate *c2 = (candidate *)arg2;
  if(c1->fitness < c2->fitness){
    return -1;
  }else if(c1->fitness > c2->fitness){
    return 1;
  }else{
    return 0;
  }  
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
