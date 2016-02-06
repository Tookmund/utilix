/* Borrow file permissions from coreutils system.h
 * http://www.gnu.org/software/coreutils/coreutils.html
 */

/* Commonly used file permission combination.  */
#define MODE (S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH)
