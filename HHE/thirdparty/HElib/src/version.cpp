#include <helib/version.h>

namespace helib {

// This is stored in the compiled library.
static constexpr char versionInLib[] = "v2.1.0";

const char* version::libString() { return versionInLib; }

} // namespace helib
