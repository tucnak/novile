#ifndef NOVILE_DEBUG_H
#define NOVILE_DEBUG_H

#include <QtCore/QDebug>

#ifdef NOVILE_VERBOSE_OUTPUT
  inline QDebug mDebug() { return QDebug(QtDebugMsg); }
#else
  #define mDebug() if(false) QDebug(QtDebugMsg)
#endif

#endif // NOVILE_DEBUG_H
