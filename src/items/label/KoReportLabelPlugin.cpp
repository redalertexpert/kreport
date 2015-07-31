/* This file is part of the KDE project
   Copyright (C) 2010 by Adam Pigg (adam@piggz.co.uk)

   This library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Library General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.

   This library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Library General Public License for more details.

   You should have received a copy of the GNU Library General Public License
   along with this library; see the file COPYING.LIB.  If not, write to
   the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.
*/

#include "KoReportLabelPlugin.h"
#include "KoReportItemLabel.h"
#include "KoReportDesignerItemLabel.h"
#include "wrtembed/KoReportDesigner.h"
#include "common/KReportPluginMetaData.h"
#include "KReportLabelElement.h"
#ifdef KREPORT_SCRIPTING
#include "krscriptlabel.h"
#endif

KREPORT_PLUGIN_FACTORY(KoReportLabelPlugin, "label.json")

KoReportLabelPlugin::KoReportLabelPlugin(QObject *parent, const QVariantList &args)
    : KoReportPluginInterface(parent, args)
{
}

KoReportLabelPlugin::~KoReportLabelPlugin()
{

}

QObject* KoReportLabelPlugin::createRendererInstance(const QDomNode &elem)
{
    return new KoReportItemLabel(elem);
}

QObject* KoReportLabelPlugin::createDesignerInstance(KoReportDesigner* designer, QGraphicsScene* scene, const QPointF &pos)
{
    return new KoReportDesignerItemLabel(designer, scene, pos);
}

QObject* KoReportLabelPlugin::createDesignerInstance(const QDomNode & element, KoReportDesigner *designer, QGraphicsScene * scene)
{
    return new KoReportDesignerItemLabel(element, designer, scene);
}

KReportElement KoReportLabelPlugin::createElement()
{
    return KReportLabelElement();
}

#ifdef KREPORT_SCRIPTING
QObject* KoReportLabelPlugin::createScriptInstance(KoReportItemBase *item)
{
    KoReportItemLabel *label = dynamic_cast<KoReportItemLabel*>(item);
    if (label) {
        return new Scripting::Label(label);
    }
    return 0;
}
#endif

#include "KoReportLabelPlugin.moc"
