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

#ifndef KREPORTRENDERERBASE_H
#define KREPORTRENDERERBASE_H

#include <QUrl>

#include "kreport_export.h"

class QPainter;
class QPrinter;
class ORODocument;

//! Context for executing rendering.
class KREPORT_EXPORT KReportRendererContext
{
    public:
        KReportRendererContext();
        QUrl destinationUrl;
        QPainter *painter;
        QPrinter *printer;
};

//! Base class for report renderers.
class KREPORT_EXPORT KReportRendererBase
{
    public:
        KReportRendererBase();

        virtual ~KReportRendererBase();

        //! Render the page of the given document within the given context.
        //! If page == -1, renders the entire document.
        virtual bool render(const KReportRendererContext& context, ORODocument *document, int page = -1) = 0;
};

//! Factory for creating renderers
//! @todo make it use plugins
class KREPORT_EXPORT KReportRendererFactory
{
    public:
        KReportRendererFactory();

        KReportRendererBase* createInstance(const QString& key);
};

#endif // KREPORTRENDERERBASE_H
