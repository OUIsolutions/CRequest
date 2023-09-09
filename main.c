#define CREQUEST_USE_LIBCURL
#include "CRequest/one.h"

int main(){
    CRequestNamespace req = newCRequestNamespace();
    CRequest *r = req.newRequest("localhost:5000/sssaaaseea");
    req.add_query_parram(r,"a1","a2ee");
    req.add_query_parram(r,"a1","a2");

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