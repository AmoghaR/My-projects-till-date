/*
*****************CUSTOM SHELL**********************

Project By:
Amogha R 
1PE11CS010

**********************************************
*/


#include <stdio.h>
#include <fcntl.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>
#include<string.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<dirent.h>
#include<ustat.h>
#include<time.h>
#include<utime.h>
#include<grp.h>
#include<signal.h>


int getarguments(char inp[10],char *argv[50])
{
	char *ptr;
	int i=0;

	ptr=strtok(inp," ");       //break the input string into different strings based on delimiter- space

	while(ptr!=NULL)
	{
		argv[i++]=ptr;
		ptr=strtok(NULL," ");  // call strtok until the entire input string is broken
	}
	return i;
}
void mylink(char *argv[],int argc)
{	if(strcmp(argv[1],"-s")==0)
         		{  	if(!symlink(argv[2],argv[3]))                          //attempt to create soft link
                 			printf("soft link created successfully\n");
             			else
                			printf("error\n");

          		}
          		else if(argc==3)                                               //attempt to create hard link
			{	 if(!link(argv[1],argv[2]))
                    			printf("hard link created successfully\n");
                    		else
                   			printf("error\n");
			}
          		else
				printf("syntax error\n");

}




int mycopy(char *argv[],int argc)
{

	if(argc!=3)
		{
			printf("Insufficient args \n");
		}

	else
		{
			int fd,fd1,r;
			char buf[50],c;

     			fd=open(argv[1],0,0777); // opening the source file

			if(fd==-1)
				{
					printf("Source file missing  \n\n"); // source file missing
					return 1;
				}

				fd1=creat(argv[2],00777);    //  creating the file to copy

				while((r=read(fd,buf,1))>0)
					write(fd1,buf,1); // writing the contents to the file
				printf("File copied successfully\n");

		   }

	return 0;

}


void mydate(char *argv[], int argc)
{
	time_t t;
	time(&t);//built in function
	{
		printf("\n Date : %s\n",ctime(&t));
	}
	return 0;

}



void mytime(char *argv[], int argc)
{
	time_t t = time(NULL);
        struct tm tm = *localtime(&t);
	printf("Time: %d:%d:%d\n", tm.tm_hour, tm.tm_min, tm.tm_sec);   

}




int mycat(char *argv[],int argc)
{
	int i,fdesc,fdesc1,r;
	char buf[50];

	if(argc<2)
	{
		printf("Too few arguments");
		return 0;
	}

	else if(argc>2)
	{
		if(!strcmp(argv[1],">"))
		{
			fdesc=creat(argv[2],00777);  //attempt to obtain file descriptor
			while((r=read(0,buf,50))>0)
			write(fdesc,buf,r);
			return 0;
		}

		else if(!strcmp(argv[2],">"))
		{
			fdesc=open(argv[1],0,00777);
				if(fdesc==-1)
				{
					printf("%s:No such file or directory\n",argv[1]);
					return 0;
				}

			fdesc1=creat(argv[3],00777);  //attempt to obtain file descriptor
			while((r=read(fdesc,buf,50))>0)
			write(fdesc1,buf,r);

		return 0;
	       	}

		else if(!strcmp(argv[2],">>"))    //check for output redirection
		{
			fdesc=open(argv[1],O_RDWR);           // open both the files
			fdesc1=open(argv[3],O_RDWR|O_APPEND);

			if(fdesc==-1)
			{
				printf("error");
				return 1;
			}

			if(fdesc1==-1)
			fdesc=creat(argv[3],00777);     //output file if doesnt exist create one

			while((r=read(fdesc,buf,50))>0)
				write(fdesc1,buf,r);
				return 0;
		}

		else
		{
			for(i=1;i<argc;i++)
			{
				fdesc=open(argv[i],O_RDWR);
					if(fdesc==-1)
						printf("mycat:%s:No such file or directory!**!\n",argv[i]);
					else

					while((r=read(fdesc,buf,50))>0)
						write(1,buf,r);
			}
		}
	}

	else
	{
		fdesc=open(argv[1],0,O_RDWR);
			if(fdesc==-1)
				printf("%s:No such file or directory\n",argv[1]);
			else

			while((r=read(fdesc,buf,50))>0)
				write(1,buf,r);
	}

	return 0;
}

