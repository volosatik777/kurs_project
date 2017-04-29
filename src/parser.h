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

//int first_cof;
//int sec_cof;
//int quantity_first;
//int quantity_second;
//int quantity_what_change;

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
/*
    if(*input=='A'||*input=='B'||*input=='F'||*input=='S'||*input=='W'){
        std::string number;
        number.push_back(*input++);
        return number;
    }
*/
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
/*        else
        {
           if(e.token[0]=='F')
               return first_cof;
           if(e.token[0]=='S')
               return sec_cof;
           if(e.token[0]=='A')
               return quantity_first;
           if(e.token[0]=='B')
               return quantity_second;
           if(e.token[0]=='W')
               return quantity_what_change;
        }*/
	}

	throw std::runtime_error("Unknown expression type");
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


int errors;

void test(const char* input, double expected) {
	try {
		Parser p(input);
		auto result = eval(p.parse());
		if (result == expected) return;
		std::cout << input << " = " << expected << " : error, got " << result << '\n';
	}
	catch (std::exception& e) {
		std::cout << input << " : exception: " << e.what() << '\n';
	}
	++errors;
}

std::string convertInt(int number)
{
    std::stringstream ss;
    ss << number;
    return ss.str();
}


int min_used(std::vector<int>& vector_with_data,std::vector<int> vector_with_used_data,std::vector<int> kof, int data)
{
    std::vector<int>::iterator new_data=vector_with_data.begin();
    std::vector<int>::iterator used_data=vector_with_used_data.begin();
    for(std::vector<int>::iterator kof_iter=kof.begin();kof_iter!=kof.end();kof_iter++)
    {
        //std::cout<<"NEXT data"<<*kof_iter<<data<<*used_data<<std::endl;
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

int how_many_used (std::vector<int> &vector_with_data,std::string kof_str)
{
    std::vector<int> kof=my_kof(kof_str);
    std::vector<int>::iterator kof_iter=kof.begin();
    std::vector<int> vector_with_used_data=vector_with_data;
    for(std::vector<int>::iterator data = vector_with_used_data.begin();data!=vector_with_used_data.end();data++)
    {
        //std::cout<<"DATA"<<*data<<std::endl;
        if(kof_iter==kof.end())
        { 
            std::cout<<"not good kof"<<std::endl;
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

int X_Y_Z_coord(std::string formul,int &found,char stop_num)
{
    int number_found=formul.find(stop_num,found+1);
    std::string number=formul.substr(found+1,number_found-found-1);
    found=number_found;
    //std::cout<<number<<std::endl;
    return atoi(number.c_str());
}

int change(int bact,int substance,int razm,std::vector<int>& x_vector,std::vector<int>& y_vector,std::vector<int>& z_vector,std::vector<int>& number_of_bact_subst_vector,
        int start_x,int start_y,int start_z,std::string &formul,int formul_pos,std::string what_change,int found,std::string *all_bact_and_subst)
{
    int number_of_bact_subst=0; 
    std::cout<<"@HATtttt"<<what_change<<found<<std::endl;
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

    //std::cout<<x<<y<<z<<"!"<<number_of_bact_subst<<formul<<std::endl;
    x_vector.push_back(x);
    y_vector.push_back(y);
    z_vector.push_back(z);
    //std::cout<<formul_pos<<"!!"<<found<<std::endl;
    number_of_bact_subst_vector.push_back(number_of_bact_subst);
    formul.replace(formul_pos,found-formul_pos+1,"$");
    //std::cout<<formul<<std::endl;
    //если меньше радиуса
    return 1;
}

void delete_old_cube_data(int *cube,int bact,int substance,int razm,std::vector<int>real_used_data,std::vector<int>::iterator x_iter,
        std::vector<int>::iterator y_iter,std::vector<int>::iterator z_iter,std::vector<int>::iterator number_of_bact_subst_iter)
{
    int N=razm*(bact+substance);
    for(std::vector<int>::iterator iter=real_used_data.begin();iter!=real_used_data.end();iter++)
    {
        std::cout<<"NEAD IT???"<<*iter<<std::endl;
        std::cout<<"NEAD IT"<<*x_iter<<*y_iter<<*z_iter<<*number_of_bact_subst_iter<<std::endl;
        std::cout<<cube((*x_iter),(*y_iter),(*z_iter),(*number_of_bact_subst_iter))<<std::endl;
        std::cout<<(cube(*x_iter,*y_iter,*z_iter,*number_of_bact_subst_iter)=cube(*x_iter,*y_iter,*z_iter,*number_of_bact_subst_iter)-*iter)<<std::endl;
        x_iter++;
        y_iter++;
        z_iter++;
        number_of_bact_subst_iter++;
    }
}

int find_all(std::vector<int>& vector_number,int *cube,int start_x,int start_y,int start_z,int razm,int bact,int substance,int radius,
        std::string& formul,std::string all_used_reagents,std::string kof_str,std::string *all_bact_and_subst)
{
    int N=razm*(bact+substance);
    int found=0;                                                            
    std::vector<int> x_vector,y_vector,z_vector,number_of_bact_subst_vector;
    int iter_x=0;
    int iter_y=0;
    int iter_z=0;
    int iter_number_of_bact_subst=0;
    found=formul.find("["); 

    //std::cout<<"START"<<formul<<all_used_reagents<<kof_str<<std::endl;
    while(found!=std::string::npos)                                         
    {                   
        //std::cout<<"NOWwwww111111!"<<formul<<std::endl;
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
                    //std::cout<<"vector_number="<<cube(x_vector[iter_x],y_vector[iter_y],z_vector[iter_z],
                    //        number_of_bact_subst_vector[iter_number_of_bact_subst])<<x_vector[iter_x]<<y_vector[iter_y]<<z_vector[iter_z]<<number_of_bact_subst_vector[iter_number_of_bact_subst]<<std::endl;
                    iter_x++;
                    iter_y++;
                    iter_z++;
                    iter_number_of_bact_subst++;
                    break;
                }
            reagent_pos=found_reagent+1;
            //std::cout<<"NOW2!"<<std::endl;
            found_reagent=all_used_reagents.find(",",reagent_pos);                                         
        }
        if(found_reagent==std::string::npos)
            return -2;
        found=formul.find("[");
        //std::cout<<"NOW3!"<<std::endl;
    }
    //std::cout<<"End"<<formul<<std::endl;
    //std::cout<<"NOW4!"<<kof_str<<std::endl;
    int result_new_data= how_many_used(vector_number,kof_str);
    if(result_new_data==-1)
        return -1;
    else if(result_new_data==-2)
        return -2;
    //std::cout<<"NOW6!"<<std::endl;
    std::cout<<cube(1,0,1,1);
    std::cout<<cube(x_vector[0],y_vector[0],z_vector[0],number_of_bact_subst_vector[0])<<vector_number[0]<<std::endl;
    delete_old_cube_data(cube,bact,substance,razm,vector_number,x_vector.begin(),y_vector.begin(),z_vector.begin(),number_of_bact_subst_vector.begin());
    //std::cout<<"NOW7!"<<std::endl;
    return 1;
}

void plus_symbols(std::string& formul,std::vector<int> data)
{
    for(std::vector<int>::iterator iter=data.begin();iter!=data.end();iter++)
    {
        int found=formul.find("$");
        std::stringstream number;
        number<<(*iter);
        formul.replace(found,1,number.str());
        //std::cout<<formul<<std::endl;
    }
}

int result_of_function(int *new_cube,int *cube,int start_x,int start_y,int start_z,int razm,int bact,int substance,int radius,
        std::string kof_str,std::string function,std::string who_change,std::string all_used_reagents,std::string *all_bact_and_subst)
{
    //сброс значений всех правил при первом выхде за границы
    //std::cout<<function<<std::endl;
    //std::cout<<"1111111111111"<<kof_str<<"!"<<who_change<<"!"<<all_used_reagents<<std::endl;
    int x,y,z;
    int found_who_change;
    int reag_what_change;
    int N=razm*(bact+substance);
    std::vector<int> vector_with_data;
    for(reag_what_change=0;reag_what_change!=bact+substance;reag_what_change++)
    {
        found_who_change=who_change.find(all_bact_and_subst[reag_what_change]);
        std::cout<<who_change<<std::endl;
        if(found_who_change!=std::string::npos)
        {
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
    int result_of_find=find_all(vector_with_data,cube,start_x,start_y,start_z,razm,bact,substance,radius,function,all_used_reagents,kof_str,all_bact_and_subst);
    if(result_of_find==-1)
        return -1;
    else if(result_of_find==-2)
        return -2;
    plus_symbols(function,vector_with_data);
    char* char_function = new char[function.length() + 1]; // or
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

    /*
    int found=0;                                                            
    int pos=0;
    int number_of_bact_subst=0;
    found=who_change.find(",",pos+1); 
    while(found!=std::string::npos)                                         
    {                                                                    
        int formul_pos=0;
        formul_pos=function.find(who_change.substr(pos,found-pos));
        while(formul_pos!=std::string::npos)
        {
            function.replace(formul_pos,found-pos,usingconvertInt(how_many[number_of_bact_subst]));             
            formul_pos=function.find(who_change.substr(pos,found-pos));
        }
        pos=found;                                                          
        found=who_change.find(",",pos+1);                                         
    } 
    std::cout<<function<<std::endl;
    char* char_function = new char[function.length() + 1]; // or
    std::strcpy(char_function, function.c_str());
    Parser p(char_function);
    int now_result = eval(p.parse());
    delete[] char_function;
    if(now_result<0)
        return 0;
    return now_result;
}

*
int result_function(char* function,int name_f_cof,int f_cof,int name_sec_cof,int s_cof,int who_change)
{
    quantity_first=name_f_cof;
    first_cof=f_cof;
    quantity_second=name_sec_cof;
    sec_cof=s_cof;
    quantity_what_change=who_change;
    Parser p(function);
    int now_result = eval(p.parse());
    if(now_result<0)
        return 0;
    return now_result;
}

int main() {
	test("0", 0);
	test("1", 1);
	test("9", 9);
	test("10", 10);
	test("+1", 1);
	test("-1", -1);
	test("(1)", 1);
	test("(-1)", -1);
	test("abs(-1)", 1);
	test("1+20", 21);
	test("1 + 20", 21);
	test("1+20+300", 321);
	test("1+20+300+4000", 4321);
    test("-1+20", 19);
    test("--1+20", 21);
    test("---1+20", 19);
	test("(1+20)", 21);
	test("-2*3", -6);
	test("2*-3", -6);
	test("1++2", 3);
	test("1+10*2", 21);
	test("10*2+1", 21);
	test("(1+20)*2", 42);
	test("2*(1+20)", 42);
	test("(1+2)*(3+4)", 21);
	test("2*3+4*5", 26);
	test("100+2*10+3", 123);
	test("2**3", 8);
	test("2**3*5+2", 42);
	test("5*2**3+2", 42);
	test("2+5*2**3", 42);
	test("1+2**3*10", 81);
	test("2**3+2*10", 28);
	test("5 * 4 + 3 * 2 + 1", 27);
	std::cout << "Done with " << errors << " errors.\n";
}
*/
