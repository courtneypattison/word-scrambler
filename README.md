# Word Scrambler
Scrambles the inner letters of words from text documents.

## Compilation
Compile the program with the following command:
gcc word-scrambler.c

## Running the program
To run the program, you must know the full filename for the file that holds the 
text you would like scrambled (e.g., poetry.txt), place that file in the same 
directory as the program, and enter the filename when prompted. All the 
characters except the first and last of each word will be scrambled, then output 
to the screen. Numbers will be treated in the same way as letters. Punctuation 
will be preserved.

## Example output
```
$ ./a.out jane_eyre.txt
Enter the filename: jane_eyre.txt
Terhe was no piliibtsosy of tnkiag a wlak taht day. We had been waredinng, ideend, in the lealsefs sbhberury an huor in the monnrig; but sicne dnnier (Mrs. Reed, wehn terhe was no cpomnay, dneid eraly) the clod weitnr wnid had bgruoht wtih it cudlos so somrbe, and a rian so pnetrtnaeig, taht fehutrr oto-uodr ecresxie was now out of the qsotuien.
```

## Known Limitations
For the program to run successfully, the file must not contain strings longer 
than 29 characters. Similarly, the filename must not exceed 29 characters.
If words are separated by hyphens or dashes, the program will mistakenly 
scramble all the letters except the first of the first word and the last of the 
last word. Also, text formatting from the file will not be preserved (e.g., 
newlines).
