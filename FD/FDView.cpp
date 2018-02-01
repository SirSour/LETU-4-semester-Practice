
// FDView.cpp : ���������� ������ CFDView
//
#define _CRT_SECURE_NO_WARNINGS
#include "stdafx.h"
#include "FD.h"
#include "FDDoc.h"
#include "FDView.h"
#include "FDSet.h"

#include "Search.h"



#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CFDView

IMPLEMENT_DYNCREATE(CFDView, CListView)

BEGIN_MESSAGE_MAP(CFDView, CListView)
	ON_COMMAND(ID_VIEW_DRIVER, &CFDView::OnViewDriver)
	ON_COMMAND(ID_EDIT_DEL_DRIVER, &CFDView::OnDeleteDriver)
	ON_COMMAND(ID_EDIT_FIND_DRIVER, &CFDView::OnEditSearchDriver)
END_MESSAGE_MAP()

// ��������/����������� CFDView

CFDView::CFDView()
{ /*������ ������������ � ���� ������, ���������� �� ��������*/
	m_dwDefaultStyle |= (LVS_REPORT); //����� �� ���������

}

CFDView::~CFDView() {
	void* ptr;
	CString Driver_;
	CFDSet* driver;
	POSITION position = pDoc->cMapDriver.GetStartPosition(); //��������� �������
	while (position != NULL) {
		/*������� ���� ���������*/
		pDoc->cMapDriver.GetNextAssoc(position, Driver_, ptr); 
		/*position - �������
		Driver_ - ���� ������������� ��������
		ptr - ������������ ��������*/
		driver = ((CFDSet*)ptr);
		delete driver;
	}
	pDoc->cMapDriver.RemoveAll(); //��������
}

BOOL CFDView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: �������� ����� Window ��� ����� ����������� ���������
	//  CREATESTRUCT cs

	return CListView::PreCreateWindow(cs);
}

void CFDView::OnInitialUpdate()
{
	CListView::OnInitialUpdate();

	pDoc = GetDocument();
	pListCtrl = &GetListCtrl(); //��������� ������ �� ������� ����������

	DWORD ExStyle = pListCtrl->GetExtendedStyle(); //��������� ����� ������
	ExStyle |= LVS_EX_FULLROWSELECT; //��������� ���������� ��������
	pListCtrl->SetExtendedStyle(ExStyle); //��������� �����
	column = 0; //������ �������

	// TODO: ListView ����� ��������� ���������� ����������� ����������������� ���������
	//  � ��������� ���������� ����� ������ ����� ����� GetListCtr().
}

// ����������� CFDView

#ifdef _DEBUG
void CFDView::AssertValid() const
{
	CListView::AssertValid();
}

void CFDView::Dump(CDumpContext& dc) const
{
	CListView::Dump(dc);
}

CFDDoc* CFDView::GetDocument() const // �������� ������������ ������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CFDDoc))); //��������� �� ������
	/*iskindof - �������� ����� ������� � ������ �������
	runtime_class - �������� ��������� ���������*/
	return (CFDDoc*)m_pDocument;
}
#endif //_DEBUG

// ����������� ��������� CFDView
void CFDView::OnViewDriver() {
	
	CFDSet* driver;
	CMapStringToPtr* ptrMap;
	POSITION position;
//	CString a;
	pListCtrl->DeleteAllItems();
	ASSERT(pListCtrl->GetItemCount() == 0); //���������� ��������� � ������

	for (int i = column; i >= 0; i--)
	{
		pListCtrl->DeleteColumn(i); //������� i-��� �������
	//	a.Format("������ �������, %.i", i);
	//	MessageBox(a);
	}
	//MessageBox("������ �������.");
	DisplayDriverColumn();  //������� �������

//	if ((pDoc->cMapDriver.GetSize()) == 0) { //�������� �� ������
		driver = new CFDSet();
		ptrMap = &(pDoc->cMapDriver);
		driver->GetInfoDriver(ptrMap);
		delete driver;
//	}
	position = pDoc->cMapDriver.GetStartPosition();

	CString ID;
	void *ptr;
	char str[3] = " ";
	int i = 0, j = 1;
	CFDSet* Driver;
	while (position) {
		pDoc->cMapDriver.GetNextAssoc(position, ID, ptr); //��������� ������� � ��������� �������
		/*position - �������
		ID - ���� ������������� ��������
		ptr - ���������� ������������ ��������*/
		Driver = ((CFDSet*)ptr);	
	//	AfxMessageBox("������ ��������� Insert");
		pListCtrl->InsertItem(LVIF_TEXT | LVIF_STATE, i, Driver->m_DriversID,
			 /* (i%2)==0 ? LVIS_SELECTED: */ 0, LVIS_SELECTED, 0, 0);
		//a.Format("��������, %.i", i);
		//MessageBox(a);
		/*insert ��������� �������� �������
		set ��������� ���������*/
		//pListCtrl->SetItemText(i, 0, Driver->m_DriversID);
		pListCtrl->SetItemText(i, 1, Driver->m_DriversDriverSurmane);
		pListCtrl->SetItemText(i, 2, Driver->m_DriversDriverName);
		pListCtrl->SetItemText(i, 3, Driver->m_DriversSponsor);
		pListCtrl->SetItemText(i, 4, Driver->m_DriversCategory);
		pListCtrl->SetItemText(i, 5, Driver->m_DriversManufacturer);
		i++;
		Driver = 0;
	}
}

