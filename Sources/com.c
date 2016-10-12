/*
 * communication.c
 *
 *  Created on: 11-Oct-2016
 *      Author: Vikhyat
 */


#include<main.h>

uint8_t COM_FOUR_input(void){
	if(RXBUFF.count > 0) {
		return(1);
	}
	else{
		return(0);
	}
}

uint8_t COM_get_first(void){
	uint8_t rec;
	Circular_Pop(&RXBUFF,&rec);
	return(rec);
}

uint8_t COM_process_command(uint8_t ch)
{
	uint8_t result = 0;
	uint8_t rec;
	switch( ch )
	      {
	         case 'C':
	            //if((Rx[1] == 'L') || (Rx[2] == 'E') || (Rx[3] == 'D')){
	            	result = 1;
	           // }
	            break;
	         case 'L':
	           // if((Rx[1] == 'O') || (Rx[2] == 'G') || (Rx[3] == 'T')) {
	            	result = 2;
	           // }
	            break;
	         case 'T':
	           // if((Rx[1] == 'S')  || (Rx[2] == 'T') || (Rx[3] == 'C')) {
	            	result = 3;
	           // }
	            break;
	         case 'E':
				//if((Rx[1] == 'C') || (Rx[2] == 'O') || (Rx[3] == 'C')){
	            	result = 4;
				//}
				break;
	         case 'P':
	        	// if((Rx[1] == 'R') || (Rx[2] == 'O') || (Rx[3] == 'F')){
		            result = 5;
	           // }
	            break;

	         default:
	        	 break;
	      }
	return(result);
}

uint8_t COM_process_command1(uint8_t ch)
{
	uint8_t result = 0;
	uint8_t rec;
	switch( ch )
	      {
	     case 'M':
			 result = 1;
			 break;
		 case 'S':
			 result = 2;
			 break;
		 case 'I':
			 result = 3;
			 break;
		 case 'F':
			 result = 4;
			 break;
		 case 'L':
			 result = 5;
			 break;
		 case 'A':
			 result = 6;
			 break;
		 case 'C':
			 result = 7;
			 break;
		 case 'D':
			 result = 8;
			 break;

	         default:
	        	 break;
	      }
	return(result);
}


 void communicate(void)
 {

 }

 uint8_t User_Command(uint8_t* done){
	 uint8_t c;
	 uint8_t result=0;
	 *done = 0;
	    while((!*done))
	    {
	       c = COM_get_first();

            if ((c != 'C') && (c != 'L') &&
	            (c != 'T') && (c != 'E') &&
	            (c != 'P') )
	          {
	             //print error "not valid command"
	          }
	      else {
		         result = COM_process_command(c);
		         *done = 1;
	       }
	    }

	  return(result);
 }

 uint8_t User_Command1(uint8_t* done){
 	 uint8_t c;
 	 uint8_t result=0;
 	 *done = 0;
 	    while((!*done))
 	    {
 	       c = COM_get_first();

             if ((c != 'M') && (c != 'S') &&
 	            (c != 'I') && (c != 'F') &&
 	            (c != 'L') && (c != 'A')&&
				(c != 'C') && (c != 'D'))
 	          {
 	             //print error "not valid command"
 	          }
 	      else {
 		         result = COM_process_command1(c);
 		         *done = 1;
 	       }
 	    }

 	  return(result);
  }


void COM_PrintChar_withbuffer(uint8_t* data)
{
	uint8_t TxAddResult;
	Circular_Push(&TXBUFF,data);
}

uint8_t COM_getChar_withbuffer(void)
{
   uint8_t c;
   uint8_t RxRemResult;

   while(Is_buffer_full(&RXBUFF));      /* wait for a received character*/
   Circular_Pop(&RXBUFF,&c);
   return(c);
}

void COM_printstring_withbuffer( uint8_t *str)
{
   uint8_t TxAddResult;
   while( *str != '\0' )
   {
    Circular_Push(&TXBUFF,*str);
	str++;

   }
}


void COM_Create_Tx(cirbuffer_t *cptr,uint8_t size){
	CirBuff_init(cptr, size,Tx);
}
void COM_Create_Rx(cirbuffer_t *cptr,uint8_t size){
	CirBuff_init(cptr, size,Rx);
};
