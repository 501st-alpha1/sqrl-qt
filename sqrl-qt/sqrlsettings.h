#ifndef SQRLSETTINGS_H
#define SQRLSETTINGS_H

#include <QDebug>

class SqrlSettings : QObject {
  Q_OBJECT

 public:
  SqrlSettings();
  bool getOption(int optCode);

  // Options Flags
  static const int OPT_CHECK_FOR_UPDATES = 0x0001;
  static const int OPT_ALWAYS_ASK_FOR_IDENTITY = 0x0002;
  static const int OPT_SQRL_ONLY = 0x0004;
  static const int OPT_HARD_LOCK = 0x0008;
  static const int OPT_WARN_MITM = 0x0010;
  static const int OPT_WIPE_HINT_SUSPEND = 0x0020;
  static const int OPT_WIPE_HINT_USER_CHANGE = 0x0040;
  static const int OPT_WIPE_HINT_IDLE = 0x0080;

 private:
  int options;
};

#endif
