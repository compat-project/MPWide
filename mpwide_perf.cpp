#include "mpwide_perf.h"
#include "MPWide.h"

/* Expose static getter function from `env' C++ class as a C function */
int MPWIDE_Perf_Get_Counter(mpwide_perf_counter_t id, uint64_t *value) {
	return get_perf_counter(id, value);
}

bool MPWIDE_Perf_In_Call(struct timespec *start_time, mpwide_perf_counter_t *id) {
	return is_in_call(start_time, id);
}

const char * MPWIDE_Perf_Dump(void) {
	return get_perf_string();
}
