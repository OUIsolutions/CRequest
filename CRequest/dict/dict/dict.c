

CRequestDict * newCRequestDict(){
    CRequestDict *self = (CRequestDict*) malloc(sizeof (CRequestDict));
    self->elements = malloc(0);
    self->size = 0;
}

void CRequestDict_set_element(const char *key, const char *value){
    
}