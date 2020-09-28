#ifndef _REM_HPP_
#define _REM_HPP_

#include <iostream>
#include <stdio.h>
#include <string>
#include <memory>
#include <sstream>
#include <json/json.h>
#include <base/http.h>

#define SPEECH_ASR "asr.wav"
#define VOICE_PATH "voice"

using namespace std;

class TuLin{
public:
    TuLin(){};
    ~TuLin(){};
    // 接收消息(反序列化)
    string ResponsePinkup(string& str)
    {
       JSONCPP_STRING errs;     // 错误信息
       Json::Value root;        // 反序列化的json
       Json::CharReaderBuilder rb;
       std::unique_ptr< Json::CharReader > jsonReader(rb.newCharReader());

       bool res = jsonReader->parse(str.data(), str.data()+str.size(), &root, &errs);
       if(!res || !errs.empty()){
            return errs;
       }

       Json::Value results = root["results"];
       Json::Value values = results[0]["values"];
       // cout << values["text"].asString() << endl;
       return values["text"].asString();

    }

    // 聊天接口(序列化)
    string Chat(string& message){
        // 创建Json字符串root
        Json::Value root;
        Json::StreamWriterBuilder wb;
        std::ostringstream os;
        
        // root的reqType
        root["reqType"] = 0;
        
        // root的perception
        Json::Value text;
        text["text"] = message;
        Json::Value inputText;
        inputText["inputText"] = text;
        root["perception"] = inputText;

        // root的userInfor
        Json::Value user;
        user["apiKey"] = apikey;
        user["userId"] = userId;
        root["userInfo"] = user;
        
        std::unique_ptr <Json::StreamWriter> jsonwrite(wb.newStreamWriter());
        jsonwrite->write(root, &os);
        std::string body = os.str();
        
        // 收到图灵机器人的回应response
        string response;
        int status_code = client.post(url, nullptr, body, nullptr, &response);
        if(status_code != CURLcode::CURLE_OK){
            cout << "http request error!!!" << endl;
            return "";
        }
        // cout << "Rem: " << response << endl;
        return ResponsePinkup(response);
    }

private:
    string url = "http://openapi.tuling123.com/openapi/api/v2";
    string apikey = "70ff58d07a414294a520a3aa20327eb1";
    string userId = "1";
    aip::HttpClient client;

};

class Rem{
public:
    string Exec(string& cmd, bool is_print)
    {
        FILE* fp = popen(cmd.c_str(), "r");
        if(fp == nullptr){
            cout << "popen error!!!" << endl;
        }
        
        string result;
        if(is_print){
            char c;
            size_t len = 0;
            while((len = fread(&c, 1, 1, fp)) > 0){
                result += c;
            }
            cout << result << endl;
        }

        pclose(fp);
    }

    void Run()
    {
        string cmd = "arecord -t wav -c 1 -r 16000 -d 5 -f S16_LE ";
        cmd += VOICE_PATH;
        cmd += '/';
        cmd += SPEECH_ASR; 

        Exec(cmd, false);
    }

private:
    TuLin tl;
};

#endif

