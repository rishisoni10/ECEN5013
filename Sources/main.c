
#include "main.h"

typedef void(*UserAction)(void);

static int i = 0;
uint8_t TransferState = 0,CmdProcessingDone = 0;
uint8_t CmdDone = 0;
uint8_t LEDControlRequested = 0;
uint8_t LogRequested =0;
uint8_t ECOReqested = 0;
uint8_t MENUprinted = 0;
UserAction TaskToPerform[6];
UserAction FuntionToProfile[9];
uint8_t testdone = 0,ECOdone = 0, PROdone = 0;
uint8_t test = 4;
uint8_t cammand = 0;
uint8_t cammand1 = 0;

void Task_LED(void)
{
	if(!LEDControlRequested){
    LOG_4("\r\nControl LED through UART\r\n");
    LOG_4("\r\nPress 'A' to glow previous color\r\n");
    LOG_4("\r\nPress 'D' to glow next color\r\n");
    LOG_4("\r\nPress 'W' to increase brightness\r\n");
    LOG_4("\r\nPress 'S' to decrease brightness\r\n");
    LOG_4("\r\nPress 'B' to go back to main menu\r\n");
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
	MENUprinted = 0;
	CmdProcessingDone = 0;
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
		MENUprinted = 0;
		CmdProcessingDone = 0;

}

void Task_ECO(void)
{
	uint8_t read_char,i=0;
	ECOReqested = 1;
	  if(ECOdone == 0){
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
					LOG_4("\r\nECO\r\n");
					break;
					//delete heap memory
				}
			}
			ECOdone = 1;
	  }
		MENUprinted = 0;
		CmdProcessingDone = 0;
}

void Test_memmov(void){
	uint8_t src[DATA_LEN_MAX];
	uint32_t length;
	uint8_t dst[DATA_LEN_MAX];

	if(test == 4){
		length = 10;
	}
	else if(test == 3){
		length = 100;
	}
	else if(test == 2){
		length = 1000;
	}
	else
	{
		length = 5000;
	}

	start_profiler();
	my_memmove(src,dst,length);
	stop_profiler();

}

void Test_memset(void){

	uint8_t src[DATA_LEN_MAX];
	uint32_t length;

	if(test == 4){
		length = 10;
	}
	else if(test == 3){
		length = 100;
	}
	else if(test == 2){
		length = 1000;
	}
	else
	{
		length = 5000;
	}

	start_profiler();
	my_memzero(src,length);
	stop_profiler();


}

void Test_itoa(void){

	uint8_t src[DATA_LEN_MAX];
	uint8_t* str;
	uint32_t data;
	str = src;

	   if(test == 4){
		   data = 10;
		}
		else if(test == 3){
			data = 100;
		}
		else if(test == 2){
			data = 1000;
		}
		else
		{
			data = 5000;
		}

		start_profiler();
		itoa(str, data, 10);
		stop_profiler();
}

void Test_ftoa(void){

	uint8_t src[DATA_LEN_MAX];
	uint8_t* str;
	float data;
	str = src;

	if(test == 4){
		data = 123.23;
		}
		else if(test == 3){
			data = 1002.3;
		}
		else if(test == 2){
			data = 1023.345;
		}
		else
		{
			data = 3243.345;
		}

		start_profiler();
		str = ftoa( data);
		stop_profiler();
}

void Test_log1(void){
	uint8_t src[DATA_LEN_MAX];
	uint32_t length;

	if(test == 4){
		length = 10;
	}
	else if(test == 3){
		length = 100;
	}
	else if(test == 2){
		length = 1000;
	}
	else
	{
		length = 5000;
	}

	start_profiler();
	LOG_0(src,length);
	stop_profiler();

}

void Test_maloc(void){
	    uint8_t src[DATA_LEN_MAX];
		uint32_t length;
		cirbuffer_t testbuf;

		if(test == 4){
			length = 10;
		}
		else if(test == 3){
			length = 100;
		}
		else if(test == 2){
			length = 1000;
		}
		else
		{
			length = 5000;
		}
		start_profiler();
		CirBuff_init(&testbuf,length,src);
		stop_profiler();
}

