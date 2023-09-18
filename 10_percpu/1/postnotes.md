get_cpu() on top of returning the current processor number also disables kernel preemption.
put_cpu() enables kernel preemption.

Why is disabling kernel preemption needed
=========================================

Just consider, for instance, what would happen 
	if a kernel control path gets the address of its local copy of a per-CPU variable, 
	then it is preempted and 
	moved to another CPU: the address still refers to the element of the previous CPU.

