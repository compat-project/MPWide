#ifndef MPWIDE_PERF_H
#define MPWIDE_PERF_H

#ifdef __cplusplus
extern "C" {
#endif //__cplusplus

#include <stdint.h>
#include <stdbool.h>
#include <time.h>

/* Enum for various MPWIDE performance metrics */
typedef enum {
	MPWIDE_PERF_COUNTER_ADMIN_CALLS,      // Number of admin calls via MPWIDE so far (cumulative value)
	MPWIDE_PERF_COUNTER_ADMIN_DURATION,   // Nanoseconds spent with MPWIDE connection operations so far (cumulative value)
	MPWIDE_PERF_COUNTER_SEND_CALLS,       // Number of send calls via MPWIDE so far (cumulative value)
	MPWIDE_PERF_COUNTER_SEND_DURATION,    // Nanoseconds spent with MPWIDE send operations so far (cumulative value)
	MPWIDE_PERF_COUNTER_SEND_SIZE,        // Number of bytes sent via MPWIDE so far (cumulative value)
	MPWIDE_PERF_COUNTER_RECEIVE_CALLS,    // Number of receive calls via MPWIDE so far (cumulative value)
	MPWIDE_PERF_COUNTER_RECEIVE_DURATION, // Nanoseconds spent with MPWIDE receive operations so far (cumulative value)
	MPWIDE_PERF_COUNTER_RECEIVE_SIZE,     // Number of bytes received via MPWIDE so far (cumulative value)
	MPWIDE_PERF_COUNTER_SENDRECV_CALLS,    // Number of receive calls via MPWIDE so far (cumulative value)
	MPWIDE_PERF_COUNTER_SENDRECV_DURATION, // Nanoseconds spent with MPWIDE receive operations so far (cumulative value)
	MPWIDE_PERF_COUNTER_SENDRECV_SEND_SIZE,     // Number of bytes received via MPWIDE so far (cumulative value)
	MPWIDE_PERF_COUNTER_SENDRECV_RECV_SIZE,     // Number of bytes received via MPWIDE so far (cumulative value)
	MPWIDE_PERF_COUNTER_BARRIER_CALLS,    // Number of calls to MPWIDE barrier
	MPWIDE_PERF_COUNTER_BARRIER_DURATION, // Nanoseconds spent in MPWIDE barriers
	MPWIDE_PERF_COUNTER_LAST      // LAST element for iterating over the enum
} mpwide_perf_counter_t;

/* Struct to store values of a metric type (i.e. sends) */
struct mpwide_perf_t {
	uint64_t calls;    // Total number of calls
	uint64_t duration; // Total time spent in ns
	uint64_t size;     // Total number of sent/received bytes
	uint64_t size2;     // Total number of sent/received bytes
};

/* Returns a C string managed internally by MPWIDE, with a pretty print of the performance values. The return
 * pointer is valid only until the next call to this function. */
const char * MPWIDE_Perf_Dump(void);

/* Writes a performance metric value denoted by id to the location pointed to by value. 
 * Internally forwards the call to the env::MPWIDE_Perf_Get_Counter(mpwide_perf_counter_t id, uint64_t * value) 
 * C++ function.
 * Returns 0 on success, -1 on failure. */
int MPWIDE_Perf_Get_Counter(mpwide_perf_counter_t id, uint64_t *value);

/* Returns true if MPWIDE is inside an API call (send, receive, barrier). 
 * If it is, writes the timestamp of the start of the call to start_time and the counter id of the call duration counter
 * to id (e.g. MPWIDE_PERF_COUNTER_BARRIER_DURATION). If we aren't in any call, sets both start_time and id to NULL. */
bool MPWIDE_Perf_In_Call(struct timespec *start_time, mpwide_perf_counter_t *id);

#ifdef __cplusplus
}
#endif //__cplusplus

#endif //MPWIDE_PERF_H
