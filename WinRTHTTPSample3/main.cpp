#include "pch.h"
#include <winrt\Windows.Web.Http.h>
#include <winrt\Windows.Data.Json.h>
#include <winrt\Windows.Storage.Streams.h>
#include <iostream>
#include <string>
using namespace winrt;
using namespace Windows::Foundation;
using namespace Windows::Data::Json;
using namespace Windows::Web::Http;
using namespace std;


const std::wstring llm_type{L"gpt2"};
const std::wstring pipeline_type{L"action" };

const std::wstring prompt_type{L"text"};
const std::wstring prompt{L"what is an operating system"};
const std::wstring lobe_url{L"http://localhost:5002/execute"};


int main()
{
    init_apartment();
    Uri uri(lobe_url);
    JsonObject lobeJsonRequest;

    lobeJsonRequest.Insert(pipeline_type, JsonValue::CreateStringValue(llm_type));
    lobeJsonRequest.Insert(prompt_type, JsonValue::CreateStringValue(prompt));

    auto httpContent = ::HttpStringContent(
        lobeJsonRequest.Stringify(),
        winrt::Windows::Storage::Streams::UnicodeEncoding::Utf8,
        L"application/json");
    winrt::Windows::Web::Http::HttpClient client;
    auto response = client.PostAsync(uri, httpContent).get();
    auto responseBody = response.Content().ReadAsStringAsync().get();
    auto responseJson = JsonObject::Parse(responseBody);
    
    string gpt_res = to_string(responseJson.GetNamedString(L"text"));
    cout << "GPT response: " << gpt_res.c_str() << endl;
 }
