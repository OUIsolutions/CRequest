//
// Created by mateusmoutinho on 04/09/23.
//
#include "CRequest/CRequest.h"

int main(){

    CRequest *t = newCRequest("google.com.br");

    CRequest_set_headder(t,"aa","bbbb");
    CRequest_represent(t);

}