void Test_Addc(void){
	    uint8_t src[DATA_LEN_MAX];
		uint32_t length ;
		cirbuffer_t testbuf;
		CirBuff_init(&testbuf,5,src);

		if(test == 4){
			length = 1;
		}
		else if(test == 3){
			length = 2;
		}
		else if(test == 2){
			length = 3;
		}
		else
		{
			length = 6;
		}
		while(length--){
		start_profiler();
		Circular_Push(&testbuf,'a');
		stop_profiler();
		}
}



void Test_Delc(void){
	    uint8_t src[DATA_LEN_MAX];
		uint32_t length = 5 ;
		uint8_t* data;
		cirbuffer_t testbuf;
		CirBuff_init(&testbuf,5,src);
		while(length--){
				Circular_Push(&testbuf,'a');
				}

		if(test == 4){
			length = 1;
		}
		else if(test == 3){
			length = 2;
		}
		else if(test == 2){
			length = 3;
		}
		else
		{
			length = 6;
		}
		while(length--){
		start_profiler();
		Circular_Pop(&testbuf,&data);
		stop_profiler();
		}
}

void Test_None(void){

}

void test_setup(void){

	//FuntionToProfile[0] = &Test_None;
	FuntionToProfile[1] = &Test_memmov;
	FuntionToProfile[2] = &Test_memset;
	FuntionToProfile[3] = &Test_itoa;
	FuntionToProfile[4] = &Test_ftoa;
	FuntionToProfile[5] = &Test_log1;
	FuntionToProfile[6] = &Test_maloc;
	FuntionToProfile[7] = &Test_Addc;
	FuntionToProfile[8] = &Test_Delc;

}

