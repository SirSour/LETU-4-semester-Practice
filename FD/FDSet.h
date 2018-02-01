
// FDSet.h: ��������� ������ CFDSet
//

#define _CRT_SECURE_NO_WARNINGS

#pragma once


class CFDSet : public CRecordset //������������ ������ ��� ������ � ��������, ������� �������� � ������� �������� ODBC
{
public:
	CFDSet(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CFDSet)

// ������ ����� � ����������

// ��������� ���� ����� (���� ������������) �������� ����������� ���� ������ 
// ���� ���� ������ - CStringA ��� ����� ������ ANSI � CStringW ��� ����� 
// ������ �������. ��� ������ ������������� ���������� ��������� ODBC 
// ������������ �������� ��������������.  ��� ������� ����� �������� ��� ����� �� 
// ���� CString, � ������� ODBC �������� ��� ����������� ��������������.
// (����������. ���������� ������������ ������� ODBC ������ 3.5 ��� ����� ������� 
// ��� ��������� ��� �������, ��� � ���� ��������������).

	CString	m_DriversID;
	CString	m_DriversDriverSurmane;
	CString	m_DriversDriverName;
	CString	m_DriversSponsor;
	CString	m_DriversCategory;
	CString	m_DriversManufacturer;

// ���������������
	// ������ ������ ��������������� ����������� �������
	public:
	virtual CString GetDefaultConnect();	// ������ ����������� �� ���������

	virtual CString GetDefaultSQL(); 	// ��� SQL �� ��������� ��� ������ �������
private:
	virtual void DoFieldExchange(CFieldExchange* pFX);	// ��������� RFX

// ����������
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif
public:
	CFDSet(CString	_m_DriversID, CString _m_DriversDriverSurmane, CString _m_DriversDriverName,
		CString	_m_DriversSponsor, CString	_m_DriversCategory, CString	_m_DriversManufacturer) {

		m_DriversID = _m_DriversID;
		m_DriversDriverSurmane = _m_DriversDriverSurmane;
		m_DriversDriverName = _m_DriversDriverName;
		m_DriversSponsor = _m_DriversSponsor;
		m_DriversCategory = _m_DriversCategory;
		m_DriversManufacturer = _m_DriversManufacturer;
	};
	
	~CFDSet();

	void GetInfoDriver(CMapStringToPtr* ptrMap);
	void DeleteInfoDriver(CMapStringToPtr* ptrMap, CString str);

};

