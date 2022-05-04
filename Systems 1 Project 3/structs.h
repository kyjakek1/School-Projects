/*Jake Kennedy Structure Header File*/
struct BallData{
    int ballNum;
    double xPos,yPos,xVel,yVel;
    struct Simulation *table;
};

struct Simulation{
    double elapsedT,dt;
    void *balls;
};
