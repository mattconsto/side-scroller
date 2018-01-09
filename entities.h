
class Object {
    public:
        Vector2f location = Vector2f(gameWidth/2, gameHeight/2);
        float    angle    = 0.0;
        float    velocity = 0.0;
        float    topspeed = 0.0;
        int      health   = 1;
        int      sheilds  = 0;
        string   texture  = "";

    void Draw(RenderWindow & targetWindow, Sprite & targetSprite, map <string, Texture> & targetList) {
        targetSprite.setPosition(location.x, location.y);
        targetSprite.setRotation(angle);
        targetSprite.setTexture(targetList[texture]);
        targetSprite.setOrigin(targetList[texture].getSize().x/2, targetList[texture].getSize().y/2);
        targetWindow.draw(targetSprite);
    }
    void Accelerate(float amount) {
        if(velocity + amount >= topspeed)
            velocity += amount;
    }
    void Update() {
        location.x += velocity * cos(angle) * frameLength;
        location.y += velocity * sin(angle) * frameLength;

        if(velocity > 0) {
            velocity -= gravity * frameLength;
        }
    }
    void Orient(float degrees) {
        angle += degrees;
        while(angle >= 360)
            angle -= 360;
        while(angle <= 0)
            angle += 360;
    }
    void Injure(int damage) {
        if(health - damage <= 0) {
            health = 0;
        } else {
            health -= damage;
        }
    }
};

class Copter : public Object {
    public:

    Copter() {

    }
};
