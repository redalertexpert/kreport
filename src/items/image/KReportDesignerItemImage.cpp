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

#include "KReportDesignerItemImage.h"
#include "KReportDesignerItemBase.h"
#include "KReportDesigner.h"

#include <KPropertySet>
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QDomDocument>
#include <QPainter>

//
// ReportEntitiesImage
//
// contructors/deconstructors

void KReportDesignerItemImage::init(QGraphicsScene *scene, KReportDesigner *d)
{
    //kreportpluginDebug();
    if (scene)
        scene->addItem(this);

    KReportDesignerItemRectBase::init(&m_pos, &m_size, m_set, d);

    connect(m_set, SIGNAL(propertyChanged(KPropertySet&,KProperty&)),
            this, SLOT(slotPropertyChanged(KPropertySet&,KProperty&)));

    m_controlSource->setListData(m_reportDesigner->fieldKeys(), m_reportDesigner->fieldNames());
    setZValue(Z);
}

KReportDesignerItemImage::KReportDesignerItemImage(KReportDesigner * rw, QGraphicsScene* scene, const QPointF &pos)
        : KReportDesignerItemRectBase(rw)
{
    Q_UNUSED(pos);
    //kreportpluginDebug();
    init(scene, rw);
    setSceneRect(properRect(*rw, KREPORT_ITEM_RECT_DEFAULT_WIDTH, KREPORT_ITEM_RECT_DEFAULT_WIDTH));
    m_name->setValue(m_reportDesigner->suggestEntityName(typeName()));
}

KReportDesignerItemImage::KReportDesignerItemImage(const QDomNode & element, KReportDesigner * rw, QGraphicsScene* scene)
        : KReportItemImage(element), KReportDesignerItemRectBase(rw)
{
    init(scene, rw);
    setSceneRect(m_pos.toScene(), m_size.toScene());
}

KReportDesignerItemImage* KReportDesignerItemImage::clone()
{
    QDomDocument d;
    QDomElement e = d.createElement(QLatin1String("clone"));
    QDomNode n;
    buildXML(&d, &e);
    n = e.firstChild();
    return new KReportDesignerItemImage(n, designer(), 0);
}

KReportDesignerItemImage::~KReportDesignerItemImage()
{
    // do we need to clean anything up?
}

void KReportDesignerItemImage::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);

    // store any values we plan on changing so we can restore them
    QPen  p = painter->pen();

    if (isInline()) {
        //QImage t_img = _image;
        QImage t_img = m_staticImage->value().value<QPixmap>().toImage();
        if (mode() == QLatin1String("stretch")) {
            t_img = t_img.scaled(rect().width(), rect().height(), Qt::KeepAspectRatio);
        }
        painter->drawImage(rect().left(), rect().top(), t_img, 0, 0, rect().width(), rect().height());
    } else {
        painter->drawText(rect(), 0, dataSourceAndObjectTypeName(itemDataSource(), QLatin1String("image")));
    }

    //Draw a border so user knows the object edge
    painter->setPen(QPen(Qt::lightGray));
    painter->drawRect(rect());


    drawHandles(painter);

    // restore an values before we started just in case
    painter->setPen(p);
}

void KReportDesignerItemImage::buildXML(QDomDocument *doc, QDomElement *parent)
{
    QDomElement entity = doc->createElement(QLatin1String("report:") + typeName());

    // properties
    addPropertyAsAttribute(&entity, m_name);
    addPropertyAsAttribute(&entity, m_resizeMode);
    entity.setAttribute(QLatin1String("report:z-index"), zValue());
    buildXMLRect(doc, &entity, &m_pos, &m_size);


    if (isInline()) {
        QDomElement map = doc->createElement(QLatin1String("report:inline-image-data"));
        map.appendChild(doc->createTextNode(QLatin1String(inlineImageData())));
        entity.appendChild(map);
    } else {
        addPropertyAsAttribute(&entity, m_controlSource);
    }

    parent->appendChild(entity);
}

void KReportDesignerItemImage::slotPropertyChanged(KPropertySet &s, KProperty &p)
{
    if (p.name() == "name") {
        //For some reason p.oldValue returns an empty string
        if (!m_reportDesigner->isEntityNameUnique(p.value().toString(), this)) {
            p.setValue(m_oldName);
        } else {
            m_oldName = p.value().toString();
        }
    }

    KReportDesignerItemRectBase::propertyChanged(s, p);
    if (m_reportDesigner) m_reportDesigner->setModified(true);
}

void KReportDesignerItemImage::mousePressEvent(QGraphicsSceneMouseEvent * event)
{
    m_controlSource->setListData(m_reportDesigner->fieldKeys(), m_reportDesigner->fieldNames());
    KReportDesignerItemRectBase::mousePressEvent(event);
}
