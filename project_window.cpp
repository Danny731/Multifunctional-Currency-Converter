#include <iostream>
#include <string>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

using std::to_string;
using std::string;
using std::cout;

int main()
{
// Insert function
    sf::RenderWindow window(sf::VideoMode(200, 350), "SFML works!");
    // set currency name text
    sf::Text cur_1;
    sf::Text cur_2;
    sf::Text cur_3;
    sf::Text cur_4;
    sf::Text cur_5;
    sf::Text cur_6;
    sf::Text usd;

    cur_1.setCharacterSize(20);
    cur_2.setCharacterSize(20);
    cur_3.setCharacterSize(20);
    cur_4.setCharacterSize(20);
    cur_5.setCharacterSize(20);
    cur_6.setCharacterSize(20);

    double USD, CNY, GBP, EUR, AUD, CAD;
    USD = 10000;
 

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        //  words.setString(to_string(now.tm_hour) + ":" +
                    //  to_string(now.tm_min) + ":" + to_string(now.tm_sec));

        sf::Font font;
        font.loadFromFile("/usr/share/fonts/truetype/ubuntu/Ubuntu-BI.ttf");    
        cur_1.setFont(font);
        cur_1.setString("USD");
        cur_1.setPosition(0,50);
        cur_1.setFillColor(sf::Color::White);
        usd.setFont(font);
        usd.setString(to_string(USD));
        usd.setPosition(100,50);
        usd.setFillColor(sf::Color::White);



        cur_2.setFont(font);
        cur_2.setString("CNY");
        cur_2.setPosition(0,100);
        cur_2.setFillColor(sf::Color::White);

        cur_3.setFont(font);
        cur_3.setString("GBP");
        cur_3.setPosition(0,150);
        cur_3.setFillColor(sf::Color::White);

        cur_4.setFont(font);
        cur_4.setString("EUR");
        cur_4.setPosition(0,200);
        cur_4.setFillColor(sf::Color::White);

        cur_5.setFont(font);
        cur_5.setString("AUD");
        cur_5.setPosition(0,250);
        cur_5.setFillColor(sf::Color::White);

        cur_6.setFont(font);
        cur_6.setString("CAD");
        cur_6.setPosition(0,300);
        cur_6.setFillColor(sf::Color::White);

        window.draw(cur_1);
        window.draw(usd);
        window.draw(cur_2);
        window.draw(cur_3);
        window.draw(cur_4);
        window.draw(cur_5);
        window.draw(cur_6);
        window.display();

    }

    return 0;
}
