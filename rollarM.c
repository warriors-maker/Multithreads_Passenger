#include "rollar.h"
#include "pass.h"
#include <stdio.h>
#include <stdlib.h>
#include "pthread.h"

int main(int argc,char *argv[]){
  initCoaster(atoi(argv[1]),atoi(argv[2]));
  pthread_t passList[remainPassenger];//at the beginning the remainPassenger is total.
  pthread_t coaster;
  //initialization
  pthread_mutex_init(&lock,NULL);//lock for the rollar coaster
  pthread_mutex_init(&pasLock,NULL);//lock for the passenger
  pthread_mutex_init(&openLock,NULL); //lock for the open
  pthread_cond_init(&openWait,NULL);//cond for waitOpen cart
  pthread_cond_init(&coa,NULL);//conditional variable for rollar coaster.
  pthread_cond_init(&pas,NULL);//conditional variable for pas
  pthread_cond_init(&waitLine,NULL);//conditional variable for waiting pass

  int total = remainPassenger;
  //puts("Hi");
  //coaster thread created;
  pthread_create(&coaster,NULL,(void*)startRoaster,NULL);

  //customer thread created;
  int num = 0;

  while(num < total){
    //printf("the total is%d\n",total);
    int *ptr = malloc(sizeof(int));
    *ptr = num;
    pthread_create(&passList[num],NULL,(void*)takeRide,ptr);
    num++;
  }

  //main wait for everyone
  for(int n=0; n<total; n++){
    //printf("the total is%d\n",total);
    pthread_join(passList[n],NULL);
    //puts("I am here");
  }
  pthread_join(coaster,NULL);
  puts("-----------------------------");
  puts("No more Passengers, we close");
}
