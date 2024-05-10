//utils.c
#include "utils.h"

void BubbleSort(CHELTUIALA_P Array, Cmp cmp, int len){
    if(len<=1)
        return;
    bool sort=0;
    while(!sort){
        sort=1;
        for(int i=0; i< len - 1; i++)
            if(!cmp(Array[i], Array[i+1])){
                CHELTUIALA c = Array[i];
                Array[i] = Array[i+1];
                Array[i+1] = c;
                sort = 0;
            }
    }
}

/*
void SelectionSort(CHELTUIALA_P Array, Cmp cmp, int len){
    for(int i=0;i<len;i++)
        for(int j=i+1;j<len;j++)
            if(!cmp(Array[i], Array[j])){
                CHELTUIALA c = Array[i];
                Array[i] = Array[j];
                Array[j] = c;
            }
}
 */
