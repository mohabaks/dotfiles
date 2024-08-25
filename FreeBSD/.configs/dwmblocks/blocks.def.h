//Modify this file to change what commands output to your statusbar, and recompile using the make command.
static const Block blocks[] = {
	/*Icon*/	     /*Command*/		 /*Update Interval*/	/*Update Signal*/
	{"^c#454545^[^d^", "",	       0,		       0},
	{"^c#ff0000^Temp^d^ ", "~/.local/bin/status_temp",	       5,		       1},
	{"^c#454545^]^d^", "",	       0,		       0},
	{"^c#454545^[^d^", "",	       0,		       0},
	{"^c#ff0000^VMs^d^ ", "~/.local/bin/status_vms",	       5,		       2},
	{"^c#454545^]^d^", "",	       0,		       0},
	{"^c#454545^[^d^", "",	       0,		       0},
	{"^c#ff0000^Time^d^ ", "~/.local/bin/status_date",	      60,		       3},
	{"^c#454545^]^d^", "",	       0,		       0},
	{"^c#454545^[^d^", "",	       0,		       0},
	{"^c#ff0000^Bat^d^ ", "~/.local/bin/status_bat",	      60,		       4},
	{"^c#454545^]^d^", "",	       0,		       0},
};

//sets delimeter between status commands. NULL character ('\0') means no delimeter.
static char delim[] = "";
static unsigned int delimLen = 5;
