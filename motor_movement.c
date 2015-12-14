/*
 The contents of this file are subject to the "do whatever you like"-license.
 That means: Do, whatver you want, this file is under public domain. It is an
 example for ev3c. Copy it and learn from it for your project and release
 it under every license you want. ;-)
 For feedback and questions about my Files and Projects please mail me,
 Alexander Matthes (Ziz) , ziz_at_mailbox.org, http://github.com/theZiz
*/
#define FULLTURN_SPEED 150
#define FULLTURN_TIME 4800
#include "ev3c.h"

#include <stdio.h>


void move(ev3_motor_ptr leftM, ev3_motor_ptr rightM, int time, int speed){
	
	// set speed and time
	ev3_stop_command_motor_by_name(leftM , "coast");	
	ev3_set_speed_sp( leftM, speed);
	ev3_set_time_sp( leftM, time );
		
	ev3_stop_command_motor_by_name( rightM, "coast");
	ev3_set_speed_sp( rightM, speed);
	ev3_set_time_sp( rightM, time);
	
	//start motors
	ev3_command_motor_by_name( rightM, "run-timed");
	ev3_command_motor_by_name( leftM, "run-timed");

}


void turn(ev3_motor_ptr leftM, ev3_motor_ptr rightM, int time, int degree){
	
	int turn_time = time * degree/360;

	// set speed and time
	ev3_stop_command_motor_by_name(leftM , "coast");		
	ev3_set_speed_sp( leftM, FULLTURN_SPEED);
	ev3_set_time_sp( leftM, turn_time );
	
	ev3_stop_command_motor_by_name( rightM, "coast");
	ev3_set_speed_sp( rightM, -FULLTURN_SPEED);
	ev3_set_time_sp( rightM, turn_time);

	//start motors
	ev3_command_motor_by_name( rightM, "run-timed");
	ev3_command_motor_by_name( leftM, "run-timed");

}

void grab(ev3_motor_ptr middleM){
	ev3_stop_command_motor_by_name(middleM , "coast");		
	ev3_set_speed_sp( middleM, -70);
	ev3_set_time_sp( middleM, 1000 );
	ev3_command_motor_by_name( middleM, "run-timed");
}

void release(ev3_motor_ptr middleM){
	ev3_stop_command_motor_by_name(middleM , "coast");		
	ev3_set_speed_sp( middleM, 70);
	ev3_set_time_sp( middleM, 1000 );
	ev3_command_motor_by_name( middleM, "run-timed");
}

/*
int main(int argc,char** argv)
{
	int i,time,speed,op_cl;
	//Loading all motors
	ev3_motor_ptr motors = ev3_load_motors();
	//Interating over the motors and printing some interesting data

	ev3_motor_ptr motor = motors;
	//ev3_motor_ptr sensor = sensors;
	

	ev3_motor_ptr leftM   = ev3_search_motor_by_port(motors, 'B');
	ev3_motor_ptr rightM  = ev3_search_motor_by_port(motors, 'C');
	ev3_motor_ptr middleM = ev3_search_motor_by_port(motors, 'D');

	while (motor)
	{
		ev3_reset_motor(motor);
	    printf("==== %s ====\n",motor->driver_name);
		printf("ident: %i\n",motor->driver_identifier);
		printf("motor: %i\n",motor->motor_nr);
		printf("port: %c\n",motor->port);
		printf("command count: %i\n",motor->command_count);
		for (i = 0; i < motor->command_count; i++)
			printf("command[%i]: %s\n",i,motor->commands[i]);
		printf("stop_command count: %i\n",motor->stop_command_count);
		for (i = 0; i < motor->stop_command_count; i++)
			printf("stop_command[%i]: %s\n",i,motor->stop_commands[i]);
		printf("stop_command %i is choosen.\n",motor->stop_command);
		//Let's open the motors ;)
		
		ev3_open_motor(motor);
		motor = motor->next;
		
		
	}
	
	
	//Loading all sensors
	ev3_sensor_ptr sensors = ev3_load_sensors();
	//I myself have a nxt sound sensor, which I detect here and set the
	//correct driver. If you don't have an nxt analog sensor connected
	//nothing should happen. If you have another than the sound sensor
	//connected the values will be interpreted as sound values. Adjust
	//this line in that case.
	ev3_driver_sensor(
		ev3_search_sensor_by_identifier( sensors, NXT_ANALOG, 0 ),
		"lego-nxt-sound"
	);
	//Interating over the sensors and printing some interesting data
	ev3_sensor_ptr sensor = sensors;
	while (sensor)
	{
		if (sensor->mode_count > 1)
			ev3_mode_sensor(sensor,1);
		
		//Let's open the sensors ;)
		ev3_open_sensor(sensor);
		sensor = sensor->next;
	}
	//Let's do this again, but this time we print the bin and val data
	//values for every found sensor for the next 10 seconds
	printf("Showing the sensor values for the next 10 seconds\n");
	for (i = 0; i < 10; i++)
	{
		sensor = sensors;
		while (sensor)
		{
			ev3_update_sensor_bin(sensor);
			ev3_update_sensor_val(sensor);
			printf("%s [%i]: \n",sensor->driver_name,sensor->port);
			int j;
			for (j = 0; j < sensor->data_count;j++)
				printf("\tvalue %i: %i (raw) - %i (formated)\n",j,sensor->bin_data[0].s32,sensor->val_data[0].s32);
			sensor = sensor->next;
		}
		sleep(1);
	}




	


	grab(middleM);
	turn(leftM, rightM, (int)FULLTURN_TIME, 45);

	//Waiting for the second motor to get to holding position
	while (
		(ev3_motor_state( leftM ) & MOTOR_RUNNING) ||
		(ev3_motor_state( rightM ) & MOTOR_RUNNING) ||
		(ev3_motor_state( middleM ) & MOTOR_RUNNING)
	);
	
	//release(middleM);
	move(leftM, rightM, 1000, 200);
	//Waiting for the second motor to get to holding position
	while (
		(ev3_motor_state( leftM ) & MOTOR_RUNNING) ||
		(ev3_motor_state( rightM ) & MOTOR_RUNNING) ||
		(ev3_motor_state( middleM ) & MOTOR_RUNNING)
	);

	//Let's delete the list in the very end. It will also close the
	//motors
	
	ev3_delete_motors(motors);
	ev3_delete_sensors(sensors);
	return 0;
	
	
}

*/

