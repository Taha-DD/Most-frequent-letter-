#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define H 26

typedef struct {
    char chrctr;
    int frqncy;
} alph;

void stralloc ( char **str ) {
    *str = ( char* ) realloc ( *str, strlen( *str ) + 1 );
    if ( *str == NULL ) {
        printf(" str's memory re-allocation failed");
        abort();
    }
}

void alfalloc ( alph **i, int n ) {
    *i = ( alph* ) realloc ( *i, n * sizeof( alph ) );
    if ( *i == NULL ) {
        printf(" i's memory re-allocation failed");
        abort();
    }
}

void tozero ( alph *i, int n ) {
    for ( alph *r = i; r < i + n; ++r ) {
        r -> chrctr = 0;
        r -> frqncy = 0;
    }
}

char *strtolower ( char *str ) {
    char *st = ( char* ) malloc ( strlen( str ) + 1 );
    strcpy( st, str );
    for ( char *s = st; *s; ++s )
        *s = tolower( *s );
    return st;
}

void frqncounter ( char *str, alph **i ) {
    int r = 1;
    *i = ( alph* ) calloc ( H, sizeof( alph ) );
    if ( *i == NULL ) {
        printf(" i's contiguous allocation failed");
        abort();
    }
    
    for ( char *s = str; *s; ++s ) {
        if ( !isalpha(*s) ) continue;
        int k = 0;
        char *p = s;
        
        if ( strchr( strtolower( str ), tolower( *s ) ) < s ) continue;

        while ( p ) {
            k++;
            p++;
            p = strchr( strtolower( p ), tolower( *s ) );
        }

        if ( k > (*i) -> frqncy ) {
            tozero( *i, H );
            r = 1;
            (*i)->frqncy = k;
            (*i)->chrctr = *s;
        } else if ( k == (*i) -> frqncy ) {
            r = 1;
            for (alph *o = *i; o < *i + H; ++o, ++r )
                if ( !o -> chrctr ) {
                    o->frqncy = k;
                    o->chrctr = *s;
                    break;
                }
        }
    }
    
    alfalloc( i, r );
}

int main()
{
    alph *i;
    char *str = ( char* ) malloc ( 400 );
    if ( str == NULL ) {
        printf(" memory allocation failed");
        abort();
    }

    printf(" enter a string: ");
    gets( str );

    stralloc( &str);

    frqncounter ( str, &i );
    
    if ( !i->frqncy )
        printf(" there's no alphabetical characters");
    else {
        printf(" the most repeated characters are:");
        for(int r = 0; i[r].frqncy; ++r )
            printf("\n \"%c\" with %d occurrences", i[r].chrctr, i[r].frqncy);
    }
    
    free( str ); free( i );
    str = NULL; i = NULL;
    return 0;
}