//Libraries included
#include <curl/curl.h>
#include <iostream>
#include <string>
#include <vector>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

using std::string;
using std::cout;
using std::cin;
using std::to_string;
using std::endl;
using std::vector;
//using library curl to get string response from internet using API
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
//The function to return accurate exchange rate
float get_accurate_exchangeRate(string source, string resp, string target) {
  float exchangeRate;
  std::vector<int> pos;
  resp.erase(std::remove_if(resp.begin(), resp.end(), isalpha), resp.end());
  resp.erase(std::remove_if(resp.begin(), resp.end(), isspace), resp.end());

  string flag = ",";
  int position = 0;
  int i = 1;

  while((position = resp.find(flag, position)) != string::npos) {
    pos.push_back(position);
    position++;
    i++;
  }

  if(source == target)
    exchangeRate = 1;
  if(source == "EUR") {
    if (target == "GBP")
      exchangeRate = std::stof(resp.substr(60, pos.at(5) - 61));
    else if (target == "CAD")
      exchangeRate = std::stof(resp.substr(pos.at(5) + 4, pos.at(6) - pos.at(5) - 4));
    else if (target == "USD")
      exchangeRate = std::stof(resp.substr(pos.at(6) + 4, pos.at(7) - pos.at(6) - 4));
    else if (target == "CNY")
      exchangeRate = std::stof(resp.substr(pos.at(7) + 4, pos.at(8) - pos.at(7) - 4));
    else if (target == "AUD")
      exchangeRate = std::stof(resp.substr(pos.at(8) + 4, 4));
  }
  if(source == "GBP") {
    if (target == "EUR")
      exchangeRate = std::stof(resp.substr(60, pos.at(5) - 61));
    else if (target == "CAD")
      exchangeRate = std::stof(resp.substr(pos.at(5) + 4, pos.at(6) - pos.at(5) - 4));
    else if (target == "USD")
      exchangeRate = std::stof(resp.substr(pos.at(6) + 4, pos.at(7) - pos.at(6) - 4));
    else if (target == "CNY")
      exchangeRate = std::stof(resp.substr(pos.at(7) + 4, pos.at(8) - pos.at(7) - 4));
    else if (target == "AUD")
      exchangeRate = std::stof(resp.substr(pos.at(8) + 4, 4));
  }
  if(source == "CAD") {
    if (target == "EUR")
      exchangeRate = std::stof(resp.substr(60, pos.at(5) - 61));
    if (target == "GBP")
      exchangeRate = std::stof(resp.substr(pos.at(5) + 4, pos.at(6) - pos.at(5) - 4));
    if (target == "USD")
      exchangeRate = std::stof(resp.substr(pos.at(6) + 4, pos.at(7) - pos.at(6) - 4));
    if (target == "CNY")
      exchangeRate = std::stof(resp.substr(pos.at(7) + 4, pos.at(8) - pos.at(7) - 4));
    if (target == "AUD")
      exchangeRate = std::stof(resp.substr(pos.at(8) + 4, 4));
  }
  if(source == "USD") {
    if (target == "EUR")
      exchangeRate = std::stof(resp.substr(60, pos.at(5) - 61));
    if (target == "GBP")
      exchangeRate = std::stof(resp.substr(pos.at(5) + 4, pos.at(6) - pos.at(5) - 4));
    if (target == "CAD")
      exchangeRate = std::stof(resp.substr(pos.at(6) + 4, pos.at(7) - pos.at(6) - 4));
    if (target == "CNY")
      exchangeRate = std::stof(resp.substr(pos.at(7) + 4, pos.at(8) - pos.at(7) - 4));
    if (target == "AUD")
      exchangeRate = std::stof(resp.substr(pos.at(8) + 4, 4));
  }
  if(source == "CNY") {
    if (target == "EUR")
      exchangeRate = std::stof(resp.substr(60, pos.at(5) - 61));
    if (target == "GBP")
      exchangeRate = std::stof(resp.substr(pos.at(5) + 4, pos.at(6) - pos.at(5) - 4));
    if (target == "CAD")
      exchangeRate = std::stof(resp.substr(pos.at(6) + 4, pos.at(7) - pos.at(6) - 4));
    if (target == "USD")
      exchangeRate = std::stof(resp.substr(pos.at(7) + 4, pos.at(8) - pos.at(7) - 4));
    if (target == "AUD")
      exchangeRate = std::stof(resp.substr(pos.at(8) + 4, 4));
  }
  if(source == "AUD") {
    if (target == "EUR")
      exchangeRate = std::stof(resp.substr(60, pos.at(5) - 61));
    if (target == "GBP")
      exchangeRate = std::stof(resp.substr(pos.at(5) + 4, pos.at(6) - pos.at(5) - 4));
    if (target == "CAD")
      exchangeRate = std::stof(resp.substr(pos.at(6) + 4, pos.at(7) - pos.at(6) - 4));
    if (target == "USD")
      exchangeRate = std::stof(resp.substr(pos.at(7) + 4, pos.at(8) - pos.at(7) - 4));
    if (target == "CNY")
      exchangeRate = std::stof(resp.substr(pos.at(8) + 4, 4));
  }

  return exchangeRate;
}

