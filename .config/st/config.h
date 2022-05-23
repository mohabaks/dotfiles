/* See LICENSE file for copyright and license details. */

/*
 * appearance
 *
 * font: see http://freedesktop.org/software/fontconfig/fontconfig-user.html
 */
static char *font = "tewi:pixelsize=9:antialias=true:autohint=true";
static int borderpx = 2;

/*
 * What program is execed by st depends of these precedence rules:
 * 1: program passed with -e
 * 2: utmp option
 * 3: SHELL environment variable
 * 4: value of shell in /etc/passwd
 * 5: value of shell in config.h
 */
static char *shell = "/bin/sh";
char *utmp = NULL;
char *stty_args = "stty raw pass8 nl -echo -iexten -cstopb 38400";

/* identification sequence returned in DA and DECID */
char *vtiden = "\033[?6c";

/* Kerning / character bounding-box multipliers */
static float cwscale = 1.0;
static float chscale = 1.0;

/*
 * word delimiter string
 *
 * More advanced example: " `'\"()[]{}"
 */
char *worddelimiters = " ";

/* selection timeouts (in milliseconds) */
static unsigned int doubleclicktimeout = 300;
static unsigned int tripleclicktimeout = 600;

/* alt screens */
int allowaltscreen = 1;

/* frames per second st should at maximum draw to the screen */
static unsigned int xfps = 120;
static unsigned int actionfps = 30;

/*
 * blinking timeout (set to 0 to disable blinking) for the terminal blinking
 * attribute.
 */
static unsigned int blinktimeout = 800;

/*
 * thickness of underline and bar cursors
 */
static unsigned int cursorthickness = 2;

/*
 * bell volume. It must be a value between -100 and 100. Use 0 for disabling
 * it
 */
static int bellvolume = 0;

/* default TERM value */
char *termname = "st-256color";

/*
 * spaces per tab
 *
 * When you are changing this value, don't forget to adapt the »it« value in
 * the st.info and appropriately install the st.info in the environment where
 * you use this st version.
 *
 *	it#$tabspaces,
 *
 * Secondly make sure your kernel is not expanding tabs. When running `stty
 * -a` »tab0« should appear. You can tell the terminal to not expand tabs by
 *  running following command:
 *
 *	stty tabs
 */
unsigned int tabspaces = 8;

/* bg opacity */
unsigned int alpha = 0xcc;

/* Terminal colors (16 first used in escape sequence) */
static const char *colorname[] = {

          /* 8 normal colors */
          [0] = "#080808", /* black   */
          [1] = "#aa0017", /* red     */
          [2] = "#865959", /* green   */
          [3] = "#686868", /* yellow  */
          [4] = "#8e8e8e", /* blue    */
          [5] = "#da2121", /* magenta */
          [6] = "#675f5f", /* cyan    */
          [7] = "#b9b9b9", /* white   */

          /* 8 bright colors */
          [8]  = "#404040", /* black   */
          [9]  = "#aa0017", /* red     */
          [10] = "#865959", /* green   */
          [11] = "#686868", /* yellow  */
          [12] = "#8e8e8e", /* blue    */
          [13] = "#da2121", /* magenta */
          [14] = "#675f5f", /* cyan    */
          [15] = "#c9c9c9", /* white   */

          /* special colors */
          [256] = "#000000", /* background */
          [257] = "#b9b9b9", /* foreground */
};

/*
 *  * Default colors (colorname index)
 *   * foreground, background, cursor
 *    */
unsigned int defaultfg = 257;
unsigned int defaultbg = 256;
static unsigned int defaultcs = 257;
static unsigned int defaultrcs = 257;

/*
 *  * Colors used, when the specific fg == defaultfg. So in reverse mode this
 *   * will reverse too. Another logic would only make the simple feature too
 *    * complex.
 *     */
static unsigned int defaultitalic = 7;
static unsigned int defaultunderline = 7;

/*
 * Default shape of cursor
 * 2: Block ("█")
 * 4: Underline ("_")
 * 6: Bar ("|")
 * 7: Snowman ("☃")
 */
static unsigned int cursorshape = 2;

/*
 * Default columns and rows numbers
 */

static unsigned int cols = 80;
static unsigned int rows = 24;

/*
 * Default colour and shape of the mouse cursor
 */
static unsigned int mouseshape = XC_xterm;
static unsigned int mousefg = 7;
static unsigned int mousebg = 0;

/*
 * Color used to display font attributes when fontconfig selected a font which
 * doesn't match the ones requested.
 */
static unsigned int defaultattr = 11;

/*
 * Internal mouse shortcuts.
 * Beware that overloading Button1 will disable the selection.
 */
static MouseShortcut mshortcuts[] = {
	/* button               mask            string */
	{ Button4,              XK_ANY_MOD,     "\031" },
	{ Button5,              XK_ANY_MOD,     "\005" },
};

/* Internal keyboard shortcuts. */
#define MODKEY Mod1Mask
#define TERMMOD (ControlMask|ShiftMask)

static Shortcut shortcuts[] = {
	/* mask                 keysym          function        argument */
	{ XK_ANY_MOD,           XK_Break,       sendbreak,      {.i =  0} },
	{ ControlMask,          XK_Print,       toggleprinter,  {.i =  0} },
	{ ShiftMask,            XK_Print,       printscreen,    {.i =  0} },
	{ XK_ANY_MOD,           XK_Print,       printsel,       {.i =  0} },
	{ TERMMOD,              XK_Prior,       zoom,           {.f = +1} },
	{ TERMMOD,              XK_Next,        zoom,           {.f = -1} },
	{ TERMMOD,              XK_Home,        zoomreset,      {.f =  0} },
	{ TERMMOD,              XK_C,           clipcopy,       {.i =  0} },
	{ TERMMOD,              XK_V,           clippaste,      {.i =  0} },
	{ TERMMOD,              XK_Y,           selpaste,       {.i =  0} },
	{ TERMMOD,              XK_Num_Lock,    numlock,        {.i =  0} },
};

/*
 * Special keys (change & recompile st.info accordingly)
 *
 * Mask value:
 * * Use XK_ANY_MOD to match the key no matter modifiers state
 * * Use XK_NO_MOD to match the key alone (no modifiers)
 * appkey value:
 * * 0: no value
 * * > 0: keypad application mode enabled
 * *   = 2: term.numlock = 1
 * * < 0: keypad application mode disabled
 * appcursor value:
 * * 0: no value
 * * > 0: cursor application mode enabled
 * * < 0: cursor application mode disabled
 * crlf value
 * * 0: no value
 * * > 0: crlf mode is enabled
 * * < 0: crlf mode is disabled
 *
 * Be careful with the order of the definitions because st searches in
 * this table sequentially, so any XK_ANY_MOD must be in the last
 * position for a key.
 */

/*
 * If you want keys other than the X11 function keys (0xFD00 - 0xFFFF)
 * to be mapped below, add them to this array.
 */
static KeySym mappedkeys[] = {
	XK_space,
	XK_m,
	XK_i,
	XK_A,
	XK_B,
	XK_C,
	XK_D,
	XK_E,
	XK_F,
	XK_G,
	XK_H,
	XK_I,
	XK_K,
	XK_J,
	XK_L,
	XK_M,
	XK_N,
	XK_O,
	XK_P,
	XK_Q,
	XK_R,
	XK_S,
	XK_T,
	XK_U,
	XK_V,
	XK_W,
	XK_X,
	XK_Y,
	XK_Z,
	XK_Z,
	XK_0,
	XK_1,
	XK_2,
	XK_3,
	XK_4,
	XK_5,
	XK_6,
	XK_7,
	XK_8,
	XK_9,
	XK_exclam,
	XK_quotedbl,
	XK_numbersign,
	XK_dollar,
	XK_percent,
	XK_ampersand,
	XK_apostrophe,
	XK_parenleft,
	XK_parenright,
	XK_asterisk,
	XK_plus,
	XK_comma,
	XK_minus,
	XK_period,
	XK_slash,
	XK_colon,
	XK_semicolon,
	XK_less,
	XK_equal,
	XK_greater,
	XK_question,
	XK_at,
	XK_bracketleft,
	XK_backslash,
	XK_bracketright,
	XK_asciicircum,
	XK_underscore,
	XK_grave,
	XK_braceleft,
	XK_bar,
	XK_braceright,
	XK_asciitilde,
};

/*
 * State bits to ignore when matching key or button events.  By default,
 * numlock (Mod2Mask) and keyboard layout (XK_SWITCH_MOD) are ignored.
 */
static uint ignoremod = Mod2Mask|XK_SWITCH_MOD;

/*
 * Override mouse-select while mask is active (when MODE_MOUSE is set).
 * Note that if you want to use ShiftMask with selmasks, set this to an other
 * modifier, set to 0 to not use it.
 */
static uint forceselmod = ShiftMask;

/*
 * This is the huge key array which defines all compatibility to the Linux
 * world. Please decide about changes wisely.
 */
