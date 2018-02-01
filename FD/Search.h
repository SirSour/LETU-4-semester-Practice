#pragma once


// диалоговое окно Search

class Search : public CDialogEx
{
	DECLARE_DYNAMIC(Search)

public:
	Search(CWnd* pParent = NULL);   // стандартный конструктор
	virtual ~Search();

// Данные диалогового окна
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG1 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // поддержка DDX/DDV
	CString* search;	
	
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	CString m_search;
	void SetInfo(CString* search);	
};