void printinfo(uint8_t cmd, uint8_t test){
	if(cmd == 1 || cmd == 2){
		if(test == 4){
			LOG_4("\r\nFor 10 bytes\r\n");
		}
		else if(test == 3){
			LOG_4("\r\nFor 100 bytes\r\n");
		}
		else if(test == 2){
			LOG_4("\r\nFor 1000 bytes\r\n");
		}
		else
		{
			LOG_4("\r\nFor 5000 bytes\r\n");
		}
	}
	else if(cmd == 4)
	{
		if(test == 4){
			LOG_4("\r\nFor float data as 123.23\r\n");
		}
		else if(test == 3){
			LOG_4("\r\nFor float data as 1002.3\r\n");
		}
		else if(test == 2){
			LOG_4("\r\nFor float data as 1023.345\r\n");
		}
		else
		{
			LOG_4("\r\nFor float data as 3243.345\r\n");
		}

	}
	else if(cmd == 4)
	{
		if(test == 4){
			LOG_4("\r\nFor integer data as 10\r\n");
		}
		else if(test == 3){
			LOG_4("\r\nFor integer data as 100\r\n");
		}
		else if(test == 2){
			LOG_4("\r\nFor integer data as 1000\r\n");
		}
		else
		{
			LOG_4("\r\nFor integer data as 5000\r\n");
		}
	}
	else if(cmd == 5)
	{
		if(test == 4){
			LOG_4("\r\nFor Logging a 10 byte string\r\n");
		}
		else if(test == 3){
			LOG_4("\r\nFor Logging a 100 byte string\r\n");
		}
		else if(test == 2){
			LOG_4("\r\nFor Logging a 1000 byte string\r\n");
		}
		else
		{
			LOG_4("\r\nFor Logging a 5000 byte string\r\n");
		}
	}
	else if(cmd == 6)
		{
			if(test == 4){
				LOG_4("\r\nMalloc a memory of size  10\r\n");
			}
			else if(test == 3){
				LOG_4("\r\nMalloc a memory of size  100\r\n");
			}
			else if(test == 2){
				LOG_4("\r\nMalloc a memory of size  1000\r\n");
			}
			else
			{
				LOG_4("\r\nMalloc a memory of size  5000\r\n");
			}
		}
	else if(cmd == 7)
			{
				if(test == 4){
					LOG_4("\r\nadd FIVE element to buffer of size 5\r\n");
				}
				else if(test == 3){
					LOG_4("\r\nadd FOUR element to buffer of size 5\r\n");
				}
				else if(test == 2){
					LOG_4("\r\nadd THREE element to buffer of size 5\r\n");
				}
				else
				{
					LOG_4("\r\nadd ONE element to buffer of size 5\r\n");
				}

			}
	else if(cmd == 8)
			{
		if(test == 4){
				LOG_4("\r\nremove FIVE element to buffer of size 5\r\n");
			}
			else if(test == 3){
				LOG_4("\r\nremove THREE element to buffer of size 5\r\n");
			}
			else if(test == 2){
				LOG_4("\r\nremove TWO element to buffer of size 5\r\n");
			}
			else
			{
				LOG_4("\r\nremove ONE element to buffer of size 5\r\n");
			}


			}
}
void Task_PRO(void)
{
 // profiler code
	uint8_t i = 0;
	uint32_t avg_clock_cycle=0;
	uint32_t avg_time=0;
	uint32_t sum1=0, sum2=0;
	float a [10];
	double b[10];

    test_setup();

  if(PROdone == 0){

	if(!CmdDone){
	  LOG_4("\r\n  Choose a function to profile from the list below:");
	  LOG_4("\r\n|________________________________________________|\r\n");
	  LOG_4("\r\n|  Press M to profile memmov                     |\r\n");
	  LOG_4("\r\n|  Press S to profile memset                     |\r\n");
	  LOG_4("\r\n|  Press I to profile itoa                       | \r\n");
	  LOG_4("\r\n|  Press F to profile ftoa                       |\r\n");
	  LOG_4("\r\n|  Press L to profile log1                       |\r\n");
	  LOG_4("\r\n|  Press A to profile malloc                     |\r\n");
	  LOG_4("\r\n|  Press C to profile addcirbuf                  |\r\n");
	  LOG_4("\r\n|  Press D to profile delcirbuf                  |\r\n");
	  LOG_4("\r\n|________________________________________________|\r\n");
		}

	if(!CmdDone){
	  cammand1 = User_Command1(&CmdDone);
	}
	else{
       while(test){

    	     avg_clock_cycle=0;
    	   	 avg_time=0;
    	   	 sum1=0;
    	   	 sum2=0;
    	   	 i = 0;

    	   	 printinfo(cammand1,test);

			while(i<10)
			{
				FuntionToProfile[cammand1]();

				a[i] = count*40 + TPM1_CNT;
				sum1 += a[i];
				b[i] = (a[i] / 4);
				sum2 += b[i];

				i++;
			}
			    avg_clock_cycle = sum1*12/(i*10); // multiply by 12 as the core is 12 times faster than the timer
				avg_time = sum2/(i*10);

				LOG_2("\r\nAverage number of CPU cycles :",32,avg_clock_cycle);
				LOG_2("\r\nAverage time take:",20,avg_time);
				LOG_4(" MicroSecond \r\n");
				test--;
          }
       PROdone = 1;
       CmdDone = 0;
       test =4;
	  }
  }
  else{

	MENUprinted = 0;
	CmdProcessingDone = 0;
  }
}

void Task_Ask(void)
{
	if(!MENUprinted){
	//reset all control flags
	 LEDControlRequested = 0;
	 LogRequested =0;
	 ECOReqested = 0;
	 testdone = 0;
	 ECOdone = 0;
     TransferState = 0;
     PROdone = 0;
		// ask user for a command
        LOG_4("\r\n");
	    LOG_4("\r\n ________________________________________________\r\n");
	    LOG_4("\r\n| Choose an operation to perform:                |\r\n");
	    LOG_4("\r\n|________________________________________________|\r\n");
	    LOG_4("\r\n|  Press C to control                            |\r\n");
	    LOG_4("\r\n|  Press L to test log functions                 |\r\n");
	    LOG_4("\r\n|  Press T to test circular buffer               | \r\n");
	    LOG_4("\r\n|  Press E to check circular buffer echo function|\r\n");
	    LOG_4("\r\n|  Press P to profile                            |\r\n");
	    LOG_4("\r\n|________________________________________________|\r\n");
	    LOG_4("\r\n");
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
