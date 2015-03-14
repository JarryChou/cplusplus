
// Host1Dlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Host.h"
#include "HostDlg.h"
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


// CHost1Dlg �Ի���



CHostDlg::CHostDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CHostDlg::IDD, pParent)
	, m_dataToSend(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CHostDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT3, m_message);
	DDX_Text(pDX, IDC_EDIT1, m_dataToSend);
}

BEGIN_MESSAGE_MAP(CHostDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_RADIO1, &CHostDlg::OnBnClickedRadio1)
	ON_BN_CLICKED(IDC_RADIO2, &CHostDlg::OnBnClickedRadio2)
	ON_BN_CLICKED(IDC_BUTTON1, &CHostDlg::OnBnClickedButton1)
END_MESSAGE_MAP()


// CHost1Dlg ��Ϣ�������

BOOL CHostDlg::OnInitDialog()
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

void CHostDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CHostDlg::OnPaint()
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
HCURSOR CHostDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CHostDlg::OnBnClickedRadio1()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	((CButton*)GetDlgItem(IDC_RADIO2))->SetCheck(false);
}


void CHostDlg::OnBnClickedRadio2()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	((CButton*)GetDlgItem(IDC_RADIO1))->SetCheck(false);
}


void CHostDlg::InitUI()
{
	switch (setting->m_idOfHost){
	case IDOFHOST1:
		AfxGetMainWnd()->SetWindowText("Host1");
		((CButton*)GetDlgItem(IDC_RADIO1))->SetWindowText("Host2");
		((CButton*)GetDlgItem(IDC_RADIO2))->SetWindowText("Host3");
		break;
	case IDOFHOST2:
		AfxGetMainWnd()->SetWindowText(_T("Host2"));
		((CButton*)GetDlgItem(IDC_RADIO1))->SetWindowText("Host1");
		((CButton*)GetDlgItem(IDC_RADIO2))->SetWindowText("Host3");
		break;
	case IDOFHOST3:
		AfxGetMainWnd()->SetWindowText(_T("Host3"));
		((CButton*)GetDlgItem(IDC_RADIO1))->SetWindowText("Host1");
		((CButton*)GetDlgItem(IDC_RADIO2))->SetWindowText("Host2");
		break;

	}
	((CButton*)GetDlgItem(IDC_RADIO1))->SetCheck(true);
}

UINT RecvThread(LPVOID lpParm)
{
	CHostDlg *dlg = (CHostDlg*)lpParm;
	char gcInBuffer[1027];
	int length;
	int size = sizeof(sockaddr_in);

	while (1)
	{
		if ((length = recvfrom(dlg->m_sock, gcInBuffer, 1024, 0, (struct sockaddr *)&dlg->m_routerAddr, &size))>0)
		{
			CString strReceive;
			gcInBuffer[length] = '\0';
			strReceive += gcInBuffer;
			CString temp;
			dlg->m_message.GetWindowTextA(temp);
			temp += "�յ�����";
			CString originalHost;
			CString data;
			AfxExtractSubString(originalHost, strReceive, 0, '/');
			AfxExtractSubString(data, strReceive, 1, '/');
			temp += " ";
			temp += originalHost;
			temp += " ";
			temp += "������";
			temp += " ";
			temp += data;
			temp += "\r\n";
			dlg->m_message.SetWindowText(temp);
		}
	}
	return 0;
}

void CHostDlg::InitEnvironment()
{
	WSADATA	wsaData;
	PHOSTENT hostinfo;
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
	{
		MessageBox("WSAStartup ERROR!");
	}

	if ((m_sock = socket(AF_INET, SOCK_DGRAM, 0)) == INVALID_SOCKET)
	{
		MessageBox("ERROR: Create Client Socket Error!");
		exit(-1);
	}
	m_routerAddr.sin_family = AF_INET;
	m_routerAddr.sin_port = htons(setting->m_routerPort);
	m_routerAddr.sin_addr.s_addr = inet_addr(setting->m_routerIP);


	struct sockaddr_in m_hostAddr;
	m_hostAddr.sin_family = AF_INET;
	m_hostAddr.sin_port = htons(setting->m_hostPort);
	(m_hostAddr.sin_addr).s_addr = htonl(INADDR_ANY);
	if ((bind(m_sock, (LPSOCKADDR)&m_hostAddr, sizeof(m_hostAddr))) == SOCKET_ERROR)
	{
		MessageBox("ERROR: Bind Socket Error!");
		exit(-1);
	}

	AfxBeginThread(RecvThread, this, THREAD_PRIORITY_NORMAL, 0, 0, NULL);

}

void CHostDlg::OnBnClickedButton1()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
	
	if(m_dataToSend.IsEmpty())
	{
		AfxMessageBox("������Ҫ���͵����ݣ�");
		return;
	}
	CString aimHost;
	if (((CButton*)GetDlgItem(IDC_RADIO1))->GetCheck() == 1)
		aimHost = setting->aimHost1;
	else
		aimHost = setting->aimHost2;
	CString sendTemp = setting->m_host;
	sendTemp.Append("/");
	sendTemp.Append(m_dataToSend);
	sendTemp.Append("/");
	sendTemp.Append(aimHost);
	sendto(m_sock, sendTemp, strlen(sendTemp), 0, (struct sockaddr*)&m_routerAddr, sizeof(sockaddr));
	CString temp;
	m_message.GetWindowTextA(temp);
	
	temp += "��������";
	temp.Append(" ");
	temp.Append(m_dataToSend);
	temp.Append(" ");
	temp.Append("��Ŀ������ ");
	temp.Append(aimHost);
	temp.Append(" ");
	temp.Append("�ɹ�");
	temp += "\r\n";
	m_message.SetWindowTextA(temp);
	
}
