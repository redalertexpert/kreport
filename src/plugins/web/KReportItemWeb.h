/* This file is part of the KDE project
   Copyright Shreya Pandit <shreya@shreyapandit.com>
   Copyright 2011 Adam Pigg <adam@piggz.co.uk>

   This library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Library General Public
   License as published by the Free Software Foundation; either
   version 2 of the License, or (at your option) any later version.

   This library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Library General Public License for more details.

   You should have received a copy of the GNU Library General Public License
   along with this library; see the file COPYING.LIB.  If not, write to
   the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
 * Boston, MA 02110-1301, USA.
*/

#ifndef KREPORTITEMWEB_H
#define KREPORTITEMWEB_H

#include "KReportAsyncItemBase.h"
#include "KReportPosition.h"
#include "KReportSize.h"
#include "KReportData.h"

#include <QGraphicsScene>
#include <QUrl>
#include <QDomNode>

class QUrl;
class QWebPage;

namespace Scripting
{
class Web;
}

/**
*/
class KReportItemWeb : public KReportAsyncItemBase
{
    Q_OBJECT
public:
    KReportItemWeb();
    explicit KReportItemWeb(const QDomNode &element);
    virtual ~KReportItemWeb();

    virtual QString typeName() const;
    virtual int renderSimpleData(OROPage *page, OROSection *section, const QPointF &offset, const QVariant &data, KReportScriptHandler *script);
    virtual QString itemDataSource() const;

private Q_SLOTS:
    void loadFinished(bool);

private:
    void init();

    bool m_rendering;
    OROPage *m_targetPage;
    OROSection *m_targetSection;
    QPointF m_targetOffset;

protected:
    virtual void createProperties();

    KProperty *m_controlSource;
    QWebPage *m_webPage;

    friend class Scripting::Web;
};

#endif
