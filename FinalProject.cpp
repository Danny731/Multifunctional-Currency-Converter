#include <cstdio>
#include <curl/curl.h>
#include<iostream>
#include<fstream>
#include<string>
#include<algorithm>
#include<vector>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

using std::string;
using std::cout;
using std::cin;
using std::to_string;

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

void set_transform_window(string source,float source_amount) {
  float USD, CNY, GBP, EUR, AUD, CAD;
  float USD_RATE, CNY_RATE, GBP_RATE, EUR_RATE, AUD_RATE, CAD_RATE;

// Insert function
  sf::RenderWindow window(sf::VideoMode(200, 300), "Currency Convertor");
  // set background
  sf::RectangleShape background(sf::Vector2f(200.f, 300.f));
  background.setFillColor(sf::Color::White);
  //set font
  sf::Font font;
  font.loadFromFile("/usr/share/fonts/truetype/ubuntu/Ubuntu-BI.ttf");
  // set currency name
  sf::Text cur_1;
  sf::Text cur_2;
  sf::Text cur_3;
  sf::Text cur_4;
  sf::Text cur_5;
  sf::Text cur_6;

  cur_1.setCharacterSize(15);
  cur_2.setCharacterSize(15);
  cur_3.setCharacterSize(15);
  cur_4.setCharacterSize(15);
  cur_5.setCharacterSize(15);
  cur_6.setCharacterSize(15);
  
  cur_1.setFont(font);
  cur_1.setString("USD");
  cur_1.setPosition(0, 0);
  cur_1.setFillColor(sf::Color::Black);

  cur_2.setFont(font);
  cur_2.setString("CNY");
  cur_2.setPosition(0, 50);
  cur_2.setFillColor(sf::Color::Black);

  cur_3.setFont(font);
  cur_3.setString("GBP");
  cur_3.setPosition(0, 100);
  cur_3.setFillColor(sf::Color::Black);

  cur_4.setFont(font);
  cur_4.setString("EUR");
  cur_4.setPosition(0, 150);
  cur_4.setFillColor(sf::Color::Black);

  cur_5.setFont(font);
  cur_5.setString("AUD");
  cur_5.setPosition(0, 200);
  cur_5.setFillColor(sf::Color::Black);

  cur_6.setFont(font);
  cur_6.setString("CAD");
  cur_6.setPosition(0, 250);
  cur_6.setFillColor(sf::Color::Black);
  // set currency value
  sf::Text usd;
  sf::Text cny;
  sf::Text aud;
  sf::Text cad;
  sf::Text gbp;
  sf::Text eur;

  if(source == "USD") {
    USD = source_amount;
    USD_RATE = 1;
    CNY_RATE = get_accurate_exchangeRate(source,get_url_contents(get_source_url(source)),"CNY");
    GBP_RATE = get_accurate_exchangeRate(source,get_url_contents(get_source_url(source)),"GBP");
    EUR_RATE = get_accurate_exchangeRate(source,get_url_contents(get_source_url(source)),"EUR");
    AUD_RATE = get_accurate_exchangeRate(source,get_url_contents(get_source_url(source)),"AUD");
    CAD_RATE = get_accurate_exchangeRate(source,get_url_contents(get_source_url(source)),"CAD");
    CNY = currency_translation(USD, CNY_RATE);
    GBP = currency_translation(USD, GBP_RATE);
    EUR = currency_translation(USD, EUR_RATE);
    AUD = currency_translation(USD, AUD_RATE);
    CAD = currency_translation(USD, CAD_RATE);
    usd.setFont(font);
    usd.setString(to_string(source_amount));
    usd.setCharacterSize(20);
    usd.setPosition(70, 15);
    usd.setFillColor(sf::Color::Black);
    cny.setFont(font);
    cny.setString(to_string(CNY));
    cny.setCharacterSize(20);
    cny.setPosition(70, 65);
    cny.setFillColor(sf::Color::Black);
    gbp.setFont(font);
    gbp.setString(to_string(GBP));
    gbp.setCharacterSize(20);
    gbp.setPosition(70, 115);
    gbp.setFillColor(sf::Color::Black);
    eur.setFont(font);
    eur.setString(to_string(EUR));
    eur.setCharacterSize(20);
    eur.setPosition(70, 165);
    eur.setFillColor(sf::Color::Black);
    aud.setFont(font);
    aud.setString(to_string(AUD));
    aud.setCharacterSize(20);
    aud.setPosition(70, 215);
    aud.setFillColor(sf::Color::Black);
    cad.setFont(font);
    cad.setString(to_string(CAD));
    cad.setCharacterSize(20);
    cad.setPosition(70, 265);
    cad.setFillColor(sf::Color::Black);

  }
  else if(source == "CNY") {
    CNY = source_amount;
    CNY_RATE = 1;
    USD_RATE = get_accurate_exchangeRate(source,get_url_contents(get_source_url(source)),"USD");
    GBP_RATE = get_accurate_exchangeRate(source,get_url_contents(get_source_url(source)),"GBP");
    EUR_RATE = get_accurate_exchangeRate(source,get_url_contents(get_source_url(source)),"EUR");
    AUD_RATE = get_accurate_exchangeRate(source,get_url_contents(get_source_url(source)),"AUD");
    CAD_RATE = get_accurate_exchangeRate(source,get_url_contents(get_source_url(source)),"CAD");
    USD = currency_translation(CNY, USD_RATE);
    GBP = currency_translation(CNY, GBP_RATE);
    EUR = currency_translation(CNY, EUR_RATE);
    AUD = currency_translation(CNY, AUD_RATE);
    CAD = currency_translation(CNY, CAD_RATE);
    usd.setFont(font);
    usd.setString(to_string(USD));
    usd.setCharacterSize(20);
    usd.setPosition(70, 15);
    usd.setFillColor(sf::Color::Black);
    cny.setFont(font);
    cny.setString(to_string(source_amount));
    cny.setCharacterSize(20);
    cny.setPosition(70, 65);
    cny.setFillColor(sf::Color::Black);
    gbp.setFont(font);
    gbp.setString(to_string(GBP));
    gbp.setCharacterSize(20);
    gbp.setPosition(70, 115);
    gbp.setFillColor(sf::Color::Black);
    eur.setFont(font);
    eur.setString(to_string(EUR));
    eur.setCharacterSize(20);
    eur.setPosition(70, 165);
    eur.setFillColor(sf::Color::Black);
    aud.setFont(font);
    aud.setString(to_string(AUD));
    aud.setCharacterSize(20);
    aud.setPosition(70, 215);
    aud.setFillColor(sf::Color::Black);
    cad.setFont(font);
    cad.setString(to_string(CAD));
    cad.setCharacterSize(20);
    cad.setPosition(70, 265);
    cad.setFillColor(sf::Color::Black);

  }
  else if(source == "GBP") {
    GBP = source_amount;
    GBP_RATE = 1;
    CNY_RATE = get_accurate_exchangeRate(source,get_url_contents(get_source_url(source)),"CNY");
    USD_RATE = get_accurate_exchangeRate(source,get_url_contents(get_source_url(source)),"USD");
    EUR_RATE = get_accurate_exchangeRate(source,get_url_contents(get_source_url(source)),"EUR");
    AUD_RATE = get_accurate_exchangeRate(source,get_url_contents(get_source_url(source)),"AUD");
    CAD_RATE = get_accurate_exchangeRate(source,get_url_contents(get_source_url(source)),"CAD");
    CNY = currency_translation(GBP, CNY_RATE);
    USD = currency_translation(GBP, USD_RATE);
    EUR = currency_translation(GBP, EUR_RATE);
    AUD = currency_translation(GBP, AUD_RATE);
    CAD = currency_translation(GBP, CAD_RATE);
    usd.setFont(font);
    usd.setString(to_string(USD));
    usd.setCharacterSize(20);
    usd.setPosition(70, 15);
    usd.setFillColor(sf::Color::Black);
    cny.setFont(font);
    cny.setString(to_string(CNY));
    cny.setCharacterSize(20);
    cny.setPosition(70, 65);
    cny.setFillColor(sf::Color::Black);
    gbp.setFont(font);
    gbp.setString(to_string(source_amount));
    gbp.setCharacterSize(20);
    gbp.setPosition(70, 115);
    gbp.setFillColor(sf::Color::Black);
    eur.setFont(font);
    eur.setString(to_string(EUR));
    eur.setCharacterSize(20);
    eur.setPosition(70, 165);
    eur.setFillColor(sf::Color::Black);
    aud.setFont(font);
    aud.setString(to_string(AUD));
    aud.setCharacterSize(20);
    aud.setPosition(70, 215);
    aud.setFillColor(sf::Color::Black);
    cad.setFont(font);
    cad.setString(to_string(CAD));
    cad.setCharacterSize(20);
    cad.setPosition(70, 265);
    cad.setFillColor(sf::Color::Black);
  }
  else if(source == "EUR") {
    EUR = source_amount;
    EUR_RATE = 1;
    CNY_RATE = get_accurate_exchangeRate(source,get_url_contents(get_source_url(source)),"CNY");
    GBP_RATE = get_accurate_exchangeRate(source,get_url_contents(get_source_url(source)),"GBP");
    USD_RATE = get_accurate_exchangeRate(source,get_url_contents(get_source_url(source)),"USD");
    AUD_RATE = get_accurate_exchangeRate(source,get_url_contents(get_source_url(source)),"AUD");
    CAD_RATE = get_accurate_exchangeRate(source,get_url_contents(get_source_url(source)),"CAD");
    CNY = currency_translation(EUR, CNY_RATE);
    GBP = currency_translation(EUR, GBP_RATE);
    USD = currency_translation(EUR, USD_RATE);
    AUD = currency_translation(EUR, AUD_RATE);
    CAD = currency_translation(EUR, CAD_RATE);
    usd.setFont(font);
    usd.setString(to_string(USD));
    usd.setCharacterSize(20);
    usd.setPosition(70, 15);
    usd.setFillColor(sf::Color::Black);
    cny.setFont(font);
    cny.setString(to_string(CNY));
    cny.setCharacterSize(20);
    cny.setPosition(70, 65);
    cny.setFillColor(sf::Color::Black);
    gbp.setFont(font);
    gbp.setString(to_string(GBP));
    gbp.setCharacterSize(20);
    gbp.setPosition(70, 115);
    gbp.setFillColor(sf::Color::Black);
    eur.setFont(font);
    eur.setString(to_string(source_amount));
    eur.setCharacterSize(20);
    eur.setPosition(70, 165);
    eur.setFillColor(sf::Color::Black);
    aud.setFont(font);
    aud.setString(to_string(AUD));
    aud.setCharacterSize(20);
    aud.setPosition(70, 215);
    aud.setFillColor(sf::Color::Black);
    cad.setFont(font);
    cad.setString(to_string(CAD));
    cad.setCharacterSize(20);
    cad.setPosition(70, 265);
    cad.setFillColor(sf::Color::Black);
  }
  else if(source == "AUD") {
    AUD = source_amount;
    AUD_RATE = 1;
    CNY_RATE = get_accurate_exchangeRate(source,get_url_contents(get_source_url(source)),"CNY");
    GBP_RATE = get_accurate_exchangeRate(source,get_url_contents(get_source_url(source)),"GBP");
    EUR_RATE = get_accurate_exchangeRate(source,get_url_contents(get_source_url(source)),"EUR");
    USD_RATE = get_accurate_exchangeRate(source,get_url_contents(get_source_url(source)),"USD");
    CAD_RATE = get_accurate_exchangeRate(source,get_url_contents(get_source_url(source)),"CAD");
    CNY = currency_translation(AUD, CNY_RATE);
    GBP = currency_translation(AUD, GBP_RATE);
    EUR = currency_translation(AUD, EUR_RATE);
    USD = currency_translation(AUD, USD_RATE);
    CAD = currency_translation(AUD, CAD_RATE);
    usd.setFont(font);
    usd.setString(to_string(USD));
    usd.setCharacterSize(20);
    usd.setPosition(70, 15);
    usd.setFillColor(sf::Color::Black);
    cny.setFont(font);
    cny.setString(to_string(CNY));
    cny.setCharacterSize(20);
    cny.setPosition(70, 65);
    cny.setFillColor(sf::Color::Black);
    gbp.setFont(font);
    gbp.setString(to_string(GBP));
    gbp.setCharacterSize(20);
    gbp.setPosition(70, 115);
    gbp.setFillColor(sf::Color::Black);
    eur.setFont(font);
    eur.setString(to_string(EUR));
    eur.setCharacterSize(20);
    eur.setPosition(70, 165);
    eur.setFillColor(sf::Color::Black);
    aud.setFont(font);
    aud.setString(to_string(source_amount));
    aud.setCharacterSize(20);
    aud.setPosition(70, 215);
    aud.setFillColor(sf::Color::Black);
    cad.setFont(font);
    cad.setString(to_string(CAD));
    cad.setCharacterSize(20);
    cad.setPosition(70, 265);
    cad.setFillColor(sf::Color::Black);
  }
  else if(source == "CAD") {
    CAD = source_amount;
    CAD_RATE = 1;
    CNY_RATE = get_accurate_exchangeRate(source,get_url_contents(get_source_url(source)),"CNY");
    GBP_RATE = get_accurate_exchangeRate(source,get_url_contents(get_source_url(source)),"GBP");
    EUR_RATE = get_accurate_exchangeRate(source,get_url_contents(get_source_url(source)),"EUR");
    AUD_RATE = get_accurate_exchangeRate(source,get_url_contents(get_source_url(source)),"AUD");
    USD_RATE = get_accurate_exchangeRate(source,get_url_contents(get_source_url(source)),"USD");
    CNY = currency_translation(CAD, CNY_RATE);
    GBP = currency_translation(CAD, GBP_RATE);
    EUR = currency_translation(CAD, EUR_RATE);
    AUD = currency_translation(CAD, AUD_RATE);
    USD = currency_translation(CAD, USD_RATE);
    usd.setFont(font);
    usd.setString(to_string(USD));
    usd.setCharacterSize(20);
    usd.setPosition(70, 15);
    usd.setFillColor(sf::Color::Black);
    cny.setFont(font);
    cny.setString(to_string(CNY));
    cny.setCharacterSize(20);
    cny.setPosition(70, 65);
    cny.setFillColor(sf::Color::Black);
    gbp.setFont(font);
    gbp.setString(to_string(GBP));
    gbp.setCharacterSize(20);
    gbp.setPosition(70, 115);
    gbp.setFillColor(sf::Color::Black);
    eur.setFont(font);
    eur.setString(to_string(EUR));
    eur.setCharacterSize(20);
    eur.setPosition(70, 165);
    eur.setFillColor(sf::Color::Black);
    aud.setFont(font);
    aud.setString(to_string(AUD));
    aud.setCharacterSize(20);
    aud.setPosition(70, 215);
    aud.setFillColor(sf::Color::Black);
    cad.setFont(font);
    cad.setString(to_string(source_amount));
    cad.setCharacterSize(20);
    cad.setPosition(70, 265);
    cad.setFillColor(sf::Color::Black);
  }

  
  

  // set lines
  sf::RectangleShape l1(sf::Vector2f(350.f, 2.f));
  sf::RectangleShape l2(sf::Vector2f(350.f, 2.f));
  sf::RectangleShape l3(sf::Vector2f(350.f, 2.f));
  sf::RectangleShape l4(sf::Vector2f(350.f, 2.f));
  sf::RectangleShape l5(sf::Vector2f(350.f, 2.f));
  l1.setFillColor(sf::Color::Black);
  l2.setFillColor(sf::Color::Black);
  l3.setFillColor(sf::Color::Black);
  l4.setFillColor(sf::Color::Black);
  l5.setFillColor(sf::Color::Black);
  l1.setPosition(0, 40);
  l2.setPosition(0, 90);
  l3.setPosition(0, 140);
  l4.setPosition(0, 190);
  l5.setPosition(0, 240);

  //set flag pics
  sf::Texture usaflag;
  usaflag.loadFromFile("usa.jpeg");
  sf::Texture chinaflag;
  chinaflag.loadFromFile("china.jpeg");
  sf::Texture ukflag;
  ukflag.loadFromFile("uk.jpeg");
  sf::Texture eurflag;
  eurflag.loadFromFile("eur.jpeg");
  sf::Texture ausflag;
  ausflag.loadFromFile("aus.jpeg");
  sf::Texture caflag;
  caflag.loadFromFile("canada.jpeg");

  sf::Sprite usaf;
  usaf.setTexture(usaflag);
  usaf.scale(sf::Vector2f(0.1155f,0.115f));
  usaf.setPosition(1,19);
  sf::Sprite chinaf;
  chinaf.setTexture(chinaflag);
  chinaf.scale(sf::Vector2f(0.072f,0.072f));
  chinaf.setPosition(0.5,69);
  sf::Sprite ukf;
  ukf.setTexture(ukflag);
  ukf.scale(sf::Vector2f(0.0355f,0.05f));
  ukf.setPosition(0.5,119);
  sf::Sprite eurf;
  eurf.setTexture(eurflag);
  eurf.scale(sf::Vector2f(0.045f,0.045f));
  eurf.setPosition(0.5,169);
  sf::Sprite ausf;
  ausf.setTexture(ausflag);
  ausf.scale(sf::Vector2f(0.06f,0.075f));
  ausf.setPosition(0.5,219);
  sf::Sprite caf;
  caf.setTexture(caflag);
  caf.scale(sf::Vector2f(0.093f,0.085f));
  caf.setPosition(0.5,269);

  while (window.isOpen()) {
    sf::Event event;
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed)
        window.close();
    }
    //  words.setString(to_string(now.tm_hour) + ":" +
    //  to_string(now.tm_min) + ":" + to_string(now.tm_sec));
    
    window.draw(background);
    window.draw(l1);
    window.draw(l2);
    window.draw(l3);
    window.draw(l4);
    window.draw(l5);
    window.draw(cur_1);
    window.draw(usd);
    window.draw(cny);
    window.draw(cad);
    window.draw(aud);
    window.draw(gbp);
    window.draw(eur);
    window.draw(cur_2);
    window.draw(cur_3);
    window.draw(cur_4);
    window.draw(cur_5);
    window.draw(cur_6);
    window.draw(usaf);
    window.draw(chinaf);
    window.draw(ukf);
    window.draw(eurf);
    window.draw(ausf);
    window.draw(caf);
    window.display();

  }
}

int main() {
  string source;
  float source_amount;
  cout << "Choose a source currency. Commands: " << "\n";
  cout << "CNY,USD,GBP,EUR,AUD,CAD"<< "\n";
  cin >> source;
  cout << "How much source currency do you have: " << "\n";
  cin >> source_amount;
  set_transform_window(source,source_amount);
  return 0;
}
