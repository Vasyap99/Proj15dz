#include <iostream>
#include "chat.h"
/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main(int argc, char** argv) {
	Chat c;
	c.reg("kok","pip",3);
	c.reg("kko1","pip1",4);	
	c.reg("login","passw1",6);		
	c.reg("login2","passw2",6);		
	c.reg("login3","passw3",6);	
	c.reg("login4","passw4",6);	
	c.reg("login5","passw5",6);	
	c.reg("login6","passw6",6);	
	c.reg("login7","passw7",6);						
	
	std::cout << c.login("kok","pip",3) << std::endl;
	std::cout << c.login("kok","2ip",3) << std::endl;	

	std::cout << c.login("login","passw1",6) << std::endl;			
	std::cout << c.login("kko1","pip1",4) << std::endl;		
	std::cout << c.login("kko1","pip2",4) << std::endl;			

	std::cout << c.login("login2","passw2",6) << std::endl;		
	std::cout << c.login("login3","passw3",6) << std::endl;			
	std::cout << c.login("login4","passw4",6) << std::endl;	

	std::cout << c.login("login5","passwÔ",6) << std::endl;	
	
	std::cout << c.login("login5","passw5",6) << std::endl;	
	std::cout << c.login("login6","passw6",6) << std::endl;			
	std::cout << c.login("login7","passw7",6) << std::endl;				
	return 0;
}
