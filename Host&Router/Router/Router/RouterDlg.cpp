
// RouterDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Router.h"
#include "RouterDlg.h"
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


// CRouterDlg �Ի���



CRouterDlg::CRouterDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CRouterDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CRouterDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_table);
	DDX_Control(pDX, IDC_EDIT1, m_message);
}

BEGIN_MESSAGE_MAP(CRouterDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
END_MESSAGE_MAP()


// CRouterDlg ��Ϣ�������

BOOL CRouterDlg::OnInitDialog()
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

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO:  �ڴ���Ӷ���ĳ�ʼ������
	setting = new Setting();
	InitUI();
	InitEnvironment();

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CRouterDlg::OnSysCommand(UINT nID, LPARAM lParam)
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
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CRouterDlg::OnPaint()
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
HCURSOR CRouterDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CRouterDlg::InitUI()
{
	switch (setting->m_idOfRouter){
	case IDOFROUTER1:
		AfxGetMainWnd()->SetWindowText("Router1");
		break;
	case IDOFROUTER2:
		AfxGetMainWnd()->SetWindowText(_T("Router2"));
		break;
	case IDOFROUTER3:
		AfxGetMainWnd()->SetWindowText(_T("Router3"));
		break;

	}
	DWORD dwStyle = m_table.GetExtendedStyle();                    //����б���������

	dwStyle |= LVS_EX_FULLROWSELECT;
	dwStyle |= LVS_EX_GRIDLINES;
	m_table.SetExtendedStyle(dwStyle);

	
	m_table.InsertColumn(0,"Ŀ������",LVCFMT_LEFT,140);
	m_table.InsertColumn(1, "��һ��", LVCFMT_LEFT,140);
	m_table.InsertItem(0, setting->routing1.aimHost);
	m_table.SetItemText(0, 1, setting->routing1.nextHop);
	m_table.InsertItem(1, setting->routing2.aimHost);
	m_table.SetItemText(1, 1, setting->routing2.nextHop);
	m_table.InsertItem(2, setting->m_host);
	m_table.SetItemText(2, 1, "-");
	//m_table.InsertItem(1, "1.2");
	//m_table.SetItemText(0, 1, setting->routing1.nextHop);

	//m_table.InsertItem(2, "2.1");
	//m_table.SetItemText(2, 1, setting->routing2.aimHost);
	//m_table.InsertItem(3, "2.2");
	//m_table.SetItemText(3, 1, setting->routing2.nextHop);

	//m_table.InsertItem(4, "3.1");
	//m_table.SetItemText(4, 1, setting->m_host);
	//m_table.InsertItem(5, "3.2");
	//m_table.SetItemText(5, 1,"-");


	
}

UINT RecvThread(LPVOID lpParm)
{
	CRouterDlg *dlg = (CRouterDlg*)lpParm;
	char gcInBuffer[1027];
	int length;
	int size = sizeof(sockaddr_in);
	CString strReceive, tempStr;
	while (1)
	{
		if ((length = recvfrom(dlg->m_sock, gcInBuffer, 1024, 0, (struct sockaddr *)&dlg->m_desAddr, &size))>0)
		{
			CString strReceive;
			gcInBuffer[length] = '\0';
			strReceive += gcInBuffer;
			CString temp;
			dlg->m_message.GetWindowTextA(temp);
			CString originalHost;
			CString data;
			CString desHost;
			AfxExtractSubString(originalHost, strReceive, 0, '/');
			AfxExtractSubString(data, strReceive, 1, '/');
			AfxExtractSubString(desHost, strReceive, 2, '/');
			temp += originalHost;
			temp += "->";
			temp += desHost;
			temp += ":";
			temp += data;
			temp += "\r\n";
			dlg->m_message.SetWindowText(temp);
			unsigned short aimPort;
			if (desHost.Compare(dlg->setting->m_host) == 0)
				aimPort = dlg->setting->m_hostPort;
			else if(desHost.Compare(dlg->setting->routing1.aimHost)==0)
				aimPort = dlg->setting->routing1.nextHopPort;
			else
				aimPort = dlg->setting->routing2.nextHopPort;



			struct sockaddr_in addr;
			addr.sin_family = AF_INET;
			addr.sin_port = htons(aimPort);
			addr.sin_addr.s_addr = inet_addr(dlg->setting->m_routerIP);
			sendto(dlg->m_sock, strReceive, strlen(strReceive), 0, (struct sockaddr*)&addr, sizeof(sockaddr));
		}
	}
	return 0;
}
void CRouterDlg::InitEnvironment()
{
	WSADATA	wsaData; //�洢��WSAStartup�������ú󷵻ص�Windows sockets����
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
	{
		MessageBox("WSAStartup ERROR!");
	}
	//�����׽���UDP���ӣ�AF_INET��ʾʹ��IPV4Э�飬SOCK_DGRAM�������ӱ������ͣ�Ĭ��UDPЭ��
	if ((m_sock = socket(AF_INET, SOCK_DGRAM, 0)) == INVALID_SOCKET)
	{
		MessageBox("ERROR: Create Server Socket Error!");
		exit(-1);
	}
	struct sockaddr_in serAddr;
	serAddr.sin_family = AF_INET;
	serAddr.sin_port = htons(setting->m_routerPort);
	serAddr.sin_addr.s_addr = htonl(INADDR_ANY);
	if ((bind(m_sock, (LPSOCKADDR)&serAddr, sizeof(serAddr))) == SOCKET_ERROR)
	{
		MessageBox("ERROR: Bind Socket Error!");
		exit(-1);
	}
	AfxBeginThread(RecvThread, this, THREAD_PRIORITY_NORMAL, 0, 0, NULL);
}
