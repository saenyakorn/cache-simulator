/**
 * CacheSim.c
 * This program is designed for class exercise only.
 * It is provided as is. There is no warranty or support of any kind.
 *
 * Krerk Piromsopa, Ph.D.
 * Department of Computer Engineering
 * Chulalongkorn University
 * Bangkok, Thailand.
 *
 * History
 * 2013 - Initial design
 * 2015 - Refactor/Clean code
 **/
#include <stdio.h>
#include <string.h>

#include "CacheSim.h"

class CacheSim {
 public:
  long MISS;
  long HIT;
  long CURRENT_TIMESTAMP;
  int currentCacheSet[INDEX_SIZE];
  struct Cache cache[SET_SIZE][INDEX_SIZE];

  CacheSim() {
    MISS = 0;
    HIT = 0;
    CURRENT_TIMESTAMP = 0;
    for (int i = 0; i < SET_SIZE; i++) {
      for (int j = 0; j < INDEX_SIZE; j++) {
        cache[i][j].valid = 0;
        cache[i][j].tag = 0;
        cache[i][j].dirty = 0;
        cache[i][j].timestamp = 0;
        currentCacheSet[j] = 0;
      }
    }
  }

  int calAddr(unsigned long addr, unsigned long *tag, unsigned long *idx,
              unsigned long *offset) {
    unsigned long tmp;
    int i;
    *tag = addr >> (OFFSETLEN + INDEXLEN);
    tmp = 0;
    for (i = 0; i < INDEXLEN; i++) {
      tmp <<= 1;
      tmp |= 0x01;
    }
    *idx = addr >> OFFSETLEN & tmp;
    tmp = 0;
    for (i = 0; i < OFFSETLEN; i++) {
      tmp <<= 1;
      tmp |= 0x01;
    }
    *offset = addr & tmp;
  }

  int findSetNumber(unsigned long tag, unsigned long idx) {
    for (int i = 0; i < SET_SIZE; i++) {
      if (cache[i][idx].valid == 1 && cache[i][idx].tag == tag) {
        return i;
      }
    }
    return -1;
  }

  void access(unsigned long addr) {
    unsigned long offset, tag, idx;
    CURRENT_TIMESTAMP += 1;
    calAddr(addr, &tag, &idx, &offset);
    int setNumber = this->findSetNumber(tag, idx);
    if (setNumber != -1) {
      this->HIT++;
    } else {
      this->MISS++;
      this->replacementPolicy(tag, idx, REPLACE_POLICY);
    }
  }

  void replacementPolicy(unsigned long tag, unsigned long idx, int type) {
    switch (type) {
      case 0:
        LRU(tag, idx);
      case 1:
        RR(tag, idx);
      default:
        LRU(tag, idx);
    }
  }

  void LRU(unsigned long tag, unsigned long idx) {
    int minTimestampIndex = 0;
    for (int i = 0; i < SET_SIZE; i++) {
      if (cache[i][idx].valid == 1 && cache[i][idx].tag == tag) {
        minTimestampIndex = i;
      }
    }
    cache[minTimestampIndex][idx].tag = tag;
    cache[minTimestampIndex][idx].valid = 1;
    cache[minTimestampIndex][idx].timestamp = this->CURRENT_TIMESTAMP;
  }

  void RR(unsigned long tag, unsigned long idx) {
    int nextCacheSet = (currentCacheSet[idx] + 1) % SET_SIZE;
    cache[nextCacheSet][idx].tag = tag;
    cache[nextCacheSet][idx].valid = 1;
    cache[nextCacheSet][idx].timestamp = this->CURRENT_TIMESTAMP;
    currentCacheSet[idx] = nextCacheSet;
  }
};

int main(int argc, char *argv[]) {
  CacheSim cacheSim;

  printf("CacheSim v.2015\n");
  printf("This program is designed for class exercise only.\n");
  printf("By Krerk Piromsopa, Ph.D.\n");
  FILE *input;
  char buff[1025];
  unsigned long myaddr;
  if (argc < 2) {
    fprintf(stderr, "Usage:\n\t%s address_file\n", argv[0]);
    return 1;
  }
  input = fopen(argv[1], "r");
  // read file
  while (fgets(&buff[0], 1024, input)) {
    sscanf(buff, "0x%x", &myaddr);
    cacheSim.access(myaddr);
  }
  printf("HIT:%7d MISS: %7d\n", cacheSim.HIT, cacheSim.MISS);
}