void CFDView::DisplayDriverColumn() {

	LV_COLUMN col;
	col.mask = LVCF_TEXT | LVCF_SUBITEM | LVCF_WIDTH; //�������� �����, text,cx,isubitem

	col.iSubItem = 0; //�����
	col.pszText = _T("Car Number"); //�������� �������
	col.cx = 100; //������
	GetListCtrl().InsertColumn(0, &col); //��������� �������
	column++;
	col.iSubItem = 1;
	col.pszText = _T("Surname");
	col.cx = 125;
	GetListCtrl().InsertColumn(1, &col);
	column++;
	col.iSubItem = 2;
	col.pszText = _T("Name");
	col.cx = 125;
	GetListCtrl().InsertColumn(2, &col);
	column++;
	col.iSubItem = 3;
	col.pszText = _T("Sponsor");
	col.cx = 200;
	GetListCtrl().InsertColumn(3, &col);
	column++;
	col.iSubItem = 4;
	col.pszText = _T("Category");
	col.cx = 170;
	GetListCtrl().InsertColumn(4, &col);
	column++;
	col.iSubItem = 5;
	col.pszText = _T("Car Manufacturer");
	col.cx = 110;
	GetListCtrl().InsertColumn(5, &col);
	column++;
}

void CFDView::OnDeleteDriver()
{
	/*getselectedcount - ���������� ��������� ���������*/
	UINT select = pListCtrl->GetSelectedCount(), i, j; 
	int  item = -1;
	int* count = new int[select];
	CString str;
	CFDSet driver;
	try {
		if (select > 0) {
			for (i = 0; i < select; i++) {
				item = pListCtrl->GetNextItem(item, LVNI_SELECTED); //��������� � ����������
				count[i] = item;
				str = pListCtrl->GetItemText(item, 0);
				driver.DeleteInfoDriver((&(pDoc->cMapDriver)), str); //������� ����
				pListCtrl->Update(item);
			}
			for (i = 0; i < select; i++) {
				pListCtrl->DeleteItem(count[i]); //������� �������
				for (j = i + 1; j < select; j++) {
					if (j == select) {
						break;
					}
					count[j]--;
				}
			}
		}
	}
	catch (CDBException* pException) {
		AfxMessageBox(pException->m_strStateNativeOrigin);
		AfxMessageBox(pException->m_strError);
		pException->Delete();
	}
	delete[] count;
}

void CFDView::OnEditSearchDriver() {

	search = new CString();
	CString str;
	BOOL flag = 0;
	int item = 0, i;
	UINT count = pListCtrl->GetItemCount(); //����������
	Search driver;
	driver.SetInfo(search);
	driver.DoModal();
	try {
		for (i = count; i >= 0; i--) {
			item = pListCtrl->GetNextItem(item, LVNI_ALL);
			str = pListCtrl->GetItemText(item, 0);
			if ((str) == *search) {
				pListCtrl->SetItem(item, 0, LVIF_STATE, NULL, 0, LVIS_SELECTED, LVIS_SELECTED, 0);
				pListCtrl->EnsureVisible(item, TRUE); //�������� ��� ���������
				break;
			}
		}
	}
	catch (CDBException* pException) {
		AfxMessageBox(pException->m_strStateNativeOrigin);
		AfxMessageBox(pException->m_strError);
		pException->Delete();
	}
	delete search;
}


