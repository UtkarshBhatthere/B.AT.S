#include <stdio.h>
#include "parse.h"
#include <stdlib.h>

int main(){
	Event_TypeDef json[5];
	//Event_TypeDef *ptr = &json;
	char* string = "{\"status\": 200,\"message\": \"1,Maths Class;2,HS Class;3,DS Class;4,Digital Class;5,Physics Class;\"}";
	parseString(string, json);
	printf("%s\n",json[0].Event);
	printf("%s\n",json[1].Event);
	printf("%s\n",json[2].Event);
	printf("%s\n",json[3].Event);
	printf("%s\n",json[4].Event);
system("pause");
}