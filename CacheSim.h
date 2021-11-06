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
#define REPLACE_POLICY 0  // 0 -> LRU, 1 -> RR
#define SET_SIZE 1
#define CACHE_SIZE 1024
#define INDEX_SIZE 256
#define BLOCK_SIZE 4
#define TAGLEN 22
#define INDEXLEN 8
#define OFFSETLEN 2
typedef unsigned char Byte;
typedef struct Cache {
  char valid;
  char dirty;
  int timestamp;
  unsigned long tag;
  Byte data[BLOCK_SIZE];
};

#endif  // CACHESIM_H_INCLUDED