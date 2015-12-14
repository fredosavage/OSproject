#include "motor_movement.h"
#include "sensor_readout.h"
#include <mqueue.h>

#define MQ_NAME "/instructions" 
#define MAX_MSG 5

#define MQ_SIZE 5
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
    init_queue(&mqWriter, O_CREAT | O_WRONLY);
    pthread_t = controlThread;
    pthread_create(&controlThread, NULL, control, mqWriter);

    init_queue(&mqReader, O_RDONLY);
    while(1){
        instruction = get_integer_from_mq(mqReader);
        switch(instruction){
            case MSG_KEEP_SEARCHING:
                //turn and search
                break;
            case MSG_BALL_IN_RANGE:
                // grab the ball
                break;
            case MSG_BUTTON_PUSHED:
                // handle push
                break;
            default:
                break;
        } 


                    

    }        
    mq_unlink(MQ_NAME);
    return;
}
