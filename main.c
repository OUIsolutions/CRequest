//
// Created by mateusmoutinho on 04/09/23.
//
#include "CRequest/CRequest.h"

int main(){
    CRequestNamespace req = newCRequestNamespace();
    CRequest *r = req.newRequest("google.com.br");

    req.add_headder(r, "aa", "bbbb");
    req.add_query_parram(r, "aaaaaa", "bbbbb");
    req.set_body_string(r,"aaaaaaaaaaaaaaa");
    req.represent(r);
    req.free(r);



}