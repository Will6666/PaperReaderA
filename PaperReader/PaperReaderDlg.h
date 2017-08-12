
// PaperReaderDlg.h : ͷ�ļ�
//

#pragma once
#include "afxwin.h"
#include "CvvImage.h"
#include "cv.h"
#include "cxcore.h"
#include "highgui.h"
#include <iostream>

// CPaperReaderDlg �Ի���
class CPaperReaderDlg : public CDialogEx
{
// ����
public:
	CPaperReaderDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_PAPERREADER_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedBtnCam();
	afx_msg void OnClose();
	afx_msg void OnBnClickedBtnYuejuan();
	afx_msg void OnBnClickedBtnDaoru();
	afx_msg void OnBnClickedBtnShoudongluru();
	afx_msg void OnBnClickedBtnAutoyuejuan();
	afx_msg void OnBnClickedBtnDaochu();

public:	
	static CvCapture* m_pCapture;
	static IplImage* m_pFrame;
	bool m_Opened;
	bool m_checked;
	bool m_yuejuan;
	CButton m_btn_openCam;
	static CStatic m_Pic;
	static VOID CALLBACK TimerProc(HWND hwnd, UINT uMsg, UINT_PTR idEvent, DWORD dwTime);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnBnClickedBtnXuanqu();
	int coordinate[100][2];
	static int num;//�������
	CString m_edit_coordinate;
	TCHAR szBuffer[20];
	CButton m_btn_xuanqu;

	static int ptArray[200][2];//��������������
	static int rightnum;//������
	afx_msg void OnBnClickedBtnShow();
	int m_edit_zhengda;//�༭�����
	int m_edit_yixuantishu;//�༭�����
	afx_msg void OnMenuExit();
	afx_msg void OnMenuHelp();
};