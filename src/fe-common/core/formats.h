#ifndef __FORMATS_H
#define __FORMATS_H

#include "themes.h"
#include "fe-windows.h"

#define PRINTFLAG_BOLD          0x01
#define PRINTFLAG_REVERSE       0x02
#define PRINTFLAG_UNDERLINE     0x04
#define PRINTFLAG_BEEP          0x08
#define PRINTFLAG_BLINK         0x10
#define PRINTFLAG_MIRC_COLOR    0x20
#define PRINTFLAG_INDENT        0x40
#define PRINTFLAG_NEWLINE       0x80

#define MAX_FORMAT_PARAMS 10
#define DEFAULT_FORMAT_ARGLIST_SIZE 200

enum {
	FORMAT_STRING,
	FORMAT_INT,
	FORMAT_LONG,
	FORMAT_FLOAT
};

struct _FORMAT_REC {
	char *tag;
	char *def;

	int params;
	int paramtypes[MAX_FORMAT_PARAMS];
};

typedef struct {
	WINDOW_REC *window;
	void *server;
	const char *target;
	int level;
} TEXT_DEST_REC;

int format_find_tag(const char *module, const char *tag);

char *format_get_text(const char *module, WINDOW_REC *window,
		      void *server, const char *target,
		      int formatnum, ...);

/* good size for buffer is DEFAULT_FORMAT_ARGLIST_SIZE */
void format_read_arglist(va_list va, FORMAT_REC *format,
			 char **arglist, int arglist_size,
			 char *buffer, int buffer_size);
char *format_get_text_theme(THEME_REC *theme, const char *module,
			    TEXT_DEST_REC *dest, int formatnum, ...);
char *format_get_text_theme_args(THEME_REC *theme, const char *module,
				 TEXT_DEST_REC *dest, int formatnum,
				 va_list va);
char *format_get_text_theme_charargs(THEME_REC *theme, const char *module,
				     TEXT_DEST_REC *dest, int formatnum,
				     char **args);

/* add `linestart' to start of each line in `text'. `text' may contain
   multiple lines separated with \n. */
char *format_add_linestart(const char *text, const char *linestart);

/* return the "-!- " text at the start of the line */
char *format_get_level_tag(THEME_REC *theme, TEXT_DEST_REC *dest);

/* return timestamp + server tag */
char *format_get_line_start(THEME_REC *theme, TEXT_DEST_REC *dest);


/* "private" functions for printtext */
void format_create_dest(TEXT_DEST_REC *dest,
			void *server, const char *target,
			int level, WINDOW_REC *window);

void format_newline(WINDOW_REC *window);

/* strip all color (etc.) codes from `input'. returns newly allocated string. */
char *strip_codes(const char *input);

/* send a fully parsed text string for GUI to print */
void format_send_to_gui(TEXT_DEST_REC *dest, const char *text);

#define FORMAT_COLOR_NOCHANGE	('0'-1)

#define FORMAT_STYLE_SPECIAL	0x60
#define FORMAT_STYLE_UNDERLINE	(0x01 + FORMAT_STYLE_SPECIAL)
#define FORMAT_STYLE_BOLD	(0x02 + FORMAT_STYLE_SPECIAL)
#define FORMAT_STYLE_REVERSE	(0x03 + FORMAT_STYLE_SPECIAL)
#define FORMAT_STYLE_INDENT	(0x04 + FORMAT_STYLE_SPECIAL)
#define FORMAT_STYLE_DEFAULTS	(0x05 + FORMAT_STYLE_SPECIAL)
int format_expand_styles(GString *out, char format, TEXT_DEST_REC *dest);

void formats_init(void);
void formats_deinit(void);

#endif
