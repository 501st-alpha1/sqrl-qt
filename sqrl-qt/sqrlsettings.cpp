#include "sqrlsettings.h"

// Options Flags
const int OPT_CHECK_FOR_UPDATES = 0x0001;
const int OPT_ALWAYS_ASK_FOR_IDENTITY = 0x0002;
const int OPT_SQRL_ONLY = 0x0004;
const int OPT_HARD_LOCK = 0x0008;
const int OPT_WARN_MITM = 0x0010;
const int OPT_WIPE_HINT_SUSPEND = 0x0020;
const int OPT_WIPE_HINT_USER_CHANGE = 0x0040;
const int OPT_WIPE_HINT_IDLE = 0x0080;

SqrlSettings::SqrlSettings() {
}
