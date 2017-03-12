import random
import string

target = "Hello, World!"

# crossover_prob = 30 # TODO: Introduce cross over probability
mutation_prob = 100

GENSIZE = 20
genepool = []

def get_fitness(dna):
    fitness = 0;
    for i in range(len(target)):
        fitness += abs(ord(target[i]) - ord(dna[i]))
    return fitness
    
# Mutation operation to determine how random deviations manifest themselves
def mutate(parent1, parent2):
    
    # Crossover operation to determine how parents combine to produce offspring
    
    # Re-structured crossover section to avoid chance of total clones
    # between parent 1 and child
    
    child_dna = ""
    pos = (random.randint(0, len(parent1['dna']) ))
    
    child_dna1 = parent1['dna'][:pos] + parent2['dna'][pos:]
    child_dna2 = parent2['dna'][:pos] + parent1['dna'][pos:]
    
    if (get_fitness(child_dna1) > get_fitness(child_dna2)):
        child_dna = child_dna1
    else:
        child_dna = child_dna2
    
    #child_dna = parent1['dna'][:]    
    #start = random.randint(0, len(parent2['dna']) - 1)
    #stop = random.randint(0, len(parent2['dna']) - 1)
    #if start > stop:
    #    stop, start = start, stop
    #child_dna[start:stop] = parent2['dna'][start:stop]
    
    # mutate only according to the probability set for this purpose
    if (random.randint(0, 100) < mutation_prob):
        # mutate one position
        index_to_mutate = random.randint(0, len(child_dna) - 1)    
        # mutation only affects fitness by 5 points max
        child_dna[index_to_mutate] = chr(ord(child_dna[index_to_mutate]) + random.randint(-5,5))
    
    child_fitness = get_fitness(child_dna)
    
    return ({'dna': child_dna, 'fitness': child_fitness})
    
def get_rand_parent():
    
    #Re-structured so that parents with lower fitness have *some* chance of getting picked

    # Selection method to determine how parents are selected for breeding from population
    rand_index = int(random.random() * random.random() * ((GENSIZE/2) - 1))
    return (genepool[rand_index])
    
def seed_population():
    # generate 20 random candidates to populate the genepool
    for i in range (GENSIZE):
        # printable: string constant. combination of digits, letters, punctuation, and whitespace.
        # note: a more secure version could be random.SystemRandom()
        dna = [random.choice(string.printable[:-5]) for _ in range(len(target))]
        fitness = get_fitness (dna)
        candidate = {'dna': dna, 'fitness': fitness}
        print (candidate)
        genepool.append(candidate)

if __name__ == "__main__":
    
    seed_population()
    
    # initialize first iteration
    generation = 0    
    
    while True:
        generation += 1
        # sort genepool by fitness
        genepool.sort(key=lambda candidate: candidate['fitness'])
        
        #for candidate in genepool:
        #    print ("%6i, %6i, %15s" % (generation, candidate['fitness'], ''.join(candidate['dna'])))
        
        print("Fittest string: " + str(''.join(genepool[0]['dna'])) + ", fitness: " + str(genepool[0]['fitness']))
            
        # if the best fitness is 0, target was reached
        if (genepool[0]['fitness'] == 0):
            print("Target was reached in generation "+ str(generation) +"!")
            break
        
        # otherwise, keep on breeding
        parent1 = get_rand_parent()
        parent2 = get_rand_parent()
        child = mutate(parent1, parent2)

        # if the child's fitness is better than the one of the current worst, then replace
        if (child['fitness'] < genepool[(len(genepool) - 1)]['fitness']):
            genepool[(len(genepool) - 1)] = child