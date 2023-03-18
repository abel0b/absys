#include "absys/parallel.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#if WINDOWS
#include <sysinfoapi.h>
#else
#include <unistd.h>
#include <errno.h>
#endif

int absys_nproc(void) {
  long nprocs = -1;
  long nprocs_max = -1;

#if WINDOWS
#if ABSYS_NPROC_BACKEND_WINDOWS_SYSINFO
	SYSTEM_INFO info;
	GetSystemInfo(&info);
  	nprocs = info.dwNumberOfProcessors;
#else
	DWORD nprocs = GetActiveProcessorCount(ALL_PROCESSOR_GROUPS);
#endif
#else
#ifdef _SC_NPROCESSORS_ONLN
  nprocs = sysconf(_SC_NPROCESSORS_ONLN);

  if (nprocs < 1) {
    fprintf(stderr, "Could not determine number of CPUs online:\n%s\n", strerror (errno));
    exit (EXIT_FAILURE);
  }

  nprocs_max = sysconf(_SC_NPROCESSORS_CONF);

  if (nprocs_max < 1) {
    fprintf(stderr, "Could not determine number of CPUs configured:\n%s\n", strerror (errno));
    exit (EXIT_FAILURE);
  }
#else
  fprintf(stderr, "Could not determine number of CPUs\n");
  exit (EXIT_FAILURE);
#endif
#endif

  return (int)nprocs;
}
