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

#include "KReportScriptLabel.h"

namespace Scripting
{
Label::Label(KReportItemLabel *l)
{
    m_label = l;
}


Label::~Label()
{
}

QString Label::caption() const
{
    return m_label->text();
}

void Label::setCaption(const QString& c)
{
    m_label->setText(c);
}

int Label::horizontalAlignment() const
{
    const QString a = m_label->m_horizontalAlignment->value().toString().toLower();

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
void Label::setHorizonalAlignment(int a)
{
    switch (a) {
    case -1:
        m_label->m_horizontalAlignment->setValue(QLatin1String("left"));
        break;
    case 0:
        m_label->m_horizontalAlignment->setValue(QLatin1String("center"));
        break;
    case 1:
        m_label->m_horizontalAlignment->setValue(QLatin1String("right"));
        break;
    default:
        m_label->m_horizontalAlignment->setValue(QLatin1String("left"));
        break;
    }
}

int Label::verticalAlignment() const
{
    const QString a = m_label->m_horizontalAlignment->value().toString().toLower();

    if (a == QLatin1String("top")) {
        return -1;
    }
    if (a == QLatin1String("middle")) {
        return 0;
    }
    if (a == QLatin1String("bottom")) {
        return 1;
    }
    return -1;
}
void Label::setVerticalAlignment(int a)
{
    switch (a) {
    case -1:
        m_label->m_verticalAlignment->setValue(QLatin1String("top"));
        break;
    case 0:
        m_label->m_verticalAlignment->setValue(QLatin1String("middle"));
        break;
    case 1:
        m_label->m_verticalAlignment->setValue(QLatin1String("bottom"));
        break;
    default:
        m_label->m_verticalAlignment->setValue(QLatin1String("middle"));
        break;
    }
}

QColor Label::backgroundColor() const
{
    return m_label->m_backgroundColor->value().value<QColor>();
}
void Label::setBackgroundColor(const QColor& c)
{
    m_label->m_backgroundColor->setValue(c);
}

QColor Label::foregroundColor() const
{
    return m_label->m_foregroundColor->value().value<QColor>();
}
void Label::setForegroundColor(const QColor& c)
{
    m_label->m_foregroundColor->setValue(c);
}

int Label::backgroundOpacity() const
{
    return m_label->m_backgroundOpacity->value().toInt();
}
void Label::setBackgroundOpacity(int o)
{
    m_label->m_backgroundOpacity->setValue(o);
}

QColor Label::lineColor() const
{
    return m_label->m_lineColor->value().value<QColor>();
}
void Label::setLineColor(const QColor& c)
{
    m_label->m_lineColor->setValue(c);
}

int Label::lineWeight() const
{
    return m_label->m_lineWeight->value().toInt();
}
void Label::setLineWeight(int w)
{
    m_label->m_lineWeight->setValue(w);
}

int Label::lineStyle() const
{
    return m_label->m_lineStyle->value().toInt();
}
void Label::setLineStyle(int s)
{
    if (s < 0 || s > 5) {
        s = 1;
    }
    m_label->m_lineStyle->setValue(s);
}

QPointF Label::position() const
{
    return m_label->m_pos.toPoint();
}
void Label::setPosition(const QPointF &p)
{
    m_label->m_pos.setPointPos(p);
}

QSizeF Label::size() const
{
    return m_label->m_size.toPoint();
}
void Label::setSize(const QSizeF &s)
{
    m_label->m_size.setPointSize(s);
}
}

