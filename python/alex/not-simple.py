import random
import string
from functools import reduce

alphabet=string.printable[:-5]

def main():
    #run_alg(True) #True means we want debugging(printing) enabled
    benchmark_alg(100) #Run the alg 10 times and get the average: 1000 RUNS = 1352.591

def benchmark_alg(num_runs):
    #Runs the algorithm num_run times and get the average number of generations it took
    generations_count = list()

    #Run the algorithm num_runs amount of times
    for i in range(0, num_runs):
        curr_generation_count = run_alg(False)
        generations_count.append(curr_generation_count)
        print("Run#",i, " Generations:", curr_generation_count)

    #calculate the average for the results
    avg = reduce(lambda x,y: x+y, generations_count) / len(generations_count)
    print("Average generations = ", avg)
    
def run_alg(debug):
    GENE_POOL_SIZE = 10
    
    target = "Hello, World!"
    target_length = len(target)    
    # target_length = 10
    # target = gen_string(target_length);

    #Create the genepool
    genepool = list()
    for i in range(0, GENE_POOL_SIZE):
        new_dna = gen_string(target_length)
        new_fitval = fitness(new_dna, target)
        new_person = {"dna":new_dna, "fitness":new_fitval}
        #print(new_dna, new_fitval)
        genepool.append(new_person);
       
    #test()
    ##Main Loop
    generation = 0
    while True:
        generation += 1
        genepool.sort(key=lambda person: person["fitness"])

        #Comment one of these out
        #if debug: print(generation, genepool[0])
        if debug: debug_by_generation(genepool, generation) #for debugging
        
        if genepool[0]["fitness"] == 0:
            #Target Reached
            if debug: print("TARGET =", target)
            return generation
        else:
            #Select two random parents
            parent1 = random_parent(genepool, GENE_POOL_SIZE)
            parent2 = random_parent(genepool, GENE_POOL_SIZE)

            #make a baby ;)
            child_dna = crossover_dna(parent1["dna"], parent2["dna"])
            child = {"dna": child_dna, "fitness":fitness(child_dna, target)}

            #Check if the child is better than the worst person in the genepool
            if(child["fitness"] < genepool[-1]["fitness"]):
                genepool[-1] = child
                                   
def test():
    print("test() called")
    #print(random.uniform(-1,1))
    crossover_dna("aaaa", "bbbb")

#--------------MAIN FUNCTIONS------------

def random_parent(genepool, GENE_SIZE):
    random_index = int(random.random() * random.random() * (GENE_SIZE - 1))
    return genepool[random_index]
    

def crossover_dna(parent1, parent2):
    child_dna = list(parent1)

    #Bix both DNAs
    start = random.randint(0, len(parent2) -1)
    stop = random.randint(0, len(parent2) - 1)
    if start > stop:
        stop, start = start, stop
    
    child_dna[start:stop] = list(parent2)[start:stop]
    child_dna = "".join(child_dna)

    child_dna = mutate_single_dna(child_dna)
    return child_dna

def my_crossover_dna(parent1, parent2):
    #Mix both parent's dna so that it's a combination of both
    parent1_list = list(parent1)
    parent2_list = list(parent2)
    child = list()
    #Each child's char has a 50/50 chance to be either parent1 or parent2
    for i, ele in enumerate(parent1_list):
        chance = random.uniform(-1, 1)
        if(chance >=0):
            child.append(parent1_list[i])
        else:
            child.append(parent2_list[i])
    child = "".join(child)

    #finally mutate the child
    mutant_child = mutate_single_dna(child)
    
    return mutant_child

def mutate_single_dna(source):
   charpos = random.randint(0, len(source) - 1)
   parts = list(source)
   parts[charpos] = chr(ord(parts[charpos]) + random.randint(-10,10))
   return(''.join(parts))    
    
def fitness(source, target):
    debug = False
    if debug: print("my_fitness() called")
    #both source and target must be the same length
    fitness = 0 #init the fitness to be 0
    for i in range(0, len(source)): #for every character in source/target
        #calcualte the diff b/w source and target characters
        curr_fitness = abs(ord(source[i]) - ord(target[i])) 
        if debug: print(source[i], target[i], curr_fitness)
        #add the difference to the total fitness
        fitness += curr_fitness
    if debug: print("Total Fitness =", fitness)
    return fitness
    
    
def gen_string(length):
    #generates a random string from the given parameter length
    return "".join([random.choice(alphabet) for _ in range(length)])

#--------------OTHER UTIL FUNCTIONS------------

def debug_by_generation(genepool, generation):
    print("GENERATION", generation)
    for person in genepool:
        print(person["dna"], person["fitness"])
    input("...")

#test()
main()
