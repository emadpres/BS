/**
 * Title:        ATN<p>
 * Description:  Implements a simpl ATN parser that uses WordNet data
 * Copyright:    Copyright (c) by Mark Watson, 2000<p>
 * @author Mark Watson
 * @version 1.2
 */

import java.io.*;
import java.util.*;

public class ATN {

    public ATN() {
        try {
	    // the following code will read either a local file of a
	    // resource in a JAR file:
            InputStream ins =
		ClassLoader.getSystemResourceAsStream("wncache.dat");
            if (ins==null) {
                System.out.println("Failed to open 'wncache.dat'");
                System.exit(1);
            } else {
                ObjectInputStream p = new ObjectInputStream(ins);
                adj = (Hashtable)p.readObject();
                adv = (Hashtable)p.readObject();
                noun = (Hashtable)p.readObject();
                verb = (Hashtable)p.readObject();
                ins.close();
            }
	    // Augment the WordNet 1.6 entries:
	    art = new Hashtable(); addWords(art, ARTS);
	    conj = new Hashtable(); addWords(conj, CONJS);
	    det = new Hashtable(); addWords(det, DETS);
	    pron = new Hashtable(); addWords(pron, PRONS);
	    prep = new Hashtable(); addWords(prep, PREPS);
	    // fill in a few common verbs that are not in Wordnet 1.6:
	    verb.put("ran", b);
       } catch (Exception e) {
            e.printStackTrace();
        }
    }
    private Boolean b = new Boolean(true);

    private void addWords(Hashtable h, String [] ws) {
	for (int i=0; i<ws.length; i++) {
	    h.put(ws[i], b);
	}
    }

    Hashtable adj, adv, art, conj, det, noun, pron, verb, prep;

    String [] PRONS = {"he", "she", "me", "it", "you", "I"};
    String [] ARTS  = {"the", "a", "an"};
    String [] CONJS = {"and", "or"};
    String [] DETS = {"who", "what", "where", "when"};
    String [] PREPS = {"on", "at", "under", "above", "behind", "to", "about","down"};
    private boolean checkWord(String word, int type) {
	if (type == PREP) {
	    if (prep.get(word) != null) return true;
	} else if (type == VERB) {
	    if (verb.get(word) != null) return true;
	    // some simple kluges to accept words like "likes" when
	    // only "like" is in the lexicon:
	    if (word.endsWith("s") || word.endsWith("ed")) {
		String s = word.substring(0, word.length() - 1);
		if (verb.get(s) != null) return true;
	    }
	} else if (type == NOUN) {
	    if (noun.get(word) != null) return true;
	} else if (type == CONJ) {
	    if (conj.get(word) != null) return true;
	} else if (type == ADJ) {
	    if (adj.get(word) != null) return true;
	} else if (type == ADV) {
	    if (adv.get(word) != null) return true;
	} else if (type == PRON) {
	    if (pron.get(word) != null) return true;
	} else if (type == DET) {
	    if (det.get(word) != null) return true;
	} else if (type == ART) {
	    if (art.get(word) != null) return true;
	}
	return false;
    }

    public int [] parse(String s) {
        Vector v = new Vector();
        StringTokenizer st = new StringTokenizer(s);
        while (st.hasMoreTokens()) {
            String str = st.nextToken();
            if (str.length() > 2 && str.endsWith(",")) {
		str = str.substring(0, str.length() - 1);
	    }
            if (str.length() > 2 && str.endsWith(".")) {
		str = str.substring(0, str.length() - 1);
	    }
            if (str.length() > 2 && str.endsWith(":")) {
		str = str.substring(0, str.length() - 1);
	    }
            if (str.length() > 2 && str.endsWith(";")) {
		str = str.substring(0, str.length() - 1);
	    }
            v.addElement(str.toLowerCase());
        }
	// It is easier to work with an array, so convert the Vector
	// to an array of Java strings:
	int size = v.size();
	if (size == 0) return null;
	words = new String[size];
	partsOfSpeech = new int[size];
	num_words = size;
	for (int i=0; i<size; i++) words[i] = (String)v.elementAt(i);
	// quick test against lexicon for word types:
	for (int i=0; i<words.length; i++) {
	    System.out.print("'" + words[i] + "' possible word types: ");
	    if (adj.get(words[i]) != null) System.out.print("adj ");
	    if (adv.get(words[i]) != null) System.out.print("adv ");
	    if (art.get(words[i]) != null) System.out.print("art ");
	    if (noun.get(words[i]) != null) System.out.print("noun ");
	    if (prep.get(words[i]) != null) System.out.print("prep ");
	    if (verb.get(words[i]) != null) System.out.print("verb ");
	    System.out.println();
	}
	System.out.println();
	// execute the parsing helper methods until one succeeds:
	parse_it();
	return null;
    }

