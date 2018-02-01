
// FDView.h : интерфейс класса CFDView
//

#pragma once
#include "FDDoc.h"

class CFDView : public CListView
{
protected: // создать только из сериализации
	CFDView();
	DECLARE_DYNCREATE(CFDView) //динамическое создание

// Атрибуты
public:
	CFDDoc* GetDocument() const;

// Операции
public:

// Переопределение
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs); //вызывается структурой при создании окна, вложенного в объект
protected:
	virtual void OnInitialUpdate(); // вызывается в первый раз после конструктора

// Реализация
public:
	virtual ~CFDView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Созданные функции схемы сообщений
protected:
	DECLARE_MESSAGE_MAP()
	CListCtrl* pListCtrl; /*Класс инкапсулирует функциональность элемента управления "список", 
						  который отображает коллекцию элементов*/
	CFDDoc* pDoc;
private:
	UINT column;
public:
	void DisplayDriverColumn(); //выводим столбцы
	CString* search; //переменная для поиска
	afx_msg void OnViewDriver(); //вывод базы
	afx_msg void OnDeleteDriver(); //удалить
	afx_msg void OnEditSearchDriver(); //поиск
};

#ifndef _DEBUG  // отладочная версия в FDView.cpp
inline CFDDoc* CFDView::GetDocument() const
   { return reinterpret_cast<CFDDoc*>(m_pDocument); }
#endif

