/* This file is part of the KDE project
 * Copyright (C) 2007-2008 by Adam Pigg (adam@piggz.co.uk)
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

#include "KReportScriptBarcode.h"

#include <KProperty>

namespace Scripting
{

Barcode::Barcode(KReportItemBarcode *b)
{
    m_barcode = b;
}


Barcode::~Barcode()
{
}

QPointF Barcode::position()
{
    return m_barcode->m_pos.toPoint();
}
void Barcode::setPosition(const QPointF& p)
{
    m_barcode->m_pos.setPointPos(p);
}

QSizeF Barcode::size()
{
    return m_barcode->m_size.toPoint();
}
void Barcode::setSize(const QSizeF& s)
{
    m_barcode->m_size.setPointSize(s);
}

int Barcode::horizontalAlignment()
{
    const QString a = m_barcode->m_horizontalAlignment->value().toString().toLower();

    if (a == QLatin1String("left")) {
        return -1;
    }
    if (a == QLatin1String("center")) {
        return 0;
    }
    if (a == QLatin1String("right")) {
        return 1;
    }
    return -1;
}
void Barcode::setHorizonalAlignment(int a)
{
    switch (a) {
    case -1:
        m_barcode->m_horizontalAlignment->setValue(QLatin1String("left"));
        break;
    case 0:
        m_barcode->m_horizontalAlignment->setValue(QLatin1String("center"));
        break;
    case 1:
        m_barcode->m_horizontalAlignment->setValue(QLatin1String("right"));
        break;
    default:
        m_barcode->m_horizontalAlignment->setValue(QLatin1String("left"));
        break;
    }
}

QString Barcode::source()
{
    return m_barcode->m_controlSource->value().toString();
}

void Barcode::setSource(const QString& s)
{
    m_barcode->m_controlSource->setValue(s);
}

QString Barcode::format()
{
    return m_barcode->m_format->value().toString();
}

void Barcode::setFormat(const QString& s)
{
    m_barcode->m_format->setValue(s);
}
}
