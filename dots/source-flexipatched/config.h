/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx = 2; /* border pixel of windows */
static const unsigned int snap = 0;     /* snap pixel */
static const unsigned int gappih = 5;   /* horiz inner gap between windows */
static const unsigned int gappiv = 5;   /* vert inner gap between windows */
static const unsigned int gappoh =
    5; /* horiz outer gap between windows and screen edge */
static const unsigned int gappov =
    5; /* vert outer gap between windows and screen edge */
static const int smartgaps_fact =
    1; /* gap factor when there is only one client; 0 = no gaps, 3 = 3x outer
          gaps */
static const int showbar = 1; /* 0 means no bar */
static const int topbar = 1;  /* 0 means bottom bar */
static const int vertpad = 5; /* vertical padding of bar */
static const int sidepad = 5; /* horizontal padding of bar */
/* Status is to be shown on: -1 (all monitors), 0 (a specific monitor by index),
 * 'A' (active monitor) */
static const int statusmon = 'A';
static const int horizpadbar = 10; /* horizontal padding for statusbar */
static const int vertpadbar = 20;  /* vertical padding for statusbar */
static const unsigned int ulinepad =
    10; /* horizontal padding between the underline and tag */
static const unsigned int ulinestroke =
    2; /* thickness / height of the underline */
static const unsigned int ulinevoffset =
    33; /* how far above the bottom of the bar the line should appear */
static const int ulineall =
    0; /* 1 to show underline on all tags, 0 for just the active ones */

/* Indicators: see patch/bar_indicators.h for options */
static int tagindicatortype = INDICATOR_BOTTOM_BAR_SLIM;
static int tiledindicatortype = INDICATOR_NONE;
static int floatindicatortype = INDICATOR_NONE;
static const char *fonts[] = {
    "JetBrainsMono Nerd Font:size=10",
    "NotoColorEmoji:pixelsize=15:antialias=true:autohint=true"};

static char c000000[] = "#000000"; // placeholder value
#include "/home/crystal/.cache/wal/colors-wal-dwm.h"

static const unsigned int baralpha = 150;
static const unsigned int borderalpha = OPAQUE;
static const unsigned int alphas[][3] = {
    /*                       fg      bg        border     */
    [SchemeNorm] = {OPAQUE, baralpha, borderalpha},
    [SchemeSel] = {OPAQUE, baralpha, borderalpha},
    [SchemeTitleNorm] = {OPAQUE, baralpha, borderalpha},
    [SchemeTitleSel] = {OPAQUE, baralpha, borderalpha},
    [SchemeTagsNorm] = {OPAQUE, baralpha, borderalpha},
    [SchemeTagsSel] = {OPAQUE, baralpha, borderalpha},
    [SchemeHidNorm] = {OPAQUE, baralpha, borderalpha},
    [SchemeHidSel] = {OPAQUE, baralpha, borderalpha},
    [SchemeUrg] = {OPAQUE, baralpha, borderalpha},
};

static char *colors[][ColCount] = {
    /*                       fg                bg                border float */
    [SchemeNorm] = {normfgcolor, normbgcolor, normbordercolor, normfloatcolor},
    [SchemeSel] = {selfgcolor, selbgcolor, selbordercolor, selfloatcolor},
    [SchemeTitleNorm] = {titlenormfgcolor, titlenormbgcolor,
                         titlenormbordercolor, titlenormfloatcolor},
    [SchemeTitleSel] = {titleselfgcolor, titleselbgcolor, titleselbordercolor,
                        titleselfloatcolor},
    [SchemeTagsNorm] = {tagsnormfgcolor, tagsnormbgcolor, tagsnormbordercolor,
                        tagsnormfloatcolor},
    [SchemeTagsSel] = {tagsselfgcolor, tagsselbgcolor, tagsselbordercolor,
                       tagsselfloatcolor},
    [SchemeHidNorm] = {hidnormfgcolor, hidnormbgcolor, c000000, c000000},
    [SchemeHidSel] = {hidselfgcolor, hidselbgcolor, c000000, c000000},
    [SchemeUrg] = {urgfgcolor, urgbgcolor, urgbordercolor, urgfloatcolor},
};

