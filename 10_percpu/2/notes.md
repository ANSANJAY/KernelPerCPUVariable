percpu interface
===================

The 2.6 kernel introduced a new interface, known as percpu, for creating and manipulating per-CPU data.

Creation and manipulation of per-CPU data is simplified with this new approach

The previously discussed method of creating and accessing per-CPU data is still valid and accepted.

This new interface, however, grew out of the needs for a simpler and more powerful method for manipulating per-CPU data on large symmetrical multiprocessing computers.

Header File: <linux/percpu.h>

To create a per-CPU variable at compile time, use this macro

DEFINE_PER_CPU(type, name);

This creates an instance of a variable of type type, named name, for each processor on the system.

E.g 
DEFINE_PER_CPU(int, i);
DEFINE_PER_CPU(int[3], my_array);

If you need a declaration of the variable elsewhere, to avoid compile warnings, the following macro is your friend:

DECLARE_PER_CPU(type, name);

You can manipulate the variables with the get_cpu_var() and put_cpu_var() routines

A call to get_cpu_var() returns an lvalue for the given variable on the current processor. It also disables preemption, which put_cpu_var() correspondingly enables.


What is lvalue?
================

lvalue (locator value) represents an object that occupies some identifiable location in memory (i.e. has an address).

int var;
var = 4;

var is lvalue.

4 = var;       // ERROR!
(var + 1) = 4; // ERROR!

They're not lvalues because both are temporary results of expressions, which don't have an identifiable memory location (i.e. they can just reside in some temporary register for the duration of the computation). 
