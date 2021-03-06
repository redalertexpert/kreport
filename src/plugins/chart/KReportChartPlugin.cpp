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

#include "KReportChartPlugin.h"
#include "KReportItemChart.h"
#include "KReportDesignerItemChart.h"
#include "KReportPluginInfo.h"
#ifdef KREPORT_SCRIPTING
#include "krscriptchart.h"
#endif

#include <KoIcon.h>

K_EXPORT_KOREPORT_ITEMPLUGIN(KoReportChartPlugin, chartplugin)

KReportChartPlugin::KReportChartPlugin(QObject *parent, const QVariantList &args) : KReportPluginInterface(parent)
{
    Q_UNUSED(args);

    KoReportPluginInfo *info = new KoReportPluginInfo();
    info->setClassName("chart");
    info->setIcon(koIcon("office-chart-area"));
    info->setName(tr("Chart"));
    info->setPriority(10);
    setInfo(info);
}

KReportChartPlugin::~KReportChartPlugin()
{

}

QObject* KReportChartPlugin::createRendererInstance(const QDomNode& element)
{
    return new KReportItemChart(element);
}

QObject* KReportChartPlugin::createDesignerInstance(const QDomNode& element, KoReportDesigner* designer, QGraphicsScene* scene)
{
    return new KReportDesignerItemChart(element, designer, scene);
}

QObject* KReportChartPlugin::createDesignerInstance(KoReportDesigner* designer, QGraphicsScene* scene, const QPointF& pos)
{
    return new KReportDesignerItemChart(designer, scene, pos);
}

#ifdef KREPORT_SCRIPTING
QObject* KoReportChartPlugin::createScriptInstance(KReportItemBase* item)
{
    KoReportItemChart *chart = dynamic_cast<KoReportItemChart*>(item);
    if (chart) {
        return new Scripting::Chart(chart);
    }
    return 0;
}
#endif
