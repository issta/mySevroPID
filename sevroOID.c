#include  <stdio.h>
#include  <stdlib.h>
#include  <ctype.h>
#include  <conio.h>
#include  <string.h>
#include  <dos.h>
#include  <math.h>
#include  <bios.h>


typedef struct {
long float P_gain;
long float I_gain;
long float D_gain;
long float lasterror;
long float Llasterror;
long float deltaTime;
} PID;

long float getDeltaError(long float PV ,long float setP)
{
   return setP-PV;
}

long float PIDprocess(PID* P_Pid,long float deltaE)
{
    long float PV=0.0;
    long float Pgain=0.0;
    long float Igain=0.0;
    long float Dgain=0.0;
    
    
    
    /*P gain*/ 
        Pgain=P_Pid->P_gain*(deltaE-P_Pid->lasterror);
    /*I gain  */ 
        Igain=P_Pid->I_gain*deltaE;
    /*D gain */ 
        Dgain=P_Pid->D_gain*((deltaE-P_Pid->lasterror) -P_Pid->lasterror+P_Pid->Llasterror)/P_Pid->deltaTime;
    
       P_Pid->Llasterror=P_Pid->lasterror;
       P_Pid->lasterror=deltaE;

       return Pgain+Igain+Dgain;
       
}

void PrintPID_PV_Out(PID* P_Pid,long float pv)
{
   printf("\r\nP gain is %f\r\n",P_Pid->P_gain);
    printf("I gain is %f\r\n",P_Pid->I_gain);
     printf("D gain is %f\r\n",P_Pid->D_gain);
      printf("LastError gain is %f\r\n",P_Pid->lasterror);
       printf("LastLastError gain is %f\r\n",P_Pid->Llasterror);
         printf("Pv outputis %f\r\n\r\n",pv);
}

int main(void)
{
   PID myServo;
   int  time=0;
   long float mPvback=150.0;
   
   long float msetP=50.0;
   long float delta=0;
   long float PVout=0;
   myServo.P_gain=4.0;
   myServo.I_gain=0.50;
   myServo.D_gain=0.09;
   myServo.lasterror=0.0;
   myServo.Llasterror=0.0;
   myServo.deltaTime=20;
   while(1)
   	{
   	/*if((time%10)==5)*/
   	  {
   	  printf("\r\nplease input your parameter!\r\n");
   	  scanf("%lf %lf",&mPvback,&msetP);
   	  printf("mPvback=%f msetP=%f,",mPvback,msetP);
   	
   	  }
   	   
   	  delta=getDeltaError(mPvback ,msetP);
   	  PVout=PIDprocess(&myServo,delta);
   	  PrintPID_PV_Out(&myServo,PVout);
   	  
   	  time++;
   	  sleep(0.1);
   	}
   
   	return 0;
 }
