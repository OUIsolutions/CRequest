//
// Created by mateusmoutinho on 04/09/23.
//
#include "CRequest/one.h"

int main(){
    CRequestNamespace req = newCRequestNamespace();
    CRequest *r = req.newRequest(
"https://www.nwf.org/-/media/NEW-WEBSITE/Shared-Folder/Wildlife/Mammals/mammal_mule-deer-California_Richard-Douse_600x300.ashx"

            );
    r->driver_location = "drivers/curl";
    long size;
    bool isbinary;
    char *result = (char*) CRequest_get_any_response(r, &size, &isbinary);


    req.free(r);



}