# splchk

[![Build Status][1]][2]

**splchk** is an interactive command-line tool to find and fix potential
spelling errors in a given text document.

```bash
username@hostname:~/$ spellcheck -h

usage: splchk [-hv] [[-i] input_file] [-p | -o output_file]
                      [-d dictionary_file]

  -d dictionary_file    file to be used as dictionary
  -h                    prints this message and exits
  -i input_file         file to check
  -o output_file        file to write corrected text into
  -p                    makes document to be modified in-place
  -v                    prints version and exits
```

**splchk** was originally developed as a solution to a final course project
for the [Programming in C][3] course that I taught in Spring 2016.

## Demo

To illustrate the look and feel of **splchk**, let us check for potential
spelling errors in a [sample-01.txt][4] excerpt (from [lumenlearning.com][5])
using a small dictionary of 10,000 words and rewrite a processed version of
the document in a new file `sample-01.out.txt`.

```bash
splchk -d dat/dictionary.txt -i dat/sample-01.txt -o dat/sample-01.out.txt
```

The application output is shown below:

```
splchk                                                        dat/sample-01.txt
-------------------------------------------------------------------------------

Word-processing programs usually have a spell-checker, but you should still
carefully check for correct changes in your words. This is because automatic
spell-checkers may not always understand the context of a word.

Misspelling a word might seem like a minor mistake, but it can reflect
very porly on a writer. It suggests one of two things: either the writer
does not care enough about his work to proofread it, or he does not know
his topic well enough to properly spell words related to it. Either way,
spelling errors will make a reader less likely to trust a writer’s authority.

-------------------------------------------------------------------------------
word "porly" not found in the dictionary
------------------------
(a) add to dictionary
(s) substitute word
(c) ignore word
(q) abort program
```

## License

Source code is released under the [MIT License][6].

[1]: https://travis-ci.com/ghorbanzade/splchk.svg?branch=master
[2]: https://travis-ci.com/ghorbanzade/splchk
[3]: https://travis-ci.com/ghorbanzade/UMB-CS240-2016S
[4]: https://github.com/ghorbanzade/splchk/blob/master/dat/sample-01.txt
[5]: https://courses.lumenlearning.com/styleguide/chapter/the-importance-of-spelling/
[6]: https://github.com/ghorbanzade/splchk/blob/master/License.md
