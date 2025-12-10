# Text File Word Processor
Arranges .txt files into neat paragraphs with specified characters per line.
Features
- gets rid of unnecessary whitespace (e.g. 5 spaces between two words is reduced to 1 space; 2 empty lines between words is reduced to 1 space)
- left-justify paragraphs
- creates a new paragraph when encountering a paragraph tag (if encounters consecutive tags, it will only create one new line)
- based on number of specified characters wanted per line, will fit as many words on each line as possible
- formats for hyphens/hyphenated-words being broken off at line break
- returns error messages if specified characters per line is too short OR if a word is too long to fit on a line with the specified character limit
