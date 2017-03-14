import random
import string

def main():
    print("Hello Simple GA")

    run_my_simple()
    #test()
    
    
def run_my_simple():
    #Init all the necessary variables
    i = 0
    #source  = "dawdddawdawds"
    target  = "Hello, World!"
    source = gen_source(len(target))
    fitval = my_fitness(source, target)

    while True:
        i += 1
        mutant = mutate(source)
        new_fitval = my_fitness(mutant, target)
        if(new_fitval < fitval):            
            fitval = new_fitval
            source = mutant
            print(i, fitval, source)
        if(fitval == 0):
            break
    

    #test()    

def gen_source(length):
    return "".join([random.choice(string.printable[:-5]) for _ in range(length)])
    
def my_fitness(source, target):
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

def my_mutate(tomutate):
    #Has a 30% chance to randomly change a character to any character in the asci letters
    
    #Create a
    chance = 1.00 #the percent chance that a character is likely to mutate
    roll = random.uniform(0,1) #roll the dice, generates a random # from 0-1
    #Check to see if we are within the given range
    if(roll <= chance):
        randIndex = random.randint(0, len(tomutate) - 1) #generate random index
        #randChar = random.choice(string.ascii_letters + " ") #generate a random character
        randChar = random.choice(string.printable[:-5]) #generate a random character
        tomutate = list(tomutate) #turn the string into a list
        tomutate[randIndex] = randChar #replace the existing char with the random one
        tomutate = "".join(tomutate) #make it into a string again
    #print(tomutate)
    return tomutate

def mutate(source):
   charpos = random.randint(0, len(source) - 1)
   parts = list(source)
   parts[charpos] = chr(ord(parts[charpos]) + random.randint(-10,10))
   return(''.join(parts))

def test():
    print("test() called")

    #Testing fitness function
    source  = "dawdddawdaw"
    target  = "Hello World"
    fitness_val = my_fitness(source, target)
    #print(fitness_val)

    #Testing the mutate function
    #print(mutate("aaaaaa"))#len6

    print(gen_source(len("adwaddaadwadw")))
    
main()
