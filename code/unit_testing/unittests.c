#include <stdlib.h>
#include "ctest.h"
#include "button.h"
#include "led.h"
#include "lcd.h"
#include "physics.h"
#include "params.h"
#include "slider.h"


//makes sure that button0 is read correctly when pressed, the button logic should say no button was pressed, but then after released it should log the button press.

CTEST_DATA(button_test0) {
	uint8_t flag_loads[2];
	button_result results[2];
};

CTEST_SETUP(button_test0) {
	data->flag_loads[0] = button_0p;
	data->flag_loads[1] = button_0r;
	data->results[0] = button_nothing;
	data->results[1] = button_decrement;
}

CTEST2(button_test0, bt0) { 

    for (int i = 0; i < 2; i++) {
        ASSERT_EQUAL(data->results[i], button_decoder(data->flag_loads[i]));
    }
}

//makes sure that button1 is read correctly when pressed, the button logic should say no button1 was pressed, but then after released it should log the button press.

CTEST_DATA(button_test1) {
	uint8_t flag_loads[2];
	button_result results[2];
};

CTEST_SETUP(button_test1) {
	data->flag_loads[0] = button_1p;
	data->flag_loads[1] = button_1r;
	data->results[0] = button_nothing;
	data->results[1] = button_increment;
}

CTEST2(button_test1, bt1) { 

    for (int i = 0; i < 2; i++) {
        ASSERT_EQUAL(data->results[i], button_decoder(data->flag_loads[i]));
    }
}


//makes sure that button0 is read correctly when pressed, the button logic should say no button is pressed if button 0 is pressed and then buton 1 is pressed and then button 0 is released, in the whole scenario no buttons should be recorded

CTEST_DATA(button_error_test0) {
	uint8_t flag_loads[8];
};

CTEST_SETUP(button_error_test0) {
	data->flag_loads[0] = button_0p;
	data->flag_loads[1] = button_1p;
	data->flag_loads[2] = button_0r;
	data->flag_loads[3] = button_1r;
	data->flag_loads[4] = button_0p;
	data->flag_loads[5] = button_1p;
	data->flag_loads[6] = button_1r;
	data->flag_loads[7] = button_0r;
}

CTEST2(button_error_test0, bte0) { 

    for (int i = 0; i < 8; i++) {
        ASSERT_EQUAL(button_nothing, button_decoder(data->flag_loads[i]));
    }
}


//makes sure that button1 is read correctly when pressed, the button logic should say no button is pressed if button 1 is pressed and then buton 0 is pressed and then button 1 is released, in the whole scenario no buttons should be recorded

CTEST_DATA(button_error_test1) {
	uint8_t flag_loads[8];
};

CTEST_SETUP(button_error_test1) {
	data->flag_loads[0] = button_1p;
	data->flag_loads[1] = button_0p;
	data->flag_loads[2] = button_1r;
	data->flag_loads[3] = button_0r;
	data->flag_loads[4] = button_1p;
	data->flag_loads[5] = button_0p;
	data->flag_loads[6] = button_0r;
	data->flag_loads[7] = button_1r;
}

CTEST2(button_error_test1, bt1) { 

    for (int i = 0; i < 8; i++) {
        ASSERT_EQUAL(button_nothing, button_decoder(data->flag_loads[i]));
    }
}

//Makes sure to return the low value of the threshold in a given array passed in  
static void arr_cpy(uint32_t* a1, uint32_t* a2){
	for(int i=0; i<4; i++){
		a1[i] = a2[i];
	}
}

CTEST_DATA(slider_test1) {
	uint32_t flag_loads[8][4];
	slider_value results[8];
};

