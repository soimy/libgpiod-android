%module gpiodroid 

// Add necessary symbols to generate header
%{
#include "gpiod.hpp"
using namespace gpiod;
%}
// Define the __attribute__ macro because SWIG doesn't know of its existence
// and gets confused.
#define __attribute__(x)

// This is really ugly to manually define the timespec type from time.h
// however SWIG can't process the file.  This seems like a shocking omission
// or problem with SWIG and any interface to POSIX libraries--something is
// clearly not right and needs to be investigated (cannot find any info online
// about this issue).  For now just force the timespec type to be defined
// using basic types.
// struct timespec
// {
//   long tv_sec;
//   long tv_nsec;
// };

%include "gpiod.hpp"
%include "gpiodcxx/chip-info.hpp"
%include "gpiodcxx/chip.hpp"
%include "gpiodcxx/edge-event-buffer.hpp"
%include "gpiodcxx/edge-event.hpp"
%include "gpiodcxx/exception.hpp"
%include "gpiodcxx/info-event.hpp"
%include "gpiodcxx/line-config.hpp"
%include "gpiodcxx/line-info.hpp"
%include "gpiodcxx/line-request.hpp"
%include "gpiodcxx/line-settings.hpp"
%include "gpiodcxx/line.hpp"
%include "gpiodcxx/misc.hpp"
%include "gpiodcxx/request-builder.hpp"
%include "gpiodcxx/request-config.hpp"
%include "gpiodcxx/timestamp.hpp"
