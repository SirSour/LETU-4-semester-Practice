
// FDDoc.cpp : ���������� ������ CFDDoc
//

#include "stdafx.h"
#include "FD.h"
#include "FDDoc.h"

#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CFDDoc

IMPLEMENT_DYNCREATE(CFDDoc, CDocument) //������������ �������� �������

BEGIN_MESSAGE_MAP(CFDDoc, CDocument) //����� ���������
END_MESSAGE_MAP()

// ��������/����������� CFDDoc
CFDDoc::CFDDoc()
{
	// TODO: �������� ��� ��� ������������ ������ ������������

}

CFDDoc::~CFDDoc()
{
}

BOOL CFDDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: �������� ��� ��������� �������������
	// (��������� SDI ����� �������� ������������ ���� ��������)
	return TRUE;
}

// ������������ CFDDoc

void CFDDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: �������� ��� ����������
	}
	else
	{
		// TODO: �������� ��� ��������
	}
}

// ����������� CFDDoc

#ifdef _DEBUG
void CFDDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CFDDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG
// ������� CFDDoc
