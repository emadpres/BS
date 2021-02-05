/**
 * Parser.java
 *
 * Example program to demonstrate using both a set of
 * Prolog rules for parsing simple English sentences,
 * and shows how to embed Sieuwert van Otterloo's Prolog Engine
 * in a Java program.
 *
 * Mark Watson.
 */

import java.util.*;
import java.io.*;

public class Parser {

    public static void main(String [] args) {
	try {
	    BufferedReader in
		= new BufferedReader(new InputStreamReader(System.in));
	    Prolog prologEngine = new Prolog();
	    prologEngine.consultFile("p.pl", true);
	    while (true) {
		System.out.println("Enter a sentence:");
		String line = in.readLine();
		if (line == null) return;
		if (line.length() < 2) return;
		line = line.trim().toLowerCase();
		if (line.endsWith(".")) line = line.substring(0, line.length() - 1);
		StringBuffer sb = new StringBuffer("sentence([");
		StringTokenizer st = new StringTokenizer(line);
		while (st.hasMoreTokens()) {
		    sb.append(st.nextToken() + ",");
		}
		// drop the last comma and close the brace:
		String query = sb.toString().substring(0, sb.length()-1) +
		    "],S).";
		System.out.println("Generated Prolog query: " + query);
		Vector v = prologEngine.solve(query);
		Hashtable the_answers = (Hashtable)v.elementAt(0);
		Enumeration enum = the_answers.keys();
		while (enum.hasMoreElements()) {
		    String var = (String)enum.nextElement();
		    String val = (String)the_answers.get(var);
		    System.out.println(val);
		}
	    }
	} catch (Exception e) {
	    System.out.println("Error: " + e);
	}
    }
}

		
