[Setup]
AppName=KSOT
AppVerName=KSOT 1.0
AppPublisher=invt
AppPublisherURL=http://www.invt.ru
AppSupportURL=http://www.invt.ru
AppUpdatesURL=http://www.invt.ru

DefaultDirName={code:GETAPP}

DisableProgramGroupPage=true
OutputDir=out
OutputBaseFilename=ksot[1.0.5]
;SetupIconFile=16.ico
DisableDirPage=false
UsePreviousAppDir=true
DirExistsWarning=no
AllowUNCPath=false
AppendDefaultDirName=false
UsePreviousGroup=true
DisableFinishedPage=false
AlwaysShowComponentsList=true
ShowComponentSizes=true
FlatComponentsList=true
UsePreviousSetupType=true
UsePreviousTasks=true
AlwaysShowDirOnReadyPage=false
ShowLanguageDialog=no
Uninstallable=true
CreateAppDir=true
AllowCancelDuringInstall=true
Compression=lzma/fast
InternalCompressLevel=none
VersionInfoVersion=1.1
VersionInfoCompany=INVT
VersionInfoDescription=KSOT
VersionInfoCopyright=INVT

UseSetupLdr=true
InfoBeforeFile=
AppCopyright=INVT
SetupLogging=true
VersionInfoProductVersion=1.0
SolidCompression=false
RestartIfNeededByRun=true
AppID={{E66697FF-60C4-43C0-95CF-43A6F52BF78A}
DisableReadyMemo=false
VersionInfoProductName=KSOT
UninstallDisplayIcon={app}\icon.ico
;SetupIconFile=C:\setups\mosmon\mos.ico
DefaultGroupName=KSOT
AppendDefaultGroupName=false
DisableReadyPage=true
CompressionThreads=16
SetupIconFile=icon.ico
VersionInfoTextVersion=Рабочее место КСОТ
PrivilegesRequired=poweruser
ShowTasksTreeLines=true


[Languages]
Name: russian; MessagesFile: compiler:Languages\Russian.isl

[Files]
;Source: ISSkin.dll; DestDir: {app}; Flags: dontcopy; Components: ; Languages:
;Source: Office2007.cjstyles; DestDir: {tmp}; Flags: dontcopy

;Source: lastversion\x64\*.*; DestDir: {code:GetSubscr}; Flags: recursesubdirs ignoreversion createallsubdirs replacesameversion; Check: is64bit; Components:
;Source: lastversion\x64\*.*; DestDir: {app}\GUI; Flags: recursesubdirs ignoreversion createallsubdirs restartreplace replacesameversion; Check: is64bit; Components:
Source: release\*.*; DestDir: {app}; Flags: overwritereadonly recursesubdirs uninsremovereadonly touch replacesameversion createallsubdirs restartreplace ignoreversion; Excludes: *.ini,*.o,*.cpp,*.res,*.cfg
Source: icon.ico; DestDir: {app}; Flags: uninsremovereadonly replacesameversion


[Components]
Name: common_files; Description: Основные файлы приложения; Flags: fixed; Types: full



[CustomMessages]
sql_Caption=Параметры подключения к SQL серверу
sql_Description=Введите параметры подключения к базе данных продукта
sql_Label1_Caption0=Сервер
sql_Label2_Caption0=Пользователь
sql_Label3_Caption0=Пароль
sql_db_Caption0=База данных
sql_ComboBox1_Text0=
sql_user_Text0=sa
sql_password_Text0=
sql_ComboBox2_Text0=kioskmanager
sql_sqlauth_Caption0=Проверка подлинности SQL
;sql_winauth_Caption0=Windows авторизация


[_ISToolPreCompile]
;Name: precompile.bat; Parameters:

[Run]
Filename: {app}\ksot-ui.exe; WorkingDir: {app}; Description: Запустить графический интерфейс пользователя; Flags: nowait postinstall
[LangOptions]
;LanguageName=Russian
;LanguageID=$0419
[Icons]
Name: {group}\Рабочее место КСОТ; Filename: {app}\ksot-ui.exe; WorkingDir: {app}; IconFilename: {app}\icon.ico; IconIndex: 0
[Types]
Name: full; Description: Полный; Flags: iscustom
[Code]
//procedure LoadSkin(lpszPath: String; lpszIniFileName: String);
//external 'LoadSkin@files:isskin.dll stdcall';

// Importing UnloadSkin API from ISSkin.DLL
//procedure UnloadSkin();
//external 'UnloadSkin@files:isskin.dll stdcall';

// Importing ShowWindow Windows API from User32.DLL
function ShowWindow(hWnd: Integer; uType: Integer): Integer;
external 'ShowWindow@user32.dll stdcall';

function InitializeSetup(): Boolean;
begin
//ExtractTemporaryFile('Office2007.cjstyles');
//LoadSkin(ExpandConstant('{tmp}\Office2007.cjstyles'), '');
result:=true;
end;





procedure DeinitializeSetup();
begin
        // Hide Window before unloading skin so user does not get
        // a glimse of an unskinned window before it is closed.
        ShowWindow(StrToInt(ExpandConstant('{wizardhwnd}')), 0);
        //UnloadSkin();
end;


function isEnableSettingsDemo():boolean;
begin
try
if FileExists(expandconstant('{app}\ksot-ui.exe.cfg')) =true then

 result:=false;
except

result:=true;
end;

end;


function is64bit():boolean;
begin
try
if DirExists(expandconstant('{pf64}')) =true then

 result:=true;
except

result:=false;
end;

end;


Procedure InitializeWizard;
Begin
        //ExtractTemporaryFile('Office2007.cjstyles');
        //LoadSkin(ExpandConstant('{tmp}\Office2007.cjstyles'), '');
End;

function dbpresent():boolean;
begin
result:=false;
end;



//
function GETAPP(a:string):string;
var
f:string;
begin
if fileexists(expandconstant('{src}\options.ini')) =true then
f:=ExpandConstant('{ini:{src}\options.ini,app,path|{sd}\ksot}')
else

f:=expandconstant('{reg:HKCU\SOFTWARE\invt\ksot,GUI|{sd}\ksot}');
 if f[1]='"' then f:=copy(f,2,length(f)-1);
  //бывает что при извлечении пути присутствует "-обрезаю ее
result:=f;
 end;

//



 var
 Label1: TLabel;
 Label2: TLabel;
 Label3: TLabel;
 db: TLabel;
 ComboBox1: TComboBox;
 user: TEdit;
 password: TEdit;
 DBfield: TEDIT;
 sqlauth: TRadioButton;
 winauth: TRadioButton;
srv2,authtype, user2,password2,database2:string;
dmo,dmo2, sn: Variant;
i: Integer;



 procedure sql_Activate(Page: TWizardPage);
 begin
 // enter code here...

if not  FileExists (expandconstant('{src}\options.ini')) then
begin
dmo:=CreateOleObject('SQLDMO.Application');
sn:=dmo.ListAvailableSQLServers;
if sn.Count <> 0 then
begin
ComboBox1.Items.Clear;
for i:=1 to sn.Count do
ComboBox1.Items.Add(sn.Item(i));
end;
//чтение запомненых параметров
combobox1.items.add(expandconstant('{reg:HKLM\SOFTWARE\Barsum\bbw,server|127.0.0.1,1433}'));
combobox1.itemindex:=combobox1.items.count-1;

//база
dbfield.text:=expandconstant('{reg:HKLM\SOFTWARE\Barsum\bbw,database|BarsumBW}');

//пользователь

user.text:=expandconstant('{reg:HKLM\SOFTWARE\Barsum\bbw,user|sa}');
//пароль

password.text:=expandconstant('{reg:HKLM\SOFTWARE\Barsum\bbw,pass|}');


//win авторизация
 authtype:=expandconstant('{reg:HKLM\SOFTWARE\Barsum\bbw,winauth|1}');
 if authtype='1' then winauth.checked:=true;
if authtype='0' then sqlauth.checked:=true;
end;



if fileexists(expandconstant('{src}\options.ini'))=true then

begin
srv2:=expandconstant('{ini:{src}\options.ini,db,host| 127.0.0.1}');
combobox1.items.add(srv2);
combobox1.itemindex:=combobox1.items.count-1;

user2:=expandconstant('{ini:{src}\options.ini,db,user| petrosoft}');
user.text:=user2
database2:=expandconstant('{ini:{src}\options.ini,db,database|kioskmanager}');
dbfield.text:=database2;
password2:=expandconstant('{ini:{src}\options.ini,db,password| }');

end;

 end;

 { sql_ShouldSkipPage }

 function sql_ShouldSkipPage(Page: TWizardPage): Boolean;
 begin
 if fileexists (expandconstant ('{app}\usedb') ) then
 begin

 Result := false;
 end

  else result:=true;
 end;

 { sql_BackButtonClick }

 function sql_BackButtonClick(Page: TWizardPage): Boolean;
 begin
 Result := false;
 end;

 { sql_NextkButtonClick }

 function sql_NextButtonClick(Page: TWizardPage): Boolean;

 var
resultcode:integer;
   sql,db:variant;

 script:string;
s:string;

 begin
sql:=CreateOleObject('SQLDMO.SQLServer');
//msgbox(combobox1.text+ ' '+User.text+ ' '+password.text,mbInformation,mb_ok);


if sqlauth.checked= true then sql.connect(combobox1.text,user.text,password.text);
if winauth.checked= true then
begin
 sql.loginsecure:=true;
sql.connect(combobox1.text);


end;
dmo2:=CreateOleObject('SQLDMO.Database');
//sql.Databases(combobox2.text);
script:='USE ' +dbfield.text +#13#10+'GO' +#13#10;
//loadstringfromfile(ExpandConstant('{tmp}\update.sql'),s);
s:=script+s;
sql.ExecuteImmediate(s);
Result := True;



//Запись выбранного пользователем SQL сервера
  RegWriteStringValue(HKEY_LOCAL_MACHINE, 'Software\Barsum\bbw','server', combobox1.text);
    log('WRite new server='+combobox1.text);
//Запись выбранного пользователем    SQL пользователя
  RegWriteStringValue(HKEY_LOCAL_MACHINE, 'Software\Barsum\bbw','user', user.text);
    log('WRite new user='+user.text);

 //Запись выбранного пользователем    SQL пароля
  RegWriteStringValue(HKEY_LOCAL_MACHINE, 'Software\Barsum\bbw','pass', password.text);
    log('WRite new user='+password.text);


     //Запись выбранной пользователем    SQL базы
  RegWriteStringValue(HKEY_LOCAL_MACHINE, 'Software\Barsum\bbw','database', dbfield.text);
    log('WRite new password='+dbfield.text);
 if winauth.checked = true then    RegWriteStringValue(HKEY_LOCAL_MACHINE, 'Software\Barsum\bbw','winauth', '1')

 else
      RegWriteStringValue(HKEY_LOCAL_MACHINE, 'Software\Barsum\bbw','winauth', '0');

 end;
   { sql_CancelButtonClick }

 procedure sql_CancelButtonClick(Page: TWizardPage; var Cancel, Confirm: Boolean);
 begin
 // enter code here...
 end;

 { sql_CreatePage }

 function sql_CreatePage(PreviousPageId: Integer): Integer;
 var
 Page: TWizardPage;
 begin
 Page := CreateCustomPage(
 PreviousPageId,
 ExpandConstant('{cm:sql_Caption}'),
 ExpandConstant('{cm:sql_Description}')
 );

 { Label1 }
 Label1 := TLabel.Create(Page);
 with Label1 do
 begin
 Parent := Page.Surface;
 Caption := ExpandConstant('{cm:sql_Label1_Caption0}');
 Left := ScaleX(40);
 Top := ScaleY(24);
 Width := ScaleX(37);
 Height := ScaleY(13);
 end;

 { Label2 }
 Label2 := TLabel.Create(Page);
 with Label2 do
 begin
 Parent := Page.Surface;
 Caption := ExpandConstant('{cm:sql_Label2_Caption0}');
 Left := ScaleX(112);
 Top := ScaleY(80);
 Width := ScaleX(72);
 Height := ScaleY(13);
 end;

 { Label3 }
 Label3 := TLabel.Create(Page);
 with Label3 do
 begin
 Parent := Page.Surface;
 Caption := ExpandConstant('{cm:sql_Label3_Caption0}');
 Left := ScaleX(112);
 Top := ScaleY(120);
 Width := ScaleX(37);
 Height := ScaleY(13);
 end;

 { db }
 db := TLabel.Create(Page);
 with db do
 begin
 Parent := Page.Surface;
 Caption := ExpandConstant('{cm:sql_db_Caption0}');
 Left := ScaleX(40);
 Top := ScaleY(208);
 Width := ScaleX(65);
 Height := ScaleY(13);

 end;

 { ComboBox1 }
 ComboBox1 := TComboBox.Create(Page);
 with ComboBox1 do
 begin
 Parent := Page.Surface;
 Left := ScaleX(112);
 Top := ScaleY(16);
 Width := ScaleX(282);
 Height := ScaleY(21);
 TabOrder := 0;
 //        items:=GetSQLServersList();
 //Text := ExpandConstant('{cm:sql_ComboBox1_Text0}');
 end;



 { user }
 user := TEdit.Create(Page);
 with user do
 begin
 Parent := Page.Surface;
 Left := ScaleX(216);
 Top := ScaleY(72);
 Width := ScaleX(177);
 Height := ScaleY(21);
 TabOrder := 2;
 Text := ExpandConstant('{cm:sql_user_Text0}');
 end;

 { password }
 password := TEdit.Create(Page);
 with password do
 begin
 Parent := Page.Surface;
 Left := ScaleX(216);
 Top := ScaleY(112);
 Width := ScaleX(177);
 Height := ScaleY(21);
 PasswordChar := '*';
 TabOrder := 3;
 Text := ExpandConstant('{cm:sql_password_Text0}');
 end;

 { ComboBox2 }
 DBfield := TEdit.Create(Page);
 with DBfield do
 begin
 Parent := Page.Surface;
 Left := ScaleX(112);
 Top := ScaleY(200);
 Width := ScaleX(282);
 Height := ScaleY(21);
 TabOrder := 5;
 Text := ExpandConstant('{cm:sql_ComboBox2_Text0}');
 end;

 { sqlauth }
 sqlauth := TRadioButton.Create(Page);
 with sqlauth do
 begin
 Parent := Page.Surface;
 Caption := ExpandConstant('{cm:sql_sqlauth_Caption0}');
 Left := ScaleX(96);
 Top := ScaleY(48);
 Width := ScaleX(185);
 Height := ScaleY(17);
 TabOrder := 1;
 checked:=true;
 end;

 //{ winauth }
 //winauth := TRadioButton.Create(Page);
 //with winauth do
 //begin
 //Parent := Page.Surface;
 //Caption := ExpandConstant('{cm:sql_winauth_Caption0}');
 //Left := ScaleX(96);
 //Top := ScaleY(168);
 //Width := ScaleX(241);
// Height := ScaleY(17);
 //TabOrder := 4;
 //end;

 with Page do
 begin
 OnActivate := @sql_Activate;
 OnShouldSkipPage := @sql_ShouldSkipPage;
 OnBackButtonClick := @sql_BackButtonClick;
 OnNextButtonClick := @sql_NextButtonClick;
 OnCancelButtonClick := @sql_CancelButtonClick;
 end;

 Result := Page.ID;

 end;






 procedure CurPageChanged(CurPageID: Integer);
 var
 resultcode:integer;
 begin
//ShowSkinPage(CurPageID);
//ShowSkinPage(100);
if CurPageID=wpInstalling
then   sql_CreatePage(wpInstalling);

if CurPageID=WpReady then
begin

//Запись выбранной пользователм папки
  RegWriteStringValue(HKEY_LOCAL_MACHINE, 'Software\invt\ksot','GUI', ExpandConstant('{app}'));
    log('WRite new GUI='+ExpandConstant('{app}'));

//поиск файла использования БД USEDB
if fileexists(expandconstant('{app}\usedb'))= true then deletefile(expandconstant('{app}\usedb'));
if dbpresent=true then
begin

end;
end;

 end;





function updgui():boolean;
begin

result:=true;


end;



end.
