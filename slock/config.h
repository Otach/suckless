/* user and group to drop privileges to */
static const char *user  = "mason";
static const char *group = "mason";

static const char *colorname[NUMCOLS] = {
	[BACKGROUND] =   "#000000",     /* after initialization */
	[INIT] =   "#2d2d2d",     /* after initialization */
	[INPUT] =  "#005577",   /* during input */
	[FAILED] = "#CC3333",   /* wrong password */
};

/* treat a cleared input like a wrong password (color) */
static const int failonclear = 1;

/* default message */
static const char *message = "Suckless: Software that sucks less.";

/* text color */
static const char *text_color = "#ffffff";

/* text size (must be a valid size) */
static const char *font_name = "-adobe-times-bold-r-normal--25-180-100-100-p-132-iso8859-1";

/* text offsets */
static const int x_offset = 1875;
static const int y_offset = 500;

/* time in seconds before the monitor shuts down */
static const int monitortime = 5 * 60;

/* insert grid pattern with scale 1:1, the size can be changed with logosize */
static const int logosize = 100;
static const int logow = 12;	/* grid width and height for right center alignment*/
static const int logoh = 6;

static XRectangle rectangles[9] = {
	/* x	y	w	h */
	{ 0,	3,	1,	3 },
	{ 1,	3,	2,	1 },
	{ 0,	5,	8,	1 },
	{ 3,	0,	1,	5 },
	{ 5,	3,	1,	2 },
	{ 7,	3,	1,	2 },
	{ 8,	3,	4,	1 },
	{ 9,	4,	1,	2 },
	{ 11,	4,	1,	2 },
};
