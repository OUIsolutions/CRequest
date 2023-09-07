#define CREQUEST_USE_CUSTOM_DRIVER
#include "CRequest/one.h"

int main(){

    CRequestNamespace req = newCRequestNamespace();
    CRequest *r = req.newRequest("localhost:5000/sssaaaseea");
    r->driver_location = ".CRequest/curl";
    req.add_query_parram(r,"name","teste5.jpg");
    req.set_body_file(r,"aaa.jpg");
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