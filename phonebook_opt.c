#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
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



hashTable *createTable(int tableSize)
{
    hashTable *ht =NULL;
    int i;

    for(i=0;i<tableSize;i++){
        ht->list[i]=NULL;
    }

    ht->tableSize = tableSize;
    return ht;
}

entry *findName_hash(char *key,hashTable *ht)
{
    entry *lne;
    hashIndex index = hash_(key,ht);

    for(lne=ht->list[index];lne!=NULL;lne=lne->pNext){
        if(strcasecmp(key,lne->lastName)==0){
        return lne;
        }
    }

    return NULL;
}


int append_hash(char *key,hashTable *ht)
{
    hashIndex index = hash_(key,ht);
    entry *entry_;

    if((entry_ = (entry *)malloc (sizeof(entry)))==NULL){
        return 2;
    }

    strcpy(entry_->lastName, key);
    entry_->pNext = ht->list[index];
    ht->list[index] = entry_;
    return 0;
}


hashIndex hash_(char *key, hashTable *ht){

    unsigned int hashVal = 0;
    while(*key != '\0'){
    hashVal = (hashVal << 5) + *key++;
    }
    return hashVal % ht->tableSize;
}
