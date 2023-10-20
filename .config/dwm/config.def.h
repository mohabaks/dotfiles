/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 1;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const unsigned int gappx     = 0;        /* gaps between windows */
static const int user_bh            = 20;        /* 0 means that dwm will calculate bar height, >= 1 means dwm will user_bh as bar height */
static const char *fonts[]          = {
        "Tewi:size=8",
        "Siji:size=8",
};
static const char dmenufont[]       = "Fixed:size=8";
static const char col_bg[]          = "#100e1f";
static const char col_bl[]          = "#18152f";
static const char col_fg[]          = "#c3d4f8";
static const char col_wh[]          = "#c3d4f8";
static const char col_cn[]          = "#0188aa";
static const char *colors[][3]      = {
	/*               fg         bg   border   */
	[SchemeNorm] = { col_fg, col_bg, col_bl  },
	[SchemeSel]  = { col_cn, col_bg, col_bl  },
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static const Rule rules[] = {
        /* xprop(1):
         *      WM_CLASS(STRING) = instance, class
         *      WM_NAME(STRING) = title
         */
        /* class                instance    title       tags mask     isfloating   monitor */
        { "Brim",               NULL,       NULL,       1 << 3,       0,           -1 },
        { "Chromium",           NULL,       NULL,       1 << 0,       0,           -1 },
        { "Ghidra",             NULL,       NULL,       1 << 7,       0,           -1 },
        { "Gimp",               NULL,       NULL,       1 << 7,       0,           -1 },
        { "Lxappearance",       NULL,       NULL,       0,            1,           -1 },
        { "Maltego",            NULL,       NULL,       1 << 7,       0,           -1 },
        { "Nitrogen",           NULL,       NULL,       0,            1,           -1 },
        { "Pavucontrol",        NULL,       NULL,       0,            1,           -1 },
        { "Postman",            NULL,       NULL,       1 << 7,       0,           -1 },
        { "Remote-viewer",      NULL,       NULL,       1 << 5,       0,           -1 },
        { "Slack",              NULL,       NULL,       1 << 8,       0,           -1 },
        { "TelegramDesktop",    NULL,       NULL,       1 << 8,       0,           -1 },
        { "Tor Browser",        NULL,       NULL,       1 << 0,       0,           -1 },
        { "Virt-manager",       NULL,       NULL,       1 << 5,       0,           -1 },
        { "Vmware-view",        NULL,       NULL,       0,            1,           -1 },
        { "Vncviewer",          NULL,       NULL,       1 << 5,       0,           -1 },
        { "Wireshark",          NULL,       NULL,       1 << 6,       0,           -1 },
        { "Zathura",            NULL,       NULL,       1 << 2,       0,           -1 },
        { "discord",            NULL,       NULL,       1 << 8,       0,           -1 },
        { "feh",                NULL,       NULL,       0,            1,           -1 },
        { "firefox",            NULL,       NULL,       1 << 0,       0,           -1 },
        { "firefox",            NULL,       NULL,       1 << 0,       0,           -1 },
        { "mpv",                NULL,       NULL,       1 << 3,       0,           -1 },
        { "obsidian",           NULL,       NULL,       1 << 2,       0,           -1 },
        { "qutebrowser",        NULL,       NULL,       1 << 0,       0,           -1 },
        { "rdesktop",           NULL,       NULL,       1 << 5,       0,           -1 },
        { "xfreerdp",           NULL,       NULL,       1 << 5,       0,           -1 },
};

/* layout(s) */
static const float mfact     = 0.50; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 0;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */

#include "tcl.c"
static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
	{ "|||",      tcl },
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-p", ">>>", "-h", "20", "-m", dmenumon, "-fn", dmenufont, "-nb", col_bg, "-nf", col_fg, "-sb", col_cn, "-sf", col_wh, NULL };
static const char *termcmd[]  = { "sensible-terminal", NULL };
static const char *dmenuext[]  = { "dmenu_extended_run", NULL };


#define STATUSBAR "dwmblocks"

#include <X11/XF86keysym.h>

static Key keys[] = {
        /* modifier                     key        function        argument */
        { MODKEY,                       XK_p,      spawn,          {.v = dmenucmd } },
        { MODKEY,                       XK_s,      spawn,          {.v = dmenuext } },
        { MODKEY,                       XK_Return, spawn,          {.v = termcmd } },
        { MODKEY,                       XK_b,      togglebar,      {0} },
        { MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
        { MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
        { MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
        { MODKEY,                       XK_d,      incnmaster,     {.i = -1 } },
        { MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
        { MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
        { MODKEY|ShiftMask,             XK_Return, zoom,           {0} },
        { MODKEY,                       XK_Tab,    view,           {0} },
        { MODKEY|ShiftMask,             XK_c,      killclient,     {0} },
        { MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
        { MODKEY,                       XK_f,      setlayout,      {.v = &layouts[1]} },
        { MODKEY,                       XK_m,      setlayout,      {.v = &layouts[2]} },
        { MODKEY,                       XK_w,      setlayout,      {.v = &layouts[3]} },
        { MODKEY,                       XK_space,  setlayout,      {0} },
        { MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
        { MODKEY,                       XK_0,      view,           {.ui = ~0 } },
        { MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
        { MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
        { MODKEY,                       XK_period, focusmon,       {.i = +1 } },
        { MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
        { MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
        { MODKEY,                       XK_minus,  setgaps,        {.i = -1 } },
        { MODKEY,                       XK_equal,  setgaps,        {.i = +1 } },
        { MODKEY|ShiftMask,             XK_equal,  setgaps,        {.i = 0  } },
        TAGKEYS(                        XK_1,                      0)
        TAGKEYS(                        XK_2,                      1)
        TAGKEYS(                        XK_3,                      2)
        TAGKEYS(                        XK_4,                      3)
        TAGKEYS(                        XK_5,                      4)
        TAGKEYS(                        XK_6,                      5)
        TAGKEYS(                        XK_7,                      6)
        TAGKEYS(                        XK_8,                      7)
        TAGKEYS(                        XK_9,                      8)
        { MODKEY|ShiftMask,             XK_Escape,      quit,           {0} },
        { MODKEY|ControlMask|ShiftMask, XK_q,           quit,           {1} },
        { MODKEY,                       XK_Print,       spawn,          SHCMD("screenshot") },
        { MODKEY|ControlMask,           XK_b,           spawn,          SHCMD("burpsuite") },
        { MODKEY|ControlMask,           XK_f,           spawn,          SHCMD("firefox") },
        { MODKEY|ControlMask,           XK_q,           spawn,          SHCMD("qutebrowser") },
        { 0, XF86XK_MonBrightnessUp,    spawn,          SHCMD("changeBrightness up") },
        { 0, XF86XK_MonBrightnessDown,  spawn,          SHCMD("changeBrightness down") },
        { 0, XF86XK_AudioMute,          spawn,          SHCMD("pactl set-sink-mute @DEFAULT_SINK@ toggle; pkill -RTMIN+10 dwmblocks")},
        { 0, XF86XK_AudioLowerVolume,   spawn,          SHCMD("pactl set-sink-volume @DEFAULT_SINK@ -10%; pkill -RTMIN+10 dwmblocks")},
        { 0, XF86XK_AudioRaiseVolume,   spawn,          SHCMD("pactl set-sink-volume @DEFAULT_SINK@ +10%; pkill -RTMIN+10 dwmblocks")},
        { 0, XF86XK_AudioMicMute,       spawn,          SHCMD("pactl set-source-mute @DEFAULT_SOURCE@ toggle; pkill -RTMIN+10 dwmblocks")},

};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
        /* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
        { ClkStatusText,        0,              Button1,        sigstatusbar,   {.i = 1} },
	{ ClkStatusText,        0,              Button2,        sigstatusbar,   {.i = 2} },
	{ ClkStatusText,        0,              Button3,        sigstatusbar,   {.i = 3} },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },

};
