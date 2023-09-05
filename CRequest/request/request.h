

#define CREQUEST_NOT_RESPOND 1
#define CREQUEST_NOT_A_STRING 2
#define CREQUEST_NOT_VALID_JSON 3


typedef struct CRequest{

    const char * binary_location;
    int cache_time;
    bool use_cache;
    bool clear_cache;
    const char * cache_location;
    const char *method;
    bool error_code;
    char *error_menssage;


    char *private_url;
    CRequestDict  *private_paramns;
    CRequestDict  *private_headers;
    long private_body_size;
    const char *private_body_file;
    unsigned char *private_body;



}CRequest;

CRequest * newCRequest(const char *url);


void CRequest_add_query_parram(CRequest *self, const char *key, const char *value);

void CRequest_add_headder(CRequest *self, const char *key, const char *value);

void CRequest_set_body(CRequest *self,unsigned char *body,long size);

void CRequest_set_b64_body(CRequest *self,unsigned char *body,long size);

void CRequest_set_body_string(CRequest *self,const char *body);

void CRequest_resset_body(CRequest *self);

void CRequest_set_body_json(CRequest *self,cJSON *body);

char * CRequest_assign_requisition(CRequest *self);

char * CRequest_get_cache_location(CRequest *self);


unsigned char * CRequest_get_any(CRequest *self,long *size,bool *is_binary);

char * CRequest_get_string(CRequest *self);

cJSON *CRequest_get_json(CRequest *self);

void CRequest_free(CRequest *self);

void CRequest_represent(CRequest *self);

