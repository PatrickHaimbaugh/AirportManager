#include "airport_manager.h"
#include <stdio.h>
void InitializeAirline(Airline *airline, int maxAirportsN) {
	airline->airports = (Airport **)malloc(sizeof(Airport *) * maxAirportsN);
	airline->numAirports = 0;
	airline->maxAirports = maxAirportsN;
}

int AddAirport (Airline *airline, const char *name) {
	for (int i = 0; i < airline->numAirports; i++) {
		if (strcmp(airline->airports[i]->name, name) == 0) {
			return 0;
		}
	}
	Airport * new_airport = (Airport *)malloc(sizeof(Airport));
	char * new_name = (char *)malloc((strlen(name) + 1) * sizeof(char));
	strcpy(new_name, name);
	new_airport->name = new_name;
	new_airport->numDestinations = 0;
	new_airport->destinations = NULL;
	if (airline->numAirports == airline->maxAirports) {
		airline->airports = realloc(airline->airports, sizeof(Airport *) * 2 * airline->maxAirports);
		airline->maxAirports = airline->maxAirports * 2;
	}
	airline->airports[airline->numAirports] = new_airport;
	airline->numAirports++;
	return 1;
}

Airport *FindAirport (Airline *airline, const char *name) {
	for (int i = 0; i < airline->numAirports; i++) {
		if (strcmp(airline->airports[i]->name, name) == 0) {
			return airline->airports[i];
		}
	}
	return NULL;
}

