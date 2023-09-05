//
// Created by mateusmoutinho on 05/09/23.
//

void private_CRequest_format_url(CRequest *self,CTextStack *comand) {
    CTextStack_format(comand, " %s", self->private_url);
    long size = self->private_paramns->size;
    if(!size){
        return;
    }

    CTextStack * test_inclusion = newCTextStack_string(self->private_url);
    if(CTextStack_index_of(test_inclusion,"?") == -1 ){
        CTextStack_format(comand,"?");
    }
    if(size >= 1){
        CRequestKeyVal  *current = self->private_paramns->elements[0];
        CTextStack_format(comand,"%s=%s",current->key,current->value);
    }
    if(size == 1){
        return;
    }

    for(int i = 1;i <size; i++){
        CRequestKeyVal  *current = self->private_paramns->elements[i];
        CTextStack_format(comand,"&%s=%s",current->key,current->value);
    }


}

void private_CRequest_format_curl_comand(CRequest *self,CTextStack *comand){
    if(self->use_native_curl){
        CTextStack_format(comand,"curl");
    }
    else{
        #ifdef __linux__
                CTextStack_format(comand,"./%s",self->binary_location);
        #elif _win32
                CTextStack_format(comand,"%s",self->binary_location);
        #endif
    }
}

void private_CRequest_format_headers(CRequest *self,CTextStack *comand){

    for(int i = 0; i < self->private_headers->size; i++){
        CRequestKeyVal  *current = self->private_headers->elements[i];
        CTextStack_format(comand," -H \"%s:%s\"",current->key,current->value);
    }

}

unsigned char * CRequest_get_any(CRequest *self,long *size,bool *is_binary){
    char *response_cache_location = CRequest_get_cache_response_location(self);

    if(CRequest_valid_cache_file(self, response_cache_location)){
        unsigned  char *content = dtw_load_any_content(response_cache_location, size, is_binary);
        free(response_cache_location);
        return content;
    }

    dtw_create_dir_recursively(response_cache_location);

    CTextStack *comand = newCTextStack_string_empty();


    private_CRequest_format_curl_comand(self,comand);
    private_CRequest_format_url(self,comand);
    private_CRequest_format_headers(self,comand);
    CTextStack_format(comand, " -X %s", self->method);

    if(self->private_body_file){
        CTextStack_format(comand, " -d %s", self->private_body_file);
    }

    char * body_path = NULL;
    if(self->private_body){
        body_path = CRequest_get_cache_body_location(self);
        if(!CRequest_valid_cache_file(self,body_path)){
            dtw_write_any_content(body_path,self->private_body,self->private_body_size);
        }
        CTextStack_format(comand, " -d %s", body_path);
    }


    CTextStack_format(comand, " -L -o  %s", response_cache_location);
    printf("comando :%s\n",comand->rendered_text);

    system(comand->rendered_text);
    CTextStack_free(comand);

    unsigned  char *result = dtw_load_any_content(response_cache_location, size, is_binary);

    if(self->delete_cache){
        dtw_remove_any(response_cache_location);
        if(body_path){
            dtw_remove_any(body_path);
        }
    }

    free(response_cache_location);
    if(body_path){
        free(body_path);
    }

    return result;
}