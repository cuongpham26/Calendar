#include <stdio.h> // for printf()
#include <stdlib.h> // for atoi()
#include <string.h> // for strlen(), strncpy(), strcasecmp()
#include <time.h> // for time()

const char* months[] = {"Janurary", "February", "March", "April", "May", "June", "July", "August", 
"September", "October", "November", "December"};
const char* monthCodes[] = {"jan", "feb", "mar", "apr", "may", "jun", "jul", "aug", "sep", "oct", "nov", "dec"};
int daysOfMonth[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31, 30, 31};

// The function receives the year as an input
// returns 1 if it's a leap year
// and returns 0 if it's not a leap year
int isLeapYear(int year)
{
	if ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0){
		return 1;
	}
	else {
		return 0;
	}
}

// The function receives a integer pointer to month and year as input
// and modifies the month and year so that it describe the current month and year
void getCurrentTime(int* month, int* year)
{
    time_t t = time(NULL);
    struct tm current_time = *localtime(&t);
    *month = current_time.tm_mon + 1;
    *year = current_time.tm_year + 1900;
}

// The function calculates the number of days from Janurary 1 1753
// the given day is, and then from that return the day of the week
// the given day is, 0 means Sunday, 6 means Saturday
int findDayOfWeek(int month, int day, int year)
{
	if (isLeapYear(year) == 1) {
		daysOfMonth[1] = 29;
	}

	if (year < 1753 || month < 1 || month > 12 || day < 1 || day > daysOfMonth[month-1]) {
		printf("Not a valid date\n");
	}

	for (int i = 1753; i < year; ++i) {
		if (isLeapYear(i) == 1) {
			day += 366;
		}
		else {
			day += 365;
		}
	}

	for (int i = 0; i < month-1; ++i) {
		day += daysOfMonth[i];
	}

	return day%7;
}


// The function receives a string like "Marchy"
// and then finds the corresponding month to it ("March" in this example)
// and then returns the number of the month, 1 means January, 12 means December
// it returns 0 if the string doesn't match with any months
int findMonth(char* str)
{
	char monthCode[4];
	strncpy(monthCode, str, 3);
	monthCode[3] = '\0';

	for (int i = 0; i < 12; ++i) {
		if (strcasecmp(monthCode, monthCodes[i]) == 0) {
			return i+1;
		}
	}

	return 0;
}

// The function receives a month and a year as input
// and print the calendar for the corresponding month
void printMonth(int month, int year)
{
	const char* month_str = months[month-1];

	for (int i = 0; i < (15 - strlen(month_str)) / 2; ++i){
		printf(" ");
	}
	printf("%s %d\n", month_str, year);

	printf("Su Mo Tu We Th Fr Sa\n");

	int spaceCount = 0;
	
	// prints the spacing before the 1st day of month
    for (int i = 0; i < findDayOfWeek(month, 1, year) * 3 + 1; ++i) {
        printf(" ");
        ++spaceCount;
    }
    
    // prints the day of month
	for (int i = 1; i <= 31; ++i) {
	    if (i == 1) {
	        printf("%d", i);
	        spaceCount += 1;
	    }
		else if (spaceCount == 20) {
		    printf("\n%2d", i);
		    spaceCount = 2;
		}
		else {
		    printf("%3d", i);
		    spaceCount += 3;
		}
	}
}

// The function is a helper function for printYear()
// It receives the line, month, and year as input
// and prints out the corresponding line
void printLine(int line, int month, int year)
{
	if (line == 1) 
	{
		int spaceCount = 0;

		for (int i = 0; i < findDayOfWeek(month, 1, year) * 3 + 1; ++i) {
			printf(" ");
			++spaceCount;
		}

		int day = 1;
		while (spaceCount < 20) {
			if (day == 1) {
				printf("%d", day);
				++spaceCount;
			}
			else {
				printf("%3d", day);
				spaceCount += 3;
			}
			++day;
		}
	}
	else if (line == 5 || line == 6)
	{
		/* [firstDayOfCurrentLine] = [lastDayOfLine1] + 1 + 7 * (currentLine - 2)
		 *                         = 7 - findDayOfWeek(month, 1, year) + 1 + 7 * (currentLine - 2)
		 *                         = 7 * currentLine - 6 - findDayOfWeek(month, 1, year)
		 */

		int firstDayOfLine = 7 * line - 6 - findDayOfWeek(month, 1, year);

		for (int i = firstDayOfLine; i < firstDayOfLine + 7; ++i) {
			if (i > daysOfMonth[month-1] && i == firstDayOfLine) {
				printf("                    "); // print the whole line as spaces
				break;
			}
			else if (i > daysOfMonth[month-1]) {
				break;
			}
			else if (i == firstDayOfLine) {
				printf("%2d", i);
			}
			else {
				printf("%3d", i);
			}
		}
		// [saturdayOfCurrentLine (assuming it exist)] = [firstDayOfCurrentLine] + 6

		int lastDayOfLine = 6 + firstDayOfLine;

		// We add the condition daysOfMonth[month-1] > lastDayOfLine -7 because the week might already end before
		// Saturday of week 5 and we don't need to do these spacing for week 6 anymore but the following if statement
		// would still execute without the addtional condition
		if (daysOfMonth[month-1] < lastDayOfLine && daysOfMonth[month-1] > lastDayOfLine - 7) {

			int lastDayOfLineInWeek = findDayOfWeek(month, daysOfMonth[month-1], year); // 0 if Sunday, 6 if Saturday

			for (int i = 0; i < (6 - lastDayOfLineInWeek) * 3; ++i) {
				printf(" ");
			}
		}
	}
	else 
	{
		/* [firstDayOfCurrentLine] = [lastDayOfLine1] + 1 + 7 * (currentLine - 2)
		 *                         = 7 - findDayOfWeek(month, 1, year) + 1 + 7 * (currentLine - 2)
		 *                         = 7 * currentLine - 6 - findDayOfLine(month, 1, year)
		 */

		int firstDayOfLine = 7 * line - 6 - findDayOfWeek(month, 1, year);

		for (int i = firstDayOfLine; i < firstDayOfLine + 7; ++i) {
			if (i > daysOfMonth[month-1]) {
				break;
			}
			else if (i == firstDayOfLine) {
				printf("%2d", i);
			}
			else {
				printf("%3d", i);
			}
		}
	}
}

