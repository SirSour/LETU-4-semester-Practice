// Search.cpp: ���� ����������
//

#include "stdafx.h"
#include "FD.h"
#include "Search.h"
#include "afxdialogex.h"
#include "FDView.h"


// ���������� ���� Search

IMPLEMENT_DYNAMIC(Search, CDialogEx)

Search::Search(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG1, pParent)
	, m_search(_T(""))
{

}

Search::~Search()
{
}

void Search::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_FIND_DRIVER, m_search);
}

BEGIN_MESSAGE_MAP(Search, CDialogEx)
	ON_BN_CLICKED(IDOK, &Search::OnBnClickedOk)
END_MESSAGE_MAP()

void Search::SetInfo(CString* search) {

	(this->search) = search; //����
}

// ����������� ��������� Search

void Search::OnBnClickedOk() {
	UpdateData(1); //������������� ������ ����
	(this->search)->Format("%s", m_search); //Format - ��������������
	AfxMessageBox("Done.", MB_ICONINFORMATION);
	CDialogEx::OnOK();
}

