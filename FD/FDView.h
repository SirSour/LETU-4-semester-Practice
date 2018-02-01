
// FDView.h : ��������� ������ CFDView
//

#pragma once
#include "FDDoc.h"

class CFDView : public CListView
{
protected: // ������� ������ �� ������������
	CFDView();
	DECLARE_DYNCREATE(CFDView) //������������ ��������

// ��������
public:
	CFDDoc* GetDocument() const;

// ��������
public:

// ���������������
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs); //���������� ���������� ��� �������� ����, ���������� � ������
protected:
	virtual void OnInitialUpdate(); // ���������� � ������ ��� ����� ������������

// ����������
public:
	virtual ~CFDView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ��������� ������� ����� ���������
protected:
	DECLARE_MESSAGE_MAP()
	CListCtrl* pListCtrl; /*����� ������������� ���������������� �������� ���������� "������", 
						  ������� ���������� ��������� ���������*/
	CFDDoc* pDoc;
private:
	UINT column;
public:
	void DisplayDriverColumn(); //������� �������
	CString* search; //���������� ��� ������
	afx_msg void OnViewDriver(); //����� ����
	afx_msg void OnDeleteDriver(); //�������
	afx_msg void OnEditSearchDriver(); //�����
};

#ifndef _DEBUG  // ���������� ������ � FDView.cpp
inline CFDDoc* CFDView::GetDocument() const
   { return reinterpret_cast<CFDDoc*>(m_pDocument); }
#endif

