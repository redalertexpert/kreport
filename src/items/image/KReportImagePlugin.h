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

#ifndef KREPORTIMAGEPLUGIN_H
#define KREPORTIMAGEPLUGIN_H

#include "KReportStaticPluginInterface.h"

KREPORT_DECLARE_STATIC_PLUGIN(KReportImagePlugin)

class KReportImagePlugin : public KReportPluginInterface
{
    public:
    explicit KReportImagePlugin(QObject *parent, const QVariantList &args = QVariantList());
    virtual ~KReportImagePlugin();

    virtual QObject* createRendererInstance(const QDomNode& element);
    virtual QObject* createDesignerInstance(const QDomNode& element, KReportDesigner* , QGraphicsScene* scene);
    virtual QObject* createDesignerInstance(KReportDesigner* , QGraphicsScene* scene, const QPointF& pos);
#ifdef KREPORT_SCRIPTING
    virtual QObject* createScriptInstance(KReportItemBase* item);
#endif
};

#endif // KREPORTIMAGEPLUGIN_H
