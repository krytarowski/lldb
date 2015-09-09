/* This generated file is for internal use. Do not include it from headers. */

#ifdef CONFIG_H
#error config.h can only be included once
#else
#define CONFIG_H

/* Define to 1 if you have the <ncurses.h> header file. */
#cmakedefine CURSES_HAVE_NCURSES_H

/* Define to 1 if you have the <ncurses/ncurses.h> header file. */
#cmakedefine CURSES_HAVE_NCURSES_NCURSES_H

/* autotools compat */
#ifdef CURSES_HAVE_NCURSES_H
#define HAVE_NCURSES_H 1
#endif

#ifdef CURSES_HAVE_NCURSES_NCURSES_H
#define HAVE_NCURSES_NCURSES_H 1
#endif

#endif // CONFIG_H