CTEST_SETUP(slider_test1) {
	data->results[0] = slider_farleft;
	data->results[1] = slider_left;
	data->results[2] = slider_right;
	data->results[3] = slider_farright;
	data->results[4] = slider_farleft;
	data->results[5] = slider_left;
	data->results[6] = slider_right;
	data->results[7] = slider_farright;
	
	
	uint32_t  a0[4] = {128, 255, 255, 255};
	uint32_t  a1[4] = {255, 128, 255, 255};
	uint32_t  a2[4] = {255, 255, 128, 255};
	uint32_t  a3[4] = {255, 255, 255, 128};
	uint32_t  a4[4] = {128, 130, 150, 129};
	uint32_t  a5[4] = {128, 120, 240, 150};
	uint32_t  a6[4] = {128, 254, 90, 185};
	uint32_t  a7[4] = {128, 120, 175, 55};

	arr_cpy(data->flag_loads[0], a0);
	arr_cpy(data->flag_loads[1], a1);
	arr_cpy(data->flag_loads[2], a2);
	arr_cpy(data->flag_loads[3], a3);
	arr_cpy(data->flag_loads[4], a4);
	arr_cpy(data->flag_loads[5], a5);
	arr_cpy(data->flag_loads[6], a6);
	arr_cpy(data->flag_loads[7], a7);
}

CTEST2(slider_test1, slider1) { 

    for (int i = 0; i < 8; i++) {
        ASSERT_EQUAL(data->results[i], capsense_getVal(data->flag_loads[i]));
    }
}

//Makes sure to return the center if no value is below the threshold

CTEST_DATA(slider_center_test) {
	uint32_t flag_loads[3][4];
	slider_value results[3];
};

CTEST_SETUP(slider_center_test) {
	data->results[0] = slider_center;
	data->results[1] = slider_center;
	data->results[2] = slider_center;

	
	
	uint32_t  a0[4] = {255, 255, 255, 255};
	uint32_t  a1[4] = {255, 230, 255, 255};
	uint32_t  a2[4] = {250, 235, 230, 253};


	arr_cpy(data->flag_loads[0], a0);
	arr_cpy(data->flag_loads[1], a1);
	arr_cpy(data->flag_loads[2], a2);

}

CTEST2(slider_center_test, slider_center) { 

    for (int i = 0; i < 3; i++) {
        ASSERT_EQUAL(data->results[i], capsense_getVal(data->flag_loads[i]));
    }
}


//Makes sure to return the error if values are not valid inputs
CTEST_DATA(slider_error_test) {
	uint32_t flag_loads[3][4];
	slider_value results[3];
};

CTEST_SETUP(slider_error_test) {
	data->results[0] = slider_error;
	data->results[1] = slider_error;
	data->results[2] = slider_error;

	
	
	uint32_t  a0[4] = {0, 0, 0, 0};
	uint32_t  a1[4] = {500, 500, 500, 500};
	uint32_t  a2[4] = {250, 235, 2000, 253};


	arr_cpy(data->flag_loads[0], a0);
	arr_cpy(data->flag_loads[1], a1);
	arr_cpy(data->flag_loads[2], a2);

}

CTEST2(slider_error_test, slider_error) { 

    for (int i = 0; i < 3; i++) {
        ASSERT_EQUAL(data->results[i], capsense_getVal(data->flag_loads[i]));
    }
}

//Makes sure the LED1 is driven correctly so that if the flag for LED1 is passed, LED1 will still be up after
CTEST_DATA(LED1_test) {
	uint16_t percentage;
	uint8_t flags[3];
	uint8_t results[3];
};

CTEST_SETUP(LED1_test) {
	data->percentage = 5;
	
	data->results[0] = 0;
	data->results[1] = LED1;
	data->results[2] = LED1;

	
	
	
	data->flags[0] = 0;
	data->flags[1] = LED1;
	data->flags[2] = 0;

}

CTEST2(LED1_test, LED1) { 

    for (int i = 0; i < 3; i++) {
        ASSERT_EQUAL(data->results[i],  LED1 & pwm_LED_driver(data->percentage, data->flags[i])); //make sure to only look for LED1's flag
    }
}

//Makes sure the LED0 is driven correctly so that if the flag for LED0 is passed, LED0 will restart and remain lit based on percentage -in this case it will remain lit for all 8 parts of the cycle
CTEST_DATA(LED0_full_test) {
	uint16_t percentage;
	uint8_t flags[8];
	uint8_t results[8];
};

CTEST_SETUP(LED0_full_test) {
	data->percentage = 8;
	
	data->results[0] = LED0;
	data->results[1] = LED0;
	data->results[2] = LED0;
	data->results[3] = LED0;
	data->results[4] = LED0;
	data->results[5] = LED0;
	data->results[6] = LED0;
	data->results[7] = LED0;
	
	
	
	data->flags[0] = LED0;
	data->flags[1] = 0;
	data->flags[2] = 0;
	data->flags[3] = 0;
	data->flags[4] = 0;
	data->flags[5] = 0;
	data->flags[6] = 0;
	data->flags[7] = 0;


}