// The Function to calculate the amount of the currency
float currency_translation(float source_amount, float exchangeRate) {
  float target_amount = source_amount * exchangeRate;
  return target_amount;
}
// The function to display the translate window
void set_transform_window(string source, float source_amount) {
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
    CNY_RATE = get_accurate_exchangeRate(source, get_url_contents(get_source_url(source)), "CNY");
    GBP_RATE = get_accurate_exchangeRate(source, get_url_contents(get_source_url(source)), "GBP");
    EUR_RATE = get_accurate_exchangeRate(source, get_url_contents(get_source_url(source)), "EUR");
    AUD_RATE = get_accurate_exchangeRate(source, get_url_contents(get_source_url(source)), "AUD");
    CAD_RATE = get_accurate_exchangeRate(source, get_url_contents(get_source_url(source)), "CAD");
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

  } else if(source == "CNY") {
    CNY = source_amount;
    CNY_RATE = 1;
    USD_RATE = get_accurate_exchangeRate(source, get_url_contents(get_source_url(source)), "USD");
    GBP_RATE = get_accurate_exchangeRate(source, get_url_contents(get_source_url(source)), "GBP");
    EUR_RATE = get_accurate_exchangeRate(source, get_url_contents(get_source_url(source)), "EUR");
    AUD_RATE = get_accurate_exchangeRate(source, get_url_contents(get_source_url(source)), "AUD");
    CAD_RATE = get_accurate_exchangeRate(source, get_url_contents(get_source_url(source)), "CAD");
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

  } else if(source == "GBP") {
    GBP = source_amount;
    GBP_RATE = 1;
    CNY_RATE = get_accurate_exchangeRate(source, get_url_contents(get_source_url(source)), "CNY");
    USD_RATE = get_accurate_exchangeRate(source, get_url_contents(get_source_url(source)), "USD");
    EUR_RATE = get_accurate_exchangeRate(source, get_url_contents(get_source_url(source)), "EUR");
    AUD_RATE = get_accurate_exchangeRate(source, get_url_contents(get_source_url(source)), "AUD");
    CAD_RATE = get_accurate_exchangeRate(source, get_url_contents(get_source_url(source)), "CAD");
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
  } else if(source == "EUR") {
    EUR = source_amount;
    EUR_RATE = 1;
    CNY_RATE = get_accurate_exchangeRate(source, get_url_contents(get_source_url(source)), "CNY");
    GBP_RATE = get_accurate_exchangeRate(source, get_url_contents(get_source_url(source)), "GBP");
    USD_RATE = get_accurate_exchangeRate(source, get_url_contents(get_source_url(source)), "USD");
    AUD_RATE = get_accurate_exchangeRate(source, get_url_contents(get_source_url(source)), "AUD");
    CAD_RATE = get_accurate_exchangeRate(source, get_url_contents(get_source_url(source)), "CAD");
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
  } else if(source == "AUD") {
    AUD = source_amount;
    AUD_RATE = 1;
    CNY_RATE = get_accurate_exchangeRate(source, get_url_contents(get_source_url(source)), "CNY");
    GBP_RATE = get_accurate_exchangeRate(source, get_url_contents(get_source_url(source)), "GBP");
    EUR_RATE = get_accurate_exchangeRate(source, get_url_contents(get_source_url(source)), "EUR");
    USD_RATE = get_accurate_exchangeRate(source, get_url_contents(get_source_url(source)), "USD");
    CAD_RATE = get_accurate_exchangeRate(source, get_url_contents(get_source_url(source)), "CAD");
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
  } else if(source == "CAD") {
    CAD = source_amount;
    CAD_RATE = 1;
    CNY_RATE = get_accurate_exchangeRate(source, get_url_contents(get_source_url(source)), "CNY");
    GBP_RATE = get_accurate_exchangeRate(source, get_url_contents(get_source_url(source)), "GBP");
    EUR_RATE = get_accurate_exchangeRate(source, get_url_contents(get_source_url(source)), "EUR");
    AUD_RATE = get_accurate_exchangeRate(source, get_url_contents(get_source_url(source)), "AUD");
    USD_RATE = get_accurate_exchangeRate(source, get_url_contents(get_source_url(source)), "USD");
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
  usaf.scale(sf::Vector2f(0.1155f, 0.115f));
  usaf.setPosition(1, 19);
  sf::Sprite chinaf;
  chinaf.setTexture(chinaflag);
  chinaf.scale(sf::Vector2f(0.072f, 0.072f));
  chinaf.setPosition(0.5, 69);
  sf::Sprite ukf;
  ukf.setTexture(ukflag);
  ukf.scale(sf::Vector2f(0.0355f, 0.05f));
  ukf.setPosition(0.5, 119);
  sf::Sprite eurf;
  eurf.setTexture(eurflag);
  eurf.scale(sf::Vector2f(0.045f, 0.045f));
  eurf.setPosition(0.5, 169);
  sf::Sprite ausf;
  ausf.setTexture(ausflag);
  ausf.scale(sf::Vector2f(0.06f, 0.075f));
  ausf.setPosition(0.5, 219);
  sf::Sprite caf;
  caf.setTexture(caflag);
  caf.scale(sf::Vector2f(0.093f, 0.085f));
  caf.setPosition(0.5, 269);

  while (window.isOpen()) {
    sf::Event event;
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed)
        window.close();
    }

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

