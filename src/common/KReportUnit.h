/* This file is part of the KDE project
   Copyright (C) 1998, 1999 Reginald Stadlbauer <reggie@kde.org>
   Copyright (C) 1998, 1999 Torben Weis <weis@kde.org>
   Copyright (C) 2004, Nicolas GOUTTE <goutte@kde.org>
   Copyright (C) 2010 Thomas Zander <zander@kde.org>
   Copyright 2012 Friedrich W. H. Kossebau <kossebau@kde.org>

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

#ifndef KREPORTUNIT_H
#define KREPORTUNIT_H

#include <math.h> // for floor

#include <QString>
#include <QDebug>
#include <QMetaType>

#include "kreport_export.h"

class QStringList;

// 1 inch ^= 72 pt
// 1 inch ^= 25.399956 mm (-pedantic ;p)
// 1 pt = 1/12 pi
// 1 pt ^= 0.0077880997 cc
// 1 cc = 12 dd
// Note: I don't use division but multiplication with the inverse value
// because it's faster ;p (Werner)
#define POINT_TO_MM(px) qreal((px)*0.352777167)
#define MM_TO_POINT(mm) qreal((mm)*2.83465058)
#define POINT_TO_CM(px) qreal((px)*0.0352777167)
#define CM_TO_POINT(cm) qreal((cm)*28.3465058)
#define POINT_TO_DM(px) qreal((px)*0.00352777167)
#define DM_TO_POINT(dm) qreal((dm)*283.465058)
#define POINT_TO_INCH(px) qreal((px)*0.01388888888889)
#define INCH_TO_POINT(inch) qreal((inch)*72.0)
#define MM_TO_INCH(mm) qreal((mm)*0.039370147)
#define INCH_TO_MM(inch) qreal((inch)*25.399956)
#define POINT_TO_PI(px) qreal((px)*0.083333333)
#define POINT_TO_CC(px) qreal((px)*0.077880997)
#define PI_TO_POINT(pi) qreal((pi)*12)
#define CC_TO_POINT(cc) qreal((cc)*12.840103)
/**
 * %KReport stores everything in pt (using "qreal") internally.
 * When displaying a value to the user, the value is converted to the user's unit
 * of choice, and rounded to a reasonable precision to avoid 0.999999
 *
 * For implementing the selection of a unit type in the UI use the *ForUi() methods.
 * They ensure the same order of the unit types in all places, with the order not
 * bound to the order in the enum (so ABI-compatible extension is possible) and
 * with the order and scope of listed types controlled by the @c ListOptions parameter.
 */
class KREPORT_EXPORT KReportUnit
{
public:
    /** Length units supported by %KReport. */
    enum Type {
        Millimeter = 0,
        Point,  ///< Postscript point, 1/72th of an Inco
        Inch,
        Centimeter,
        Decimeter,
        Pica,
        Cicero,
        Pixel,
        TypeCount ///< @internal
    };

    /// Used to control the scope of the unit types listed in the UI
    enum ListOption {
        ListAll = 0,
        HidePixel = 1,
        HideMask = HidePixel
    };
     Q_DECLARE_FLAGS(ListOptions, ListOption)

    /** Returns a KReportUnit instance with the type at the @p index of the UI list with the given @p listOptions. */
    static KReportUnit fromListForUi(int index, ListOptions listOptions = ListAll, qreal factor = 1.0);

    /// Convert a unit symbol string into a KReportUnit
    /// @param symbol symbol to convert
    /// @param ok if set, it will be true if the unit was known, false if unknown
    static KReportUnit fromSymbol(const QString &symbol, bool *ok = 0);

    /** Construction requires initialization. The factor is for variable factor units like pixel */
    explicit KReportUnit(Type unit = Point, qreal factor = 1.0) {
        m_type = unit;
        m_pixelConversion = factor;
    }

    KReportUnit& operator=(Type unit) {
        m_type = unit; m_pixelConversion = 1.0; return *this;
    }

    bool operator!=(const KReportUnit &other) const {
        return !operator==(other);
    }

    bool operator==(const KReportUnit &other) const {
        return m_type == other.m_type &&
            (m_type != Pixel ||
             qFuzzyCompare(m_pixelConversion, other.m_pixelConversion));
    }

    KReportUnit::Type type() const {
        return m_type;
    }

    void setFactor(qreal factor) {
        m_pixelConversion = factor;
    }
    /**
     * Prepare ptValue to be displayed in pt
     * This method will round to 0.001 precision
     */
    static qreal toPoint(qreal ptValue) {
        // No conversion, only rounding (to 0.001 precision)
        return floor(ptValue * 1000.0) / 1000.0;
    }

