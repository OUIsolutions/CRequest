//
// Created by mateusmoutinho on 05/09/23.
//


unsigned char * private_CRequest_get_any_response_using_cache(CRequest *self, long *size, bool *is_binary) {

    CRequest_clear_expired_cache(self);
    char *response_cache_location = CRequest_get_cache_response_location(self);
    if(CRequest_valid_cache_file(self, response_cache_location)){
        unsigned  char *content = dtw_load_any_content(response_cache_location, size, is_binary);
        free(response_cache_location);
        return content;
    }
    CTextStack *url = private_CRequest_format_url(self);
    CURL *curl = curl_easy_init();
    curl_easy_setopt(curl, CURLOPT_URL, url);


    CURLcode res;

    res = curl_easy_perform(curl);
    if (res != CURLE_OK) {
        self->error = CREQUEST_NOT_RESPOND;
        self->error_menssage = "requisition not respond\n";
        curl_easy_cleanup(curl);
    }
    curl_easy_cleanup(curl);

    *is_binary= false;
    *size = strlen("a");
    return (unsigned char*) strdup("a");

}

unsigned char * CRequest_get_any_response(CRequest *self, long *size, bool *is_binary) {


    if(self->use_cache){
        return private_CRequest_get_any_response_using_cache(self,size,is_binary);
    }


    return NULL;
}