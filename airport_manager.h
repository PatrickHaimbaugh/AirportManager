#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/*
DO NOT MODIFY.
*/

typedef struct Airport{
	char * name; /*The airport name*/
	int numDestinations; /*The number of destinations the airport offers flights to*/
	struct Airport ** destinations; /*The array of destinations the airport offers flights to*/
} Airport;

typedef struct Airline {
    Airport** airports; /*The array of all airports managed  by the company*/
    int numAirports; /*The current number of airports managed by the company*/
    int maxAirports; /*The max number of airports the airports array can store*/
} Airline;

void InitializeAirline(Airline *airline, int maxAirportsN); // Part 1
int AddAirport(Airline *airline, const char* name); // Part 2
Airport *FindAirport(Airline *airline, const char *name); // Part 3
int AddFlight(Airline *airline, const char* origin_name, const char* dest_name); // Part 4
int PrintFlightsFromAirport(Airline *airline, const char *origin_name);    // Part 5
int PrintFlightsToAirport(Airline *airline, const char *dest_name);    // Part 6
void PrintAirlineAsMatrix(Airline *airline); // Part 7
int HasDirectFlight(Airline *airline, const char *origin_name, const char *dest_name); // Part 8
int HasOneStopFlight(Airline *airline, const char *origin_name, const char *dest_name); // Part 9
void DeleteAirline(Airline *airline); // Part 10

void GuaranteeOneStop(Airline *airline); // Part 11 extra credit
