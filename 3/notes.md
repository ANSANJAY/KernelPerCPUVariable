You can access another processor's copy of the variable with:

per_cpu(variable, int cpu_id);

If you write code that involves processors reaching into each other's per-CPU variables, you, of course, have to implement a locking scheme that makes that access safe.