CTEST2(LED0_full_test, LED0) { 

    for (int i = 0; i < 8; i++) {
        ASSERT_EQUAL(data->results[i],  LED0 & pwm_LED_driver(data->percentage, data->flags[i])); //make sure to only look for LED0's flag
    }
}

//Makes sure the LED0 is driven correctly so that if the flag for LED0 is passed, LED0 will restart and remain lit based on percentage -in this case it will remain lit for half / 4 parts of the cycle
CTEST_DATA(LED0_half_test) {
	uint16_t percentage;
	uint8_t flags[8];
	uint8_t results[8];
};

CTEST_SETUP(LED0_half_test) {
	data->percentage = 4;
	
	data->results[0] = LED0;
	data->results[1] = LED0;
	data->results[2] = LED0;
	data->results[3] = LED0;
	data->results[4] = 0;
	data->results[5] = 0;
	data->results[6] = 0;
	data->results[7] = 0;
	
	
	
	data->flags[0] = LED0;
	data->flags[1] = 0;
	data->flags[2] = 0;
	data->flags[3] = 0;
	data->flags[4] = 0;
	data->flags[5] = 0;
	data->flags[6] = 0;
	data->flags[7] = 0;


}

CTEST2(LED0_half_test, LED0) { 

    for (int i = 0; i < 8; i++) {
        ASSERT_EQUAL(data->results[i],  LED0 & pwm_LED_driver(data->percentage, data->flags[i])); //make sure to only look for LED0's flag
    }
}

//Makes sure the LED0 is driven correctly so that if the flag for LED0 is passed, LED0 will restart and remain lit based on percentage -in this case it will remain lit for none / 0 parts of the cycle
CTEST_DATA(LED0_off_test) {
	uint16_t percentage;
	uint8_t flags[8];
	uint8_t results[8];
};

CTEST_SETUP(LED0_off_test) {
	data->percentage = 0;
	
	data->results[0] = 0;
	data->results[1] = 0;
	data->results[2] = 0;
	data->results[3] = 0;
	data->results[4] = 0;
	data->results[5] = 0;
	data->results[6] = 0;
	data->results[7] = 0;
	
	
	
	data->flags[0] = LED0;
	data->flags[1] = 0;
	data->flags[2] = 0;
	data->flags[3] = 0;
	data->flags[4] = 0;
	data->flags[5] = 0;
	data->flags[6] = 0;
	data->flags[7] = 0;


}

CTEST2(LED0_off_test, LED0) { 

    for (int i = 0; i < 8; i++) {
        ASSERT_EQUAL(data->results[i],  LED0 & pwm_LED_driver(data->percentage, data->flags[i])); //make sure to only look for LED0's flag
    }
}


//Makes sure the forces are computed properly
CTEST_DATA(physics_test) {
	uint32_t max_f;
	uint16_t f_percent[8];
	slider_value direction[8];
	int results[8];
};

CTEST_SETUP(physics_test) {
	data->max_f = 160;
	
	data->f_percent[0] = 0;
	data->f_percent[1] = 8;
	data->f_percent[2] = 8;
	data->f_percent[3] = 8;
	data->f_percent[4] = 8;
	data->f_percent[5] = 4;
	data->f_percent[6] = 3;
	data->f_percent[7] = 7;

	
	data->results[0] = 0;
	data->results[1] = 80;
	data->results[2] = -80;
	data->results[3] = -160;
	data->results[4] = 160;
	data->results[5] = 40;
	data->results[6] = 30;
	data->results[7] = 70;
	
	
	
	data->direction[0] = slider_farright;
	data->direction[1] = slider_right;
	data->direction[2] = slider_left;
	data->direction[3] = slider_farleft;
	data->direction[4] = slider_farright;
	data->direction[5] = slider_right;
	data->direction[6] = slider_right;
	data->direction[7] = slider_right;


}

CTEST2(physics_test, LED0) { 

    for (int i = 0; i < 8; i++) {
        ASSERT_EQUAL(data->results[i],  force_generator(data->direction[i],data->f_percent[i], data->max_f)); //make sure to only look for LED0's flag
    }
}


