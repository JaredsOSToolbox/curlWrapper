#include <iostream>
#include <string>
#include <vector>

#include <curl/curl.h> //your directory may be different

//string data; //will hold the url's contents
//std::vector<char> data = std::vector<char>();
static std::vector<std::string> data = std::vector<std::string>();

size_t writeCallback(char* buf, size_t size, size_t nmemb, void* up) { //callback must have this declaration
    //buf is a pointer to the data that curl has for us
    //size*nmemb is the size of the buffer
    //
    if (!data.empty()) { std::cout << "clearing" << std::endl; data.clear(); }
    data.push_back(buf);

    return size*nmemb; //tell curl how many bytes we handled
}

class curlWrapper {
  public:
    curlWrapper();
    ~curlWrapper();
    //static size_t callBack(char*, size_t, size_t, void*);

    void get(std::string);
    //static std::vector<std::string> getData();
  private:
    CURL* curl;
    //static std::vector<std::string> data;
};

//size_t curlWrapper::callBack(char* buffer, size_t size, size_t nmemb, void* up) {
  //data.push_back(buffer);
  //return (size * nmemb);
//}


curlWrapper::curlWrapper() {
  curl_global_init(CURL_GLOBAL_ALL);
  this->curl = curl_easy_init();
}

void curlWrapper::get(std::string url) {
    curl_easy_setopt(this->curl, CURLOPT_URL, url.c_str());
    curl_easy_setopt(this->curl, CURLOPT_WRITEFUNCTION, &writeCallback);
    curl_easy_perform(this->curl);
}

//std::vector<std::string> curlWrapper::getData() {
  //return data;
//}

curlWrapper::~curlWrapper() {
    curl_easy_cleanup(this->curl);
    curl_global_cleanup();
}

int main(){
    curlWrapper wrapper = curlWrapper();
    wrapper.get("https://google.com");
    for(std::string line : data) {
      std::cout << line << std::endl;
    }

    wrapper.get("https://google.com");

    return 0;
}
