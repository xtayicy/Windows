; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CMainFrame
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "MFCSingleDemo.h"
LastPage=0

ClassCount=7
Class1=CMFCSingleDemoApp
Class2=CMFCSingleDemoDoc
Class3=CMFCSingleDemoView
Class4=CMainFrame

ResourceCount=4
Resource1=IDR_MAINFRAME
Class5=CAboutDlg
Resource2=IDD_ABOUTBOX
Class6=CScrollDlg
Resource3=IDD_DIALOG_SCROLL
Class7=CDialogModalAndModeless
Resource4=IDD_DIALOG

[CLS:CMFCSingleDemoApp]
Type=0
HeaderFile=MFCSingleDemo.h
ImplementationFile=MFCSingleDemo.cpp
Filter=N
LastObject=CMFCSingleDemoApp

[CLS:CMFCSingleDemoDoc]
Type=0
HeaderFile=MFCSingleDemoDoc.h
ImplementationFile=MFCSingleDemoDoc.cpp
Filter=N
LastObject=CMFCSingleDemoDoc

[CLS:CMFCSingleDemoView]
Type=0
HeaderFile=MFCSingleDemoView.h
ImplementationFile=MFCSingleDemoView.cpp
Filter=C
BaseClass=CView
VirtualFilter=VWC
LastObject=CMFCSingleDemoView


[CLS:CMainFrame]
Type=0
HeaderFile=MainFrm.h
ImplementationFile=MainFrm.cpp
Filter=T
LastObject=ID_FILE_OPEN
BaseClass=CFrameWnd
VirtualFilter=fWC




[CLS:CAboutDlg]
Type=0
HeaderFile=MFCSingleDemo.cpp
ImplementationFile=MFCSingleDemo.cpp
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
Command14=ID_VIEW_TOOLBAR
Command15=ID_VIEW_STATUS_BAR
Command16=ID_COLOR_BLACK
Command17=ID_COLOR_RED
Command18=ID_COLOR_BLUE
Command19=ID_COLOR_YELLOW
Command20=ID_COLOR_CUSTOM
Command21=ID_APP_ABOUT
Command22=ID_DIALOG_MODAL
Command23=ID_DIALOG_MODELESS
CommandCount=23

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
Command8=ID_APP_ABOUT
CommandCount=8

[DLG:IDD_DIALOG_SCROLL]
Type=1
Class=CScrollDlg
ControlCount=4
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,static,1342308352
Control4=IDC_SLIDER1,msctls_trackbar32,1342242840

[CLS:CScrollDlg]
Type=0
HeaderFile=ScrollDlg.h
ImplementationFile=ScrollDlg.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=CScrollDlg

[DLG:IDD_DIALOG]
Type=1
Class=CDialogModalAndModeless
ControlCount=3
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_TEXT,static,1342308352

[CLS:CDialogModalAndModeless]
Type=0
HeaderFile=DialogModalAndModeless.h
ImplementationFile=DialogModalAndModeless.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=CDialogModalAndModeless

