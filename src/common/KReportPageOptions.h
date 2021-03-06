/* This file is part of the KDE project
 * Copyright (C) 2001-2007 by OpenMFG, LLC (info@openmfg.com)
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

#ifndef KREPORTPAGEOPTIONS_H
#define KREPORTPAGEOPTIONS_H

#include <QObject>
#include <QString>

#include "kreport_export.h"

class KREPORT_EXPORT KReportPageOptions : public QObject
{
    Q_OBJECT
public:
    KReportPageOptions();
    KReportPageOptions(const KReportPageOptions &);

    KReportPageOptions & operator=(const KReportPageOptions &);

    enum PageOrientation {
        Landscape = 0, // essentially false
        Portrait = 1   // and true
    };

    qreal getMarginTop() const;
    void setMarginTop(qreal v);
    qreal getMarginBottom() const;
    void setMarginBottom(qreal v);
    qreal getMarginLeft() const;
    void setMarginLeft(qreal v);
    qreal getMarginRight() const;
    void setMarginRight(qreal v);

    QSizeF pixelSize() const;

    const QString & getPageSize() const;
    void setPageSize(const QString & s);
    qreal getCustomWidth() const;
    void setCustomWidth(qreal v);
    qreal getCustomHeight() const;
    void setCustomHeight(qreal v);

    PageOrientation getOrientation() const;
    bool isPortrait() const;
    void setOrientation(PageOrientation o);
    void setPortrait(bool yes);

    void setLabelType(const QString &);
    const QString & getLabelType() const;

Q_SIGNALS:
    void pageOptionsChanged();

private:
    qreal m_marginTop;
    qreal m_marginBottom;
    qreal m_marginLeft;
    qreal m_marginRight;

    QString m_pageSize;
    qreal m_customWidth;
    qreal m_customHeight;

    PageOrientation m_orientation;

    QString m_labelType;
};

#endif
