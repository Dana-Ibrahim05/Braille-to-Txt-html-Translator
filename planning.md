# Planning Document
This document is where we can put our planning for this project. It also includes pseudocode and steps.
## Step 1: File IO basics
This step is the foundation of the program. We build the basic file IO system that allows the program to copy the contents of the braille file into a text file. IMplented as follows:

1. Create 2 file objects: one for the input (braille) and another for writing to the text file.
2. open the braille file.
3. use a string to store each word.
4. write each string to the new file
## step 2 (A): translating contractions.
There are over 150 contractions in braille, some of them being one-cell symbols and other being 2 (or more) letter combinations.
We therefore must create rules to allow the program to  translate these contractions.
I have thought of various tools to do this and used this resource to generate ideas:
[GeeksforGeeks] (https://www.geeksforgeeks.org/cpp/switch-vs-else/)
1. If-statements: they were my initial thoughts, but these are not very efficient when we have more than 5 cases, which we do.
2. Switch statements: Switch statements are a more efficient and clean way to do our translation if we have more than 5 cases.
2. polymorphism: I believe it would be a really good idea but I am still unsure how it can be implemented in this scope.
3. maps: I also thought of using maps because we could map strings (keys) to values (what they can be replaced with). This can be done in a separate header file for efficiency where we manually add these strings and somehow read in this map from within main.


## Step 2 (B): Translating math formulas
This step is similar to the previous, except that some of the symbols in contractions and the symbols in math overlap, and therefore we must create another set of rules to allow this translation to occur without causing any mistranslation of math content into text and vice versa.

## Step 3: Formatting
It would be very helpful to have a converted file that has some element of formatting, particularly headings. Headings assist in navigation and significantly speed it up. These can be used to mark slide numbers, as well as section titltes.
