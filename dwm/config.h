/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 2;        /* border pixel of windows */
static const unsigned int gappx     = 4;        /* gap pixel between windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const unsigned int systraypinning = 1;   /* 0: sloppy systray follows selected monitor, >0: pin systray to monitor X */
static const unsigned int systrayspacing = 2;   /* systray spacing */
static const int systraypinningfailfirst = 1;   /* 1: if pinning fails, display systray on the first monitor, False: display systray on the last monitor*/
static const int showsystray        = 1;        /* 0 means no systray */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const char *fonts[]          = { "Hack Nerd Font:size=12:antialias=true:autohint=true" };
static const char dmenufont[]       = "Hack Nerd Font:size=12:antialias=true:autohint=true";
static const char col_gray1[]       = "#222222";
static const char col_gray2[]       = "#444444";
static const char col_gray3[]       = "#666666";
static const char col_gray4[]       = "#bbbbbb";
static const char col_gray5[]       = "#eeeeee";
static const char col_red[]         = "#dd0000";
static const char col_black[]       = "#000000";
static const char col_white[]       = "#ffffff";
static const char col_cyan[]        = "#005577";
static const char run_application_preferences[] = "lxappearance,firefox-developer-edition,pavucontrol,thunar,thunderbird,nvidia-setting,smerge,subl,virt-manager,discord,evince,designer-qt5,libreoffice,anydesk,obsidian";
static const char *colors[][3]      = {
    /*               fg         bg         border   */
    //[SchemeNorm] = { col_gray3, col_gray1, col_gray2 },
    [SchemeNorm] = { col_gray4, col_black, col_black },
    [SchemeSel] = { col_white, col_black, col_cyan }, // Currently selected tag
    [SchemeTag] = { col_gray1, col_black, NULL }, // Not selected tags
    [SchemeApp] = { col_gray3, col_black, NULL }, // Not Selected tag with Apps
};

#define ICONSIZE (bh - 2)
#define ICONSPACING 5

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static const Rule rules[] = {
    /* xprop(1):
     *  WM_CLASS(STRING) = instance, class
     *  WM_NAME(STRING) = title
     */
    /* class                        instance         title                                   tags mask     isfloating   monitor */
    { "Gimp",                       NULL,            NULL,                                   0,            0,           -1 },
    { "firefoxdeveloperedition",    "Navigator",     NULL,                                   0,            0,            1 },
    { "firefoxdeveloperedition",    "Navigator",     "YouTube — Firefox Developer Edition",  0,            0,            2 },
    { "Thunderbird",                "Mail",          NULL,                                   1 << 1,       0,            1 },
    { "Thunderbird",                "Calendar",      NULL,                                   1 << 1,       1,            1 },
    { "Sublime_text",               "sublime_text",  NULL,                                   0,            0,            0 },
    { "Sublime_merge",              "sublime_merge", NULL,                                   1 << 1,       0,            0 },
    { "discord",                    "discord",       NULL,                                   1 << 3,       0,            1 },
    { "obsidian",                   "obsidian",      NULL,                                   1 << 8,       0,           -1 },
};

/* layout(s) */
static const float mfact     = 0.5; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */

static const Layout layouts[] = {
    /* symbol     arrange function */
    { "[T]",      tile },    /* first entry is default */
    { "[F]",      NULL },    /* no layout function means floating behavior */
    { "[M]",      monocle },
};

/* key definitions */
#define MODKEY Mod1Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },


