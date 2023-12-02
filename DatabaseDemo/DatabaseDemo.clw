; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=ADODlg
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "DatabaseDemo.h"
LastPage=0

ClassCount=8
Class1=CDatabaseDemoApp
Class2=CDatabaseDemoDoc
Class3=CDatabaseDemoView
Class4=CMainFrame
Class6=CAboutDlg

ResourceCount=4
Resource1=IDD_DATABASEDEMO_FORM
Resource2=IDR_MAINFRAME
Class5=CDatabaseDemoSet
Class7=CInputDlg
Resource3=IDD_ABOUTBOX
Class8=ADODlg
Resource4=IDD_DIALOG1

[CLS:CDatabaseDemoApp]
Type=0
HeaderFile=DatabaseDemo.h
ImplementationFile=DatabaseDemo.cpp
Filter=N

[CLS:CDatabaseDemoDoc]
Type=0
HeaderFile=DatabaseDemoDoc.h
ImplementationFile=DatabaseDemoDoc.cpp
Filter=N

[CLS:CDatabaseDemoView]
Type=0
HeaderFile=DatabaseDemoView.h
ImplementationFile=DatabaseDemoView.cpp
Filter=D
BaseClass=CRecordView
VirtualFilter=RVWC
LastObject=ID_DATABASE_ADO


[CLS:CDatabaseDemoSet]
Type=0
HeaderFile=DatabaseDemoSet.h
ImplementationFile=DatabaseDemoSet.cpp
Filter=N

[DB:CDatabaseDemoSet]
DB=1
DBType=ODBC
ColumnCount=1
Column1=[username], 12, 40


[CLS:CMainFrame]
Type=0
HeaderFile=MainFrm.h
ImplementationFile=MainFrm.cpp
Filter=T
LastObject=CMainFrame
BaseClass=CFrameWnd
VirtualFilter=fWC




[CLS:CAboutDlg]
Type=0
HeaderFile=DatabaseDemo.cpp
ImplementationFile=DatabaseDemo.cpp
Filter=D

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[MNU:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_FILE_SAVE_AS
Command5=ID_FILE_PRINT
Command6=ID_FILE_PRINT_PREVIEW
Command7=ID_FILE_PRINT_SETUP
Command8=ID_FILE_MRU_FILE1
Command9=ID_APP_EXIT
Command10=ID_EDIT_UNDO
Command11=ID_EDIT_CUT
Command12=ID_EDIT_COPY
Command13=ID_EDIT_PASTE
Command14=ID_RECORD_FIRST
Command15=ID_RECORD_PREV
Command16=ID_RECORD_NEXT
Command17=ID_RECORD_LAST
Command18=ID_VIEW_TOOLBAR
Command19=ID_VIEW_STATUS_BAR
Command20=ID_APP_ABOUT
Command21=ID_DATABASE_TEST
Command22=ID_DATABASE_ADO
CommandCount=22

[ACL:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_FILE_PRINT
Command5=ID_EDIT_UNDO
Command6=ID_EDIT_CUT
Command7=ID_EDIT_COPY
Command8=ID_EDIT_PASTE
Command9=ID_EDIT_UNDO
Command10=ID_EDIT_CUT
Command11=ID_EDIT_COPY
Command12=ID_EDIT_PASTE
Command13=ID_NEXT_PANE
Command14=ID_PREV_PANE
CommandCount=14

[DLG:IDD_DATABASEDEMO_FORM]
Type=1
Class=CDatabaseDemoView
ControlCount=3
Control1=IDC_STATIC,static,1342308352
Control2=IDC_EDIT_USERNAME,edit,1350631552
Control3=IDC_BUTTON_OK,button,1342242816

[TB:IDR_MAINFRAME]
Type=1
Class=?
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_EDIT_CUT
Command5=ID_EDIT_COPY
Command6=ID_EDIT_PASTE
Command7=ID_FILE_PRINT
Command8=ID_RECORD_FIRST
Command9=ID_RECORD_PREV
Command10=ID_RECORD_NEXT
Command11=ID_RECORD_LAST
Command12=ID_APP_ABOUT
CommandCount=12

[CLS:CInputDlg]
Type=0
HeaderFile=InputDlg2.h
ImplementationFile=InputDlg2.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=CInputDlg

[DLG:IDD_DIALOG1]
Type=1
Class=ADODlg
ControlCount=3
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_LIST1,SysListView32,1350631813

[CLS:ADODlg]
Type=0
HeaderFile=ADODlg.h
ImplementationFile=ADODlg.cpp
BaseClass=CDialog
Filter=D
LastObject=ADODlg
VirtualFilter=dWC