const char *spcmd1[] = {"echo", "OK", NULL};
static Sp scratchpads[] = {
    /* name          cmd  */
    {"spterm", spcmd1},
};

/* Tags
 * In a traditional dwm the number of tags in use can be changed simply by
 * changing the number of strings in the tags array. This build does things a
 * bit different which has some added benefits. If you need to change the number
 * of tags here then change the NUMTAGS macro in dwm.c.
 *
 * Examples:
 *
 *  1) static char *tagicons[][NUMTAGS*2] = {
 *         [DEFAULT_TAGS] = { "1", "2", "3", "4", "5", "6", "7", "8", "9", "A",
 * "B", "C", "D", "E", "F", "G", "H", "I" },
 *     }
 *
 *  2) static char *tagicons[][1] = {
 *         [DEFAULT_TAGS] = { "•" },
 *     }
 *
 * The first example would result in the tags on the first monitor to be 1
 * through 9, while the tags for the second monitor would be named A through I.
 * A third monitor would start again at 1 through 9 while the tags on a fourth
 * monitor would also be named A through I. Note the tags count of NUMTAGS*2 in
 * the array initialiser which defines how many tag text / icon exists in the
 * array. This can be changed to *3 to add separate icons for a third monitor.
 *
 * For the second example each tag would be represented as a bullet point. Both
 * cases work the same from a technical standpoint - the icon index is derived
 * from the tag index and the monitor index. If the icon index is is greater
 * than the number of tag icons then it will wrap around until it an icon
 * matches. Similarly if there are two tag icons then it would alternate between
 * them. This works seamlessly with alternative tags and alttagsdecoration
 * patches.
 */
static char *tagicons[][NUMTAGS] = {
    [DEFAULT_TAGS] = {"I", "II", "III", "IV", "V", "VI", "VII", "VIII", "IX"},
};

/* There are two options when it comes to per-client rules:
 *  - a typical struct table or
 *  - using the RULE macro
 *
 * A traditional struct table looks like this:
 *    // class      instance  title  wintype  tags mask  isfloating  monitor
 *    { "Gimp",     NULL,     NULL,  NULL,    1 << 4,    0,          -1 },
 *    { "Firefox",  NULL,     NULL,  NULL,    1 << 7,    0,          -1 },
 *
 * The RULE macro has the default values set for each field allowing you to only
 * specify the values that are relevant for your rule, e.g.
 *
 *    RULE(.class = "Gimp", .tags = 1 << 4)
 *    RULE(.class = "Firefox", .tags = 1 << 7)
 *
 * Refer to the Rule struct definition for the list of available fields
 * depending on the patches you enable.
 */
static const Rule rules[] = {
    /* xprop(1):
     *	WM_CLASS(STRING) = instance, class
     *	WM_NAME(STRING) = title
     *	WM_WINDOW_ROLE(STRING) = role
     *	_NET_WM_WINDOW_TYPE(ATOM) = wintype
     */
    RULE(.wintype = WTYPE "DIALOG", .isfloating = 1)
        RULE(.wintype = WTYPE "UTILITY", .isfloating = 1)
            RULE(.wintype = WTYPE "TOOLBAR", .isfloating = 1)
                RULE(.wintype = WTYPE "SPLASH", .isfloating = 1)
                        RULE(.class = "Nsxiv", .isfloating = 1)
                            RULE(.instance = "spterm", .tags = SPTAG(0),
                                 .isfloating = 1)

};

/* Bar rules allow you to configure what is shown where on the bar, as well as
 * introducing your own bar modules.
 *
 *    monitor:
 *      -1  show on all monitors
 *       0  show on monitor 0
 *      'A' show on active monitor (i.e. focused / selected) (or just -1 for
 * active?) bar - bar index, 0 is default, 1 is extrabar alignment - how the
 * module is aligned compared to other modules widthfunc, drawfunc, clickfunc -
 * providing bar module width, draw and click functions name - does nothing,
 * intended for visual clue and for logging / debugging
 */