/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static const char *dmenucmd[]    = { "dmenu_run", "-i", "-p", " Run:", "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray3, "-sb", col_black, "-sf", col_gray4, "-hp", run_application_preferences, NULL };
static const char *termcmd[]     = { "st", NULL };
static const char *firefox[]     = { "firefox-developer-edition", NULL };
static const char *privateff[]   = { "firefox-developer-edition", "--private-window", NULL };
static const char *slock[]       = { "slock", NULL };
static const char *subl[]        = { "subl", NULL };
static const char *smerge[]      = { "smerge", NULL };
static const char *fileman[]     = { "thunar", NULL };
static const char *virtman[]     = { "virt-manager", NULL };
static const char *lxappear[]    = { "lxappearance", NULL };
static const char *compcrm[]     = { "python", "/home/mason/Company/Programs/application/mwtech.py", NULL };

/* SPT Commands */
static const char *togglespt[]   = { "spt", "pb", "-t", NULL };
static const char *prevtrack[]   = { "spt", "pb", "-p", NULL };
static const char *nexttrack[]   = { "spt", "pb", "-n", NULL };

// Volume Scripts Commands
static const char *muteaudio[]   = { "sh", "/home/mason/suckless/dwm/scripts/toggle_mute.sh", NULL };
static const char *incaudio[]    = { "sh", "/home/mason/suckless/dwm/scripts/volumeup.sh", "5", NULL };
static const char *sincaudio[]   = { "sh", "/home/mason/suckless/dwm/scripts/volumeup.sh", "1", NULL };
static const char *decaudio[]    = { "sh", "/home/mason/suckless/dwm/scripts/volumedown.sh", "5", NULL };
static const char *sdecaudio[]   = { "sh", "/home/mason/suckless/dwm/scripts/volumedown.sh", "1", NULL };

// Dmenu Script Commands
static const char *passmenu[]    = { "sh", "/home/mason/suckless/dmenu/scripts/passmenu.sh", NULL };
static const char *potpmenu[]    = { "sh", "/home/mason/suckless/dmenu/scripts/passotpmenu.sh", NULL };
static const char *dmconf[]      = { "sh", "/home/mason/suckless/dmenu/scripts/dmconf.sh", NULL };
static const char *compotppass[] = { "sh", "/home/mason/suckless/dmenu/scripts/compotppass.sh", NULL };
static const char *comppass[]    = { "sh", "/home/mason/suckless/dmenu/scripts/comppass.sh", NULL };
static const char *nmdmenu[]     = { "python", "/home/mason/suckless/dmenu/scripts/networkmanager_dmenu.py", NULL };
static const char *dmpower[]     = { "sh", "/home/mason/suckless/dmenu/scripts/dm_power.sh", NULL };
static const char *genpass[]     = { "sh", "/home/mason/suckless/dmenu/scripts/genpass.sh", NULL };
static const char *gencpass[]    = { "sh", "/home/mason/suckless/dmenu/scripts/gencomppass.sh", NULL };
static const char *todoscript[]  = { "sh", "/home/mason/suckless/dmenu/scripts/todo.sh", NULL };
static const char *mntwrkshare[] = { "sh", "/home/mason/suckless/dmenu/scripts/mount_remote_shares.sh", "m", NULL };
static const char *untwrkshare[] = { "sh", "/home/mason/suckless/dmenu/scripts/mount_remote_shares.sh", "u", NULL };
static const char *jfdownload[]  = { "python", "/home/mason/suckless/dmenu/scripts/jf-download-client.py", NULL };

// Dunst Commands
static const char *dunst_close[]      = { "dunstctl", "close", NULL };
static const char *dunst_closeall[]   = { "dunstctl", "close-all", NULL };
static const char *dunst_history[]    = { "dunstctl", "history-pop", NULL };
//
//a - Todo Dmenu Script
//A
//b - Toggle Bar
//B
//c - Config Edit Menu
//C - Kill Client
//d - Decrease Master Stack Number
//D -
//e - PC Man File Manager
//E
//f - Set floating layout
//F
//g - Generate Password
//G - Generate Company Password
//h - Increase Horizontal Window Size
//H - Decrease Horizontal Window Size
//i - Increase Master Stack Number
//I
//j - Focus Stack Forward
//J - Rotate Stack Forward
//k - Focus Stack Backward
//K - Rotate Stack Backward
//l - Lock (slock)
//L
//m
//M - Set Monocle layout
//n - Network Manager Menu
//N
//o - Pass OTP Menu
//O - Company Pass OTP Menu
//p - Pass menu
//P - Company Pass menu
//q
//Q
//r - Dmenu
//R - Company CRM
//s - Sublime Text
//S - Sublime Merge
//t - Set tiling Layout
//T -
//u - Mount Remote Shares
//U - Unmount Remote Shares
//v - Virt-manager
//V
//w - Firefox
//W - Firefox Private Browser
//x - lxappearance
//X
//y - Jellyfin Downloader
//Y
//z
//Z
//Escape - Power Menu
static Key keys[] = {
    /* modifier                     key         function        argument */
    { MODKEY,                       XK_r,       spawn,          {.v = dmenucmd } },
    { MODKEY|ShiftMask,             XK_r,       spawn,          {.v = compcrm } },
    { MODKEY,                       XK_p,       spawn,          {.v = passmenu } },
    { MODKEY|ShiftMask,             XK_p,       spawn,          {.v = comppass } },
    { MODKEY,                       XK_o,       spawn,          {.v = potpmenu } },
    { MODKEY|ShiftMask,             XK_o,       spawn,          {.v = compotppass } },
    { MODKEY|ShiftMask,             XK_Return,  spawn,          {.v = termcmd } },
    { MODKEY,                       XK_n,       spawn,          {.v = nmdmenu } },
    { MODKEY,                       XK_Escape,  spawn,          {.v = dmpower } },
    { MODKEY,                       XK_a,       spawn,          {.v = todoscript } },
    { MODKEY,                       XK_u,       spawn,          {.v = mntwrkshare } },
    { MODKEY|ShiftMask,             XK_u,       spawn,          {.v = untwrkshare } },
    { MODKEY,                       XK_b,       togglebar,      {0} },
    { MODKEY|ShiftMask,             XK_j,       rotatestack,    {.i = +1 } },
    { MODKEY|ShiftMask,             XK_k,       rotatestack,    {.i = -1 } },
    { MODKEY,                       XK_j,       focusstack,     {.i = +1 } },
    { MODKEY,                       XK_k,       focusstack,     {.i = -1 } },
    { MODKEY,                       XK_i,       incnmaster,     {.i = +1 } },
    { MODKEY,                       XK_d,       incnmaster,     {.i = -1 } },
    { MODKEY,                       XK_h,       setmfact,       {.f = +0.05} },
    { MODKEY|ShiftMask,             XK_h,       setmfact,       {.f = -0.05} },
    { MODKEY,                       XK_Return,  zoom,           {0} },
    { MODKEY,                       XK_Tab,     view,           {0} },
    { MODKEY|ShiftMask,             XK_c,       killclient,     {0} },
    { MODKEY,                       XK_t,       setlayout,      {.v = &layouts[0]} }, // Set tiling layout
    { MODKEY,                       XK_f,       setlayout,      {.v = &layouts[1]} }, // Set floating layout
    { MODKEY|ShiftMask,             XK_m,       setlayout,      {.v = &layouts[2]} }, // Set monocle layout
    { MODKEY|ShiftMask,             XK_space,   togglefloating, {0} },
    { MODKEY,                       XK_0,       view,           {.ui = ~0 } },
    { MODKEY|ShiftMask,             XK_0,       tag,            {.ui = ~0 } },
    { MODKEY,                       XK_comma,   focusmon,       {.i = +1 } },
    { MODKEY,                       XK_period,  focusmon,       {.i = -1 } },
    { MODKEY|ShiftMask,             XK_comma,   tagmon,         {.i = +1 } },
    { MODKEY|ShiftMask,             XK_period,  tagmon,         {.i = -1 } },
    { MODKEY,                       XK_w,       spawn,          {.v = firefox } },
    { MODKEY|ShiftMask,             XK_w,       spawn,          {.v = privateff } },
    { 0,                            0x1008ff11, spawn,          {.v = decaudio } },
    { MODKEY,                       0x1008ff11, spawn,          {.v = sdecaudio } },
    { 0,                            0x1008ff13, spawn,          {.v = incaudio } },
    { MODKEY,                       0x1008ff13, spawn,          {.v = sincaudio } },
    { 0,                            0x1008ff12, spawn,          {.v = muteaudio } },
    { 0,                            0x1008ff14, spawn,          {.v = togglespt } },
    { 0,                            0x1008ff16, spawn,          {.v = prevtrack } },
    { 0,                            0x1008ff17, spawn,          {.v = nexttrack } },
    { MODKEY,                       XK_y,       spawn,          {.v = jfdownload } },
    { MODKEY,                       XK_l,       spawn,          {.v = slock } },
    { MODKEY,                       XK_s,       spawn,          {.v = subl } },
    { MODKEY|ShiftMask,             XK_s,       spawn,          {.v = smerge } },
    { MODKEY,                       XK_c,       spawn,          {.v = dmconf } },
    { MODKEY,                       XK_e,       spawn,          {.v = fileman } },
    { MODKEY,                       XK_v,       spawn,          {.v = virtman } },
    { MODKEY,                       XK_g,       spawn,          {.v = genpass } },
    { MODKEY|ShiftMask,             XK_g,       spawn,          {.v = gencpass } },
    { MODKEY,                       XK_x,       spawn,          {.v = lxappear } },
    { MODKEY,                       XK_Left,    focusnthmon,    {.i = 1 } },
    { MODKEY,                       XK_Down,    focusnthmon,    {.i = 0 } },
    { MODKEY,                       XK_Up,      focusnthmon,    {.i = 2 } },
    { MODKEY,                       XK_Right,   focusnthmon,    {.i = 3 } },
    { MODKEY|ShiftMask,             XK_Left,    tagnthmon,      {.i = 1 } },
    { MODKEY|ShiftMask,             XK_Down,    tagnthmon,      {.i = 0 } },
    { MODKEY|ShiftMask,             XK_Up,      tagnthmon,      {.i = 2 } },
    { MODKEY|ShiftMask,             XK_Right,   tagnthmon,      {.i = 3 } },
    { MODKEY,                       XK_space,   spawn,          {.v = dunst_close } },
    { MODKEY|ShiftMask,             XK_grave,   spawn,          {.v = dunst_closeall } },
    { MODKEY,                       XK_grave,   spawn,          {.v = dunst_history } },
    TAGKEYS(                        XK_1,                       0)
    TAGKEYS(                        XK_2,                       1)
    TAGKEYS(                        XK_3,                       2)
    TAGKEYS(                        XK_4,                       3)
    TAGKEYS(                        XK_5,                       4)
    TAGKEYS(                        XK_6,                       5)
    TAGKEYS(                        XK_7,                       6)
    TAGKEYS(                        XK_8,                       7)
    TAGKEYS(                        XK_9,                       8)
    { MODKEY|ShiftMask,             XK_q,       quit,           {0} },
    { MODKEY|ControlMask|ShiftMask, XK_q,       quit,           {1} },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static const Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
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

