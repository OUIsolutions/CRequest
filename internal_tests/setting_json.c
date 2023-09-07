#define CREQUEST_USE_NATIVE_CURL
#include "CRequest/one.h"

int main(){

    CRequestNamespace req = newCRequestNamespace();
    CRequest *r = req.newRequest("localhost:5001/sssaaaseea");

    cJSON *json = cJSON_CreateObject();
    cJSON_AddStringToObject(json,"aaaa","aaaaaaaa");
    req.set_body_json(r,json);
    cJSON_Delete(json);
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