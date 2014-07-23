// #include "hash.h"
// #define DEFAULT_CAPACITY 25

// #define MAX_ALIGN 16
// #define ALIGNMENT(size) ((size) > MAX_ALIGN? MAX_ALIGN : mult2Alignment(size))
// #define ALIGN_TO(size, to) (((size) - ((size) - 1) % (to)) - 1 + (to))

// #define PTR_SIZE sizeof(fx_HashNode*)
// #define KEY_OFFSET(hash) ALIGN_TO(PTR_SIZE, ALIGNMENT((hash->key_size)))
// #define VAL_OFFSET(hash) ALIGN_TO(KEY_OFFSET(hash) + hash->key_size, hash->val_size)

// #define KEY_PTR(hash, node) (void*) (((char*) node) + KEY_OFFSET(hash))
// #define VAL_PTR(hash, node) (void*) (((char*) node) + VAL_OFFSET(hash))
// #define NODE_SIZE(hash) (VAL_OFFSET(hash) + hash->val_size)

// // Finds maximum multiple of two <= size.
// static size_t mult2Alignment(const size_t size)
// {
// 	size_t ret = 2;
// 	while(ret <= size)
// 		ret <<= 1;
// 	ret >>= 1;
// 	return ret;
// }

// // Creates a HashNode with <key> and <val> according to <hash>'s
// // configuration.
// static fx_HashNode *fx_HashNode_from(const fx_Hash *const hash, const void *const key, const void *const val)
// {
// 	fx_checkPtr3(hash, key, val);
// 	fx_HashNode *ret = malloc(NODE_SIZE(hash));
// 	if(!ret)
// 		return NULL;

// 	ret->next = NULL;
// 	memcpy(KEY_PTR(hash, ret), key, hash->key_size);
// 	memcpy(VAL_PTR(hash, ret), val, hash->val_size);
// 	return ret;
// }

// // Removes all all elements stored beyond or within <node> in LL.
// static void fx_HashNode_free(fx_HashNode *node)
// {
// 	while(node){
// 		fx_HashNode *tmp = node->next;
// 		free(node);
// 		node = tmp;
// 	}
// }

// // Removes all entries stored in bucket <i>.
// static void fx_Hash_freeBucket(fx_Hash *const hash, const unsigned i)
// {
// 	fx_HashNode_free(hash->buckets[i]);
// 	hash->buckets[i] = NULL;
// }

// // Jenkins's one-at-a-time hash (from http://en.wikipedia.org/wiki/Jenkins_hash_function#cite_note-dobbs-2).
// static uint32_t fx_Hash_default(const char *const key, const size_t len)
// {
// 	uint32_t hash, i;
//     for(hash = i = 0; i < len; ++i)
//     {
//         hash += key[i];
//         hash += (hash << 10);
//         hash ^= (hash >> 6);
//     }
//     hash += (hash << 3);
//     hash ^= (hash >> 11);
//     hash += (hash << 15);
//     return hash;
// }

// uint32_t fx_StrHash(const void *str)
// {
// 	fx_checkPtr(str);
// 	return fx_Hash_default((char*) str, strlen(str));
// }

// int fx_StrCmp(const void *a, const void *b)
// {
// 	fx_checkPtrs(a, b);
// 	return strcmp((char*) a, (char*) b);
// }

// // Computes hash value for specified key.
// static uint32_t fx_Hash_hash(const fx_Hash *const hash, const void *const key)
// {
// 	if(hash->hash)
// 		return hash->hash(key);
// 	return fx_Hash_default((char*) key, hash->key_size);
// }

// static int fx_Hash_cmp(const fx_Hash *const hash, const void *const a, const void *const b)
// {
// 	fx_checkPtr3(hash, a, b);
// 	if(hash->cmp)
// 		return hash->cmp(a,b);
// 	else
// 		return memcmp(a,b,hash->key_size);
// }

