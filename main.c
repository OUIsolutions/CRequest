#define CREQUEST_USE_NATIVE_CURL
#include "CRequest/one.h"

int main(){
    CRequestNamespace req = newCRequestNamespace();


    CRequest *r = req.newRequest("localhost:5001/sssaaaseea");
    r->cache_time = 0;
    req.add_query_parram(r,"a1","a2ee");
    req.add_query_parram(r,"a1","a2");
    req.set_body_string(r, "aaaaaaaddd");

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