#include <stdio.h>
#include <stdlib.h>
#include "pass.h"

void takeRide(int *id){
  waitCoaster(id);
  canRide(id);
  onRide(id);
  offRide(id);
}

void waitCoaster(int *id){
  pthread_mutex_lock(&openLock);
  while(open==0){
    printf("Passenger %d is waiting for the rollar coaster to open\n",*id);
    pthread_cond_wait(&openWait,&openLock);
  }
  pthread_mutex_unlock(&openLock);
}

void canRide(int *id){
  pthread_mutex_lock(&pasLock);
  // while(open==0){
  //   printf("Passenger %d is waiting for the rollar coaster to open\n",*id);
  //   pthread_cond_wait(&pas,&pasLock);
  // }
  while(currentPassenger==capacity || start==0){//start = 0 prevents pass to get into the coaster when coaster is not really for loading
    printf("Passenger %d is waiting\n",*id);
    pthread_cond_wait(&waitLine,&pasLock);
  }
  pthread_mutex_unlock(&pasLock);
}

void onRide(int *id){
  pthread_mutex_lock(&pasLock);
  currentPassenger++;
  remainPassenger--;
  printf("Passenger %d gets on the coaster\n",*id);
  pthread_cond_broadcast(&coa);//wake up the rollar coaster
  while(start==1){// on the rollar coaster;
    pthread_cond_wait(&pas,&pasLock);
  }
  pthread_mutex_unlock(&pasLock);
}

void offRide(int *id){
  pthread_mutex_lock(&pasLock);
  currentPassenger--;
  printf("Passenger %d gets off the coaster\n",*id);
  pthread_cond_broadcast(&coa);//wake up the rollar coaster
  pthread_mutex_unlock(&pasLock);
}
