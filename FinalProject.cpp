#include <cstdio>
#include <curl/curl.h>
#include<iostream>
#include<fstream>
#include<string>
#include<algorithm>
#include<iomanip>
#include<vector>

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
  std::vector<int> pos;
  resp.erase(std::remove_if(resp.begin(), resp.end(), isalpha), resp.end());
  resp.erase(std::remove_if(resp.begin(), resp.end(), isspace), resp.end());

  string flag=",";
  int position=0;
  int i=1;

  while((position=resp.find(flag,position))!=string::npos) {
      pos.push_back(position);
      position++;
      i++;
  }

  if(source == "EUR") {
    if (target == "GBP")
        exchangeRate = std::stof(resp.substr(60,pos.at(5)-61));
    else if (target == "CAD")
        exchangeRate = std::stof(resp.substr(pos.at(5)+4,pos.at(6)-pos.at(5)-4));
    else if (target == "USD")
        exchangeRate = std::stof(resp.substr(pos.at(6)+4,pos.at(7)-pos.at(6)-4));
    else if (target == "CNY")
        exchangeRate = std::stof(resp.substr(pos.at(7)+4,pos.at(8)-pos.at(7)-4));
    else if (target == "AUD")
        exchangeRate = std::stof(resp.substr(pos.at(8)+4,4));
  }
  if(source == "GBP") {
    if (target == "EUR")
        exchangeRate = std::stof(resp.substr(60,pos.at(5)-61));
    else if (target == "CAD")
        exchangeRate = std::stof(resp.substr(pos.at(5)+4,pos.at(6)-pos.at(5)-4));
    else if (target == "USD")
        exchangeRate = std::stof(resp.substr(pos.at(6)+4,pos.at(7)-pos.at(6)-4));
    else if (target == "CNY")
        exchangeRate = std::stof(resp.substr(pos.at(7)+4,pos.at(8)-pos.at(7)-4));
    else if (target == "AUD")
        exchangeRate = std::stof(resp.substr(pos.at(8)+4,4));
  }
  if(source == "CAD") {
      if (target == "EUR")
        exchangeRate = std::stof(resp.substr(60,pos.at(5)-61));
      if (target == "GBP")
        exchangeRate = std::stof(resp.substr(pos.at(5)+4,pos.at(6)-pos.at(5)-4));
      if (target == "USD")
        exchangeRate = std::stof(resp.substr(pos.at(6)+4,pos.at(7)-pos.at(6)-4));
      if (target == "CNY")
        exchangeRate = std::stof(resp.substr(pos.at(7)+4,pos.at(8)-pos.at(7)-4));
      if (target == "AUD")
        exchangeRate = std::stof(resp.substr(pos.at(8)+4,4));
  }
  if(source == "USD") {
      if (target == "EUR")
        exchangeRate = std::stof(resp.substr(60,pos.at(5)-61));
      if (target == "GBP")
        exchangeRate = std::stof(resp.substr(pos.at(5)+4,pos.at(6)-pos.at(5)-4));
      if (target == "CAD")
        exchangeRate = std::stof(resp.substr(pos.at(6)+4,pos.at(7)-pos.at(6)-4));
      if (target == "CNY")
        exchangeRate = std::stof(resp.substr(pos.at(7)+4,pos.at(8)-pos.at(7)-4));
      if (target == "AUD")
        exchangeRate = std::stof(resp.substr(pos.at(8)+4,4));
  }
  if(source == "CNY") {
      if (target == "EUR")
        exchangeRate = std::stof(resp.substr(60,pos.at(5)-61));
      if (target == "GBP")
        exchangeRate = std::stof(resp.substr(pos.at(5)+4,pos.at(6)-pos.at(5)-4));
      if (target == "CAD")
        exchangeRate = std::stof(resp.substr(pos.at(6)+4,pos.at(7)-pos.at(6)-4));
      if (target == "USD")
        exchangeRate = std::stof(resp.substr(pos.at(7)+4,pos.at(8)-pos.at(7)-4));
      if (target == "AUD")
        exchangeRate = std::stof(resp.substr(pos.at(8)+4,4));
  }
  if(source == "AUD") {
      if (target == "EUR")
        exchangeRate = std::stof(resp.substr(60,pos.at(5)-61));
      if (target == "GBP")
        exchangeRate = std::stof(resp.substr(pos.at(5)+4,pos.at(6)-pos.at(5)-4));
      if (target == "CAD")
        exchangeRate = std::stof(resp.substr(pos.at(6)+4,pos.at(7)-pos.at(6)-4));
      if (target == "USD")
        exchangeRate = std::stof(resp.substr(pos.at(7)+4,pos.at(8)-pos.at(7)-4));
      if (target == "CNY")
        exchangeRate = std::stof(resp.substr(pos.at(8)+4,4));
  }
  
  return exchangeRate;
}

float currency_translation(float source_amount, float exchangeRate) {
  float target_amount = source_amount * exchangeRate;
  return target_amount;
}

int main() {
  string source, url, resp, target;

  float source_amount,exchangeRate,target_amount;
  cout << "Choose a source currency. Commands: " << "\n";
  cout << "CNY,USD,GBP,EUR,AUD,CAD"<< "\n";
  cin >> source;
  cout << "Choose a currency you want to translate to:" << "\n";
  cin >> target;
  cout << "How much source currency do you have: " << "\n";
  cin >> source_amount;
  url = get_source_url(source);  
  resp = get_url_contents(url);
  exchangeRate = get_accurate_exchangeRate(source,resp,target);
  target_amount = currency_translation(source_amount,exchangeRate);
  cout << "You have " << target_amount << target << "\n";
  return 0;
}
