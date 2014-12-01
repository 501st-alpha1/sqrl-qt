#include "SqrlIdentity.h"
#include <QDebug>

SqrlIdentity::SqrlIdentity() {
  // Creating a new SQRL identity.
  // **LOTS** of entropy here.
  qDebug() << "lots of entropy here";
  qDebug() << "Security warning: don't use this key for anything but testing!";
}
