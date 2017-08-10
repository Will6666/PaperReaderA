
// PaperReaderDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "PaperReader.h"
#include "PaperReaderDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CPaperReaderDlg �Ի���


//����������������ȡ����ͷ�ͻ���
CvCapture* CPaperReaderDlg:: m_pCapture ;
IplImage* CPaperReaderDlg::m_pFrame;
CStatic CPaperReaderDlg::m_Pic;


CPaperReaderDlg::CPaperReaderDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CPaperReaderDlg::IDD, pParent)
	, m_edit_coordinate(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_Opened = false;
	m_checked = false;
	num = 0;
}

void CPaperReaderDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BTN_CAM, m_btn_openCam);
	DDX_Control(pDX, IDC_PIC_CAM, m_Pic);
	DDX_Text(pDX, IDC_EDIT_ZUOBIAO, m_edit_coordinate);
	DDX_Control(pDX, IDC_BTN_XUANQU, m_btn_xuanqu);
}

BEGIN_MESSAGE_MAP(CPaperReaderDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BTN_CAM, &CPaperReaderDlg::OnBnClickedBtnCam)
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_BTN_YUEJUAN, &CPaperReaderDlg::OnBnClickedBtnYuejuan)
	ON_BN_CLICKED(IDC_BTN_DAORU, &CPaperReaderDlg::OnBnClickedBtnDaoru)
	ON_BN_CLICKED(IDC_BTN_SHOUDONGLURU, &CPaperReaderDlg::OnBnClickedBtnShoudongluru)
	ON_BN_CLICKED(IDC_BTN_AUTOYUEJUAN, &CPaperReaderDlg::OnBnClickedBtnAutoyuejuan)
	ON_BN_CLICKED(IDC_BTN_DAOCHU, &CPaperReaderDlg::OnBnClickedBtnDaochu)
	ON_WM_TIMER()
	ON_WM_LBUTTONUP()
	ON_BN_CLICKED(IDC_BTN_XUANQU, &CPaperReaderDlg::OnBnClickedBtnXuanqu)
END_MESSAGE_MAP()


// CPaperReaderDlg ��Ϣ�������

BOOL CPaperReaderDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CPaperReaderDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CPaperReaderDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CPaperReaderDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


//������ͷ��ť
void CPaperReaderDlg::OnBnClickedBtnCam()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if(!m_Opened)
	{
		if(!(m_pCapture=cvCaptureFromCAM(0)))
		{
			MessageBox(TEXT("����ͷ��ʧ�ܣ�"));
			return;
		}  
		else
		{
			SetTimer(1, 10, TimerProc);
			m_Opened = true;
			m_btn_openCam.SetWindowText(TEXT("�ر�����ͷ"));
		}
	}
	else
	{
		KillTimer(1);
		m_Opened = false;
		m_btn_openCam.SetWindowText(TEXT("������ͷ"));

		if(m_pCapture)
		{
			cvReleaseCapture(&m_pCapture);
			m_pCapture = NULL;
		}
		this->RedrawWindow();
	}

}

//�رհ�ť
void CPaperReaderDlg::OnClose()
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	KillTimer(1);
	KillTimer(2);
	cvReleaseCapture(&m_pCapture);
	CDialogEx::OnClose();
}

//������Ϣ��ť
void CPaperReaderDlg::OnBnClickedBtnDaoru()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}

//�ֶ�¼����Ϣ��ť
void CPaperReaderDlg::OnBnClickedBtnShoudongluru()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}

//�ľ�ť
void CPaperReaderDlg::OnBnClickedBtnYuejuan()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	SetTimer(2,10,TimerProc);
	
}

//�Զ��ľ�ť
void CPaperReaderDlg::OnBnClickedBtnAutoyuejuan()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}

//�����ɼ�����ť
void CPaperReaderDlg::OnBnClickedBtnDaochu()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}


VOID CALLBACK CPaperReaderDlg::TimerProc(
	HWND hwnd,         // handle to window
	UINT uMsg,         // WM_TIMER message
	UINT_PTR idEvent,  // timer identifier
	DWORD dwTime	   // current system time
	)
{

	CRect rect;
	HDC hDC;
	CvvImage cimg;
	if(idEvent == 1 && m_pCapture)			
	{
		m_pFrame =cvQueryFrame(m_pCapture);

		if(m_Pic.GetSafeHwnd())
		{
			hDC = m_Pic.GetDC()->GetSafeHdc();
			m_Pic.GetClientRect(&rect);
			IplImage *pGray = cvCreateImage(cvGetSize(m_pFrame),8,1);//ֱ�Ӷ�ֵ����ʾ
			cvCvtColor(m_pFrame,pGray,CV_BGR2GRAY);//ֱ�Ӷ�ֵ����ʾ
			cvThreshold(pGray,pGray,100,255,CV_THRESH_BINARY);//ֱ�Ӷ�ֵ����ʾ
			cimg.CopyOf(pGray);
			cimg.DrawToHDC(hDC,&rect);
			DeleteDC(hDC);
		}
	}
	if (idEvent == 2)
	{
		hDC = m_Pic.GetDC()->GetSafeHdc();
// 		SetPixel(hDC,point.x,point.y,RGB(0,0,0));
// 		SetPixel(hDC,point.x+1,point.y+1,RGB(0,0,0));
		DeleteDC(hDC);
	}
}


CArray<CPoint,CPoint>ptArray;
void CPaperReaderDlg::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	if (m_checked == true)
	{
		ptArray.Add(point);
		wsprintf(szBuffer,TEXT("%d,%d "),ptArray.GetAt(num),ptArray.GetAt(num));

		UpdateData(TRUE);
		m_edit_coordinate += szBuffer;
		UpdateData(FALSE);
		num +=1;
	}
	//SetTimer(2,10,TimerProc);
	CDialogEx::OnLButtonUp(nFlags, point);
}

//ȡ�㰴ť
void CPaperReaderDlg::OnBnClickedBtnXuanqu()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if (!m_checked == true)
	{
		m_checked = true;
		m_btn_xuanqu.SetWindowTextA("ѡȡ���");
		//������������
		ptArray.RemoveAll();
		num = 0;
		UpdateData(TRUE);
		m_edit_coordinate = TEXT("");
		UpdateData(FALSE);
	}
	else
	{
		m_checked = false;
		m_btn_xuanqu.SetWindowTextA("����ѡȡ");
	}

}