static Key key[] = {
	/* keysym           mask            string      appkey appcursor */
	{ XK_KP_Home,       ShiftMask,      "\033[2J",       0,   -1},
	{ XK_KP_Home,       ShiftMask,      "\033[1;2H",     0,   +1},
	{ XK_KP_Prior,      ShiftMask,      "\033[5;2~",     0,    0},
	{ XK_KP_End,        ControlMask,    "\033[J",       -1,    0},
	{ XK_KP_End,        ControlMask,    "\033[1;5F",    +1,    0},
	{ XK_KP_End,        ShiftMask,      "\033[K",       -1,    0},
	{ XK_KP_End,        ShiftMask,      "\033[1;2F",    +1,    0},
	{ XK_KP_Next,       ShiftMask,      "\033[6;2~",     0,    0},
	{ XK_KP_Insert,     ShiftMask,      "\033[2;2~",    +1,    0},
	{ XK_KP_Insert,     ShiftMask,      "\033[4l",      -1,    0},
	{ XK_KP_Insert,     ControlMask,    "\033[L",       -1,    0},
	{ XK_KP_Insert,     ControlMask,    "\033[2;5~",    +1,    0},
	{ XK_KP_Delete,     ControlMask,    "\033[M",       -1,    0},
	{ XK_KP_Delete,     ControlMask,    "\033[3;5~",    +1,    0},
	{ XK_KP_Delete,     ShiftMask,      "\033[2K",      -1,    0},
	{ XK_KP_Delete,     ShiftMask,      "\033[3;2~",    +1,    0},
	{ XK_Up,            ShiftMask,      "\033[1;2A",     0,    0},
	{ XK_Up,            Mod1Mask,       "\033[1;3A",     0,    0},
	{ XK_Up,         ShiftMask|Mod1Mask,"\033[1;4A",     0,    0},
	{ XK_Up,            ControlMask,    "\033[1;5A",     0,    0},
	{ XK_Up,      ShiftMask|ControlMask,"\033[1;6A",     0,    0},
	{ XK_Up,       ControlMask|Mod1Mask,"\033[1;7A",     0,    0},
	{ XK_Up,ShiftMask|ControlMask|Mod1Mask,"\033[1;8A",  0,    0},
	{ XK_Up,            XK_ANY_MOD,     "\033[A",        0,   -1},
	{ XK_Up,            XK_ANY_MOD,     "\033OA",        0,   +1},
	{ XK_Down,          ShiftMask,      "\033[1;2B",     0,    0},
	{ XK_Down,          Mod1Mask,       "\033[1;3B",     0,    0},
	{ XK_Down,       ShiftMask|Mod1Mask,"\033[1;4B",     0,    0},
	{ XK_Down,          ControlMask,    "\033[1;5B",     0,    0},
	{ XK_Down,    ShiftMask|ControlMask,"\033[1;6B",     0,    0},
	{ XK_Down,     ControlMask|Mod1Mask,"\033[1;7B",     0,    0},
	{ XK_Down,ShiftMask|ControlMask|Mod1Mask,"\033[1;8B",0,    0},
	{ XK_Down,          XK_ANY_MOD,     "\033[B",        0,   -1},
	{ XK_Down,          XK_ANY_MOD,     "\033OB",        0,   +1},
	{ XK_Left,          ShiftMask,      "\033[1;2D",     0,    0},
	{ XK_Left,          Mod1Mask,       "\033[1;3D",     0,    0},
	{ XK_Left,       ShiftMask|Mod1Mask,"\033[1;4D",     0,    0},
	{ XK_Left,          ControlMask,    "\033[1;5D",     0,    0},
	{ XK_Left,    ShiftMask|ControlMask,"\033[1;6D",     0,    0},
	{ XK_Left,     ControlMask|Mod1Mask,"\033[1;7D",     0,    0},
	{ XK_Left,ShiftMask|ControlMask|Mod1Mask,"\033[1;8D",0,    0},
	{ XK_Left,          XK_ANY_MOD,     "\033[D",        0,   -1},
	{ XK_Left,          XK_ANY_MOD,     "\033OD",        0,   +1},
	{ XK_Right,         ShiftMask,      "\033[1;2C",     0,    0},
	{ XK_Right,         Mod1Mask,       "\033[1;3C",     0,    0},
	{ XK_Right,      ShiftMask|Mod1Mask,"\033[1;4C",     0,    0},
	{ XK_Right,         ControlMask,    "\033[1;5C",     0,    0},
	{ XK_Right,   ShiftMask|ControlMask,"\033[1;6C",     0,    0},
	{ XK_Right,    ControlMask|Mod1Mask,"\033[1;7C",     0,    0},
	{ XK_Right,ShiftMask|ControlMask|Mod1Mask,"\033[1;8C",0,   0},
	{ XK_Right,         XK_ANY_MOD,     "\033[C",        0,   -1},
	{ XK_Right,         XK_ANY_MOD,     "\033OC",        0,   +1},
	{ XK_ISO_Left_Tab,  ShiftMask,      "\033[Z",        0,    0},
	{ XK_Return,        Mod1Mask,       "\033\r",        0,    0},
	{ XK_Return,        XK_NO_MOD,      "\r",            0,    0},
	{ XK_Insert,        ShiftMask,      "\033[4l",      -1,    0},
	{ XK_Insert,        ShiftMask,      "\033[2;2~",    +1,    0},
	{ XK_Insert,        ControlMask,    "\033[L",       -1,    0},
	{ XK_Insert,        ControlMask,    "\033[2;5~",    +1,    0},
	{ XK_Delete,        ControlMask,    "\033[M",       -1,    0},
	{ XK_Delete,        ControlMask,    "\033[3;5~",    +1,    0},
	{ XK_Delete,        ShiftMask,      "\033[2K",      -1,    0},
	{ XK_Delete,        ShiftMask,      "\033[3;2~",    +1,    0},
	{ XK_BackSpace,     XK_NO_MOD,      "\177",          0,    0},
	{ XK_BackSpace,     Mod1Mask,       "\033\177",      0,    0},
	{ XK_Home,          ShiftMask,      "\033[2J",       0,   -1},
	{ XK_Home,          ShiftMask,      "\033[1;2H",     0,   +1},
	{ XK_End,           ControlMask,    "\033[J",       -1,    0},
	{ XK_End,           ControlMask,    "\033[1;5F",    +1,    0},
	{ XK_End,           ShiftMask,      "\033[K",       -1,    0},
	{ XK_End,           ShiftMask,      "\033[1;2F",    +1,    0},
	{ XK_Prior,         ControlMask,    "\033[5;5~",     0,    0},
	{ XK_Prior,         ShiftMask,      "\033[5;2~",     0,    0},
	{ XK_Next,          ControlMask,    "\033[6;5~",     0,    0},
	{ XK_Next,          ShiftMask,      "\033[6;2~",     0,    0},
	{ XK_F1,            XK_NO_MOD,      "\033OP" ,       0,    0},
	{ XK_F1, /* F13 */  ShiftMask,      "\033[1;2P",     0,    0},
	{ XK_F1, /* F25 */  ControlMask,    "\033[1;5P",     0,    0},
	{ XK_F1, /* F37 */  Mod4Mask,       "\033[1;6P",     0,    0},
	{ XK_F1, /* F49 */  Mod1Mask,       "\033[1;3P",     0,    0},
	{ XK_F1, /* F61 */  Mod3Mask,       "\033[1;4P",     0,    0},
	{ XK_F2,            XK_NO_MOD,      "\033OQ" ,       0,    0},
	{ XK_F2, /* F14 */  ShiftMask,      "\033[1;2Q",     0,    0},
	{ XK_F2, /* F26 */  ControlMask,    "\033[1;5Q",     0,    0},
	{ XK_F2, /* F38 */  Mod4Mask,       "\033[1;6Q",     0,    0},
	{ XK_F2, /* F50 */  Mod1Mask,       "\033[1;3Q",     0,    0},
	{ XK_F2, /* F62 */  Mod3Mask,       "\033[1;4Q",     0,    0},
	{ XK_F3,            XK_NO_MOD,      "\033OR" ,       0,    0},
	{ XK_F3, /* F15 */  ShiftMask,      "\033[1;2R",     0,    0},
	{ XK_F3, /* F27 */  ControlMask,    "\033[1;5R",     0,    0},
	{ XK_F3, /* F39 */  Mod4Mask,       "\033[1;6R",     0,    0},
	{ XK_F3, /* F51 */  Mod1Mask,       "\033[1;3R",     0,    0},
	{ XK_F3, /* F63 */  Mod3Mask,       "\033[1;4R",     0,    0},
	{ XK_F4,            XK_NO_MOD,      "\033OS" ,       0,    0},
	{ XK_F4, /* F16 */  ShiftMask,      "\033[1;2S",     0,    0},
	{ XK_F4, /* F28 */  ControlMask,    "\033[1;5S",     0,    0},
	{ XK_F4, /* F40 */  Mod4Mask,       "\033[1;6S",     0,    0},
	{ XK_F4, /* F52 */  Mod1Mask,       "\033[1;3S",     0,    0},
	{ XK_F5,            XK_NO_MOD,      "\033[15~",      0,    0},
	{ XK_F5, /* F17 */  ShiftMask,      "\033[15;2~",    0,    0},
	{ XK_F5, /* F29 */  ControlMask,    "\033[15;5~",    0,    0},
	{ XK_F5, /* F41 */  Mod4Mask,       "\033[15;6~",    0,    0},
	{ XK_F5, /* F53 */  Mod1Mask,       "\033[15;3~",    0,    0},
	{ XK_F6,            XK_NO_MOD,      "\033[17~",      0,    0},
	{ XK_F6, /* F18 */  ShiftMask,      "\033[17;2~",    0,    0},
	{ XK_F6, /* F30 */  ControlMask,    "\033[17;5~",    0,    0},
	{ XK_F6, /* F42 */  Mod4Mask,       "\033[17;6~",    0,    0},
	{ XK_F6, /* F54 */  Mod1Mask,       "\033[17;3~",    0,    0},
	{ XK_F7,            XK_NO_MOD,      "\033[18~",      0,    0},
	{ XK_F7, /* F19 */  ShiftMask,      "\033[18;2~",    0,    0},
	{ XK_F7, /* F31 */  ControlMask,    "\033[18;5~",    0,    0},
	{ XK_F7, /* F43 */  Mod4Mask,       "\033[18;6~",    0,    0},
	{ XK_F7, /* F55 */  Mod1Mask,       "\033[18;3~",    0,    0},
	{ XK_F8,            XK_NO_MOD,      "\033[19~",      0,    0},
	{ XK_F8, /* F20 */  ShiftMask,      "\033[19;2~",    0,    0},
	{ XK_F8, /* F32 */  ControlMask,    "\033[19;5~",    0,    0},
	{ XK_F8, /* F44 */  Mod4Mask,       "\033[19;6~",    0,    0},
	{ XK_F8, /* F56 */  Mod1Mask,       "\033[19;3~",    0,    0},
	{ XK_F9,            XK_NO_MOD,      "\033[20~",      0,    0},
	{ XK_F9, /* F21 */  ShiftMask,      "\033[20;2~",    0,    0},
	{ XK_F9, /* F33 */  ControlMask,    "\033[20;5~",    0,    0},
	{ XK_F9, /* F45 */  Mod4Mask,       "\033[20;6~",    0,    0},
	{ XK_F9, /* F57 */  Mod1Mask,       "\033[20;3~",    0,    0},
	{ XK_F10,           XK_NO_MOD,      "\033[21~",      0,    0},
	{ XK_F10, /* F22 */ ShiftMask,      "\033[21;2~",    0,    0},
	{ XK_F10, /* F34 */ ControlMask,    "\033[21;5~",    0,    0},
	{ XK_F10, /* F46 */ Mod4Mask,       "\033[21;6~",    0,    0},
	{ XK_F10, /* F58 */ Mod1Mask,       "\033[21;3~",    0,    0},
	{ XK_F11,           XK_NO_MOD,      "\033[23~",      0,    0},
	{ XK_F11, /* F23 */ ShiftMask,      "\033[23;2~",    0,    0},
	{ XK_F11, /* F35 */ ControlMask,    "\033[23;5~",    0,    0},
	{ XK_F11, /* F47 */ Mod4Mask,       "\033[23;6~",    0,    0},
	{ XK_F11, /* F59 */ Mod1Mask,       "\033[23;3~",    0,    0},
	{ XK_F12,           XK_NO_MOD,      "\033[24~",      0,    0},
	{ XK_F12, /* F24 */ ShiftMask,      "\033[24;2~",    0,    0},
	{ XK_F12, /* F36 */ ControlMask,    "\033[24;5~",    0,    0},
	{ XK_F12, /* F48 */ Mod4Mask,       "\033[24;6~",    0,    0},
	{ XK_F12, /* F60 */ Mod1Mask,       "\033[24;3~",    0,    0},
	{ XK_F13,           XK_NO_MOD,      "\033[1;2P",     0,    0},
	{ XK_F14,           XK_NO_MOD,      "\033[1;2Q",     0,    0},
	{ XK_F15,           XK_NO_MOD,      "\033[1;2R",     0,    0},
	{ XK_F16,           XK_NO_MOD,      "\033[1;2S",     0,    0},
	{ XK_F17,           XK_NO_MOD,      "\033[15;2~",    0,    0},
	{ XK_F18,           XK_NO_MOD,      "\033[17;2~",    0,    0},
	{ XK_F19,           XK_NO_MOD,      "\033[18;2~",    0,    0},
	{ XK_F20,           XK_NO_MOD,      "\033[19;2~",    0,    0},
	{ XK_F21,           XK_NO_MOD,      "\033[20;2~",    0,    0},
	{ XK_F22,           XK_NO_MOD,      "\033[21;2~",    0,    0},
	{ XK_F23,           XK_NO_MOD,      "\033[23;2~",    0,    0},
	{ XK_F24,           XK_NO_MOD,      "\033[24;2~",    0,    0},
	{ XK_F25,           XK_NO_MOD,      "\033[1;5P",     0,    0},
	{ XK_F26,           XK_NO_MOD,      "\033[1;5Q",     0,    0},
	{ XK_F27,           XK_NO_MOD,      "\033[1;5R",     0,    0},
	{ XK_F28,           XK_NO_MOD,      "\033[1;5S",     0,    0},
	{ XK_F29,           XK_NO_MOD,      "\033[15;5~",    0,    0},
	{ XK_F30,           XK_NO_MOD,      "\033[17;5~",    0,    0},
	{ XK_F31,           XK_NO_MOD,      "\033[18;5~",    0,    0},
	{ XK_F32,           XK_NO_MOD,      "\033[19;5~",    0,    0},
	{ XK_F33,           XK_NO_MOD,      "\033[20;5~",    0,    0},
	{ XK_F34,           XK_NO_MOD,      "\033[21;5~",    0,    0},
	{ XK_F35,           XK_NO_MOD,      "\033[23;5~",    0,    0},

	// libtermkey compatible keyboard input
	{ XK_KP_Home,      XK_NO_MOD,                      "\033[H",      0, -1},
	{ XK_KP_Home,      XK_NO_MOD,                      "\033[1~",     0, +1},
	{ XK_KP_Home,      ControlMask,                    "\033[149;5u", 0,  0},
	{ XK_KP_Home,      ControlMask|ShiftMask,          "\033[149;6u", 0,  0},
	{ XK_KP_Home,      Mod1Mask,                       "\033[149;3u", 0,  0},
	{ XK_KP_Home,      Mod1Mask|ControlMask,           "\033[149;7u", 0,  0},
	{ XK_KP_Home,      Mod1Mask|ControlMask|ShiftMask, "\033[149;8u", 0,  0},
	{ XK_KP_Home,      Mod1Mask|ShiftMask,             "\033[149;4u", 0,  0},
	{ XK_KP_Home,      ShiftMask,                      "\033[149;2u", 0,  0},
	{ XK_KP_Up,        XK_NO_MOD,                      "\033Ox",     +1,  0},
	{ XK_KP_Up,        XK_NO_MOD,                      "\033[A",      0, -1},
	{ XK_KP_Up,        XK_NO_MOD,                      "\033OA",      0, +1},
	{ XK_KP_Up,        ControlMask,                    "\033[151;5u", 0,  0},
	{ XK_KP_Up,        ControlMask|ShiftMask,          "\033[151;6u", 0,  0},
	{ XK_KP_Up,        Mod1Mask,                       "\033[151;3u", 0,  0},
	{ XK_KP_Up,        Mod1Mask|ControlMask,           "\033[151;7u", 0,  0},
	{ XK_KP_Up,        Mod1Mask|ControlMask|ShiftMask, "\033[151;8u", 0,  0},
	{ XK_KP_Up,        Mod1Mask|ShiftMask,             "\033[151;4u", 0,  0},
	{ XK_KP_Up,        ShiftMask,                      "\033[151;2u", 0,  0},
	{ XK_KP_Down,      XK_NO_MOD,                      "\033Or",     +1,  0},
	{ XK_KP_Down,      XK_NO_MOD,                      "\033[B",      0, -1},
	{ XK_KP_Down,      XK_NO_MOD,                      "\033OB",      0, +1},
	{ XK_KP_Down,      ControlMask,                    "\033[153;5u", 0,  0},
	{ XK_KP_Down,      ControlMask|ShiftMask,          "\033[153;6u", 0,  0},
	{ XK_KP_Down,      Mod1Mask,                       "\033[153;3u", 0,  0},
	{ XK_KP_Down,      Mod1Mask|ControlMask,           "\033[153;7u", 0,  0},
	{ XK_KP_Down,      Mod1Mask|ControlMask|ShiftMask, "\033[153;8u", 0,  0},
	{ XK_KP_Down,      Mod1Mask|ShiftMask,             "\033[153;4u", 0,  0},
	{ XK_KP_Down,      ShiftMask,                      "\033[153;2u", 0,  0},
	{ XK_KP_Left,      XK_NO_MOD,                      "\033Ot",     +1,  0},
	{ XK_KP_Left,      XK_NO_MOD,                      "\033[D",      0, -1},
	{ XK_KP_Left,      XK_NO_MOD,                      "\033OD",      0, +1},
	{ XK_KP_Left,      ControlMask,                    "\033[150;5u", 0,  0},
	{ XK_KP_Left,      ControlMask|ShiftMask,          "\033[150;6u", 0,  0},
	{ XK_KP_Left,      Mod1Mask,                       "\033[150;3u", 0,  0},
	{ XK_KP_Left,      Mod1Mask|ControlMask,           "\033[150;7u", 0,  0},
	{ XK_KP_Left,      Mod1Mask|ControlMask|ShiftMask, "\033[150;8u", 0,  0},
	{ XK_KP_Left,      Mod1Mask|ShiftMask,             "\033[150;4u", 0,  0},
	{ XK_KP_Left,      ShiftMask,                      "\033[150;2u", 0,  0},
	{ XK_KP_Right,     XK_NO_MOD,                      "\033Ov",     +1,  0},
	{ XK_KP_Right,     XK_NO_MOD,                      "\033[C",      0, -1},
	{ XK_KP_Right,     XK_NO_MOD,                      "\033OC",      0, +1},
	{ XK_KP_Right,     ControlMask,                    "\033[152;5u", 0,  0},
	{ XK_KP_Right,     ControlMask|ShiftMask,          "\033[152;6u", 0,  0},
	{ XK_KP_Right,     Mod1Mask,                       "\033[152;3u", 0,  0},
	{ XK_KP_Right,     Mod1Mask|ControlMask,           "\033[152;7u", 0,  0},
	{ XK_KP_Right,     Mod1Mask|ControlMask|ShiftMask, "\033[152;8u", 0,  0},
	{ XK_KP_Right,     Mod1Mask|ShiftMask,             "\033[152;4u", 0,  0},
	{ XK_KP_Right,     ShiftMask,                      "\033[152;2u", 0,  0},
	{ XK_KP_Prior,     XK_NO_MOD,                      "\033[5~",     0,  0},
	{ XK_KP_Prior,     ControlMask,                    "\033[154;5u", 0,  0},
	{ XK_KP_Prior,     ControlMask|ShiftMask,          "\033[154;6u", 0,  0},
	{ XK_KP_Prior,     Mod1Mask,                       "\033[154;3u", 0,  0},
	{ XK_KP_Prior,     Mod1Mask|ControlMask,           "\033[154;7u", 0,  0},
	{ XK_KP_Prior,     Mod1Mask|ControlMask|ShiftMask, "\033[154;8u", 0,  0},
	{ XK_KP_Prior,     Mod1Mask|ShiftMask,             "\033[154;4u", 0,  0},
	{ XK_KP_Begin,     XK_NO_MOD,                      "\033[E",      0,  0},
	{ XK_KP_Begin,     ControlMask,                    "\033[157;5u", 0,  0},
	{ XK_KP_Begin,     ControlMask|ShiftMask,          "\033[157;6u", 0,  0},
	{ XK_KP_Begin,     Mod1Mask,                       "\033[157;3u", 0,  0},
	{ XK_KP_Begin,     Mod1Mask|ControlMask,           "\033[157;7u", 0,  0},
	{ XK_KP_Begin,     Mod1Mask|ControlMask|ShiftMask, "\033[157;8u", 0,  0},
	{ XK_KP_Begin,     Mod1Mask|ShiftMask,             "\033[157;4u", 0,  0},
	{ XK_KP_Begin,     ShiftMask,                      "\033[157;2u", 0,  0},
	{ XK_KP_End,       XK_NO_MOD,                      "\033[4~",     0,  0},
	{ XK_KP_End,       ControlMask|ShiftMask,          "\033[156;6u", 0,  0},
	{ XK_KP_End,       Mod1Mask,                       "\033[156;3u", 0,  0},
	{ XK_KP_End,       Mod1Mask|ControlMask,           "\033[156;7u", 0,  0},
	{ XK_KP_End,       Mod1Mask|ControlMask|ShiftMask, "\033[156;8u", 0,  0},
	{ XK_KP_End,       Mod1Mask|ShiftMask,             "\033[156;4u", 0,  0},
	{ XK_KP_Next,      XK_NO_MOD,                      "\033[6~",     0,  0},
	{ XK_KP_Next,      ControlMask,                    "\033[155;5u", 0,  0},
	{ XK_KP_Next,      ControlMask|ShiftMask,          "\033[155;6u", 0,  0},
	{ XK_KP_Next,      Mod1Mask,                       "\033[155;3u", 0,  0},
	{ XK_KP_Next,      Mod1Mask|ControlMask,           "\033[155;7u", 0,  0},
	{ XK_KP_Next,      Mod1Mask|ControlMask|ShiftMask, "\033[155;8u", 0,  0},
	{ XK_KP_Next,      Mod1Mask|ShiftMask,             "\033[155;4u", 0,  0},
	{ XK_KP_Insert,    XK_NO_MOD,                      "\033[4h",    -1,  0},
	{ XK_KP_Insert,    XK_NO_MOD,                      "\033[2~",    +1,  0},
	{ XK_KP_Insert,    ControlMask|ShiftMask,          "\033[158;6u", 0,  0},
	{ XK_KP_Insert,    Mod1Mask,                       "\033[158;3u", 0,  0},
	{ XK_KP_Insert,    Mod1Mask|ControlMask,           "\033[158;7u", 0,  0},
	{ XK_KP_Insert,    Mod1Mask|ControlMask|ShiftMask, "\033[158;8u", 0,  0},
	{ XK_KP_Insert,    Mod1Mask|ShiftMask,             "\033[158;4u", 0,  0},
	{ XK_KP_Delete,    XK_NO_MOD,                      "\033[P",     -1,  0},
	{ XK_KP_Delete,    XK_NO_MOD,                      "\033[3~",    +1,  0},
	{ XK_KP_Delete,    ControlMask|ShiftMask,          "\033[159;6u", 0,  0},
	{ XK_KP_Delete,    Mod1Mask,                       "\033[159;3u", 0,  0},
	{ XK_KP_Delete,    Mod1Mask|ControlMask,           "\033[159;7u", 0,  0},
	{ XK_KP_Delete,    Mod1Mask|ControlMask|ShiftMask, "\033[159;8u", 0,  0},
	{ XK_KP_Delete,    Mod1Mask|ShiftMask,             "\033[159;4u", 0,  0},
	{ XK_KP_Multiply,  XK_NO_MOD,                      "\033Oj",     +2,  0},
	{ XK_KP_Multiply,  ControlMask,                    "\033[170;5u", 0,  0},
	{ XK_KP_Multiply,  ControlMask|ShiftMask,          "\033[170;6u", 0,  0},
	{ XK_KP_Multiply,  Mod1Mask,                       "\033[170;3u", 0,  0},
	{ XK_KP_Multiply,  Mod1Mask|ControlMask,           "\033[170;7u", 0,  0},
	{ XK_KP_Multiply,  Mod1Mask|ControlMask|ShiftMask, "\033[170;8u", 0,  0},
	{ XK_KP_Multiply,  Mod1Mask|ShiftMask,             "\033[170;4u", 0,  0},
	{ XK_KP_Multiply,  ShiftMask,                      "\033[170;2u", 0,  0},
	{ XK_KP_Add,       XK_NO_MOD,                      "\033Ok",     +2,  0},
	{ XK_KP_Add,       ControlMask,                    "\033[171;5u", 0,  0},
	{ XK_KP_Add,       ControlMask|ShiftMask,          "\033[171;6u", 0,  0},
	{ XK_KP_Add,       Mod1Mask,                       "\033[171;3u", 0,  0},
	{ XK_KP_Add,       Mod1Mask|ControlMask,           "\033[171;7u", 0,  0},
	{ XK_KP_Add,       Mod1Mask|ControlMask|ShiftMask, "\033[171;8u", 0,  0},
	{ XK_KP_Add,       Mod1Mask|ShiftMask,             "\033[171;4u", 0,  0},
	{ XK_KP_Add,       ShiftMask,                      "\033[171;2u", 0,  0},
	{ XK_KP_Enter,     XK_NO_MOD,                      "\033OM",     +2,  0},
	{ XK_KP_Enter,     XK_NO_MOD,                      "\r",         -1,  0},
	{ XK_KP_Enter,     XK_NO_MOD,                      "\r\n",       -1,  0},
	{ XK_KP_Enter,     ControlMask,                    "\033[141;5u", 0,  0},
	{ XK_KP_Enter,     ControlMask|ShiftMask,          "\033[141;6u", 0,  0},
	{ XK_KP_Enter,     Mod1Mask,                       "\033[141;3u", 0,  0},
	{ XK_KP_Enter,     Mod1Mask|ControlMask,           "\033[141;7u", 0,  0},
	{ XK_KP_Enter,     Mod1Mask|ControlMask|ShiftMask, "\033[141;8u", 0,  0},
	{ XK_KP_Enter,     Mod1Mask|ShiftMask,             "\033[141;4u", 0,  0},
	{ XK_KP_Enter,     ShiftMask,                      "\033[141;2u", 0,  0},
	{ XK_KP_Subtract,  XK_NO_MOD,                      "\033Om",     +2,  0},
	{ XK_KP_Subtract,  ControlMask,                    "\033[173;5u", 0,  0},
	{ XK_KP_Subtract,  ControlMask|ShiftMask,          "\033[173;6u", 0,  0},
	{ XK_KP_Subtract,  Mod1Mask,                       "\033[173;3u", 0,  0},
	{ XK_KP_Subtract,  Mod1Mask|ControlMask,           "\033[173;7u", 0,  0},
	{ XK_KP_Subtract,  Mod1Mask|ControlMask|ShiftMask, "\033[173;8u", 0,  0},
	{ XK_KP_Subtract,  Mod1Mask|ShiftMask,             "\033[173;4u", 0,  0},
	{ XK_KP_Subtract,  ShiftMask,                      "\033[173;2u", 0,  0},
	{ XK_KP_Decimal,   XK_NO_MOD,                      "\033On",     +2,  0},
	{ XK_KP_Decimal,   ControlMask,                    "\033[174;5u", 0,  0},
	{ XK_KP_Decimal,   ControlMask|ShiftMask,          "\033[174;6u", 0,  0},
	{ XK_KP_Decimal,   Mod1Mask,                       "\033[174;3u", 0,  0},
	{ XK_KP_Decimal,   Mod1Mask|ControlMask,           "\033[174;7u", 0,  0},
	{ XK_KP_Decimal,   Mod1Mask|ControlMask|ShiftMask, "\033[174;8u", 0,  0},
	{ XK_KP_Decimal,   Mod1Mask|ShiftMask,             "\033[174;4u", 0,  0},
	{ XK_KP_Decimal,   ShiftMask,                      "\033[174;2u", 0,  0},
	{ XK_KP_Divide,    XK_NO_MOD,                      "\033Oo",     +2,  0},
	{ XK_KP_Divide,    ControlMask,                    "\033[175;5u", 0,  0},
	{ XK_KP_Divide,    ControlMask|ShiftMask,          "\033[175;6u", 0,  0},
	{ XK_KP_Divide,    Mod1Mask,                       "\033[175;3u", 0,  0},
	{ XK_KP_Divide,    Mod1Mask|ControlMask,           "\033[175;7u", 0,  0},
	{ XK_KP_Divide,    Mod1Mask|ControlMask|ShiftMask, "\033[175;8u", 0,  0},
	{ XK_KP_Divide,    Mod1Mask|ShiftMask,             "\033[175;4u", 0,  0},
	{ XK_KP_Divide,    ShiftMask,                      "\033[175;2u", 0,  0},
	{ XK_KP_0,         XK_NO_MOD,                      "\033Op",     +2,  0},
	{ XK_KP_0,         ControlMask,                    "\033[176;5u", 0,  0},
	{ XK_KP_0,         ControlMask|ShiftMask,          "\033[176;6u", 0,  0},
	{ XK_KP_0,         Mod1Mask,                       "\033[176;3u", 0,  0},
	{ XK_KP_0,         Mod1Mask|ControlMask,           "\033[176;7u", 0,  0},
	{ XK_KP_0,         Mod1Mask|ControlMask|ShiftMask, "\033[176;8u", 0,  0},
	{ XK_KP_0,         Mod1Mask|ShiftMask,             "\033[176;4u", 0,  0},
	{ XK_KP_0,         ShiftMask,                      "\033[176;2u", 0,  0},
	{ XK_KP_1,         XK_NO_MOD,                      "\033Oq",     +2,  0},
	{ XK_KP_0,         ControlMask,                    "\033[177;5u", 0,  0},
	{ XK_KP_0,         ControlMask|ShiftMask,          "\033[177;6u", 0,  0},
	{ XK_KP_0,         Mod1Mask,                       "\033[177;3u", 0,  0},
	{ XK_KP_0,         Mod1Mask|ControlMask,           "\033[177;7u", 0,  0},
	{ XK_KP_0,         Mod1Mask|ControlMask|ShiftMask, "\033[177;8u", 0,  0},
	{ XK_KP_0,         Mod1Mask|ShiftMask,             "\033[177;4u", 0,  0},
	{ XK_KP_0,         ShiftMask,                      "\033[177;2u", 0,  0},
	{ XK_KP_2,         XK_NO_MOD,                      "\033Or",     +2,  0},
	{ XK_KP_2,         ControlMask,                    "\033[178;5u", 0,  0},
	{ XK_KP_2,         ControlMask|ShiftMask,          "\033[178;6u", 0,  0},
	{ XK_KP_2,         Mod1Mask,                       "\033[178;3u", 0,  0},
	{ XK_KP_2,         Mod1Mask|ControlMask,           "\033[178;7u", 0,  0},
	{ XK_KP_2,         Mod1Mask|ControlMask|ShiftMask, "\033[178;8u", 0,  0},
	{ XK_KP_2,         Mod1Mask|ShiftMask,             "\033[178;4u", 0,  0},
	{ XK_KP_2,         ShiftMask,                      "\033[178;2u", 0,  0},
	{ XK_KP_3,         XK_NO_MOD,                      "\033Os",     +2,  0},
	{ XK_KP_3,         ControlMask,                    "\033[179;5u", 0,  0},
	{ XK_KP_3,         ControlMask|ShiftMask,          "\033[179;6u", 0,  0},
	{ XK_KP_3,         Mod1Mask,                       "\033[179;3u", 0,  0},
	{ XK_KP_3,         Mod1Mask|ControlMask,           "\033[179;7u", 0,  0},
	{ XK_KP_3,         Mod1Mask|ControlMask|ShiftMask, "\033[179;8u", 0,  0},
	{ XK_KP_3,         Mod1Mask|ShiftMask,             "\033[179;4u", 0,  0},
	{ XK_KP_3,         ShiftMask,                      "\033[179;2u", 0,  0},
	{ XK_KP_4,         XK_NO_MOD,                      "\033Ot",     +2,  0},
	{ XK_KP_4,         ControlMask,                    "\033[180;5u", 0,  0},
	{ XK_KP_4,         ControlMask|ShiftMask,          "\033[180;6u", 0,  0},
	{ XK_KP_4,         Mod1Mask,                       "\033[180;3u", 0,  0},
	{ XK_KP_4,         Mod1Mask|ControlMask,           "\033[180;7u", 0,  0},
	{ XK_KP_4,         Mod1Mask|ControlMask|ShiftMask, "\033[180;8u", 0,  0},
	{ XK_KP_4,         Mod1Mask|ShiftMask,             "\033[180;4u", 0,  0},
	{ XK_KP_4,         ShiftMask,                      "\033[180;2u", 0,  0},
	{ XK_KP_5,         XK_NO_MOD,                      "\033Ou",     +2,  0},
	{ XK_KP_5,         ControlMask,                    "\033[181;5u", 0,  0},
	{ XK_KP_5,         ControlMask|ShiftMask,          "\033[181;6u", 0,  0},
	{ XK_KP_5,         Mod1Mask,                       "\033[181;3u", 0,  0},
	{ XK_KP_5,         Mod1Mask|ControlMask,           "\033[181;7u", 0,  0},
	{ XK_KP_5,         Mod1Mask|ControlMask|ShiftMask, "\033[181;8u", 0,  0},
	{ XK_KP_5,         Mod1Mask|ShiftMask,             "\033[181;4u", 0,  0},
	{ XK_KP_5,         ShiftMask,                      "\033[181;2u", 0,  0},
	{ XK_KP_6,         XK_NO_MOD,                      "\033Ov",     +2,  0},
	{ XK_KP_6,         ControlMask,                    "\033[182;5u", 0,  0},
	{ XK_KP_6,         ControlMask|ShiftMask,          "\033[182;6u", 0,  0},
	{ XK_KP_6,         Mod1Mask,                       "\033[182;3u", 0,  0},
	{ XK_KP_6,         Mod1Mask|ControlMask,           "\033[182;7u", 0,  0},
	{ XK_KP_6,         Mod1Mask|ControlMask|ShiftMask, "\033[182;8u", 0,  0},
	{ XK_KP_6,         Mod1Mask|ShiftMask,             "\033[182;4u", 0,  0},
	{ XK_KP_6,         ShiftMask,                      "\033[182;2u", 0,  0},
	{ XK_KP_7,         XK_NO_MOD,                      "\033Ow",     +2,  0},
	{ XK_KP_7,         ControlMask,                    "\033[183;5u", 0,  0},
	{ XK_KP_7,         ControlMask|ShiftMask,          "\033[183;6u", 0,  0},
	{ XK_KP_7,         Mod1Mask,                       "\033[183;3u", 0,  0},
	{ XK_KP_7,         Mod1Mask|ControlMask,           "\033[183;7u", 0,  0},
	{ XK_KP_7,         Mod1Mask|ControlMask|ShiftMask, "\033[183;8u", 0,  0},
	{ XK_KP_7,         Mod1Mask|ShiftMask,             "\033[183;4u", 0,  0},
	{ XK_KP_7,         ShiftMask,                      "\033[183;2u", 0,  0},
	{ XK_KP_8,         XK_NO_MOD,                      "\033Ox",     +2,  0},
	{ XK_KP_8,         ControlMask,                    "\033[184;5u", 0,  0},
	{ XK_KP_8,         ControlMask|ShiftMask,          "\033[184;6u", 0,  0},
	{ XK_KP_8,         Mod1Mask,                       "\033[184;3u", 0,  0},
	{ XK_KP_8,         Mod1Mask|ControlMask,           "\033[184;7u", 0,  0},
	{ XK_KP_8,         Mod1Mask|ControlMask|ShiftMask, "\033[184;8u", 0,  0},
	{ XK_KP_8,         Mod1Mask|ShiftMask,             "\033[184;4u", 0,  0},
	{ XK_KP_8,         ShiftMask,                      "\033[184;2u", 0,  0},
	{ XK_KP_9,         XK_NO_MOD,                      "\033Oy",     +2,  0},
	{ XK_KP_9,         ControlMask,                    "\033[185;5u", 0,  0},
	{ XK_KP_9,         ControlMask|ShiftMask,          "\033[185;6u", 0,  0},
	{ XK_KP_9,         Mod1Mask,                       "\033[185;3u", 0,  0},
	{ XK_KP_9,         Mod1Mask|ControlMask,           "\033[185;7u", 0,  0},
	{ XK_KP_9,         Mod1Mask|ControlMask|ShiftMask, "\033[185;8u", 0,  0},
	{ XK_KP_9,         Mod1Mask|ShiftMask,             "\033[185;4u", 0,  0},
	{ XK_KP_9,         ShiftMask,                      "\033[185;2u", 0,  0},
	{ XK_BackSpace,    ControlMask,                    "\033[127;5u", 0,  0},
	{ XK_BackSpace,    ControlMask|ShiftMask,          "\033[127;6u", 0,  0},
	{ XK_BackSpace,    Mod1Mask,                       "\033[127;3u", 0,  0},
	{ XK_BackSpace,    Mod1Mask|ControlMask,           "\033[127;7u", 0,  0},
	{ XK_BackSpace,    Mod1Mask|ControlMask|ShiftMask, "\033[127;8u", 0,  0},
	{ XK_BackSpace,    Mod1Mask|ShiftMask,             "\033[127;4u", 0,  0},
	{ XK_BackSpace,    ShiftMask,                      "\033[127;2u", 0,  0},
	{ XK_Tab,          ControlMask,                    "\033[9;5u",   0,  0},
	{ XK_Tab,          ControlMask|ShiftMask,          "\033[1;5Z",   0,  0},
	{ XK_Tab,          Mod1Mask,                       "\033[1;3Z",   0,  0},
	{ XK_Tab,          Mod1Mask|ControlMask,           "\033[1;7Z",   0,  0},
	{ XK_Tab,          Mod1Mask|ControlMask|ShiftMask, "\033[1;8Z",   0,  0},
	{ XK_Tab,          Mod1Mask|ShiftMask,             "\033[1;4Z",   0,  0},
	{ XK_Return,       ControlMask,                    "\033[13;5u",  0,  0},
	{ XK_Return,       ControlMask|ShiftMask,          "\033[13;6u",  0,  0},
	{ XK_Return,       Mod1Mask,                       "\033[13;3u",  0,  0},
	{ XK_Return,       Mod1Mask|ControlMask,           "\033[13;7u",  0,  0},
	{ XK_Return,       Mod1Mask|ControlMask|ShiftMask, "\033[13;8u",  0,  0},
	{ XK_Return,       Mod1Mask|ShiftMask,             "\033[13;4u",  0,  0},
	{ XK_Return,       ShiftMask,                      "\033[13;2u",  0,  0},
	{ XK_Pause,        ControlMask,                    "\033[18;5u",  0,  0},
	{ XK_Pause,        ControlMask|ShiftMask,          "\033[18;6u",  0,  0},
	{ XK_Pause,        Mod1Mask,                       "\033[18;3u",  0,  0},
	{ XK_Pause,        Mod1Mask|ControlMask,           "\033[18;7u",  0,  0},
	{ XK_Pause,        Mod1Mask|ControlMask|ShiftMask, "\033[18;8u",  0,  0},
	{ XK_Pause,        Mod1Mask|ShiftMask,             "\033[18;4u",  0,  0},
	{ XK_Pause,        ShiftMask,                      "\033[18;2u",  0,  0},
	{ XK_Scroll_Lock,  ControlMask,                    "\033[20;5u",  0,  0},
	{ XK_Scroll_Lock,  ControlMask|ShiftMask,          "\033[20;6u",  0,  0},
	{ XK_Scroll_Lock,  Mod1Mask,                       "\033[20;3u",  0,  0},
	{ XK_Scroll_Lock,  Mod1Mask|ControlMask,           "\033[20;7u",  0,  0},
	{ XK_Scroll_Lock,  Mod1Mask|ControlMask|ShiftMask, "\033[20;8u",  0,  0},
	{ XK_Scroll_Lock,  Mod1Mask|ShiftMask,             "\033[20;4u",  0,  0},
	{ XK_Scroll_Lock,  ShiftMask,                      "\033[20;2u",  0,  0},
	{ XK_Escape,       ControlMask,                    "\033[27;5u",  0,  0},
	{ XK_Escape,       ControlMask|ShiftMask,          "\033[27;6u",  0,  0},
	{ XK_Escape,       Mod1Mask,                       "\033[27;3u",  0,  0},
	{ XK_Escape,       Mod1Mask|ControlMask,           "\033[27;7u",  0,  0},
	{ XK_Escape,       Mod1Mask|ControlMask|ShiftMask, "\033[27;8u",  0,  0},
	{ XK_Escape,       Mod1Mask|ShiftMask,             "\033[27;4u",  0,  0},
	{ XK_Escape,       ShiftMask,                      "\033[27;2u",  0,  0},
	{ XK_Home,         XK_NO_MOD,                      "\033[H",      0, -1},
	{ XK_Home,         XK_NO_MOD,                      "\033[1~",     0, +1},
	{ XK_Home,         ControlMask|ShiftMask,          "\033[80;6u",  0,  0},
	{ XK_Home,         Mod1Mask,                       "\033[80;3u",  0,  0},
	{ XK_Home,         Mod1Mask|ControlMask,           "\033[80;7u",  0,  0},
	{ XK_Home,         Mod1Mask|ControlMask|ShiftMask, "\033[80;8u",  0,  0},
	{ XK_Home,         Mod1Mask|ShiftMask,             "\033[80;4u",  0,  0},
	{ XK_End,          XK_NO_MOD,                      "\033[4~",     0,  0},
	{ XK_End,          ControlMask|ShiftMask,          "\033[87;6u",  0,  0},
	{ XK_End,          Mod1Mask,                       "\033[87;3u",  0,  0},
	{ XK_End,          Mod1Mask|ControlMask,           "\033[87;7u",  0,  0},
	{ XK_End,          Mod1Mask|ControlMask|ShiftMask, "\033[87;8u",  0,  0},
	{ XK_End,          Mod1Mask|ShiftMask,             "\033[87;4u",  0,  0},
	{ XK_Prior,        XK_NO_MOD,                      "\033[5~",     0,  0},
	{ XK_Prior,        ControlMask|ShiftMask,          "\033[85;6u",  0,  0},
	{ XK_Prior,        Mod1Mask,                       "\033[85;3u",  0,  0},
	{ XK_Prior,        Mod1Mask|ControlMask,           "\033[85;7u",  0,  0},
	{ XK_Prior,        Mod1Mask|ControlMask|ShiftMask, "\033[85;8u",  0,  0},
	{ XK_Prior,        Mod1Mask|ShiftMask,             "\033[85;4u",  0,  0},
	{ XK_Next,         XK_NO_MOD,                      "\033[6~",     0,  0},
	{ XK_Next,         ControlMask|ShiftMask,          "\033[86;6u",  0,  0},
	{ XK_Next,         Mod1Mask,                       "\033[86;3u",  0,  0},
	{ XK_Next,         Mod1Mask|ControlMask,           "\033[86;7u",  0,  0},
	{ XK_Next,         Mod1Mask|ControlMask|ShiftMask, "\033[86;8u",  0,  0},
	{ XK_Next,         Mod1Mask|ShiftMask,             "\033[86;4u",  0,  0},
	{ XK_Print,        ControlMask,                    "\033[97;5u",  0,  0},
	{ XK_Print,        ControlMask|ShiftMask,          "\033[97;6u",  0,  0},
	{ XK_Print,        Mod1Mask,                       "\033[97;3u",  0,  0},
	{ XK_Print,        Mod1Mask|ControlMask,           "\033[97;7u",  0,  0},
	{ XK_Print,        Mod1Mask|ControlMask|ShiftMask, "\033[97;8u",  0,  0},
	{ XK_Print,        Mod1Mask|ShiftMask,             "\033[97;4u",  0,  0},
	{ XK_Print,        ShiftMask,                      "\033[97;2u",  0,  0},
	{ XK_Insert,       XK_NO_MOD,                      "\033[4h",    -1,  0},
	{ XK_Insert,       XK_NO_MOD,                      "\033[2~",    +1,  0},
	{ XK_Insert,       ControlMask|ShiftMask,          "\033[99;6u",  0,  0},
	{ XK_Insert,       Mod1Mask,                       "\033[99;3u",  0,  0},
	{ XK_Insert,       Mod1Mask|ControlMask,           "\033[99;7u",  0,  0},
	{ XK_Insert,       Mod1Mask|ControlMask|ShiftMask, "\033[99;8u",  0,  0},
	{ XK_Insert,       Mod1Mask|ShiftMask,             "\033[99;4u",  0,  0},
	{ XK_Menu,         ControlMask,                    "\033[103;5u", 0,  0},
	{ XK_Menu,         ControlMask|ShiftMask,          "\033[103;6u", 0,  0},
	{ XK_Menu,         Mod1Mask,                       "\033[103;3u", 0,  0},
	{ XK_Menu,         Mod1Mask|ControlMask,           "\033[103;7u", 0,  0},
	{ XK_Menu,         Mod1Mask|ControlMask|ShiftMask, "\033[103;8u", 0,  0},
	{ XK_Menu,         Mod1Mask|ShiftMask,             "\033[103;4u", 0,  0},
	{ XK_Menu,         ShiftMask,                      "\033[103;2u", 0,  0},
	{ XK_Delete,       XK_NO_MOD,                      "\033[P",     -1,  0},
	{ XK_Delete,       XK_NO_MOD,                      "\033[3~",    +1,  0},
	{ XK_Delete,       ControlMask|ShiftMask,          "\033[255;6u", 0,  0},
	{ XK_Delete,       Mod1Mask,                       "\033[255;3u", 0,  0},
	{ XK_Delete,       Mod1Mask|ControlMask,           "\033[255;7u", 0,  0},
	{ XK_Delete,       Mod1Mask|ControlMask|ShiftMask, "\033[255;8u", 0,  0},
	{ XK_Delete,       Mod1Mask|ShiftMask,             "\033[255;4u", 0,  0},
	{ XK_i,            ControlMask,                    "\033[105;5u", 0,  0},
	{ XK_i,            Mod1Mask|ControlMask,           "\033[105;7u", 0,  0},
	{ XK_m,            ControlMask,                    "\033[109;5u", 0,  0},
	{ XK_m,            Mod1Mask|ControlMask,           "\033[109;7u", 0,  0},
	{ XK_space,        ControlMask|ShiftMask,          "\033[32;6u",  0,  0},
	{ XK_space,        Mod1Mask,                       "\033[32;3u",  0,  0},
	{ XK_space,        Mod1Mask|ControlMask,           "\033[32;7u",  0,  0},
	{ XK_space,        Mod1Mask|ControlMask|ShiftMask, "\033[32;8u",  0,  0},
	{ XK_space,        Mod1Mask|ShiftMask,             "\033[32;4u",  0,  0},
	{ XK_space,        ShiftMask,                      "\033[32;2u",  0,  0},
	{ XK_0,            ControlMask,                    "\033[48;5u",  0,  0},
	{ XK_A,            ControlMask|ShiftMask,          "\033[65;6u",  0,  0},
	{ XK_B,            ControlMask|ShiftMask,          "\033[66;6u",  0,  0},
	{ XK_C,            ControlMask|ShiftMask,          "\033[67;6u",  0,  0},
	{ XK_D,            ControlMask|ShiftMask,          "\033[68;6u",  0,  0},
	{ XK_E,            ControlMask|ShiftMask,          "\033[69;6u",  0,  0},
	{ XK_F,            ControlMask|ShiftMask,          "\033[70;6u",  0,  0},
	{ XK_G,            ControlMask|ShiftMask,          "\033[71;6u",  0,  0},
	{ XK_H,            ControlMask|ShiftMask,          "\033[72;6u",  0,  0},
	{ XK_I,            ControlMask|ShiftMask,          "\033[73;6u",  0,  0},
	{ XK_I,            Mod1Mask|ControlMask|ShiftMask, "\033[73;8u",  0,  0},
	{ XK_J,            ControlMask|ShiftMask,          "\033[75;6u",  0,  0},
	{ XK_K,            ControlMask|ShiftMask,          "\033[74;6u",  0,  0},
	{ XK_L,            ControlMask|ShiftMask,          "\033[76;6u",  0,  0},
	{ XK_M,            ControlMask|ShiftMask,          "\033[77;6u",  0,  0},
	{ XK_M,            Mod1Mask|ControlMask|ShiftMask, "\033[77;8u",  0,  0},
	{ XK_N,            ControlMask|ShiftMask,          "\033[78;6u",  0,  0},
	{ XK_O,            ControlMask|ShiftMask,          "\033[79;6u",  0,  0},
	{ XK_P,            ControlMask|ShiftMask,          "\033[80;6u",  0,  0},
	{ XK_Q,            ControlMask|ShiftMask,          "\033[81;6u",  0,  0},
	{ XK_R,            ControlMask|ShiftMask,          "\033[82;6u",  0,  0},
	{ XK_S,            ControlMask|ShiftMask,          "\033[83;6u",  0,  0},
	{ XK_T,            ControlMask|ShiftMask,          "\033[84;6u",  0,  0},
	{ XK_U,            ControlMask|ShiftMask,          "\033[85;6u",  0,  0},
	{ XK_V,            ControlMask|ShiftMask,          "\033[86;6u",  0,  0},
	{ XK_W,            ControlMask|ShiftMask,          "\033[87;6u",  0,  0},
	{ XK_X,            ControlMask|ShiftMask,          "\033[88;6u",  0,  0},
	{ XK_Y,            ControlMask|ShiftMask,          "\033[89;6u",  0,  0},
	{ XK_Z,            ControlMask|ShiftMask,          "\033[90;6u",  0,  0},
	{ XK_Z,            ControlMask|ShiftMask,          "\033[90;6u",  0,  0},
	{ XK_0,            Mod1Mask|ControlMask,           "\033[48;7u",  0,  0},
	{ XK_1,            ControlMask,                    "\033[49;5u",  0,  0},
	{ XK_1,            Mod1Mask|ControlMask,           "\033[49;7u",  0,  0},
	{ XK_2,            ControlMask,                    "\033[50;5u",  0,  0},
	{ XK_2,            Mod1Mask|ControlMask,           "\033[50;7u",  0,  0},
	{ XK_3,            ControlMask,                    "\033[51;5u",  0,  0},
	{ XK_3,            Mod1Mask|ControlMask,           "\033[51;7u",  0,  0},
	{ XK_4,            ControlMask,                    "\033[52;5u",  0,  0},
	{ XK_4,            Mod1Mask|ControlMask,           "\033[52;7u",  0,  0},
	{ XK_5,            ControlMask,                    "\033[53;5u",  0,  0},
	{ XK_5,            Mod1Mask|ControlMask,           "\033[53;7u",  0,  0},
	{ XK_6,            ControlMask,                    "\033[54;5u",  0,  0},
	{ XK_6,            Mod1Mask|ControlMask,           "\033[54;7u",  0,  0},
	{ XK_7,            ControlMask,                    "\033[55;5u",  0,  0},
	{ XK_7,            Mod1Mask|ControlMask,           "\033[55;7u",  0,  0},
	{ XK_8,            ControlMask,                    "\033[56;5u",  0,  0},
	{ XK_8,            Mod1Mask|ControlMask,           "\033[56;7u",  0,  0},
	{ XK_9,            ControlMask,                    "\033[57;5u",  0,  0},
	{ XK_9,            Mod1Mask|ControlMask,           "\033[57;7u",  0,  0},
	{ XK_ampersand,    ControlMask,                    "\033[38;5u",  0,  0},
	{ XK_ampersand,    ControlMask|ShiftMask,          "\033[38;6u",  0,  0},
	{ XK_ampersand,    Mod1Mask,                       "\033[38;3u",  0,  0},
	{ XK_ampersand,    Mod1Mask|ControlMask,           "\033[38;7u",  0,  0},
	{ XK_ampersand,    Mod1Mask|ControlMask|ShiftMask, "\033[38;8u",  0,  0},
	{ XK_ampersand,    Mod1Mask|ShiftMask,             "\033[38;4u",  0,  0},
	{ XK_apostrophe,   ControlMask,                    "\033[39;5u",  0,  0},
	{ XK_apostrophe,   ControlMask|ShiftMask,          "\033[39;6u",  0,  0},
	{ XK_apostrophe,   Mod1Mask,                       "\033[39;3u",  0,  0},
	{ XK_apostrophe,   Mod1Mask|ControlMask,           "\033[39;7u",  0,  0},
	{ XK_apostrophe,   Mod1Mask|ControlMask|ShiftMask, "\033[39;8u",  0,  0},
	{ XK_apostrophe,   Mod1Mask|ShiftMask,             "\033[39;4u",  0,  0},
	{ XK_asciicircum,  ControlMask,                    "\033[94;5u",  0,  0},
	{ XK_asciicircum,  ControlMask|ShiftMask,          "\033[94;6u",  0,  0},
	{ XK_asciicircum,  Mod1Mask,                       "\033[94;3u",  0,  0},
	{ XK_asciicircum,  Mod1Mask|ControlMask,           "\033[94;7u",  0,  0},
	{ XK_asciicircum,  Mod1Mask|ControlMask|ShiftMask, "\033[94;8u",  0,  0},
	{ XK_asciicircum,  Mod1Mask|ShiftMask,             "\033[94;4u",  0,  0},
	{ XK_asciitilde,   ControlMask,                    "\033[126;5u", 0,  0},
	{ XK_asciitilde,   ControlMask|ShiftMask,          "\033[126;6u", 0,  0},
	{ XK_asciitilde,   Mod1Mask,                       "\033[126;3u", 0,  0},
	{ XK_asciitilde,   Mod1Mask|ControlMask,           "\033[126;7u", 0,  0},
	{ XK_asciitilde,   Mod1Mask|ControlMask|ShiftMask, "\033[126;8u", 0,  0},
	{ XK_asciitilde,   Mod1Mask|ShiftMask,             "\033[126;4u", 0,  0},
	{ XK_asterisk,     ControlMask,                    "\033[42;5u",  0,  0},
	{ XK_asterisk,     ControlMask|ShiftMask,          "\033[42;6u",  0,  0},
	{ XK_asterisk,     Mod1Mask,                       "\033[42;3u",  0,  0},
	{ XK_asterisk,     Mod1Mask|ControlMask,           "\033[42;7u",  0,  0},
	{ XK_asterisk,     Mod1Mask|ControlMask|ShiftMask, "\033[42;8u",  0,  0},
	{ XK_asterisk,     Mod1Mask|ShiftMask,             "\033[42;4u",  0,  0},
	{ XK_at,           ControlMask,                    "\033[64;5u",  0,  0},
	{ XK_at,           ControlMask|ShiftMask,          "\033[64;6u",  0,  0},
	{ XK_at,           Mod1Mask,                       "\033[64;3u",  0,  0},
	{ XK_at,           Mod1Mask|ControlMask,           "\033[64;7u",  0,  0},
	{ XK_at,           Mod1Mask|ControlMask|ShiftMask, "\033[64;8u",  0,  0},
	{ XK_at,           Mod1Mask|ShiftMask,             "\033[64;4u",  0,  0},
	{ XK_backslash,    ControlMask,                    "\033[92;5u",  0,  0},
	{ XK_backslash,    ControlMask|ShiftMask,          "\033[92;6u",  0,  0},
	{ XK_backslash,    Mod1Mask,                       "\033[92;3u",  0,  0},
	{ XK_backslash,    Mod1Mask|ControlMask,           "\033[92;7u",  0,  0},
	{ XK_backslash,    Mod1Mask|ControlMask|ShiftMask, "\033[92;8u",  0,  0},
	{ XK_backslash,    Mod1Mask|ShiftMask,             "\033[92;4u",  0,  0},
	{ XK_bar,          ControlMask,                    "\033[124;5u", 0,  0},
	{ XK_bar,          ControlMask|ShiftMask,          "\033[124;6u", 0,  0},
	{ XK_bar,          Mod1Mask,                       "\033[124;3u", 0,  0},
	{ XK_bar,          Mod1Mask|ControlMask,           "\033[124;7u", 0,  0},
	{ XK_bar,          Mod1Mask|ControlMask|ShiftMask, "\033[124;8u", 0,  0},
	{ XK_bar,          Mod1Mask|ShiftMask,             "\033[124;4u", 0,  0},
	{ XK_braceleft,    ControlMask,                    "\033[123;5u", 0,  0},
	{ XK_braceleft,    ControlMask|ShiftMask,          "\033[123;6u", 0,  0},
	{ XK_braceleft,    Mod1Mask,                       "\033[123;3u", 0,  0},
	{ XK_braceleft,    Mod1Mask|ControlMask,           "\033[123;7u", 0,  0},
	{ XK_braceleft,    Mod1Mask|ControlMask|ShiftMask, "\033[123;8u", 0,  0},
	{ XK_braceleft,    Mod1Mask|ShiftMask,             "\033[123;4u", 0,  0},
	{ XK_braceright,   ControlMask,                    "\033[125;5u", 0,  0},
	{ XK_braceright,   ControlMask|ShiftMask,          "\033[125;6u", 0,  0},
	{ XK_braceright,   Mod1Mask,                       "\033[125;3u", 0,  0},
	{ XK_braceright,   Mod1Mask|ControlMask,           "\033[125;7u", 0,  0},
	{ XK_braceright,   Mod1Mask|ControlMask|ShiftMask, "\033[125;8u", 0,  0},
	{ XK_braceright,   Mod1Mask|ShiftMask,             "\033[125;4u", 0,  0},
	{ XK_bracketleft,  ControlMask,                    "\033[91;5u",  0,  0},
	{ XK_bracketleft,  ControlMask|ShiftMask,          "\033[91;6u",  0,  0},
	{ XK_bracketleft,  Mod1Mask,                       "\033[91;3u",  0,  0},
	{ XK_bracketleft,  Mod1Mask|ControlMask,           "\033[91;7u",  0,  0},
	{ XK_bracketleft,  Mod1Mask|ControlMask|ShiftMask, "\033[91;8u",  0,  0},
	{ XK_bracketleft,  Mod1Mask|ShiftMask,             "\033[91;4u",  0,  0},
	{ XK_bracketright, ControlMask,                    "\033[93;5u",  0,  0},
	{ XK_bracketright, ControlMask|ShiftMask,          "\033[93;6u",  0,  0},
	{ XK_bracketright, Mod1Mask,                       "\033[93;3u",  0,  0},
	{ XK_bracketright, Mod1Mask|ControlMask,           "\033[93;7u",  0,  0},
	{ XK_bracketright, Mod1Mask|ControlMask|ShiftMask, "\033[93;8u",  0,  0},
	{ XK_bracketright, Mod1Mask|ShiftMask,             "\033[93;4u",  0,  0},
	{ XK_colon,        ControlMask,                    "\033[58;5u",  0,  0},
	{ XK_colon,        ControlMask|ShiftMask,          "\033[58;6u",  0,  0},
	{ XK_colon,        Mod1Mask,                       "\033[58;3u",  0,  0},
	{ XK_colon,        Mod1Mask|ControlMask,           "\033[58;7u",  0,  0},
	{ XK_colon,        Mod1Mask|ControlMask|ShiftMask, "\033[58;8u",  0,  0},
	{ XK_colon,        Mod1Mask|ShiftMask,             "\033[58;4u",  0,  0},
	{ XK_comma,        ControlMask,                    "\033[44;5u",  0,  0},
	{ XK_comma,        ControlMask|ShiftMask,          "\033[44;6u",  0,  0},
	{ XK_comma,        Mod1Mask,                       "\033[44;3u",  0,  0},
	{ XK_comma,        Mod1Mask|ControlMask,           "\033[44;7u",  0,  0},
	{ XK_comma,        Mod1Mask|ControlMask|ShiftMask, "\033[44;8u",  0,  0},
	{ XK_comma,        Mod1Mask|ShiftMask,             "\033[44;4u",  0,  0},
	{ XK_dollar,       ControlMask,                    "\033[36;5u",  0,  0},
	{ XK_dollar,       ControlMask|ShiftMask,          "\033[36;6u",  0,  0},
	{ XK_dollar,       Mod1Mask,                       "\033[36;3u",  0,  0},
	{ XK_dollar,       Mod1Mask|ControlMask,           "\033[36;7u",  0,  0},
	{ XK_dollar,       Mod1Mask|ControlMask|ShiftMask, "\033[36;8u",  0,  0},
	{ XK_dollar,       Mod1Mask|ShiftMask,             "\033[36;4u",  0,  0},
	{ XK_equal,        ControlMask,                    "\033[61;5u",  0,  0},
	{ XK_equal,        ControlMask|ShiftMask,          "\033[61;6u",  0,  0},
	{ XK_equal,        Mod1Mask,                       "\033[61;3u",  0,  0},
	{ XK_equal,        Mod1Mask|ControlMask,           "\033[61;7u",  0,  0},
	{ XK_equal,        Mod1Mask|ControlMask|ShiftMask, "\033[61;8u",  0,  0},
	{ XK_equal,        Mod1Mask|ShiftMask,             "\033[61;4u",  0,  0},
	{ XK_exclam,       ControlMask,                    "\033[33;5u",  0,  0},
	{ XK_exclam,       ControlMask|ShiftMask,          "\033[33;6u",  0,  0},
	{ XK_exclam,       Mod1Mask,                       "\033[33;3u",  0,  0},
	{ XK_exclam,       Mod1Mask|ControlMask,           "\033[33;7u",  0,  0},
	{ XK_exclam,       Mod1Mask|ControlMask|ShiftMask, "\033[33;8u",  0,  0},
	{ XK_exclam,       Mod1Mask|ShiftMask,             "\033[33;4u",  0,  0},
	{ XK_grave,        ControlMask,                    "\033[96;5u",  0,  0},
	{ XK_grave,        ControlMask|ShiftMask,          "\033[96;6u",  0,  0},
	{ XK_grave,        Mod1Mask,                       "\033[96;3u",  0,  0},
	{ XK_grave,        Mod1Mask|ControlMask,           "\033[96;7u",  0,  0},
	{ XK_grave,        Mod1Mask|ControlMask|ShiftMask, "\033[96;8u",  0,  0},
	{ XK_grave,        Mod1Mask|ShiftMask,             "\033[96;4u",  0,  0},
	{ XK_greater,      ControlMask,                    "\033[62;5u",  0,  0},
	{ XK_greater,      ControlMask|ShiftMask,          "\033[62;6u",  0,  0},
	{ XK_greater,      Mod1Mask,                       "\033[62;3u",  0,  0},
	{ XK_greater,      Mod1Mask|ControlMask,           "\033[62;7u",  0,  0},
	{ XK_greater,      Mod1Mask|ControlMask|ShiftMask, "\033[62;8u",  0,  0},
	{ XK_greater,      Mod1Mask|ShiftMask,             "\033[62;4u",  0,  0},
	{ XK_less,         ControlMask,                    "\033[60;5u",  0,  0},
	{ XK_less,         ControlMask|ShiftMask,          "\033[60;6u",  0,  0},
	{ XK_less,         Mod1Mask,                       "\033[60;3u",  0,  0},
	{ XK_less,         Mod1Mask|ControlMask,           "\033[60;7u",  0,  0},
	{ XK_less,         Mod1Mask|ControlMask|ShiftMask, "\033[60;8u",  0,  0},
	{ XK_less,         Mod1Mask|ShiftMask,             "\033[60;4u",  0,  0},
	{ XK_minus,        ControlMask,                    "\033[45;5u",  0,  0},
	{ XK_minus,        ControlMask|ShiftMask,          "\033[45;6u",  0,  0},
	{ XK_minus,        Mod1Mask,                       "\033[45;3u",  0,  0},
	{ XK_minus,        Mod1Mask|ControlMask,           "\033[45;7u",  0,  0},
	{ XK_minus,        Mod1Mask|ControlMask|ShiftMask, "\033[45;8u",  0,  0},
	{ XK_minus,        Mod1Mask|ShiftMask,             "\033[45;4u",  0,  0},
	{ XK_numbersign,   ControlMask,                    "\033[35;5u",  0,  0},
	{ XK_numbersign,   ControlMask|ShiftMask,          "\033[35;6u",  0,  0},
	{ XK_numbersign,   Mod1Mask,                       "\033[35;3u",  0,  0},
	{ XK_numbersign,   Mod1Mask|ControlMask,           "\033[35;7u",  0,  0},
	{ XK_numbersign,   Mod1Mask|ControlMask|ShiftMask, "\033[35;8u",  0,  0},
	{ XK_numbersign,   Mod1Mask|ShiftMask,             "\033[35;4u",  0,  0},
	{ XK_parenleft,    ControlMask,                    "\033[40;5u",  0,  0},
	{ XK_parenleft,    ControlMask|ShiftMask,          "\033[40;6u",  0,  0},
	{ XK_parenleft,    Mod1Mask,                       "\033[40;3u",  0,  0},
	{ XK_parenleft,    Mod1Mask|ControlMask,           "\033[40;7u",  0,  0},
	{ XK_parenleft,    Mod1Mask|ControlMask|ShiftMask, "\033[40;8u",  0,  0},
	{ XK_parenleft,    Mod1Mask|ShiftMask,             "\033[40;4u",  0,  0},
	{ XK_parenright,   ControlMask,                    "\033[41;5u",  0,  0},
	{ XK_parenright,   ControlMask|ShiftMask,          "\033[41;6u",  0,  0},
	{ XK_parenright,   Mod1Mask,                       "\033[41;3u",  0,  0},
	{ XK_parenright,   Mod1Mask|ControlMask,           "\033[41;7u",  0,  0},
	{ XK_parenright,   Mod1Mask|ControlMask|ShiftMask, "\033[41;8u",  0,  0},
	{ XK_parenright,   Mod1Mask|ShiftMask,             "\033[41;4u",  0,  0},
	{ XK_percent,      ControlMask,                    "\033[37;5u",  0,  0},
	{ XK_percent,      ControlMask|ShiftMask,          "\033[37;6u",  0,  0},
	{ XK_percent,      Mod1Mask,                       "\033[37;3u",  0,  0},
	{ XK_percent,      Mod1Mask|ControlMask,           "\033[37;7u",  0,  0},
	{ XK_percent,      Mod1Mask|ControlMask|ShiftMask, "\033[37;8u",  0,  0},
	{ XK_percent,      Mod1Mask|ShiftMask,             "\033[37;4u",  0,  0},
	{ XK_period,       ControlMask,                    "\033[46;5u",  0,  0},
	{ XK_period,       ControlMask|ShiftMask,          "\033[46;6u",  0,  0},
	{ XK_period,       Mod1Mask|ControlMask,           "\033[46;7u",  0,  0},
	{ XK_period,       Mod1Mask|ControlMask|ShiftMask, "\033[46;8u",  0,  0},
	{ XK_period,       Mod1Mask|ShiftMask,             "\033[46;4u",  0,  0},
	{ XK_plus,         ControlMask,                    "\033[43;5u",  0,  0},
	{ XK_plus,         ControlMask|ShiftMask,          "\033[43;6u",  0,  0},
	{ XK_plus,         Mod1Mask,                       "\033[43;3u",  0,  0},
	{ XK_plus,         Mod1Mask|ControlMask,           "\033[43;7u",  0,  0},
	{ XK_plus,         Mod1Mask|ControlMask|ShiftMask, "\033[43;8u",  0,  0},
	{ XK_plus,         Mod1Mask|ShiftMask,             "\033[43;4u",  0,  0},
	{ XK_question,     ControlMask,                    "\033[63;5u",  0,  0},
	{ XK_question,     ControlMask|ShiftMask,          "\033[63;6u",  0,  0},
	{ XK_question,     Mod1Mask,                       "\033[63;3u",  0,  0},
	{ XK_question,     Mod1Mask|ControlMask,           "\033[63;7u",  0,  0},
	{ XK_question,     Mod1Mask|ControlMask|ShiftMask, "\033[63;8u",  0,  0},
	{ XK_question,     Mod1Mask|ShiftMask,             "\033[63;4u",  0,  0},
	{ XK_quotedbl,     ControlMask,                    "\033[34;5u",  0,  0},
	{ XK_quotedbl,     ControlMask|ShiftMask,          "\033[34;6u",  0,  0},
	{ XK_quotedbl,     Mod1Mask,                       "\033[34;3u",  0,  0},
	{ XK_quotedbl,     Mod1Mask|ControlMask,           "\033[34;7u",  0,  0},
	{ XK_quotedbl,     Mod1Mask|ControlMask|ShiftMask, "\033[34;8u",  0,  0},
	{ XK_quotedbl,     Mod1Mask|ShiftMask,             "\033[34;4u",  0,  0},
	{ XK_semicolon,    ControlMask,                    "\033[59;5u",  0,  0},
	{ XK_semicolon,    ControlMask|ShiftMask,          "\033[59;6u",  0,  0},
	{ XK_semicolon,    Mod1Mask,                       "\033[59;3u",  0,  0},
	{ XK_semicolon,    Mod1Mask|ControlMask,           "\033[59;7u",  0,  0},
	{ XK_semicolon,    Mod1Mask|ControlMask|ShiftMask, "\033[59;8u",  0,  0},
	{ XK_semicolon,    Mod1Mask|ShiftMask,             "\033[59;4u",  0,  0},
	{ XK_slash,        ControlMask|ShiftMask,          "\033[47;6u",  0,  0},
	{ XK_slash,        Mod1Mask,                       "\033[47;3u",  0,  0},
	{ XK_slash,        Mod1Mask|ControlMask,           "\033[47;7u",  0,  0},
	{ XK_slash,        Mod1Mask|ControlMask|ShiftMask, "\033[47;8u",  0,  0},
	{ XK_slash,        Mod1Mask|ShiftMask,             "\033[47;4u",  0,  0},
	{ XK_underscore,   ControlMask,                    "\033[95;5u",  0,  0},
	{ XK_underscore,   ControlMask|ShiftMask,          "\033[95;6u",  0,  0},
	{ XK_underscore,   Mod1Mask,                       "\033[95;3u",  0,  0},
	{ XK_underscore,   Mod1Mask|ControlMask,           "\033[95;7u",  0,  0},
	{ XK_underscore,   Mod1Mask|ControlMask|ShiftMask, "\033[95;8u",  0,  0},
	{ XK_underscore,   Mod1Mask|ShiftMask,             "\033[95;4u",  0,  0},
};

/*
 * Selection types' masks.
 * Use the same masks as usual.
 * Button1Mask is always unset, to make masks match between ButtonPress.
 * ButtonRelease and MotionNotify.
 * If no match is found, regular selection is used.
 */
static uint selmasks[] = {
	[SEL_RECTANGULAR] = Mod1Mask,
};

/*
 * Printable characters in ASCII, used to estimate the advance width
 * of single wide characters.
 */
static char ascii_printable[] =
	" !\"#$%&'()*+,-./0123456789:;<=>?"
	"@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_"
	"`abcdefghijklmnopqrstuvwxyz{|}~";
