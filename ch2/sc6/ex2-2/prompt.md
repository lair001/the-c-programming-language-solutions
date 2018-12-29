Write a loop equivalent to the for loop above without using && or ||.

# Editorial Comment

The prompt is referring to the following code:

`
    for (i=0; i<lim-1 && (c=getchar()) != '\n' && c != EOF; ++i)  
        s[i] = c;
`
