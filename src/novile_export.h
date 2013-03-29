/*
 * This file is part of the Novile Editor
 * This program is free software licensed under the GNU LGPL. You can
 * find a copy of this license in LICENSE in the top directory of
 * the source code.
 *
 * Copyright 2013    Illya Kovalevskyy   <illya.kovalevskyy@gmail.com>
 *
 */

#ifndef NOVILE_EXPORT_H
#define NOVILE_EXPORT_H

#include <QtCore/qglobal.h>

#ifndef NOVILE_EXPORT
# if defined(NOVILE_MAKEDLL)
#  define NOVILE_EXPORT Q_DECL_EXPORT
# else
#  define NOVILE_EXPORT Q_DECL_IMPORT
# endif
#endif

#endif // NOVILE_EXPORT_H
