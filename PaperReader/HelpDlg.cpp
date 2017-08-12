// HelpDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "PaperReader.h"
#include "HelpDlg.h"
#include "afxdialogex.h"
#include "PaperReaderDlg.h"


// CHelpDlg 对话框

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


// CHelpDlg 消息处理程序


void CHelpDlg::OnMenuHelp()
{
	// TODO: 在此添加命令处理程序代码
	CPaperReaderDlg pDlg;
	pDlg.DoModal();
}
