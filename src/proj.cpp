#include "menu.h"

using namespace std; 

#define cube(x,y,z,t) cube[(x)*(N)*(N)+(y)*(N)+z*(bact+substance)+t]

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
    
    //считываем информацию о кубе
    file_with_data>>razm>>bact>>substance;

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

    // строим массив всех реагентов
    
    std::string all_bact_and_subst[substance+bact];
    for(int j=0;j!=substance+bact;j++)
        file_with_data>>all_bact_and_subst[j];

    int N=razm*(bact+substance);

    //создаём куб и заполняем его
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

    //читаем инструции их XML файла
    all_instruction instruction;
    if(instruction.read_new_instraction()!=1)
    {
        printf("we havent conf file \n");
        return -1;
    }
    instruction.print_instraction();

    cout<<"end-instr"<<endl;

    menu(argc,argv,cube,instruction,razm,bact,substance,N,all_bact_and_subst);

    return 0;
}





















