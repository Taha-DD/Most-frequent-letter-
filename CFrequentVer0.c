#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct {
    char chrctr;
    int frqncy;
} alph;

char *strtolower ( char *str ) {
    char *st = ( char* ) malloc ( strlen( str ) + 1 );
    strcpy( st, str );
    for ( char *s = st; *s; ++s )
        *s = tolower( *s );
    return st;
}

alph frqncounter ( char *str ) {
    alph b = {'a', 0};
    for ( int i = 0; i < 26; ++i ) {
        char *p = strchr( strtolower( str ), 'a' + i );
        int k = 0;
        while ( p ) {
            k++;
            p++;
            p = strchr( strtolower( p ), 'a' + i );
        }
        if ( k > b.frqncy ) {
            b.frqncy = k;
            b.chrctr = 'a' + i;
        }
    }
    return b;
}

int main()
{
    char *str = ( char* ) malloc ( 400 );
    if ( str == NULL ) {
        printf(" memory allocation failed");
        exit(1);
    }

    printf(" enter a string: ");
    gets( str );

    str = ( char* ) realloc ( str, strlen( str ) + 1 );
    if ( str == NULL ) {
        printf(" memory re-allocation failed");
        exit(1);
    }

    alph b = frqncounter ( str );
    if ( !b.frqncy )
        printf(" there's no alphabetical characters");
    else
        printf(" the most repeated character is \"%c\" with %d occurrences", b.chrctr, b.frqncy);
    
    free(str);
    str = NULL;
    
    return 0;
}