int AddFlight (Airline *airline, const char * origin_name, const char * dest_name) {
	if (strcmp(origin_name, dest_name) == 0) {
		return 0;
	}
	int has_airports = 0;
	int origin_index = 0;
	int dest_index = 0;
	for (int i = 0; i < airline->numAirports; i++) {
		if (strcmp(airline->airports[i]->name, origin_name) == 0) {
			for (int j  = 0; j < airline->airports[i]->numDestinations; j++) {
				if (strcmp(airline->airports[i]->destinations[j]->name, dest_name) == 0) {
					return 0;
				}
			}
			origin_index = i;
			has_airports++;
		} else if (strcmp(airline->airports[i]->name, dest_name) == 0) {
			dest_index = i;
			has_airports++;
		}
	}
	if (has_airports != 2) {
		return 0;
	}
	airline->airports[origin_index]->destinations = (Airport **)realloc(airline->airports[origin_index]->destinations, sizeof(Airport *) * (airline->airports[origin_index]->numDestinations + 1));
	airline->airports[origin_index]->destinations[airline->airports[origin_index]->numDestinations] = airline->airports[dest_index];
	airline->airports[origin_index]->numDestinations++;
	return 1;
}
int PrintFlightsFromAirport(Airline *airline, const char *origin_name) {
	int origin_index = -1;
	for (int i = 0; i < airline->numAirports; i++) {
		if (strcmp(airline->airports[i]->name, origin_name) == 0) {
			origin_index = i;
			break;
		}
	}
	if (origin_index == -1) {
		return 0;
	}
	for (int i = 0; i < airline->airports[origin_index]->numDestinations; i++) {
		printf("%s\n",airline->airports[origin_index]->destinations[i]->name);
	}
	return 1;
}
int PrintFlightsToAirport(Airline *airline, const char *dest_name) {
	int printed = 0;
	for (int i = 0; i < airline->numAirports; i++) {
		for(int j = 0; j < airline->airports[i]->numDestinations; j++) {
			if (strcmp(airline->airports[i]->destinations[j]->name, dest_name) == 0) {
				printed = 1;
				printf("%s\n", airline->airports[i]->name);
			}
		}
	}
	if (printed) {
		return 1;
	} else {
		return 0;
	}
}
void PrintAirlineAsMatrix(Airline *airline) {
	for (int i = 0; i < airline->numAirports; i++) {
		for (int j = 0; j < airline-> numAirports; j++) {
			int added = 0;
			for (int k = 0; k < airline->airports[i]->numDestinations; k++) {
				if (strcmp(airline->airports[i]->destinations[k]->name, airline->airports[j]->name) == 0) {
					added = 1;
				}
			}
			printf("%d", added);
		}
		printf("\n");
	}

}
int HasDirectFlight(Airline *airline, const char *origin_name, const char *dest_name) {
	if (strcmp(origin_name, dest_name) == 0) {
		return 0;
	}
	for (int i = 0; i < airline->numAirports; i++) {
		if (strcmp(airline->airports[i]->name, origin_name) == 0) {
			for (int j = 0; j < airline->airports[i]->numDestinations; j++) {
				if (strcmp(airline->airports[i]->destinations[j]->name, dest_name) == 0) {
					return 1;
				}
			}
			break;
		}
	}
	return 0;
}
int HasOneStopFlight(Airline *airline, const char *origin_name, const char *dest_name) {
	if (strcmp(origin_name, dest_name) == 0) {
		return 0;
	}
	for (int i = 0; i < airline->numAirports; i++) {
		if (strcmp(airline->airports[i]->name, origin_name) == 0) {
			for (int j = 0; j < airline->airports[i]->numDestinations; j++) {
				//printf("num of destinations of %s is %d\n", airline->airports[i]->name, airline->airports[i]->numDestinations);
				if (HasDirectFlight(airline, airline->airports[i]->destinations[j]->name, dest_name) == 1) {
					//printf("one stop from %s to %s through %s\n", origin_name, dest_name, airline->airports[i]->destinations[j]->name);
					return 1;
				}
			}
		break;
		}
	}
	//printf("reached end of hasonestop\n");
	return 0;
}
void DeleteAirline(Airline *airline) {
	for (int i = 0; i < airline->numAirports; i++) {
		free(airline->airports[i]->destinations);
		free(airline->airports[i]->name);
		free(airline->airports[i]);
	}
	free(airline->airports);
}
void GuaranteeOneStop(Airline *airline){
	for (int i = 0; i < airline->numAirports; i++) {
		for (int j = 0; j < airline->numAirports; j++) {
			if (HasDirectFlight(airline, airline->airports[i]->name, airline->airports[j]->name) != 1 && HasOneStopFlight(airline, airline->airports[i]->name, airline->airports[j]->name) != 1) {
				AddFlight(airline, airline->airports[i]->name, airline->airports[j]->name);
				//printf("adding flight from %s to %s ", airline->airports[i]->name, airline->airports[j]->name);
				//printf("one stop is %d\n", HasOneStopFlight(airline, airline->airports[i]->name, airline->airports[j]->name));
			}
		}
	}
}
int main() {
	Airline airline;
	//printf("inital airline -> %p\n", &airline);
	InitializeAirline(&airline, 3);
	//printf("test airline -> %p\nmaxAirports -> %d\n", &airline, (&airline)->maxAirports);
	AddAirport(&airline, "test");
	//printf("two -> %d\n", two);
	//Airport * finding = FindAirport(&airline, "test");
	//printf("found -> %s\n", finding->name);
	AddAirport(&airline, "test2");
	//int one = AddFlight(&airline, "test", "test2");
	AddAirport(&airline, "test3");
	AddAirport(&airline, "test4");
	AddAirport(&airline, "test5");
	AddAirport(&airline, "test6");
	//AddFlight(&airline, "test", "test3");
	//printf("flight added -> %d\n", one);
	//PrintFlightsFromAirport(&airline, "test");
	//PrintFlightsToAirport(&airline, "test2");
	//AddFlight(&airline, "test2", "test3");
	PrintAirlineAsMatrix(&airline);	
	//int direct = HasDirectFlight(&airline, "test3", "test2");
	//printf("direct flight %d\n", direct);
	//int oneStop = HasOneStopFlight(&airline, "test2", "test3");
	//printf("one stop flight %d\n", oneStop);
	//printf("testing garantee one stop\n");
	GuaranteeOneStop(&airline);
	PrintAirlineAsMatrix(&airline);
	DeleteAirline(&airline);
	return 0;
}
