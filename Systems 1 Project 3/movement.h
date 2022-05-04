/*Jake Kennedy Lab 3 Movement Header File*/
int inMotion(void *data);

int bounce(struct BallData *ball);

int basicMove(struct BallData *ball);

void applyFriction(struct BallData *ball);

void moveBalls(void *data);
