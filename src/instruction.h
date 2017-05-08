#include <math.h>                                       
#include <stdlib.h>
#include <stdio.h>
//#include <vector>
//#include <stdexcept>
#include "tinyxml.h"
//#include <iostream>
//#include <string>
#include <parser.h>

using namespace std;

struct now_relation
{
    std::string reagent;
    std::string destroy;
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
//запись правил из XML Документа
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
                    now_relat->used = xml_reagent->Attribute("used");  
                    now_relat->formuls = xml_reagent->Attribute("new");  
                    now_relat->destroy = xml_reagent->Attribute("destroy");
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
        delete instruction_file;
        return 1;
    }
    //вывод инструкций
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
    //удаление правил
    void all_free()
    {
        now_all_relation *all_now=all_relation;
        while(all_now!=NULL)
        {
            now_all_relation *delete_all_now =all_now;
            now_name_of_relation *name_now=all_now->name_of_relation;
            while(name_now!=NULL)
            {
                now_name_of_relation *delete_name_now = name_now;
                now_relation *now=name_now->relation;
                while(now!=NULL)
                {
                    now_relation *delete_now =now;
                    now=now->next;
                    delete delete_now;
                }
                name_now=name_now->next;
                delete delete_name_now;
            }
            all_now=all_now->next;
            delete delete_all_now;
        }
    }
    //начало работы с рассматриваемой точкой пространства, на основе полученных
    //правил
    int work_with_data (int*new_cube,int*cube,int start_x,int start_y,int start_z,int razm,int bact,int substance,int radius,
            now_relation *now,string name_of_function,string *all_bact_and_subst)
    {
        //std::cout<<"now we work with data"<<(now->formuls)<<std::endl;
        while(now!=NULL)
        {
           int result = result_of_function(new_cube,cube,start_x,start_y,start_z,razm,bact,substance,radius,
                   now->used,now->formuls,now->reagent,(now->destroy),(name_of_function+","),all_bact_and_subst);
           if(result==-2)
           {
               //если правило не может быть выполнено-выход
               cout<<"FATAL ERROR IN RULES.XML"<<endl;
               return -2;
           }//else if(result==-1)//не сработала инструкция для данного реагента, переходим к следующей
           now=now->next;
        }
        return 1;
    }
    //проверка, все ли реагенты есть в рассматриваемой инструкции
    int this_reagent(std::string name,std::string have_reagents)
    {
        int found=0;
        int pos=0;
        //std::cout<<have_reagents<<endl;
        //cout<<name<<endl;
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
        int found2=0;
        int pos2=0;
        found2=have_reagents.find(",",pos2);
        while(have_reagents.substr(pos2, found2-pos2)!=name.substr(pos, name.length()-pos+1))
        {
            pos2=found2+1;
            found2=have_reagents.find(",",pos2);
            if(found2==std::string::npos)
               return -1;
        }
        return 1;
    }
    //проверка: соответсвуют ли выбранные в окресности реагенты какй либо
    //интсрукции, если нет идём на радис выше, если да работаем с полученными
    //данными
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

//нев вошедшее
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
 
