NAME:
     cal - displays a calendar

SYNOPSIS:
     cal [[month] year]
     cal -m month [year]

DESCRIPTION:
     The cal utility displays a simple calendar in traditional format.

     The options are as follows:
     
     ./cal
             Display the current month of the current year
      
     ./cal year
             Display the current year
     
     ./cal -m month
             Display the current month (can be in integer or string format) of the current year
     
     ./cal month year
             Display the specified month of the specified year
     
     ./cal -m month year
             Display the specified month (can be in integer or string format) of the specifed year
    

     A single parameter specifies the year (1-9999) to be displayed; note the
     year must be fully specified: "cal 89" will not display a calendar for 1989.
     Two parameters denote the month and year; the month is either a number
     between 1 and 12, or a full or abbreviated name as specified by the current
     locale. Month and year default to those of the current system clock and
     time zone (so "cal -m 8" will display a calendar for the month of August in
     the current year).

     A year starts on January 1.
     
     Note that year must be larger or equal to 1753 because it is the start of
     the Gregorian calendar.

SEE ALSO:
     calendar(3), strftime(3)

HISTORY:
     A cal command appeared in Version 5 AT&T UNIX and later in BSD UNIX.
     The output of the cal command is supposed to be bit for bit compatible to
     the original Unix cal command, because its output is processed by other
     programs like CGI scripts, that should not be broken. Therefore it will
     always output 8 lines, even if only 7 contain data. This extra blank
     line also appears with the original cal command, at least on Solaris 8

AUTHORS:
     phamquoccuong343@gmail.com

BUGS:
     This program can only perform a subset of the BSD cal program.

