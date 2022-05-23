//Modify this file to change what commands output to your statusbar, and recompile using the make command.
static const Block blocks[] = {
	/*Icon*/	     /*Command*/		 /*Update Interval*/	/*Update Signal*/
	{"^c#198388^^d^ ", "~/.local/bin/status_ssid",       60,		       8},
	{"^c#198388^^d^ ", "~/.local/bin/.m",	              60,		       1},
	{"^c#198388^^d^ ", "~/.local/bin/status_temp",	       5,		       5},
	{"^c#198388^^d^ ", "~/.local/bin/status_fan",	       5,		      13},
	{"^c#198388^^d^ ", "~/.local/bin/status_cpu",	       5,		       2},
	{"^c#198388^^d^ ", "~/.local/bin/status_mem",	       5,	               3},
	{"^c#198388^^d^ ", "~/.local/bin/status_cons",	       5,		       4},
	{"^c#198388^^d^ ", "~/.local/bin/status_vms",	       5,		       9},
	{"^c#198388^^d^ ", "~/.local/bin/status_disk",	      60,		      11},
	{"^c#198388^^d^ ", "~/.local/bin/status_vol",	       0,		      10},
	{"^c#198388^^d^ ", "~/.local/bin/status_date",	      60,		       6},
	{"^c#198388^^d^ ", "~/.local/bin/status_bat",	      60,		      12},
	{"^c#198388^^d^ ", "~/.local/bin/status_power",       0,		       7},
};

//sets delimeter between status commands. NULL character ('\0') means no delimeter.
static char delim[] = " ";
static unsigned int delimLen = 5;
