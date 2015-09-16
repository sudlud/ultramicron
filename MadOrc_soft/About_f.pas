unit About_f;

interface

uses
  Windows, Messages, SysUtils, Variants, Classes, Graphics, Controls, Forms,
  Dialogs, StdCtrls, pngimage, ExtCtrls, Registry, iaRS232;

type
  TAbout = class(TForm)
    Label1: TLabel;
    Image1: TImage;
    Button1: TButton;
    Label2: TLabel;
    Label3: TLabel;
    Label4: TLabel;
    Label5: TLabel;
    Edit1: TEdit;
    Label6: TLabel;
    Edit2: TEdit;
    Label7: TLabel;
    Button2: TButton;
    procedure Button1Click(Sender: TObject);
    procedure FormCreate(Sender: TObject);
    procedure Button2Click(Sender: TObject);
  private
    { Private declarations }
  public
    { Public declarations }
  end;

var
  About: TAbout;

implementation

{$R *.dfm}
uses main;

procedure TAbout.Button1Click(Sender: TObject);
var
  reg: TRegistry;
begin
  reg := TRegistry.Create;                               // Открываем реестр
  reg.RootKey := HKEY_CURRENT_USER;                      // Для текущего пользователя
  reg.OpenKey('Software\USB_Geiger\USB_Geiger', true); // Открываем раздел
  reg.WriteString('Reg_key', Edit1.Text);
  reg.CloseKey;                                          // Закрываем раздел
  reg.Free;
About.Close;
end;

procedure TAbout.Button2Click(Sender: TObject);
var
  vAns: TiaBuf;
begin

if (main.mainFrm.RS232.Active = false) then
begin
  DevPresent:=false;
  main.mainFrm.RS232.Properties.PortNum  := comport_number;
  main.mainFrm.RS232.Properties.BaudRate := CBR_115200;
  main.mainFrm.RS232.Properties.Parity   := NOPARITY;
  main.mainFrm.RS232.Properties.StopBits := ONESTOPBIT;
  main.mainFrm.RS232.Open;
  main.mainFrm.RS232.StartListner;



  if (main.mainFrm.RS232.Active)then
  begin
   DevPresent:=true;

   SetLength(vAns, 1);
   vAns[0]:=$e0; // считать серийный номер МК U_ID_0
   main.mainFrm.RS232.Send(vAns);

   SetLength(vAns, 1);
   vAns[0]:=$e1; // считать серийный номер МК U_ID_1
   main.mainFrm.RS232.Send(vAns);

   SetLength(vAns, 1);
   vAns[0]:=$e2; // считать серийный номер МК U_ID_2
   main.mainFrm.RS232.Send(vAns);

  end;
 end;
end;

procedure TAbout.FormCreate(Sender: TObject);
var
  reg: TRegistry;
begin

  reg := TRegistry.Create;                              // Открываем реестр
  reg.RootKey := HKEY_CURRENT_USER;
  reg.OpenKey('Software\USB_Geiger\USB_Geiger', false);
  Edit1.Text := reg.ReadString('Reg_key');
  reg.CloseKey;                                          // Закрываем раздел
end;

end.
