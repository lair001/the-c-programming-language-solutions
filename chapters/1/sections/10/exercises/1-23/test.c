/* Tests 
 * This is not a compilable program.
 * This is test input for solution.c */

// should not appear 001 // should not appear 002
// should not appear 003
/* should not appear 004
 * should not appear 005
should not appear 006 **/ should appear 101
/* should not appear 007
should not appear 008 // should not appear 009
should not appear 010 */ should appear 102
should appear 103
"/*" should appear 104 "*/"
'should appear 105 /*' should not appear 011 '*/ should appear 106'
'"' should appear 107 /* should not appear 012 */ should appear 108 '"'
should appear 109 \/* should not appear 013 */ should appear 110
/* should not appear 014 \*/ should appear 111

/* These are the index ranges.
 * The should not appear labels should not appear.
 * The should appear labels should appear for the
 * entirety of their respective index range. */
should not appear indexes: 001-014
should appear indexes: 101-111
