#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>
#include "phonebook_opt.h"

/* FILL YOUR OWN IMPLEMENTATION HERE! */
entry *findName(char lastname[], entry *pHead)
    {
        while(pHead != NULL){
            if(strcasecmp(lastname,pHead->lastName) == 0)
                return pHead;
        pHead = pHead->pNext;
        }
        return NULL;
    }

entry *append(char lastName[], entry *e)
{
        e->pNext = (entry *)malloc(sizeof(entry));
        e = e->pNext;
        strcpy(e->lastName, lastName);
        e->pNext = NULL;
        return e;
}


hashtable *ht_create(int size){
    hashtable *hashtable;
    int i;
    if( size < 1 ) return NULL;

    if(  (hashtable = malloc( sizeof(hashtable))) == NULL) {
        return NULL;
    }
    if( ( hashtable->table = malloc (sizeof(entry *) * size ) )==NULL){
        return NULL;
    }
for( i=0;i<size ;i++){
        hashtable->table[i]=NULL;
    }
    
    hashtable->size = size ;

    return hashtable;
}


int ht_hash(hashtable *hashtable , char *key){
        unsigned long int hashval;
        int i=0;

    while(hashval < ULONG_MAX && i < strlen (key) ){
        hashval = hashval << 8 ;
        hashval += key[i];
        i++;
    }
        return hashval % hashtable->size;

}


entry *ht_newpair (char *key){
        entry * newpair;

        if(  (newpair= malloc (sizeof(entry))) == NULL   ){
                return NULL;        
        }

        if((strcpy(newpair->lastName,key)) == NULL ){
                return NULL;
        }
        
        newpair->pNext = NULL;
        return newpair;
}


void ht_append(hashtable *hashtable , char *key){
        int bin = NULL;
        entry *lastPair = NULL;
        entry *next = NULL;
        entry *newpair=NULL;

        bin = ht_hash(hashtable , key);
        
        next = hashtable->table[ bin ];

        while (next != NULL && next->lastName != NULL && strcmp(next->lastName , key) >0){
            lastPair = next ;
            next = next->pNext;
        }

            newpair = ht_newpair(key);
        if( next == hashtable->table[ bin ]){
            newpair-> pNext = next;      
            hashtable->table[ bin ] = newpair;
        }
        else if (next == NULL){
            lastPair->pNext = newpair;
        }
        else{
            newpair->pNext = next ;
            lastPair->pNext = newpair;
        }
}


void ht_findName(hashtable *hashtable ,char *key){
        int bin = 0;
        entry *pair;
        bin = ht_hash(hashtable , key);

        pair = hashtable->table[ bin ];

        while( strcmp(pair->lastName,key) >0 ){
            pair = pair->pNext;
        }

        if( strcmp(pair->lastName,key)!=0){
            printf("%s is not found\n",key);
        }
        else{
            printf("%s is found\n",key);   
        }
}
