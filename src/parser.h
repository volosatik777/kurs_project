#include <string>
#include <vector>
#include <cmath>
#include <cctype>
#include <cstring>
#include <stdexcept>
#include <sstream>
#include <iostream>

#define cube(x,y,z,t) cube[(x)*(N)*(N)+(y)*(N)+z*(bact+substance)+t]            
#define new_cube(x,y,z,t) new_cube[(x)*(N)*(N)+(y)*(N)+z*(bact+substance)+t]    

struct Expression {
    Expression(std::string token) : token(token) {}
	Expression(std::string token, Expression a) : token(token), args{ a } {}
	Expression(std::string token, Expression a, Expression b) : token(token), args{ a, b } {}

	std::string token;
	std::vector<Expression> args;
};

class Parser {
public:
	explicit Parser(const char* input) : input(input) {}
	Expression parse();
private:
	std::string parse_token();
	Expression parse_simple_expression();
	Expression parse_binary_expression(int min_priority);

	const char* input;
};

std::string Parser::parse_token() {
	while (std::isspace(*input)) ++input;

    if (std::isdigit(*input)) {
		std::string number;
		while (std::isdigit(*input) || *input == '.') number.push_back(*input++);
		return number;
	}

	static const std::string tokens[] =
	{ "+", "-", "**", "*", "/", "mod", "abs", "sin", "cos", "(", ")" };
	for (auto& t : tokens) {
		if (std::strncmp(input, t.c_str(), t.size()) == 0) {
			input += t.size();
			return t;
		}
	}

	return "";
}

Expression Parser::parse_simple_expression() {
	auto token = parse_token();
	if (token.empty()) throw std::runtime_error("Invalid input");

	if (token == "(") {
		auto result = parse();
		if (parse_token() != ")") throw std::runtime_error("Expected ')'");
		return result;
	}

	if (std::isdigit(token[0]))//||token[0]=='A'||token[0]=='B'||token[0]=='F'||token[0]=='S'||token[0]=='W')
		return Expression(token);

	return Expression(token, parse_simple_expression());
}

int get_priority(const std::string& binary_op) {
	if (binary_op == "+") return 1;
	if (binary_op == "-") return 1;
	if (binary_op == "*") return 2;
	if (binary_op == "/") return 2;
	if (binary_op == "mod") return 2;
	if (binary_op == "**") return 3;
	return 0;
}

Expression Parser::parse_binary_expression(int min_priority) {
	auto left_expr = parse_simple_expression();

	for (;;) {
		auto op = parse_token();
		auto priority = get_priority(op);
		if (priority <= min_priority) {
			input -= op.size();
			return left_expr;
		}

		auto right_expr = parse_binary_expression(priority);
		left_expr = Expression(op, left_expr, right_expr);
	}
}

