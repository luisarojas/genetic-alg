#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define GENESIZE 20
#define MAX_CHAIN_LENGTH 1

char *target = "Hello, World!";

/* We need to keep keys and values */
typedef struct {
    char* dna;
    float fitness;
} candidate;

/* A hashmap has some maximum size and current size,
 * as well as the data to hold. */
typedef struct {
	int count;
	int size;
	candidate *cand;
} hashmap;

// int crossover_prob; // TODO: Introduce cross over probability
int mutation_prob;

//genepool[GENESIZE]; // TODO: need dictionary-like data structure for this

int rand_num(int range);

int main() {
    
    mutation_prob = 100;
    
    return 0;
}

int rand_num(int range) {
    srand(time(NULL));
    int r = rand() % range;
}

hashmap* hash_create(int start_size) {
    
    hashmap* hm = (hashmap*)malloc(sizeof(hashmap));

    hm->cand = (candidate*)calloc(sizeof(candidate), start_size);
    hm->size = start_size;
    hm->count = 0;

    return hm;
}