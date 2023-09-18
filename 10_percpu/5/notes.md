Per-CPU Data at Runtime
========================

Dynamically allocated per-CPU variables are also possible

void *alloc_percpu(type); /* a macro */
void *__alloc_percpu(size_t size, size_t align);
void free_percpu(const void *);

The alloc_percpu() macro allocates one instance of an object of the given type for every processor on the system

It is a wrapper around __alloc_percpu(), which takes the actual number of bytes to allocate as a parameter and the number of bytes on which to align the allocation.

struct abc = alloc_percpu(struct abc);
is the same as
struct abc = __alloc_percpu(sizeof (struct abc), __alignof__ (struct abc));

A call to alloc_percpu()or __alloc_percpu() returns a pointer, which is used to indirectly reference the dynamically created per-CPU data.

A corresponding call to free_percpu() frees the given data on all processors

get_cpu_var(ptr); /* return a void pointer to this processor’s copy of ptr */
put_cpu_var(ptr); /* done; enable kernel preemption */
