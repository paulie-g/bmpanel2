#ifndef BMPANEL2_THEME_PARSER_H 
#define BMPANEL2_THEME_PARSER_H

#include "util.h"

/* A named theme format entry with optional associated value and children. It
 * is capable of building trees of entries. 
 */
struct theme_format_entry {
	char *name; 
	char *value;

	size_t children_n;
	struct theme_format_entry *children;
};

/* A theme format tree representation. 
 *
 * "dir" is a directory of a theme file.
 *
 * "buf" is a buffer containing modified theme format data (used for in-situ
 * parsing). Usually it's a pointer to a zero-terminated string which
 * represents modified contents of a theme config file. Normally not used
 * directly (private data). 
 *
 * "root" is the root of theme format entries tree. Name and value of this root
 * always point to zero. Only "children_n" and "children" values are
 * meaningful. 
 */
struct theme_format_tree {
	char *dir;
	char *buf;
	struct theme_format_entry root;
};

/* Failed to open file (no rights to read, doesn't exist, etc.) */
#define THEME_FORMAT_BAD_FILE 1
/* Failed to read file contents properly (fseek/ftell/fread fail) */
#define THEME_FORMAT_READ_ERROR 2
/* File was empty, no entries were parsed */
#define THEME_FORMAT_FILE_IS_EMPTY 3

/* Load the "tree" from a file located at "path"/theme. The "tree" structure
 * should be empty (all zeroes) or uninitialized (stack garbage). After
 * successful loading "tree" should be released using "theme_format_free_tree"
 * function when the data isn't needed anymore.
 *
 * RETURNS
 * 	Zero - success.
 * 	Non-zero - error (see defines above).
 */
int theme_format_load_tree(struct theme_format_tree *tree, const char *path);
void theme_format_free_tree(struct theme_format_tree *tree);

/* Find child entry of entry "e" with name "name".
 *
 * RETURNS
 * 	Zero - not found, or entry has no "value".
 * 	Non-zero - the "value" of the entry.
 */
struct theme_format_entry *theme_format_find_entry(struct theme_format_entry *e, 
		const char *name);

/* Same as above, but returns "value" or 0 if not found or no value. */
const char *theme_format_find_entry_value(struct theme_format_entry *e, 
		const char *name);

/* Memory source used for working with theme format trees. */
extern struct memory_source msrc_theme;

#endif /* BMPANEL2_THEME_PARSER_H */
