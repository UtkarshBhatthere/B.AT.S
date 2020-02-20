#pragma once

#ifndef ARDUINO
	#include <string>
	using String = std::string;
#endif

#define NOT_APPLICABLE "NA"

class Event
{
 private:
	int ev_ID;
	String ev_Name;
	String ev_Meta;

 public:
	Event(void) {
		ev_ID = NULL;
		ev_Name = NOT_APPLICABLE;
		ev_Meta = NOT_APPLICABLE;
	}

	Event(int ev_IDp, String ev_Namep, String ev_Metap) {
		ev_ID = ev_IDp;
		ev_Name = ev_Namep;
		ev_Meta = ev_Metap;
	}

	int getID(void) {
		return ev_ID;
	}

	std::string getName(void) {
		return ev_Name;
	}

	std::string getMeta(void) {
		return ev_Meta;
	}
};
