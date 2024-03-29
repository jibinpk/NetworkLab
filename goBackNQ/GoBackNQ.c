//GoBackNQ

#include<stdio.h>
#include<time.h>
#include<stdlib.h>
int main()
{
    int nf,N;
    int tr=0;
    srand(time(NULL));
    printf("Enter the number of frames : ");
    scanf("%d",&nf);
    printf("Enter the window Size : ");
    scanf("%d",&N);
    int i =  1;
    while(i<=nf)
    {
        int x=0;
        for(int j=i;j<i+N && j<=nf;j++)
        {
            printf("Sent Frame %d 'n ",j);
            tr++;
            //After each freame is end , increment tr by 1
            //to track total number of transmissions
        }
        for(int j=i;j<i+N && j<=nf;j++)
        {
            int flag = rand()%2; //lost frame set as frame 2
            if(!flag){
                printf("%d: Acknowlegment! \n",j);
                x++;
                //After acknowledging frame,increment x indicating
                //success of frame transmission
            }
            else
            {
                printf("Frame %d Not Received \n",j);
                printf("Retransmitting Window \n");
                break;
            }
        }
        printf("\n");
        i+=x;
        //i updates number of successful
        //transfers -all acknowledged frames
    }
    printf("Total number of transmissions : %d \n",tr);
    return 0;
}
