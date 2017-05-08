#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <vector>
#include <algorithm>
#include "instruction.h"

#define Max_radius 20
#define cube(x,y,z,t) cube[(x)*(N)*(N)+(y)*(N)+z*(bact+substance)+t]
#define new_cube(x,y,z,t) new_cube[(x)*(N)*(N)+(y)*(N)+z*(bact+substance)+t]

//просмотр всех соседних клеток на наличее входных реагентов
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

//просмотр всех окресностей точки, до тех пора пока не найдётся правило
//удовлетворяющие условиям поиска
int this_relation(all_instruction instruction,int x,int y,int z,int razm,int N,int bact,int substance,int* cube,int* new_cube,std::string* all_bact_and_subst)
{
    for(int radius=1;radius!=Max_radius;radius++)////осторожно хардкод
    {
        std::string have_reagents=watch(cube,x,y,z,razm,N,radius,substance,bact,all_bact_and_subst);
        //std::cout<<have_reagents<<"now in this relat"<<std::endl;
        if(instruction.this_maybe_line(new_cube,cube,x,y,z,razm,bact,substance,radius,have_reagents,all_bact_and_subst)==1)
            return 1;
    }
    //std::cout<<"WHAT????MAX RADIUS REALY????"<<std::endl;
    return 1;//ИЛИ ЧТО ТО ДЕЛАТЬ????
}

//шаг моделирующий правила
int new_now_step(all_instruction instruction,int razm,int bact,int substance,int ** cube,std::string* all_bact_and_subst)
{
    int N=razm*(bact+substance);
    int *new_cube=new int[(N*N*N)]; 

    //создаётся новая матрица
    for(int x=0;x!=razm;x++)                                                            
         for(int y=0;y!=razm;y++)                                                
             for(int z=0;z!=razm;z++){                                           
                 for(int t=0;t!=bact+substance;t++)                              
                    new_cube(x,y,z,t)=0;                                         
                 }     
    
    //проверка всех точек, на основе случайного выбора точки пространства
    //таким образом некоторые клетки могут "сходить дважды" за ход, а некоторые
    //его "пропустить"
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

