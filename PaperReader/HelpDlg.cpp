// HelpDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "PaperReader.h"
#include "HelpDlg.h"
#include "afxdialogex.h"
#include "PaperReaderDlg.h"


// CHelpDlg �Ի���

IMPLEMENT_DYNAMIC(CHelpDlg, CDialogEx)

CHelpDlg::CHelpDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CHelpDlg::IDD, pParent)
{

}

CHelpDlg::~CHelpDlg()
{
}

void CHelpDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CHelpDlg, CDialogEx)
	
END_MESSAGE_MAP()


// CHelpDlg ��Ϣ�������


void CHelpDlg::OnMenuHelp()
{
	// TODO: �ڴ���������������
	CPaperReaderDlg pDlg;
	pDlg.DoModal();
}
