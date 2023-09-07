

CRequestNamespace newCRequestNamespace(){
    CRequestNamespace self = {0};
    self.newRequest = newCRequest;
    self.add_headder = CRequest_add_headder;
    self.add_query_parram = CRequest_add_query_parram;
    self.set_body = CRequest_set_body;
    self.set_body_string = CRequest_set_body_string;
    self.set_b64_body =CRequest_set_b64_body;
    self.set_body_json = CRequest_set_body_json;
    self.set_body_file = CRequest_set_body_file;
    self.get_any_response = CRequest_get_any_response;
    self.get_string_response = CRequest_get_string_response;
    self.get_json_response = CRequest_get_json_response;

    self.represent = CRequest_represent;
    self.free = CRequest_free;
    return self;
}