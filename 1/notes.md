Per CPU Variables
=================

The simplest and most efficient synchronization technique consists of declaring kernel variables as per-CPU Variables.

Basically a per CPU Variables is an array of data structures, one element  per each CPU in the system.

A CPU should not access the elements  of the array corresponding to other CPU.

It can freely read and modify its own element without fear of race conditions, because it is the only CPU Entitled to do so.

The elements of the per-CPU array are aligned in main memory so that each data structure falls on a different line of the hardware cache


