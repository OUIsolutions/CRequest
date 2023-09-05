//
// Created by mateusmoutinho on 04/09/23.
//
#include "CRequest/CRequest.h"

int main(){
    CRequestNamespace req = newCRequestNamespace();
    CRequest *t = req.newRequest("google.com.br");

    req.add_headder(t, "aa", "bbbb");
    req.add_query_parram(t, "aaaaaa", "bbbbb");
    //CRequest_set_body_string(t,"aaaaaaaaaaaaaaa");
    req.represent(t);


}