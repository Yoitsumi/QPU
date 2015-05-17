#pragma once

#if !defined PROC_32BIT & !defined PROC_64BIT
#define PROC_32BIT
#endif


#ifdef PROC_32BIT
typedef signed int reg;
typedef unsigned int ureg;
#elif defined PROC_64BIT
typedef long int reg;
typedef unsigned long int ureg;
#endif
