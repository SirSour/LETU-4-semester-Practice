
// FDView.cpp : реализация класса CFDView
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

// создание/уничтожение CFDView

CFDView::CFDView()
{ /*список отображается в виде отчета, состоящего из столбцов*/
	m_dwDefaultStyle |= (LVS_REPORT); //стиль по умолчанию

}

CFDView::~CFDView() {
	void* ptr;
	CString Driver_;
	CFDSet* driver;
	POSITION position = pDoc->cMapDriver.GetStartPosition(); //начальная позиция
	while (position != NULL) {
		/*перебор всех элементов*/
		pDoc->cMapDriver.GetNextAssoc(position, Driver_, ptr); 
		/*position - позиция
		Driver_ - ключ возвращаемого значения
		ptr - возвращаемое значение*/
		driver = ((CFDSet*)ptr);
		delete driver;
	}
	pDoc->cMapDriver.RemoveAll(); //удаление
}

BOOL CFDView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: изменить класс Window или стили посредством изменения
	//  CREATESTRUCT cs

	return CListView::PreCreateWindow(cs);
}

void CFDView::OnInitialUpdate()
{
	CListView::OnInitialUpdate();

	pDoc = GetDocument();
	pListCtrl = &GetListCtrl(); //получение ссылки на элемент управления

	DWORD ExStyle = pListCtrl->GetExtendedStyle(); //получение стиля списка
	ExStyle |= LVS_EX_FULLROWSELECT; //выделение выбранного элемента
	pListCtrl->SetExtendedStyle(ExStyle); //установка стиля
	column = 0; //индекс столбца

	// TODO: ListView можно заполнить элементами посредством непосредственного обращения
	//  к элементам управления этого списка через вызов GetListCtr().
}

// диагностика CFDView

#ifdef _DEBUG
void CFDView::AssertValid() const
{
	CListView::AssertValid();
}

void CFDView::Dump(CDumpContext& dc) const
{
	CListView::Dump(dc);
}

CFDDoc* CFDView::GetDocument() const // встроена неотлаженная версия
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CFDDoc))); //сообщение об ошибке
	/*iskindof - проверка связи объекта с данным классом
	runtime_class - получает классовую структуру*/
	return (CFDDoc*)m_pDocument;
}
#endif //_DEBUG

// обработчики сообщений CFDView
void CFDView::OnViewDriver() {
	
	CFDSet* driver;
	CMapStringToPtr* ptrMap;
	POSITION position;
//	CString a;
	pListCtrl->DeleteAllItems();
	ASSERT(pListCtrl->GetItemCount() == 0); //количество элементов в списке

	for (int i = column; i >= 0; i--)
	{
		pListCtrl->DeleteColumn(i); //удаляем i-тый столбец
	//	a.Format("Удалил столбец, %.i", i);
	//	MessageBox(a);
	}
	//MessageBox("Вывожу столбцы.");
	DisplayDriverColumn();  //выводим столбцы

//	if ((pDoc->cMapDriver.GetSize()) == 0) { //проверка на размер
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
		pDoc->cMapDriver.GetNextAssoc(position, ID, ptr); //извлекаем элемент и обновляем позицию
		/*position - позиция
		ID - ключ возвращаемого элемента
		ptr - определяет возвращаемое значение*/
		Driver = ((CFDSet*)ptr);	
	//	AfxMessageBox("Сейчас сработает Insert");
		pListCtrl->InsertItem(LVIF_TEXT | LVIF_STATE, i, Driver->m_DriversID,
			 /* (i%2)==0 ? LVIS_SELECTED: */ 0, LVIS_SELECTED, 0, 0);
		//a.Format("Сработал, %.i", i);
		//MessageBox(a);
		/*insert вставляет ключевой столбец
		set вставляет остальные*/
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
	col.mask = LVCF_TEXT | LVCF_SUBITEM | LVCF_WIDTH; //значения стиля, text,cx,isubitem

	col.iSubItem = 0; //номер
	col.pszText = _T("Car Number"); //название столбца
	col.cx = 100; //ширина
	GetListCtrl().InsertColumn(0, &col); //вставляем столбец
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
	/*getselectedcount - количество выбранных элементов*/
	UINT select = pListCtrl->GetSelectedCount(), i, j; 
	int  item = -1;
	int* count = new int[select];
	CString str;
	CFDSet driver;
	try {
		if (select > 0) {
			for (i = 0; i < select; i++) {
				item = pListCtrl->GetNextItem(item, LVNI_SELECTED); //переходим к следующему
				count[i] = item;
				str = pListCtrl->GetItemText(item, 0);
				driver.DeleteInfoDriver((&(pDoc->cMapDriver)), str); //удаляем инфо
				pListCtrl->Update(item);
			}
			for (i = 0; i < select; i++) {
				pListCtrl->DeleteItem(count[i]); //удаляем элемент
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
	UINT count = pListCtrl->GetItemCount(); //количество
	Search driver;
	driver.SetInfo(search);
	driver.DoModal();
	try {
		for (i = count; i >= 0; i--) {
			item = pListCtrl->GetNextItem(item, LVNI_ALL);
			str = pListCtrl->GetItemText(item, 0);
			if ((str) == *search) {
				pListCtrl->SetItem(item, 0, LVIF_STATE, NULL, 0, LVIS_SELECTED, LVIS_SELECTED, 0);
				pListCtrl->EnsureVisible(item, TRUE); //вызываем для выделения
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


