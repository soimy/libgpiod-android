%module libgpiod

%{
#include "../../../include/gpiod.h"
#include "../../../tools/tools-common.h"
%}

// Define the __attribute__ macro because SWIG doesn't know of its existence
// and gets confused.
#define __attribute__(x)

%include "../../../include/gpiod.h"
%include "../../tools/tools-common.h"

