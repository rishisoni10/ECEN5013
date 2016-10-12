
#include "main.h"

typedef void(*UserAction)(void);

static int i = 0;
uint8_t TransferState = 0,CmdProcessingDone = 0;
uint8_t LEDControlRequested = 0;
uint8_t LogRequested =0;
uint8_t ECOReqested = 0;
uint8_t MENUprinted = 0;
UserAction TaskToPerform[6];
uint8_t testdone = 0;

void Task_LED(void)
{
	if(!LEDControlRequested){
    LOG_4("\r\nControl LED through UART\r\n");
    LOG_4("\r\nPress 'a' to glow previous color\r\n");
    LOG_4("\r\nPress 'd' to glow next color\r\n");
    LOG_4("\r\nPress 'w' to increase brightness\r\n");
    LOG_4("\r\nPress 's' to decrease brightness\r\n");
	}
	LEDControlRequested = 1;
	//code to control LED based on UART input
	Control_LED();
}

void Task_LOG(void)
{
	if(!LogRequested){
	LOG_0("\r\nTesting123,Serial print test,no params",40);
	LOG_1("\r\nThis is an integer number:",28,200,sizeof(200));
	LOG_1("\r\nThis is an integer number:",28,4096,sizeof(4096));
	LOG_1("\r\nThis is an integer number:",28,123456,sizeof(123456));
	LOG_2("\r\nThis is a floating number:",29,1543.321);

	LogRequested = 1;
	}
}

void Task_TST(void)
{
	 cirbuffer_t testbuff;
	 uint8_t test[5];
	 uint8_t result,len=5,data;
     //module test circular buffer
	  if(testdone == 0){
		 LOG_4("\r\nRunning Unit Tests for circular buffer\r\n");
		 //create a test circular buffer and initialize it:

		 CirBuff_init(&testbuff,5,test);

		 //test addition of data
		 LOG_4("\r\nTest1: Test addition of a new element \r\n");
		 result = Circular_Push(&testbuff,'a');
		 if(result) {
		 LOG_4("\r\nTestCase 1/6: passed \r\n");
		 }
		 else {
			 LOG_4("\r\nTestCase 1/6: passed \r\n");
		 }

		 //test that no element is added after the buffer is full
		 LOG_4("\r\nTest2: Test addition of a new element after buffer is full \r\n");
		 while(len--){
		  Circular_Push(&testbuff,'a');
		 }
		 result = Circular_Push(&testbuff,'b');
		 if(result) {
		 LOG_4("\r\nTestCase 2/6: Failed \r\n");
		 }
		 else {
			 LOG_4("\r\nTestCase 2/6: passed \r\n");
		 }

		 //test removal of element from the buffer
		 LOG_4("\r\nTest3: Test removal of an element \r\n");
		 result = Circular_Pop(&testbuff,&data);
		 if(result) {
		 LOG_4("\r\nTestCase 3/6: Passed \r\n");
		 }
		 else {
			 LOG_4("\r\nTestCase 3/6: Failed \r\n");
		 }

		 //test removal of element from an empty buffer
		 LOG_4("\r\nTest4: Test removal of an element from empty buffer \r\n");
		 len = 20;
		 while(len--){
			 Circular_Pop(&testbuff,&data);
		 }
		 result = Circular_Pop(&testbuff,&data);
		 if(result) {
		  LOG_4("\r\nTestCase 4/6: Failed \r\n");
		 }
		 else {
		  LOG_4("\r\nTestCase 4/6: Passed \r\n");
		 }

		 //test buffer empty function
		 LOG_4("\r\nTest5: Test buffer empty function \r\n");
		 result = Is_buffer_Empty(&testbuff);
		 if(result) {
		  LOG_4("\r\nTestCase 5/6: Passed \r\n");
		 }
		 else {
		  LOG_4("\r\nTestCase 5/6: Failed \r\n");
		 }

		 //test buffer full function
		 LOG_4("\r\nTest6: Test buffer full function \r\n");
		 len = 6;
		 while(len--){
			   Circular_Push(&testbuff,'a');
			 }
			 result = Is_buffer_full(&testbuff);
			 if(result) {
			  LOG_4("\r\nTestCase 6/6: Passed \r\n");
			 }
			 else {
				 LOG_4("\r\nTestCase 6/6: Failed \r\n");
			 }

			 testdone = 1;
	 }

}

void Task_ECO(void)
{
	uint8_t read_char,i=0;
	ECOReqested = 1;

			LOG_4("\r\nEnter a string to echo\r\n");
			TransferState=0;
			while(1)									//infinite loop
			{
				//receive in RX buff ,loop to copy contents from UART0_D into RX BUFFER
				if(TransferState == 1)						//incoming data in rx buff complete
				{
					i=0;
					while(i<=10)
					{
						Circular_Pop(&RXBUFF,&read_char);	//read from rx buff
						Circular_Push(&TXBUFF,read_char);	//write to tx buff
						i++;
					}
					TransferState=2;
					UART0_C2 |= UART0_C2_TIE_MASK;		//enable tx interrupt after copy from rxbuff complete
				}
				if(TransferState == 3)						//copied from tx buff complete
				{
					break;
					//delete heap memory
				}
			}
}

void Task_PRO(void)
{
 // profiler code
	uint8_t i = 0;
	//pll_init(8000000, LOW_POWER, CRYSTAL,4,24,MCGOUT);

	uint32_t avg_clock_cycles;
	uint32_t avg_time;
	uint32_t sum1=0, sum2=0;
	float a [10];
	double b[10];


	while(i<10)
{
	uint8_t src[DATA_LEN_MAX];
	uint32_t length;
	length = DATA_LEN_MAX;
	uint8_t dst[DATA_LEN_MAX];

	start_profiler();
	my_memmove(dst, src, length);
	stop_profiler();

	a[i] = count*480 + TPM0_CNT;
	sum1 += a[i];
	b[i] = (a[i] / 48000000.00)*1000000.00;
	sum2 += b[i];

	i++;
}
	avg_clock_cycles = sum1/(10*i);
	avg_time = sum2/(i*10);
}

void Task_Ask(void)
{
	if(!MENUprinted){
	//reset all control flags
	 LEDControlRequested = 0;
	 LogRequested =0;
	 ECOReqested = 0;

		// ask user for a command
	    LOG_4("\r\nChoose an operation to perform:\r\n");
	    LOG_4("\r\nPress C to control\r\n");
	    LOG_4("\r\nPress L to test log functions\r\n");
	    LOG_4("\r\nPress T to test circular buffer \r\n");
	    LOG_4("\r\nPress E to check circular buffer echo function\r\n");
	    LOG_4("\r\nPress P to profile \r\n");
	    MENUprinted = 1;
	}
}

void Env_Setup(void)
{
	//Setup teh tx and rx buffers
	COM_Create_Tx(&TXBUFF,25);
	COM_Create_Rx(&RXBUFF,25);

	TaskToPerform[0] = &Task_Ask;
	TaskToPerform[1] = &Task_LED;
	TaskToPerform[2] = &Task_LOG;
	TaskToPerform[3] = &Task_TST;
	TaskToPerform[4] = &Task_ECO;
	TaskToPerform[5] = &Task_PRO;
}

int main(void)
{
    uint8_t cammand = 0;
	initialize_UART(BAUD_RATE);
    led_init();
    Env_Setup();

    while(1)
    {
    //wait for charter string from user
        TaskToPerform[cammand]();

    //check the command given
    	if(!CmdProcessingDone){
    	   Task_Ask();
           cammand = User_Command(&CmdProcessingDone);
    	}

    }
	return 0;
}
