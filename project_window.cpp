#include <iostream>
#include <string>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

using std::to_string;
using std::string;
using std::cout;

int main() {
  double USD, CNY, GBP, EUR, AUD, CAD;
  USD = 10000;
// Insert function
  sf::RenderWindow window(sf::VideoMode(200, 300), "Currency Convertor");
  // set background
  sf::RectangleShape background(sf::Vector2f(200.f, 300.f));
  background.setFillColor(sf::Color::White);
  //set font
  sf::Font font;
  font.loadFromFile("/usr/share/fonts/truetype/ubuntu/Ubuntu-BI.ttf");
  //set texture
  sf::Texture usaflag;
  usaflag.loadFromFile("/home/ece-student/project/usa.jpeg");
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
  usd.setFont(font);
  usd.setString(to_string(USD));
  usd.setCharacterSize(20);
  usd.setPosition(70, 15);
  usd.setFillColor(sf::Color::Black);

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
  sf::Sprite usaf;
  usaf.setPosition(0,20);




  


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
    window.draw(cur_2);
    window.draw(cur_3);
    window.draw(cur_4);
    window.draw(cur_5);
    window.draw(cur_6);
    window.draw(usaf);
    window.display();

  }

  return 0;
}
