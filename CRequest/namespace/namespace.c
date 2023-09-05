

CRequestNamespace newCRequestNamespace(){
    CRequestNamespace self = {0};
    self.newRequest = newCRequest;
    self.add_headder = CRequest_add_headder;
    self.add_query_parram = CRequest_add_query_parram;
    self.set_body = CRequest_set_body;
    self.set_body_string = CRequest_set_body_string;
    self.set_b64_body =CRequest_set_b64_body;
    self.set_body_json = CRequest_set_body_json;
    self.represent = CRequest_represent;
    self.free = CRequest_free;
    return self;
}