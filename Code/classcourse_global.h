#pragma once
#ifndef CLASSCOURSE_GLOBAL_H
#define CLASSCOURSE_GLOBAL_H

#include <QtCore/qglobal.h>
#include <QString>
#include <QVector>
#include <QtSql/qsqldatabase.h>
#include <QtSql/qsqlerror.h>
#include <QtSql/qsqlquery.h>

#if defined(CLASSCOURSE_LIBRARY)
#define CLASSCOURSE_EXPORT Q_DECL_EXPORT
#else
#define CLASSCOURSE_EXPORT Q_DECL_IMPORT
#endif

#endif // CLASSCOURSE_GLOBAL_H