static const BarRule barrules[] = {
    /* monitor   bar    alignment         widthfunc                drawfunc
       clickfunc                name */
    {-1, 0, BAR_ALIGN_LEFT, width_tags, draw_tags, click_tags, "tags"},
    {-1, 0, BAR_ALIGN_LEFT, width_ltsymbol, draw_ltsymbol, click_ltsymbol,
     "layout"},
    {statusmon, 0, BAR_ALIGN_RIGHT, width_status2d, draw_status2d,
     click_status2d, "status2d"},
};

/* layout(s) */
static const float mfact = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster = 1;    /* number of clients in master area */
static const int nstack = 0;     /* number of clients in primary stack area */
static const int resizehints =
    0; /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen =
    1; /* 1 will force focus on the fullscreen window */

#define FORCE_VSPLIT 1

static const Layout layouts[] = {
    /* symbol     arrange function, { nmaster, nstack, layout, master axis,
       stack axis, secondary stack axis, symbol func } */
    {"[]=",
     flextile,
     {-1, -1, SPLIT_VERTICAL, TOP_TO_BOTTOM, TOP_TO_BOTTOM, 0,
      NULL}},           // default tile layout
    {"><>", NULL, {0}}, /* no layout function means floating behavior */
    {"[M]", flextile, {-1, -1, NO_SPLIT, MONOCLE, MONOCLE, 0, NULL}}, // monocle
    {"|||",
     flextile,
     {-1, -1, SPLIT_VERTICAL, LEFT_TO_RIGHT, TOP_TO_BOTTOM, 0,
      NULL}}, // columns (col) layout
    {">M>",
     flextile,
     {-1, -1, FLOATING_MASTER, LEFT_TO_RIGHT, LEFT_TO_RIGHT, 0,
      NULL}}, // floating master
    {"[D]",
     flextile,
     {-1, -1, SPLIT_VERTICAL, TOP_TO_BOTTOM, MONOCLE, 0, NULL}}, // deck
    {"TTT",
     flextile,
     {-1, -1, SPLIT_HORIZONTAL, LEFT_TO_RIGHT, LEFT_TO_RIGHT, 0,
      NULL}}, // bstack
    {"===",
     flextile,
     {-1, -1, SPLIT_HORIZONTAL, LEFT_TO_RIGHT, TOP_TO_BOTTOM, 0,
      NULL}}, // bstackhoriz
    {"|M|",
     flextile,
     {-1, -1, SPLIT_CENTERED_VERTICAL, LEFT_TO_RIGHT, TOP_TO_BOTTOM,
      TOP_TO_BOTTOM, NULL}}, // centeredmaster
    {"-M-",
     flextile,
     {-1, -1, SPLIT_CENTERED_HORIZONTAL, TOP_TO_BOTTOM, LEFT_TO_RIGHT,
      LEFT_TO_RIGHT, NULL}}, // centeredmaster horiz
    {":::",
     flextile,
     {-1, -1, NO_SPLIT, GAPPLESSGRID, GAPPLESSGRID, 0, NULL}}, // gappless grid
    {"[\\]",
     flextile,
     {-1, -1, NO_SPLIT, DWINDLE, DWINDLE, 0, NULL}}, // fibonacci dwindle
    {"(@)",
     flextile,
     {-1, -1, NO_SPLIT, SPIRAL, SPIRAL, 0, NULL}}, // fibonacci spiral
    {"[T]",
     flextile,
     {-1, -1, SPLIT_VERTICAL, LEFT_TO_RIGHT, TATAMI, 0, NULL}}, // tatami mats
    {"[]=", tile, {0}},
    {"[M]", monocle, {0}},
    {"TTT", bstack, {0}},
    {"===", bstackhoriz, {0}},
    {"|M|", centeredmaster, {0}},
    {">M>", centeredfloatingmaster, {0}},
    {"|||", col, {0}},
    {"[D]", deck, {0}},
    {"(@)", spiral, {0}},
    {"[\\]", dwindle, {0}},
    {"HHH", grid, {0}},
    {"---", horizgrid, {0}},
    {":::", gaplessgrid, {0}},
    {"###", nrowgrid, {0}},
    {NULL, NULL, {0}},
};

