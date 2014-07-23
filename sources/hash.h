#ifndef _FLUX_UTILITY_hash_
#define _FLUX_UTILITY_hash_
#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "debug.h"


typedef struct hashnode {
	struct hashnode *next;
	void *key;
	void *val;
} hashnode;

typedef struct hash {
	HashNode **buckets;
	size_t num_buckets;
	size_t num_entries;
	size_t key_size;
	size_t val_size;
	uint32_t (*hash)(const void*);
	int (*cmp)(const void*, const void*);
} hash;


type

// Management & Allocation.
int hash_init(hash*, size_t, size_t);
void hash_sethash(hash*, uint32_t (*)(const void*));
void hash_setCmp(hash*, int (*)(const void*, const void*));
void hash_clear(hash*);
void hash_clean(hash *const);

// Storage & Removal.
int hash_put(hash *const, const void *const, const void *const);
bool hash_has(const hash *const, const void *const);
void hash_rem(hash *const, const void *const);
void *hash_hook(const hash *const, const void *const);
int hash_fetch(const hash *const, const void *const, void *const);

// Extras.
void hash_forEach(hash *const, void (*)(const void*, void*));
uint32_t Strhash(const void *const);
int StrCmp(const void *const, const void *const);


#endif