    String [] words;
    int [] partsOfSpeech;
    int wordIndex;
    int num_words;
    
    public static void main(String [] args) {
	ATN nf = new ATN();
	if (args.length < 1) {
	    nf.parse("the dog ran down the street");
	} else {
	    for (int i=0; i<args.length; i++) {
		System.out.println("\nProcessing : " + args[i]);
		nf.parse(args[i]);
	    }
	}
    }


    //////////////// ATN functions:


    String getPOSname(int pos) {
	switch (pos) {
	case 1: return "NP";
	case 2: return "VP";
	case 3: return "PP";
	case 1001: return "noun";
	case 1002: return "verb";
	case 1003: return "prep";
	case 1004: return "conj";
	case 1005: return "adj";
	case 1006: return "adv";
	case 1007: return "pron";
	case 1008: return "det";
	case 1009: return "art";
	default: return "unknown";
	}
    }
    public final static int NP = 1;
    public final static int VP = 2;
    public final static int PP = 3;

    public final static int NOUN = 1001;
    public final static int VERB = 1002;
    public final static int PREP = 1003;
    public final static int CONJ = 1004;
    public final static int ADJ  = 1005;
    public final static int ADV  = 1006;
    public final static int PRON = 1007;
    public final static int DET  = 1008;
    public final static int ART  = 1009;

    public final static int NUM_S = 9;
    //    int [] LEN_S   = { 5,  4,  3,  4,  3,  2,  2,  2,  1};

    int [] ALL_S [] = {
	{NP, VP, NP, PP, VP},
	{NP, VP, PP, NP},
	{NP, VP, NP},
	{VP, NP, PP, NP},
	{VP, PP, NP},
	{NP, VP},
	{VP, PP},
	{VP, NP},
	{VP}
    };

    //////////////// The actual parser:

    int parsePP(int start_word_index, int word_index) {
	if (word_index >= num_words)  return word_index;
	// test ATN transitions <PREP> --> <NP>
	if (checkWord(words[word_index], PREP)) {
	    partsOfSpeech[start_word_index + word_index] = PREP;
	    int ii = parseNP(start_word_index, word_index + 1);
	    if (ii > -1) {
		return ii;
	    }
	}
	return -1;
    }

    int parseNP(int start_word_index, int word_index) {
	if (word_index >= num_words)  return word_index;
	// test ATN transitions <NOUN> --> <CONJ> --> <NP>
	if (word_index < num_words - 2 && checkWord(words[word_index], NOUN)) {
	    if (checkWord(words[word_index + 1], CONJ)) {
		int ii = parseNP(start_word_index, word_index + 2);
		if (ii > -1) {
		    partsOfSpeech[start_word_index + word_index] = NOUN;
		    partsOfSpeech[start_word_index + word_index + 1] = CONJ;
		    return ii;
		}
	    }
	}
	// test ATN transitions <ART> --> <NP>
	if (word_index < num_words - 1 && checkWord(words[word_index], ART)) {
	    int ii = parseNP(start_word_index, word_index + 1);
	    if (ii > -1) {
		partsOfSpeech[start_word_index + word_index] = ART;
		return ii;
	    }
	}
	// test ATN transitions <DET> --> <NP>
	if (word_index < num_words - 1 && checkWord(words[word_index], ADJ)) {
	    int ii = parseNP(start_word_index, word_index + 1);
	    if (ii > -1) {
		partsOfSpeech[start_word_index + word_index] = ADJ;
		return ii;
	    }
	}
	// test ATN transitions <ADJ> --> <NP>
	if (checkWord(words[word_index], ADJ)) {
	    int ii = parseNP(start_word_index, word_index + 1);
	    if (ii > -1) {
		partsOfSpeech[start_word_index + word_index] = ADJ;
		return ii;
	    }
	}
	// test ATN transitions <ADV> --> <NP>
	if (word_index < num_words - 1 && checkWord(words[word_index], ADV)) {
	    int ii = parseNP(start_word_index, word_index + 1);
	    if (ii > -1) {
		partsOfSpeech[start_word_index + word_index] = ADV;
		return ii;
	    }
	}
	// test ATN transitions <NOUN> --> <NOUN>
	if (word_index < num_words - 1 && checkWord(words[word_index], NOUN)) {
	    if (checkWord(words[word_index + 1], NOUN)) {
		partsOfSpeech[start_word_index + word_index] = NOUN;
		partsOfSpeech[start_word_index + word_index + 1] = NOUN;
		return word_index + 2;
	    }
	}
	if (checkWord(words[word_index], NOUN)) {
	    partsOfSpeech[start_word_index + word_index] = NOUN;
	    return word_index + 1;
	}
	if (checkWord(words[word_index], PRON)) {
	    int ii = parseNP(start_word_index, word_index + 1);
	    if (ii > -1) {
		partsOfSpeech[start_word_index + word_index] = PRON;
		return ii;
	    }
	}
	if (checkWord(words[word_index], PRON)) {
	    partsOfSpeech[start_word_index + word_index] = PRON;
	    return word_index + 1;
	}
	return -1;
    }

