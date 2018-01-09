#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/System.hpp>
#include <list>

// Defines
#define str(x) dynamic_cast<std::ostringstream&>((std::ostringstream()<<std::dec<<x)).str()

// Namespaces
using namespace std;
using namespace sf;

// Includes
#include "console.h"
#include "settings.h"
#include "classes.h"

// Global Variables
list <Object*> entityList;

int main()
{
    Console console;

    // Initialize the window
    RenderWindow window(VideoMode(gameWidth, gameHeight), "Copter Game");
    window.setVerticalSyncEnabled(true);
    window.setMouseCursorVisible(false);

    // Loop through every Texture, load it and add it too the textureList map.
    string textureNames[] = {"player", "cursor"};
    map <string, Texture> textureList;
    for(string name : textureNames) {
        if (!textureList[name].loadFromFile(resourceFolder+"/"+textureFolder+"/"+name+".png")) {
            textureList[name].create(2, 2);
            console.log(2, "Could not load texture: "+resourceFolder+"/"+textureFolder+"/"+name+".png");
        }
    }

    string backgroundNames[] = {"menu"};
    map <string, Texture> backgroundList;
    for(string name : backgroundNames)
        if (!backgroundList[name].loadFromFile(resourceFolder+"/"+backgroundFolder+"/"+name+".png")) return EXIT_FAILURE;

    string fontNames[] = {"moonhouse"};
    map <string, Font> fontList;
    for(string name : fontNames)
        if (!fontList[name].loadFromFile(resourceFolder+"/"+fontFolder+"/"+name+".ttf")) return EXIT_FAILURE;

    string musicNames[] = {"Year"};
    map <string, Music> musicList;
    //for(string name : musicNames) {
     //   if (!musicList[name].openFromFile(resourceFolder+"/"+musicFolder+"/"+name+".ogg")) return EXIT_FAILURE;

//if (!music.openFromFile(resourceFolder+"/"+musicFolder+"/"+name+".ogg"))
 //   return -1; // error
//music.play();
////    sf::Music music;
//if (!music.openFromFile("resources/music/Year.ogg"))
//    return -1; // error
//music.play();

    // Setup assorted things
    map <string, Clock> clockList;
    Sprite      globalSprite;
    Sprite      cursorSprite;
    Sprite      backgroundSprite;
    Vector2f    mouse;
    Text        globalText;
    TextHandler t(Color(255, 255, 255), fontList["moonhouse"], 60);

    cursorSprite.setTexture(textureList["cursor"]);
    backgroundSprite.setPosition(Vector2f(gameWidth/2, gameHeight/2));
    backgroundSprite.setScale(2.0/3.0, 2.0/3.0);
    backgroundSprite.setOrigin(backgroundList["menu"].getSize().x/2, backgroundList["menu"].getSize().y/2);

    // Create a player
    auto player = new Copter();
    player -> texture = "player";
    entityList.push_back(player);

    //musicList["A Year"].play();

    while (window.isOpen())
    {
        // Restarts the frame timer
        clockList["gameClock"].restart();

        // Allows the window to be closed
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();
        }

        // Get the mouse position
        mouse.x = Mouse::getPosition(window).x;
        mouse.y = Mouse::getPosition(window).y;

        // Check it is within bounds
        mouse.x = (mouse.x < 0 ? 0 : (mouse.x > gameWidth ? gameWidth : mouse.x));
        mouse.y = (mouse.y < 0 ? 0 : (mouse.y > gameHeight ? gameHeight : mouse.y));

        // Get ready to draw
        window.clear();

        backgroundSprite.setTexture(backgroundList["menu"]);
        window.draw(backgroundSprite);

        float fade = 128*(1+cos(2*clockList["fadeClock"].getElapsedTime().asSeconds()));
        t.color = Color(200, 200, 255);
        t.size  = 61;
        t.Write(window, "Side Scrolling Game", Vector2f(gameWidth/2, 40));
        t.Write(window, "Click to start", Vector2f(gameWidth/2,gameHeight-40));
        t.color = Color(fade, fade, 255);
        t.size  = 60;
        t.Write(window, "Side Scrolling Game", Vector2f(gameWidth/2, 40));
        t.Write(window, "Click to start", Vector2f(gameWidth/2,gameHeight-40));

        for(auto entity : entityList) {
            entity -> Update();
            entity -> Draw(window, globalSprite, textureList);
        }

        // Lastly draw the cursor
        cursorSprite.setPosition(Vector2f(Mouse::getPosition(window).x, Mouse::getPosition(window).y));
        window.draw(cursorSprite);

        window.display();

        float frameTime = clockList["gameClock"].getElapsedTime().asSeconds();
        if (frameTime < frameLength) sleep(seconds(frameLength - frameTime));
    }

    return 0;
}
