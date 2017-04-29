#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <vector>
#include <stdexcept>   
//#include "struct_cell.h"     
#include "new_information.h"
//#include "new_instruction.h"
#include "new_step.h"
//#include "tinyxml.h" 
#include <iostream>
#include <string>
#include <fstream>

using namespace std; 

#define cube(x,y,z,t) cube[(x)*(N)*(N)+(y)*(N)+z*(bact+substance)+t]
//#define new_cube(x,y,z,t) new_cube[(x)*(N)*(N)+(y)*(N)+z*(bact+substance)+t]
/*
bool max_sort (int a,int b) { return (a>b); }

struct now_relation
{
    std::string reagent;
//    std::string new_live_in;
//    std::string verteilung;
    std::string used;
    std::string formuls;
    now_relation *next;
};

struct now_name_of_relation
{
    std::string name;
    now_relation *relation;
    now_name_of_relation *next;
};

struct now_all_relation
{
    int radius;
    now_name_of_relation *name_of_relation;
    now_all_relation *next;
};

class all_instruction
{
    private:
        now_all_relation *all_relation;
    public:
    int read_new_instraction()
    {
        TiXmlDocument *instruction_file = new TiXmlDocument("rules.xml"); 
        if(!instruction_file->LoadFile()) 
           return -1;
        
        TiXmlElement *xml_all_relation = 0;
        xml_all_relation = instruction_file->FirstChildElement("all_relation");  
        
        TiXmlElement *xml_distantion = 0; 
        xml_distantion = xml_all_relation->FirstChildElement("distantion");

        all_relation = new now_all_relation();
        now_all_relation *now;
        now=all_relation;

        while(xml_distantion!=NULL)
        {
            const char *radius = xml_distantion->Attribute("radius");
            now->radius = atoi (radius);
            
            TiXmlElement *xml_relation = 0;
            xml_relation = xml_distantion->FirstChildElement("relation");
            
            now->name_of_relation = new now_name_of_relation();
            now_name_of_relation *now_name = now->name_of_relation;

            while(xml_relation!=NULL)
            {
                now_name->name = xml_relation->Attribute("name");

                TiXmlElement *xml_reagent = 0;                                     
                xml_reagent = xml_relation->FirstChildElement("reagent");
                
                now_name->relation = new now_relation;
                now_relation *now_relat = now_name->relation;

                while(xml_reagent!=NULL)
                {
                    now_relat->reagent= xml_reagent->Attribute("name");
//                    now_relat->new_live_in = xml_reagent->Attribute("new_live_in");  
                    now_relat->used = xml_reagent->Attribute("used");  
//                    now_relat->verteilung = xml_reagent->Attribute("new");  
                    now_relat->formuls = xml_reagent->Attribute("new");  

                    if((xml_reagent=xml_reagent->NextSiblingElement("reagent"))!=NULL)
                        {
                            now_relat->next= new now_relation();
                            now_relat=now_relat->next;
                        }
                }

                if ((xml_relation= xml_relation->NextSiblingElement("relation"))!=NULL)
                {
                    now_name->next = new now_name_of_relation();
                    now_name=now_name->next;
                }
            }
            
            if((xml_distantion = xml_distantion->NextSiblingElement("distantion"))!=NULL)
            {
                now->next = new now_all_relation();
                now=now->next;
            }
        }
        return 1;
    }
    void print_instraction()
    {
        now_all_relation *all_now=all_relation;
        while(all_now!=NULL)
        {
            cout<<all_now->radius<<endl;
            now_name_of_relation *name_now=all_now->name_of_relation;
            while(name_now!=NULL)
            {
                cout<<name_now->name<<endl;
                now_relation *now=name_now->relation;
                while(now!=NULL)
                {
                    cout<<now->reagent<<endl;
                    cout<<now->formuls<<endl;
                    cout<<now->used<<endl;
                    now=now->next;
                }
                name_now=name_now->next;
            }
            all_now=all_now->next;
        }
    }
//лучше юзать алгоритм евклида и во входных данных иеть вид 
// <reagent name="volk" used="20%" new="volk+ovc/volk*ox" new_live_in="ovc" raspred="max"/> 
//
*/
/*
    int min_used(std::vector<int>::iterator new_data,vector<float> kof, vector<int>::iterator data) 
    {
        for(vector<float>::iterator kof_iter=kof.begin();kof_iter!=kof.end();kof_iter++)
        {
            if((*data)*(*kof_iter)>*new_data)
               return -1;
            (*new_data)=(*data)*(*kof_iter);
            new_data++;
        }
        return 1;
    }

    vector<int> how_many_used (now_relation *now,vector<int> vector_with_data)
    {
        vector<float> kof;
        while((now->next)!=NULL){error
            kof.push_back(now->used);
            now=now->next;
        }
        for(std::vector<int>::iterator data = vector_with_data.begin();data!=vector_with_data.end();data++)
        {
            vector<int> vector_with_used_data=vector_with_data;
            vector<int>::iterator new_data =vector_with_used_data.begin();
            if(min_used(new_data,kof,data)==1)
                return vector_with_used_data;
        }
    }

    vector<int> how_many_data(vector<int>& vector_with_data,int * cube,int start_x,int start_y,int start_z,
            int razm,int bact,int substance,int radius,now_relation *this_relation,std::string* all_bact_and_subst)
    {
        int N=razm*(bact+substance);   
        now_relation *now=this_relation;
        vector <int>::iterator iter = vector_with_data.begin(); 
        for(int number=0; number!=substance+bact;number++)              
        {                                                               
            if(now->reagent==all_bact_and_subst[number])                         
            {                                      
                vector_with_data.push_back(0);
                for(int x=start_x-radius;x!=start_x+radius||x!=razm;x++){                   
                    if(x<0) continue;                                                       
                    for(int y=start_y-radius;y!=start_y+radius||y!=razm;y++){               
                        if(y<0) continue;                                                   
                        for(int z=start_z-radius;z!=start_z+radius||z!=razm;z++){           
                            if(z<0)continue;                                                
                            *iter+=cube(x,y,z,number);
                            cube(x,y,z,number)=0;
                        }                                                           
                    }                                                               
                }
                iter++;
                if((now=now->next)==NULL)
                    return how_many_used(this_relation,vector_with_data);
            }
        }
        cout<<"HMMMMM its not goood"<<endl;
        return how_many_used(now,vector_with_data);
    }                        
*/    
/*
 *  int delite old()
*/   
/*    int new_live(int how_many_reagent,int number_graph)
    {
        //засунуть что то нормальное из формул распределения
        return how_many_reagent*(0.3-0.05*number_graph);
    }


    //можно улучшить выбирая стартовые xyz
    int find_new_place(int* new_cube,int *cube,int start_x,int start_y,int start_z,int razm,int bact,int substance,int radius,
            int who_in_new_live,int new_live_because, string how_live,int how_many_new_reagent,int how_many_old_reagent)
    {
        int N=razm*(bact+substance);   
        vector<int>vector_new_live;
        vector<int>vec_x;
        vector<int>vec_y;
        vector<int>vec_z;
        for(int x=start_x-radius;x!=start_x+radius||x!=razm;x++){                   
            if(x<0) continue;                                                       
            for(int y=start_y-radius;y!=start_y+radius||y!=razm;y++){               
                if(y<0) continue;                                                   
                for(int z=start_z-radius;z!=start_z+radius||z!=razm;z++){           
                    if(z<0)continue;
                    vector_new_live.push_back(cube(x,y,z,new_live_because));
                    vec_x.push_back(x);
                    vec_y.push_back(y);
                    vec_z.push_back(z);
                }                                                           
            }                                                               
        }
        vector<int>xyz_live=vector_new_live;
        if(how_live=="min")
            sort(vector_new_live.begin(),vector_new_live.end());
        if(how_live=="max")
            sort(vector_new_live.begin(),vector_new_live.end(),max_sort);
        for(int number_graph=0;number_graph!=5;number_graph++)//ХАРДКООООД
          for(int iter=0;;iter++)
          {
                if(vector_new_live[number_graph]==xyz_live[iter])
                {
                    new_cube(vec_x[iter],vec_y[iter],vec_z[iter],who_in_new_live)=new_live(how_many_new_reagent,number_graph);
                    cube(vec_x[iter],vec_y[iter],vec_z[iter],who_in_new_live)=new_live(how_many_old_reagent,number_graph);
                }
          }
        return 1;
    }

    int new_raspred(int* new_cube,int *cube,int start_x,int start_y,int start_z,int razm,int bact,int substance,int radius,
            string str_live_because, string who,string how_live,string* all_bact_and_subst,int how_many_new_reagent,int how_many_old_reagent)
    {
      for(int live_because=0;live_because!=bact+substance;live_because++)
      {
        if(str_live_because==all_bact_and_subst[live_because]){
          for(int number_who=0;number_who!=bact+substance;number_who++)
            if(who==all_bact_and_subst[number_who])
              return(find_new_place(new_cube,cube,start_x,start_y,start_z,razm,bact,substance,radius,
                number_who,live_because,how_live,how_many_new_reagent,how_many_old_reagent));
        }
      }
*      //на случай no
 *      int i=0;
        while(who!=all_bact_and_subst[i]);
        find_new_place(i,"max")    
/  }
    
    int use_formuls (int *new_cube,int *cube,int start_x,int start_y,int start_z,int razm,int bact,int substance,int radius,
            string function,string live_because,string how_live,string who_change,vector<int> working_reagent,vector<int> all_reagent, string name_reagent,string* all_bact_and_subst)
    {
        int result=result_of_function(function,who_change,working_reagent);        
        new_raspred(new_cube,cube,start_x,start_y,start_z,razm,bact,substance,radius,
            live_because,name_reagent,how_live,all_bact_and_subst,result,how_many_old_reagent);
    }

    int work_with_data (int*new_cube,int*cube,int start_x,int start_y,int start_z,int razm,int bact,int substance,int radius,
            now_relation *now,string name_of_function,string *all_bact_and_subst)
    {
        vector<int> all_reagent;
        vector<int> working_reagent = how_many_data(all_reagent,cube,start_x,start_y,start_z,razm,bact,substance,radius,
                now,all_bact_and_subst);
        for(vector<int>::iterator number_reagent=all_reagent.begin();number_reagent!=all_reagent.end();number_reagent++)
        {
            use_formuls(new_cube,cube,start_x,start_y,start_z,razm,bact,substance,radius,
                    now->formuls,now->new_live_in,now->verteilung,name_of_function,working_reagent,all_reagent,now->reagent);
            now=now->next;
        }

    }
*/

