
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

  void calAddr(unsigned long addr, unsigned long *tag, unsigned long *idx,
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
      if (cache[i][idx].valid && cache[i][idx].tag == tag) {
        return i;
      }
    }
    return -1;
  }

  void access(unsigned long addr) {
    unsigned long offset, tag, idx;
    CURRENT_TIMESTAMP += 1;
    calAddr(addr, &tag, &idx, &offset);
    int setNumber = findSetNumber(tag, idx);
    if (setNumber != -1) {
      HIT++;
      if (REPLACE_POLICY == 0)
        cache[setNumber][idx].timestamp = CURRENT_TIMESTAMP;
    } else {
      MISS++;
      replacementPolicy(tag, idx, REPLACE_POLICY);
    }
  }

  void replacementPolicy(unsigned long tag, unsigned long idx, int type) {
    if (type == 1)
      RR(tag, idx);
    else
      LRU(tag, idx);
  }

  void LRU(unsigned long tag, unsigned long idx) {
    int minTimestampIndex = 0;
    int minTimestamp = cache[0][idx].timestamp;
    for (int i = 0; i < SET_SIZE; i++) {
      if (cache[i][idx].timestamp < minTimestamp) {
        minTimestamp = cache[i][idx].timestamp;
        minTimestampIndex = i;
      }
    }
    cache[minTimestampIndex][idx].tag = tag;
    cache[minTimestampIndex][idx].valid = 1;
    cache[minTimestampIndex][idx].timestamp = CURRENT_TIMESTAMP;
  }

  void RR(unsigned long tag, unsigned long idx) {
    long long nextCacheSet = (currentCacheSet[idx] + 1) % SET_SIZE;
    cache[nextCacheSet][idx].tag = tag;
    cache[nextCacheSet][idx].valid = 1;
    cache[nextCacheSet][idx].timestamp = CURRENT_TIMESTAMP;
    currentCacheSet[idx] = nextCacheSet;
  }
};

int main(int argc, char *argv[]) {
  CacheSim cacheSim;

  printf("CacheSim v.2015\n");
  printf("This program is designed for class exercise only.\n");
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
  printf("SET SIZE: %d\n", SET_SIZE);
  printf("METHOD: %s\n", REPLACE_POLICY == 0 ? "LRU" : "RR");
  printf("BLOCK SIZE: %d\n", BLOCK_SIZE);
  printf("INDEX SIZE: %d\n", INDEX_SIZE);
  printf("CACHE SIZE: %d\n", CACHE_SIZE);
  printf("HIT: %d\nMISS: %d\n", cacheSim.HIT, cacheSim.MISS);
  long long all = cacheSim.HIT + cacheSim.MISS;
  double hitrate = (double)cacheSim.HIT / (double)all;
  double missrate = (double)cacheSim.MISS / (double)all;
  printf("HIT rate: %.7f\nMISS rate: %.7f\n", hitrate, missrate);
  return 0;
}