void mymkdir(char *argv[],int argc)
{
	if(argc!=2)
	{
		printf("Invalid number of arguments \n");
		return;
	}

	if(mkdir(argv[1],0777)==0)
		printf("Directory %s created! \n",argv[1]);
	else
		printf("Invalid path Or directory already exists \n");
}

void myrmdir(char *argv[],int argc)
{
	if(argc!=2)
	{
		printf("Invalid number of argv \n");
		return;
	}

	if(rmdir(argv[1])==0)
		printf("Directory %s successfully removed!\n",argv[1]);
	else
		printf("Invalid path / Directory is not empty \n");
}

int mychdir(char *argv[],int argc)
{
	

	if(argc!=2)
	{
		printf("invalid!!\n");
		exit(0);
	}

	if(access(argv[1],F_OK)==0)
	{
		if(!chdir(argv[1]));
		printf("directory changed\n");

		
	}

	else
	{
		perror("access");
}
	return 0;
}

void mymove(char *argv[],int argc)
{
	if(argc==3)
	{
		if(link(argv[1],argv[2])==0)
		{
			printf("%s has been copied to %s\n",argv[1],argv[2]);
			unlink(argv[1]);
		}
	}
	return 0;
}

void myrm(char *argv[],int argc)
{
	if(argc!=2)
	{	printf("Not enough argv\n");
		return ;
	}

			unlink(argv[1]);
			printf("File successfully deleted\n");


}

int mytouch(char *argv[],int argc)
{
	struct utimbuf times;
	if(argc!=2)
	{
		printf("usage error\n");
		exit(0);
	}
	if(access(argv[1],F_OK)==0)
	{
		times.actime=times.modtime=time(0);
	}
	else
	{
	creat(argv[1],S_IRWXU);
	times.actime=times.modtime=time(0);
	}
	if(utime(argv[1],&times))
	{
		printf("error\n");
	}
	return 0;
}

int myls(char *argv[],int argc)
{
	if(argc!=2)
	{
		printf("usage error: provide argument\n");
		exit(0);
	}
	DIR *dp;
	struct dirent *d;
	if(argc==2)
	{
		dp=opendir(argv[1]);
		{
			while((d=readdir(dp))!=NULL)
			printf("%s\t",d->d_name);
			printf("\n");
		}
	}	
	closedir(dp);
}


int mypwd(char *argv[],int argc)
{
	char buf[100];
	if(argc!=1)
	{
		printf("invalid number of arguments\n");
		exit(0);
	}
	else
	{
		getcwd(buf,sizeof(buf));
		printf("%s",buf);
	}
	return 0;
}

int myperm(char *argv[],int argc)
{
	int fd;
	if(argc!=2)
	{
		printf("Too few arguments");
		return;
	}
	else
	{
		if(access(argv[1],R_OK)==0)
		{
			printf("read permission exists\n");
		}
		if(access(argv[1],W_OK)==0)
		{
			printf("write permission exists\n");
		}
		if(access(argv[1],X_OK)==0)
		{
			printf("execute permission executes\n");
		}
		
	}
	return 0;
}

int myexit()
{
	exit(0);
}	



int mywc(char *argv[],int argc)
{
int character_count = 0;
           int space_count = 0;
           int word_count = 0;
           int line_count = 0;
           char ch;

           FILE *fp;
           fp = fopen(argv[1],"r");

           if(argc == 0)
           {
   printf("Please specify the filename as argument\n");
                      exit(0);
           }

           


           while((ch=fgetc(fp))!=EOF)
           {
                       character_count++;
                       if(ch == ' ')
                       {
                             space_count++;
                             word_count++;
                       }
                       if(ch == '\n')
                       {
                         line_count++;
                       }
           }
           printf("character_count = %d\n",character_count);
           printf("space_count = %d\n",space_count);
           printf("word_count = %d\n",word_count+1);
           printf("line_count = %d\n",line_count);

return 0;
}



