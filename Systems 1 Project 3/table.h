/*Jake Kennedy Lab 3 Table Header File*/
int offTable(void *data);

double frictionPercent(struct BallData *ball);

void reflectLeft(struct BallData *ball);

void reflectRight(struct BallData *ball);

void reflectTop(struct BallData *ball);

void reflectBottom(struct BallData *ball);

int inLeftRail(struct BallData *ball);

int inRightRail(struct BallData *ball);

int inTopRail(struct BallData *ball);

int inBottomRail(struct BallData *ball);

double frameTimeX(struct BallData *ball);

double frameTimeY(struct BallData *ball);
