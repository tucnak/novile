/*
 * This file is part of the Novile Editor
 * This program is free software licensed under the GNU LGPL. You can
 * find a copy of this license in LICENSE in the top directory of
 * the source code.
 *
 * Copyright 2013    Illya Kovalevskyy   <illya.kovalevskyy@gmail.com>
 *
 */

#ifndef NOVILE_DEBUG_H
#define NOVILE_DEBUG_H

#include <QtCore/QDebug>

#ifdef NOVILE_VERBOSE_OUTPUT
  inline QDebug mDebug() { return QDebug(QtDebugMsg); }
#else
  #define mDebug() if(false) QDebug(QtDebugMsg)
#endif

#endif // NOVILE_DEBUG_H
