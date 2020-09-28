#include <iostream>
#include <string>
#include <sstream>
#include <memory>
#include <json/json.h>

using namespace std;

int main(){
    std::string s = "{\"Age\" : 26,\"Lang\" : \"c++\",\"Name\" : \"zhangsan\"}";
    JSONCPP_STRING errs;    // 错误信息
    Json::Value root;       //反序列化后的json
    Json::CharReaderBuilder rb;
    std::unique_ptr< Json::CharReader > const jsonReader(rb.newCharReader());

    bool res = jsonReader->parse(s.data(), s.data()+s.size(), &root, &errs);
    if(!res || !errs.empty()){
        cout << "json parse error" << endl;
        return 1;
    }

    cout << s << endl;
    cout << root["Age"].asInt() << endl;
    cout <<  root["Lang"].asString() << endl;
    cout << root["Name"].asString() << endl;
    return 0;
}
