#include <cstdio>
#include <curl/curl.h>
#include<iostream>
#include<fstream>
#include<string>

using std::string;
using std::cout;
using std::cin;

size_t writeFunction(void *ptr, size_t size, size_t nmemb, std::string* data) {
  data->append((char*) ptr, size * nmemb);
  return size * nmemb;
}

string get_url_contents(string theurl) {
  CURL *curl;
  CURLcode res;
  string response_string;
  curl_global_init(CURL_GLOBAL_DEFAULT);
  curl = curl_easy_init();
  if(curl) {
    curl_easy_setopt(curl, CURLOPT_URL, theurl.c_str());
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeFunction);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response_string);
    res = curl_easy_perform(curl);
    if(res != CURLE_OK)
      fprintf(stderr, "curl_easy_perform() failed: %s\n",
              curl_easy_strerror(res));
    curl_easy_cleanup(curl);
  }
  curl_global_cleanup();
  return response_string;
}


int main() {
  string source;
  string url;
  string resp;
  cout << "Choose a source currency. Commands: " << "\n";
  cout << "CNY, USD, GBP, EUR, AUD, CAD"<< "\n";
  cin >> source;
  if (source == "CNY")
  url = "http://apilayer.net/api/live?access_key=5fb7031283d6c916732e110820671fc9&currencies=EUR,GBP,CAD,USD,AUD&source=CNY&format=1";
  else if (source == "USD")
  url = "http://apilayer.net/api/live?access_key=5fb7031283d6c916732e110820671fc9&currencies=EUR,GBP,CAD,CNY,AUD&source=USD&format=1";
  else if (source == "GBP")
  url = "http://apilayer.net/api/live?access_key=5fb7031283d6c916732e110820671fc9&currencies=EUR,USD,CAD,CNY,AUD&source=GBP&format=1";
  else if (source == "EUR")
  url = "http://apilayer.net/api/live?access_key=5fb7031283d6c916732e110820671fc9&currencies=GBP,USD,CAD,CNY,AUD&source=EUR&format=1";
  else if (source == "AUD")
  url = "http://apilayer.net/api/live?access_key=5fb7031283d6c916732e110820671fc9&currencies=EUR,USD,CAD,CNY,GBP&source=AUD&format=1";
  else if (source == "CAD")
  url = "http://apilayer.net/api/live?access_key=5fb7031283d6c916732e110820671fc9&currencies=EUR,USD,AUD,CNY,GBP&source=CAD&format=1";
    
  resp = get_url_contents(url);
  cout << resp << "\n";

  return 0;
}
