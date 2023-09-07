#define CREQUEST_USE_NATIVE_CURL
#include "CRequest/one.h"

int main(){

    CRequestNamespace req = newCRequestNamespace();
    CRequest *r = req.newRequest("localhost:5000/sssaaaseea");
    req.add_query_parram(r,"name","teste5.jpg");
    long size;
    unsigned char *content = dtw_load_binary_content("aaa.jpg", &size);
    req.set_body(r,content,size);
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