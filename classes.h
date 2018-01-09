class TextHandler {
    private:
        Text text;
    public:
        Color    color;
        Font     font;
        int      size;

    void Write(RenderWindow & targetWindow, string message, Vector2f position) {
        text.setFont(font);
        text.setCharacterSize(size);
        text.setColor(color);
        text.setPosition(position);
        text.setString(message);
        text.setOrigin(text.getLocalBounds().width/2, 3*text.getCharacterSize()/4);
        targetWindow.draw(text);
    }

    TextHandler(Color icolor, Font ifont, int isize) {
        color = icolor; font = ifont; size = isize;
    }
};
