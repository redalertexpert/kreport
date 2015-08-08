/* This file is part of the KDE project
 * Copyright (C) 2007-2010 by Adam Pigg (adam@piggz.co.uk)
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "KoReportData.h"
#include <QDebug>
#include <QVariant>

KoReportData::~KoReportData()
{
}

KoReportData::SortedField::SortedField()
    : order(Qt::AscendingOrder)
{
}

QStringList KoReportData::fieldKeys() const
{
    return fieldNames();
}

QString KoReportData::sourceName() const
{
    return QString();
}

void KoReportData::setSorting(const QList<SortedField> &sorting)
{
    Q_UNUSED(sorting);
}

void KoReportData::addExpression(const QString &field, const QVariant &value, char relation)
{
    Q_UNUSED(field);
    Q_UNUSED(value);
    Q_UNUSED(relation);
}

#ifdef KREPORT_SCRIPTING
QStringList KoReportData::scriptList() const
{
    return QStringList();
}

QString KoReportData::scriptCode(const QString &script) const
{
    Q_UNUSED(script);
    return QString();
}
#endif

QStringList KoReportData::dataSources() const
{
    return QStringList();
}

QStringList KoReportData::dataSourceNames() const
{
    qDebug() << "Returning data sources";
    return dataSources();
}

KoReportData* KoReportData::data(const QString &source)
{
    Q_UNUSED(source);
    return 0;
}
