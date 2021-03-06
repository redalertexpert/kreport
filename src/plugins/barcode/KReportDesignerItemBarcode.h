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


#ifndef KREPORTDESIGNERITEMBARCODE_H
#define KREPORTDESIGNERITEMBARCODE_H

#include "KReportDesignerItemRectBase.h"
#include "KReportItemBarcode.h"

#include <KPropertySet>

//
// ReportEntityBarcode
//
class KReportDesignerItemBarcode : public KReportItemBarcode, public KReportDesignerItemRectBase
{
    Q_OBJECT
public:
    KReportDesignerItemBarcode(KReportDesigner *, QGraphicsScene* scene, const QPointF &pos);
    KReportDesignerItemBarcode(const QDomNode & element, KReportDesigner *, QGraphicsScene* scene);

    virtual ~KReportDesignerItemBarcode();
    virtual void buildXML(QDomDocument *doc, QDomElement *parent);
    virtual void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget = 0);

    virtual KReportDesignerItemBarcode* clone();


protected:
    virtual void mousePressEvent(QGraphicsSceneMouseEvent * event);

private:
    void init(QGraphicsScene*, KReportDesigner*);

    QRect getTextRect();

private Q_SLOTS:
    void slotPropertyChanged(KPropertySet &, KProperty &);
};

#endif
