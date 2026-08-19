#include <stdio.h>
#include "the1.h"

void task1_assembly(void)
{
    int number;
    scanf("%d",&number);
    int R0=0,R1=0,R2=0,R3=0,R4=0,R5=0,R6=0,R7=0,R8=0;
    int registers[9]={R0,R1,R2,R3,R4,R5,R6,R7,R8};
    char letter;
    char S1[number+1],S2[number+1],C1[number+1],C2[number+1],I1[number+1],D1[number+1],J1[number+1],J2[number+1],J3[number+1],A1[number+1],A2[number+1];
    int a,b,c,d,e,f,g,h,k,m,n,v;
    char letters[number+1];
    int count=0;
    int i;
    for (i=1;i<=number;i++)
    {
        scanf(" %c", &letter);
        count+=1;
        letters[count]=letter;
        if (letter=='S')
        {
            scanf("%d %d",&a,&b);
            S1[i]=a;
            S2[i]=b;
            registers[a]=b;
        }
        else if (letter=='I')
        {
            scanf("%d",&c);
            I1[i]=c;
            registers[c]+=1;
        }
        else if (letter=='D')
        {
            scanf("%d",&d);
            D1[i]=d;
            registers[d]-=1;
        }
        else if (letter=='C')
        {
            scanf("%d %d",&e,&f);
            C1[i]=e;
            C2[i]=f;
            registers[e]=registers[f];
        }
        else if (letter=='A')
        {
            scanf("%d %d",&m,&n);
            A1[i]=m;
            A2[i]=n;
            registers[m]+=registers[n];
        }
        else if (letter=='J')
        {
            scanf("%d %d %d",&g,&h,&k);
            v=k;
            J1[i]=g;
            J2[i]=h;
            J3[i]=k;
            
            if (registers[g]>registers[h])
            {
                
            	while(k<=count)
            	{
            	    
            	    letter=letters[k];
                    if (letter=='S')
                    {
                    	
                        registers[S1[k]]=S2[k];
                    }
                    else if (letter=='I')
                    {
                        registers[I1[k]]+=1;
                    }
                    else if (letter=='D')
                    {
                        registers[D1[k]]-=1;
                    }
                    else if (letter=='C')
                    {
                        registers[C1[k]]=registers[C2[k]];
                    }
                    else if (letter=='A')
                    {
                        registers[A1[k]]+=registers[A2[k]];
                    }
                    else if (letter=='J' && registers[J1[k]]>registers[J2[k]] )
                    {
                    	k=v-1;
					}
					
					
                    k++;
            		
				}
	 	    }
        }
        
    }
    printf("R1: %d\nR2: %d\nR3: %d\nR4: %d\nR5: %d\nR6: %d\nR7: %d\nR8: %d\n",registers[1],registers[2],registers[3],registers[4],registers[5],registers[6],registers[7],registers[8]);
}

int ebob(int x,int y)
{
	if (y==0)
	{
		return x;
	}
	return ebob(y,x%y);
}
int helper(int land_length, int land_width, int plane_capacities[], int num_of_planes,int count)
{
	int i,count1,count2,count3,count4;
	if (land_length==0 || land_width==0)
	{
		return count;
	}
	for (i=0;i<num_of_planes;i++)
	{
	    if (land_length>=plane_capacities[i] && land_width>=plane_capacities[i])
	    {
	    	if (plane_capacities[i+1]==ebob(land_length,land_width) && plane_capacities[i]%plane_capacities[i+1]!=0)
            {
            	count=(land_length*land_width)/(plane_capacities[i+1]*plane_capacities[i+1]);
            	land_length=0;
            	land_width=0;
            	return helper(land_length,land_width,plane_capacities,num_of_planes,count);
            	
			}
	        else
	        {
	        	if (land_width<land_length)
	            {
	                count++;
	                count1=helper(land_length-plane_capacities[i],plane_capacities[i],plane_capacities,num_of_planes,count);
	                count2=helper(land_length,land_width-plane_capacities[i],plane_capacities,num_of_planes,count);
	                return count1+count2-count;
	            }
	            else if (land_width>=land_length)
	            {
	        	    count++;
	                count1=helper(plane_capacities[i],land_width-plane_capacities[i],plane_capacities,num_of_planes,count);
	                count2=helper(land_length-plane_capacities[i],land_width,plane_capacities,num_of_planes,count);
	                return count1+count2-count;
	   
                }
	        	
			}
            
            
	            
	    }
	    
	}
	
}
int calculate_planes(int land_length, int land_width, int plane_capacities[], int num_of_planes) 
{
    return helper(land_length,land_width,plane_capacities,num_of_planes,0);
}
void task2_planes(void)
{
	int i;
	int land_length,land_width,plane_capacities[5],num_of_planes;
	scanf("%d %d",&land_length,&land_width);
	scanf("%d",&num_of_planes);
	
	for (i=0;i<num_of_planes;i++)
	{
		scanf(" %d", &plane_capacities[i]);
	}
	printf("%d planes\n",calculate_planes(land_length,land_width,plane_capacities,num_of_planes));
}

int main(void) {
    /* DO NOT CHANGE main() FUNCTION IMPLEMENTATION */
    int task_id;
    
    scanf("%d", &task_id);
    
    switch(task_id) {
        case 1:
            task1_assembly();
            break;
        case 2:
            task2_planes();
            break;
        default:
            /* no op */
            break;
    }

    return 0;
    
}