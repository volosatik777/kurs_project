#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <vector>
#include "EasyBMP.h"
#include "string"
#include "iostream"

#define cube(x,y,z,t) cube[(x)*(N)*(N)+(y)*(N)+z*(bact+substance)+t]
/*
void list(struct cell *head)
{  
   struct cell *p;
   p=head;
   while (p!=NULL) 
   { 
      printf("  property: %s, with charact %d\n",p->property,p->charact);
      p=p->next; 
   }
}
*/
void new_information(int section,int number_section,int number_bact,int razm,int* cube,int bact,int substance)
{
int N=razm*(bact+substance);
BMP AnImage;
//максимальная концентрация объектов
int max_concentration=1;
AnImage.SetSize(razm,razm);

if(section==0){
 for(int y=0;y!=razm;y++)
     for(int z=0;z!=razm;z++)
     {
        if(cube(number_section,y,z,number_bact)>max_concentration)
            max_concentration=cube(number_section,y,z,number_bact);
     }
 for(int y=0;y!=razm;y++)
     for(int z=0;z!=razm;z++)
     {
        AnImage(y,z)->Red=255-255*cube(number_section,y,z,number_bact)/ max_concentration;
     }
}
if(section==1){
 for(int x=0;x!=razm;x++)
     for(int z=0;z!=razm;z++)
     {
        if(cube(x,number_section,z,number_bact)>max_concentration)
            max_concentration=cube(x,number_section,z,number_bact);
     }
 for(int x=0;x!=razm;x++)
     for(int z=0;z!=razm;z++)
     {
        AnImage(x,z)->Blue=255-255*cube(x,number_section,z,number_bact)/ max_concentration;
     }
}
if(section==2){
 for(int x=0;x!=razm;x++)
     for(int y=0;y!=razm;y++)
     {
        if(cube(x,y,number_section,number_bact)>max_concentration)
            max_concentration=cube(x,y,number_section,number_bact);
     }
 for(int x=0;x!=razm;x++)
     for(int y=0;y!=razm;y++)
     {
        AnImage(x,y)->Green=255-255*cube(x,y,number_section,number_bact)/ max_concentration;
     }
}
 AnImage.WriteToFile("Now.bmp");
}

void information(std::string *all_bact_and_substance,int razm,int bact,int substance,int*cube)
{
    int N=razm*(bact+substance);
    printf("we have cube: %d, with  %d  some bacteries and %d some substanse \n",razm,bact,substance);
    int x,y,z,t;
    for(x=0;x!=razm;x++)
        for(y=0;y!=razm;y++)
            for(z=0;z!=razm;z++){
                for(t=0;t!=bact+substance;t++)
                {
                    std::cout<<all_bact_and_substance[t];
                    printf("  have  quantity- %d with cord x=%d y=%d z=%d",cube(x,y,z,t),x,y,z);
                    printf("\n");
                }
                printf("\n");
                }
}   

