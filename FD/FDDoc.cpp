
// FDDoc.cpp : реализация класса CFDDoc
//

#include "stdafx.h"
#include "FD.h"
#include "FDDoc.h"

#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CFDDoc

IMPLEMENT_DYNCREATE(CFDDoc, CDocument) //динамическое создание объекта

BEGIN_MESSAGE_MAP(CFDDoc, CDocument) //схема сообщений
END_MESSAGE_MAP()

// создание/уничтожение CFDDoc
CFDDoc::CFDDoc()
{
	// TODO: добавьте код для одноразового вызова конструктора

}

CFDDoc::~CFDDoc()
{
}

BOOL CFDDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: добавьте код повторной инициализации
	// (Документы SDI будут повторно использовать этот документ)
	return TRUE;
}

// сериализация CFDDoc

void CFDDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: добавьте код сохранения
	}
	else
	{
		// TODO: добавьте код загрузки
	}
}

// диагностика CFDDoc

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
// команды CFDDoc
