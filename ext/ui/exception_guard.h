#ifndef RUBY_NATIVE_EXCEPTION_GUARD_H
#define RUBY_NATIVE_EXCEPTION_GUARD_H

#include <YUIException.h>

//use this same as try beginning
#define YEXCEPTION_TRY \
  try {

// use this at the end of guarded block
// It is defined this way to be DRY and allow easy changes
// in exception handling like introducing own class or create own hierarchy
// coresponding to libYUI hierarchy
#define YEXCEPTION_CATCH \
  } catch (YUIException e) { \
    rb_raise(rb_eRuntimeError,e.msg().c_str()); \
  }

#endif
