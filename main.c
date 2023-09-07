#define CREQUEST_USE_NATIVE_CURL
#include "CRequest/one.h"

int main(){
    CRequestNamespace req = newCRequestNamespace();


    CRequest *r = req.newRequest("localhost:5000");


    req.add_query_parram(r,"a1","a2");
    req.add_query_parram(r,"a2","a2");
    //req.add_headder(r,"b1","bb");
    //req.add_headder(r,"b2","cc");

    char *response = req.get_string_response(r);
    if(!r->error){
        printf("%s",response);
        free(response);
    }
    else{
        printf("%s",r->error_menssage);
    }



    req.free(r);



}