#define MODKEY Mod4Mask
#define ALTKEY Mod1Mask
#define TAGKEYS(KEY, TAG)                                                      \
  {MODKEY, KEY, view, {.ui = 1 << TAG}},                                       \
      {MODKEY | ControlMask, KEY, toggleview, {.ui = 1 << TAG}},               \
      {MODKEY | ShiftMask, KEY, tag, {.ui = 1 << TAG}},                        \
      {MODKEY | ControlMask | ShiftMask, KEY, toggletag, {.ui = 1 << TAG}},

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd)                                                             \
  {                                                                            \
    .v = (const char *[]) { "/bin/sh", "-c", cmd, NULL }                       \
  }

/* ******************** Commands ******************** */
static char dmenumon[2] =
    "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = {"dmenu", NULL};

/* Launch Apps */
static const char *stcmd[] = {"/home/crystal/Crystalwm/bins/st/bin/st", NULL};
static const char *termcmd[] = {"/home/crystal/Crystalwm/bins/st/bin/st", NULL};

/* Rofi Menus */
static const char *drun[] = {"drun", NULL};
/* Misc */

/* Hardware keys for volume and brightness */
#include <X11/XF86keysym.h>
static const char *upbl[] = {"xbacklight", "-inc", "5", NULL};
static const char *downbl[] = {"xbacklight", "-dec", "5", NULL};

