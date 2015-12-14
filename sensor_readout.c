#include "ev3c.h"

#include <stdio.h>
#include <mqueue.h>

#include "bumblebeeTypes.h"

int push(ev3_sensor_ptr pushS){
		ev3_update_sensor_val(pushS);
		return pushS->val_data[0].s32;
}

int color(ev3_sensor_ptr colorS){
	    ev3_update_sensor_val(colorS);
	    return colorS->val_data[0].s32;
}	

int compass(ev3_sensor_ptr compassS){
		ev3_update_sensor_val(compassS);
		return compassS->val_data[0].s32;
}

int distance(ev3_sensor_ptr distanceS){
		ev3_update_sensor_val(distanceS);
		return distanceS->val_data[0].s32;
}


void *control(void *vargp){
    int distanceRO, colorRO, pushRO, compassRO, msg;    

	ev3_sensor_ptr sensors  = ev3_load_sensors();
	ev3_sensor_ptr pushS     = ev3_search_sensor_by_port(sensors,1);
	ev3_sensor_ptr colorS    = ev3_search_sensor_by_port(sensors,2);
	ev3_sensor_ptr compassS  = ev3_search_sensor_by_port(sensors,3);
	ev3_sensor_ptr distanceS = ev3_search_sensor_by_port(sensors,4);
	// 3 compass / 1 push / 2 color / 4 distance
	ev3_open_sensor(pushS);
	ev3_open_sensor(colorS);
	ev3_open_sensor(compassS); 
	ev3_open_sensor(distanceS);
    
    struct threadParams params = (struct threadParams)vargp;
    mqWriter = params.mq;
    instructionLock = params.mutex;

    while(1){	            
        distanceRO = distance(distanceS);
        colorRO = color(colorS);
        pushRO = push(pushS);
        //compassRO = compass(compassS);
    
        msg = MSG_KEEP_SEARCHING;
    
        if(disanceRO > BALL_IN_RANGE_DISTANCE || colorRO > BALL_IN_RANGE_COLOR){
            msg = MSG_BALL_IN_RANGE;
        }else if(pushRO == 1){
            msg = MSG_BUTTON_PUSHED;
        }

        status = mq_send(mqWriter, (char*)&msg, sizeof(int), 1);
        if (status == -1)
            perror("mq_send failure"); 
        
    }
    ev3_delete_sensors(sensors);
}


