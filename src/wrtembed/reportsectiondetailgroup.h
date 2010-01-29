/*
 * OpenRPT report writer and rendering engine
 * Copyright (C) 2001-2007 by OpenMFG, LLC
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
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
 * Please contact info@openmfg.com with any questions on this license.
 */

#ifndef REPORTSECTIONDETAILGROUP_H
#define REPORTSECTIONDETAILGROUP_H

#include <qobject.h>

class ReportSection;
class ReportSectionDetail;

class QDomElement;
class QDomDocument;

/**
 @author
*/
class ReportSectionDetailGroup : public QObject
{
    Q_OBJECT
public:
    ReportSectionDetailGroup(const QString &, ReportSectionDetail *, QWidget * parent, const char * name = 0);
    ~ReportSectionDetailGroup();

    enum PageBreak {
        BreakNone = 0,
        BreakAfterGroupFooter = 1,
        BreakBeforeGroupHeader = 2
    };

    enum Sort {
        Ascending = 1,
        Descending
    };
    

    void setColumn(const QString &);
    QString column() const;

    void setGroupHeaderVisible(bool yes = TRUE);
    bool groupHeaderVisible() const;

    void setGroupFooterVisible(bool yes = TRUE);
    bool groupFooterVisible() const;

    void setPageBreak(PageBreak);
    PageBreak  pageBreak() const;

    void setSort(Sort);
    Sort sort();

    ReportSection * groupHeader() const;
    ReportSection * groupFooter() const;

    void buildXML(QDomDocument & doc, QDomElement & section) const;
    void initFromXML( const QDomElement &element );
    
protected:
    QString m_column;

    ReportSection * m_groupHeader;
    ReportSection * m_groupFooter;

    ReportSectionDetail * m_reportSectionDetail;

    PageBreak m_pageBreak;
    Sort m_sort;
};


#endif
