#ifndef _PARSE_H
#define _PARSE_H

#include <stdio.h>

typedef struct{
	char eventId;
	char Event[25];
}Event_TypeDef;

typedef enum{
	SUCCESS = 1,
	FAILURE = !SUCCESS
}status;

void delay(){
	int counter = 0xFFFF;
	while(--counter!=0);
}

status parseString(char* Input, Event_TypeDef* events){
	int count = 0;
	int counter;
	while(*Input != '\0')
	{	
		while(*Input != ',') // Comment it if the required string in json is before the status element, otherwise it'll skip the string portion.
			Input++;
		// while(*Input != ':')
		// 	Input++;
		// Input++;
		events[count].eventId = count;
		counter = 0;
		while(*Input != ';')
		{
			events[count].Event[counter++] = *Input++;
			if(*Input == '\0' || *Input == ';' || *Input == ',')
			{	
				events[count].Event[counter++] = '\0';
				break;
			}
		}
		count++;


	}
}
#endif