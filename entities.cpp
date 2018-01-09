class BaseEntity {
    public:
        Vector2f location;
        float    angle;
        float    velocity;
        float    topspeed;
        int      health;
        int      sheilds;
        std::string texture;

    void Draw(sf::RenderWindow, sf::Sprite, map);
    void Accelerate(float);
    void Update();
    void Orient(float);
    void Injure(int);
};

class Player : public BaseEntity {
    public:
};

class
