/*
 * Copyright (C) 2007-2016 by Adam Pigg (adam@piggz.co.uk)
 * Copyright (C) 2011-2015 by Radoslaw Wicik (radoslaw@wicik.pl)
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

#include "KReportDesignerItemMaps.h"
#include "KReportDesignerItemBase.h"
#include "KReportDesigner.h"

#include <KProperty>
#include <KPropertySet>

#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QDomDocument>
#include <QPainter>
#include "kreportplugin_debug.h"

void KReportDesignerItemMaps::init(QGraphicsScene *scene, KReportDesigner *d)
{
    if (scene)
        scene->addItem(this);

    KReportDesignerItemRectBase::init(&m_pos, &m_size, m_set, d);

    connect(m_set, SIGNAL(propertyChanged(KPropertySet&,KProperty&)),
            this, SLOT(slotPropertyChanged(KPropertySet&,KProperty&)));

    m_controlSource->setListData(m_reportDesigner->fieldKeys(), m_reportDesigner->fieldNames());
    setZValue(Z);
}

KReportDesignerItemMaps::KReportDesignerItemMaps(KReportDesigner * rw, QGraphicsScene* scene, const QPointF &pos)
        : KReportDesignerItemRectBase(rw)
{
    Q_UNUSED(pos);
    init(scene, rw);
    setSceneRect(properRect(*rw, KREPORT_ITEM_RECT_DEFAULT_WIDTH, KREPORT_ITEM_RECT_DEFAULT_WIDTH));
    m_name->setValue(m_reportDesigner->suggestEntityName(typeName()));
}

KReportDesignerItemMaps::KReportDesignerItemMaps(const QDomNode &element, KReportDesigner * rw, QGraphicsScene* scene)
        : KReportItemMaps(element), KReportDesignerItemRectBase(rw)
{
    init(scene, rw);
    setSceneRect(m_pos.toScene(), m_size.toScene());
}

KReportDesignerItemMaps* KReportDesignerItemMaps::clone()
{
    QDomDocument d;
    QDomElement e = d.createElement(QLatin1String("clone"));
    QDomNode n;
    buildXML(&d, &e);
    n = e.firstChild();
    return new KReportDesignerItemMaps(n, designer(), 0);
}

KReportDesignerItemMaps::~KReportDesignerItemMaps()
{
    // do we need to clean anything up?
}

void KReportDesignerItemMaps::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);
    // store any values we plan on changing so we can restore them
    QPen  p = painter->pen();
    painter->fillRect(rect(), QColor(0xc2, 0xfc, 0xc7));//C2FCC7

    //Draw a border so user knows the object edge
    painter->setPen(QPen(QColor(224, 224, 224)));
    painter->drawRect(rect());
    painter->setPen(Qt::black);
    painter->drawText(rect(), 0, dataSourceAndObjectTypeName(itemDataSource(), QLatin1String("map")));

    drawHandles(painter);

    // restore an values before we started just in case
    painter->setPen(p);
}

void KReportDesignerItemMaps::buildXML(QDomDocument *doc, QDomElement *parent)
{
    QDomElement entity = doc->createElement(QLatin1String("report:") + typeName());

    // properties
    addPropertyAsAttribute(&entity, m_name);
    addPropertyAsAttribute(&entity, m_controlSource);
    addPropertyAsAttribute(&entity, m_latitudeProperty);
    addPropertyAsAttribute(&entity, m_longitudeProperty);
    addPropertyAsAttribute(&entity, m_zoomProperty);
    addPropertyAsAttribute(&entity, m_themeProperty);
    //addPropertyAsAttribute(&entity, m_resizeMode);
    entity.setAttribute(QLatin1String("report:z-index"), zValue());
    buildXMLRect(doc, &entity, &m_pos, &m_size);

    parent->appendChild(entity);
}

void KReportDesignerItemMaps::slotPropertyChanged(KPropertySet &s, KProperty &p)
{
    //kreportpluginDebug() << p.name() << ":" << p.value();
    if (p.name().toLower() == "name") {
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

void KReportDesignerItemMaps::mousePressEvent(QGraphicsSceneMouseEvent * event)
{
    m_controlSource->setListData(m_reportDesigner->fieldKeys(), m_reportDesigner->fieldNames());
    KReportDesignerItemRectBase::mousePressEvent(event);
}
