#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <vector>
#include <algorithm>
//#include "parser.h"
#include "instruction.h"

#define Max_radius 20
#define cube(x,y,z,t) cube[(x)*(N)*(N)+(y)*(N)+z*(bact+substance)+t]
#define new_cube(x,y,z,t) new_cube[(x)*(N)*(N)+(y)*(N)+z*(bact+substance)+t]
/*
bool true_condition(char* condit,int quantity_first_bact,int quantity_first_cof,
        int quantity_secon_bact,int quantity_secon_cof,int now_quantity)
{
    char formul[80];
    int i=2;
    for(;condit[i]!='\0';i++)
       formul[i-2]=condit[i];
    formul[i-2]='\0';
    int result_quantity=result_function(
         formul,
         quantity_first_bact,
         quantity_first_cof,
         quantity_secon_bact,
         quantity_secon_cof,
         now_quantity);
    if(condit[0]=='W'&&condit[1]=='<')
        if(now_quantity<result_quantity)
            return true;
    if(condit[0]=='W'&&condit[1]=='=')
        if(now_quantity==result_quantity)
            return true;
    if(condit[0]=='W'&&condit[1]=='>')
        if(now_quantity>result_quantity)
            return true;
    if(condit[0]=='A'&&condit[1]=='<')
        if(quantity_first_bact<result_quantity)
            return true;
    if(condit[0]=='A'&&condit[1]=='=')
        if(quantity_first_bact==result_quantity)
            return true;
    if(condit[0]=='A'&&condit[1]=='>')
        if(quantity_first_bact>result_quantity)
            return true;
    if(condit[0]=='B'&&condit[1]=='<')
        if(quantity_secon_bact<result_quantity)
            return true;
    if(condit[0]=='B'&&condit[1]=='=')
        if(quantity_secon_bact==result_quantity)
            return true;
    if(condit[0]=='B'&&condit[1]=='>')
        if(quantity_secon_bact>result_quantity)
            return true;
    return false;
}
*/
std::string watch(int * cube,int start_x,int start_y,int start_z,int razm,int N, int radius,int substance,int bact,std::string* all_bact_and_subst)
{
    std::vector<int> vector_of_number;
    std::string all_reagents;
    for(int x=start_x-radius;x<=start_x+radius;x++){
        if(x==razm) break;
        if(x<0) continue;
        for(int y=start_y-radius;y<=start_y+radius;y++){
            if(y==razm)break;
            if(y<0) continue;
            for(int z=start_z-radius;z<=start_z+radius;z++){
                if(z==razm)break;
                if(z<0)continue;
                for(int number=0; number!=substance+bact;number++)
                {
                    if(cube(x,y,z,number)>0)
                    {   
                        if(!vector_of_number.empty())
                        {
                            bool new_num=true;
                            for(std::vector<int>::iterator iter = vector_of_number.begin();iter!=vector_of_number.end();iter++)
                                if(*iter==number)
                                {
                                    new_num=false;
                                    break;
                                }
                            if(new_num)
                                vector_of_number.push_back(number);
                        }else
                            vector_of_number.push_back(number);
                    }
                }
            }
        }
    }
    std::sort(vector_of_number.begin(), vector_of_number.end());  
    for (std::vector <int>::iterator iter = vector_of_number.begin() ; iter != vector_of_number.end();iter++)
    {
        all_reagents +=all_bact_and_subst[*iter];
        all_reagents +=",";
    }
    return all_reagents;
}

int this_relation(all_instruction instruction,int x,int y,int z,int razm,int N,int bact,int substance,int* cube,int* new_cube,std::string* all_bact_and_subst)
{
    for(int radius=1;radius!=Max_radius;radius++)////осторожно хардкод
    {
        std::string have_reagents=watch(cube,x,y,z,razm,N,radius,substance,bact,all_bact_and_subst);
        std::cout<<have_reagents<<"now in this relat"<<std::endl;
        if(instruction.this_maybe_line(new_cube,cube,x,y,z,razm,bact,substance,radius,have_reagents,all_bact_and_subst)==1)
            return 1;
    }
    std::cout<<"WHAT????MAX RADIUS REALY????"<<std::endl;
    return 1;//ИЛИ ЧТО ТО ДЕЛАТЬ????
}

