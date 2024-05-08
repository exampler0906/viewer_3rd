/********************************************************************************

  boolSupport.h

  Some compilers don't support bool, TRUE, and FALSE, even though they are ANSI
  standard.  Sigh . . .  

  If you define a bool, usually you have to match a type which is used for that
  purpose in some other system headers, for example the C++ IO headers.  Failure
  to do so generally results in bad crazyness at compile time.

  In order to support binary interchange between various machines (SGI's and PC's
  for example) we can't change our underlying RESCUEBOOL type from machine to machine.
  Furthermore, for historical reasons we have settled on "RESCUESHORT" for RESCUEBOOL (and it
  is also handy for polymorphing if bool's underlying type is not the same as any
  other underlying type that we use.

  So we have to use a fake RESCUEBOOL type even on compilers that actually HAVE a real
  RESCUEBOOL type.

  Rod Hanks   March, 1999

***********************************************************************************/

#ifndef RESCUEBOOL
#define RESCUEBOOL RESCUESHORT
#endif

#ifndef TRUE
#define TRUE 1
#endif

#ifndef FALSE
#define FALSE 0
#endif


