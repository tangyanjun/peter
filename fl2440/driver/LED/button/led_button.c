#include <stdio.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <unistd.h>
#include <linux/fb.h>
#include <sys/mman.h>


#define KEY1 0x01
#define KEY2 0x02
#define KEY3 0x04
#define KEY4 0x08
#define PLATDRV_MAGIC   0x60
#define OFF _IO (PLATDRV_MAGIC,0x18)
#define ON _IO (PLATDRV_MAGIC,0X19)
#if 0
int  fork_1()
{    
     int pid = 0;
     pid = fork();      
     if(pid < 0)
     {
         printf("failed to fork!\n");
         return 1;
     }
     if(pid > 0)
     {
         wait(NULL);
     }

     else
     {
         execl("/bin/cp", "cp", "dev/fb0", "qwe", NULL);
     }
     return 0;
}

int fork_2()
{
    int pid = 0;
    pid = fork();
    if(pid < 0)
    {
         printf("failed to fork!\n");
         return 1;
    }

    if(pid > 0)
    {
         wait(NULL);
    }

    else
    {
         execl("/bin/tftp","tftp", "-p", "-r", "qwe", "192.168.1.8", NULL);
    }
    return 0;   
}
#endif

int main (int argc, char **argv)
{
    int button_fd;
    int led_fd;
    int ret_button;
    int current_button;
	int i=1;
	int j=1;
	int x=1;
	int y=1;
       

    button_fd = open("/dev/button", 0);
    
    

    if (button_fd < 0)
    {
        printf("open button failed.\n");
        exit(1);
    }
	
	while (1)
    {
        ret_button = read(button_fd, &current_button, sizeof(4));
        if (ret_button != sizeof(current_button))
        {
            printf("Read() button failed.\n");
        }
		
		else
		{
		    if (current_button == KEY1)
			{ 
                led_fd = open("/dev/led0",O_RDWR,755);
		        
                
                switch (i%2)
                {
                     case 0:
                          ioctl(led_fd, OFF, 0);
                          i++;
                          printf("Turn led0 OFF.\n");
                          break;

                     case 1:
                          ioctl(led_fd, ON, 0);
                          i++;
                          printf("Turn led0 ON.\n"); 
                          break;
				}
				
			}
			
			else if (current_button == KEY2)
			{
                   
                led_fd = open("/dev/led1",O_RDWR,755);
			    switch (j%2)
                {
                     case 0:
                          ioctl(led_fd, OFF, 1);
                          j++;
                          printf("Turn led1 OFF.\n");
                          break;
                     case 1:
                          ioctl(led_fd, ON, 1);
                          j++;
                          printf("Turn led1 ON.\n");
                          break;
				}
			}
			
			else if (current_button == KEY3)
			{
                led_fd = open("/dev/led2",O_RDWR,755);
			    switch (x%2)
                {
                     case 0:
                          ioctl(led_fd, OFF, 2);
                          x++;
                          printf("Turn led2 OFF.\n");
                          break;
                     case 1:
                          ioctl(led_fd, ON, 2);
                          x++;
                          printf("Turn led2 ON.\n");
                          break;
				}
				
			}
		    
		    else if (current_button == KEY4)
			{
                led_fd = open("/dev/led3",O_RDWR,755);
			    switch (y%2)
                {
                     case 0:
                          ioctl(led_fd, OFF, 3);
                          y++;
                          printf("Turn led3 OFF.\n");
                          break;
                     case 1:
                          ioctl(led_fd, ON, 3);
                          y++;
                          printf("Turn led3 ON.\n");
                          break;
				}
				
			}
	    }	
	
		
	
	}
	ioctl(led_fd,OFF);
    close(led_fd);
    close(button_fd);
	return 0;
}
