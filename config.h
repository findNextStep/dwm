#include "push.c"
#include <X11/XF86keysym.h>
#include "volume.h"
void volume_set(const Arg *arg){
	audio_volume_set(arg->i);
}
void volume_plus(const Arg *arg){
	audio_volume_plus(arg->i);
}
/* See LICENSE file for copyright and license details. */
/* appearance */
static const unsigned int borderpx  = 1;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const int showbar            = 1;        /* 0 means no bar */
static const unsigned int systraypinning = 0;   /* 0: sloppy systray follows selected monitor, >0: pin systray to monitor X */
static const unsigned int systrayspacing = 2;   /* systray spacing */
static const int systraypinningfailfirst = 1;   /* 1: if pinning fails, display systray on the first monitor, False: display systray on the last monitor*/
static const int showsystray        = 1;     /* 0 means no systray */
static const int topbar             = 0;        /* 0 means bottom bar */
static const char *fonts[]          = { "DroidSansMono Nerd Font:size=12" };
static const char dmenufont[]       = "DroidSansMono Nerd Font:size=20";
static const char col_gray1[]       = "#222222";
static const char col_gray2[]       = "#000000";
static const char col_gray3[]       = "#bbbbbb";
static const char col_gray4[]       = "#eeeeee";
static const char col_cyan[]        = "#0088ff";
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_cyan, col_gray2, col_gray2 },
	[SchemeSel]  = { col_gray2, col_cyan,  "#ff0000"  },
};

/* tagging */
static const char *tags[] = { "a", "s", "d", "f", "u", "i", "o", "p"};

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask     isfloating   monitor */
	{ "Gimp",     NULL,       NULL,       0,            1,           -1 },
    { NULL,       "tim.exe",  NULL,       1 << 7,       0,           1 },
};

/* layout(s) */
static const float mfact     = 0.5; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 0;    /* 1 means respect size hints in tiled resizals */

static const Layout layouts[] = {
	/* symbol     arrange function */
    { " 匿 ",      tile },    /* first entry is default */
    { " ﲔ ",      bstack },  /* vertical layout */
	{ "  ",      monocle }, /* full screen */
};

/* key definitions */
#define MODKEY Mod3Mask
#define r_alt_ Mod3Mask
#define l_alt_ Mod1Mask
#define superk Mod4Mask
#define ctrl_k ControlMask
#define shift_ ShiftMask

#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[]   = { "dmenu_run",    NULL };
static const char *termcmd[]    = { "st",           NULL };
// static const char *browser      = { "x-www-browser",NULL };
// static const char *file_browser = { "nemo",         NULL };
// static const char *dmenu_z      = { "dmenu_z",      NULL };

static Key keys[] = {
	/* modifier                     key        function        argument */
    /* applications */
    { superk,                       XK_1,      focus_client,   {.i = 0} },
    { superk,                       XK_2,      focus_client,   {.i = 1} },
    { superk,                       XK_3,      focus_client,   {.i = 2} },
    { superk,                       XK_4,      focus_client,   {.i = 3} },
    { superk,                       XK_5,      focus_client,   {.i = 4} },
    { superk,                       XK_6,      focus_client,   {.i = 5} },
    { superk,                       XK_7,      focus_client,   {.i = 6} },
    { superk,                       XK_8,      focus_client,   {.i = 7} },
    { superk,                       XK_9,      focus_client,   {.i = 8} },
	{ superk,                       XK_j,      spawn,          {.v = dmenucmd } },
	{ superk,                       XK_d,      spawn,          SHCMD("firefox") },
	{ superk,                       XK_f,      spawn,          SHCMD("nemo") },
	{ superk|shift_,                XK_Return, spawn,          SHCMD("dmenu_z") },
	{ superk,                       XK_Return, spawn,          SHCMD("st") },
    { ctrl_k|l_alt_,                XK_a,      spawn,          SHCMD("shutter -s -n -c")  },
    { l_alt_,                       XK_g,      spawn,          SHCMD("adb shell input tap 1878 363&&sleep 5&&adb shell input tap 1878 963&&sleep 1&&adb shell input tap 1878 963")  },
    /* about windows move */
	{ MODKEY,                       XK_n,      togglebar,      {0} },
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
    { MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
    { MODKEY|ctrl_k,                XK_j,      pushdown,       {0} },
    { MODKEY|ctrl_k,                XK_k,      pushup,         {0} },
	{ MODKEY|shift_,                XK_h,      incnmaster,     {.i = +1 } },
	{ MODKEY|shift_,                XK_l,      incnmaster,     {.i = -1 } },
	{ MODKEY|ctrl_k,                XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY|ctrl_k,                XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY,                       XK_Return, zoom,           {0} }, // toggle to master
	{ MODKEY,                       XK_g,      view,           {0} }, // toggle in last view tag
	{ MODKEY|shift_,                XK_c,      killclient,     {0} },
    /* set layout */
	{ MODKEY|shift_,                XK_space,  my_setlayout,   {.v = &layouts[2]} },
	{ MODKEY,                       XK_space,  my_setlayout,   {0} }, // toggle between layout 1 and 2
	{ MODKEY,                       XK_t,      togglefloating, {0} },
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } }, // show all windows
    { MODKEY|shift_,                XK_0,      tag,            {.ui = ~0 } }, // show in all tags
    /* switch monitor */
	{ MODKEY,                       XK_q,      focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_w,      focusmon,       {.i = +1 } },
	{ MODKEY|shift_,                XK_q,      tagmon,         {.i = -1 } },
	{ MODKEY|shift_,                XK_w,      tagmon,         {.i = +1 } },
	TAGKEYS(                        XK_a,                      0)
	TAGKEYS(                        XK_s,                      1)
	TAGKEYS(                        XK_d,                      2)
	TAGKEYS(                        XK_f,                      3)
	TAGKEYS(                        XK_u,                      4)
	TAGKEYS(                        XK_i,                      5)
	TAGKEYS(                        XK_o,                      6)
    // special view 'p'
    // TODO make toggle_view that toggle back when in view 7
	{ MODKEY,                       XK_p,      view,           {.ui = 1 << 7} }, \
	{ MODKEY|ControlMask,           XK_p,      toggleview,     {.ui = 1 << 7} }, \
	{ MODKEY|ShiftMask,             XK_p,      tag,            {.ui = 1 << 7} }, \
	{ MODKEY|ControlMask|ShiftMask, XK_p,      toggletag,      {.ui = 1 << 7} },
	{ MODKEY|ShiftMask,             XK_r,      quit,           {0} },
    {0,                             XF86XK_AudioMute,volume_set, {.i=0}},
    {0,                             XF86XK_AudioLowerVolume,volume_plus,{.i=-5}},
    {0,                             XF86XK_AudioRaiseVolume,volume_plus,{.i=5}},
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        my_setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

