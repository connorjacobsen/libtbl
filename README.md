# libtbl

A simple hash table implementation in C.

_NOTE: This library is currently under development along with another project I am working on. It hasn't yet been extensively tested for performance or memory leaks._

## Usage

You'll need to `include` the `tbl.h` file and link to `tbl.o`.

Simple example:

```c
#include <stdlib.h>
#include "tbl.h"

int
main(int argc, char** argv)
{
    tbl_t* tt = mk_tbl();

    tbl_put(tt, "foo", (void*) 42);
    printf("Foo: %d\n", (int) tbl_get(tt, "foo"));

    return 0;
}
```

Objects are stored in the `tbl` as `void*`, and the library does not perform typecasts for you.

