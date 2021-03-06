/* This file is part of the KDE project
   Copyright (C) 2010 by Adam Pigg (adam@piggz.co.uk)
   Copyright (C) 2011, 2012 by Dag Andersen (danders@get2net.dk)

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

#ifndef KOODTFRAMEREPORTDOCUMENT_H
#define KOODTFRAMEREPORTDOCUMENT_H

#include <QFile>
#include <QMap>
#include <QList>

#include "reportpageoptions.h"

class KoOdfWriteStore;
class KoXmlWriter;
class KoOdtFrameReportPrimitive;
class KoGenStyles;

class OROSection;

class KoOdtFrameReportDocument
{
public:
    KoOdtFrameReportDocument();
    ~KoOdtFrameReportDocument();

    void startTable(OROSection *section);
    void addPrimitive(KoOdtFrameReportPrimitive *data);
    void setPageOptions(const ReportPageOptions &pageOptions);
    QFile::FileError saveDocument(const QString&);

private:
    void createStyles(KoGenStyles *coll);
    bool createContent(KoOdfWriteStore* odfStore, KoGenStyles *coll);
    void createPages(KoXmlWriter* bodyWriter, KoGenStyles *coll);

    KoXmlWriter* manifestWriter;
    ReportPageOptions m_pageOptions;

    QMap<int, QList<KoOdtFrameReportPrimitive*> > m_pagemap;
};

#endif // KOODTFRAMESREPORTDOCUMENT_H
