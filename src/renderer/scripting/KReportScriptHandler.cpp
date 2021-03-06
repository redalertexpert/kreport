/* This file is part of the KDE project
 * Copyright (C) 2007-2008 by Adam Pigg <adam@piggz.co.uk>
 * Copyright (C) 2012 Jarosław Staniek <staniek@kde.org>
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

#include "KReportScriptHandler.h"

#include "KReportScriptSection.h"
#include "KReportScriptDebug.h"
#include "KReportScriptReport.h"
#include "KReportScriptDraw.h"
#include "KReportScriptConstants.h"
#include "KReportSectionData.h"
#include "KReportItemBase.h"
#include "KReportDocument.h"
#include "KReportDetailSectionData.h"
#include "KReportRenderObjects.h"
#include "kreport_debug.h"

#include <QMessageBox>
#include <QJSEngine>
#include <QJSValue>

KReportScriptHandler::KReportScriptHandler(const KReportData* kodata, KReportDocument* d)
{
    m_reportData = d;
    m_kreportData = kodata;

    m_engine = 0;
    m_constants = 0;
    m_debug = 0;
    m_draw = 0;

    // Create the script engine instance .
    m_engine = new QJSEngine(this);

    //Add constants object
    m_constants = new KReportScriptConstants();
    registerScriptObject(m_constants, QLatin1String("constants"));

    //A simple debug function to allow printing from functions
    m_debug = new KReportScriptDebug();
    registerScriptObject(m_debug, QLatin1String("debug"));

    //A simple drawing object
    m_draw = new KReportScriptDraw();
    registerScriptObject(m_draw, QLatin1String("draw"));

    //Add a general report object
    m_report = new Scripting::Report(m_reportData);
    QJSValue r = registerScriptObject(m_report, m_reportData->name());

    //Add the sections
    QList<KReportSectionData*> secs = m_reportData->sections();
    foreach(KReportSectionData *sec, secs) {
        m_sectionMap[sec] = new Scripting::Section(sec);
        m_sectionMap[sec]->setParent(m_report);
        m_sectionMap[sec]->setObjectName(sec->name().replace(QLatin1Char('-'), QLatin1Char('_'))
                                         .remove(QLatin1String("report:")));
        QJSValue s = m_engine->newQObject(m_sectionMap[sec]);
        r.setProperty(m_sectionMap[sec]->objectName(), s);
        //kreportDebug() << "Added" << m_sectionMap[sec]->objectName() << "to report" << m_reportData->name();
    }

    //kreportDebug() << "Report name is" << m_reportData->name();
}

bool KReportScriptHandler::trigger()
{
    QString code = m_kreportData->scriptCode(m_reportData->script());
    //kreportDebug() << code;

    if (code.isEmpty()) {
        return true;
    }

    m_scriptValue = m_engine->evaluate(code, m_reportData->script());

    if (m_scriptValue.isError()) {
        return false;
    }/*TODO else {
        kreportDebug() << "Function Names:" << m_engine->functionNames();
    }*/
    m_report->eventOnOpen();
    return true;
}

KReportScriptHandler::~KReportScriptHandler()
{
    delete m_report;
    delete m_engine;
}

void KReportScriptHandler::newPage()
{
    if (m_report) {
        m_report->eventOnNewPage();
    }
}

void KReportScriptHandler::slotEnteredGroup(const QString &key, const QVariant &value)
{
    //kreportDebug() << key << value;
    m_groups[key] = value;
    emit(groupChanged(m_groups));
}
void KReportScriptHandler::slotExitedGroup(const QString &key, const QVariant &value)
{
    Q_UNUSED(value);
    //kreportDebug() << key << value;
    m_groups.remove(key);
    emit(groupChanged(m_groups));
}

void KReportScriptHandler::slotEnteredSection(KReportSectionData *section, OROPage* cp, QPointF off)
{
    if (cp)
        m_draw->setPage(cp);
    m_draw->setOffset(off);

    Scripting::Section *ss = m_sectionMap[section];
    if (ss) {
        ss->eventOnRender();
    }
}

QVariant KReportScriptHandler::evaluate(const QString &code)
{
    if (!m_scriptValue.isError()) {
        QJSValue result = m_engine->evaluate(code);
        if (!result.isError()) {
            return result.toVariant();
        } else {
            QMessageBox::warning(0, tr("Script Error"), m_scriptValue.toString());
        }
    }
    return QVariant();
}

void KReportScriptHandler::displayErrors()
{
    if (m_scriptValue.isError()) {
        QMessageBox::warning(0, tr("Script Error"), m_scriptValue.toString());
    }
}

//! @todo KEXI3 move to kexi
#if 0
QString KReportScriptHandler::where()
{
    QString w;
    QMap<QString, QVariant>::const_iterator i = m_groups.constBegin();
    while (i != m_groups.constEnd()) {
        w += QLatin1Char('(') + i.key() + QLatin1String(" = '") + i.value().toString() + QLatin1String("') AND ");
        ++i;
    }
    w.chop(4);
    //kreportDebug() << w;
    return w;
}
#endif

QJSValue KReportScriptHandler::registerScriptObject(QObject* obj, const QString& name)
{
    QJSValue val;
    val = m_engine->newQObject(obj);
    m_engine->globalObject().setProperty(name, val);
    return val;
}

