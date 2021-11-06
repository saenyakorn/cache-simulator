/**
 * CacheSim.h
 * This program is designed for class exercise only.
 * It is provided as is. There is no warranty or support of any kind.
 *
 * Krerk Piromsopa, Ph.D.
 * Department of Computer Engineering
 * Chulalongkorn University
 * Bangkok, Thailand.
 **/
#ifndef CACHESIM_H_INCLUDED
#define CACHESIM_H_INCLUDED

/* Please adjust parameters here */
#define REPLACE_POLICY 1  // 0 -> LRU, 1 -> RR
#define SET_SIZE 4
#define BLOCK_SIZE_BITS 2  // log2 of BLOCK_SIZE
#define BLOCK_SIZE (1 << BLOCK_SIZE_BITS)
#define INDEX_SIZE_BITS 6  // log2 of INDEX_SIZE
#define INDEX_SIZE (1 << INDEX_SIZE_BITS)
#define CACHE_SIZE (SET_SIZE * BLOCK_SIZE * INDEX_SIZE)

#define TAGLEN (32 - BLOCK_SIZE_BITS - INDEX_SIZE_BITS)
#define INDEXLEN (INDEX_SIZE_BITS)
#define OFFSETLEN (BLOCK_SIZE_BITS)

typedef unsigned char Byte;
typedef struct Cache {
  char valid;
  char dirty;
  int timestamp;
  unsigned long tag;
  Byte data[BLOCK_SIZE];
};

#endif  // CACHESIM_H_INCLUDED