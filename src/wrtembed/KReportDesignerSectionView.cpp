/* This file is part of the KDE project
 * Copyright (C) 2001-2007 by OpenMFG, LLC (info@openmfg.com)
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
 * License along with this library.  If not, see <http://www.gnu.org/licenses/>.
 */

//
// ReportSceneView method implementations
//
#include "KReportDesignerSectionView.h"
#include "KReportDesigner.h"

#include "kreport_debug.h"

KReportDesignerSectionView::KReportDesignerSectionView(KReportDesigner * designer, QGraphicsScene *scene, QWidget * parent)
 : QGraphicsView(scene, parent)
{
    m_reportDesigner = designer;

    viewport()->setMouseTracking(true);
    setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

    setCacheMode(QGraphicsView::CacheBackground);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setDragMode(QGraphicsView::RubberBandDrag);
    setFrameStyle(0);
    m_reportDesigner->setActiveScene(scene);

}

KReportDesignerSectionView::~KReportDesignerSectionView()
{
    viewport()->setMouseTracking(false);
}

//! @todo check
void KReportDesignerSectionView::resizeContents(const QSize &s)
{
    setMinimumSize(s);
    setMaximumSize(s);
}

KReportDesigner * KReportDesignerSectionView::designer() const
{
    return m_reportDesigner;
}

void KReportDesignerSectionView::mousePressEvent(QMouseEvent * e)
{
    m_reportDesigner->sectionMousePressEvent(this, e);
    QGraphicsView::mousePressEvent(e);
}

void KReportDesignerSectionView::mouseReleaseEvent(QMouseEvent * e)
{
    m_reportDesigner->sectionMouseReleaseEvent(this, e);
    QGraphicsView::mouseReleaseEvent(e);
}

QSize KReportDesignerSectionView::sizeHint() const
{
    //kreportDebug() <<  scene()->width() << "x" << scene()->height();
    return QSize(scene()->width(), scene()->height());
}

