/**
 * Title:        MakeWordNetCache<p>
 * Description:  Reads WordNet 1.6 index files and makes a part of speech
 *               serialized file consisting of 4 Java hash tables (for adj,
 *               adv, noun, and verb).
 * Copyright:    Copyright (c) by Mark Watson, 2000<p>
 * @author Mark Watson
 * @version 1.1
 */

/**      Wordnet 1.6 Copyright and License:

  1 This software and database is being provided to you, the LICENSEE, by  
  2 Princeton University under the following license.  By obtaining, using  
  3 and/or copying this software and database, you agree that you have  
  4 read, understood, and will comply with these terms and conditions.:  
  5   
  6 Permission to use, copy, modify and distribute this software and  
  7 database and its documentation for any purpose and without fee or  
  8 royalty is hereby granted, provided that you agree to comply with  
  9 the following copyright notice and statements, including the disclaimer,  
  10 and that the same appear on ALL copies of the software, database and  
  11 documentation, including modifications that you make for internal  
  12 use or for distribution.  
  13   
  14 WordNet 1.6 Copyright 1997 by Princeton University.  All rights reserved.  
  15   
  16 THIS SOFTWARE AND DATABASE IS PROVIDED "AS IS" AND PRINCETON  
  17 UNIVERSITY MAKES NO REPRESENTATIONS OR WARRANTIES, EXPRESS OR  
  18 IMPLIED.  BY WAY OF EXAMPLE, BUT NOT LIMITATION, PRINCETON  
  19 UNIVERSITY MAKES NO REPRESENTATIONS OR WARRANTIES OF MERCHANT-  
  20 ABILITY OR FITNESS FOR ANY PARTICULAR PURPOSE OR THAT THE USE  
  21 OF THE LICENSED SOFTWARE, DATABASE OR DOCUMENTATION WILL NOT  
  22 INFRINGE ANY THIRD PARTY PATENTS, COPYRIGHTS, TRADEMARKS OR  
  23 OTHER RIGHTS.  
  24   
  25 The name of Princeton University or Princeton may not be used in  
  26 advertising or publicity pertaining to distribution of the software  
  28 and/or database.  Title to copyright in this software, database and  
  29 any associated documentation shall at all times remain with  
  30 Princeton University and LICENSEE agrees to preserve same.  

*/

import java.io.*;
import java.util.*;

public class MakeWordNetCache {

    Hashtable adj = new Hashtable();
    Hashtable adv = new Hashtable();
    Hashtable noun = new Hashtable();
    Hashtable verb = new Hashtable();

    public MakeWordNetCache() {
        helper("index.adj", adj);
        helper("index.adv", adv);
        helper("index.noun", noun);
        helper("index.verb", verb);
        //System.out.println(verb.get("run"));
        try {
            FileOutputStream ostream = new FileOutputStream("wncache.dat");
            ObjectOutputStream p = new ObjectOutputStream(ostream);
            p.writeObject(adj);
            p.writeObject(adv);
            p.writeObject(noun);
            p.writeObject(verb);
            p.flush();
            ostream.close();
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    Boolean t = new Boolean(true);

    public void helper(String file, Hashtable hash) {
	int count = 0;
        try {
            FileReader fr = new FileReader(file);
            BufferedReader br = new BufferedReader(fr);
	    // skip copyright notice:
	    for (int i=0; i<30; i++) br.readLine();
            while (true) {
                String line = br.readLine();
                if (line == null) break;
                line = line.trim();
                int index1 = line.indexOf(" ");
                if (index1 == -1) continue;
		line = line.substring(0, index1);
                int index2 = line.indexOf(".");
                if (index2 != -1) continue;
                index2 = line.indexOf("_");
                if (index2 != -1) continue;
		line = line.toLowerCase();
                Object o = hash.get(line);
                if (o == null) {
                    hash.put(line, t);
                    //System.out.println(file + " : " + line);
		    count++;
                }
            }
	    System.out.println("" + count + " words added for " + file);
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    public static void main(String[] args) {
        MakeWordNetCache MakeWordNetCache1 = new MakeWordNetCache();
    }
}
