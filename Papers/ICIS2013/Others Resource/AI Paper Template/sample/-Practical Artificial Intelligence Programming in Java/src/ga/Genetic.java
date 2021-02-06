// Genetic Algorithm Java classes
//
// Copyright 1996, Mark Watson.  All rights reserved.

import java.util.*;

abstract public class Genetic {

   protected int numGenesPerChromosome;  // number of genes per chromosome
   protected int numChromosomes;  // number of chromosomes
   private BitSet chromosomes[];
   protected float fitness[];
   private float crossoverFraction;
   private float mutationFraction;
   private int [] rouletteWheel;
    private int rouletteWheelSize;

   public Genetic(int num_genes_per_chromosome, int num_chromosomes) {
       this(num_genes_per_chromosome, num_chromosomes, 0.8f, 0.01f);
   }
   public Genetic(int num_genes_per_chromosome, int num_chromosomes,
		  float crossover_fraction, float mutation_fraction) {
       numGenesPerChromosome = num_genes_per_chromosome;
       numChromosomes = num_chromosomes;
       crossoverFraction = crossover_fraction;
       mutationFraction = mutation_fraction;
       chromosomes = new BitSet[num_chromosomes];
       for (int i=0; i<num_chromosomes; i++) {
          chromosomes[i] = new BitSet(num_genes_per_chromosome);
          for (int j=0; j<num_genes_per_chromosome; j++) {
             if (Math.random() < 0.5) chromosomes[i].set(j);
          }
       }
       fitness = new float[num_chromosomes];
       for (int f=0; f<num_chromosomes; f++)  {
         fitness[f] = -999;
       }
       sort();
       // define the roulette wheel:
       rouletteWheelSize = 0;
       for (int i=0; i<numGenesPerChromosome; i++) {
	   rouletteWheelSize += i + 1;
       }
       System.out.println("count of slots in roulette wheel=" + rouletteWheelSize);
       rouletteWheel = new int[rouletteWheelSize];
       int num_trials = numGenesPerChromosome;
       int index = 0;
       for (int i=0; i<numGenesPerChromosome; i++) {
	   for (int j=0; j<num_trials; j++) {
	       rouletteWheel[index++] = i;
	   }
	   num_trials--;
       }
   }
    public boolean getGene(int chromosome, int gene) {
       return chromosomes[chromosome].get(gene);
    }
    public void setGene(int chromosome, int gene, int value) {
        if (value == 0)  chromosomes[chromosome].clear(gene);
        else             chromosomes[chromosome].set(gene);
    }
    public void setGene(int chromosome, int gene, boolean value) {
        if (value)  chromosomes[chromosome].set(gene);
        else        chromosomes[chromosome].clear(gene);
    }
    public void sort() {
       BitSet btemp;
       for (int c=0; c<numChromosomes; c++) {
           for (int d=(numChromosomes - 2); d>=c; d--) {
                if (fitness[d] < fitness[d+1]) {
                   btemp = chromosomes[d];
                   float x = fitness[d];
                   chromosomes[d] = chromosomes[d+1];
                   fitness[d] = fitness[d+1];
                   chromosomes[d+1] = btemp;
                   fitness[d+1] = x;
                }
            }
        }
    }
    public void evolve() {
	calcFitness();
	sort();
	doCrossovers();
	doMutations();
	doRemoveDuplicates();
    }
    public void doCrossovers()  {
      int num = (int)(numChromosomes * crossoverFraction);
      for (int i=num-1; i>=0; i--) {
	  int c1 = (int)(rouletteWheelSize * Math.random() * 0.9999f);
	  int c2 = (int)(rouletteWheelSize * Math.random() * 0.9999f);
	  c1 = rouletteWheel[c1];
	  c2 = rouletteWheel[c2];
	  if (c1 != c2) {
	      int locus = 1 + (int)((numGenesPerChromosome - 2) * Math.random());
	      for (int g=0; g<numGenesPerChromosome; g++) {
		  if (g < locus) {
		      setGene(i, g, getGene(c1, g));
		  } else {
		      setGene(i, g, getGene(c2, g));
		  }
	      }
	  }
      }
    }
    // 'to' and 'from' are 'sorted' indices:
    private void copyGene(int to, int from) {
       for (int i=0; i<numGenesPerChromosome; i++)
            if (getGene(from, i))  setGene(to, i, 1);
            else                   setGene(to, i, 0);
    }
    public void doMutations() {
      int num = (int)(numChromosomes * mutationFraction);
      for (int i=0; i<num; i++) {
	  int c = (int)(numChromosomes * Math.random() * 0.99);
	  int g = (int)(numGenesPerChromosome * Math.random() * 0.99);
	  setGene(c, g, !getGene(c, g));
      }
    }
    public void doRemoveDuplicates() {
	for (int i=numChromosomes - 1; i>3; i--) {
	    for (int j=0; j<i; j++) {
		if (chromosomes[i].equals(chromosomes[j])) {
		    int g = (int)(numGenesPerChromosome * Math.random() * 0.99);
		    setGene(i, g, !getGene(i, g));
		    break;
		}
	    }
	}
    }
    // Override the following function in sub-classes:
    abstract public void calcFitness() ;
}
