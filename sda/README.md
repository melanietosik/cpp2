Edit Distance and Sequence Alignment
====================================

NAME
----

sda - Computes various string metrics (Hamming distance, Minimum Edit distance, Levenshtein distance) and optimal global sequence alignment

SYNOPSIS
--------

$ make

$ make test 

$ ./bin/sda [-option] [sequence1] [sequence2]

DESCRIPTION
-----------

### EDIT DISTANCE

The edit distance, defined between two strings of not necessarily equal length, is the minimum number of edit operations required to transform one string into the other. An edit operation is either a deletion, an insertion, or a substitution of a single character in either sequence. As a way of quantifying how dissimilar two strings are (e.g., words or DNA sequences), edit distances find manifold applications in [Natural Language Processing (NLP)](https://en.wikipedia.org/wiki/Natural_language_processing) and [bioinformatics](https://en.wikipedia.org/wiki/Bioinformatics).

Several definitions of edit distance exist, using different sets of string operations. One of the most common variants is called Levenshtein distance, named after the Soviet Russian computer scientist Vladimir Levenshtein. For example, here is the operation list for computing the Levenshtein distance between intention and execution (taken from Jurafsky and Martin (2009)):

**intention** &rarr; [_delete i_] &rarr; **ntention** &rarr; [_substitute n by e_] &rarr; **etention** &rarr; [_substitute t by x_] &rarr; **exention** &rarr; [_insert u_] &rarr; **exenution** &rarr; [_substitute n by c_] &rarr; **execution**

Originally, Levenshtein assigned a cost of 1 for each of three operations, defining the Minimum Edit distance. Thus, the minimum edit distance between intention and execution would be 5. Later on, he proposed an alternate version of his metric, assinging a cost of 1 to each deletion or insertion, and a cost of 2 for each substitution. Substitutions are really an insert with a delete, hence the double weight. Using this version, the Levenshtein distance between intention and execution is 8.

If two strings are of equal length, the Minimum Edit distance is obtained by computing the Hamming distance -- the number of character positions where they differ. For equal-length strings, the Hamming distance also functions as upper bound on the Levenshtein distance.

See also: 

- [Hamming distance] [0] on Wikipedia
- [Edit distance] [1] on Wikipedia
- [Levenshtein distance] [2] on Wikipedia
- [Wagner-Fischer algorithm] [3] on Wikipedia

### SEQUENCE ALIGNMENT

See also: 

- [Sequence alignment] [4] on Wikipedia
- [Needleman-Wunsch algorithm] [5] on Wikipedia


OPTION
------

**-m** &nbsp; Compute minimum edit distance

**-l** &nbsp;&nbsp;&nbsp; Compute levenshtein distance

**-a** &nbsp;&nbsp; Compute global sequence alignment
 
**-h** &nbsp;&nbsp; Print help message

INPUT
-----

Edit distances and sequence alignment are computed for any two given strings.

In theory, the strings can of arbitrary length. Practically, eventually you will probably run out of space for very long sequences.

If only one input string is provided, the second string is interpreted as the empty string. 

EXAMPLE
-------

**INPUT**

insertion execution

**COMMAND**

  $ ./bin/sda -m insertion execution

  $ ./bin/sda -a insertion execution
    
**OUTPUT**

  Minimum edit distance: 5
  
  Sequence A: inse-rtion<br>
  Sequence B: -execution<br>
  Maximum alignment score: 0

TO DO
-----

[Some of this, maybe.] [6] And there's many more string metrics out there! I also really want to read a good intro on bioinformatcs now.

AUTHOR
------

Melanie Tosik, tosik@uni-potsdam.de

REFERENCES
----------

Jurafsky, Daniel, and James H. Martin. 2009. Speech and Language Processing: An Introduction to Natural Language Processing, Speech Recognition, and Computational Linguistics. 2nd edition. Prentice-Hall.

Needleman, Saul B.; and Wunsch, Christian D. (1970). "A general method applicable to the search for similarities in the amino acid sequence of two proteins". Journal of Molecular Biology 48 (3): 443–53.

Navarro, Gonzalo (2001). "A guided tour to approximate string matching". ACM Computing Surveys 33 (1): 31–88.

[0]: https://en.wikipedia.org/wiki/Hamming_distance
[1]: https://en.wikipedia.org/wiki/Edit_distance
[2]: https://en.wikipedia.org/wiki/Levenshtein_distance
[3]: https://en.wikipedia.org/wiki/Wagner%E2%80%93Fischer_algorithm
[4]: https://en.wikipedia.org/wiki/Sequence_alignment
[5]: https://en.wikipedia.org/wiki/Needleman%E2%80%93Wunsch_algorithm
[6]: https://en.wikipedia.org/wiki/Wagner%E2%80%93Fischer_algorithm#Possible_modifications