/*
    int use_formuls (int *new_cube,int *cube,int start_x,int start_y,int start_z,int razm,int bact,int substance,int radius,
            string function,string live_because,string how_live,string who_change,vector<int> working_reagent,vector<int> all_reagent, string name_reagent,string* all_bact_and_subst)
    {
        int result=result_of_function(function,who_change,working_reagent);        
        new_raspred(new_cube,cube,start_x,start_y,start_z,razm,bact,substance,radius,
            live_because,name_reagent,how_live,all_bact_and_subst,result,how_many_old_reagent);
    }
*/
/*
    int work_with_data (int*new_cube,int*cube,int start_x,int start_y,int start_z,int razm,int bact,int substance,int radius,
            now_relation *now,string name_of_function,string *all_bact_and_subst)
    {
        while(now!=NULL)
        {
//            result_of_function(); 
            now=now->next;
        }
    }

    int this_reagent(std::string name,std::string have_reagents)
    {
        int found=0;
        int pos=0;
        found=name.find(",",pos);
        while(found!=std::string::npos)
        {
            int found2=0;
            int pos2=0;
            found2=have_reagents.find(",",pos2);
           
            while(have_reagents.substr(pos2, found2-pos2)!=name.substr(pos, found-pos))
            {
                pos2=found2+1;
                found2=have_reagents.find(",",pos2);
                if(found2==std::string::npos)
                    return -1;
            }
            pos=found+1;
            found=name.find(",",pos);
        }
        return 1;
    }

    int this_maybe_line(int*new_cube,int*cube,int start_x,int start_y,int start_z,int razm,int bact,int substance,
            int now_radius,std::string have_reagents,string *all_bact_and_subst)
    {
        struct now_all_relation *now;
        now=all_relation;
        while(now->radius!=now_radius)
        {
            if(now->next==NULL)
                return -1;
            now=now->next;
        }
        struct now_name_of_relation *now_name;
        now_name=now->name_of_relation;

        while(this_reagent(now_name->name,have_reagents)==-1)
        {
            if(now_name->next==NULL)
                return -1;
            now_name=now_name->next;
        }
        return work_with_data(new_cube,cube,start_x,start_y,start_z,razm,bact,substance,now_radius,
                now_name->relation,now_name->name,all_bact_and_subst);//здесь закинуть функцию обработки в случае NULL
    }
};
*/ 
//void all_free(std::vector<std::vector<char*>>free_vector)
//{
//    for(int i=0;i!=bact+substance;i++)
//        for(int j=0;j!=free_vector[i].size();j++)
//            free(free_vector[i][j]);
//}

