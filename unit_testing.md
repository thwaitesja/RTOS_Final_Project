**Unit Tests** 

My current plan for unit tests are to have these tests be implemented as calling and testing the inner functions of a task. This allows me to simulate desired testing
data as if I recieved the data from ITC without having to actually load the data into the ITC. The unit tests will be as follows:

- Button 0 read to insure a button0 pressed event and then a button0 released event are sent into the pushbutton task the button recording function of PushButton_task will return that pushbutton 0 is pressed. This is cut by the Button ISR and before the writing of force percentage to the shared Force Percentage Data.

- Button 1 read to insure a button1 pressed event and then a button1 released event are sent into the pushbutton task the button recording function of PushButton_task will return that pushbutton 1 is pressed. This is cut by the Button ISR and before the writing of force percentage to the shared Force Percentage Data.

- Button error read to insure a button1 pressed event and then a button0 pressed event and then a button1 released event are sent into the pushbutton task the button recording function of PushButton_task will return that no pushbuttons are pressed. This is cut by the Button ISR and before the writing of force percentage to the shared Force Percentage Data.

- Button error read to insure a button0 pressed event and then a button1 pressed event and then a button0 released event are sent into the pushbutton task the button recording function of PushButton_task will return that no pushbuttons are pressed. This is cut by the Button ISR and before the writing of force percentage to the shared Force Percentage Data.

- Slider Reading pressed test, ensures that given values of the normalized slider positions function with all below the pressed threshold, it will return the lowest slider position. This unit test is cut by the Touch slider semaphore an the input to the force direction data.

- Slider Reading not pressed, ensures that given values of the normalized slider positions function with all values above the pressed threshold, it will return that no slider is pressed. This unit test is cut by the Touch slider semaphore an the input to the force direction data.

- Slider Reading out of bounds error,  ensures that given values of the normalized slider positions are all 0 or all above the given threshold, it will return an error code that can be caught to prevent buggy performance.  This unit test is cut by the Touch slider semaphore an the input to the force direction data.

- LED1 Control, this unit test looks at the handling logic and makes sure if a stub provides the Event Flag for LED1 to be turned on, the handling logic will turn on LED1. This Unit test is cut Around the LED Task by the Event Flag data structure and the BSP LED functions.

- LED0 Control, this unit test looks at the handling logic and makes sure if a stub provides the Force percentage at 100%, the logic will return that LED0 should be high. This Unit test is cut Around the LED Task by the force percentage data structure and the BSP LED functions.

- LED0 Control, this unit test looks at the handling logic and makes sure if a stub provides the Force percentage at 50%, the logic will return that LED0 should be low. This Unit test is cut Around the LED Task by the force percentage data structure and the BSP LED functions.

- LED0 Control, this unit test looks at the handling logic and makes sure if a stub provides the Force percentage at 0%, the logic will return that LED0 should be low. This Unit test is cut Around the LED Task by the force percentage data structure and the BSP LED functions.

- Physics_generator task, this unit test tests the physics engine with given global inputs as well as the force direction and force percentage and makes sure that the correct force is computed as a result of the global constants as well as the force direction and force percentage.