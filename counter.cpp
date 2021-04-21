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
    // window
	sf::RenderWindow window(sf::VideoMode(200, 300), "Bean Counter");

    // background
    sf::RectangleShape background(sf::Vector2f(200.f, 300.f));
    background.setFillColor(sf::Color::White);

    // text font
    sf::Font font;
    font.loadFromFile("/usr/share/fonts/truetype/ubuntu/Ubuntu-BI.ttf");
    
    // lines
	sf::RectangleShape l1(sf::Vector2f(200, 1));
  	sf::RectangleShape l2(sf::Vector2f(200, 1));
  	sf::RectangleShape l3(sf::Vector2f(200, 1));
 	sf::RectangleShape l4(sf::Vector2f(200, 1));
 	sf::RectangleShape l5(sf::Vector2f(200, 1));
	sf::RectangleShape l6(sf::Vector2f(200, 1));
  	sf::RectangleShape l7(sf::Vector2f(200, 1));
  	sf::RectangleShape l8(sf::Vector2f(200, 1));
 	sf::RectangleShape l9(sf::Vector2f(200, 1)); 
    sf::RectangleShape l10(sf::Vector2f(1,300));
  	l1.setFillColor(sf::Color::Black);
  	l2.setFillColor(sf::Color::Black);
  	l3.setFillColor(sf::Color::Black);
  	l4.setFillColor(sf::Color::Black);
  	l5.setFillColor(sf::Color::Black);
  	l6.setFillColor(sf::Color::Black);
  	l7.setFillColor(sf::Color::Black);
  	l8.setFillColor(sf::Color::Black);
  	l9.setFillColor(sf::Color::Black);
  	l10.setFillColor(sf::Color::Black);
  	l1.setPosition(0, 30);
  	l2.setPosition(0, 60);
  	l3.setPosition(0, 90);
  	l4.setPosition(0, 120);
  	l5.setPosition(0, 150);
  	l6.setPosition(0, 180);
  	l7.setPosition(0, 210);
  	l8.setPosition(0, 240);
  	l9.setPosition(0, 270);
  	l10.setPosition(99,0);

    // Fixed Texts
    sf::Text Dates;
    sf::Text Amount;
    sf::Text Total;
    Dates.setFont(font);
    Amount.setFont(font);
    Total.setFont(font);
    Dates.setString("Dates");
    Amount.setString("Amount");
    Total.setString("Total");
    Dates.setCharacterSize(15);
    Amount.setCharacterSize(15);
    Total.setCharacterSize(15);
    Dates.setPosition(25, 5);
    Amount.setPosition(119, 5);
    Total.setPosition(27, 275);
    Dates.setFillColor(sf::Color::Black);
    Amount.setFillColor(sf::Color::Black);
    Total.setFillColor(sf::Color::Black);
    
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
    	window.draw(Dates);
    	window.draw(Amount);
    	window.draw(Total);
    	window.display();

    }


}
