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
