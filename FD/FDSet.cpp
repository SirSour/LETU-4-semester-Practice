
// FDSet.cpp : реализация класса CFDSet
//

#include "stdafx.h"
#include "FD.h"
#include "FDSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// реализация CFDSet

IMPLEMENT_DYNAMIC(CFDSet, CRecordset)

CFDSet::CFDSet(CDatabase* pdb)
	: CRecordset(pdb)
{
	m_DriversID = L"";
	m_DriversDriverSurmane = L"";
	m_DriversDriverName = L"";
	m_DriversSponsor = L"";
	m_DriversCategory = L"";
	m_DriversManufacturer = L"";
	m_nFields = 6;
	m_nDefaultType = dynaset;
}

CFDSet::~CFDSet() {

}

CString CFDSet::GetDefaultConnect()
{
	return _T("DSN=FD;DBQ=C:\\USERS\\IBM\\DOCUMENTS\\Visual Studio 2015\\Projects\\FormulaDrift.accdb;DefaultDir=C:\\USERS\\IBM\\DOCUMENTS\\Visual Studio 2015\\Projects;DriverId=25;FIL=MS Access;MaxBufferSize=2048;PageTimeout=5;PWD=systemerror404;UID=admin;");
}

CString CFDSet::GetDefaultSQL()
{
	return _T("[Drivers], [Rounds]");
}

void CFDSet::DoFieldExchange(CFieldExchange* pFX) //функция для обмена данными
{
	pFX->SetFieldType(CFieldExchange::outputColumn); //вывод столбцов
// Такие макросы, как RFX_Text() и RFX_Int(), зависят от типа 
// переменной члена, а не от типа поля в базе данных.
// ODBC выполняет попытку автоматически преобразовать значение столбца к нужному типу
	/*RFX поддерживает передачу данных из набора в источник*/
	RFX_Text(pFX, _T("Car Number"), m_DriversID); 
	RFX_Text(pFX, _T("Surname"), m_DriversDriverSurmane);
	RFX_Text(pFX, _T("Name"), m_DriversDriverName);
	RFX_Text(pFX, _T("Sponsor"), m_DriversSponsor);
	RFX_Text(pFX, _T("Category"), m_DriversCategory);
	RFX_Text(pFX, _T("Car Manufacturer"), m_DriversManufacturer);

}

void CFDSet::GetInfoDriver(CMapStringToPtr* ptrMap) { //CMapStringToPtr поддерживает сопоставление пустых указателей

	void *ptr; //пустой указатель
	CDatabase Database;
	Database.Open("FD", FALSE, FALSE, "ODBC;", TRUE); //открываем БД 
	CRecordset RecSet(&Database); //набор записей
	try {
		RecSet.Open(CRecordset::dynaset, "SELECT* FROM Drivers"); //открываем набор записей
		/*SELECT* FROM: для извлечения строк из выбранной таблицы (Drivers)*/
		/*snapshot: изменения отображаются после перезагрузки;
		dynaset: изменения отображаются сразу;
		forwardonly: только чтение*/
		do {
			RecSet.GetFieldValue((short)0, m_DriversID); //значения полей
			RecSet.GetFieldValue(1, m_DriversDriverSurmane);
			RecSet.GetFieldValue(2, m_DriversDriverName);
			RecSet.GetFieldValue(3, m_DriversSponsor);
			RecSet.GetFieldValue(4, m_DriversCategory);
			RecSet.GetFieldValue(5, m_DriversManufacturer);

			//создаём элемент со считанными значениями
			ptr = new CFDSet(m_DriversID,m_DriversDriverSurmane, m_DriversDriverName,
				m_DriversSponsor, m_DriversCategory, m_DriversManufacturer);
			(*ptrMap)[m_DriversDriverSurmane] = ptr;
			ptr = 0;
			delete ptr;

			//переход к следующей записи
			RecSet.MoveNext();
		} while (!RecSet.IsEOF()); //пока не конец БД
		RecSet.Close(); //закрываем набор записей
		Database.Close(); //закрываем БД
	}
	catch (CDBException* pException) { //если словили ошибку любого рода
		AfxMessageBox(pException->m_strStateNativeOrigin); //строка с описанием ошибки, которая вызвала исключение
		AfxMessageBox(pException->m_strError); //описание ошибки
		pException->Delete(); //удаляем 
	}
}

void CFDSet::DeleteInfoDriver(CMapStringToPtr* ptrMap, CString str) {

	void* ptr;
	int item = -1, /*отсчёт элементов начинается с 0*/ i = 0;
	CDatabase Database;
	Database.Open("FD", FALSE, FALSE, "ODBC;", TRUE);
	CFDSet RecSet(&Database);
	
	try {
		if (!RecSet.Open(CRecordset::snapshot, "SELECT* FROM Drivers")) { //если БД не открыта
			AfxMessageBox("Open Base!", MB_ICONINFORMATION);
			return;
		}
		do {
			RecSet.Move(i); //i - число строк для перемещения
			i = 1;
			item++;
		} while (RecSet.m_DriversID != str); 
		RecSet.Delete(); 
		if (!RecSet.IsDeleted()) //определяем, удалена ли текущая запись
		{
			AfxMessageBox("You can`t delete this driver.", MB_ICONINFORMATION);
		}
		if ((*ptrMap).Lookup(str, ptr)) { 
			/*Lookup ищет указатель void,
			str задаёт ключ строки,
			ptr указывает возвращаемое значение*/
			CFDSet* driver_ = ((CFDSet*)ptr);
			delete driver_;
			(*ptrMap).RemoveKey(str); /*RemoveKey удаляет элемент с заданным ключем str*/
		}
		//else { 
		//	AfxMessageBox("Not found.", MB_ICONINFORMATION);  //вывод ошибки, если не найдено
		//	return; 
		//}
		RecSet.Close(); //закрываем набор записей
		Database.Close(); //закрываем БД
	}
	catch (CDBException* pException) { //если словили ошибку
		AfxMessageBox(pException->m_strStateNativeOrigin);
		AfxMessageBox(pException->m_strError);
		pException->Delete();
	}
}


/////////////////////////////////////////////////////////////////////////////
// CFDSet диагностика

#ifdef _DEBUG
void CFDSet::AssertValid() const
{
	CRecordset::AssertValid(); // проверка на целостность объекта
}

void CFDSet::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG

