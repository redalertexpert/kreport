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

#ifndef KREPORTITEMIMAGE_H
#define KREPORTITEMIMAGE_H

#include "KReportItemBase.h"
#include "KReportPosition.h"
#include "KReportSize.h"

class QDomNode;

namespace Scripting
{
class Image;
}

class KReportItemImage : public KReportItemBase
{
    Q_OBJECT
public:
    KReportItemImage();
    explicit KReportItemImage(const QDomNode & element);
    virtual ~KReportItemImage();

    virtual QString typeName() const;
    virtual int renderSimpleData(OROPage *page, OROSection *section, const QPointF &offset, const QVariant &data, KReportScriptHandler *script);

    virtual QString itemDataSource() const;

protected:
    KProperty * m_controlSource;
    KProperty* m_resizeMode;
    KProperty* m_staticImage;

    void setMode(const QString&);
    void setInlineImageData(const QByteArray &dat, const QString& = QString());
    void setColumn(const QString&);
    QString mode() const;
    bool isInline() const;
    QByteArray inlineImageData() const;

private:
    virtual void createProperties();

    friend class Scripting::Image;
};

#endif
