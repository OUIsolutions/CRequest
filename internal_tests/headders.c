#define CREQUEST_USE_NATIVE_CURL
#include "CRequest/one.h"

int main(){
    CRequestNamespace req = newCRequestNamespace();
    CRequest *r = req.newRequest("localhost:5001/sssaaaseea");
    req.add_headder(r,"a1","aaawssss");
    req.add_headder(r,"a2","aaaxxxx");

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