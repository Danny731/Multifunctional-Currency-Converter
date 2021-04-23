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
    
    // Ask users to choose currency;

    //currency
    string currency;
    currency = "USD";
    int currency_number = 1;
    // choose flag
    string selected_flag;
    switch(currency_number) {
      case 1 : selected_flag = "usa.jpeg";
      case 2 : selected_flag = "uk.jpeg";
      case 3 : selected_flag = "canada.jpeg";
      case 4 : selected_flag = "china.jpeg";
      case 5 : selected_flag = "aus.jpeg";
      case 6 : selected_flag = "eur.jpeg";
    }
    
    // disp flag;
    

    //make all dates
    string date1 = "4/1/2021";
    string date2 = "4/2/2021";
    string date3 = "4/3/2021";
    string date4 = "4/4/2021";
    string date5 = "4/5/2021";
    string date6 = "4/6/2021";
    string date7 = "4/7/2021";
    string date8 = "4/8/2021";
    string date9 = "4/9/2021";
    string date10 = "4/10/2021";
    
    //make all amounts
    string amount1 = "10000";
    string amount2 = "20000";
    string amount3 = "30000";
    string amount4 = "40000";
    string amount5 = "50000";
    string amount6 = "60000";
    string amount7 = "70000";
    string amount8 = "80000";
    string amount9 = "90000";
    string amount10 = "100000";

    //make all currencies
    string currency1 = "USD";
    string currency2 = "EUR";
    string currency3 = "USD";
    string currency4 = "EUR";
    string currency5 = "USD";
    string currency6 = "EUR";
    string currency7 = "USD";
    string currency8 = "EUR";
    string currency9 = "USD";
    string currency10 = "EUR";
    
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
    sf::RectangleShape l10(sf::Vector2f(2,500));
    sf::RectangleShape l14(sf::Vector2f(2,500));
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
  	l10.setPosition(149,40);
    l14.setPosition(299,40);
    
    // Fixed texts
    sf::Text Dates;
    sf::Text Amount;
    sf::Text Total;
    sf::Text Currency;
    sf::Text Now_currency;
    Dates.setFont(font);
    Amount.setFont(font);
    Total.setFont(font);
    Currency.setFont(font);
    Now_currency.setFont(font);
    Dates.setString("Dates");
    Amount.setString("Amounts");
    Total.setString("Total");
    Currency.setString("The Currency you are using is");
    Now_currency.setString("Currency");
    Dates.setCharacterSize(25);
    Amount.setCharacterSize(25);
    Total.setCharacterSize(25);
    Currency.setCharacterSize(25);
    Now_currency.setCharacterSize(25);
    Dates.setPosition(35, 45);
    Amount.setPosition(165, 45);
    Total.setPosition(33, 485);
    Currency.setPosition(0,5);
    Now_currency.setPosition(315,45);
    Dates.setFillColor(sf::Color::Black);
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

    // Dates
    sf::Text Date1;
    sf::Text Date2;
    sf::Text Date3;
    sf::Text Date4;
    sf::Text Date5;
    sf::Text Date6;
    sf::Text Date7;
    sf::Text Date8;
    sf::Text Date9;
    sf::Text Date10;
    Date1.setFont(font);
    Date2.setFont(font);
    Date3.setFont(font);
    Date4.setFont(font);
    Date5.setFont(font);
    Date6.setFont(font);
    Date7.setFont(font);
    Date8.setFont(font);
    Date9.setFont(font);
    Date10.setFont(font);
    Date1.setString(date1);
    Date2.setString(date2);
    Date3.setString(date3);
    Date4.setString(date4);
    Date5.setString(date5);
    Date6.setString(date6);
    Date7.setString(date7);
    Date8.setString(date8);
    Date9.setString(date9);
    Date10.setString(date10);
    Date1.setCharacterSize(25);
    Date2.setCharacterSize(25);
    Date3.setCharacterSize(25);
    Date4.setCharacterSize(25);
    Date5.setCharacterSize(25);
    Date6.setCharacterSize(25);
    Date7.setCharacterSize(25);
    Date8.setCharacterSize(25);
    Date9.setCharacterSize(25);
    Date10.setCharacterSize(25);
    Date1.setPosition(0, 85);
    Date2.setPosition(0, 125);
    Date3.setPosition(0, 165);
    Date4.setPosition(0, 205);
    Date5.setPosition(0, 245);
    Date6.setPosition(0, 285);
    Date7.setPosition(0, 325);
    Date8.setPosition(0, 365);
    Date9.setPosition(0, 405);
    Date10.setPosition(0, 445);
    Date1.setFillColor(sf::Color::Black);
    Date2.setFillColor(sf::Color::Black);
    Date3.setFillColor(sf::Color::Black);
    Date4.setFillColor(sf::Color::Black);
    Date5.setFillColor(sf::Color::Black);
    Date6.setFillColor(sf::Color::Black);
    Date7.setFillColor(sf::Color::Black);
    Date8.setFillColor(sf::Color::Black);
    Date9.setFillColor(sf::Color::Black);
    Date10.setFillColor(sf::Color::Black);

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
    total_amount = stof(amount1) + stof(amount2) + stof(amount3) + stof(amount4) + stof(amount5) + stof(amount6) + stof(amount7) + stof(amount8) + stof(amount9) + stof(amount10);
    total_amount_disp = to_string(total_amount);
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
    	window.draw(Dates);
    	window.draw(Amount);
    	window.draw(Total);
      window.draw(Currency);
      window.draw(currency_disp);
      window.draw(Total_amount_disp);
      window.draw(Now_currency);
      window.draw(Date1);
      window.draw(Date2);
      window.draw(Date3);
      window.draw(Date4);
      window.draw(Date5);
      window.draw(Date6);
      window.draw(Date7);
      window.draw(Date8);
      window.draw(Date9);
      window.draw(Date10);
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
