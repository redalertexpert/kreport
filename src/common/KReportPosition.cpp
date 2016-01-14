/* This file is part of the KDE project
 * Copyright (C) 2007-2008 by Adam Pigg (adam@piggz.co.uk)
 * Copyright (C) 2010 Jarosław Staniek <staniek@kde.org>
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

#include "KReportPosition.h"
#include "KReportDpi.h"

#include <KProperty>

#include <QApplication>

KReportPosition::KReportPosition(const KReportUnit& unit)
{
    m_unit = unit;
    m_property = new KProperty("position", toScene(), QCoreApplication::translate("KReportPosition", "Position"));
}

void KReportPosition::setName(const QString& name)
{
    m_property->setName(name.toLatin1());
    m_property->setCaption(name);
}

KReportPosition::~KReportPosition()
{
}

void KReportPosition::setScenePos(const QPointF& pos, UpdatePropertyFlag update)
{
    const qreal x = INCH_TO_POINT(pos.x() / KReportDpi::dpiX());
    const qreal y = INCH_TO_POINT(pos.y() / KReportDpi::dpiY());

    m_pointPos.setX(x);
    m_pointPos.setY(y);

    if (update == UpdateProperty)
        m_property->setValue(toUnit());
}

void KReportPosition::setUnitPos(const QPointF& pos, UpdatePropertyFlag update)
{
    const qreal x = m_unit.fromUserValue(pos.x());
    const qreal y = m_unit.fromUserValue(pos.y());

    m_pointPos.setX(x);
    m_pointPos.setY(y);

    if (update == UpdateProperty)
        m_property->setValue(toUnit());
}

void KReportPosition::setPointPos(const QPointF& pos, UpdatePropertyFlag update)
{
    m_pointPos.setX(pos.x());
    m_pointPos.setY(pos.y());

    if (update == UpdateProperty)
        m_property->setValue(toUnit());
}

void KReportPosition::setUnit(const KReportUnit& u)
{
    m_unit = u;
    m_property->setValue(toUnit());
}

QPointF KReportPosition::toPoint() const
{
    return m_pointPos;
}

QPointF KReportPosition::toScene() const
{
    const qreal x = POINT_TO_INCH(m_pointPos.x()) * KReportDpi::dpiX();
    const qreal y = POINT_TO_INCH(m_pointPos.y()) * KReportDpi::dpiY();

    return QPointF(x, y);
}

QPointF KReportPosition::toUnit() const
{
    const qreal x = m_unit.toUserValue(m_pointPos.x());
    const qreal y = m_unit.toUserValue(m_pointPos.y());

    return QPointF(x, y);
}