// The function receives a year as an input
// and prints out the calendar for the whole year
void printYear(int year)
{
	printf("                            %d\n", year);
	printf("      January               February               March        \n");
	printf("Su Mo Tu We Th Fr Sa  Su Mo Tu We Th Fr Sa  Su Mo Tu We Th Fr Sa\n");

	for (int i = 1; i <= 6; ++i) {
		printLine(i, 1, year);
		printf("  ");
		printLine(i, 2, year);
		printf("  ");
		printLine(i, 3, year);
		printf("\n");
	}

    printf("\n       April                  May                   June        \n");
	printf("Su Mo Tu We Th Fr Sa  Su Mo Tu We Th Fr Sa  Su Mo Tu We Th Fr Sa\n");

	for (int i = 1; i <= 6; ++i) {
		printLine(i, 4, year);
		printf("  ");
		printLine(i, 5, year);
		printf("  ");
		printLine(i, 6, year);
		printf("\n");
	}

	printf("\n        July                 August              September      \n");
	printf("Su Mo Tu We Th Fr Sa  Su Mo Tu We Th Fr Sa  Su Mo Tu We Th Fr Sa\n");

	for (int i = 1; i <= 6; ++i) {
		printLine(i, 7, year);
		printf("  ");
		printLine(i, 8, year);
		printf("  ");
		printLine(i, 9, year);
		printf("\n");
	}

	printf("\n      October               November              December      \n");
	printf("Su Mo Tu We Th Fr Sa  Su Mo Tu We Th Fr Sa  Su Mo Tu We Th Fr Sa\n");

	for (int i = 1; i <= 6; ++i) {
		printLine(i, 10, year);
		printf("  ");
		printLine(i, 11, year);
		printf("  ");
		printLine(i, 12, year);
		printf("\n");
	}
}


int main(int argc, char* argv[])
{
	if (argc == 1){
		// If argc == 1, the only possibility is ./cal
		// which prints out current month and year
		int month, year;
		getCurrentTime(&month, &year);
		printMonth(month, year);
	}
	else if (argc == 2) {
		// if argc == 2, the only possibility is ./cal 2016
		// which prints out the entire year 2016
		int year = atoi(argv[1]);

		if (year >= 1753) {
			printYear(year);
		}
		else {
			printf("Invalid input. Year must be >= 1753.");
		}
	}
	else if (argc == 3) {
		// If argc == 3, there are 4 possibilities
		// ./cal -m Marchy
		// ./cal -m 3
		// ./cal Marchy 2016
		// ./cal 3 2016
		if (strcmp(argv[1], "-m") == 0 && findMonth(argv[2]) != 0) {
			int temp, year;
			getCurrentTime(&temp, &year);
			printMonth(findMonth(argv[2]), year);
		}
		else if (strcmp(argv[1], "-m") == 0 && atoi(argv[2]) >= 1 && atoi(argv[2]) <= 12) {
			int temp, year;
			getCurrentTime(&temp, &year);
			printMonth(atoi(argv[2]), year);
		}
		else if (findMonth(argv[1]) != 0 && atoi(argv[2]) >= 1753) {
			printMonth(findMonth(argv[1]), atoi(argv[2]));
		}
		else if (atoi(argv[1]) >= 1 && atoi(argv[1]) <= 12 && atoi(argv[2]) >= 1753) {
			printMonth(atoi(argv[1]), atoi(argv[2]));
		}
		else {
			printf("Invalid input.");
		}
	}
	else if (argc == 4) {
		// If argc == 4, there are 2 possibilities
		// ./cal -m Marchy 2016
		// ./cal -m 3 2016
		int year = atoi(argv[3]);

		if (strcmp(argv[1], "-m") == 0 && findMonth(argv[2]) != 0 && year >= 1753) {
			printMonth(findMonth(argv[2]), atoi(argv[3]));
		}
		else if (strcmp(argv[1], "-m") == 0 && atoi(argv[2]) >= 1 && atoi(argv[2]) <= 12 && year >= 1753) {
			printMonth(atoi(argv[2]), year);
			// Replacing [year] with [argv[3]] in the previous line will make crash the code when we provide
			// arguments like [./a.out -m 9 2022], this is because argv[3] is parsed in as 2 instead of 2022
			// for some unknown reasons. I believe the problem lies in the atoi() function
		}
		else {
			printf("Invalid input.");
		}
	}
	else {
		printf("Invalid input. There must be less than 5 arguments.");
	}
	printf("\n");
	return 0;
}
