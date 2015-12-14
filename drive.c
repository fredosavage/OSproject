#include "motor_movement.h"
#include "sensor_readout.h"
#include "bumblebeeTypes.h"
#include <mqueue.h>

#define MQ_NAME "/instructions" 

#define MQ_SIZE 1
#define PMODE 0666 

void init_queue (mqd_t *mq_desc, int open_flags) {
  struct mq_attr attr;
  
  // fill attributes of the mq
  attr.mq_maxmsg = MQ_SIZE;
  attr.mq_msgsize = sizeof (int);
  attr.mq_flags = 0;

  // open the mq
  //*mq_desc = mq_open (MQ_NAME, open_flags);
  *mq_desc = mq_open (MQ_NAME, open_flags, PMODE, &attr);
  if (*mq_desc == (mqd_t)-1) {
    perror("Mq opening failed");
    exit(-1);
  }
}

/* to get an integer from message queue */
int get_integer_from_mq (mqd_t mq_desc) {
  ssize_t num_bytes_received = 0;
  int data=0;

  //receive an int from mq
  num_bytes_received = mq_receive (mq_desc, (char *) &data, sizeof (int), NULL);
  if (num_bytes_received == -1)
    perror ("mq_receive failure");
  return (data);
}


void main(void){
    int instruction;
    mqd_t mqWriter, mqReader;
    pthread_mutex_t = instructionLock;
    init_queue(&mqWriter, O_CREAT | O_WRONLY);
    // CHECK THIS LINE
    struct threadParams controlParams = {mqWriter, instructionLock}; 
    pthread_t = controlThread;
    pthread_create(&controlThread, NULL, control, controlParams);

    init_queue(&mqReader, O_RDONLY);

	//Loading all motors
	ev3_motor_ptr motors = ev3_load_motors();
	ev3_motor_ptr motor = motors;
	ev3_motor_ptr leftM   = ev3_search_motor_by_port(motors, 'B');
	ev3_motor_ptr rightM  = ev3_search_motor_by_port(motors, 'C');
	ev3_motor_ptr middleM = ev3_search_motor_by_port(motors, 'D');
	while (motor)
	{
		ev3_reset_motor(motor);
		ev3_open_motor(motor);
		motor = motor->next;
	}
	 

    while(1){
        instruction = get_integer_from_mq(mqReader);
        switch(instruction){
            case MSG_KEEP_SEARCHING:
                //turn and search
                printf("searching");
                break;
            case MSG_BALL_IN_RANGE:
                // grab the ball
                printf("searching");
                break;
            case MSG_BUTTON_PUSHED:
                // handle push
                printf("button pushed");
                break;
            default:
                break;
        } 


                    

    }        
    mq_unlink(MQ_NAME);
    return;
}
