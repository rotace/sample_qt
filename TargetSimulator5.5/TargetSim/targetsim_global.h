#ifndef TARGETSIM_GLOBAL_H
#define TARGETSIM_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(TARGETSIM_LIBRARY)
#  define TARGETSIMSHARED_EXPORT Q_DECL_EXPORT
#else
#  define TARGETSIMSHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // TARGETSIM_GLOBAL_H