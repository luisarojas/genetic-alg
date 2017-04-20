# Parallel Genetic Algorithm

### Proposal

Our proposal consists on implementing and parallelizing a genetic algorithm.
We will generate a final solution, which the program will reach based on different generated parameters and transformations. Some of these will include a fitness criterion, as well as a mutation, a migration and a cross-over process.

The parent selection and crossover processes will be modified to enable parallelization and optimize execution. Both global single-population and multi-population approaches will be considered for further parallelization.

Since there are multiple unknowns in the scope of the project, we will approach it by implementing a serial genetic algorithm program in Python first, and then mapping it over to a serial implementation in C or Java, and finally paralleling it using pthreads/java-concurrency.

After, run times between the sequential and parallelized program(s) will be compared and analyzed. The comparison will also involve times between varying number of threads for the parallel version of the program, which will be outlined in a report.

###Pseudocode
```
Generate Gene pool
    -> New random DNA (SAME)
    -> New fitness calculation (SAME)
    -> Append to genepool (SAME)
    
While (true)
    -> If the best fitness in the
       genepool is 0, break - found a match. (SAME)
    -> Get 2 random parents to generate a new
       child (Luisa's) ***
        o Crossover: Portions of BOTH parents' DNAs
          are combined into the child (Luisa's) ***
        o Mutation: Select a random character in the
          resulting child's DNA, and switch it to a
          different character in a change of 5,
          following its ASCII representation (SAME)
    -> If the resulting child has better fitness than
       the current worst in the genepool, replace it (SAME)
```


### Resources
- http://tracer.uc3m.es/tws/cEA/documents/cant98.pdf
- https://www.electricmonk.nl/log/2011/09/28/evolutionary-algorithm-evolving-hello-world/
- https://news.ycombinator.com/item?id=3047046
