

#define CREQUEST_NOT_RESPOND 1
#define CREQUEST_NOT_A_STRING 2
#define CREQUEST_NOT_VALID_JSON 3


typedef struct CRequest{

    const char * binary_location;
    int cache_time;
    bool use_cache;
    const char * cache_location;
    const char *method;
    char *url;
    CRequestDict  *paramns;
    CRequestDict  *headers;

    bool error_code;
    char *error_menssage;

    long body_size;
    unsigned char *body;


}CRequest;

CRequest newCRequest(const char *url);


void CRequest_set_param(CRequest *self,const char *key, const char *value);

void CRequest_set_headder(CRequest *self,const char *key, const char *value);

void CRequest_set_body(CRequest *self,unsigned char *body,long size);

void CRequest_set_b64_body(CRequest *self,unsigned char *body,long size);

void CRequest_set_body_string(CRequest *self,const char *body);

void CRequest_resset_body(CRequest *self);

void CRequest_set_body_json(CRequest *self,cJSON *body);



unsigned char * CRequest_get_any(CRequest *self,long *size,bool *is_binary);

char * CRequest_get_string(CRequest *self);

cJSON *CRequest_get_json(CRequest *self);

void CRequest_represent(CRequest *self);

