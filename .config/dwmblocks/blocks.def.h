//Modify this file to change what commands output to your statusbar, and recompile using the make command.
static const Block blocks[] = {
	/*Icon*/	     /*Command*/		 /*Update Interval*/	/*Update Signal*/
        {"^c#302a5c^[^d^", "",                                      0,                      0},
        {"^c#079096^WiFi^d^", "~/.local/bin/status_ssid",           5,                      5},
        {"^c#302a5c^]^d^", "",                                      0,                      0},
        {"^c#302a5c^[^d^", "",                                      0,                      0},
        {"^c#de1b2f^Mail^d^", "~/.local/bin/status_mail",         120,                      2},
        {"^c#302a5c^]^d^", "",                                      0,                      0},
        {"^c#302a5c^[^d^", "",                                      0,                      0},
        {"^c#8f04ae^Cons^d^", "~/.local/bin/status_cons",           5,                      0},
        {"^c#302a5c^]^d^", "",                                      0,                      0},
        {"^c#302a5c^[^d^", "",                                      0,                      0},
        {"^c#277fff^VMs^d^", "~/.local/bin/status_vms",            5,                      0},
        {"^c#302a5c^]^d^", "",                                      0,                      0},
        {"^c#302a5c^[^d^", "",                                      0,                      0},
        {"^c#0188aa^Temp^d^", "~/.local/bin/status_temp",           5,                      0},
        {"^c#302a5c^]^d^", "",                                      0,                      0},
        {"^c#302a5c^[^d^", "",                                      0,                      0},
        {"^c#ee8109^Mem^d^", "~/.local/bin/status_mem",             5,                      3},
        {"^c#302a5c^]^d^", "",                                      0,                      0},
        {"^c#302a5c^[^d^", "",                                      0,                      0},
        {"^c#277fff^Cpu^d^", "~/.local/bin/status_cpu",             5,                      4},
        {"^c#302a5c^]^d^", "",                                      0,                      0},
        {"^c#302a5c^[^d^", "",                                      0,                      0},
        {"^c#8f04ae^Time^d^", "~/.local/bin/status_date",          60,                      6},
        {"^c#302a5c^]^d^", "",                                      0,                      0},
        {"^c#302a5c^[^d^", "",                                      0,                      0},
        {"^c#de1b2f^Bat^d^", "~/.local/bin/status_bat",            60,                      0},
        {"^c#302a5c^]^d^", "",                                      0,                      0},
};

//sets delimeter between status commands. NULL character ('\0') means no delimeter.
static char delim[] = "";
static unsigned int delimLen = 2;
