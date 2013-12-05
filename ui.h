#ifndef UI_H
#define UI_H

/* Maximum width of the terminal */
#define MAXWIDTH 256

/* Maximum number of lines to keep in memory */
#define SCROLLMAX 1000

/*
 * The scrollback buffer is represented
 * internally by a linked list.  The list
 * head should always point to the *LAST*
 * message in the buffer and iterate upwards
 * via the prev pointer. 
 *
 * Some notes:
 *  1) The string is permanently stored here.  ui->s is malloc()d 
 *     every time a line is added to the scroll buffer.
 *  2) We chomp anything that would create a new line (\r, \n, etc)
 *     to avoid screwing up the way the UI is painted.
 */
typedef struct ui_scroll
{
	size_t l;                       /* Length of the string */
	char *s;                        /* The string itself */
	struct ui_scroll *prev, *next;  /* For iteration */
	struct ui_scroll *top;          /* First line (oldest) */
	struct ui_scroll *bot;          /* Last line (newest) */
	struct ui_scroll *head;         /* Last unused position */
} UI_SCROLL;

/*
 * This is the object which describes our UI and gets
 * passed around from function to function
 *
 * Some Notes:
 *  1) pos is the current position of the scroll buffer.  It's largely
 *     tracked and used internally.  PageUP and PageDOWN scrolls the screen
 *     by int(rows/2).  If pos=0 that means we're at the bottom of the screen.
 */
typedef struct ui
{
	NCURSES_BOOL newline;           /* If true, we need to insert a
					 * '\n' on the next pass in order
					 *  to scroll the window.
					 */
	UI_SCROLL *scroll;              /* The scrollback buffer */
	WINDOW *status;                 /* The status bar */
	WINDOW *input;                  /* The input bar */
	WINDOW *text;                   /* The scolling text window */
	int rows, cols;                 /* The dimensions of the terminal */
	int lines;                      /* The line count */
	int pos;                        /* Scroll position */
} UI;


/* 
 * Public API (function prototypes)
 */
int main(int argc, char **argv);

/*
 * ui_init() initializes the scrollback buffer and the ui struct
 */
UI *ui_init(void);

/*
 * Add a line to the scroll window
 *
 * If l = 0, then ui_addline() will attempt to figure out the
 * size of the string.  NOTE:  The string MUST be null-terminated.
 */
void ui_addline(UI *ui, size_t l, char *s);


/*
 * ui_scrollup() and ui_scrolldown() scroll the text area by exactly
 * half of the screen height
 */
void ui_scrollup(UI *ui);
void ui_scrolldown(UI *ui);
inline void ui_repaint(UI *ui);
int ui_printf(UI *ui, char *format, ...);
inline int waddch_stub(WINDOW *w, chtype c);
void ui_chomp(char *s);

/*
 * Some utility functions stolen from the K&R book.  Needed by ui_printf()
 */
void portable_itoa(int value, char *str, int base);
void strreverse(char* begin, char* end);

#endif /* UI_H */
