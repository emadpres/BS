// File: RegressionTest.java
// This file contains a text-mode test program
// for class Genetic for doing a polynomial regression test.

public class RegressionTest {

    static RegressionGenetic g;

    static public void main(String args[]) {
        // we will use chromosomes with 10 1 bit genes per
        // floating pouint number (20 bits for 5 numbers)
        // and a population of 100 chromosomes:
        g = new RegressionGenetic(30, 5000, 0.98f, 0.15f);
        System.out.println("calcNormalization(10)=" + g.calcNormalization(10));
        System.out.println("calcNormalization(20)=" + g.calcNormalization(20));
        System.out.println("calcNormalization(5)=" + g.calcNormalization(5));
        for (int i=0; i<501; i++) {
            g.evolve();
            if ((i%50)==0 || i < 8) {
                System.out.println("Generation " + i);
                g.print();
            }
        }
        System.out.println("gmin="+RegressionGenetic.gmin+", gmax="+RegressionGenetic.gmax);
    }
}

class RegressionGenetic extends Genetic {
    RegressionGenetic(int num_g, int num_c, float crossover_fraction,
                      float mutation_fraction) {
        super(num_g, num_c, crossover_fraction, mutation_fraction);
        if ((num_g / 5)*5 != num_g) {
            System.out.println("Error, number of genes per chromosome must be evenly divisible by 5");
            System.exit(1);
        }
        bitsPerNumber = num_g / 5;
        normalization = calcNormalization(bitsPerNumber);
    }
    public float calcNormalization(int num_bits) {
        float base = 1.0f;
        float ret = 0.0f;
        for (int i=0; i<num_bits - 3; i++) {
            ret += base;
            base *= 2;
        }
        return base;
    }

    private int bitsPerNumber;
    private float normalization;
    private float calcFitnessForCoefficients(float [] coef) {
        float ret = 0.0f;
        // evaluate function error over a range of values of x:
        for (float x=0.0f; x<=10.0f; x+= 0.05) {
            // true value of regression function:
            float Ftrue = x*x*x*x + x*x*x + x*x + x;
            // value of generated function at x:
            float F = coef[0] * x*x*x*x +
                coef[1] * x*x*x +
                coef[2] * x*x +
                coef[3] * x +
                coef[4];
            //ret += (float)Math.sqrt((F - Ftrue) * (F - Ftrue));
            ret += (F - Ftrue) * (F - Ftrue);
        }
        return 25000.0f - ret;
    }
    public static float gmin = 10000000000.0f;
    public static float gmax = -gmin;
    float geneToFloat(int chromosomeIndex, int numberIndex) {
        int base = 1;
        float x = 0;
        for (int j=0; j<bitsPerNumber; j++)  {
            if (getGene(chromosomeIndex, j + numberIndex * bitsPerNumber)) {
                x += base;
            }
            base *= 2;
        }
        x /= normalization;
        x -= 5.0f;
        if (gmin > x) gmin = x;
        if (gmax < x) gmax = x;
        return x;
    }
    // more efficient to allocate this only once:
    private float [] coefficients = new float[5];
    public void calcFitness() {
        for (int i=0; i<numChromosomes; i++) {
            for (int j=0; j<5; j++) {
                coefficients[j] = geneToFloat(i, j);
            }
            fitness[i] = calcFitnessForCoefficients(coefficients);
        }
    }
    public void print() {
        sort();
        int maxindex = 0;
        float maval = 0.0f;
        float sum = 0.0f;
        for (int i=0; i<numChromosomes; i++) {
            for (int j=0; j<5; j++) {
                coefficients[j] = geneToFloat(i, j);
            }
            sum += fitness[i];
            if (i < 4 || (i % 100) == 0) {
                System.out.print("Fitness for chromosome " + i + " is ");
                System.out.print(fitness[i] + " coefficients:");
                for (int j=0; j<5; j++) System.out.print(pp(coefficients[j]));
                System.out.println();
            }
        }
        sum /= (float)numChromosomes;
        System.out.println("Average fitness=" + sum);
    }
    private String pp(float x) {
        x = (int)(1000 * x);
        x /= 1000.0f;
        return "" + x + " ";
    }
}
