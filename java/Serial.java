import java.util.Random;
import java.util.List;
import java.util.ArrayList;

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
                
        return 1;
    }

    public static void main(String[] args) {
        
        int sum = 0;
        int timesToRun = 1000;
        
        for (int i = 0; i < timesToRun; i ++) {
            System.out.println(i);
            sum += run();
        }
        
        System.out.println("Average: " + (float) sum/timesToRun);
    }
}

class Candidate {
    
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
        System.out.println("DNA: " + this.dna + ", FITNESS: " + this.fitness);
    }
    
    public void setDna(String dna) { this.dna = dna; }
    public void setFitness(float fitness) { this.fitness = fitness; }
    public String getDna() { return this.dna; }
    public float getFitness() { return this.fitness; }
    
}