// // Gets bucket index for given key.
// static size_t fx_Hash_index(const fx_Hash *const hash, const void *const key)
// {
// 	unsigned raw = fx_Hash_hash(hash, key);
// 	return (size_t) raw % hash->num_buckets;
// }

// static fx_HashNode *fx_Hash_hookNode(const fx_Hash *const hash, const void *const key)
// {
// 	fx_checkPtrs(hash, key);

// 	size_t i = fx_Hash_index(hash, key);
// 	fx_HashNode *ret = hash->buckets[i];
// 	while(ret){
// 		if(!fx_Hash_cmp(hash, KEY_PTR(hash, ret), key))
// 			return ret;
// 		ret = ret->next;
// 	}
// 	return NULL;
// }

// // Expands to have <n> buckets.
// static int fx_Hash_expandTo(fx_Hash *const hash, const size_t n)
// {
// 	fx_checkPtr(hash);

// 	// try allocating new buckets
// 	fx_HashNode **buckets = hash->buckets;
// 	size_t num_buckets = hash->num_buckets;
// 	size_t num_entries = hash->num_entries;

// 	hash->num_buckets = n;
// 	hash->num_entries = 0;
// 	hash->buckets = calloc(n, sizeof(fx_HashNode*));
// 	if(!hash->buckets)
// 		goto error;

// 	// try storing old key-value pairs again
// 	for(int i = 0; i < num_buckets; ++i){
// 		fx_HashNode *node = buckets[i];
// 		while(node){
// 			if(fx_Hash_put(hash, KEY_PTR(hash, node), VAL_PTR(hash, node)))
// 				goto error;
// 			node = node->next;
// 		}
// 		fx_HashNode_free(buckets[i]);
// 	}
// 	free(buckets);
// 	return 0;

// error:
// 	hash->buckets = buckets;
// 	hash->num_buckets = num_buckets;
// 	hash->num_entries = num_entries;
// 	return -1;
// }

// // (buckets + 1) *= 2
// static int fx_Hash_expand(fx_Hash *const hash)
// {
// 	size_t size = hash->num_buckets;
// 	++size;
// 	return fx_Hash_expandTo(hash, 2 * size);
// }

// static void fx_Hash_contract(fx_Hash *const hash)
// {
// 	size_t size = hash->num_buckets / 2;
// 	if(!size)
// 		++size;
// 	fx_Hash_expandTo(hash, size);
// }

// static void fx_Hash_checkExpand(fx_Hash *const hash)
// {
// 	float ratio = (float) hash->num_entries / (float) hash->num_buckets;
// 	if(ratio > .75)
// 		fx_Hash_expand(hash);
// }

// static void fx_Hash_checkContract(fx_Hash *const hash)
// {
// 	float ratio = (float) hash->num_entries / (float) hash->num_buckets;
// 	if(ratio < .05  &&  hash->num_buckets < DEFAULT_CAPACITY)
// 		fx_Hash_contract(hash);
// }

// // Initialize hash.
// int fx_Hash_init(fx_Hash *const hash, const size_t ks, const size_t vs)
// {
// 	fx_checkPtr(hash);
// 	hash->num_entries = 0;
// 	hash->num_buckets = DEFAULT_CAPACITY;
// 	hash->key_size = ks;
// 	hash->val_size = vs;
// 	hash->hash = NULL;
// 	hash->cmp  = NULL;
// 	hash->buckets = calloc(DEFAULT_CAPACITY, sizeof(fx_HashNode*));
// 	return hash->buckets? 0:1;
// }

// // Sets internal hash function. NULL results in the default.
// void fx_Hash_setHash(fx_Hash *const hash, uint32_t (*func)(const void*))
// {
// 	fx_checkPtr(hash);
// 	hash->hash = func;
// }

// // Sets the comparison function. By default, this is the standard memcmp().
// void fx_Hash_setCmp(fx_Hash *const hash, int (*func)(const void*, const void*))
// {
// 	fx_checkPtr(hash);
// 	hash->cmp = func;
// }

