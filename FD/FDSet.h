
// FDSet.h: интерфейс класса CFDSet
//

#define _CRT_SECURE_NO_WARNINGS

#pragma once


class CFDSet : public CRecordset //наследование класса для работы с записями, которые получены с помощью драйвера ODBC
{
public:
	CFDSet(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CFDSet)

// Данные полей и параметров

// Следующие типы строк (если присутствуют) отражают фактические типы данных 
// поля базы данных - CStringA для типов данных ANSI и CStringW для типов 
// данных Юникода. Это должно предотвратить выполнение драйвером ODBC 
// потенциально ненужных преобразований.  При желании можно заменить эти члены на 
// типы CString, и драйвер ODBC выполнит все необходимые преобразования.
// (Примечание. Необходимо использовать драйвер ODBC версии 3.5 или более поздней 
// для поддержки как Юникода, так и этих преобразований).

	CString	m_DriversID;
	CString	m_DriversDriverSurmane;
	CString	m_DriversDriverName;
	CString	m_DriversSponsor;
	CString	m_DriversCategory;
	CString	m_DriversManufacturer;

// Переопределение
	// Мастер создал переопределения виртуальных функций
	public:
	virtual CString GetDefaultConnect();	// Строка подключения по умолчанию

	virtual CString GetDefaultSQL(); 	// код SQL по умолчанию для набора записей
private:
	virtual void DoFieldExchange(CFieldExchange* pFX);	// поддержка RFX

// Реализация
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

