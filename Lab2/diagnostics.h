#ifndef _DIAGNOSTICS_H_
#define _DIAGNOSTICS_H_

#define DIAG_ERROR 0
#define DIAG_APPLICATION 1
#define DIAG_FUNCTION 2
#define DIAG_VERBOSE 3

void diag_set_level(char *prog, int level);

void diag_print(int level, char *func, char *diag);

#endif /* _DIAGNOSTICS_H_ */
