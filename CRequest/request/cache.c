
char  * CRequest_assign_requisition(CRequest *self){
    DtwHash *hash = newDtwHash();
    DtwHash_digest_string(hash,self->method);
    DtwHash_digest_string(hash,self->private_url);
    for(int i = 0; i < self->private_paramns->size; i++){
        CRequestKeyVal *current = self->private_paramns->elements[i];
        DtwHash_digest_string(hash,current->key);
        DtwHash_digest_string(hash,current->value);
    }
    for(int i = 0; i < self->private_headers->size; i++){
        CRequestKeyVal *current = self->private_headers->elements[i];
        DtwHash_digest_string(hash,current->key);
        DtwHash_digest_string(hash,current->value);
    }
    if(self->private_body){
        DtwHash_digest_any(hash,self->private_body,self->private_body_size);
    }
    if(self->private_body_file){
        DtwHash_digest_file(hash,self->private_body_file);
    }
    char *result = strdup(hash->hash);
    DtwHash_free(hash);
    return result;
}

char * CRequest_get_cache_response_location(CRequest *self){
    CTextStack * location = newCTextStack_string_empty();
    char *sha = CRequest_assign_requisition(self);
    CTextStack_format(location,"%s/response/%s",self->cache_location,sha);
    free(sha);
    return CTextStack_self_transform_in_string_and_self_clear(location);
}


char * CRequest_get_cache_body_location(CRequest *self){
    CTextStack * location = newCTextStack_string_empty();
    char *sha = dtw_generate_sha_from_any(self->private_body,self->private_body_size);
    CTextStack_format(location,"%s/body/%s",self->cache_location,sha);
    free(sha);
    return CTextStack_self_transform_in_string_and_self_clear(location);

}
char * CRequest_clear_expired_cache(CRequest *self){

    CTextStack  *cache_body_location = newCTextStack_string_empty();
    CTextStack_format(cache_body_location, "%s/body", self->cache_location);
    dtw_remove_any(cache_body_location->rendered_text);
    CTextStack_free(cache_body_location);

    CTextStack  *cache_response_location = newCTextStack_string_empty();
    CTextStack_format(cache_response_location, "%s/response/%s", self->cache_location);
    DtwStringArray *elements = dtw_list_files(cache_response_location->rendered_text, DTW_CONCAT_PATH);
    for(int i =0; i < elements->size; i++){
        char *current = elements->strings[i];
        if(!CRequest_valid_cache_file(self,current)){
            dtw_remove_any(current);
        }
    }

    CTextStack_free(cache_response_location);
    DtwStringArray_free(elements);
}
