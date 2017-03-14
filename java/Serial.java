import java.util.Random;
import java.util.List;
import java.util.ArrayList;
import java.util.*;
import java.lang.*;

public class Serial {
    
    public static int GENESIZE = 20;
    public static String TARGET = "Hello, World!";
    
    // public static int CROSSOVER_PROB = 100 // TODO: Introduce cross over probability
    public static int PARENT1_PROB = 50; // so, parent2_prob = 100 - PARENT1_PROB
    public static int MUTATION_PROB = 100;
    public static int FIT_PARENT_PROB = 100;

    public static void getFitness(String dna) {
        
    }
    
    public static void mutate(Candidate parent1, Candidate parent2) {

    }
    
    public static Candidate getRandParent(List<Candidate> genepool) {
        
        return null;
    }
    
    public static List<Candidate> seedPopulation() {
        
        
    
        return null;
    }

    public static int run() {
        
        int generation = 0;
        //List<Candidate> genepool = seedPopulation();
        
                
        return 1;
    }

    public static void main(String[] args) {
        
        int sum = 0;
        int timesToRun = 1;
        
        for (int i = 0; i < timesToRun; i ++) {
            System.out.println(i);
            sum += run();
        }
        
        // System.out.println("Average: " + (float) sum/timesToRun);
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
        System.out.println("dna: " + this.getDna() + ", fitness: " + this.getFitness());
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