//
// Created by mateusmoutinho on 04/09/23.
//
#include "CRequest/one.h"

int main(){
    CRequestNamespace req = newCRequestNamespace();

    CRequest *r = req.newRequest("https://woliveiras.com.br/posts/como-instalar-o-nodejs-via-bin%C3%A1rios-tar-xz-no-linux/");

    char *t = req.get_string_response(r);
    printf("%s",t);


    req.free(r);



}