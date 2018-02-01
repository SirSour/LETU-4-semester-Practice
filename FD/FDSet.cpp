
// FDSet.cpp : ���������� ������ CFDSet
//

#include "stdafx.h"
#include "FD.h"
#include "FDSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ���������� CFDSet

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

void CFDSet::DoFieldExchange(CFieldExchange* pFX) //������� ��� ������ �������
{
	pFX->SetFieldType(CFieldExchange::outputColumn); //����� ��������
// ����� �������, ��� RFX_Text() � RFX_Int(), ������� �� ���� 
// ���������� �����, � �� �� ���� ���� � ���� ������.
// ODBC ��������� ������� ������������� ������������� �������� ������� � ������� ����
	/*RFX ������������ �������� ������ �� ������ � ��������*/
	RFX_Text(pFX, _T("Car Number"), m_DriversID); 
	RFX_Text(pFX, _T("Surname"), m_DriversDriverSurmane);
	RFX_Text(pFX, _T("Name"), m_DriversDriverName);
	RFX_Text(pFX, _T("Sponsor"), m_DriversSponsor);
	RFX_Text(pFX, _T("Category"), m_DriversCategory);
	RFX_Text(pFX, _T("Car Manufacturer"), m_DriversManufacturer);

}

void CFDSet::GetInfoDriver(CMapStringToPtr* ptrMap) { //CMapStringToPtr ������������ ������������� ������ ����������

	void *ptr; //������ ���������
	CDatabase Database;
	Database.Open("FD", FALSE, FALSE, "ODBC;", TRUE); //��������� �� 
	CRecordset RecSet(&Database); //����� �������
	try {
		RecSet.Open(CRecordset::dynaset, "SELECT* FROM Drivers"); //��������� ����� �������
		/*SELECT* FROM: ��� ���������� ����� �� ��������� ������� (Drivers)*/
		/*snapshot: ��������� ������������ ����� ������������;
		dynaset: ��������� ������������ �����;
		forwardonly: ������ ������*/
		do {
			RecSet.GetFieldValue((short)0, m_DriversID); //�������� �����
			RecSet.GetFieldValue(1, m_DriversDriverSurmane);
			RecSet.GetFieldValue(2, m_DriversDriverName);
			RecSet.GetFieldValue(3, m_DriversSponsor);
			RecSet.GetFieldValue(4, m_DriversCategory);
			RecSet.GetFieldValue(5, m_DriversManufacturer);

			//������ ������� �� ���������� ����������
			ptr = new CFDSet(m_DriversID,m_DriversDriverSurmane, m_DriversDriverName,
				m_DriversSponsor, m_DriversCategory, m_DriversManufacturer);
			(*ptrMap)[m_DriversDriverSurmane] = ptr;
			ptr = 0;
			delete ptr;

			//������� � ��������� ������
			RecSet.MoveNext();
		} while (!RecSet.IsEOF()); //���� �� ����� ��
		RecSet.Close(); //��������� ����� �������
		Database.Close(); //��������� ��
	}
	catch (CDBException* pException) { //���� ������� ������ ������ ����
		AfxMessageBox(pException->m_strStateNativeOrigin); //������ � ��������� ������, ������� ������� ����������
		AfxMessageBox(pException->m_strError); //�������� ������
		pException->Delete(); //������� 
	}
}

void CFDSet::DeleteInfoDriver(CMapStringToPtr* ptrMap, CString str) {

	void* ptr;
	int item = -1, /*������ ��������� ���������� � 0*/ i = 0;
	CDatabase Database;
	Database.Open("FD", FALSE, FALSE, "ODBC;", TRUE);
	CFDSet RecSet(&Database);
	
	try {
		if (!RecSet.Open(CRecordset::snapshot, "SELECT* FROM Drivers")) { //���� �� �� �������
			AfxMessageBox("Open Base!", MB_ICONINFORMATION);
			return;
		}
		do {
			RecSet.Move(i); //i - ����� ����� ��� �����������
			i = 1;
			item++;
		} while (RecSet.m_DriversID != str); 
		RecSet.Delete(); 
		if (!RecSet.IsDeleted()) //����������, ������� �� ������� ������
		{
			AfxMessageBox("You can`t delete this driver.", MB_ICONINFORMATION);
		}
		if ((*ptrMap).Lookup(str, ptr)) { 
			/*Lookup ���� ��������� void,
			str ����� ���� ������,
			ptr ��������� ������������ ��������*/
			CFDSet* driver_ = ((CFDSet*)ptr);
			delete driver_;
			(*ptrMap).RemoveKey(str); /*RemoveKey ������� ������� � �������� ������ str*/
		}
		//else { 
		//	AfxMessageBox("Not found.", MB_ICONINFORMATION);  //����� ������, ���� �� �������
		//	return; 
		//}
		RecSet.Close(); //��������� ����� �������
		Database.Close(); //��������� ��
	}
	catch (CDBException* pException) { //���� ������� ������
		AfxMessageBox(pException->m_strStateNativeOrigin);
		AfxMessageBox(pException->m_strError);
		pException->Delete();
	}
}


/////////////////////////////////////////////////////////////////////////////
// CFDSet �����������

#ifdef _DEBUG
void CFDSet::AssertValid() const
{
	CRecordset::AssertValid(); // �������� �� ����������� �������
}

void CFDSet::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG

