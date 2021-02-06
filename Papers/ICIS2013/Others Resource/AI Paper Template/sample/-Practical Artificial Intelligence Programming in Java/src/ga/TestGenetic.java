// File: textGenetic.java
// This file contains a text-mode test program
// for class Genetic.

public class TestGenetic {

    static MyGenetic g;

    static public void main(String args[]) {
        // we will use chromosomes with 10 1 bit genes per
        // chromosomes, and a population of 12 chromosomes:
        g = new MyGenetic(10, 30, 0.85f, 0.2);
        for (int i=0; i<21; i++) {
            g.evolve();
            //g.calcFitness();
            //if ((i%5)==0) {
            System.out.println("Generation " + i);
            g.print();
            //}
        }
    }
}

class MyGenetic extends Genetic {
    MyGenetic(int num_g, int num_c, float crossover_fraction,
              float mutation_fraction) {
        super(num_g, num_c, crossover_fraction, mutation_fraction);
    }
    private float fitness(float x) {
        return (float)(Math.sin(x) * Math.sin(0.4f * x) * Math.sin(3.0f * x));
    }
    float geneToFloat(int geneIndex) {
        int base = 1;
        float x = 0;
        for (int j=0; j<numGenesPerChromosome; j++)  {
            if (getGene(geneIndex, j)) {
                x += base;
            }
            base *= 2;
        }
        x /= 128.0f;
        return x;
    }
    public void calcFitness() {
        for (int i=0; i<numChromosomes; i++) {
            float x = geneToFloat(i);
            fitness[i] = fitness(x);
        }
    }
    public void print() {
        sort();
        int maxindex = 0;
        float maval = 0.0f;
        float sum = 0.0f;
        for (int i=0; i<numChromosomes; i++) {
            float x = geneToFloat(i);
            sum += fitness[i];
            if (i < 6) {
                System.out.print("Fitness for chromosome ");
                System.out.print(i);
                System.out.print(" is ");
                System.out.println(fitness[i] + ", occurs at x=" + x);
            }
        }
        sum /= (float)numChromosomes;
        System.out.println("Average fitness=" + sum);
    }
}
