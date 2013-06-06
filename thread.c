/*
 * Copyright 2013 Thomas Abraham (methomasabraham@gmail.com), BSD-style copyright and disclaimer apply
 */

#include<unistd.h>
#include<stdio.h>
#include<pthread.h>

struct args{
  int a,b;
};

void* myThreadFunction(void * argstruct){
  int i;
  struct args *myargs = argstruct;

  for(i=1;i<100000;i++){
    printf("In Child : %d\n",i);
  }

  return myargs->a+myargs->b;
}

int main(){
  int i;
  struct args myargs;
  pthread_t thread_id;
  
  myargs.a=10;
  myargs.b=15;
  
  pthread_create (&thread_id, NULL, &myThreadFunction, &myargs);
  
  for(i=1;i<100000;i++){
    printf("In Parent : %d\n",i);
  }

  pthread_join(thread_id,&i);
  printf("Result returned by the thread : %d\n",i);

  return 0;
}

