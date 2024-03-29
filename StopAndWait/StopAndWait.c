//StopAndWait

#include<stdlib.h>
#include<stdio.h>

struct frame
{
    int info;
    int seq;
};
int ak;
int t=5,k;
int disconnect=0;
struct frame p;
char turn='s';//initialize first turn as sender
int errorframe=1;//no error
int errorack=1;

void sender();
void receiver();
void main()
{
    p.info=0;//datat part
    p.seq=0;//sequence number
    while(!disconnect)
    {
        sender();//call sender
        for(k=1;k<=10000000;k++);
        //after a finite amount of time call receiver
        receiver();
    }
}

void sender()
{
    static int flag=0;
        if(turn='s')//sender turn
        {
            if(errorack==0)//Ack didn't arrive
            {
                printf("SENDER : sent packet with seq NO : %d \n",p.seq);
                errorframe=rand()%4;
                //randomly pick Error frame as 4

                printf("%s\n",(errorframe==0?"Error While sending packet":""));
                turn='r';
            }
            else{
                if(flag==1)
                    printf("SENDER: Received ACK for packet %d\n",ak);
                if(p.seq==5){
                    disconnect=1;
                    return;
                }
                p.info=p.info+1;
                p.seq=p.seq+1;
                printf("SENDER: sent packet with seq NO:%d\n",p.seq);
                errorframe=rand()%4;
                //Message below is printed only if Error occured while sending packet
                printf("%s\n",(errorframe==0?"Error While sending packet":""));
                turn='r';
                //Set next turn as Receiver for transmission
                flag=1;
            }
        }
        else
        {
            t--;
            printf("SENDER time reduncing\n");
            if(t==0)
            {
                turn='s';
                errorack=0;
                t=5;
            }
        }
}

void receiver()
{
    static int frexp=1;
    if(turn=='r')
    {
        if(errorframe!=0)
        {
            if(p.seq==frexp)
            //if frame sequence number is eq  to frexp
        {
            printf("RECEIVER: Received packet with seq %d\n",p.seq);
            //note sequence number of frame arrived to end acknowledgment
            ak=p.seq;
            //increment the frame sequence number
            frexp=frexp+1;
            //set next turn as sender
            turn='s';
            //send acknowledgement error for frame number 4
            errorack=rand()%4;
            printf("%s\n",(errorack==0?"Error While sending acknowledgement":""));
        }
        else
        {
            //Receiver received Duplicated frame for lost frame after Resending
            printf("RECEIVER: Duplicated packet with seq %d\n",frexp-1);
            //Note down acknowledgement number of frame
            ak=frexp-1;
            //next turn sender
            turn='s';
            errorack=rand()%4;
        }
        }
    }
}
