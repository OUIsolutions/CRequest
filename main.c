//
// Created by mateusmoutinho on 04/09/23.
//
#include "CRequest/one.h"

int main(){
    CRequestNamespace req = newCRequestNamespace();

    CRequest *r = req.newRequest("https://jsonplaceholder.typicode.com/todos/1");

    cJSON *element = req.get_json_response(r);
    printf("%s", cJSON_Print(element));

    req.free(r);



}