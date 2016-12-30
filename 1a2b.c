#include <stdio.h>
#include <stdlib.h>
#include <time.h>
int gues[5040][6]; //1表示有可能 0表示不可能  第6個是拿來存那個數對於其他剩餘數字的分類(幾a幾b)平均程度 
int remain=5040;//剩餘的可能數 
void initialize(void);//初始化可能的答案 
void delet(int,int,int,int,int,int);//對number 做可能性刪除
int input(int,int,int,int);
int classifaction(int,int);//看是類別 
int classify[14]={0};//每個可能數對其他可能數做分類  有14種 0a0b~0a4b 並且存下數量 
int a,b;
int judge(int,int,int,int,int,int,int,int,int,int);//判斷2個組數字並且回傳幾a幾b 
int answer[4];
void segmentation(int);
int main() 
{   
    int style;
    printf("Choose the mode (1)Revealing/(2)Guessing:");
    scanf("%d",&style);
    initialize(); 
	int firstnumber,gues_number;
	srand(time(NULL));
	firstnumber=(rand() % 5040);
	if(style==2)
	{   int i,j,k;
		gues_number=firstnumber;
		printf("%d%d%d%d\n",gues[gues_number][0],gues[gues_number][1],gues[gues_number][2],gues[gues_number][3]);
		while(input(gues[gues_number][0],gues[gues_number][1],gues[gues_number][2],gues[gues_number][3])!=1)
		{   int a,b;
			if(remain==0)
			{
				printf("You cheater!\n");
				break;
			}
			int min=0,location,flag=0;
			for(i=0;i<5040;i++)
			{   
				if(gues[i][4]==1)
				{   float avg=0,sum=0;
					for(j=0;j<5040;j++)
					{
						if(gues[j][4]!=0)
						{
							if(judge(a,b,gues[i][0],gues[i][1],gues[i][2],gues[i][3],gues[j][0],gues[j][1],gues[j][2],gues[j][3])!=0);
							{
							int c;
							c=classifaction(a,b);
							classify[c]=classify[c]+1;
						   }
							
						}
					}
					for(k=0;k<14;k++)
					 {avg=avg+classify[k]; avg=avg/14;}
					for(k=0;k<14;k++)//計算標準差 
					{sum=sum+(classify[k]-avg)*(classify[k]-avg);}
					
					gues[i][5]=sum;//放入標準差 
					if(i==0)
					min=gues[i][5];
					if(min>=gues[i][5])
					{
					location=i;
					flag++;
				    }
				    
				}
			}
			if(flag==0)
			 location=0;
			gues_number=location;
			printf("%d%d%d%d\n",gues[gues_number][0],gues[gues_number][1],gues[gues_number][2],gues[gues_number][3]);
		}
    }
    else
    {   int mygues;
    	printf("The answer is %d%d%d%d\n",gues[firstnumber][0],gues[firstnumber][1],gues[firstnumber][2],gues[firstnumber][3]);
    	scanf("%d",&mygues);
    	segmentation(mygues);
    	while(judge(a,b,gues[firstnumber][0],gues[firstnumber][1],gues[firstnumber][2],gues[firstnumber][3],answer[0],answer[1],answer[2],answer[3])!=0)
    	{
    		printf("%dA%dB\n",a,b);
    		scanf("%d",&mygues);
    		segmentation(mygues);
		}
printf("4A0B");
	}

	char q;
    while(1)
    {
    	scanf("%c",&q);
    	if(q=='q')
    	break;
	}
	return 0;
}
void initialize()
{   
    int i,count=0;
	for( i=0 ; i<10000 ;i++)
    {  int n1=0,n2=0,n3=0,n4=0;
	  n1=(i/1000)%10;
	  n2=(i/100)%10;
	  n3=(i/10)%10;
	  n4=(i/1)%10;
	  if(n1!=n2&&n1!=n3&&n1!=n4&&n2!=n3&&n2!=n4&&n3!=n4)
	  {
	  	gues[count][0]=n1;
	  	gues[count][1]=n2;
	  	gues[count][2]=n3;
	  	gues[count][3]=n4;
	  	gues[count][4]=1;
	  	count=count+1; 
	  }
    }
    
}
void delet(int A,int B,int n1,int n2,int n3,int n4)
{   int i=0;
	while(i<5040)
	{
		if(gues[i][4]==1)
		{
			int acount=0,bcount=0,j;
			for(j=0;j<4;j++)
			{
				if(gues[i][j]==n1)
				{
					if(j==0)
					{
					  acount++;
					  
				    }
					else
						bcount++;
				}
				 if(gues[i][j]==n2)
				{
					if(j==1)
					{
						acount++;
					
				    }
					else
						bcount++;
				}
				if(gues[i][j]==n3)
				{
					if(j==2)
					{
						acount++;
						
				    }
					else
						bcount++;
				}
				if (gues[i][j]==n4)
				{
					if(j==3)
					{
				     	acount++;	
				    }
					else
						bcount++;
				}
			}
			if(acount!=A||bcount!=B)
			{
				gues[i][4]=0;
				remain=remain-1;
			}
		}
		i=i+1;
	}
}
int input(int n1,int n2,int n3,int n4)
{   int a,b,flag=0,i=0;
    char non1,non2;
	scanf("%d%c%d%c",&a,&non1,&b,&non2);
	if(a==4&&b==0) {printf("WIN!\n");flag=1;}
	else 
	{
	delet(a,b,n1,n2,n3,n4);
	} 
	return flag;
}
int judge(int n1,int n2,int answernumber1,int answernumber2,int answernumber3,int answernumber4,int answer1,int answer2,int answer3,int answer4)
{
	int acount=0,bcount=0,i,j;
	for(i=0;i<4;i++)
	{
		if(answer[i]==answernumber1)
		{
			if(i==0)
			acount++;
			else
			bcount++;
		}
		if(answer[i]==answernumber2)
		{
			if(i==1)
			acount++;
			else
			bcount++;
		}
		if(answer[i]==answernumber3)
		{
			if(i==2)
			acount++;
			else
			bcount++;
		}
		if(answer[i]==answernumber4)
		{
			if(i==3)
			acount++;
			else
			bcount++;
		}
		
		  
	}
	a=acount;
	b=bcount;
	if(acount==4&&bcount==0)
	return 0;
	else
	return 1;
}
void segmentation(int number)
{
	answer[0]=(number/1000)%10;
	answer[1]=(number/100)%10;
	answer[2]=(number/10)%10;
	answer[3]=(number/1)%10;
}
int classifaction(int a,int b)
{
	if(a==0&&b==0)
	return 0;
	else if(a==1&&b==0)
	return 1;
	else if(a==2&&b==0)
	return 2;
	else if(a==3&&b==0)
	return 3;
	else if(a==0&&b==1)
	return 4;
	else if(a==1&&b==1)
	return 5;
	else if(a==2&&b==1)
	return 6;
	else if(a==3&&b==1)
	return 7;
	else if(a==0&&b==1)
	return 8;
	else if(a==1&&b==2)
	return 9;
	else if(a==2&&b==2)
	return 10;
	else if(a==0&&b==3)
	return 11;
	else if(a==1&&b==3)
	return 12;
	else
	return 13;
}
