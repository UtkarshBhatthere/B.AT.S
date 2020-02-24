#pragma once
#include "Event.h"

typedef enum{
	SUCCESS,
	FAILURE
}status;

class Parser
{
	static String charsToStr(char* input, int size) {
		if (size == 0) return "";
		
		String buffer = "";
		for (int i = 0; i < size; i++) {
			buffer += input[i];
		}

		return buffer;
	}

	static void splitEventData(String ev_Data, String& Name, String& Meta) {
		char* iter = (char*)ev_Data.c_str();

		while (*iter != '_') {
			Name += *iter;
		}
		while (*iter != '\0') {
			Meta += *iter;
		}
	}

	//Obviously untested, will fix once Hardware tests are done.
	static void fillEvents(Event* ev_Array,  char* response){
		int count = 0;
		int offset_count = 0;
		char* iterator = response;

		while (*iterator != '\0') {

			while (*iterator == ':')
				iterator++;
			iterator += 2;	// Skipping the '"' in String.


			char* start = iterator;
			while (*iterator != '"') {	// Counting the size of the EventData.
				offset_count++;
			}

			String EventName, EventMeta;
			String EventData = charsToStr(start, offset_count); // Fetching EventData.
			splitEventData(EventData, EventName, EventMeta); // Splitting Event Data.
			new (ev_Array + count) Event(count, EventName, EventMeta); // Creating Event Emplace.

			count++;
		}
	}
	
};