/* ******************** Keybindings ******************** */
static Key keys[] = {
    /* modifier 				key
     * function argument
     */

    // Hardware Keys -----------
    {0, XF86XK_AudioMute, spawn, SHCMD("pactl set-sink-mute 0 toggle")},
    {0, XF86XK_AudioLowerVolume, spawn, SHCMD("pactl set-sink-volume 0 -5%")},
    {0, XF86XK_AudioRaiseVolume, spawn, SHCMD("pactl set-sink-volume 0 +5%")},
    {MODKEY, XK_z, spawn, SHCMD("pactl set-sink-volume 1 -5%")},
    {MODKEY, XK_x, spawn, SHCMD("pactl set-sink-volume 1 +5%")},

    {0, XF86XK_MonBrightnessUp, spawn, {.v = upbl}},
    {0, XF86XK_MonBrightnessDown, spawn, {.v = downbl}},

    // Print Keys -----------
    {MODKEY | ShiftMask, XK_u, spawn,
     SHCMD("maim | xclip -selection clipboard -t image/png")},
    {MODKEY, XK_u, spawn,
     SHCMD("maim -s | xclip -selection clipboard -t image/png")},
    {MODKEY, XK_k, spawn, SHCMD("emacsclient -c -a 'emacs'")},

    // Terminals -----------
    {MODKEY, XK_Return, spawn, {.v = stcmd}},
    // Rofi Menus -----------
    {MODKEY, XK_d, spawn, {.v = drun}},
    // Misc -----------

    // Tags --------
    TAGKEYS(XK_1, 0) TAGKEYS(XK_2, 1) TAGKEYS(XK_3, 2) TAGKEYS(XK_4, 3)
        TAGKEYS(XK_5, 4) TAGKEYS(XK_6, 5) TAGKEYS(XK_7, 6) TAGKEYS(XK_8, 7)
            TAGKEYS(XK_9, 8)
    // DWM Session	-----------
    {MODKEY | ControlMask, XK_a, quit, {0}},    // Quit DWM
    {MODKEY | ShiftMask, XK_r, quit, {1}},      // Restart DWW
                                                // Window Management -----------
                                                /* Murder */
    {MODKEY, XK_a, killclient, {0}},            // Kill window
    {MODKEY, XK_Escape, spawn, SHCMD("xkill")}, // xkill

    /* Switch */
    {MODKEY, XK_Left, focusstack, {.i = +1}}, // Cycle window
    {MODKEY, XK_Right, focusstack, {.i = -1}},
    {MODKEY | ShiftMask, XK_Left, movestack, {.i = +1}}, // Switch master
    {MODKEY | ShiftMask, XK_Right, movestack, {.i = -1}},

    {MODKEY, XK_i, incnmaster, {.i = +1}}, // Verticle
    {MODKEY, XK_p, incnmaster, {.i = -1}}, // Horizontal

    /* Resize */

    {MODKEY | ControlMask, XK_Left, setmfact, {.f = -0.05}},  // Shrink left
    {MODKEY | ControlMask, XK_Right, setmfact, {.f = +0.05}}, // Shrink right

    /* Misc */
    {MODKEY, XK_b, togglebar, {0}}, // Toggle bar
    {MODKEY, XK_Tab, view, {0}},    // Switch to last tag
    {MODKEY, XK_0, view, {.ui = ~0}},
    {MODKEY | ShiftMask, XK_0, tag, {.ui = ~0}},
    {MODKEY, XK_e, togglescratch, {.ui = 0}},
    {MODKEY | ControlMask, XK_e, setscratch, {.ui = 0}},
    {MODKEY | ShiftMask, XK_e, removescratch, {.ui = 0}},

    // Layouts -----------

    {MODKEY, XK_comma, cyclelayout, {.i = -1}},
    {MODKEY, XK_semicolon, cyclelayout, {.i = +1}},
    {MODKEY | ShiftMask, XK_space, togglefloating, {0}},
    {MODKEY, XK_f, togglefullscreen, {0}},

    {MODKEY, XK_space, setlayout, {0}},
    {MODKEY, XK_t, spawn, SHCMD("themer")},                    // Tile
    {MODKEY, XK_g, setlayout, {.v = &layouts[10]}},            // Grid
    {MODKEY | ShiftMask, XK_m, setlayout, {.v = &layouts[1]}}, // Monocle
    {MODKEY, XK_s, togglesticky, {0}},
    {MODKEY | ShiftMask, XK_s, setlayout, {.v = &layouts[2]}}, // Spiral
    {MODKEY | ShiftMask, XK_t, setlayout, {.v = &layouts[5]}}, // Stack
    {MODKEY | ShiftMask,
     XK_c,
     setlayout,
     {.v = &layouts[11]}}, // Centered master
    {MODKEY | ShiftMask, XK_x, setlayout, {.v = &layouts[12]}}, // Tatami

};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle,
 * ClkClientWin, or ClkRootWin */
static Button buttons[] = {
    /* click                event mask           button          function
       argument */
    {ClkLtSymbol, 0, Button1, setlayout, {0}},
    {ClkLtSymbol, 0, Button3, setlayout, {.v = &layouts[2]}},
    {ClkWinTitle, 0, Button1, togglewin, {0}},
    {ClkWinTitle, 0, Button3, showhideclient, {0}},
    {ClkWinTitle, 0, Button2, zoom, {0}},
    {ClkStatusText, 0, Button2, spawn, {.v = termcmd}},
    {ClkClientWin, MODKEY, Button1, movemouse, {0}},
    {ClkClientWin, MODKEY, Button2, togglefloating, {0}},
    {ClkClientWin, MODKEY, Button3, resizemouse, {0}},
    {ClkClientWin, MODKEY | ShiftMask, Button3, dragcfact, {0}},
    {ClkClientWin, MODKEY | ShiftMask, Button1, dragmfact, {0}},
    {ClkTagBar, 0, Button1, view, {0}},
    {ClkTagBar, 0, Button3, toggleview, {0}},
    {ClkTagBar, MODKEY, Button1, tag, {0}},
    {ClkTagBar, MODKEY, Button3, toggletag, {0}},
};

/* signal definitions */
/* signum must be greater than 0 */
/* trigger signals using `xsetroot -name "fsignal:<signum>"` */
static Signal signals[] = {
    /* signum       function        argument  */
    {1, quit, {1}},
 {2, setlayout, {.v = &layouts[12]}},

};
