#include <cstdio>
#include <curl/curl.h>
#include<iostream>
#include<fstream>
#include<string>
#include<algorithm>
#include<iomanip>

using std::string;
using std::cout;
using std::cin;
using std::setprecision;

size_t writeFunction(void *ptr, size_t size, size_t nmemb, std::string* data) {
  data->append((char*) ptr, size * nmemb);
  return size * nmemb;
}

string get_source_url(string source) {
  string url;
  if (source == "CNY")
  url = "http://apilayer.net/api/live?access_key=5fb7031283d6c916732e110820671fc9&currencies=EUR,GBP,CAD,USD,AUD&source=CNY&format=1";
  else if (source == "USD")
  url = "http://apilayer.net/api/live?access_key=5fb7031283d6c916732e110820671fc9&currencies=EUR,GBP,CAD,CNY,AUD&source=USD&format=1";
  else if (source == "GBP")
  url = "http://apilayer.net/api/live?access_key=5fb7031283d6c916732e110820671fc9&currencies=EUR,CAD,USD,CNY,AUD&source=GBP&format=1";
  else if (source == "EUR")
  url = "http://apilayer.net/api/live?access_key=5fb7031283d6c916732e110820671fc9&currencies=GBP,CAD,USD,CNY,AUD&source=EUR&format=1";
  else if (source == "AUD")
  url = "http://apilayer.net/api/live?access_key=5fb7031283d6c916732e110820671fc9&currencies=EUR,GBP,CAD,USD,CNY&source=AUD&format=1";
  else if (source == "CAD")
  url = "http://apilayer.net/api/live?access_key=5fb7031283d6c916732e110820671fc9&currencies=EUR,GBP,USD,CNY,AUD&source=CAD&format=1";
  return url;
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

float get_accurate_exchangeRate(string source,string resp, string target) {
  float exchangeRate;
  resp.erase(std::remove_if(resp.begin(), resp.end(), isalpha), resp.end());
  resp.erase(std::remove_if(resp.begin(), resp.end(), isspace), resp.end());
  if(source == "EUR") {
    if (target == "GBP")
        exchangeRate = std::stof(resp.substr(60,7));
    else if (target == "CAD")
        exchangeRate = std::stof(resp.substr(72,7));
    else if (target == "USD")
        exchangeRate = std::stof(resp.substr(84,7));
    else if (target == "CNY")
        exchangeRate = std::stof(resp.substr(96,7));
    else if (target == "AUD")
        exchangeRate = std::stof(resp.substr(108,7));
  }
  if(source == "GBP") {
    if (target == "EUR")
        exchangeRate = std::stof(resp.substr(60,7));
    else if (target == "CAD")
        exchangeRate = std::stof(resp.substr(72,7));
    else if (target == "USD")
        exchangeRate = std::stof(resp.substr(84,7));
    else if (target == "CNY")
        exchangeRate = std::stof(resp.substr(96,7));
    else if (target == "AUD")
        exchangeRate = std::stof(resp.substr(108,7));
  }
  if(source == "CAD") {
      if (target == "EUR")
        exchangeRate = std::stof(resp.substr(60,7));
      if (target == "GBP")
        exchangeRate = std::stof(resp.substr(72,7));
      if (target == "USD")
        exchangeRate = std::stof(resp.substr(84,7));
      if (target == "CNY")
        exchangeRate = std::stof(resp.substr(96,7));
      if (target == "AUD")
        exchangeRate = std::stof(resp.substr(108,7));
  }
  if(source == "USD") {
      if (target == "EUR")
        exchangeRate = std::stof(resp.substr(60,7));
      if (target == "GBP")
        exchangeRate = std::stof(resp.substr(72,7));
      if (target == "CAD")
        exchangeRate = std::stof(resp.substr(84,7));
      if (target == "CNY")
        exchangeRate = std::stof(resp.substr(96,7));
      if (target == "AUD")
        exchangeRate = std::stof(resp.substr(108,7));
  }
  if(source == "CNY") {
      if (target == "EUR")
        exchangeRate = std::stof(resp.substr(60,7));
      if (target == "GBP")
        exchangeRate = std::stof(resp.substr(72,7));
      if (target == "CAD")
        exchangeRate = std::stof(resp.substr(84,7));
      if (target == "USD")
        exchangeRate = std::stof(resp.substr(96,7));
      if (target == "AUD")
        exchangeRate = std::stof(resp.substr(108,7));
  }
  if(source == "AUD") {
      if (target == "EUR")
        exchangeRate = std::stof(resp.substr(60,7));
      if (target == "GBP")
        exchangeRate = std::stof(resp.substr(72,7));
      if (target == "CAD")
        exchangeRate = std::stof(resp.substr(84,7));
      if (target == "USD")
        exchangeRate = std::stof(resp.substr(96,7));
      if (target == "CNY")
        exchangeRate = std::stof(resp.substr(108,7));
  }
  
  return exchangeRate;
}

float currency_translation(float source_amount, float exchangeRate) {
  float target_amount = source_amount * exchangeRate;
  return target_amount;
}

int main() {
  string source, url, resp, target,ex;

  float source_amount,exchangeRate,target_amount;
  source = "CNY";
  target = "GBP";
  source_amount = 100;

  url = get_source_url(source);  
  resp = get_url_contents(url);
  exchangeRate = get_accurate_exchangeRate(source,resp,target);
  cout << exchangeRate << "\n";
  target_amount = currency_translation(source_amount,exchangeRate);
  cout << "You have " << target_amount << target << "\n";
  return 0;
}