    /**
     * Prepare ptValue to be displayed in mm
     * This method will round to 0.0001 precision, use POINT_TO_MM() for lossless conversion.
     */
    static qreal toMillimeter(qreal ptValue) {
        // "mm" values are rounded to 0.0001 millimeters
        return floor(POINT_TO_MM(ptValue) * 10000.0) / 10000.0;
    }

    /**
     * Prepare ptValue to be displayed in cm
     * This method will round to 0.0001 precision, use POINT_TO_CM() for lossless conversion.
     */
    static qreal toCentimeter(qreal ptValue) {
        return floor(POINT_TO_CM(ptValue) * 10000.0) / 10000.0;
    }

    /**
     * Prepare ptValue to be displayed in dm
     * This method will round to 0.0001 precision, use POINT_TO_DM() for lossless conversion.
     */
    static qreal toDecimeter(qreal ptValue) {
        return floor(POINT_TO_DM(ptValue) * 10000.0) / 10000.0;
    }

    /**
     * Prepare ptValue to be displayed in inch
     * This method will round to 0.00001 precision, use POINT_TO_INCH() for lossless conversion.
     */
    static qreal toInch(qreal ptValue) {
        // "in" values are rounded to 0.00001 inches
        return floor(POINT_TO_INCH(ptValue) * 100000.0) / 100000.0;
    }

    /**
     * Prepare ptValue to be displayed in pica
     * This method will round to 0.00001 precision, use POINT_TO_PI() for lossless conversion.
     */
    static qreal toPica(qreal ptValue) {
        // "pi" values are rounded to 0.00001 inches
        return floor(POINT_TO_PI(ptValue) * 100000.0) / 100000.0;
    }

    /**
     * Prepare ptValue to be displayed in cicero
     * This method will round to 0.00001 precision, use POINT_TO_CC() for lossless conversion.
     */
    static qreal toCicero(qreal ptValue) {
        // "cc" values are rounded to 0.00001 inches
        return floor(POINT_TO_CC(ptValue) * 100000.0) / 100000.0;
    }

    /**
     * convert the given value directly from one unit to another
     */
    static qreal convertFromUnitToUnit(qreal value, const KReportUnit &fromUnit, const KReportUnit &toUnit, qreal factor = 1.0);


    /**
     * This method is the one to use to display a value in a dialog
     * \return the value @p ptValue converted to unit and rounded, ready to be displayed
     */
    qreal toUserValue(qreal ptValue) const;

    /**
     * Convert the value @p ptValue to a given unit @p unit
     * Unlike KReportUnit::ptToUnit the return value remains unrounded, so that it can be used in complex calculation
     * \return the converted value
     */
    static qreal ptToUnit(qreal ptValue, const KReportUnit &unit);

    /// This method is the one to use to display a value in a dialog
    /// @return the value @p ptValue converted the unit and rounded, ready to be displayed
    QString toUserStringValue(qreal ptValue) const;

    /// This method is the one to use to read a value from a dialog
    /// @return the value converted to points for internal use
    qreal fromUserValue(qreal value) const;

    /// This method is the one to use to read a value from a dialog
    /// @param value value entered by the user
    /// @param ok if set, the pointed bool is set to true if the value could be
    /// converted to a qreal, and to false otherwise.
    /// @return the value converted to points for internal use
    qreal fromUserValue(const QString &value, bool *ok = 0) const;

    /// Get the description string of the given unit
    static QString unitDescription(KReportUnit::Type type);

    /// Get the symbol string of the unit
    QString symbol() const;

    /// Returns the list of unit types for the UI, controlled with the given @p listOptions.
    static QStringList listOfUnitNameForUi(ListOptions listOptions = ListAll);

    /// Get the index of this unit in the list of unit types for the UI,
    /// if it is controlled with the given @p listOptions.
    int indexInListForUi(ListOptions listOptions = ListAll) const;

    /// Parses common %KReport and ODF values, like "10cm", "5mm" to pt.
    /// If no unit is specified, pt is assumed.
    static qreal parseValue(const QString &value, qreal defaultVal = 0.0);

    /// parse an angle to its value in degrees
    static qreal parseAngle(const QString &value, qreal defaultVal = 0.0);

    /**
     * Equal to symbol(): returns the symbol string of the unit.
     */
    inline QString toString() const {
        return symbol();
    }

private:
    Type m_type;
    qreal m_pixelConversion;
};

#ifndef QT_NO_DEBUG_STREAM
KREPORT_EXPORT QDebug operator<<(QDebug, const KReportUnit &);
#endif

Q_DECLARE_METATYPE(KReportUnit)
Q_DECLARE_OPERATORS_FOR_FLAGS(KReportUnit::ListOptions)

#endif
