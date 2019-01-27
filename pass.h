#include <stdio.h>
#include <stdlib.h>
#include "pthread.h"

pthread_mutex_t lock;//coaster lock
pthread_mutex_t pasLock;//passenger lock
pthread_mutex_t openLock;//prevent passengers to jump right in, when the coaster is not open yet.

pthread_cond_t coa;//conditional variable on rollarcoaster
pthread_cond_t pas;//conditional variable on passengers that are on the train.
pthread_cond_t openWait;//conditional variable for waiting coaster to open;
pthread_cond_t waitLine;//conditional variable for the waiting

int open; //flag to check whtether the rollar coaster opens or not.
int start;//start flag of the rollarcoaster
int capacity;//capacity of the rollar coaster.
int currentPassenger; //number of current passenger.
int remainPassenger; //number of remaining passenger


void takeRide(int *d);
void waitCoaster(int *id);
void canRide(int *id);
void onRide(int *id);
void offRide(int *id);