void match_pattern(char *argv[])
{
    int fd,r,j=0;
    char temp,line[100];
    if((fd=open(argv[2],O_RDONLY)) != -1)
    {
        while((r=read(fd,&temp,sizeof(char)))!= 0)
        {
            if(temp!='\n')
            {
                line[j]=temp;
                j++;
            }
            else
            {
                if(strstr(line,argv[1])!=NULL)
                    printf("%s\n",line);
                memset(line,0,sizeof(line));
                j=0;
            }

        }
    }   
}

void mygrep(char *argv[],int argc)
{
    struct stat stt;
    if(argc==3)
    {
        if(stat(argv[2],&stt)==0)
            match_pattern(argv);
        else 
        {
            perror("stat()");
            exit(1);
        }
    }
}


int mykill(char **argv,int argc)
{
    if (argc < 2)
    {
        printf("usage: ./kill PID");
        return -1;
    }

    kill(atoi(argv[1]), SIGKILL);

    return 0;

}

int main()
{
	int argc,i;

printf("\n************************** My Shell ********************************\nProject By:\nAmogha R 1PE11CS010\n********************************************************************\n");
	printf("--------------------------------------------------------------------\n");
	printf("Existing Commands are : \n");
	printf("1.) pwd\t\t2.) cp\t\t3.) cat\t\t4.) mkdir\n\n");
	printf("5.) rmdir\t6.) env\t\t7.) uname\t8.) date\n\n");
	printf("9.) time\t10.) cd\t\t11.) mv\t\t12.) rm\n\n");
	printf("13.) touch\t14.) ln\t\t15.) ls\t\t16.) echo\n\n");
	printf("17.) perm\t18.) wc\t\t19.) chmod\t20.) env\n\n");
	printf("Type \"exit\" to exit this shell.\n");
	printf("_____________________________________________________________________\n");
	printf("Enter the desired commands below :\n\n");

	char input[10],*argv[50];
	do               //repeated execution of commands
	{
		
		printf(" amogha@ubuntu");
		printf(get_current_dir_name()); // print the current directory name
		printf(" $ ");
		gets(input);                    //get the input


		argc=getarguments(input,argv);
		if(strcmp(argv[0],"link")==0)           //checking for command entered 
			mylink(argv,argc);
		else if(strcmp(argv[0],"copy")==0)
			mycopy(argv,argc);
		else if(strcmp(argv[0],"date")==0)
			mydate(argv,argc);
		else if(strcmp(argv[0],"time")==0)
			mytime(argv,argc);
		else if(strcmp(argv[0],"cat")==0)
			mycat(argv,argc);
		else if(strcmp(argv[0],"mkdir")==0)
			mymkdir(argv,argc);
		else if(strcmp(argv[0],"rmdir")==0)
			myrmdir(argv,argc);
		else if(strcmp(argv[0],"chdir")==0)
			mychdir(argv,argc);
		else if(strcmp(argv[0],"move")==0)
			mymove(argv,argc);
		else if(strcmp(argv[0],"rm")==0)
			myrm(argv,argc);
		else if(strcmp(argv[0],"touch")==0)
			mytouch(argv,argc);
		else if(strcmp(argv[0],"ls")==0)
			myls(argv,argc);
		else if(strcmp(argv[0],"pwd")==0)
			mypwd(argv,argc);
		else if(strcmp(argv[0],"perm")==0)
			myperm(argv,argc);
		else if(strcmp(argv[0],"exit")==0)
	                myexit();
		else if(strcmp(argv[0],"wc")==0)
			mywc(argv,argc);
		else if(strcmp(argv[0],"grep")==0)
			mygrep(argv,argc);
		else if(strcmp(argv[0],"kill")==0)
			mykill(argv,argc);
		else printf("Sorry command not found\n");
		


	}while(1);

	return 0;
}

