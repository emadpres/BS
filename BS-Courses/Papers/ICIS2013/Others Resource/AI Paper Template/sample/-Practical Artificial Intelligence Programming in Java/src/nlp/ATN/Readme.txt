I used to provide a large serialized Java data file in
this directory that is produced by:

1. Downloading the Wordnet package from http://www.cogsci.princeton.edu/~wn/
2. copying the index.* files from the WORDNET/dict directory to this
directory
3. Running the program:

javac MakeWordNetCache.java
java MakeWordNetCache

Note that the wncache.dat file is large (removing it from the
web book ZIP file cut the ZIP file size by about 50%).

-Mark Watson   1/5/2003
