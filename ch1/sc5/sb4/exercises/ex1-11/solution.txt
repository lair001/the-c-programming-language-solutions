In the modern day, I would test the word count program using a unit test
framework. As this book was written in the 1980's, I imagine that K&R is
looking for a less sophisticated approach. Most likely, they would have created
fixtures consisting of files that represented potential edge cases. They would
have then manually run the program multiple times, each time inputting a
different fixture.

Edge cases likely to uncover bugs include:
	1. Using whitespace other than space, tab, or newline
		a. Maybe we should use the isspace function?
	2. Using punctuation in unusual ways
		a. Interlaced with whitespace without letters
		b. Interlaced with letters without whitespace
	3. Similar to 2, run the program on source code
		a. Can easily result in 'words' that are purely punctuation
	4. Using numbers and special and foreign characters
		a. Mostly a problem stemming from vague requirements
		b. Should they be part of words?
		c. If so, are '1337' and '2be' words?
	5. Nonsensical sequences of letters
		a. Another requirements issue.
		b. Should 'reemcasdmwwo' be a word?
