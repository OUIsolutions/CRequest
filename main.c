//
// Created by mateusmoutinho on 04/09/23.
//
#include "CRequest/CRequest.h"

int main(){
    CRequestNamespace req = newCRequestNamespace();
    CRequest *r = req.newRequest("google.com.br");
    r->binary_location = "curl";
    req.add_headder(r, "aa", "bbbb");
    req.add_query_parram(r, "aaaaaa", "bbbbb");
    req.set_body_string(r,"aaaaaaaaaaaaaaa");
    long size;
    bool isbinary;
    char *result = (char*)CRequest_get_any(r,&size,&isbinary);
    printf("%s",result);
    
    req.free(r);



}