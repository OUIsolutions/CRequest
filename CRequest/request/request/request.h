

#define CREQUEST_NOT_RESPOND 1
#define CREQUEST_NOT_A_STRING 2
#define CREQUEST_NOT_VALID_JSON 3


typedef struct CRequest{

    const char * driver_location;
    int cache_time;
    bool delete_cache;
    bool clear_expired_cache;
    const char * cache_location;
    const char *method;
    bool error;
    const char *error_menssage;


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

char * CRequest_get_cache_response_location(CRequest *self);

char * CRequest_get_cache_body_location(CRequest *self);

bool CRequest_valid_cache_file(CRequest *self,const char *file);




char * CRequest_get_string_response(CRequest *self);

cJSON *CRequest_get_json_response(CRequest *self);

void CRequest_free(CRequest *self);

void CRequest_represent(CRequest *self);

