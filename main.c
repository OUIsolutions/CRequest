//
// Created by mateusmoutinho on 04/09/23.
//
#include "CRequest/CRequest.h"

int main(){

    CRequest *t = newCRequest("google.com.br");

    CRequest_add_headder(t, "aa", "bbbb");
    CRequest_add_query_parram(t, "aaaaaa", "bbbbb");
    //CRequest_set_body_string(t,"aaaaaaaaaaaaaaa");
    CRequest_represent(t);


}