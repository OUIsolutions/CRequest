

typedef struct CRequestDict{
    CRequestKeyVal **elements;
    int size;
}CRequestDict;

CRequestDict * newCRequestDict();

void CRequestDict_set_element(CRequestDict *self,const char *key, const char *value);

void CRequestDict_represent(CRequestDict *self);

void CRequestDict_free(CRequestDict *self);