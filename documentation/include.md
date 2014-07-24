## Direct Include
For most projects, it's perfectly acceptable to embed Baseline directly, without the use of shared or static libraries. To do this, copy `Baseline/sources` into your source tree and rename it to `utilities`, or something of that sort. There are no external dependencies, so your compiler flags needn't change.

Then an `#include "utilities/_x_.h"` will suffice.
