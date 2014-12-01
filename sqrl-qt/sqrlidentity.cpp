#include "SqrlIdentity.h"
#include <QDebug>

SqrlIdentity::SqrlIdentity() {
  // Creating a new SQRL identity.
  // **LOTS** of entropy here.
  qDebug() << "entropy here";
}