// // Remove all elements. Buckets are left intact.
// void fx_Hash_clear(fx_Hash *const hash)
// {
// 	fx_checkPtr(hash);
// 	for(int i = 0; i < hash->num_buckets; ++i)
// 		if(hash->buckets[i])
// 			fx_Hash_freeBucket(hash, i);
// 	hash->num_entries = 0;
// }

// // Clears hash and deallocates all internal memory. Renders
// // object invalid for future use.
// void fx_Hash_clean(fx_Hash *const hash)
// {
// 	fx_checkPtr(hash);
// 	fx_Hash_clear(hash);
// 	free(hash->buckets);
// 	hash->num_buckets = 0;
// }

// // Inserts key-value pair. If key already exists, replaces its
// // associated value.
// int fx_Hash_put(fx_Hash *const hash, const void *const key, const void *const val)
// {
// 	fx_checkPtr3(hash, key, val);
// 	fx_Hash_checkExpand(hash);

// 	size_t i = fx_Hash_index(hash, key);
// 	fx_HashNode *next = fx_HashNode_from(hash, key, val);
// 	if(!next)
// 		return -1;

// 	fx_HashNode *node = hash->buckets[i];
// 	if(node){
// 		while(node->next){
// 			int cmp = fx_Hash_cmp(hash, KEY_PTR(hash, node), key);
// 			if(cmp == 0){
// 				memmove(VAL_PTR(hash, node), val, hash->val_size);
// 				free(next);
// 				return 0;
// 			}
// 			node = node->next;
// 		}
// 		node->next = next;
// 	} else {
// 		hash->buckets[i] = next;
// 	}
// 	hash->num_entries++;
// 	return 0;
// }

// // Checks for existance of <key>.
// bool fx_Hash_has(const fx_Hash *const hash, const void *const key)
// {
// 	fx_checkPtrs(hash, key);
// 	return fx_Hash_hook(hash, key)? true:false;
// }

// // Removes <key>-value pair. If not existant, does nothing.
// void fx_Hash_rem(fx_Hash *const hash, const void *const key)
// {
// 	fx_checkPtrs(hash, key);
// 	fx_Hash_checkContract(hash);

// 	int i = fx_Hash_index(hash, key);
// 	fx_HashNode *prev = NULL
// 			  , *node = hash->buckets[i];
// 	while(node){
// 		if(!fx_Hash_cmp(hash, KEY_PTR(hash, node), key)){
// 			if(prev){
// 				prev->next = node->next;
// 				free(node);
// 			} else {
// 				hash->buckets[i] = NULL;
// 				free(node);
// 			}
// 			hash->num_entries--;
// 			return;
// 		}
// 		prev = node;
// 		node = node->next;
// 	}
// }

// // Returns pointer to raw data.
// void *fx_Hash_hook(const fx_Hash *const hash, const void *const key)
// {
// 	fx_checkPtrs(hash, key);

// 	fx_HashNode *node = fx_Hash_hookNode(hash, key);
// 	if(!node)
// 		return NULL;
// 	return VAL_PTR(hash, node);
// }

// // Moves data value to address <to>. If key isn't found, does nothing.
// int fx_Hash_fetch(const fx_Hash *const hash, const void *const key, void *const to)
// {
// 	void *data = fx_Hash_hook(hash, key);
// 	if(data){
// 		memmove(to, data, hash->val_size);
// 		return 0;
// 	}
// 	return -1;
// }

// // Applies <func> to all key-value pairs in hash.
// void fx_Hash_forEach(fx_Hash *const hash, void (*func)(const void*, void*))
// {
// 	fx_checkPtrs(hash, func);

// 	for(int i = 0; i < hash->num_buckets; ++i){
// 		fx_HashNode *node = hash->buckets[i];
// 		while(node){
// 			func(KEY_PTR(hash, node), VAL_PTR(hash, node));
// 			node = node->next;
// 		}
// 	}
// }
