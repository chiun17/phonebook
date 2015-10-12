#ifndef _PHONEBOOK_H
#define _PHONEBOOK_H

#define MAX_LAST_NAME_SIZE 16

/* original version */
        typedef struct __PHONE_BOOK_ENTRY {
            char lastName[MAX_LAST_NAME_SIZE];
            char firstName[16];
            char email[16];
            char phone[10];
            char cell[10];
            char addr1[16];
            char addr2[16];
            char city[16];
            char state[2];
            char zip[5];
            struct __PHONE_BOOK_ENTRY *pNext;
        } lastNameEntry;


        typedef struct __lastName_entry {
            char lastName[MAX_LAST_NAME_SIZE];
            lastNameEntry *data;
            struct __lastName_entry *pNext;
        } entry;

entry *findName(char lastname[], entry *pHead);
entry *append(char lastName[], entry *e);

typedef unsigned int hashIndex;
typedef struct __PHONE_BOOK_HASH_TABLE {
    unsigned int tableSize;
    entry **list;
} hashTable;


hashTable *createTable(int tableSize);
entry *findName_hash(char *key,hashTable *ht);
int append_hash(char *key, hashTable *ht);
hashIndex hash_(char *key ,hashTable *ht);



#endif
