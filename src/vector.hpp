#ifndef VECTOR_H
#define VECTOR_H
#include <stdio.h>
class vectorInt{
public:
    int x;
    int y;

    vectorInt(int x, int y){
        this->x = x;
        this->y = y;
    }

    vectorInt(){
        this->x = NULL;
        this->y = NULL;
    }

    
};
#endif
