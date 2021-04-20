#include <iostream>
#include <string>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

using std::to_string;
using std::string;
using std::cout;
using std::endl;

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
  //set texture (make sure the pictures are in the same directory as this file!)
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
  l1.setPosition(0, 45);
  l2.setPosition(0, 95);
  l3.setPosition(0, 145);
  l4.setPosition(0, 195);
  l5.setPosition(0, 245);

  //set flag pics
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
    window.draw(chinaf);
    window.draw(ukf);
    window.draw(eurf);
    window.draw(ausf);
    window.draw(caf);
    window.display();

  }

  return 0;
}
