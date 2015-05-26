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

#include "KoReportBarcodePlugin.h"
#include "KoReportItemBarcode.h"
#include "KoReportDesignerItemBarcode.h"
#include "KReportPluginMetaData.h"
#ifdef KREPORT_SCRIPTING
#include "krscriptbarcode.h"
#endif


KREPORT_PLUGIN_FACTORY(KoReportBarcodePlugin, "kreport_barcodeplugin.json")

KoReportBarcodePlugin::KoReportBarcodePlugin(QObject *parent, const QVariantList &args)
    : KoReportPluginInterface(parent)
{
    Q_UNUSED(args);
}

KoReportBarcodePlugin::~KoReportBarcodePlugin()
{
}

QObject* KoReportBarcodePlugin::createRendererInstance(QDomNode& element)
{
    return new KoReportItemBarcode(element);
}

QObject* KoReportBarcodePlugin::createDesignerInstance(QDomNode& element, KoReportDesigner* designer , QGraphicsScene* scene)
{
    return new KoReportDesignerItemBarcode(element, designer, scene);
}

QObject* KoReportBarcodePlugin::createDesignerInstance(KoReportDesigner* designer, QGraphicsScene* scene, const QPointF& pos)
{
    return new KoReportDesignerItemBarcode(designer, scene, pos);
}

#ifdef KREPORT_SCRIPTING
QObject* KoReportBarcodePlugin::createScriptInstance(KoReportItemBase* item)
{
    KoReportItemBarcode *barcode = dynamic_cast<KoReportItemBarcode*>(item);
    if (barcode) {
        return new Scripting::Barcode(barcode);
    }
    return 0;
}
#endif

#include "KoReportBarcodePlugin.moc"
