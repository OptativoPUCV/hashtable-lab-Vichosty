#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include "hashmap.h"

typedef struct Pair Pair;
typedef struct HashMap HashMap;
int enlarge_called=0;

struct Pair {
     char * key;
     void * value;
};

struct HashMap {
    Pair ** buckets;
    long size; //cantidad de datos/pairs en la tabla
    long capacity; //capacidad de la tabla
    long current; //indice del ultimo dato accedido
};

Pair * createPair( char * key,  void * value) {
    Pair * new = (Pair *)malloc(sizeof(Pair));
    new->key = key;
    new->value = value;
    return new;
}

long hash( char * key, long capacity) {
    unsigned long hash = 0;
     char * ptr;
    for (ptr = key; *ptr != '\0'; ptr++) {
        hash += hash*32 + tolower(*ptr);
    }
    return hash%capacity;
}

int is_equal(void* key1, void* key2){
    if(key1==NULL || key2==NULL) return 0;
    if(strcmp((char*)key1,(char*)key2) == 0) return 1;
    return 0;
}


void insertMap(HashMap * map, char * key, void * value) {
  long cap = hash(key, map ->capacity);

  
  for (; cap < map->capacity ;cap++){
    if ( (map -> buckets[cap] == NULL) || ( map -> buckets[cap] -> key == NULL)){
      break;
    }
    if (cap == map -> capacity-1){
      cap = -1;
    }
  }
  
  map -> buckets[cap] = createPair(key,value);
  map -> size++;
  



}

void enlarge(HashMap * map) {
    enlarge_called = 1; //no borrar (testing purposes)


}


HashMap * createMap(long capacity) {
  HashMap * map = (HashMap *)malloc(sizeof(HashMap));
  map->buckets = (Pair **) calloc (capacity,sizeof(Pair *));
  map->size =0;
  map->capacity = capacity;
  map->current = -1;
  return map;

}

void eraseMap(HashMap * map,  char * key) {//pair->key=NULL
long cap = hash(key, map -> capacity);
for (; cap < map->capacity ;cap++){
    if (map -> buckets[cap] == NULL){
      break;
    }
    if (is_equal(key,map -> buckets[cap] -> key)){
      map->buckets[cap] -> key = NULL;
      map -> size = map -> size -1;
    }
  }
}

void * searchMap(HashMap * map,  char * key) {   
  long cap = hash(key, map -> capacity);
  for (; cap < map->capacity ;cap++){
    if (map -> buckets[cap] == NULL){
      break;
    }
    if (is_equal(key,map -> buckets[cap] -> key)){
      map -> current = cap;
      return map-> buckets[cap] -> value;
    }
  }
  return NULL;
}

void * firstMap(HashMap * map) {
  int cap = 0;
  
  
  return map -> buckets[cap];
}

void * nextMap(HashMap * map) {

    return NULL;
}
