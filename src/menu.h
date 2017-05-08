#include <stdlib.h>                                                             
#include <stdio.h>                                                              
#include <vector>                                                               
#include <stdexcept>                                                            
#include <iostream>                                                             
#include <string>   
#include "multik.h" 
#include "new_step.h"     
#include "new_information.h"   
#include <fstream>   

using namespace std;                                                            
                                                                                 
#define cube(x,y,z,t) cube[(x)*(N)*(N)+(y)*(N)+z*(bact+substance)+t]    
int menu(int argc,char *argv[],int *cube,all_instruction instruction,int razm,
        int bact,int substance,int N, string* all_bact_and_subst)
{
  while(1)
    {
        cout<<"MENU\n 1- new_step\n 2- n new_step \n 3- watch section \n 4- watch information about cube \n 5- multik\n 6- exit \n"<<endl;
        char c;
        cin>>c;
        int steps;
        int number_of_section;
        int section;
        int number_cell;
        switch(c)
        {
            case '1':
                  new_now_step(instruction,razm,bact,substance,&cube,all_bact_and_subst);
                  cout<<"Complite!\n";
                break;
            case '2':
                cout<<"you want steps:"<<endl;
                cin>>steps;
                for(int i=0;i!=steps;i++)
                  new_now_step(instruction,razm,bact,substance,&cube,all_bact_and_subst);
                cout<<"Complite!\n";
                break;
            case '3':
                cout<<"you want watch section:\n x- 0 \n y- 1\n z- 2\n";
                cin>>section;
                if(section<0||section>2){
                    cout<<"not correctly\n";
                    break;
                }
                cout<<"you want number section (max "<<razm<<"):\n";
                cin>>number_of_section;
                if(number_of_section<0||number_of_section>=razm){
                    break;
                }
                cout<<"number of cell or substance:\n";
                cin>>number_cell;
                if(number_cell<0||number_cell>=bact+substance){
                    cout<<"not correctly\n";
                    break;
                }
                new_information(section,number_of_section,number_cell,razm,cube,bact,substance);
                break;
            case '4':
                instruction.print_instraction();
                information(all_bact_and_subst,razm,bact,substance,cube); 
                break;
            case '5':
                cout<<"you want watch:"<<endl;
                for(int i=0;i!=bact+substance;i++)
                    cout<<i<<"-"<<all_bact_and_subst[i];
                int number_of_bact_or_subst;
                cin>>number_of_bact_or_subst;
                if(number_of_bact_or_subst<0||number_of_bact_or_subst>bact+substance){
                    cout<<"not correctly"<<endl;
                    break;
                    }
                int start_x,start_y,start_z,end_x,end_y,end_z;
                cout<<"start_x:"; cin>>start_x;
                cout<<"start_y:"; cin>>start_y;
                cout<<"start_z:"; cin>>start_z;

                cout<<"end_x:"; cin>>end_x;
                cout<<"end_y:"; cin>>end_y;
                cout<<"end_z:"; cin>>end_z;
    
                if(start_x>=razm||start_y>=razm||start_z>=razm||end_x<start_x||end_y<start_y||end_z<start_z||end_x>=razm||end_y>=razm||end_z>=razm){
                    cout<<"not correctly"<<endl;
                    break;
                    }

                multik(argc,argv,start_x,end_x,start_y,end_y,start_z,end_z,cube,number_of_bact_or_subst,N,bact,substance);
                break;
            case '6':
                delete [] cube;
                instruction.all_free();
                return 0;
        }
    }
}