    int parseVP(int start_word_index, int word_index) {
	if (word_index >= num_words)  return word_index;
	// test ATN transitions <V> --> <NP> --> <PP>
	if (checkWord(words[word_index], VERB)) {
	    partsOfSpeech[start_word_index + word_index] = VERB;
	    int ii = parseNP(start_word_index, word_index + 1);
	    if (ii > -1) {
		int jj = parsePP(start_word_index, ii);
		if (jj > -1) {
		    return jj;
		}
	    }
	}
	// test ATN transitions <V> --> <NP>
	if (checkWord(words[word_index], VERB)) {
	    partsOfSpeech[start_word_index + word_index] = VERB;
	    int ii = parseNP(start_word_index, word_index + 1);
	    if (ii > -1) {
		return ii;
	    }
	}
	// test ATN transitions <V> --> <PP>
	if (checkWord(words[word_index], VERB)) {
	    partsOfSpeech[start_word_index + word_index] = VERB;
	    int ii = parsePP(start_word_index, word_index + 1);
	    if (ii > -1) {
		return ii;
	    }
	}
	if (checkWord(words[word_index], VERB)) {
	    partsOfSpeech[start_word_index + word_index] = VERB;
	    return word_index + 1;
	}
	return -1;
    }


    int parseHelper(int [] atn, int start_word_index) {
	int word_index = 0;
	int len_atn = atn.length;
	int last_word_index = word_index;
	for (int i=0; i<len_atn; i++) {
	    last_word_index = word_index;
	    switch (atn[i]) {
	    case NP: word_index = parseNP(start_word_index, word_index);  break;
	    case VP: word_index = parseVP(start_word_index, word_index);  break;
	    case PP: word_index = parsePP(start_word_index, word_index);  break;
	    }
	    if (word_index == -1)  return last_word_index;
	}
	return word_index;
    }

    int parseSentence(int start_word_index) {

	int max_val = -1;
	int max_word_index = 0;
	for (int i=0; i<NUM_S; i++) {
	    int k = parseHelper(ALL_S[i], start_word_index);
	    //System.out.println("Score for ATN " + i + " is " + k);
	    if (k > max_val) {
		max_val = k;
		max_word_index = i;
	    }
	}
	System.out.println("Best ATN at word_index " + max_word_index);
	parseHelper(ALL_S[max_word_index], start_word_index);
	for (int i=0; i<num_words; i++) {
	    if (partsOfSpeech[start_word_index + i] == 0) {
		if (checkWord(words[i], NOUN)) {
		    partsOfSpeech[start_word_index + i] = NOUN;
		}
		if (checkWord(words[i], CONJ)) {
		    partsOfSpeech[start_word_index + i] = CONJ;
		}
	    }
	}
	return max_val;
    }

    void parse_it() {
	int word_index = parseSentence(0);
	//System.out.println("word_index from S ATN = " + word_index);
	for (int i=0; i<num_words; i++) {
	    System.out.println(" word: " + words[i] + 
			       " part of speech: " + getPOSname(partsOfSpeech[i]));
	}
    }

}
