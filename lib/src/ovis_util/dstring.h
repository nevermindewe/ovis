/*
 *  dynamic string
 *  @TODO stick license here
 */

/** @file
 *  Dynamic String Utilities.
 *  These routines are modifications of TCL code by John Osterhout at
 *  Berkeley, as allowed by the TCL distribution license.  See dstring.c
 *  for the details. There are minor differences internally.
 *
 * This implementation is biased toward large strings, because when you
 * know you need only small strings, you can usually determine a good
 * upper bound by inspection and use a fixed buffer.
 *
 * When used with capacity/length under DSTRING_STATIC_SIZE
 * these dstrings will not leak even if you forget to free because
 * malloc will never be needed internally.
 * Of course any char* turned over to the caller may leak.
 *
 * Example:
char *createfoo ()
{
	int i;
	dsinit;
	for (i=0; i < 10000; i++) {
		dscat("1 year good luck ");
	}
	return dsdone;
}

 * Extensions:
 * An version with arbitrarily large static size is available
 * in big_dstring.h. It trades speed for slight binary size increase.
 */

#ifndef DSTRING_H
#define DSTRING_H

/**	@addtogroup ovis_util_dstring General Dynamic String
	@{
*/
#define DSTRING_STATIC_SIZE 200
#define DSTRING_ALL -1

/** Dynamic string data structure. Max size INT_MAX. */
typedef struct dstring {
  char *string;   /**< Points to beginning of string:  either
                       staticSpace below or a malloc'ed array. */
  int length;     /**< Number of non-NULL characters in the string. */
  int capacity;   /**< Total number of bytes available for the
                       string and its terminating NULL char. */
  char staticSpace[DSTRING_STATIC_SIZE];
                   /**< Space to use in common case where string is small. */
} dstring_t;

/*----------------------------------------------------------------------*/
/**
 *	Returns the current length of the string.
 *	The return value is the number of non-NULL characters in
 *  the string, an integer.  dsPtr may not be NULL (not
 *  checked - crash probable).
 *
 *	@param dsPtr dstring *, pointer to a structure
 *               describing the dynamic string to query.
 */
extern inline int dstrlen(const dstring_t *dsPtr) { return dsPtr->length; }


/*----------------------------------------------------------------------*/
/**
 *	Returns the current value of the string.
 *	The return value is a pointer to the first character in the
 *  string, a char*.  The client should not free or modify this
 *  value unless they can prove they will not overrun the internal string.
 *   dsPtr is never null if the string has been initialized.
 *
 *	@param dsPtr dstring *, pointer to a structure
 *               describing the dynamic string to query.
 */
extern inline const char *dstrval(const dstring_t *dsPtr) { return dsPtr->string;}

/*----------------------------------------------------------------------*/
/**
 *	Appends more characters to the specified dynamic string.
 *	Length bytes from string (or all of string if length is less
 *	than zero) are added to the current value of the string.  If
 *  string is shorter than length, only the length of string
 *  characters are appended.  The resulting value of the
 *  dynamic string is always null-terminated.
 *  <p />
 *  Memory	gets reallocated if needed to accomodate the string's
 *  new size.  Neither dpPtr nor string may be NULL (checked by
 *  assertion).
 *
 *  @param dsPtr  Structure describing dynamic string (non-NULL).
 *  @param string String to append (non-NULL).  If length is -1
 *                then this must be null-terminated.
 *  @param length Number of characters from string to append. If
 *                < 0, then append all of string, up to null at end.
 *  @return Returns the new value of the dynamic string.
 */
extern char *dstrcat( dstring_t *dsPtr,
                     const char *string,
                     int length);

/*----------------------------------------------------------------------*/
/**
 *	Frees up any memory allocated for the dynamic string and
 *	reinitializes the string to an empty state.  The previous
 *  contents of the dynamic string are lost, and the new value
 *  is an empty string.  Note that dsPtr may not be NULL
 *  (checked by assertion).
 *
 *  @param dsPtr Structure describing dynamic string (non-NULL).
*/
extern void dstr_free(dstring_t *dsPtr);

/*----------------------------------------------------------------------*/
/**
 *Initializes a dynamic string, dropping any previous contents
 *of the string.  dstr_free() or extract should have been called already
 *if the dynamic string was previously in use.  The dynamic string
 *  is initialized to be empty.  The passed pointer dsPtr may not
 *  be NULL (checked by assertion).
 *
 *  @param dsPtr Pointer to structure for dynamic string (non-NULL).
 */
extern void dstr_init(dstring_t *dsPtr);


/*----------------------------------------------------------------------*/
/**
 * Init a dstring with capacity cap. If cap is < DSTRING_STATIC_SIZE,
 * then equivalent to dstr_init(dsPtr, DSTRING_STATIC_SIZE);
 * Handy when you want to avoid growing and know you have a big string
 * to build.
 */
extern void dstr_init2(dstring_t *dsPtr, int cap);

/*----------------------------------------------------------------------*/
/**
 *	Returns a *copy* of the string content.
 *  The returned string is owned by the caller, who is responsible
 *  for free'ing it when done with it.  The dynamic string itself
 *  is reinitialized to an empty string.  dsPtr may not be NULL
 *  (checked by assertion).
 *
 *  @param dsPtr dsPtr Dynamic string holding the returned result.
 *  @return Returns a copy of the original value of the dynamic string.
*/
extern char *dstr_extract(dstring_t *dsPtr);

/*----------------------------------------------------------------------*/
/**
 *	Truncates a dynamic string to a given length without freeing
 *	up its storage. 	The length of dsPtr is reduced to length
 *  unless it was already shorter than that.  Passing a length
 *  < 0 sets the new length to zero.  dsPtr may not be NULL
 *  (checked by assertion).
 *
 *  @param dsPtr  Structure describing dynamic string (non-NULL).
 *  @param length New maximum length for the dynamic string.
 */
extern void dstr_trunc(dstring_t *dsPtr, int length);

/*----------------------------------------------------------------------*/
/**
 *	Sets the value of the dynamic string to the specified string.
 *  String must be null-terminated.
 *  Memory gets reallocated if needed to accomodate the string's new
 *  size.  Neither dsPtr nor string may be NULL (checked by assertion).
 *
 *  @param dsPtr   Structure describing dynamic string (non-NULL).
 *  @param string  String to append (non-NULL, null-terminated).
 *  @return Returns the new value of the dynamic string.
 */
extern char *dstr_set(dstring_t *dsPtr, const char *string);

#if 0 /* macros for convenience in typical use of one dynamic string in a function */
/* paste as needed in application code. */
/** declare and init a dstring named ds */
#define dsinit \
	dstring_t ds; \
	dstr_init(&ds)

/** declare and init an oversized dstring named ds with initial capacity cap.*/
#define dsinit2(cap) \
	dstring_t ds; \
	dstr_init2(&ds,cap)

/** append a dstring with  null terminated string char_star_x.*/
#define dscat(char_star_x) \
	dstrcat(&ds, char_star_x, DSTRING_ALL)

/** create real string (char *) from ds and reset ds, freeing any internal memory allocated. returns a char* the caller must free later. */
#define dsdone \
	dstr_extract(&ds)

#endif

/* @} */

#endif /* DSTRING_H */

