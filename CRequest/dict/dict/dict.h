

typedef struct CRequestDict{
    CRequestKeyVal **elements;
    int size;
}CRequestDict;

CRequestDict * newCRequestDict();

void CRequestDict_set_element(const char *key, const char *value);


