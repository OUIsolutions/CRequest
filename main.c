#define CREQUEST_DEBUB
#include "CRequest/one.h"

int main(){

    CRequestNamespace req = newCRequestNamespace();
    CRequest *r = req.newRequest("pt.wikipedia.org");

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