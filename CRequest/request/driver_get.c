//
// Created by mateusmoutinho on 05/09/23.
//


void private_CRequest_format_curl_comand(CRequest *self,CTextStack *comand){

    #ifdef CREQUEST_USE_NATIVE_CURL
        CTextStack_format(comand,"curl ");
    #else
            #ifdef __linux__

            CTextStack_format(comand," ./%s ",self->driver_location);
            #elif _win32
                    CTextStack_format(comand,"%s",self->binary_location);
            #endif

        #ifndef  CREQUEST_USE_CUSTOM_DRIVER
            if(dtw_entity_type(self->driver_location) == DTW_NOT_FOUND){
                long  size;
                unsigned char * content = dtw_base64_decode(CREQUEST_B64_DRIVER,&size);
                dtw_write_any_content(self->driver_location,content,size);
                CTextStack  *permission_comand = newCTextStack_string_empty();
                CTextStack_format(permission_comand,"chmod +x %s", self->driver_location);
                system(permission_comand->rendered_text);
                CTextStack_free(permission_comand);
                free(content);
            }
        #endif

#endif
}

void private_CRequest_format_headers(CRequest *self,CTextStack *comand){

    for(int i = 0; i < self->private_headers->size; i++){
        CRequestKeyVal  *current = self->private_headers->elements[i];
        CTextStack_format(comand," -H \"%s:%s\"",current->key,current->value);
    }

}

unsigned char * CRequest_get_any_response(CRequest *self, long *size, bool *is_binary){

    CRequest_clear_expired_cache(self);
    char *response_cache_location = CRequest_get_cache_response_location(self);

    if(CRequest_valid_cache_file(self, response_cache_location)){
        unsigned  char *content = dtw_load_any_content(response_cache_location, size, is_binary);
        free(response_cache_location);
        return content;
    }

    char *response_dir= dtw_concat_path(self->cache_location,"response");
    dtw_create_dir_recursively(response_dir);
    free(response_dir);
    CTextStack *comand = newCTextStack_string_empty();

    private_CRequest_format_curl_comand(self,comand);
    CTextStack_format(comand, "'%tc'",private_CRequest_format_url(self));
#ifndef CREQUEST_DEBUB
    CTextStack_format(comand, " -s ");
#endif

    CTextStack_format(comand, " -L ");
    private_CRequest_format_headers(self,comand);
    CTextStack_format(comand, " -X %s", self->method);

    if(self->private_body_file){
        CTextStack_format(comand, "  --data-binary '@%s'", self->private_body_file);
    }

    if(self->private_body){
        char * body_path = CRequest_get_cache_body_location(self);
        dtw_write_any_content(body_path,self->private_body,self->private_body_size);
        CTextStack_format(comand, " --data-binary '@%s'", body_path);
        free(body_path);
    }


    CTextStack_format(comand, " -o  %s ", response_cache_location);

    //printf("comand %s\n",comand->rendered_text);;

    int comand_result = system(comand->rendered_text);
    if(comand_result != 0){

        self->error = CREQUEST_NOT_RESPOND;
        self->error_menssage = "requisition not respond\n";
    }
    printf("comand:%s\n",comand->rendered_text);
    CTextStack_free(comand);

    unsigned  char *result = dtw_load_any_content(response_cache_location, size, is_binary);


    free(response_cache_location);



    return result;
}