
// PaperReaderDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "PaperReader.h"
#include "PaperReaderDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
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


// CPaperReaderDlg 对话框


//声明两个变量，获取摄像头和画面
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


// CPaperReaderDlg 消息处理程序

BOOL CPaperReaderDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
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

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
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

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CPaperReaderDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CPaperReaderDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


//打开摄像头按钮
void CPaperReaderDlg::OnBnClickedBtnCam()
{
	// TODO: 在此添加控件通知处理程序代码
	if(!m_Opened)
	{
		if(!(m_pCapture=cvCaptureFromCAM(0)))
		{
			MessageBox(TEXT("摄像头打开失败！"));
			return;
		}  
		else
		{
			SetTimer(1, 10, TimerProc);
			m_Opened = true;
			m_btn_openCam.SetWindowText(TEXT("关闭摄像头"));
		}
	}
	else
	{
		KillTimer(1);
		m_Opened = false;
		m_btn_openCam.SetWindowText(TEXT("打开摄像头"));

		if(m_pCapture)
		{
			cvReleaseCapture(&m_pCapture);
			m_pCapture = NULL;
		}
		this->RedrawWindow();
	}

}

//关闭按钮
void CPaperReaderDlg::OnClose()
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	KillTimer(1);
	KillTimer(2);
	cvReleaseCapture(&m_pCapture);
	CDialogEx::OnClose();
}

//导入信息按钮
void CPaperReaderDlg::OnBnClickedBtnDaoru()
{
	// TODO: 在此添加控件通知处理程序代码
}

//手动录入信息按钮
void CPaperReaderDlg::OnBnClickedBtnShoudongluru()
{
	// TODO: 在此添加控件通知处理程序代码
}

//阅卷按钮
void CPaperReaderDlg::OnBnClickedBtnYuejuan()
{
	// TODO: 在此添加控件通知处理程序代码
	SetTimer(2,10,TimerProc);
	
}

//自动阅卷按钮
void CPaperReaderDlg::OnBnClickedBtnAutoyuejuan()
{
	// TODO: 在此添加控件通知处理程序代码
}

//导出成绩单按钮
void CPaperReaderDlg::OnBnClickedBtnDaochu()
{
	// TODO: 在此添加控件通知处理程序代码
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
			IplImage *pGray = cvCreateImage(cvGetSize(m_pFrame),8,1);//直接二值化显示
			cvCvtColor(m_pFrame,pGray,CV_BGR2GRAY);//直接二值化显示
			cvThreshold(pGray,pGray,100,255,CV_THRESH_BINARY);//直接二值化显示
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
	// TODO: 在此添加消息处理程序代码和/或调用默认值
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

//取点按钮
void CPaperReaderDlg::OnBnClickedBtnXuanqu()
{
	// TODO: 在此添加控件通知处理程序代码
	if (!m_checked == true)
	{
		m_checked = true;
		m_btn_xuanqu.SetWindowTextA("选取完成");
		//并且数据清零
		ptArray.RemoveAll();
		num = 0;
		UpdateData(TRUE);
		m_edit_coordinate = TEXT("");
		UpdateData(FALSE);
	}
	else
	{
		m_checked = false;
		m_btn_xuanqu.SetWindowTextA("重新选取");
	}

}