int main(int argc,char **argv)
{
    int razm,bact,substance;      
    int *cube;

    ifstream file_with_data("data.in");
//  FILE *file_with_data;
//	file_with_data=fopen("data.in","r");
	if(!file_with_data) {
		cout<<"Can not open 'data.in' "<<endl; exit(1);
	}
    
    file_with_data>>razm>>bact>>substance;

    //считываем информацию о кубе
    //int i=fscanf(file_with_data,"%d", &razm);
    /*if(razm=='#'){
         char c;
         while ((c = std::fgetc(file_with_data)) != '\0')
             if(c=='\n'){
                 printf("not right data.in\n");
                 return -1;
             }
         int i=fscanf(file_with_data,"%d", &razm);
    }
    
    i=fscanf(file_with_data,"%d%d", &bact,&substance);
    
    if(i<2) {
		printf("Wrong 'data.in'"); exit(2);
	}
*/
    printf("we have cube:%d, with  %d  some bacteries and %d some substanse \n",razm,bact,substance);

    std::string all_bact_and_subst[substance+bact];
    for(int j=0;j!=substance+bact;j++)
        file_with_data>>all_bact_and_subst[j];

    int N=razm*(bact+substance);

    //создаём куб
    //int *new_cube=new int(N*N*N);
    cube= new int[(N*N*N)];
    if(cube==NULL)
        return -1;

    for(int x=0;x!=razm;x++)
        for(int y=0;y!=razm;y++)
            for(int z=0;z!=razm;z++){
                for(int t=0;t!=bact+substance;t++)
                {
                    int type;
                    //fscanf(file_with_data,"%d",&type);
                    //if(type=='#'){
                      //  while ((type = std::fgetc(file_with_data)) != '\0')
                        //   if(type=='\n'){
                         //      printf("not right data.in\n");
                         //      return -1;
                        //   }
                    //    fscanf(file_with_data,"%d",&type);
                    //}
                    file_with_data>>type;
                    cube(x,y,z,t)=type;
                    //printf(" %d ",cube(x,y,z,t));
                }
                //printf("\n");
                }

    //fclose(file_with_data);
	file_with_data.close();
    /*открываем фаил с описанием бактерий и сред
    file_with_data=fopen("bacteria.in","r");
	if(file_with_data==NULL) {
		printf("Can not open 'bacteria.in' "); exit(1);
	}
    */
    all_instruction instruction;
    if(instruction.read_new_instraction()!=1)
    {
        printf("we havent conf file \n");
        return -1;
    }
    instruction.print_instraction();

    cout<<"end-instr"<<endl;
    //создаём списки свойств всех объектов
/*  struct cell *all_cell[bact+substance];    
    for(i=0;i!=bact+substance;i++)
    {
        all_cell[i]= create(file_with_data,all_cell[i]);
        list(all_cell[i]);
    }
    fclose(file_with_data);

    //вектора для считывания с фаила.
    std::vector<std::vector<int>> vector_of_first_cof;
    std::vector<std::vector<int>> vector_of_name_first_cof;
    std::vector<std::vector<int>> vector_of_sec_cof;
    std::vector<std::vector<int>> vector_of_name_sec_cof;
    std::vector<std::vector<int>> vector_of_priority;
    std::vector<std::vector<char*>> vector_of_formul;
    std::vector<std::vector<char*>> vector_of_condition;

    vector_of_first_cof.resize(bact+substance);
    vector_of_name_first_cof.resize(bact+substance);
    vector_of_sec_cof.resize(bact+substance);
    vector_of_name_sec_cof.resize(bact+substance);
    vector_of_priority.resize(bact+substance);
    vector_of_formul.resize(bact+substance);
    vector_of_condition.resize(bact+substance);

    //записываем новые инструкции
    new_information_for_work(
         vector_of_first_cof,
         vector_of_name_first_cof,
         vector_of_sec_cof,
         vector_of_name_sec_cof,
         vector_of_priority,
         vector_of_formul,
         vector_of_condition,
         bact,
         substance,
         cube,
         all_cell);
 
    //веутор направления потока изначально 0-ой
    std::vector<int>vector_run;
    vector_run.resize(2);
*/    
    while(1)
    {
        printf("MENU\n 1- new_step\n 2- n new_step \n 3- watch section \n");
        printf(" 4- watch information about cube \n 5- new vector of flow substance\n");
        printf(" 6- new_instruction \n 7-exit \n");
        char c=getchar();
        int steps;
        int number_of_section;
        int section;
        int number_cell;
        switch(c)
        {
            case '1':
                  new_now_step(instruction,razm,bact,substance,&cube,all_bact_and_subst);
//                new_step(vector_of_name_first_cof,vector_of_first_cof,vector_of_name_sec_cof,
//                   vector_of_sec_cof,vector_of_formul,vector_of_priority,vector_of_condition,razm,bact,substance,cube);
//                if(substance>0)
//                    run(vector_run,bact,substance,razm,cube);
                  printf("Complite!\n");
                break;
            case '2':
                cout<<"you want steps:"<<endl;
                cin>>steps;
                for(int i=0;i!=steps;i++)
                  new_now_step(instruction,razm,bact,substance,&cube,all_bact_and_subst);
//                   new_step(vector_of_name_first_cof,vector_of_first_cof,vector_of_name_sec_cof,
//                    vector_of_sec_cof,vector_of_formul,vector_of_priority,vector_of_condition,razm,bact,substance,cube);
//                   if(substance>0)
//                       run(vector_run,bact,substance,razm,cube);
                //}
                printf("Complite!\n");
                break;
            case '3':
                printf("you want watch section:\n x- 0 \n y- 1\n z- 2\n");
                scanf("%d",&section);
                if(section<0||section>2){
                    printf("not correctly\n");
                    break;
                }
                printf("you want number section (max %d):\n",razm);
                scanf("%d",&number_of_section);
                if(number_of_section<0||number_of_section>=razm){
                    printf("not correctly\n");
                    break;
                }
                printf("number of cell or substance:\n");
                scanf("%d",&number_cell);
                if(number_cell<0||number_cell>=bact+substance){
                    printf("not true\n");
                    break;
                }
                new_information(section,number_of_section,number_cell,razm,cube,bact,substance);
                break;
            case '4':
                instruction.print_instraction();
                information(all_bact_and_subst,razm,bact,substance,cube); 
                break;
            case '5':
  //             vector_run=new_vector_run();
  //              printf("%d %d",vector_run[0],vector_run[1]);
                break;
            case '6':
   /*             new_information_for_work(
                    vector_of_first_cof,
                    vector_of_name_first_cof,
                    vector_of_sec_cof,
                    vector_of_name_sec_cof,
                    vector_of_priority,
                    vector_of_formul,
                    vector_of_condition,
                    bact,
                    substance,
                    cube,
                    all_cell);
                break;
   */         case '7':
                delete [] cube;
                instruction.all_free();
   //             free(cube);
                //all_free(vector_of_formul);
                //all_free(vector_of_condition);
   //             for(i=0;i!=bact+substance;i++)
   //                 free_cell(all_cell[i]);
                return 0;
        }
        while(c!='\n')
            c=getchar();
    }
}




















