import java.util.Random;
import java.util.List;
import java.util.ArrayList;
import java.util.*;
import java.lang.*;
import java.util.concurrent.TimeUnit;

public class ParallelTime {
    public static int NUM_THREADS;
    public static int MAX_THREADS;
    public static Candidate best_child;
    
    public static int GENESIZE = 20;
    public static String TARGET = "Hello, World!";
    public static int TARGET_LEN;
    
    // public static int CROSSOVER_PROB = 100 // TODO: Introduce cross over probability
    public static int PARENT1_PROB = 50; // so, parent2_prob = 100 - PARENT1_PROB
    public static int MUTATION_PROB = 100;
    public static int FIT_PARENT_PROB = 100;

    public static float getFitness(String dna) {
        
        float fitness = 0;
        for (int i = 0; i < TARGET.length(); i++) {
            fitness += Math.abs((int)TARGET.charAt(i) - (int)dna.charAt(i));
        }
    
        return fitness;
    }
    
    public static Candidate mutate(Candidate parent1, Candidate parent2) {
        
        // Crossover
        String childDna = parent1.getDna();
        
        Random rand = new Random();
        int start = rand.nextInt(parent1.getDna().length()-1) + 1;
        int end = rand.nextInt(parent1.getDna().length()-2) + 2;

        if (start > end) {
            int tmp = start;
	    start = end;
	    end = tmp;
        }
        
        childDna = childDna.substring(0, start) + parent2.getDna().substring(start, end+1) + childDna.substring(end+1, childDna.length());
        
        // Mutation
        if (rand.nextInt(100) < MUTATION_PROB) {
            int indexToMutate = rand.nextInt(childDna.length());
            
            // String myName = "domanokz   ";
            char[] childDnaChars = childDna.toCharArray();
            childDnaChars[indexToMutate] = (char) ((int) childDnaChars[indexToMutate] + (rand.nextInt(10) - 5));
            childDna = String.valueOf(childDnaChars);
        }
        
        float childFitness = getFitness(childDna);

        return new Candidate(childDna, childFitness);
    }
    
    public static Candidate getRandParent(List<Candidate> genepool) {
        
        int randIndex = 0;
        Random rand = new Random();
        
        if (rand.nextInt(100) < FIT_PARENT_PROB) {
            randIndex = Math.round (rand.nextFloat() * rand.nextFloat() * ((GENESIZE/2) - 1));
        } else {
            randIndex = Math.round (rand.nextInt(GENESIZE/2) + GENESIZE/2);
        }
        
        return genepool.get(randIndex);
    }
    
    public static List<Candidate> seedPopulation() {
        
        List<Candidate> genepool = new ArrayList<Candidate>();
        
        for (int i = 0; i < GENESIZE; i++) {
	    String dna = gen_rand_string(TARGET.length());
            float fitness = getFitness(dna);
        
            genepool.add(new Candidate(dna, fitness));
        }

        return genepool;
    }

        public static String gen_rand_string(int length){
	String randString = "";
	Random rand = new Random();
	for(int i = 0; i < length; i++){
	    randString += (char)(rand.nextInt(95) + 31);
	}	
	return randString;
    }

    public static int run()throws Exception{
        ParallelTime.best_child = new Candidate(null, Integer.MAX_VALUE);
        int generation = 0;
        List<Candidate> genepool = seedPopulation();

        // for (Candidate c : genepool)
        //     c.print();
            
        while (true) {
            
            generation++;
            
            Collections.sort(genepool);
            
            //System.out.println (generation + " " + genepool.get(0).getFitness() + " " + genepool.get(0).getDna());
            
            if (genepool.get(0).getFitness() == 0) {
                //System.out.println("Found target at generation " + generation);
                return generation;
            }

	    //MyThread[] threads = new MyThread[ParallelTime.NUM_THREADS];
	    //Run the threads
	    for(int i = 0; i < ParallelTime.NUM_THREADS; i++){
		MyThread temp = new MyThread(""+i, genepool);
		temp.start();
		temp.join();
	    }
	    
            
            if (ParallelTime.best_child.getFitness() < genepool.get(GENESIZE - 1).getFitness())
                genepool.set(GENESIZE - 1, ParallelTime.best_child);
        }
    }

    public static void main(String[] args) throws Exception{
	Long start, end;
	int runs_per_thread_iter = 100;
	int MAX_TARGET_LEN = 15;
	ParallelTime.NUM_THREADS = 2;	
	ParallelTime.TARGET = "";	    
	
	System.out.println("LENGTH, # GENERATIONS (%" + runs_per_thread_iter +" avg)" + ", Time(microsec)");

	//for(ParallelTime.NUM_THREADS = 1; ParallelTime.NUM_THREADS <= ParallelTime.MAX_THREADS; ParallelTime.NUM_THREADS++){
	for(ParallelTime.TARGET_LEN = 3; ParallelTime.TARGET_LEN <= MAX_TARGET_LEN; ParallelTime.TARGET_LEN++){
	    ParallelTime.TARGET = gen_rand_string(ParallelTime.TARGET_LEN);
	    int sum = 0;
	    Double totalTime = new Double(0);
        
	    for (int i = 0; i < runs_per_thread_iter; i ++) {
		//System.out.println("Run #: " + i);
		start = System.nanoTime();
		sum += run();
		end = System.nanoTime();
		totalTime += (end-start)/1000.0;
	    }

	    double avg_generations = (double)sum/runs_per_thread_iter;
	    double avg_elapsed_time = totalTime/runs_per_thread_iter;
	    System.out.println(String.format("%d,%.2f,%.2f", ParallelTime.TARGET_LEN, avg_generations, avg_elapsed_time));
	}
    }
}

class Candidate implements Comparator<Candidate>, Comparable<Candidate> {
    
    private String dna;
    private float fitness;
    
    public Candidate() {
        this.dna = "";
        this.fitness = 0;
    }
    
    public Candidate(String dna, float fitness) {
        this.dna = dna;
        this.fitness = fitness;
    }
    
    public void print() {
        System.out.println( this.getFitness() + " --> " + this.getDna());
    }
    
    public void setDna(String dna) { this.dna = dna; }
    public void setFitness(float fitness) { this.fitness = fitness; }
    public String getDna() { return this.dna; }
    public float getFitness() { return this.fitness; }
    
    // Overriding the compareTo method
    @Override
    public int compareTo(Candidate c) {
        
        if (c.getFitness() < this.fitness) return 1;
        else if (c.getFitness() > this.fitness) return -1;
        return 0;
    }

    // Overriding the compare method to sort the age 
    @Override
    public int compare(Candidate c1, Candidate c2) {
        
        //ascending order
        return c1.compareTo(c2);
        
        //descending order
        //return c2.compareTo(c1);
    }
}

class MyThread extends Thread{
    List<Candidate> genepool;

    MyThread(String name, List<Candidate> genepool){
	super(name);
	this.genepool = genepool;
    }

    public void run(){
	Candidate parent1 = ParallelTime.getRandParent(this.genepool);
	Candidate parent2 = ParallelTime.getRandParent(this.genepool);
            
	// while (parent1.getDna().equals(parent2.getDna()))
	//     parent1 = getRandParent(genepool);
    
	Candidate child = ParallelTime.mutate(parent1, parent2);

	synchronized(ParallelTime.best_child){
	    if(child.getFitness() < ParallelTime.best_child.getFitness()){
		ParallelTime.best_child = child;
	    }
	}	
	//System.out.println("Running thread:" + this.getName());
    }
}
