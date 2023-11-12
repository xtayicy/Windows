struct
{
     int     iStyle ;
     TCHAR * szText ;
}
button[] =
{
     BS_PUSHBUTTON,      TEXT ("PUSHBUTTON"),
     BS_DEFPUSHBUTTON,   TEXT ("DEFPUSHBUTTON"),
     BS_CHECKBOX,        TEXT ("CHECKBOX"), 
     BS_AUTOCHECKBOX,    TEXT ("AUTOCHECKBOX"),
     BS_RADIOBUTTON,     TEXT ("RADIOBUTTON"),
     BS_3STATE,          TEXT ("3STATE"),
     BS_AUTO3STATE,      TEXT ("AUTO3STATE"),
     BS_GROUPBOX,        TEXT ("GROUPBOX"),
     BS_AUTORADIOBUTTON, TEXT ("AUTORADIO"),
     BS_OWNERDRAW,       TEXT ("OWNERDRAW")
} ;

#define NUM (sizeof button / sizeof button[0])