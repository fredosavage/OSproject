#include <mqueue.h>
#include <pthread.h>


#define BALL_IN_RANGE_DISTANCE 60
#define BALL_IN_RANGE_COLOR 5

#define MSG_KEEP_SEARCHING 0
#define MSG_BALL_IN_RANGE 1
#define MSG_BUTTON_PUSHED 2
//#define MSG_READ_COMPASS 3


struct threadParams {
    mqd_t mq;
    pthread_mutex_t* mutex;
};
