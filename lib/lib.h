/* $NetBSD: lib.h,v 1.2 2003/09/02 08:28:33 jlam Exp $ */

/* from FreeBSD Id: lib.h,v 1.25 1997/10/08 07:48:03 charnier Exp */

/*
 * FreeBSD install - a package for the installation and maintainance
 * of non-core utilities.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * Jordan K. Hubbard
 * 18 July 1993
 *
 * Include and define various things wanted by the library routines.
 *
 */

#ifndef _INST_LIB_LIB_H_
#define _INST_LIB_LIB_H_

#if HAVE_CONFIG_H
#include "config.h"
#endif
#include <nbcompat.h>
#if HAVE_SYS_PARAM_H
#include <sys/param.h>
#endif
#if HAVE_SYS_STAT_H
#include <sys/stat.h>
#endif
#if HAVE_SYS_FILE_H
#include <sys/file.h>
#endif
#if HAVE_SYS_QUEUE_H
#include <sys/queue.h>
#endif

#if HAVE_CTYPE_H
#include <ctype.h>
#endif
#if HAVE_DIRENT_H
#include <dirent.h>
#endif
#if HAVE_STDIO_H
#include <stdio.h>
#endif
#if HAVE_STDLIB_H
#include <stdlib.h>
#endif
#if HAVE_STDARG_H
#include <stdarg.h>
#endif
#if HAVE_STRING_H
#include <string.h>
#endif
#if HAVE_UNISTD_H
#include <unistd.h>
#endif

#include "path.h"

/* Macros */
#define SUCCESS	(0)
#define	FAIL	(-1)

#ifndef TRUE
#define TRUE	(1)
#endif

#ifndef FALSE
#define FALSE	(0)
#endif

/* Usually "rm", but often "echo" during debugging! */
#define REMOVE_CMD	"rm"

/* Usually "rm", but often "echo" during debugging! */
#define RMDIR_CMD	"rmdir"

/* Define tar as a string, in case it's called gtar or something */
#ifndef TAR_CMD
#define TAR_CMD	"tar"
#endif

/* Define gzip and bzip2, used to unpack binary packages */
#ifndef GZIP_CMD
#define GZIP_CMD "gzip"
#endif

#ifndef BZIP2_CMD
#define BZIP2_CMD "bzip2"
#endif

/* Define ftp as a string, in case the ftp client is called something else */
#ifndef FTP_CMD
#define FTP_CMD "ftp"
#endif

#ifndef CHOWN_CMD
#define CHOWN_CMD "chown"
#endif

#ifndef CHMOD_CMD
#define CHMOD_CMD "chmod"
#endif

#ifndef CHGRP_CMD
#define CHGRP_CMD "chgrp"
#endif

/* The names of our "special" files */
#define CONTENTS_FNAME		"+CONTENTS"
#define COMMENT_FNAME		"+COMMENT"
#define DESC_FNAME		"+DESC"
#define INSTALL_FNAME		"+INSTALL"
#define DEINSTALL_FNAME		"+DEINSTALL"
#define REQUIRE_FNAME		"+REQUIRE"
#define REQUIRED_BY_FNAME	"+REQUIRED_BY"
#define DISPLAY_FNAME		"+DISPLAY"
#define MTREE_FNAME		"+MTREE_DIRS"
#define BUILD_VERSION_FNAME	"+BUILD_VERSION"
#define BUILD_INFO_FNAME	"+BUILD_INFO"
#define SIZE_PKG_FNAME		"+SIZE_PKG"
#define SIZE_ALL_FNAME		"+SIZE_ALL"
#define PRESERVE_FNAME		"+PRESERVE"
#define VIEWS_FNAME		"+VIEWS"
#define DEPOT_FNAME		"+DEPOT"

#define CMD_CHAR		'@'	/* prefix for extended PLIST cmd */

/* The name of the "prefix" environment variable given to scripts */
#define PKG_PREFIX_VNAME	"PKG_PREFIX"

#define	PKG_PATTERN_MAX	FILENAME_MAX	/* max length of pattern, including nul */
#define	PKG_SUFFIX_MAX	10	/* max length of suffix, including nul */

/* This should only happen on 1.3 and 1.3.1, not 1.3.2 and up */
#ifndef TAILQ_FIRST
#define TAILQ_FIRST(head)               ((head)->tqh_first)
#define TAILQ_NEXT(elm, field)          ((elm)->field.tqe_next)
#endif

enum {
	ReadWrite,
	ReadOnly
};


/* Enumerated constants for plist entry types */
typedef enum pl_ent_t {
	PLIST_SHOW_ALL = -1,
	PLIST_FILE,		/*  0 */
	PLIST_CWD,		/*  1 */
	PLIST_CMD,		/*  2 */
	PLIST_CHMOD,		/*  3 */
	PLIST_CHOWN,		/*  4 */
	PLIST_CHGRP,		/*  5 */
	PLIST_COMMENT,		/*  6 */
	PLIST_IGNORE,		/*  7 */
	PLIST_NAME,		/*  8 */
	PLIST_UNEXEC,		/*  9 */
	PLIST_SRC,		/* 10 */
	PLIST_DISPLAY,		/* 11 */
	PLIST_PKGDEP,		/* 12 */
	PLIST_MTREE,		/* 13 */
	PLIST_DIR_RM,		/* 14 */
	PLIST_IGNORE_INST,	/* 15 */
	PLIST_OPTION,		/* 16 */
	PLIST_PKGCFL,		/* 17 */
	PLIST_BLDDEP		/* 18 */
}       pl_ent_t;

/* Types */
typedef unsigned int Boolean;