Expression Parser::parse() {
	return parse_binary_expression(0);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

double eval(const Expression& e) {
	switch (e.args.size()) {
	case 2: {
		auto a = eval(e.args[0]);
		auto b = eval(e.args[1]);
		if (e.token == "+") return a + b;
		if (e.token == "-") return a - b;
		if (e.token == "*") return a * b;
		if (e.token == "/") return a / b;
		if (e.token == "**") return pow(a, b);
		if (e.token == "mod") return (int)a % (int)b;
		throw std::runtime_error("Unknown binary operator");
	}

	case 1: {
		auto a = eval(e.args[0]);
		if (e.token == "+") return +a;
		if (e.token == "-") return -a;
		if (e.token == "abs") return abs(a);
		if (e.token == "sin") return sin(a);
		if (e.token == "cos") return cos(a);
		throw std::runtime_error("Unknown unary operator");
	}

	case 0:
        if(isdigit(e.token[0]))
		return strtod(e.token.c_str(), nullptr);
    }

	throw std::runtime_error("Unknown expression type");
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//поиск наименьшего реагента
int min_used(std::vector<int>& vector_with_data,std::vector<int> vector_with_used_data,std::vector<int> kof, int data)
{
    std::vector<int>::iterator new_data=vector_with_data.begin();
    std::vector<int>::iterator used_data=vector_with_used_data.begin();
    for(std::vector<int>::iterator kof_iter=kof.begin();kof_iter!=kof.end();kof_iter++)
    {
        if(new_data==vector_with_data.end())
            return -2;
        if(data*(*kof_iter)>*used_data)
            return -1;
        (*new_data)=data*(*kof_iter);
        new_data++;
        used_data++;
    }
    return 1;
}
//определение сколько какиких реагентов вступят в реакции
std::vector<int> my_kof(std::string kof_str)
{
    std::vector<int> kof_vector;
    int pos=0;
    int number=0;
    number=kof_str.find(",",pos);
    while(number!=std::string::npos)
    {
        std::string number_str=kof_str.substr(pos,number-pos);
        pos=number+1;
        kof_vector.push_back(atoi(number_str.c_str()));
        number=kof_str.find(",",pos);
    }
    std::string number_str=kof_str.substr(pos,kof_str.length()+1-pos);
    kof_vector.push_back(atoi(number_str.c_str()));
    return kof_vector;
}
//просмотр всех возможных комбинаций кофициентов
int how_many_used (std::vector<int> &vector_with_data,std::string kof_str)
{
    std::vector<int> kof=my_kof(kof_str);
    std::vector<int>::iterator kof_iter=kof.begin();
    std::vector<int> vector_with_used_data=vector_with_data;
    for(std::vector<int>::iterator data = vector_with_used_data.begin();data!=vector_with_used_data.end();data++)
    {
        if(kof_iter==kof.end())
        { 
            //Не верный XML
            return -2;
        }
        int result_min_used= min_used(vector_with_data,vector_with_used_data,kof,*data/(*kof_iter));
        if(result_min_used==1)   
            return 1;
        else if(result_min_used==-2)
            return -2;            
        kof_iter++;
    }                                              
}
//вычисление координат из скобок
int X_Y_Z_coord(std::string formul,int &found,char stop_num)
{
    int number_found=formul.find(stop_num,found+1);
    std::string number=formul.substr(found+1,number_found-found-1);
    found=number_found;
    return atoi(number.c_str());
}
//определить что за реагент находится формуле, вычислить его координаты и в
//формулу вместо него записать $
int change(int bact,int substance,int razm,std::vector<int>& x_vector,std::vector<int>& y_vector,std::vector<int>& z_vector,std::vector<int>& number_of_bact_subst_vector,
        int start_x,int start_y,int start_z,std::string &formul,int formul_pos,std::string what_change,int found,std::string *all_bact_and_subst)
{
    int number_of_bact_subst=0; 
    for(number_of_bact_subst=0;number_of_bact_subst!=bact+substance;number_of_bact_subst++)
        if(what_change==all_bact_and_subst[number_of_bact_subst])
            break;
    int x=start_x+X_Y_Z_coord(formul,found,',');
    if(x<0||x>=razm)
        return -1;
    int y=start_y+X_Y_Z_coord(formul,found,',');
    if(y<0||y>=razm)
        return -1;
    int z=start_z+X_Y_Z_coord(formul,found,']');
    if(z<0||z>=razm)
        return -1;

    x_vector.push_back(x);
    y_vector.push_back(y);
    z_vector.push_back(z);
    number_of_bact_subst_vector.push_back(number_of_bact_subst);
    formul.replace(formul_pos,found-formul_pos+1,"$");
    //если меньше радиуса
    return 1;
}
//при необходимости если реагент после ракции исчезает, удаляем его из старого cube
void delete_old_cube_data(int *cube,std::string all_destroy,int bact,int substance,int razm,std::vector<int>real_used_data,std::vector<int>::iterator x_iter,
        std::vector<int>::iterator y_iter,std::vector<int>::iterator z_iter,std::vector<int>::iterator number_of_bact_subst_iter)
{
    int N=razm*(bact+substance);
    int destroy_number =0;
    for(std::vector<int>::iterator iter=real_used_data.begin();iter!=real_used_data.end();iter++)
    {
        if(all_destroy[destroy_number]=='1')
            cube(*x_iter,*y_iter,*z_iter,*number_of_bact_subst_iter)=cube(*x_iter,*y_iter,*z_iter,*number_of_bact_subst_iter)-*iter;
        destroy_number+=2;
        x_iter++;
        y_iter++;
        z_iter++;
        number_of_bact_subst_iter++;
    }
}
//нахождение всех реагентов и последующие определение сколько в итоге возмётся
//из пространства на реакцию
int find_all(std::vector<int>& vector_number,int *cube,int start_x,int start_y,int start_z,int razm,int bact,int substance,int radius,
        std::string& formul,std::string all_used_reagents,std::string all_destroy,std::string kof_str,std::string *all_bact_and_subst)
{
    int N=razm*(bact+substance);
    int found=0;                                                            
    std::vector<int> x_vector,y_vector,z_vector,number_of_bact_subst_vector;
    int iter_x=0;
    int iter_y=0;
    int iter_z=0;
    int iter_number_of_bact_subst=0;
    found=formul.find("["); 

    while(found!=std::string::npos)                                         
    {                   
        int reagent_pos=0;
        int found_reagent=all_used_reagents.find(",",reagent_pos);
        while(found_reagent!=std::string::npos)
        {
            int formul_pos=formul.find(all_used_reagents.substr(reagent_pos,found_reagent-reagent_pos));
            if(formul_pos!=std::string::npos)
                if(formul_pos<found){
                    if(change(bact,substance,razm,x_vector,y_vector,z_vector,number_of_bact_subst_vector,start_x,start_y,start_z,formul,formul_pos,
                                all_used_reagents.substr(reagent_pos,found_reagent-reagent_pos),found,all_bact_and_subst)==-1)
                        return -1;
                    vector_number.push_back(cube(x_vector[iter_x],y_vector[iter_y],z_vector[iter_z],
                            number_of_bact_subst_vector[iter_number_of_bact_subst]));
                    iter_x++;
                    iter_y++;
                    iter_z++;
                    iter_number_of_bact_subst++;
                    break;
                }
            reagent_pos=found_reagent+1;
            found_reagent=all_used_reagents.find(",",reagent_pos);                                         
        }
        if(found_reagent==std::string::npos)
            return -2;
        found=formul.find("[");
    }
    int result_new_data= how_many_used(vector_number,kof_str);
    if(result_new_data==-1)
        return -1;
    else if(result_new_data==-2)
        return -2;
    delete_old_cube_data(cube,all_destroy,bact,substance,razm,vector_number,x_vector.begin(),y_vector.begin(),z_vector.begin(),number_of_bact_subst_vector.begin());
    return 1;
}
//замена в формуле $ на числа
void plus_symbols(std::string& formul,std::vector<int> data)
{
    for(std::vector<int>::iterator iter=data.begin();iter!=data.end();iter++)
    {
        int found=formul.find("$");
        std::stringstream number;
        number<<(*iter);
        formul.replace(found,1,number.str());
    }
}
//вычисление функции на основании правил и находящихся в конкретных координатах
//реагентов
int result_of_function(int *new_cube,int *cube,int start_x,int start_y,int start_z,int razm,int bact,int substance,int radius,
        std::string kof_str,std::string function,std::string who_change,std::string all_destroy,std::string all_used_reagents,std::string *all_bact_and_subst)
{
    int x,y,z;
    int found_who_change;
    int reag_what_change;
    int N=razm*(bact+substance);
    std::vector<int> vector_with_data;
    for(reag_what_change=0;reag_what_change!=bact+substance;reag_what_change++)
    {
        found_who_change=who_change.find(all_bact_and_subst[reag_what_change]);
        //std::cout<<who_change<<std::endl;
        if(found_who_change!=std::string::npos)
        {
            //сброс значений всех правил при первом выхде за границы
            int found=who_change.find("[");
            x=start_x+X_Y_Z_coord(who_change,found,',');
            if(x<0||x>=razm)
                return -1;
            y=start_y+X_Y_Z_coord(who_change,found,',');
            if(y<0||y>=razm)
                return -1;
            z=start_z+X_Y_Z_coord(who_change,found,']');
            if(z<0||z>=razm)
                return -1;
            break;
        }
    }
    int result_of_find=find_all(vector_with_data,cube,start_x,start_y,start_z,razm,bact,substance,radius,function,all_used_reagents,all_destroy,kof_str,all_bact_and_subst);
    if(result_of_find==-1)
        return -1;
    else if(result_of_find==-2)
        return -2;//ошибка в XML документе
    plus_symbols(function,vector_with_data);
    char* char_function = new char[function.length() + 1]; 
    std::strcpy(char_function, function.c_str());
    Parser p(char_function);
    int now_result = eval(p.parse());
    delete[] char_function;
    std::cout<<"RESULT:"<<now_result<<"for"<<reag_what_change<<x<<y<<z<<all_used_reagents<<std::endl;
    if(now_result<0)//что делать при отрицательных значениях?
        return 1;//new_cube(x,y,z,reag_what_change)=0;
    else
        new_cube(x,y,z,reag_what_change)+= now_result;
    return 1;
}

