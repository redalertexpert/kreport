/*
 * Kexi Report Plugin
 * Copyright (C) 2007-2008 by Adam Pigg (adam@piggz.co.uk)
 * Copyright (C) 2011 by Radoslaw Wicik (radoslaw@wicik.pl)
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
#ifndef KRIMAGEDATA_H
#define KRIMAGEDATA_H
#include <KoReportItemBase.h>
#include <QRect>
#include <QPainter>
#include <qdom.h>
#include "krpos.h"
#include "krsize.h"
#include <koproperty/Property.h>
#include <koproperty/Set.h>
#include <KoGlobal.h>
#include <kdebug.h>
#include <klocalizedstring.h>
#include <kglobalsettings.h>
#include <MarbleWidget.h>
#include <RdfForward.h>
#include <QMap>
#include <reportview.h>

class QImage;

namespace Scripting
{
class Maps;
}

/**
 @author
*/
class KoReportItemMaps : public KoReportItemBase
{
    Q_OBJECT
public:
    KoReportItemMaps() {
        createProperties();
        m_report = 0;
    }
    KoReportItemMaps(QDomNode & element);
    virtual ~KoReportItemMaps();

    virtual QString typeName() const;
    virtual int render(OROPage* page, OROSection* section,  QPointF offset, QVariant data, KRScriptHandler *script);
    using KoReportItemBase::render;

    virtual QString itemDataSource() const;
public slots:
    void requestRedraw();

protected:
    Marble::MarbleWidget* initMarble();
    KoProperty::Property * m_controlSource;
    KoProperty::Property* m_resizeMode;
    KoProperty::Property* m_staticImage;

    void setMode(const QString&);
    void setInlineImageData(QByteArray, const QString& = QString());
    void setColumn(const QString&);
    QString mode() const;
    bool isInline() const;
    QByteArray inlineImageData() const;
    QMap<QString,Marble::MarbleWidget*> m_marbles;
    KPlato::ReportView* m_report;
    ORODocument* m_oroDoc;
    QImage *m_mapImage;
    
private:
    virtual void createProperties();
    void deserializeData(const QVariant& serialized);
    friend class Scripting::Maps;
};

#endif
