import random
import string

GENESIZE = 20
TARGET = "Hello, World!"

# CROSSOVER_PROB = 100 # TODO: Introduce cross over probability
PARENT1_PROB = 50 # so, parent2_prob = 100 - PARENT1_PROB
MUTATION_PROB = 100
FIT_PARENT_PROB = 100

def get_fitness(dna):
    fitness = 0;
    for i in range(len(TARGET)):
        fitness += abs(ord(TARGET[i]) - ord(dna[i]))
    return fitness
    
# Mutation operation to determine how random deviations manifest themselves
def mutate(parent1, parent2):
    
    # Crossover operation to determine how parents combine to produce offspring
    
    # OPTION 1
    #----------------------------
    
    # Re-structured crossover section to avoid chance of total clones
    # between parent 1 and child
    
    # child_dna = ''
    # pos = (random.randint(1, len(parent1['dna']) ))
    # 
    # child_dna1 = parent1['dna'][:pos] + parent2['dna'][pos:]
    # child_dna2 = parent2['dna'][:pos] + parent1['dna'][pos:]
    # 
    # if (get_fitness(child_dna1) > get_fitness(child_dna2)):
    #     child_dna = child_dna1
    # else:
    #     child_dna = child_dna2
    
    # OPTION 2
    #----------------------------
        
    child_dna = parent1['dna'][:]    
    
    start = random.randint(1, len(parent2['dna']) - 1)
    end = random.randint(2, len(parent2['dna']) - 1)
    
    if start > end:
       end, start = start, end
    child_dna[start:end] = parent2['dna'][start:end]
    
    # OPTION 3
    #----------------------------
    
    # Re-structured crossover section to avoid chance of total clones
    # between parent 1 and child
    
    # child_dna = []
    # 
    # for i in range(len(parent1['dna'])):
    #     
    #     if (random.randint(0, 100) < PARENT1_PROB):
    #         # get current character from parent1
    #         child_dna.append(parent1['dna'][i])
    #         print(parent1['dna'][i])
    #         
    #     else:
    #         # get character from parent2
    #        child_dna.append(parent2['dna'][i])
            
    # print(str(''.join(child_dna)))
    
    # Mutation operation: Do so only according to the probability set for this purpose
    if (random.randint(0, 100) < MUTATION_PROB):
        # mutate one position
        index_to_mutate = random.randint(0, len(child_dna) - 1)    
        # mutation only affects fitness by 5 points max
        child_dna[index_to_mutate] = chr(ord(child_dna[index_to_mutate]) + random.randint(-5,5))
    
    child_fitness = get_fitness(child_dna)
    
    return ({'dna': child_dna, 'fitness': child_fitness})
    
def get_rand_parent(genepool):
    
    # Re-structured so that parents with lower fitness have *some* chance of getting picked
    rand_index = 0
    if (random.randint(0, 100) < FIT_PARENT_PROB):
        # rand_index = random.randint(0, GENESIZE/2)
        rand_index = int(random.random() * random.random() * ((GENESIZE/2) - 1)) # uniform product distribution
    else:
        rand_index = random.randint(GENESIZE/2, GENESIZE - 1)

    # Selection method to determine how parents are selected for breeding from population
    #rand_index = int(random.random() * random.random() * ((GENESIZE/2) - 1))
    return (genepool[rand_index])
    
def seed_population():
    
    genepool = []
    
    # generate 20 random candidates to populate the genepool
    for i in range (GENESIZE):
        # printable: string constant. combination of digits, letters, punctuation, and whitespace.
        # note: a more secure version could be random.SystemRandom()
        dna = [random.choice(string.printable[:-5]) for _ in range(len(TARGET))]
        fitness = get_fitness (dna)
        candidate = {'dna': dna, 'fitness': fitness}
        # print (candidate)
        genepool.append(candidate)
        
    return genepool

def run():
    
    genepool = seed_population()
    
    # initialize first iteration
    generation = 0
    
    while True:
        
        generation += 1
        # sort genepool by fitness
        genepool.sort(key=lambda candidate: candidate['fitness'])
        
        # for candidate in genepool:
        #     print ("%6i, %6i, %15s" % (generation, candidate['fitness'], ''.join(candidate['dna'])))
        
        # print ("%6i, %6i, %15s" % (generation, genepool[0]['fitness'], ''.join(genepool[0]['dna'])))
                    
        # if the best fitness is 0, TARGET was reached
        if (genepool[0]['fitness'] == 0):
            #print("TARGET was reached in generation "+ str(generation) +"!")
            #break
            
            return generation
        
        # otherwise, keep on breeding
        parent1 = get_rand_parent(genepool)
        parent2 = get_rand_parent(genepool)
        
        while (parent1['dna'] == parent2['dna']):
            parent1 = get_rand_parent(genepool) # doesn't matter which one we pick - they are the same
        
        child = mutate(parent1, parent2)

        # if the child's fitness is better than the one of the current worst, then replace
        if (child['fitness'] < genepool[(len(genepool) - 1)]['fitness']):
            genepool[(len(genepool) - 1)] = child
    
if __name__ == "__main__":
        
    times_to_run = 1000
    results = []
    
    for i in range(times_to_run):
        print(str(i))
        results.append(run())
    
    print("Average: " + str(sum(results) / float(len(results))))
            