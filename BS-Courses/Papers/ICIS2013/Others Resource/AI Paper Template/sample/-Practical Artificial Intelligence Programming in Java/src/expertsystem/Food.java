
import java.util.*;
import java.io.*;

import jess.*;

public class Food {

    public static void main(String[] args) {
        try {
            FileReader fr = new FileReader("food_rules.clp");
            Rete r = new Rete();
            Jesp jesp = new Jesp(fr, r);
            jesp.parse(false);
            r.executeCommand("(reset)");
            r.executeCommand("(assert (have_food (name spinach) (weight 10)))");
            r.executeCommand("(assert (have_food (name peas) (weight 14) (is_frozen yes)))");
            System.out.println("Output from executing up to 10 Jess rules:\n");
            // Note: the following command causes any 'printout' commands from Jess to print to standard output:
            r.executeCommand("(run 10)"); // run a maximum of 10 rule firings
            // print out all facts in the system:
            System.out.println("\nList of all facts asserted in the system:\n");
            Iterator iter = r.listFacts();
            while (iter.hasNext()) {
                System.out.println("Current fact: " + iter.next());
            }
        } catch (Exception ex) {
            System.err.println(ex);
        }
    }

}