/* This structure describes a packing list entry */
typedef struct plist_t {
	struct plist_t *prev;	/* previous entry */
	struct plist_t *next;	/* next entry */
	char   *name;		/* name of entry */
	Boolean marked;		/* whether entry has been marked */
	pl_ent_t type;		/* type of entry */
}       plist_t;

/* This structure describes a package's complete packing list */
typedef struct package_t {
	plist_t *head;		/* head of list */
	plist_t *tail;		/* tail of list */
}       package_t;

#define CHECKSUM_HEADER	"MD5:"

enum {
	ChecksumHeaderLen = 4,	/* strlen(CHECKSUM_HEADER) */
	ChecksumLen = 16,
	LegibleChecksumLen = 33
};

/* List of packages */
typedef struct _lpkg_t {
	TAILQ_ENTRY(_lpkg_t) lp_link;
	char   *lp_name;
}       lpkg_t;
TAILQ_HEAD(_lpkg_head_t, _lpkg_t);
typedef struct _lpkg_head_t lpkg_head_t;

/* Type of function to be handed to findmatchingname; return value of this
 * is currently ignored */
typedef int (*matchfn) (const char *, void *);

/* If URLlength()>0, then there is a ftp:// or http:// in the string,
 * and this must be an URL. Hide this behind a more obvious name. */
#define IS_URL(str)	(URLlength(str) > 0)

#define IS_STDIN(str)	((str) != NULL && !strcmp((str), "-"))
#define IS_FULLPATH(str)	((str) != NULL && (str)[0] == '/')

/* Prototypes */
/* Misc */
int     vsystem(const char *,...)
	__attribute__((__format__(__printf__, 1, 2)));
void    cleanup(int);
char   *make_playpen(char *, size_t, size_t);
char   *where_playpen(void);
void    leave_playpen(char *);
uint64_t min_free(char *);
void    save_dirs(char **c, char **p);
void    restore_dirs(char *c, char *p);
void    show_version(void);
int	fexec(const char *, ...);
int	fcexec(const char *, const char *, ...);

/* String */
char   *get_dash_string(char **);
void    str_lowercase(char *);
const char *basename_of(const char *);
const char *dirname_of(const char *);
const char *suffix_of(const char *);
int     pmatch(const char *, const char *);
int     findmatchingname(const char *, const char *, matchfn, void *); /* doesn't really belong to "strings" */
char   *findbestmatchingname(const char *, const char *);	/* neither */
int     ispkgpattern(const char *);
char   *strnncpy(char *to, size_t tosize, char *from, size_t cc);
void	strip_txz(char *buf, char *sfx, const char *fname);

/* callback functions for findmatchingname */
int     findbestmatchingname_fn(const char *, void *);	/* neither */
int     note_whats_installed(const char *, void *);
int     add_to_list_fn(const char *, void *);


/* File */
Boolean fexists(const char *);
Boolean isdir(const char *);
Boolean islinktodir(const char *);
Boolean isemptydir(const char *);
Boolean isemptyfile(const char *);
Boolean isfile(const char *);
Boolean isempty(const char *);
int     URLlength(const char *);
char   *fileGetURL(const char *);
const char *fileURLFilename(const char *, char *, int);
const char *fileURLHost(const char *, char *, int);
char   *fileFindByPath(const char *);
char   *fileGetContents(char *);
Boolean make_preserve_name(char *, size_t, char *, char *);
void    write_file(char *, char *);
void    copy_file(char *, char *, char *);
void    move_file(char *, char *, char *);
int     delete_hierarchy(char *, Boolean, Boolean);
int     unpack(const char *, const char *);
void    format_cmd(char *, size_t, char *, char *, char *);

/* ftpio.c: FTP handling */
int	expandURL(char *expandedurl, const char *wildcardurl);
int	unpackURL(const char *url, const char *dir);
int	ftp_cmd(const char *cmd, const char *expectstr);
int	ftp_start(char *base);
void	ftp_stop(void);

/* Packing list */
plist_t *new_plist_entry(void);
plist_t *last_plist(package_t *);
plist_t *find_plist(package_t *, pl_ent_t);
char   *find_plist_option(package_t *, char *name);
void    plist_delete(package_t *, Boolean, pl_ent_t, char *);
void    free_plist(package_t *);
void    mark_plist(package_t *);
void    csum_plist_entry(char *, plist_t *);
void    add_plist(package_t *, pl_ent_t, const char *);
void    add_plist_top(package_t *, pl_ent_t, const char *);
void    delete_plist(package_t *pkg, Boolean all, pl_ent_t type, char *name);
void    write_plist(package_t *, FILE *, char *);
void    read_plist(package_t *, FILE *);
int     plist_cmd(char *, char **);
int     delete_package(Boolean, Boolean, package_t *);

/* Package Database */
int     pkgdb_open(int);
void    pkgdb_close(void);
int     pkgdb_store(const char *, const char *);
char   *pkgdb_retrieve(const char *);
void	pkgdb_dump(void);
int     pkgdb_remove(const char *);
int	pkgdb_remove_pkg(const char *);
char   *_pkgdb_getPKGDB_FILE(char *, unsigned);
char   *_pkgdb_getPKGDB_DIR(void);
void	_pkgdb_setPKGDB_DIR(const char *);

/* List of packages functions */
lpkg_t *alloc_lpkg(const char *);
lpkg_t *find_on_queue(lpkg_head_t *, const char *);
void    free_lpkg(lpkg_t *);

/* For all */
int     pkg_perform(lpkg_head_t *);

/* Externs */
extern Boolean Verbose;
extern Boolean Fake;
extern Boolean Force;
extern Boolean Replace;

#endif				/* _INST_LIB_LIB_H_ */