//The function to display the tally book window
void set_tallybook_window(string target) {
  vector<string> words;
  string m;
  while(cin >> m) {
    words.push_back(m);
  }
  //currency
  string currency;
  currency = target;

  int currency_number = 1;

  //make all Numbers
  string n1 = "No.1";
  string n2 = "No.2";
  string n3 = "No.3";
  string n4 = "No.4";
  string n5 = "No.5";
  string n6 = "No.6";
  string n7 = "No.7";
  string n8 = "No.8";
  string n9 = "No.9";
  string n10 = "No.10";

  //make all amounts
  vector<string> amount;
  for (int i = 0; i < words.size(); i += 2)
    amount.push_back(words.at(i));
  amount.resize(10);
  for (int j = 0; j < amount.size(); j++)
    if(amount.at(j) == "")
      amount.at(j) = "0";
  string amount1 = amount.at(0);
  string amount2 = amount.at(1);
  string amount3 = amount.at(2);
  string amount4 = amount.at(3);
  string amount5 = amount.at(4);
  string amount6 = amount.at(5);
  string amount7 = amount.at(6);
  string amount8 = amount.at(7);
  string amount9 = amount.at(8);
  string amount10 = amount.at(9);

  //make all currencies
  vector<string> CUR;
  for (int i = 1; i < words.size(); i += 2)
    CUR.push_back(words.at(i));
  CUR.resize(10);
  for (int j = 0; j < CUR.size(); j++)
    if(CUR.at(j) == "")
      CUR.at(j) = currency;
  string currency1 = CUR.at(0);
  string currency2 = CUR.at(1);
  string currency3 = CUR.at(2);
  string currency4 = CUR.at(3);
  string currency5 = CUR.at(4);
  string currency6 = CUR.at(5);
  string currency7 = CUR.at(6);
  string currency8 = CUR.at(7);
  string currency9 = CUR.at(8);
  string currency10 = CUR.at(9);

  // window
  sf::RenderWindow window(sf::VideoMode(450, 520), "Bean Counter");

  // background
  sf::RectangleShape background(sf::Vector2f(450, 520));
  background.setFillColor(sf::Color::White);

  // text font
  sf::Font font;
  font.loadFromFile("/usr/share/fonts/truetype/ubuntu/Ubuntu-BI.ttf");

  // lines
  sf::RectangleShape l1(sf::Vector2f(450, 2));
  sf::RectangleShape l2(sf::Vector2f(450, 2));
  sf::RectangleShape l3(sf::Vector2f(450, 2));
  sf::RectangleShape l4(sf::Vector2f(450, 2));
  sf::RectangleShape l5(sf::Vector2f(450, 2));
  sf::RectangleShape l6(sf::Vector2f(450, 2));
  sf::RectangleShape l7(sf::Vector2f(450, 2));
  sf::RectangleShape l8(sf::Vector2f(450, 2));
  sf::RectangleShape l9(sf::Vector2f(450, 2));
  sf::RectangleShape l11(sf::Vector2f(450, 2));
  sf::RectangleShape l12(sf::Vector2f(450, 2));
  sf::RectangleShape l13(sf::Vector2f(450, 2));
  sf::RectangleShape l10(sf::Vector2f(2, 500));
  sf::RectangleShape l14(sf::Vector2f(2, 500));
  l1.setFillColor(sf::Color::Black);
  l2.setFillColor(sf::Color::Black);
  l3.setFillColor(sf::Color::Black);
  l4.setFillColor(sf::Color::Black);
  l5.setFillColor(sf::Color::Black);
  l6.setFillColor(sf::Color::Black);
  l7.setFillColor(sf::Color::Black);
  l8.setFillColor(sf::Color::Black);
  l9.setFillColor(sf::Color::Black);
  l11.setFillColor(sf::Color::Black);
  l12.setFillColor(sf::Color::Black);
  l13.setFillColor(sf::Color::Black);
  l10.setFillColor(sf::Color::Black);
  l14.setFillColor(sf::Color::Black);
  l1.setPosition(0, 40);
  l2.setPosition(0, 80);
  l3.setPosition(0, 120);
  l4.setPosition(0, 160);
  l5.setPosition(0, 200);
  l6.setPosition(0, 240);
  l7.setPosition(0, 280);
  l8.setPosition(0, 320);
  l9.setPosition(0, 360);
  l11.setPosition(0, 400);
  l12.setPosition(0, 440);
  l13.setPosition(0, 480);
  l10.setPosition(149, 40);
  l14.setPosition(299, 40);

  // Fixed texts
  sf::Text nums;
  sf::Text Amount;
  sf::Text Total;
  sf::Text Currency;
  sf::Text Now_currency;
  nums.setFont(font);
  Amount.setFont(font);
  Total.setFont(font);
  Currency.setFont(font);
  Now_currency.setFont(font);
  nums.setString("Time");
  Amount.setString("Amounts");
  Total.setString("Total");
  Currency.setString("The Currency you are using is");
  Now_currency.setString("Currency");
  nums.setCharacterSize(25);
  Amount.setCharacterSize(25);
  Total.setCharacterSize(25);
  Currency.setCharacterSize(25);
  Now_currency.setCharacterSize(25);
  nums.setPosition(35, 45);
  Amount.setPosition(165, 45);
  Total.setPosition(33, 485);
  Currency.setPosition(0, 5);
  Now_currency.setPosition(315, 45);
  nums.setFillColor(sf::Color::Black);
  Amount.setFillColor(sf::Color::Black);
  Total.setFillColor(sf::Color::Black);
  Currency.setFillColor(sf::Color::Black);
  Now_currency.setFillColor(sf::Color::Black);

  //disp currency
  sf::Text currency_disp;
  currency_disp.setFont(font);
  currency_disp.setString(currency);
  currency_disp.setCharacterSize(25);
  currency_disp.setPosition(390, 5);
  currency_disp.setFillColor(sf::Color::Black);
  sf::Text Total_currency;
  Total_currency.setFont(font);
  Total_currency.setString(currency);
  Total_currency.setCharacterSize(25);
  Total_currency.setPosition(360, 485);
  Total_currency.setFillColor(sf::Color::Black);

  //Amounts
  sf::Text Amount1;
  sf::Text Amount2;
  sf::Text Amount3;
  sf::Text Amount4;
  sf::Text Amount5;
  sf::Text Amount6;
  sf::Text Amount7;
  sf::Text Amount8;
  sf::Text Amount9;
  sf::Text Amount10;
  Amount1.setFont(font);
  Amount2.setFont(font);
  Amount3.setFont(font);
  Amount4.setFont(font);
  Amount5.setFont(font);
  Amount6.setFont(font);
  Amount7.setFont(font);
  Amount8.setFont(font);
  Amount9.setFont(font);
  Amount10.setFont(font);
  Amount1.setString(amount1);
  Amount2.setString(amount2);
  Amount3.setString(amount3);
  Amount4.setString(amount4);
  Amount5.setString(amount5);
  Amount6.setString(amount6);
  Amount7.setString(amount7);
  Amount8.setString(amount8);
  Amount9.setString(amount9);
  Amount10.setString(amount10);
  Amount1.setCharacterSize(25);
  Amount2.setCharacterSize(25);
  Amount3.setCharacterSize(25);
  Amount4.setCharacterSize(25);
  Amount5.setCharacterSize(25);
  Amount6.setCharacterSize(25);
  Amount7.setCharacterSize(25);
  Amount8.setCharacterSize(25);
  Amount9.setCharacterSize(25);
  Amount10.setCharacterSize(25);
  Amount1.setPosition(150, 85);
  Amount2.setPosition(150, 125);
  Amount3.setPosition(150, 165);
  Amount4.setPosition(150, 205);
  Amount5.setPosition(150, 245);
  Amount6.setPosition(150, 285);
  Amount7.setPosition(150, 325);
  Amount8.setPosition(150, 365);
  Amount9.setPosition(150, 405);
  Amount10.setPosition(150, 445);
  Amount1.setFillColor(sf::Color::Black);
  Amount2.setFillColor(sf::Color::Black);
  Amount3.setFillColor(sf::Color::Black);
  Amount4.setFillColor(sf::Color::Black);
  Amount5.setFillColor(sf::Color::Black);
  Amount6.setFillColor(sf::Color::Black);
  Amount7.setFillColor(sf::Color::Black);
  Amount8.setFillColor(sf::Color::Black);
  Amount9.setFillColor(sf::Color::Black);
  Amount10.setFillColor(sf::Color::Black);

  // numbers
  sf::Text Nums1;
  sf::Text Nums2;
  sf::Text Nums3;
  sf::Text Nums4;
  sf::Text Nums5;
  sf::Text Nums6;
  sf::Text Nums7;
  sf::Text Nums8;
  sf::Text Nums9;
  sf::Text Nums10;
  Nums1.setFont(font);
  Nums2.setFont(font);
  Nums3.setFont(font);
  Nums4.setFont(font);
  Nums5.setFont(font);
  Nums6.setFont(font);
  Nums7.setFont(font);
  Nums8.setFont(font);
  Nums9.setFont(font);
  Nums10.setFont(font);
  Nums1.setString(n1);
  Nums2.setString(n2);
  Nums3.setString(n3);
  Nums4.setString(n4);
  Nums5.setString(n5);
  Nums6.setString(n6);
  Nums7.setString(n7);
  Nums8.setString(n8);
  Nums9.setString(n9);
  Nums10.setString(n10);
  Nums1.setCharacterSize(25);
  Nums2.setCharacterSize(25);
  Nums3.setCharacterSize(25);
  Nums4.setCharacterSize(25);
  Nums5.setCharacterSize(25);
  Nums6.setCharacterSize(25);
  Nums7.setCharacterSize(25);
  Nums8.setCharacterSize(25);
  Nums9.setCharacterSize(25);
  Nums10.setCharacterSize(25);
  Nums1.setPosition(0, 85);
  Nums2.setPosition(0, 125);
  Nums3.setPosition(0, 165);
  Nums4.setPosition(0, 205);
  Nums5.setPosition(0, 245);
  Nums6.setPosition(0, 285);
  Nums7.setPosition(0, 325);
  Nums8.setPosition(0, 365);
  Nums9.setPosition(0, 405);
  Nums10.setPosition(0, 445);
  Nums1.setFillColor(sf::Color::Black);
  Nums2.setFillColor(sf::Color::Black);
  Nums3.setFillColor(sf::Color::Black);
  Nums4.setFillColor(sf::Color::Black);
  Nums5.setFillColor(sf::Color::Black);
  Nums6.setFillColor(sf::Color::Black);
  Nums7.setFillColor(sf::Color::Black);
  Nums8.setFillColor(sf::Color::Black);
  Nums9.setFillColor(sf::Color::Black);
  Nums10.setFillColor(sf::Color::Black);

  //currencies
  sf::Text Currency1;
  sf::Text Currency2;
  sf::Text Currency3;
  sf::Text Currency4;
  sf::Text Currency5;
  sf::Text Currency6;
  sf::Text Currency7;
  sf::Text Currency8;
  sf::Text Currency9;
  sf::Text Currency10;
  Currency1.setFont(font);
  Currency2.setFont(font);
  Currency3.setFont(font);
  Currency4.setFont(font);
  Currency5.setFont(font);
  Currency6.setFont(font);
  Currency7.setFont(font);
  Currency8.setFont(font);
  Currency9.setFont(font);
  Currency10.setFont(font);
  Currency1.setString(currency1);
  Currency2.setString(currency2);
  Currency3.setString(currency3);
  Currency4.setString(currency4);
  Currency5.setString(currency5);
  Currency6.setString(currency6);
  Currency7.setString(currency7);
  Currency8.setString(currency8);
  Currency9.setString(currency9);
  Currency10.setString(currency10);
  Currency1.setCharacterSize(25);
  Currency2.setCharacterSize(25);
  Currency3.setCharacterSize(25);
  Currency4.setCharacterSize(25);
  Currency5.setCharacterSize(25);
  Currency6.setCharacterSize(25);
  Currency7.setCharacterSize(25);
  Currency8.setCharacterSize(25);
  Currency9.setCharacterSize(25);
  Currency10.setCharacterSize(25);
  Currency1.setPosition(360, 85);
  Currency2.setPosition(360, 125);
  Currency3.setPosition(360, 165);
  Currency4.setPosition(360, 205);
  Currency5.setPosition(360, 245);
  Currency6.setPosition(360, 285);
  Currency7.setPosition(360, 325);
  Currency8.setPosition(360, 365);
  Currency9.setPosition(360, 405);
  Currency10.setPosition(360, 445);
  Currency1.setFillColor(sf::Color::Black);
  Currency2.setFillColor(sf::Color::Black);
  Currency3.setFillColor(sf::Color::Black);
  Currency4.setFillColor(sf::Color::Black);
  Currency5.setFillColor(sf::Color::Black);
  Currency6.setFillColor(sf::Color::Black);
  Currency7.setFillColor(sf::Color::Black);
  Currency8.setFillColor(sf::Color::Black);
  Currency9.setFillColor(sf::Color::Black);
  Currency10.setFillColor(sf::Color::Black);

  //total amount
  float total_amount;
  string total_amount_disp;

  float amount1_target = currency_translation(stof(amount1), get_accurate_exchangeRate(currency1, get_url_contents(get_source_url(currency1)), currency));
  float amount2_target = currency_translation(stof(amount2), get_accurate_exchangeRate(currency2, get_url_contents(get_source_url(currency2)), currency));
  float amount3_target = currency_translation(stof(amount3), get_accurate_exchangeRate(currency3, get_url_contents(get_source_url(currency3)), currency));
  float amount4_target = currency_translation(stof(amount4), get_accurate_exchangeRate(currency4, get_url_contents(get_source_url(currency4)), currency));
  float amount5_target = currency_translation(stof(amount5), get_accurate_exchangeRate(currency5, get_url_contents(get_source_url(currency5)), currency));
  float amount6_target = currency_translation(stof(amount6), get_accurate_exchangeRate(currency6, get_url_contents(get_source_url(currency6)), currency));
  float amount7_target = currency_translation(stof(amount7), get_accurate_exchangeRate(currency7, get_url_contents(get_source_url(currency7)), currency));
  float amount8_target = currency_translation(stof(amount8), get_accurate_exchangeRate(currency8, get_url_contents(get_source_url(currency8)), currency));
  float amount9_target = currency_translation(stof(amount9), get_accurate_exchangeRate(currency9, get_url_contents(get_source_url(currency9)), currency));
  float amount10_target = currency_translation(stof(amount10), get_accurate_exchangeRate(currency10, get_url_contents(get_source_url(currency10)), currency));

  total_amount = amount1_target + amount2_target + amount3_target + amount4_target + amount5_target + amount6_target + amount7_target + amount8_target + amount9_target + amount10_target;
  total_amount_disp = to_string(total_amount).substr(0, 6);
  sf::Text Total_amount_disp;
  Total_amount_disp.setFont(font);
  Total_amount_disp.setString(total_amount_disp);
  Total_amount_disp.setCharacterSize(25);
  Total_amount_disp.setPosition(150, 485);
  Total_amount_disp.setFillColor(sf::Color::Black);

  while (window.isOpen()) {
    sf::Event event;
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed)
        window.close();
    }

    window.draw(background);
    window.draw(l1);
    window.draw(l2);
    window.draw(l3);
    window.draw(l4);
    window.draw(l5);
    window.draw(l6);
    window.draw(l7);
    window.draw(l8);
    window.draw(l9);
    window.draw(l10);
    window.draw(l11);
    window.draw(l12);
    window.draw(l13);
    window.draw(l14);
    window.draw(nums);
    window.draw(Amount);
    window.draw(Total);
    window.draw(Currency);
    window.draw(currency_disp);
    window.draw(Total_amount_disp);
    window.draw(Now_currency);
    window.draw(Nums1);
    window.draw(Nums2);
    window.draw(Nums3);
    window.draw(Nums4);
    window.draw(Nums5);
    window.draw(Nums6);
    window.draw(Nums7);
    window.draw(Nums8);
    window.draw(Nums9);
    window.draw(Nums10);
    window.draw(Amount1);
    window.draw(Amount2);
    window.draw(Amount3);
    window.draw(Amount4);
    window.draw(Amount5);
    window.draw(Amount6);
    window.draw(Amount7);
    window.draw(Amount8);
    window.draw(Amount9);
    window.draw(Amount10);
    window.draw(Currency1);
    window.draw(Currency2);
    window.draw(Currency3);
    window.draw(Currency4);
    window.draw(Currency5);
    window.draw(Currency6);
    window.draw(Currency7);
    window.draw(Currency8);
    window.draw(Currency9);
    window.draw(Currency10);
    window.draw(Total_currency);

    window.display();
  }
}

int main() {
  string source, target;
  float source_amount;
  int choice;
  cout << "Choose a mode: 1.Currency Convertor, 2.Tally book" << "\n";
  cin >> choice;

  while (choice != 1 && choice != 2) {
    cout << "Wrong Command, type 1 or 2 to enter the right mode!" << "\n";
    cin >> choice;
  }

  if(choice == 1) {
    cout << "Choose a source currency. Commands: " << "\n";
    cout << "CNY,USD,GBP,EUR,AUD,CAD" << "\n";
    cin >> source;
    while(source != "CNY" && source != "USD" && source != "GBP" && source != "EUR" && source != "AUD" && source != "CAD") {
      cout << "Wrong Command, try again!" << "\n";
      cin >> source;
    }
    cout << "How much source currency do you have: " << "\n";
    cin >> source_amount;
    set_transform_window(source, source_amount);
  } else if(choice == 2) {
    cout << "Choose a target currency. Commands: " << "\n";
    cout << "CNY,USD,GBP,EUR,AUD,CAD" << "\n";
    cin >> target;
    cout << "Type money with currency unit(format: xxxx currency): " << "\n";
    set_tallybook_window(target);
  }


  return 0;
}