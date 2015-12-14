
#define BALL_IN_RANGE_DISTANCE 60
#define BALL_IN_RANGE_COLOR 5

#define MSG_KEEP_SEARCHING 0
#define MSG_BALL_IN_RANGE 1
#define MSG_BUTTON_PUSHED 2
//#define MSG_READ_COMPASS 3

int push(ev3_sensor_ptr pushS);
int color(ev3_sensor_ptr colorS);
int compass(ev3_sensor_ptr compassS);
int distance(ev3_sensor_ptr distanceS);
void *control(void *vargp);
