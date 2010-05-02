﻿/*!
* @file    ExcelWorkbookSet.cpp
* @brief   Implementation file for class ExcelWorkbookSet
* @date    2009-12-01
* @author  Tu Yongce <tuyongce@gmail.com>
* @version $Id$
*/


#include <tchar.h>
#include <cassert>

#include "ExcelWorkbookSet.h"
#include "ExcelWorkbook.h"
#include "ComUtil.h"
#include "Noncopyable.h"


// <begin> namespace
EXCEL_AUTOMATION_NAMESPACE_START


////////////////////////////////////////////////////////////////////////////////
// Definition and implementation of class ExcelWorkbookSetImpl

/*!
* @brief Class ExcelWorkbookSetImpl inplements ExcelWorkbookSet's interfaces.
*/
class ExcelWorkbookSetImpl : public BodyBase, public Noncopyable
{
    // All members are private. Only the friend class ExcelWorkbookSet can access members of ExcelWorkbookSetImpl.
    friend class ExcelWorkbookSet;

private:
    ExcelWorkbookSetImpl(IDispatch *pWorkbookSet): m_pWorkbookSet(pWorkbookSet)
    {
        assert(pWorkbookSet);
    }

    virtual ~ExcelWorkbookSetImpl()
    {
        if (m_pWorkbookSet)
        {
            m_pWorkbookSet->Release();
            m_pWorkbookSet = 0;
        }
    }

    ExcelWorkbook OpenWorkbook(const ELchar *filename);


private:
    IDispatch *m_pWorkbookSet;
};


ExcelWorkbook ExcelWorkbookSetImpl::OpenWorkbook(const ELchar *filename)
{
    assert(m_pWorkbookSet);

    VARIANT param;
    param.vt = VT_BSTR;
    param.bstrVal = ::SysAllocString(filename);

    VARIANT result;
    VariantInit(&result);

    HRESULT hr = ComUtil::Invoke(m_pWorkbookSet, DISPATCH_METHOD, OLESTR("Open"), &result, 1, param);

    VariantClear(&param);

    if (FAILED(hr))
        return ExcelWorkbook();

    return ExcelWorkbook(result.pdispVal);
}


////////////////////////////////////////////////////////////////////////////////
// Implementation of class ExcelWorkbookSet

ExcelWorkbookSet::ExcelWorkbookSet(IDispatch *pWorkbookSet): HandleBase(new ExcelWorkbookSetImpl(pWorkbookSet))
{
    assert(pWorkbookSet);
}


ExcelWorkbook ExcelWorkbookSet::OpenWorkbook(const ELchar *filename)
{
    return Body().OpenWorkbook(filename);
}


// <begin> Handle/Body pattern implementation

ExcelWorkbookSet::ExcelWorkbookSet(ExcelWorkbookSetImpl *impl): HandleBase(impl)
{ 
}


ExcelWorkbookSetImpl& ExcelWorkbookSet::Body() const
{
    return dynamic_cast<ExcelWorkbookSetImpl&>(HandleBase::Body());
}

// <end> Handle/Body pattern implementation


// <end> namespace
EXCEL_AUTOMATION_NAMESPACE_END