int new_now_step(all_instruction instruction,int razm,int bact,int substance,int ** cube,std::string* all_bact_and_subst)
{
    int N=razm*(bact+substance);
    int *new_cube=new int[(N*N*N)]; 

    for(int x=0;x!=razm;x++)                                                            
         for(int y=0;y!=razm;y++)                                                
             for(int z=0;z!=razm;z++){                                           
                 for(int t=0;t!=bact+substance;t++)                              
                    new_cube(x,y,z,t)=0;                                         
                 }     

    for(int x=0;x!=razm;x++)
     for(int y=0;y!=razm;y++)
      for(int z=0;z!=razm;z++)
      {      
        if(this_relation(instruction,x,y,z,razm,N,bact,substance,*cube,new_cube,all_bact_and_subst)==-1)
            return -1;
      } 
    //что делать с теми кто не реагировал? сейчас уничтожаются
    delete [] (*cube);
    (*cube)=new_cube;

/*    for(int x=0;x!=razm;x++)                                                            
         for(int y=0;y!=razm;y++)                                                
             for(int z=0;z!=razm;z++){                                           
                 for(int t=0;t!=bact+substance;t++)                              
                    std::cout<<((*cube)(x,y,z,t))<<std::endl;                                         
                 std::cout<<std::endl;    
             }     
  */               

    return 1;
}
/*
void new_step(std::vector <std::vector<int>> &vector_of_name_first_cof,
        std::vector <std::vector<int>> &vector_of_first_cof,
        std::vector <std::vector<int>> &vector_of_name_sec_cof,
        std::vector <std::vector<int>> &vector_of_sec_cof,
        std::vector <std::vector<char*>> &vector_of_formul,
        std::vector <std::vector<int>> &vector_of_priority,
        std::vector <std::vector<char*>> &vector_of_condition,
        int razm,
        int bact,
        int substance,
        int* cube)
{
   int N=razm*(bact+substance);
   int x,y,z,t,i;
   int max_priority=1;
   for(x=0;x!=razm;x++)
    for(y=0;y!=razm;y++)
     for(z=0;z!=razm;z++)
      for(int priority=0;priority<=max_priority;priority++)
        {
            std::vector<int> vector_with_bact;
            for(int now_bact=0;now_bact!=bact+substance;now_bact++){
                //были изменения концентрации
                bool new_bact=false;
                for(int now_instructions=0;now_instructions!=
                       vector_of_priority[now_bact].size();now_instructions++)
                {
                   if(max_priority<vector_of_priority[now_bact].size())
                       max_priority=vector_of_priority[now_bact].size();
                   if(vector_of_priority[now_bact][now_instructions]==priority)
                   {
                     int now_first_cof_F=
                     vector_of_first_cof[now_bact][now_instructions];
                     int quantity_first_bact_A= 
                     cube(x,y,z,vector_of_name_first_cof[now_bact][now_instructions]);
                     int now_second_cof_S=
                     vector_of_sec_cof[now_bact][now_instructions];
                     int quantity_secon_bact_B=
                     cube(x,y,z,vector_of_name_sec_cof[now_bact][now_instructions]);
                     if (now_first_cof_F<0)
                         now_first_cof_F=0;
                     if(now_second_cof_S<0)
                         now_second_cof_S=0;
                     if(quantity_first_bact_A<0)
                         quantity_first_bact_A=0;
                     if(quantity_secon_bact_B<0)
                         quantity_secon_bact_B=0;
                     if(true_condition(vector_of_condition[now_bact][now_instructions],
                             quantity_first_bact_A,
                             now_first_cof_F,
                             quantity_secon_bact_B,
                             now_second_cof_S,
                             cube(x,y,z,now_bact)))
                     {
                        int result_quantity_bact=result_function(
                        vector_of_formul[now_bact][now_instructions],
                        quantity_first_bact_A,
                        now_first_cof_F,
                        quantity_secon_bact_B,
                        now_second_cof_S,
                        cube(x,y,z,now_bact));
                        if(result_quantity_bact<0)
                            result_quantity_bact=0;
                        vector_with_bact.push_back(result_quantity_bact);
*   printf("WE HAVE - %d , %d .%d .%d , %s ,%d \n",vector_of_first_cof[now_bact][now_instructions],vector_of_name_first_cof[now_bact][now_instructions],
           vector_of_sec_cof[now_bact][now_instructions],vector_of_name_sec_cof[now_bact][now_instructions],vector_of_formul[now_bact][now_instructions],vector_of_priority[now_bact][now_instructions]); 

 printf("WE HAVE - %s  %d , %d .%d .%d , %d \n", vector_of_formul[now_bact][now_instructions],
                     cube(x,y,z,vector_of_name_first_cof[now_bact][now_instructions]),
                     vector_of_first_cof[now_bact][now_instructions],
                     cube(x,y,z,vector_of_name_sec_cof[now_bact][now_instructions]),
                     vector_of_sec_cof[now_bact][now_instructions],
                     cube(x,y,z,now_bact));


                        printf("AND NOW: %d\n",result_quantity_bact);/
                        new_bact=true;
                     }
                     break;
                   }
               }
                if(!new_bact)
                    vector_with_bact.push_back(cube(x,y,z,now_bact));
        
            }
            for(int now_bact=0;now_bact!=bact+substance;now_bact++){
                int now_quantity = vector_with_bact[now_bact];
                cube(x,y,z,now_bact)=now_quantity;
            }
        }
}

void run(std::vector<int>vector_run,int bact,int substance,int razm,int*cube)
{
    int x,y,z;
    int N=razm*(bact+substance);
    //в зависимости от направления изменяется "движение в массиве"
    if(vector_run[0]==0)
        for(x=0;x!=razm;x++)
         for(y=0;y!=razm;y++){
            std::vector<int>new_subst_arrived;
            new_subst_arrived.resize(substance);   
            for(z=0;z!=razm-1;z++){
                for(int subst=bact;subst<=substance+bact-1;subst++)
                {
                    //сколько пит.среды ушло, столько прийдёт в сосед. клетку
                    int subst_run=cube(x,y,z,subst)*vector_run[1]/100;
                    cube(x,y,z,subst)=cube(x,y,z,subst)-subst_run+new_subst_arrived[subst-bact];
                    new_subst_arrived[subst-bact]=subst_run;
                }
            }
            //от крайней клетки ничто никуда не перетикает
            z=razm-1;
            for(int subst=bact;subst<=substance+bact-1;subst++)
                cube(x,y,z,subst)+=new_subst_arrived[subst-bact];
         }
    
    if(vector_run[0]==1)
        for(x=0;x!=razm;x++)
         for(y=0;y!=razm;y++){
            std::vector<int>new_subst_arrived;
            new_subst_arrived.resize(substance);   
            for(z=razm-1;z!=0;z--){
                for(int subst=bact;subst<=substance+bact-1;subst++)
                {
                    int subst_run=cube(x,y,z,subst)*vector_run[1]/100;
                    cube(x,y,z,subst)=cube(x,y,z,subst)-subst_run+new_subst_arrived[subst-bact];
                    new_subst_arrived[subst-bact]=subst_run;
                }
            }
            z=0;
            for(int subst=bact;subst<=substance+bact-1;subst++)
                cube(x,y,z,subst)+=new_subst_arrived[subst-bact];
         }
  
    if(vector_run[0]==2)
        for(x=0;x!=razm;x++)
         for(z=0;z!=razm;z++){
            std::vector<int>new_subst_arrived;
            new_subst_arrived.resize(substance);   
            for(y=0;y!=razm-1;y++){
                for(int subst=bact;subst<=substance+bact-1;subst++)
                {
                    int subst_run=cube(x,y,z,subst)*vector_run[1]/100;
                    cube(x,y,z,subst)=cube(x,y,z,subst)-subst_run+new_subst_arrived[subst-bact];
                    new_subst_arrived[subst-bact]=subst_run;
                }
            }
            y=razm-1;
            for(int subst=bact;subst<=substance+bact-1;subst++)
                cube(x,y,z,subst)+=new_subst_arrived[subst-bact];
         }
    
    if(vector_run[0]==3)
        for(x=0;x!=razm;x++)
         for(z=0;z!=razm;z++){
            std::vector<int>new_subst_arrived;
            new_subst_arrived.resize(substance);   
            for(y=razm-1;y!=0;y--){
                for(int subst=bact;subst<=substance+bact-1;subst++)
                {
                    int subst_run=cube(x,y,z,subst)*vector_run[1]/100;
                    cube(x,y,z,subst)=cube(x,y,z,subst)-subst_run+new_subst_arrived[subst-bact];
                    new_subst_arrived[subst-bact]=subst_run;
                }
            }
            y=0;
            for(int subst=bact;subst<=substance+bact-1;subst++)
                cube(x,y,z,subst)+=new_subst_arrived[subst-bact];
         }
    
    if(vector_run[0]==4)
        for(y=0;y!=razm;y++)
         for(z=0;z!=razm;z++){
            std::vector<int>new_subst_arrived;
            new_subst_arrived.resize(substance);   
            for(x=0;x!=razm-1;x++){
                for(int subst=bact;subst<=substance+bact-1;subst++)
                {
                    int subst_run=cube(x,y,z,subst)*vector_run[1]/100;
                    cube(x,y,z,subst)=cube(x,y,z,subst)-subst_run+new_subst_arrived[subst-bact];
                    new_subst_arrived[subst-bact]=subst_run;
                }
            }
            x=razm-1;
            for(int subst=bact;subst<=substance+bact-1;subst++)
                cube(x,y,z,subst)+=new_subst_arrived[subst-bact];
         }
    
    if(vector_run[0]==5)
        for(y=0;y!=razm;y++)
         for(z=0;z!=razm;z++){
            std::vector<int>new_subst_arrived;
            new_subst_arrived.resize(substance);   
            for(x=razm-1;x!=0;x--){
                for(int subst=bact;subst<=substance+bact-1;subst++)
                {
                    int subst_run=cube(x,y,z,subst)*vector_run[1]/100;
                    cube(x,y,z,subst)=cube(x,y,z,subst)-subst_run+new_subst_arrived[subst-bact];
                    new_subst_arrived[subst-bact]=subst_run;
                }
            }
            x=0;
            for(int subst=bact;subst<=substance+bact-1;subst++)
                cube(x,y,z,subst)+=new_subst_arrived[subst-bact];
         }
}
*/

