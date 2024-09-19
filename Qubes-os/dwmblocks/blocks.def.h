//Modify this file to change what commands output to your statusbar, and recompile using the make command.
static const Block blocks[] = {
	/*Icon*/	     /*Command*/		 /*Update Interval*/	/*Update Signal*/
        {"^c#665c54^[^d^", "",                                      0,                      0},
        {"^c#b8bb26^  ^d^", "~/.local/bin/status_net",            60,                      1},
        {"^c#665c54^]^d^", "",                                      0,                      0},
        {"^c#665c54^[^d^", "",                                      0,                      0},
        {"^c#d65d0e^  ^d^", "~/.local/bin/status_btc",          240,                       2},
        {"^c#665c54^]^d^", "",                                      0,                      0},
        {"^c#665c54^[^d^", "",                                      0,                      0},
        {"^c#b16286^  ^d^", "~/.local/bin/status_tor",             5,                      3},
        {"^c#665c54^]^d^", "",                                      0,                      0},
        {"^c#665c54^[^d^", "",                                      0,                      0},
        {"^c#83a598^  ^d^", "~/.local/bin/status_qube",            5,                      4},
        {"^c#665c54^]^d^", "",                                      0,                      0},
        {"^c#665c54^[^d^", "",                                      0,                      0},
        {"^c#689d6a^ ^d^", "~/.local/bin/status_temp",            5,                      0},
        {"^c#665c54^]^d^", "",                                      0,                      0},
        {"^c#665c54^[^d^", "",                                      0,                      0},
        {"^c#458588^  ^d^", "~/.local/bin/status_mem",             5,                      5},
        {"^c#665c54^]^d^", "",                                      0,                      0},
        {"^c#665c54^[^d^", "",                                      0,                      0},
        {"^c#b16286^  ^d^", "~/.local/bin/status_cpu",             5,                      6},
        {"^c#665c54^]^d^", "",                                      0,                      0},
        {"^c#665c54^[^d^", "",                                      0,                      0},
        {"^c#d79921^  ^d^", "~/.local/bin/status_date",           60,                      7},
        {"^c#665c54^]^d^", "",                                      0,                      0},
        {"^c#665c54^[^d^", "",                                      0,                      0},
        {"^c#cc241d^ ^d^", "~/.local/bin/status_bat",             60,                      0},
        {"^c#665c54^]^d^", "",                                      0,                      0},
};

//sets delimeter between status commands. NULL character ('\0') means no delimeter.
static char delim[] = "";
static unsigned int delimLen = 2;
