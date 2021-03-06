﻿/*!
* @file    ExcelRange.h
* @brief   Header file for class ExcelRange
* @date    2009-12-08
* @author  Tu Yongce <tuyongce@gmail.com>
* @version $Id$
*/


#ifndef EXCELRANGE_H_GUID_A48F0552_080F_444F_89EC_97ADCFC3A649
#define EXCELRANGE_H_GUID_A48F0552_080F_444F_89EC_97ADCFC3A649


#include <vector>
#include "LibDef.h"
#include "HandleBody.h"
#include "StringUtil.h"
#include "ExcelCommonTypes.h"


// <begin> namespace
EXCEL_AUTOMATION_NAMESPACE_START


// Forward declarations
class ExcelWorksheet;
class ExcelFont;


/*!
* @brief Class ExcelRange represents the concept "Range" in Excel.
* @note ExcelRange/ExcelRangeImpl is an implementation of the "Handle/Body" pattern.
*/
class EXCEL_AUTOMATION_DLL_API ExcelRange : public HandleBase
{
public:
    /*!
    * Default constructor
    */ // Doc is needed by Doxygen
    ExcelRange(): HandleBase(0) { }

    /*!
    * @brief Encode values in this range into string form.
    * @param [out] data The corresponding encoded string of this range.
    * @return true if successful, otherwise false
    * @note Encoding format: @n
    *         EncodingString := <number of rows>#<number of columns>#{Values}            @n
    *         Values := {RowValues}{RowValues}...{RowValues}              --> All rows in the two-dimentional array    @n
    *         RowValues := {ColumnValue}{ColumnValue}...{ColumnValue}     --> All columns of in one row     @n
    *         ColumnValue := <number of characters>#<the character string of the value>          @n
    *       Example: @n
    *         For the two-dimensional array (2*5) @n
    *           { {abc, de, fghi, 3, 5235}, {23, 5353, 3253, 32} }, @n
    *         The correpsonding encoded string is 2#5#3#abc2#de4#fghi1#34#52352#234#53530#4#32532#32.    @n
    */
    bool ReadData(ELstring &data);

    /*!
    * @brief Read values in this range into vector.
    * @param [out] values Vector of Vectors of strings which holds values for this range
    * @return true if successful, otherwise false
    * @note values[i][j] holds the value for row i and column j of this range (i and j start from 0)
    */
    bool ReadData(std::vector<std::vector<ELstring> > &values);

    /*!
    * @brief Decode the string form of a range and write the data into this range.
    * @return true if successful, otherwise false
    * @note The encoding format of @e data must be the one specified in ExcelRange::ReadData().
    * @note The source range and this range must have the same size (same number of rows and columns).
    */
    bool WriteData(const ELchar *data);

    /*!
    * @brief Decode the string form of a range and write the data into this range.
    * @return true if successful, otherwise false
    * @note The encoding format of @e data must be the one specified in ExcelRange::ReadData().
    * @note The source range and this range must have the same size (same number of rows and columns).
    */
    bool WriteData(const ELstring &data);

    /*!
    * @brief Write values in the vector into this range.
    * @return true if successful, otherwise false
    * @note The vector and this range must have the same size (same number of rows and columns).
    * @note values[i][j] holds the value for row i and column j of this range (i and j start from 0)
    */
    bool WriteData(const std::vector<std::vector<ELstring> > &values);

    /*!
    * @brief Decode the string form of a range into values
    * @param [in] data The string form of a range (the encoded string)
    * @param [out] Which returns the values for this range
    * @return true if successful, otherwise false
    * @note The encoding format of @e data must be the one specified in ExcelRange::ReadData().
    * @note values[i][j] holds the value for row i and column j of this range (i and j start from 0)
    */
    static bool DecodeData(const ELstring &data, std::vector<std::vector<ELstring> > &values);

    /*!
    * @brief Encode values of a range into the string form
    * @param [in] values The values for a range
    * @return The string form of this range
    * @note The sub-vector objects must have the same size, which is number of columns
    * @note The encoding format is the one specified in ExcelRange::ReadData().
    * @note values[i][j] holds the value for row i and column j of this range (i and j start from 0)
    */
    static ELstring EncodeData(const std::vector<std::vector<ELstring> > &values);

    /*!
    * @brief Merge this range into one cell or merge every row of this range into one cell.
    * @param [in] multiRow If true, merge every row of the range into one cell;
    *                      otherwise (false), merge the whole range into one cell.
    * @return true if successful, otherwise false
    */
    bool Merge(bool multiRow = false);

    /*!
    * @brief Return an object representing the font property of this range
    */
    ExcelFont GetFont();

    /*!
    * @brief Set horizontal alignment of the range
    * @param [in] align Refer to ExcelHorizontalAlignment
    * @return true if successful, otherwise false
    */
    bool SetHorizontalAlignment(ExcelHorizontalAlignment align);

    /*!
    * @brief Set vertical alignment of the range
    * @param [in] align Refer to ExcelVerticalAlignment
    * @return true if successful, otherwise false
    */
    bool SetVerticalAlignment(ExcelVerticalAlignment align);


private:
    friend class ExcelWorksheetImpl;  // which will call the following ctor
    ExcelRange(IDispatch *pRange, ELchar columnFrom, ELchar columnTo, int rowFrom, int rowTo);

private:
    // <begin> Handle/Body pattern implementation
    friend class ExcelRangeImpl;
    ExcelRange(ExcelRangeImpl *impl);
    ExcelRangeImpl& Body() const;
    // <end> Handle/Body pattern implementation
};


// <end> namespace
EXCEL_AUTOMATION_NAMESPACE_END


#endif //EXCELRANGE_H_GUID_A48F0552_080F_444F_89EC_97ADCFC3A649
