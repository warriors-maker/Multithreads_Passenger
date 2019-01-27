#include <stdio.h>
#include <stdlib.h>
#include "rollar.h"
#include "pass.h"
#include <unistd.h>

void initCoaster(int total, int cap){
  //puts("Input the number of capacity of the cart:");
  capacity = cap; //get the capacity of the cart
  //puts("Input the number of passengers");
  remainPassenger = total;// get the number of passenger
  currentPassenger = 0;
  start = 0;
  open = 0;
}

void startRoaster(){
  openCoaster();
  while(remainPassenger!=0){
    puts("-----------------------------");
    puts("New Round!");
    //printf("start:%d,remainPassenger:%d,currentPassenger:%d\n",start,remainPassenger,currentPassenger);
    //printf("currentPassenger is %d\n",currentPassenger);
    //printf("start is %d\n",start);
    loadCustomer();
    puts("rollarCoaster starts...");
    sleep(1); //let them Play
    puts("rollarCoaster comes back safely...");
    unloadCustomer();
    puts("Passengers all get of the rollar coaster for this cycle");
  }
}

void openCoaster(){
  pthread_mutex_lock(&openLock);
    open=1;//flag indicate that the coaster is opene
    start=1;//indicate that the coaster is loading;
  pthread_mutex_unlock(&openLock);
}

void loadCustomer(){
  pthread_mutex_lock(&lock);
  start=1;
  puts("RollarCoaster loading passangers...");
  pthread_cond_broadcast(&waitLine);//wake up the passenger(first time will not be used)
  pthread_cond_broadcast(&openWait);//wake up the passenger (only the first time)
  while(currentPassenger!=capacity && remainPassenger != 0){
    //puts("I am sleeping inside!");
    pthread_cond_wait(&coa,&lock);//coaster wait for passenger
    //puts("I am ready to wake up!");
  }
  puts("Passengers finished loading, Lets Go!");
  pthread_mutex_unlock(&lock);
}

void unloadCustomer(){
  //puts("rollarCoaster comes back saftely");
  pthread_mutex_lock(&lock);
  //rollarCoaster finishes;
  start = 0;
  //wake up all the Passengers(mostly everyone)
  //those on the rollarCoaster and those on the waiting lie
  pthread_cond_broadcast(&pas);
  while(currentPassenger!=0){
    pthread_cond_wait(&coa,&lock);
  }
  //1 cycle is finished;
  pthread_mutex_unlock(&lock);
}
