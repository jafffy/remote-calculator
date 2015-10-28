#ifndef COMMON_H_
#define COMMON_H_

#ifndef BOOL
#define BOOL int
#endif // BOOL

#ifndef TRUE
#define TRUE 1
#endif // TRUE

#ifndef FALSE
#define FALSE 0
#endif // FALSE

enum State { Greeting, Transaction, Closing };

void convertToLowerCase(char target[], char source[], int n);

#endif // COMMON_H_
