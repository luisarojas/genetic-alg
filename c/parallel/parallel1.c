#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <pthread.h>

// #define NUM_THREADS 2

const char *ALPHABET = "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ!\"#$%&\'()*+,-./:;<=>?@[\\]^_`{|}~ ";
const char *TARGET = "Hello, World!"; //Set the target
const int GENE_POOL_SIZE = 10; //Set the size of the gene pool
const int FIT_PARENT_PROB = 90;
const int MUTATION_PROB = 100;
int TARGET_LEN;

/* We need to keep keys and values */
typedef struct{
  char* dna;
  int fitness;
} candidate;

//---------PROTOTYPES---------
void test();
char *gen_string(int length);
int get_fitness(char *source);
int candidate_comparator(const void *arg1, const void *arg2);
candidate get_rand_parent(candidate genepool[]);
void print_candidate(candidate cand);
char *crossover(candidate parent1, candidate parent2);
void mutate(char *source);
int run();

//---------MAIN---------
int main() {

	TARGET_LEN = strlen(TARGET); //Get target length

	int times_to_run = 100;
	int sum = 0;

  for(int i = 0; i < times_to_run; i++) {
    int num_generations = run();
    sum += num_generations;
    //printf("Run #%d gens=%d\n", i, num_generations);
  }

  printf("Average: %.2f\n", ((double)sum/times_to_run));
}

int run() {
  srand(time(NULL)); //Seed the random time

  //Generate the gene pool
  candidate genepool[GENE_POOL_SIZE];
  for(int i = 0; i < GENE_POOL_SIZE; i++){
    //genepool[i] = gen_string(target_len); //generate random string
    char *rand_dna = gen_string(TARGET_LEN); //create a random dna
    int fitval = get_fitness(rand_dna);
    candidate new_cand = {rand_dna, fitval}; //create a new candidate
    genepool[i] = new_cand; //add candidate to gene pool
  }

  int generation = 0;
  while(1){
    generation++;
    //Sort the genepool by fitness
    qsort(genepool, GENE_POOL_SIZE, sizeof(candidate), candidate_comparator);
    //printf("[GEN %d] ", generation); print_candidate(genepool[0]); //DEBUGING

    if(genepool[0].fitness == 0){
      //Target Reached
      //printf("TARGET REACHED: \"%s\" in %d generations\n", TARGET, generation); //UNCOMMENT WHEN BENCHMARKING
      return generation;
    }else{
      //Select two random parents
      candidate parent1 = get_rand_parent(genepool);
      candidate parent2 = get_rand_parent(genepool);

      //Create child by corssing over the two parents
      char *child_dna = crossover(parent1, parent1);
      mutate(child_dna);
      int child_fitval = get_fitness(child_dna);
      candidate child = {child_dna, child_fitval};

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

int get_fitness(char *source){
  //Calculates the difference between the source and target strings
  int fitval = 0;
  for(int i = 0; i < strlen(TARGET); i++){
    int curr_fitval = abs(source[i] - TARGET[i]);
    fitval += curr_fitval;
    //printf("source = %c | target = %c | diff = %d\n", source[i], target[i], curr_fitval);
  }
  //printf("TOTAL fitval = %d\n", fitval);
  return fitval;
}

// Normalized + probability-sensitive selection from the two halves of the genepool
candidate get_rand_parent(candidate genepool[]){
  int rand_index = 0;
   if(rand()% 100 < FIT_PARENT_PROB) {
     double rand_double1 = (double)rand() / (double)RAND_MAX;
     double rand_double2 = (double)rand() / (double)RAND_MAX;
     rand_index = (int) (rand_double1 * rand_double2 * ((GENE_POOL_SIZE/2) -1));
   }else{
	  rand_index = (rand()%(GENE_POOL_SIZE/2)) + ((GENE_POOL_SIZE/2) -1);
   }
   return genepool[rand_index];
}

void print_candidate(candidate cand){
  printf("%s : [%d] \n", cand.dna, cand.fitness);
}

char *crossover(candidate parent1, candidate parent2){

	// make a copy of parent 1, as child_dna
	int length = strlen(parent1.dna);
  char *child_dna	= (char *) malloc(length);
  strcpy(child_dna, parent1.dna);

	// select start index for parent 2 to be inserted (1 to parent2 length -1)
	int start = (rand()%(length-1)) + 1;

	// select stop index for parent 2 to end insertion (2 to parent2 length -1)
  int end = (rand()%(length-2)) + 2;

	// if start > end, then invert them
	if (start > end) {
		int tmp = start;
		start = end;
		end = tmp;
	}

	// set the defined portion of the child_dna as the parent2 dna
	for(int i = start; i <= end; i++) {
    child_dna[i] = parent2.dna[i];
	}

  return child_dna;
}

void mutate(char *source){

	if(rand()% 100 < MUTATION_PROB) {
		int rand_i = rand()%strlen(source);
  	source[rand_i] = source[rand_i] + (rand()%20 - 10);
	}

}

//---------CANDIDATE COMPARATOR---------
int candidate_comparator(const void *arg1, const void *arg2){
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

void test() {
  printf("test() called\n");
}
